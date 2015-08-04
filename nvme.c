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
__FBSDID("$FreeBSD$");

//kprintf
#include <sys/systm.h>
#include <sys/param.h>
#include <sys/kernel.h>
#include <sys/bus.h>

//#include <vm/uma.h>

#include <bus/pci/pcivar.h>
#include <bus/pci/pcireg.h>

#include "nvme.h"

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
	        "nvme", nvme_methods, sizeof(struct nvme_softc)
};

static devclass_t nvme_devclass;
DRIVER_MODULE(nvme, pci, nvme_driver, nvme_devclass, NULL, NULL);

static int
nvme_probe (device_t device)
{
	uint32_t	devid;
	uint16_t	subdevice;

	devid = pci_get_devid(device);
	subdevice = pci_get_subdevice(device);

	kprintf("hello");
	
	return (ENXIO);
}

static int
nvme_attach(device_t dev)
{
		kprintf("hello\n");
		
	return (1);
}

static int
nvme_detach (device_t dev)
{
	kprintf("exit\n");
	return (0);
}
