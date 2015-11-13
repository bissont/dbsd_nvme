#include <sys/cdefs.h>

#include <sys/param.h>
#include <sys/bus.h>
//#include <sys/sysctl.h>

#include "nvme_private.h"

/*
 *  * CTLTYPE_S64 and sysctl_handle_64 were added in r217616.  Define these
 *   *  explicitly here for older kernels that don't include the r217616
 *    *  changeset.
 *     */
#ifndef CTLTYPE_S64
#define CTLTYPE_S64             CTLTYPE_QUAD
#define sysctl_handle_64        sysctl_handle_quad
#endif

void
nvme_sysctl_initialize_ctrlr(struct nvme_controller *ctrlr)
{
/*	struct sysctl_ctx_list  *ctrlr_ctx;
	struct sysctl_oid       *ctrlr_tree, *que_tree;
	struct sysctl_oid_list  *ctrlr_list;
#define QUEUE_NAME_LENGTH       16
	char                    queue_name[QUEUE_NAME_LENGTH];
	int                     i;

	ctrlr_ctx = device_get_sysctl_ctx(ctrlr->dev);
	ctrlr_tree = device_get_sysctl_tree(ctrlr->dev);
	ctrlr_list = SYSCTL_CHILDREN(ctrlr_tree);

	SYSCTL_ADD_PROC(ctrlr_ctx, ctrlr_list, OID_AUTO,
			"int_coal_time", CTLTYPE_UINT | CTLFLAG_RW, ctrlr, 0,
			nvme_sysctl_int_coal_time, "IU",
			"Interrupt coalescing timeout (in microseconds)");

	SYSCTL_ADD_PROC(ctrlr_ctx, ctrlr_list, OID_AUTO,
			"int_coal_threshold", CTLTYPE_UINT | CTLFLAG_RW, ctrlr, 0,
			nvme_sysctl_int_coal_threshold, "IU",
			"Interrupt coalescing threshold");

	SYSCTL_ADD_PROC(ctrlr_ctx, ctrlr_list, OID_AUTO,
			"timeout_period", CTLTYPE_UINT | CTLFLAG_RW, ctrlr, 0,
			nvme_sysctl_timeout_period, "IU",
			"Timeout period (in seconds)");

	SYSCTL_ADD_PROC(ctrlr_ctx, ctrlr_list, OID_AUTO,
			"num_cmds", CTLTYPE_S64 | CTLFLAG_RD,
			ctrlr, 0, nvme_sysctl_num_cmds, "IU",
			"Number of commands submitted");

	SYSCTL_ADD_PROC(ctrlr_ctx, ctrlr_list, OID_AUTO,
			"num_intr_handler_calls", CTLTYPE_S64 | CTLFLAG_RD,
			ctrlr, 0, nvme_sysctl_num_intr_handler_calls, "IU",
			"Number of times interrupt handler was invoked (will "
			"typically be less than number of actual interrupts "
			"generated due to coalescing)");

	SYSCTL_ADD_PROC(ctrlr_ctx, ctrlr_list, OID_AUTO,
			"reset_stats", CTLTYPE_UINT | CTLFLAG_RW, ctrlr, 0,
			nvme_sysctl_reset_stats, "IU", "Reset statistics to zero");

	que_tree = SYSCTL_ADD_NODE(ctrlr_ctx, ctrlr_list, OID_AUTO, "adminq",
				   CTLFLAG_RD, NULL, "Admin Queue");

	nvme_sysctl_initialize_queue(&ctrlr->adminq, ctrlr_ctx, que_tree);

	for (i = 0; i < ctrlr->num_io_queues; i++) {
		snprintf(queue_name, QUEUE_NAME_LENGTH, "ioq%d", i);
		que_tree = SYSCTL_ADD_NODE(ctrlr_ctx, ctrlr_list, OID_AUTO,
					   queue_name, CTLFLAG_RD, NULL, "IO Queue");
		nvme_sysctl_initialize_queue(&ctrlr->ioq[i], ctrlr_ctx,
					     que_tree);
	}*/
}
