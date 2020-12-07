//
// SPDX-License-Identifier: LGPL-2.1-or-later
//
// Copyright © 2011-2019 ANSSI. All Rights Reserved.
//
// Author(s): Jean Gautier (ANSSI)
//
#pragma once

#include "CommandExecute.h"

#include "CommandNotification.h"
#include "CommandMessage.h"

#include "Output/Console/Journal.h"

#pragma managed(push, off)

namespace Orc {

namespace Command::Wolf {

class WolfTask
{
public:
    typedef enum _Status
    {
        Init = 0,
        Running,
        Cancelled,
        Stalled,
        Failed,
        Dumped,
        Done
    } Status;

    WolfTask(const std::wstring& commandSet, const std::wstring& command, Command::Output::Journal& journal)
        : m_journal(journal)
        , m_commandSet(commandSet)
        , m_command(command)
        , m_dwPID(0)
        , m_dwExitCode(-1)
        , m_dwLastReportedHang(30)
        , m_dwMostReportedHang(0)
        , m_status(Init)
    {
        ZeroMemory(&m_times, sizeof(PROCESS_TIMES));
        ZeroMemory(&m_lastActiveTime, sizeof(FILETIME));
        ZeroMemory(&m_startTime, sizeof(FILETIME));
    };

    const std::wstring& Command() const { return m_command; }
    const std::wstring& CommandSet() const { return m_commandSet; }
    DWORD Pid() const { return m_dwPID; }
    DWORD ExitCode() const { return m_dwExitCode; }

    HRESULT ApplyNotification(
        const std::shared_ptr<CommandNotification>& notification,
        std::vector<std::shared_ptr<CommandMessage>>& actions);

private:
    Orc::Command::Output::Journal& m_journal;

    std::wstring m_commandSet;
    std::wstring m_command;

    DWORD m_dwPID;
    DWORD m_dwExitCode;

    DWORD m_dwLastReportedHang;
    DWORD m_dwMostReportedHang;

    FILETIME m_startTime;
    FILETIME m_lastActiveTime;


    Status m_status;

    PROCESS_TIMES m_times;
};

}  // namespace Command::Wolf
}  // namespace Orc

#pragma managed(pop)
