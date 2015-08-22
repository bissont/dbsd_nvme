/*-
 * Copyright (C) 2012-2013 Intel Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#ifndef __NVME_PRIVATE_H__
#define __NVME_PRIVATE_H__

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/bus.h>
#include <sys/rman.h>

//#include <sys/bio.h>
//#include <sys/bus.h>
//#include <sys/kernel.h>
//#include <sys/malloc.h>
//#include <sys/mutex.h>
//#include <sys/systm.h>
//#include <sys/taskqueue.h>


//#include <machine/bus.h>

#include "nvme.h"

#define IDT32_PCI_ID	0x80d0111d /* 32 channel board */
#define IDT8_PCI_ID 	0x80d2111d /* 8 channel board */

//#This is defined in pci/pcireg.sh
#define PCIS_STORAGE_NVM    0x08
#define PCIP_STORAGE_NVM_NVMHCI_1_0 0x01
#define PCIP_STORAGE_NVM_ENTERPRISE_NVMHCI_1_0  0x02

#define nvme_printf(ctrlr, fmt, args...)        \
	    device_printf(ctrlr->dev, fmt, ##args)

/*
 * One of these per allocated PCI device.
 */
struct nvme_controller {

	device_t		dev;

//	struct mtx		lock;

	uint32_t		ready_timeout_in_ms;

	bus_space_tag_t		bus_tag;
	bus_space_handle_t	bus_handle;

	//bus_dma_tag_t		buffer_dmat;   /* dmat for buffer I/O */
	int			unit;
	int resource_id;
	struct resource *resource;

	/*
	 * The NVMe spec allows for the MSI-X table to be placed
	 * in BAR 4/5, separate from the control registers which
	 * are in BAR 0/1.  These members track the mapping of BAR
	 * 4/5 for that reason.
	 */ 
	int                     bar4_resource_id;
        struct resource         *bar4_resource;
	struct nvme_registers           *regs;

	/** minimum page size supported by this controller in bytes */
	uint32_t		min_page_size;

};

#define nvme_mmio_offsetof(reg)						       \
	offsetof(struct nvme_registers, reg)

#define nvme_mmio_read_4(sc, reg)					       \
	bus_space_read_4((sc)->bus_tag, (sc)->bus_handle,		       \
	    nvme_mmio_offsetof(reg))

int	nvme_ctrlr_construct(struct nvme_controller *ctrlr, device_t dev);
void	nvme_ctrlr_destruct(struct nvme_controller *ctrlr, device_t dev);

#endif /* __NVME_PRIVATE_H__ */
