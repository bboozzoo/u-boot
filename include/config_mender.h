/*
  Copyright (C) 2016  Mender Software

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef CONFIG_MENDER_H
#define CONFIG_MENDER_H

#include <config_mender_defines.h>

#ifndef CONFIG_ENV_IS_IN_FAT
# error CONFIG_ENV_IS_IN_FAT is required for Mender to work
#endif

#ifndef CONFIG_BOOTCOUNT_LIMIT
# error CONFIG_BOOTCOUNT_LIMIT is required for Mender to work
#endif

/* Currently Mender needs bootcount to reside in environment file. */
#ifndef CONFIG_BOOTCOUNT_ENV
# error CONFIG_BOOTCOUNT_ENV is required for Mender to work
#endif

#ifdef FAT_ENV_INTERFACE
# error FAT_ENV_INTERFACE should not be defined explicitly (will be auto-configured).
#endif

/* Post-daisy variant. */
#ifdef FAT_ENV_DEVICE_AND_PART
# error FAT_ENV_DEVICE_AND_PART should not be defined explicitly (will be auto-configured).
#endif
/* Daisy-and-earlier variants. */
#ifdef FAT_ENV_DEVICE
# error FAT_ENV_DEVICE should not be defined explicitly (will be auto-configured).
#endif
#ifdef FAT_ENV_PART
# error FAT_ENV_PART should not be defined explicitly (will be auto-configured).
#endif

#ifdef FAT_ENV_FILE
# error FAT_ENV_FILE should not be defined explicitly (will be auto-configured).
#endif

#if MENDER_BOOTENV_SIZE != CONFIG_ENV_SIZE
# error 'CONFIG_ENV_SIZE' define must be equal to bitbake variable 'BOOTENV_SIZE' set in U-Boot build recipe.
#endif

#define FAT_ENV_INTERFACE       MENDER_UBOOT_STORAGE_INTERFACE
#define FAT_ENV_DEVICE_AND_PART __stringify(MENDER_UBOOT_STORAGE_DEVICE) ":" __stringify(MENDER_BOOT_PART_NUMBER)
#define FAT_ENV_DEVICE          MENDER_UBOOT_STORAGE_DEVICE
#define FAT_ENV_PART            MENDER_BOOT_PART_NUMBER
#define FAT_ENV_FILE            "uboot.env"

#define CONFIG_FAT_WRITE

#endif /* CONFIG_MENDER_H */
