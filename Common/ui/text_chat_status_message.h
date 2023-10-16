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

#ifndef COMMON_UI_TEXT_CHAT_STATUS_MESSAGE_H
#define COMMON_UI_TEXT_CHAT_STATUS_MESSAGE_H

#include "Common/ui/text_chat_message.h"
#include "ui_text_chat_status_message.h"

namespace common {

class TextChatStatusMessage : public TextChatMessage
{
    Q_OBJECT

public:
    explicit TextChatStatusMessage(QWidget* parent = nullptr);
    ~TextChatStatusMessage() override;

    void setMessageText(const QString& text) override;
    QString messageText() const override;
    QString messageTime() const override;

private:
    Ui::TextChatStatusMessage ui;
};

} // namespace common

#endif // COMMON_UI_TEXT_CHAT_STATUS_MESSAGE_H
