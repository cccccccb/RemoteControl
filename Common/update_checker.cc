//
// Aspia Project
// Copyright (C) 2016-2023 Dmitry Chapyshev <dmitry@aspia.ru>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
//

#include "Common/update_checker.h"

#include "Base/environment.h"
#include "Base/logging.h"
#include "Base/version.h"
#include "Base/memory/byte_array.h"
#include "Base/net/curl_util.h"

namespace common {

class UpdateChecker::Runner : public std::enable_shared_from_this<Runner>
{
public:
    Runner(std::shared_ptr<base::TaskRunner> owner_task_runner, Delegate* delegate)
        : owner_task_runner_(std::move(owner_task_runner)),
          delegate_(delegate)
    {
        DCHECK(owner_task_runner_);
        DCHECK(delegate_);
    }

    ~Runner()
    {
        dettach();
    }

    void dettach()
    {
        delegate_ = nullptr;
    }

    void onFinished(const base::ByteArray& response)
    {
        if (!owner_task_runner_->belongsToCurrentThread())
        {
            owner_task_runner_->postTask(std::bind(&Runner::onFinished, shared_from_this(), response));
            return;
        }

        if (delegate_)
        {
            delegate_->onUpdateCheckedFinished(response);
            delegate_ = nullptr;
        }
    }

private:
    std::shared_ptr<base::TaskRunner> owner_task_runner_;
    Delegate* delegate_ = nullptr;

    DISALLOW_COPY_AND_ASSIGN(Runner);
};

//--------------------------------------------------------------------------------------------------
UpdateChecker::UpdateChecker() = default;

//--------------------------------------------------------------------------------------------------
UpdateChecker::~UpdateChecker()
{
    if (runner_)
    {
        runner_->dettach();
        runner_.reset();
    }
    thread_.stop();
}

//--------------------------------------------------------------------------------------------------
void UpdateChecker::setUpdateServer(std::string update_server)
{
    update_server_ = update_server;
}

//--------------------------------------------------------------------------------------------------
void UpdateChecker::setPackageName(std::string package_name)
{
    package_name_ = package_name;
}

//--------------------------------------------------------------------------------------------------
void UpdateChecker::start(std::shared_ptr<base::TaskRunner> owner_task_runner, Delegate* delegate)
{
    runner_ = std::make_shared<Runner>(std::move(owner_task_runner), delegate);
    thread_.start(std::bind(&UpdateChecker::run, this));
}

//--------------------------------------------------------------------------------------------------
static size_t writeDataFunc(void* ptr, size_t size, size_t nmemb, base::ByteArray* buffer)
{
    size_t append_size = size * nmemb;
    base::append(buffer, ptr, append_size);
    return append_size;
}

//--------------------------------------------------------------------------------------------------
void UpdateChecker::run()
{
    base::Version version(REMOTECONTROL_VERSION_MAJOR, REMOTECONTROL_VERSION_MINOR, REMOTECONTROL_VERSION_PATCH);

    std::string url(update_server_);
    url += "/update.php?";
    url += "package=" + package_name_;
    url += '&';
    url += "version=" + version.toString(3);

    LOG(LS_INFO) << "Start checking for updates. Url: " << url;

    base::ScopedCURL curl;
    curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl.get(), CURLOPT_NOPROGRESS, 1);
    curl_easy_setopt(curl.get(), CURLOPT_MAXREDIRS, 15);

    long verify_peer = 1;
    if (base::Environment::has("ASPIA_NO_VERIFY_TLS_PEER"))
        verify_peer = 0;

    base::ByteArray response;

    curl_easy_setopt(curl.get(), CURLOPT_SSL_VERIFYPEER, verify_peer);
    curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, writeDataFunc);
    curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &response);

    base::ScopedCURLM multi_curl;
    curl_multi_add_handle(multi_curl.get(), curl.get());

    int still_running = 1;
    do
    {
        CURLMcode mc = curl_multi_perform(multi_curl.get(), &still_running);
        if (!mc)
        {
              // Wait for activity, timeout or "nothing".
              mc = curl_multi_poll(multi_curl.get(), nullptr, 0, 1000, nullptr);
        }

        if (mc)
        {
            LOG(LS_WARNING) << "curl_multi_poll failed: " << mc;
            response.clear();
            break;
        }

        if (thread_.isStopping())
        {
            LOG(LS_INFO) << "Update check canceled";
            response.clear();
            break;
        }
    }
    while (still_running);

    curl_multi_remove_handle(multi_curl.get(), curl.get());

    if (!thread_.isStopping())
    {
        LOG(LS_INFO) << "Checking is finished: " << base::toStdString(response);
        if (runner_)
            runner_->onFinished(response);
    }
}

} // namespace common
