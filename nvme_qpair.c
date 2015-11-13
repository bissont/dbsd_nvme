#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <sys/param.h>
#include <sys/bus.h>

//#include <dev/pci/pcivar.h>

#include "nvme_private.h"

void
nvme_admin_qpair_disable(struct nvme_qpair *qpair)
{
//	nvme_qpair_disable(qpair);
//	nvme_admin_qpair_abort_aers(qpair);
}

void
nvme_qpair_disable(struct nvme_qpair *qpair)
{
	//struct nvme_tracker *tr;

	qpair->is_enabled = FALSE;
	//mtx_lock(&qpair->lock);
//j	TAILQ_FOREACH(tr, &qpair->outstanding_tr, tailq)
//		callout_stop(&tr->timer);
	//mtx_unlock(&qpair->lock);
}

void
nvme_io_qpair_disable(struct nvme_qpair *qpair)
{

	nvme_qpair_disable(qpair);
}
