// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2011 Samsung Electronics
 */

#include <common.h>
#include <asm/io.h>
#include <asm/gpio.h>
#include <asm/arch/cpu.h>
#include <asm/arch/mmc.h>
#include <asm/arch/periph.h>
#include <asm/arch/pinmux.h>
#include <asm/arch/clock.h>
#include <usb.h>

/*
    copy from odroid.c

    @file arch/arm/mach-exynos/clock.c
    exynos4_set_mmc_clk() config sclk_mmc2 by MODIFY MMC2_PRE_RATIO,
    and need set DOUTMMC2 = 100MHz,so set MMC2_RATIO = 7 here
*/
static int board_clock_init(void)
{
    struct exynos4x12_clock *clk = (struct exynos4x12_clock *)samsung_get_base_clock();
    
    writel(0x00066666, &clk->src_fsys);

    /*
     * For MOUTmmc0-3 = 800 MHz (MPLL)
     *
     * DOUTmmc1 = MOUTmmc1 / (ratio + 1) = 100 (7)
     * sclk_mmc1 = DOUTmmc1 / (ratio + 1) = 50 (1)
     * DOUTmmc0 = MOUTmmc0 / (ratio + 1) = 100 (7)
     * sclk_mmc0 = DOUTmmc0 / (ratio + 1) = 50 (1)
    */
    writel(0x01070107, &clk->div_fsys1);
    while (readl(&clk->div_stat_fsys1) != 0);
    /*
     * For MOUTmmc0-3 = 800 MHz (MPLL)
     *
     * DOUTmmc3 = MOUTmmc3 / (ratio + 1) = 100 (7)
     * sclk_mmc3 = DOUTmmc3 / (ratio + 1) = 50 (1)
     * DOUTmmc2 = MOUTmmc2 / (ratio + 1) = 100 (7)
     * sclk_mmc2 = DOUTmmc2 / (ratio + 1) = 50 (1)
    */
    writel(0x01070107, &clk->div_fsys2);
    while (readl(&clk->div_stat_fsys2) != 0);
    /*
     * For MOUTmmc4 = 800 MHz (MPLL)
     *
     * DOUTmmc4 = MOUTmmc4 / (ratio + 1) = 100 (7)
     * sclk_mmc4 = DOUTmmc4 / (ratio + 1) = 100 (0)
    */
    writel(0x00000007, &clk->div_fsys3);
    while (readl(&clk->div_stat_fsys3) != 0);

    return 0;
}

u32 get_board_rev(void)
{
	return 0;
}

int exynos_init(void)
{
    board_clock_init();

    return 0;
}

int board_usb_init(int index, enum usb_init_type init)
{
	return 0;
}

#ifdef CONFIG_BOARD_EARLY_INIT_F
int exynos_early_init_f(void)
{
	return 0;
}
#endif
