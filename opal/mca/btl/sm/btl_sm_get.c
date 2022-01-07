/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2010-2014 Los Alamos National Security, LLC. All rights
 *                         reserved.
 * Copyright (c) 2018      Research Organization for Information Science
 *                         and Technology (RIST).  All rights reserved.
 * Copyright (c) 2019-2021 Google, Inc. All rights reserved.
 * Copyright (c) 2020      The University of Tennessee and The University
 *                         of Tennessee Research Foundation.  All rights
 *                         reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */

#include "opal_config.h"

#include "opal/mca/btl/sm/btl_sm.h"
#include "opal/mca/btl/sm/btl_sm_frag.h"
#include "opal/mca/smsc/smsc.h"

/**
 * Initiate an synchronous get.
 *
 * @param btl (IN)         BTL module
 * @param endpoint (IN)    BTL addressing information
 * @param descriptor (IN)  Description of the data to be transferred
 */

int mca_btl_sm_get(mca_btl_base_module_t *btl, mca_btl_base_endpoint_t *endpoint,
                   void *local_address, uint64_t remote_address,
                   mca_btl_base_registration_handle_t *local_handle,
                   mca_btl_base_registration_handle_t *remote_handle, size_t size, int flags,
                   int order, mca_btl_base_rdma_completion_fn_t cbfunc, void *cbcontext,
                   void *cbdata)
{
    int ret = MCA_SMSC_CALL(copy_from, endpoint->smsc_endpoint, local_address,
                            (void *) (intptr_t) remote_address, size, remote_handle);
    if (OPAL_UNLIKELY(OPAL_SUCCESS != ret)) {
        return ret;
    }

    /* always call the callback function */
    cbfunc(btl, endpoint, local_address, local_handle, cbcontext, cbdata, OPAL_SUCCESS);

    return OPAL_SUCCESS;
}
