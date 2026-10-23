/*
 * PS5 Vulkan driver - Host tests for VideoOut high-refresh selection.
 * Copyright (C) 2026 Mihawk-99
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "ps5vk_output_mode.h"

#include <gtest/gtest.h>

namespace
{
TEST(VideoOutModePolicyTest, TrustsOnlyConfiguredRetailVrr)
{
    EXPECT_EQ(ps5vk_choose_high_refresh(UINT32_C(0x40040), 1, 0), PS5VK_HIGH_REFRESH_TRUST_VRR);
    EXPECT_EQ(ps5vk_choose_high_refresh(UINT32_C(0x40000), 1, 0), PS5VK_HIGH_REFRESH_UNAVAILABLE);
    EXPECT_EQ(ps5vk_choose_high_refresh(UINT32_C(0x40040), 0, 0), PS5VK_HIGH_REFRESH_UNAVAILABLE);
    EXPECT_EQ(ps5vk_choose_high_refresh(UINT32_C(0x40040), 1, -1), PS5VK_HIGH_REFRESH_UNAVAILABLE);
}

TEST(VideoOutModePolicyTest, KeepsFixedRateValidationForNonVrrTitles)
{
    EXPECT_EQ(ps5vk_choose_high_refresh(UINT32_C(0x40), 1, 0), PS5VK_HIGH_REFRESH_VERIFY_FIXED);
    EXPECT_EQ(ps5vk_choose_high_refresh(UINT32_C(0x80040), 1, 0), PS5VK_HIGH_REFRESH_VERIFY_FIXED);
    EXPECT_EQ(ps5vk_choose_high_refresh(UINT32_C(0xc0040), 1, 0), PS5VK_HIGH_REFRESH_VERIFY_FIXED);
}
} // namespace
