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

#ifndef BASE_NET_ADAPTER_ENUMERATOR_H
#define BASE_NET_ADAPTER_ENUMERATOR_H

#include "Base/macros_magic.h"
#include "Base/memory/byte_array.h"
#include "BuildConfig/build_config.h"
#include "Base/base_export.h"

#include <memory>
#include <string>

#if defined(OS_WIN)
struct _IP_ADAPTER_ADDRESSES_LH;
struct _IP_ADAPTER_UNICAST_ADDRESS_LH;
struct _IP_ADAPTER_DNS_SERVER_ADDRESS_XP;
struct _IP_ADAPTER_GATEWAY_ADDRESS_LH;
#endif // defined(OS_WIN)

namespace base {

class BASE_EXPORT AdapterEnumerator
{
public:
    AdapterEnumerator();
    ~AdapterEnumerator();

    bool isAtEnd() const;
    void advance();

    std::string adapterName() const;
    std::string connectionName() const;
    std::string interfaceType() const;
    uint32_t mtu() const;
    uint64_t speed() const;
    std::string macAddress() const;

    bool isDhcp4Enabled() const;
    std::string dhcp4Server() const;

    class BASE_EXPORT IpAddressEnumerator
    {
    public:
        explicit IpAddressEnumerator(const AdapterEnumerator& adapter);

        bool isAtEnd() const;
        void advance();

        std::string address() const;
        std::string mask() const;

    private:
#if defined(OS_WIN)
        const _IP_ADAPTER_UNICAST_ADDRESS_LH* address_;
#endif

        DISALLOW_COPY_AND_ASSIGN(IpAddressEnumerator);
    };

    class BASE_EXPORT GatewayEnumerator
    {
    public:
        explicit GatewayEnumerator(const AdapterEnumerator& adapter);

        bool isAtEnd() const;
        void advance();
        std::string address() const;

    private:
#if defined(OS_WIN)
        const _IP_ADAPTER_GATEWAY_ADDRESS_LH* address_;
#endif

        DISALLOW_COPY_AND_ASSIGN(GatewayEnumerator);
    };

    class BASE_EXPORT DnsEnumerator
    {
    public:
        explicit DnsEnumerator(const AdapterEnumerator& adapter);

        bool isAtEnd() const;
        void advance();
        std::string address() const;

    private:
#if defined(OS_WIN)
        const _IP_ADAPTER_DNS_SERVER_ADDRESS_XP* address_ = nullptr;
#endif

        DISALLOW_COPY_AND_ASSIGN(DnsEnumerator);
    };

private:
#if defined(OS_WIN)
    ByteArray adapters_buffer_;
    _IP_ADAPTER_ADDRESSES_LH* adapter_;
#endif

    DISALLOW_COPY_AND_ASSIGN(AdapterEnumerator);
};

} // namespace base

#endif // BASE_NET_ADAPTER_ENUMERATOR_H
