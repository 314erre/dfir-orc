//
// SPDX-License-Identifier: LGPL-2.1-or-later
//
// Copyright © 2020 ANSSI. All Rights Reserved.
//
// Author(s): fabienfl (ANSSI)
//

#pragma once

#include <optional>

#include <fmt/format.h>

template <typename T>
struct fmt::formatter<std::optional<T>> : public fmt::formatter<fmt::string_view>
{
    template <typename FormatContext>
    auto format(const std::optional<T>& optional, FormatContext& ctx)
    {
        if (!optional.has_value())
        {
            return fmt::format_to(ctx.out(), "N/A");
        }

        return fmt::format_to(ctx.out(), "{}", *optional);
    }
};

template <typename T>
struct fmt::formatter<std::optional<T>, wchar_t> : public fmt::formatter<fmt::wstring_view, wchar_t>
{
    template <typename FormatContext>
    auto format(const std::optional<T>& optional, FormatContext& ctx)
    {
        if (!optional.has_value())
        {
            return fmt::format_to(ctx.out(), L"N/A");
        }

        return fmt::format_to(ctx.out(), L"{}", *optional);
    }
};
