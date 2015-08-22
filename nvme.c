/*-
 * Copyright (C) 2012-2014 Intel Corporation
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
 */

#include <sys/cdefs.h>

//kprintf
#include <sys/systm.h>
#include <sys/param.h>
#include <sys/kernel.h>
#include <sys/bus.h>

//#include <vm/uma.h>

#include <bus/pci/pcivar.h>
#include <bus/pci/pcireg.h>

#include "nvme_private.h"

//MALLOC_DEFINE(M_NVME, "nvme", "nvme(4) memory allocations");

static int    nvme_probe(device_t);
static int    nvme_attach(device_t);
static int    nvme_detach(device_t);


static device_method_t nvme_methods[] = {
	/* Device interface */
	DEVMETHOD(device_probe,     nvme_probe),
	DEVMETHOD(device_attach,    nvme_attach),
	DEVMETHOD(device_detach,    nvme_detach),
	DEVMETHOD_END
};

static driver_t nvme_driver = {
	        "nvme", nvme_methods, sizeof(struct nvme_controller)
};

static devclass_t nvme_devclass;
DRIVER_MODULE(nvme, pci, nvme_driver, nvme_devclass, NULL, NULL);

static struct _pcsid
{
	uint32_t        devid;
	int             match_subdevice;
	uint16_t        subdevice;
	const char      *desc;
} pci_ids[] = {
	{ 0x01118086,           0, 0, "NVMe Controller"  },
        { IDT32_PCI_ID,         0, 0, "IDT NVMe Controller (32 channel)"  },
        { IDT8_PCI_ID,          0, 0, "IDT NVMe Controller (8 channel)" },
        { 0x09538086,           1, 0x3702, "DC P3700 SSD" },
        { 0x09538086,           1, 0x3703, "DC P3700 SSD [2.5\" SFF]" },
        { 0x09538086,           1, 0x3704, "DC P3500 SSD [Add-in Card]" },
        { 0x09538086,           1, 0x3705, "DC P3500 SSD [2.5\" SFF]" },
        { 0x09538086,           1, 0x3709, "DC P3600 SSD [Add-in Card]" },
        { 0x09538086,           1, 0x370a, "DC P3600 SSD [2.5\" SFF]" },
        { 0x00000000,           0, 0, NULL  }
};

static int
nvme_match(uint32_t devid, uint16_t subdevice, struct _pcsid *ep)
{
	if (devid != ep->devid)
		return 0;

	if (!ep->match_subdevice)
		return 1;

	if (subdevice == ep->subdevice)
		return 1;
	else
		return 0;
}

static int
nvme_probe (device_t device)
{
	uint32_t	devid;
	uint16_t	subdevice;
	struct _pcsid 	*ep;

	devid = pci_get_devid(device);
	subdevice = pci_get_subdevice(device);
	ep = pci_ids;

	while (ep->devid) {
		if (nvme_match(devid, subdevice, ep)) {
			kprintf("Found match Specific device:%u \n",ep->devid);
			break;
		}
		++ep;
	}
	if (ep->desc) {
		device_set_desc(device, ep->desc);
		return (BUS_PROBE_DEFAULT);
	}

	if (pci_get_class(device)    == PCIC_STORAGE &&
	    pci_get_subclass(device) == PCIS_STORAGE_NVM &&
	    pci_get_progif(device)   == PCIP_STORAGE_NVM_ENTERPRISE_NVMHCI_1_0) {
		device_set_desc(device, "Generic NVMe Device");
		return (BUS_PROBE_GENERIC);
	}

	return (ENXIO);
}

static int
nvme_attach(device_t dev)
{
	struct nvme_controller  *ctrlr = device_get_softc(dev);
	int                     status;

	status = nvme_ctrlr_construct(ctrlr, dev);

	if (status != 0) {
		nvme_ctrlr_destruct(ctrlr, dev);
		return (status);
	}

	return (0);
}
		
static int
nvme_detach (device_t dev)
{
	kprintf("exit\n");
	return (0);
}
