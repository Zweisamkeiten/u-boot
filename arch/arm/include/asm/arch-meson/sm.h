/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2016 - Beniamino Galvani <b.galvani@gmail.com>
 */

#ifndef __MESON_SM_H__
#define __MESON_SM_H__

/**
 * meson_sm_read_efuse - read efuse memory into buffer
 *
 * @offset: offset from the start efuse memory
 * @buffer: pointer to buffer
 * @size: number of bytes to read
 * @return: number of bytes read
 */
ssize_t meson_sm_read_efuse(uintptr_t offset, void *buffer, size_t size);

/**
 * meson_sm_write_efuse - write into efuse memory from buffer
 *
 * @offset: offset from the start efuse memory
 * @buffer: pointer to buffer
 * @size: number of bytes to write
 * @return: number of bytes written
 */
ssize_t meson_sm_write_efuse(uintptr_t offset, void *buffer, size_t size);

#define SM_SERIAL_SIZE	12

/**
 * meson_sm_get_serial - read chip unique id into buffer
 *
 * @buffer: pointer to buffer
 * @size: buffer size.
 * @return: zero on success or -errno on failure
 */
int meson_sm_get_serial(void *buffer, size_t size);

enum {
	REBOOT_REASON_COLD = 0,
	REBOOT_REASON_NORMAL = 1,
	REBOOT_REASON_RECOVERY = 2,
	REBOOT_REASON_UPDATE = 3,
	REBOOT_REASON_FASTBOOT = 4,
	REBOOT_REASON_SUSPEND_OFF = 5,
	REBOOT_REASON_HIBERNATE = 6,
	REBOOT_REASON_BOOTLOADER = 7,
	REBOOT_REASON_SHUTDOWN_REBOOT = 8,
	REBOOT_REASON_RPMBP = 9,
	REBOOT_REASON_CRASH_DUMP = 11,
	REBOOT_REASON_KERNEL_PANIC = 12,
	REBOOT_REASON_WATCHDOG_REBOOT = 13,
};

/**
 * meson_sm_get_reboot_reason - get reboot reason
 */
int meson_sm_get_reboot_reason(void);

#endif /* __MESON_SM_H__ */
