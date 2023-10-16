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

#include "Base/logging.h"

#include "Base/filesystem.hpp"
#include "Base/debug.h"
#include "Base/endian_util.h"
#include "Base/environment.h"
#include "Base/system_time.h"
#include "Base/strings/string_number_conversions.h"
#include "Base/strings/unicode.h"

#include <fstream>
#include <iomanip>
#include <mutex>
#include <ostream>
#include <thread>
#include <algorithm>

#if defined(OS_WIN)
#include <Windows.h>
#include <Psapi.h>
#endif // defined(OS_WIN)

#if defined(OS_LINUX)
#include <linux/limits.h>
#include <unistd.h>
#endif // defined(OS_LINUX)

#if defined(OS_MAC)
#include <mach-o/dyld.h>
#include <sys/syslimits.h>
#endif // defined(OS_MAC)

namespace base {

namespace {

const size_t kDefaultMaxLogFileSize = 2 * 1024 * 1024; // 2 Mb.
const size_t kDefaultMaxLogFileAge = 14; // 14 days.

LoggingSeverity g_min_log_level = LOG_LS_WARNING;
LoggingDestination g_logging_destination = LOG_DEFAULT;

size_t g_max_log_file_size = kDefaultMaxLogFileSize;
size_t g_max_log_file_age = kDefaultMaxLogFileAge;
int g_log_file_number = -1;

ghc::filesystem::path g_log_dir_path;
ghc::filesystem::path g_log_file_path;
std::ofstream g_log_file;
std::mutex g_log_file_lock;

//--------------------------------------------------------------------------------------------------
const char* severityName(LoggingSeverity severity)
{
    static const char* const kLogSeverityNames[] = { "I", "W", "E", "F" };

    static_assert(LOG_LS_NUMBER == std::size(kLogSeverityNames), "");

    if (severity >= 0 && severity < LOG_LS_NUMBER)
        return kLogSeverityNames[severity];

    return "UNKNOWN";
}

//--------------------------------------------------------------------------------------------------
void removeOldFiles(const ghc::filesystem::path& path,
                    const ghc::filesystem::file_time_type& current_time,
                    size_t max_file_age)
{
    ghc::filesystem::file_time_type time = current_time - std::chrono::hours(24U * max_file_age);

    std::error_code ignored_code;
    for (const auto& item : ghc::filesystem::directory_iterator(path, ignored_code))
    {
        std::error_code error_code;
        if (item.is_directory(error_code))
            continue;

        if (item.last_write_time(error_code) < time)
            ghc::filesystem::remove(item.path(), ignored_code);
    }
}

//--------------------------------------------------------------------------------------------------
ghc::filesystem::path defaultLogFileDir()
{
    std::error_code error_code;

    ghc::filesystem::path path = ghc::filesystem::temp_directory_path(error_code);
    if (error_code)
        return ghc::filesystem::path();

    path.append("RemoteControll");
    return path;
}

//--------------------------------------------------------------------------------------------------
bool initLoggingUnlocked(const std::string& prefix)
{
    g_log_file.close();

    if (!(g_logging_destination & LOG_TO_FILE))
        return true;

    // The next log file must have a number higher than the current one.
    ++g_log_file_number;

    ghc::filesystem::path file_dir = g_log_dir_path;
    if (file_dir.empty())
        file_dir = defaultLogFileDir();

    if (file_dir.empty())
        return false;

    std::error_code error_code;
    if (!ghc::filesystem::exists(file_dir, error_code))
    {
        if (error_code)
            return false;

        if (!ghc::filesystem::create_directories(file_dir, error_code))
            return false;
    }

    SystemTime time = SystemTime::now();

    std::ostringstream file_name_stream;
    file_name_stream << prefix.c_str() << '-'
                     << std::setfill('0')
                     << std::setw(4) << time.year()
                     << std::setw(2) << time.month()
                     << std::setw(2) << time.day()
                     << '-'
                     << std::setw(2) << time.hour()
                     << std::setw(2) << time.minute()
                     << std::setw(2) << time.second()
                     << '.'
                     << std::setw(3) << time.millisecond()
                     << '.'
                     << g_log_file_number
                     << ".log";

    ghc::filesystem::path file_path(file_dir);
    file_path.append(file_name_stream.str());

    g_log_file.open(file_path);
    if (!g_log_file.is_open())
        return false;

    if (g_max_log_file_age != 0)
    {
        ghc::filesystem::file_time_type file_time =
            ghc::filesystem::last_write_time(file_path, error_code);
        if (!error_code)
            removeOldFiles(file_dir, file_time, g_max_log_file_age);
    }

    g_log_file_path = std::move(file_path);
    return true;
}

} // namespace

// This is never instantiated, it's just used for EAT_STREAM_PARAMETERS to have
// an object of the correct type on the LHS of the unused part of the ternary
// operator.
std::ostream* g_swallow_stream;

//--------------------------------------------------------------------------------------------------
LoggingSettings::LoggingSettings()
    : min_log_level(LOG_LS_WARNING),
      max_log_file_size(kDefaultMaxLogFileSize),
      max_log_file_age(kDefaultMaxLogFileAge)
{
    std::string log_level_string;
    if (Environment::get("ASPIA_LOG_LEVEL", &log_level_string))
    {
        LoggingSeverity log_level = LOG_LS_WARNING;
        if (stringToInt(log_level_string, &log_level))
        {
            log_level = std::max(log_level, LOG_LS_INFO);
            log_level = std::min(log_level, LOG_LS_FATAL);

            min_log_level = log_level;
        }
    }

    int log_to_file = 0;
    if (LOG_DEFAULT & LOG_TO_FILE)
        log_to_file = 1;

    std::string log_to_file_string;
    if (Environment::get("ASPIA_LOG_TO_FILE", &log_to_file_string))
    {
        int value;
        if (stringToInt(log_to_file_string, &value))
            log_to_file = value;
    }

    int log_to_stdout = 0;
    if (LOG_DEFAULT & LOG_TO_STDOUT)
        log_to_stdout = 1;

    std::string log_to_stdout_string;
    if (Environment::get("ASPIA_LOG_TO_STDOUT", &log_to_stdout_string))
    {
        int value;
        if (stringToInt(log_to_stdout_string, &value))
            log_to_stdout = value;
    }

    if (log_to_file != 0 && log_to_stdout != 0)
        destination = LOG_TO_ALL;
    else if (log_to_file != 0 && log_to_stdout == 0)
        destination = LOG_TO_FILE;
    else if (log_to_file == 0 && log_to_stdout != 0)
        destination = LOG_TO_STDOUT;
    else
        destination = LOG_NONE;

    std::string max_log_file_size_string;
    if (Environment::get("ASPIA_MAX_LOG_FILE_SIZE", &max_log_file_size_string))
    {
        unsigned long long value;
        if (stringToULong64(max_log_file_size_string, &value))
        {
            static const unsigned long long kMinValue = 1024;
            static const unsigned long long kMaxValue = 10 * 1024 * 1024;

            max_log_file_size = static_cast<size_t>(std::min(std::max(value, kMinValue), kMaxValue));
        }
    }

    std::string max_log_file_age_string;
    if (Environment::get("ASPIA_MAX_LOG_FILE_AGE", &max_log_file_age_string))
    {
        unsigned long long value;
        if (stringToULong64(max_log_file_age_string, &value))
        {
            max_log_file_age = static_cast<size_t>(std::min(value, 366ULL));
        }
    }
}

//--------------------------------------------------------------------------------------------------
ghc::filesystem::path execFilePath()
{
    ghc::filesystem::path exec_file_path;

#if defined(OS_WIN)
    wchar_t buffer[MAX_PATH] = { 0 };
    GetModuleFileNameExW(GetCurrentProcess(), nullptr, buffer, std::size(buffer));
    exec_file_path = buffer;
#elif defined(OS_LINUX)
    char buffer[PATH_MAX] = { 0 };
    readlink("/proc/self/exe", buffer, std::size(buffer));
    exec_file_path = buffer;
#elif defined(OS_MAC)
    char buffer[PATH_MAX] = { 0 };
    uint32_t buffer_size = std::size(buffer);
    _NSGetExecutablePath(buffer, &buffer_size);
    exec_file_path = buffer;
#else
#error Not implemented
#endif

    return exec_file_path;
}

//--------------------------------------------------------------------------------------------------
std::string logFilePrefix()
{
    ghc::filesystem::path exec_file_path = execFilePath();
    ghc::filesystem::path exec_file_name = exec_file_path.filename();
    exec_file_name.replace_extension();
    return exec_file_name.string();
}

//--------------------------------------------------------------------------------------------------
bool initLogging(const LoggingSettings& settings)
{
    {
        std::lock_guard<std::mutex> lock(g_log_file_lock);

        g_logging_destination = settings.destination;
        g_min_log_level = settings.min_log_level;
        g_log_dir_path = settings.log_dir;
        g_max_log_file_size = settings.max_log_file_size;
        g_max_log_file_age = settings.max_log_file_age;

        if (!initLoggingUnlocked(logFilePrefix()))
            return false;
    }

    LOG(LS_INFO) << "Executable file: " << execFilePath();
    if (g_logging_destination & LOG_TO_FILE)
    {
        // If log output is enabled, then we output information about the file.
        LOG(LS_INFO) << "Logging file: " << g_log_file_path;
    }
    LOG(LS_INFO) << "Logging level: " << g_min_log_level;
    LOG(LS_INFO) << "Debugger present: " << (isDebuggerPresent() ? "Yes" : "No");

#if defined(NDEBUG)
    LOG(LS_INFO) << "Debug build: No";
#else
    LOG(LS_INFO) << "Debug build: Yes";
#endif // defined(NDEBUG)

    LOG(LS_INFO) << "Little endian: " << (EndianUtil::isLittle() ? "Yes" : "No");
    LOG(LS_INFO) << "Logging started";
    return true;
}

//--------------------------------------------------------------------------------------------------
void shutdownLogging()
{
    LOG(LS_INFO) << "Logging finished";

    std::lock_guard<std::mutex> lock(g_log_file_lock);
    g_log_file.close();
}

//--------------------------------------------------------------------------------------------------
bool shouldCreateLogMessage(LoggingSeverity severity)
{
    if (severity < g_min_log_level)
        return false;

    // Return true here unless we know ~LogMessage won't do anything. Note that
    // ~LogMessage writes to stderr if severity_ >= kAlwaysPrintErrorLevel, even
    // when g_logging_destination is LOG_NONE.
    return g_logging_destination != LOG_NONE || severity >= LOG_LS_ERROR;
}

//--------------------------------------------------------------------------------------------------
void makeCheckOpValueString(std::ostream* os, std::nullptr_t /* p */)
{
    (*os) << "nullptr";
}

//--------------------------------------------------------------------------------------------------
std::string* makeCheckOpString(const int& v1, const int& v2, const char* names)
{
    return makeCheckOpString<int, int>(v1, v2, names);
}

//--------------------------------------------------------------------------------------------------
std::string* makeCheckOpString(const unsigned long& v1, const unsigned long& v2, const char* names)
{
    return makeCheckOpString<unsigned long, unsigned long>(v1, v2, names);
}

//--------------------------------------------------------------------------------------------------
std::string* makeCheckOpString(const unsigned int& v1, const unsigned int& v2, const char* names)
{
    return makeCheckOpString<unsigned int, unsigned int>(v1, v2, names);
}

//--------------------------------------------------------------------------------------------------
std::string* makeCheckOpString(const unsigned long long& v1,
                               const unsigned long long& v2,
                               const char* names)
{
    return makeCheckOpString<unsigned long long, unsigned long long>(v1, v2, names);
}

//--------------------------------------------------------------------------------------------------
std::string* makeCheckOpString(const unsigned long& v1, const unsigned int& v2, const char* names)
{
    return makeCheckOpString<unsigned long, unsigned int>(v1, v2, names);
}

//--------------------------------------------------------------------------------------------------
std::string* makeCheckOpString(const unsigned int& v1, const unsigned long& v2, const char* names)
{
    return makeCheckOpString<unsigned int, unsigned long>(v1, v2, names);
}

//--------------------------------------------------------------------------------------------------
std::string* makeCheckOpString(const std::string& v1, const std::string& v2, const char* names)
{
    return makeCheckOpString<std::string, std::string>(v1, v2, names);
}

//--------------------------------------------------------------------------------------------------
LogMessage::LogMessage(std::string file,
                       int line,
                       std::string function,
                       LoggingSeverity severity)
    : severity_(severity)
{
    init(file, line, function);
}

//--------------------------------------------------------------------------------------------------
LogMessage::LogMessage(std::string file,
                       int line,
                       std::string function,
                       const char* condition)
    : severity_(LOG_LS_FATAL)
{
    init(file, line, function);
    stream_ << "Check failed: " << condition << ". ";
}

//--------------------------------------------------------------------------------------------------
LogMessage::LogMessage(std::string file,
                       int line,
                       std::string function,
                       std::string* result)
    : severity_(LOG_LS_FATAL)
{
    std::unique_ptr<std::string> result_deleter(result);
    init(file, line, function);
    stream_ << "Check failed: " << *result;
}

//--------------------------------------------------------------------------------------------------
LogMessage::LogMessage(std::string file,
                       int line,
                       std::string function,
                       LoggingSeverity severity,
                       std::string* result)
    : severity_(severity)
{
    std::unique_ptr<std::string> result_deleter(result);
    init(file, line, function);
    stream_ << "Check failed: " << *result;
}

//--------------------------------------------------------------------------------------------------
LogMessage::~LogMessage()
{
    stream_ << std::endl;

    std::string message(stream_.str());

    if ((g_logging_destination & LOG_TO_STDOUT) != 0)
    {
        debugPrint(message.data());

        fwrite(message.data(), message.size(), 1, stderr);
        fflush(stderr);
    }
    else if (severity_ >= LOG_LS_ERROR)
    {
        // When we're only outputting to a log file, above a certain log level, we
        // should still output to stderr so that we can better detect and diagnose
        // problems with unit tests, especially on the buildbots.
        fwrite(message.data(), message.size(), 1, stderr);
        fflush(stderr);
    }

    // Write to log file.
    if ((g_logging_destination & LOG_TO_FILE) != 0)
    {
        std::lock_guard<std::mutex> lock(g_log_file_lock);

        if (g_log_file.tellp() >= g_max_log_file_size)
        {
            // The maximum size of the log file has been exceeded. Close the current log file and
            // create a new one.
            initLoggingUnlocked(logFilePrefix());
        }

        g_log_file.write(message.c_str(), message.size());
        g_log_file.flush();
    }

    if (severity_ == LOG_LS_FATAL)
    {
        // Crash the process.
        debugBreak();
    }
}

//--------------------------------------------------------------------------------------------------
// Writes the common header info to the stream.
void LogMessage::init(std::string file, int line, std::string function)
{
    size_t last_slash_pos = file.find_last_of("\\/");
    if (last_slash_pos != std::string::npos)
        file = file.substr(last_slash_pos, file.length() - last_slash_pos - 1);

    SystemTime time = SystemTime::now();

    stream_ << std::setfill('0')
            << std::setw(2) << time.hour()        << ':'
            << std::setw(2) << time.minute()      << ':'
            << std::setw(2) << time.second()      << '.'
            << std::setw(3) << time.millisecond() << ' '
            << std::this_thread::get_id()         << ' '
            << severityName(severity_)            << ' '
            << file.data() << ":" << line << " " << function.data() << "] ";

    message_start_ = stream_.str().length();
}

//--------------------------------------------------------------------------------------------------
ErrorLogMessage::ErrorLogMessage(std::string file,
                                 int line,
                                 std::string function,
                                 LoggingSeverity severity,
                                 SystemError error)
    : error_(error),
      log_message_(file, line, function, severity)
{
    // Nothing
}

//--------------------------------------------------------------------------------------------------
ErrorLogMessage::~ErrorLogMessage()
{
    stream() << ": " << error_.toString();
}

} // namespace base

namespace std {

#if defined(OS_WIN)
//--------------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& out, const std::wstring& wstr)
{
    return out << base::utf8FromWide(wstr);
}

//--------------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& out, const wchar_t* wstr)
{
    return out << (wstr ? base::utf8FromWide(wstr) : "nullptr");
}
#endif // defined(OS_WIN)

//--------------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& out, const char16_t* ustr)
{
    return out << (ustr ? base::utf8FromUtf16(ustr) : "nullptr");
}

//--------------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& out, const std::u16string& ustr)
{
    return out << base::utf8FromUtf16(ustr);
}

} // namespace std
