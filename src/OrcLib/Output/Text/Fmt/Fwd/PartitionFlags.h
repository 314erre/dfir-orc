//
// SPDX-License-Identifier: LGPL-2.1-or-later
//
// Copyright © 2020 ANSSI. All Rights Reserved.
//
// Author(s): fabienfl (ANSSI)
//

#pragma once

#include <fmt/format.h>

namespace Orc {

enum class PartitionFlags : std::int32_t;

}

template <>
struct fmt::formatter<Orc::PartitionFlags> : public fmt::formatter<std::string_view>
{
    template <typename FormatContext>
    auto format(const Orc::PartitionFlags& flags, FormatContext& ctx) -> decltype(ctx.out());
};

template <>
struct fmt::formatter<Orc::PartitionFlags, wchar_t> : public fmt::formatter<std::wstring_view, wchar_t>
{
    template <typename FormatContext>
    auto format(const Orc::PartitionFlags& flags, FormatContext& ctx) -> decltype(ctx.out());
};
