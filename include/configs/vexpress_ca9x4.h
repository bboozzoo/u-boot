/*
 * (C) Copyright 2011 Linaro
 * Ryan Harkin, <ryan.harkin@linaro.org>
 *
 * Configuration for Versatile Express. Parts were derived from other ARM
 *   configurations.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __VEXPRESS_CA9X4_H
#define __VEXPRESS_CA9X4_H

#define CONFIG_VEXPRESS_ORIGINAL_MEMORY_MAP
#include "vexpress_common.h"

#define CONFIG_RBTREE
#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define CONFIG_MTD_CONCAT
#define CONFIG_FLASH_CFI_MTD
#define CONFIG_LZO

#ifdef CONFIG_SYS_MALLOC_LEN
#undef CONFIG_SYS_MALLOC_LEN
#define CONFIG_SYS_MALLOC_LEN (8 * 1024 * 1024)
#endif

/* CONFIG_MTD_CONCAT is set, hence nor0 and nor1 will become a single device
   named nor2

   NOTE: NOR flash appears as a single MTD device with name 40000000.flash */
#define MTDIDS_DEFAULT		"nor2=40000000.flash"
#define MTDPARTS_DEFAULT  "mtdparts=40000000.flash:"  \
  "1m(u-boot)ro," \
  "1m(u-boot-env)," \
  "-(ubi)"

#ifdef CONFIG_EXTRA_ENV_SETTINGS
#undef CONFIG_EXTRA_ENV_SETTINGS
#endif

#define UBI_BOOTCMD \
 	"ubiboot=" \
	"echo Booting from NOR...; "                                          \
	"run mender_setup; "                                                  \
	"run set_ubiargs; "                                                   \
	"ubi part ${mender_mtd_ubi_dev_name} && "                             \
	"ubifsmount ${mender_uboot_root_name} && "                            \
	"ubifsload ${kernel_addr_r} /boot/zImage && "                         \
	"ubifsload ${fdt_addr_r} /boot/${fdtfile} && "                        \
  "setenv bootargs ${mtdparts} ${ubiargs} ${defargs} && "               \
	"bootz ${kernel_addr_r} - ${fdt_addr_r}\0"

#define CONFIG_EXTRA_ENV_SETTINGS                                       \
  UBI_BOOTCMD \
  "kernel_addr_r=0x60100000\0"                                          \
  "fdt_addr_r=0x60000000\0"                                             \
  "fdtfile=vexpress-v2p-ca9.dtb\0"                                      \
  "mtdparts=" MTDPARTS_DEFAULT "\0"                                     \
  "set_ubiargs=setenv ubiargs ubi.mtd=${mender_mtd_ubi_dev_name} "      \
              "root=${mender_kernel_root} rootfstype=ubifs ubi.fm_autoconvert=1\0"  \
  "defargs=console=ttyAMA0,115200n8 panic=3\0"

#undef CONFIG_BOOTCOMMAND
#define CONFIG_BOOTCOMMAND "run ubiboot; run mender_try_to_recover; "

/* environment starts at 1MB offset in the flash */
#undef CONFIG_ENV_OFFSET
#define CONFIG_ENV_OFFSET 0x100000
/* was fixed in vexpress_common, but will be derived in environment.h */
#undef CONFIG_ENV_ADDR
/* required for automatic calculation of CONFIG_ENV_ADDR */
#define CONFIG_SYS_FLASH_BASE CONFIG_SYS_FLASH_BASE0

#define CONFIG_BOOTCOUNT_ENV
#define CONFIG_BOOTCOUNT_LIMIT

/* Mender integration will set this */
#undef CONFIG_ENV_OFFSET

#endif /* VEXPRESS_CA9X4_H */
