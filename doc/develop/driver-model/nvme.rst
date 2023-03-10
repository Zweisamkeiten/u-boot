.. SPDX-License-Identifier: GPL-2.0+
.. Copyright (C) 2017 NXP Semiconductors
.. Copyright (C) 2017 Bin Meng <bmeng.cn@gmail.com>

NVMe Support
============

What is NVMe
------------

NVM Express (NVMe) is a register level interface that allows host software to
communicate with a non-volatile memory subsystem. This interface is optimized
for enterprise and client solid state drives, typically attached to the PCI
express interface. It is a scalable host controller interface designed to
address the needs of enterprise and client systems that utilize PCI express
based solid state drives (SSD). The interface provides optimized command
submission and completion paths. It includes support for parallel operation by
supporting up to 64K I/O queues with up to 64K commands per I/O queue.

The device is comprised of some number of controllers, where each controller
is comprised of some number of namespaces, where each namespace is comprised
of some number of logical blocks. A namespace is a quantity of non-volatile
memory that is formatted into logical blocks. An NVMe namespace is equivalent
to a SCSI LUN. Each namespace is operated as an independent "device".

How it works
------------
There is an NVMe uclass driver (driver name "nvme"), an NVMe host controller
driver (driver name "nvme") and an NVMe namespace block driver (driver name
"nvme_blk"). The host controller driver is supposed to probe the hardware and
do necessary initialization to put the controller into a ready state at which
it is able to scan all available namespaces attached to it. Scanning namespace
is triggered by the NVMe uclass driver and the actual work is done in the NVMe
namespace block driver.

Status
------
It only support basic block read/write functions in the NVMe driver.

Config options
--------------
CONFIG_NVME	Enable NVMe device support
CONFIG_NVME_PCI	Enable PCIe NVMe device support
CONFIG_CMD_NVME	Enable basic NVMe commands

Usage in U-Boot
---------------
To use an NVMe hard disk from U-Boot shell, a 'nvme scan' command needs to
be executed for all NVMe hard disks attached to the NVMe controller to be
identified.

To list all of the NVMe hard disks, try:

.. code-block:: none

  => nvme info
  Device 0: Vendor: 0x8086 Rev: 8DV10131 Prod: CVFT535600LS400BGN
	    Type: Hard Disk
	    Capacity: 381554.0 MB = 372.6 GB (781422768 x 512)

and print out detailed information for controller and namespaces via:

.. code-block:: none

  => nvme detail

Raw block read/write to can be done via the 'nvme read/write' commands:

.. code-block:: none

  => nvme read a0000000 0 11000

  => tftp 80000000 /tftpboot/kernel.itb
  => nvme write 80000000 0 11000

Of course, file system command can be used on the NVMe hard disk as well:

.. code-block:: none

  => fatls nvme 0:1
	32376967   kernel.itb
	22929408   100m

	2 file(s), 0 dir(s)

  => fatload nvme 0:1 a0000000 /kernel.itb
  => bootm a0000000

Testing NVMe with QEMU x86
--------------------------
QEMU supports NVMe emulation and we can test NVMe driver with QEMU x86 running
U-Boot. Please see README.x86 for how to build u-boot.rom image for QEMU x86.

Example command line to call QEMU x86 below with emulated NVMe device:

.. code-block:: bash

  $ ./qemu-system-i386 -drive file=nvme.img,if=none,id=drv0 -device nvme,drive=drv0,serial=QEMUNVME0001 -bios u-boot.rom
