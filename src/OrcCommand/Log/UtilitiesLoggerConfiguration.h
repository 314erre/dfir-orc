//
// SPDX-License-Identifier: LGPL-2.1-or-later
//
// Copyright � 2021 ANSSI. All Rights Reserved.
//
// Author(s): fabienfl (ANSSI)
//

#pragma once

#include "Log/UtilitiesLogger.h"

#include <optional>

#include "FileDisposition.h"
#include "Text/Encoding.h"

namespace Orc {

class ConfigItem;

namespace Command {

struct UtilitiesLoggerConfiguration
{
    static void Parse(int argc, const wchar_t* argv[], UtilitiesLoggerConfiguration& config);

    static HRESULT Register(ConfigItem& parent, DWORD dwIndex);
    static void Parse(const ConfigItem& item, UtilitiesLoggerConfiguration& config);

    static void Apply(UtilitiesLogger& logger, const UtilitiesLoggerConfiguration& config);
    static void ApplyLogLevel(UtilitiesLogger& logger, int argc, const wchar_t* argv[]);
    static void ApplyLogLevel(UtilitiesLogger& logger, const UtilitiesLoggerConfiguration& config);

    static std::optional<std::wstring>
    UtilitiesLoggerConfiguration::ToCommandLineArguments(const UtilitiesLoggerConfiguration& config);

    struct Output
    {
        std::optional<Orc::Log::Level> level;
        std::optional<Orc::Log::Level> backtraceTrigger;
    };

    struct FileOutput : Output
    {
        // Not an OutputSpec or fs::path because of patterns that should be processed later than parsing
        std::optional<std::wstring> path;

        std::optional<Text::Encoding> encoding;
        std::optional<FileDisposition> disposition;
    };

    // Global flags value like '/debug' switch
    std::optional<Orc::Log::Level> level;
    std::optional<Orc::Log::Level> backtraceTrigger;
    std::optional<bool> verbose;
    std::optional<std::filesystem::path> logFile;  // For legacy compatibility

    // For specific flag values like /log:file,level=debug
    Output console;
    FileOutput file;
};

}  // namespace Command
}  // namespace Orc
