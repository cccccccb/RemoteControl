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

#ifndef BASE_NET_FIREWALL_MANAGER_H
#define BASE_NET_FIREWALL_MANAGER_H

#include "Base/macros_magic.h"
#include "Base/filesystem.hpp"
#include "Base/base_export.h"

#include <vector>

#include <wrl/client.h>
#include <netfw.h>

namespace base {

class BASE_EXPORT FirewallManager
{
public:
    explicit FirewallManager(const ghc::filesystem::path& application_path);
    ~FirewallManager() = default;

    // Returns true if firewall manager is valid.
    bool isValid() const;

    // Returns true if firewall is enabled.
    bool isFirewallEnabled() const;

    // Returns true if there is any rule for the application.
    bool hasAnyRule();

    // Adds a firewall rule allowing inbound connections to the application on
    // TCP port |port|. Replaces the rule if it already exists. Needs elevation.
    bool addTcpRule(std::wstring rule_name,
                    std::wstring description,
                    uint16_t port);

    // Adds a firewall rule allowing inbound connections to the application on
    // UDP port |port|. Replaces the rule if it already exists. Needs elevation.
    bool addUdpRule(std::wstring rule_name,
                    std::wstring description,
                    uint16_t port);

    // Deletes all rules with specified name. Needs elevation.
    void deleteRuleByName(std::wstring rule_name);

    // Deletes all rules for current app. Needs elevation.
    void deleteAllRules();

private:
    // Returns the list of rules applying to the application.
    void allRules(std::vector<Microsoft::WRL::ComPtr<INetFwRule>>* rules);

    // Deletes rules. Needs elevation.
    void deleteRule(Microsoft::WRL::ComPtr<INetFwRule> rule);

    Microsoft::WRL::ComPtr<INetFwPolicy2> firewall_policy_;
    Microsoft::WRL::ComPtr<INetFwRules> firewall_rules_;

    ghc::filesystem::path application_path_;

    DISALLOW_COPY_AND_ASSIGN(FirewallManager);
};

} // namespace base

#endif // BASE_NET_FIREWALL_MANAGER_H
