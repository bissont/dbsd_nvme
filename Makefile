KMOD=	nvme	
SRCS=	 nvme_qpair.c nvme_ctrlr.c nvme.c nvme_sysctl.c nvme.h opt_cam.h device_if.h bus_if.h pci_if.h

.if !defined(BUILDING_WITH_KERNEL)
opt_scsi.h:
	echo "#define SCSI_DELAY 15000" > ${.TARGET}
.endif

.include <bsd.kmod.mk>
