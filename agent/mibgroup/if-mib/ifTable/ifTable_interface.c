/*
 * Note: this file originally auto-generated by mib2c using
 *       version : 1.31 $ of : mfd-interface.m2c,v $ 
 *
 * $Id$
 */
/*
 * *********************************************************************
 * *********************************************************************
 * *********************************************************************
 * ***                                                               ***
 * ***  NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE  ***
 * ***                                                               ***
 * ***                                                               ***
 * ***       THIS FILE DOES NOT CONTAIN ANY USER EDITABLE CODE.      ***
 * ***                                                               ***
 * ***                                                               ***
 * ***       THE GENERATED CODE IS INTERNAL IMPLEMENTATION, AND      ***
 * ***                                                               ***
 * ***                                                               ***
 * ***    IS SUBJECT TO CHANGE WITHOUT WARNING IN FUTURE RELEASES.   ***
 * ***                                                               ***
 * ***                                                               ***
 * *********************************************************************
 * *********************************************************************
 * *********************************************************************
 */

/*
 * standard Net-SNMP includes 
 */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

/*
 * include our parent header 
 */
#include "ifTable.h"


#include <net-snmp/library/container.h>

#include "ifTable_interface.h"

/**********************************************************************
 **********************************************************************
 ***
 *** Table ifTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * ifTable is subid 2 of interfaces.
 * It's status is Current.
 * OID: .1.3.6.1.2.1.2.2, length: 8
 */
typedef struct ifTable_interface_ctx_s {

    netsnmp_container *container;
    netsnmp_cache  *cache;      /* optional cache */

    ifTable_registration_ptr user_ctx;

    netsnmp_table_registration_info tbl_info;

    netsnmp_baby_steps_access_methods access_multiplexer;

} ifTable_interface_ctx;

static ifTable_interface_ctx ifTable_if_ctx;

static void     _ifTable_container_init(ifTable_interface_ctx * if_ctx);


static Netsnmp_Node_Handler _mfd_ifTable_pre_request;
static Netsnmp_Node_Handler _mfd_ifTable_post_request;
static Netsnmp_Node_Handler _mfd_ifTable_object_lookup;
static Netsnmp_Node_Handler _mfd_ifTable_get_values;
static Netsnmp_Node_Handler _mfd_ifTable_check_objects;
static Netsnmp_Node_Handler _mfd_ifTable_undo_setup;
static Netsnmp_Node_Handler _mfd_ifTable_set_values;
static Netsnmp_Node_Handler _mfd_ifTable_undo_cleanup;
static Netsnmp_Node_Handler _mfd_ifTable_undo_values;
static Netsnmp_Node_Handler _mfd_ifTable_commit;
static Netsnmp_Node_Handler _mfd_ifTable_undo_commit;
static Netsnmp_Node_Handler _mfd_ifTable_check_dependencies;

NETSNMP_STATIC_INLINE int _ifTable_undo_column(ifTable_rowreq_ctx *
                                               rowreq_ctx,
                                               netsnmp_variable_list * var,
                                               int column);

static ifTable_data *ifTable_allocate_data(void);

/**
 * @internal
 * Initialize the table ifTable 
 *    (Define its contents and how it's structured)
 */
void
_ifTable_initialize_interface(ifTable_registration_ptr reg_ptr,
                              u_long flags)
{
    netsnmp_baby_steps_access_methods *access_multiplexer =
        &ifTable_if_ctx.access_multiplexer;
    netsnmp_table_registration_info *tbl_info = &ifTable_if_ctx.tbl_info;
    netsnmp_handler_registration *reginfo;
    netsnmp_mib_handler *handler;
    int             mfd_modes;

    DEBUGMSGTL(("internal:_ifTable_initialize_interface", "called\n"));


    /*
     * set up the container. This is outside the rewrite ifdef, because
     * the container is used by the ifXTable too..
     */
    _ifTable_container_init(&ifTable_if_ctx);
    if (NULL == ifTable_if_ctx.container) {
        snmp_log(LOG_ERR, "could not initialize container for ifTable\n");
        return;
    }

#ifdef NETSNMP_ENABLE_MFD_REWRITES
    /*************************************************
     *
     * save interface context for ifTable
     */
    /*
     * Setting up the table's definition
     */
    netsnmp_table_helper_add_indexes(tbl_info, ASN_INTEGER,
                                               /** index: ifIndex */
                                     0);

    /*
     * Define the minimum and maximum accessible columns.  This
     * optimizes retrival. 
     */
    tbl_info->min_column = IFTABLE_MIN_COL;
    tbl_info->max_column = IFTABLE_MAX_COL;

    /*
     * save users context
     */
    ifTable_if_ctx.user_ctx = reg_ptr;

    /*
     * call data access initialization code
     */
    ifTable_init_data(reg_ptr);

    /*
     * access_multiplexer: REQUIRED wrapper for get request handling
     */
    access_multiplexer->object_lookup = _mfd_ifTable_object_lookup;
    access_multiplexer->get_values = _mfd_ifTable_get_values;

    /*
     * no wrappers yet
     */
    access_multiplexer->pre_request = _mfd_ifTable_pre_request;
    access_multiplexer->post_request = _mfd_ifTable_post_request;


    /*
     * REQUIRED wrappers for set request handling
     */
    access_multiplexer->object_syntax_checks = _mfd_ifTable_check_objects;
    access_multiplexer->undo_setup = _mfd_ifTable_undo_setup;
    access_multiplexer->undo_cleanup = _mfd_ifTable_undo_cleanup;
    access_multiplexer->set_values = _mfd_ifTable_set_values;
    access_multiplexer->undo_sets = _mfd_ifTable_undo_values;

    /*
     * no wrappers yet
     */
    access_multiplexer->commit = _mfd_ifTable_commit;
    access_multiplexer->undo_commit = _mfd_ifTable_undo_commit;

    /*
     * REQUIRED for tables with dependencies
     */
    access_multiplexer->consistency_checks =
        _mfd_ifTable_check_dependencies;

    /*************************************************
     *
     * Create a registration, save our reg data, register table.
     */
    DEBUGMSGTL(("ifTable:init_ifTable",
                "Registering ifTable as a mibs-for-dummies table.\n"));
    handler =
        netsnmp_baby_steps_access_multiplexer_get(access_multiplexer);
    reginfo =
        netsnmp_handler_registration_create("ifTable", handler,
                                            ifTable_oid, ifTable_oid_size,
                                            HANDLER_CAN_BABY_STEP |
                                            HANDLER_CAN_RWRITE);
    if (NULL == reginfo) {
        snmp_log(LOG_ERR, "error registering tabel ifTable\n");
        return;
    }
    reginfo->my_reg_void = &ifTable_if_ctx;

    /*************************************************
     *
     * set up baby steps handler, create it and inject it
     */
    if (access_multiplexer->object_lookup)
        mfd_modes |= BABY_STEP_OBJECT_LOOKUP;
    if (access_multiplexer->set_values)
        mfd_modes |= BABY_STEP_SET_VALUES;
    if (access_multiplexer->irreversible_commit)
        mfd_modes |= BABY_STEP_IRREVERSIBLE_COMMIT;
    if (access_multiplexer->object_syntax_checks)
        mfd_modes |= BABY_STEP_CHECK_OBJECT;

    if (access_multiplexer->pre_request)
        mfd_modes |= BABY_STEP_PRE_REQUEST;
    if (access_multiplexer->post_request)
        mfd_modes |= BABY_STEP_POST_REQUEST;

    if (access_multiplexer->undo_setup)
        mfd_modes |= BABY_STEP_UNDO_SETUP;
    if (access_multiplexer->undo_cleanup)
        mfd_modes |= BABY_STEP_UNDO_CLEANUP;
    if (access_multiplexer->undo_sets)
        mfd_modes |= BABY_STEP_UNDO_SETS;

    if (access_multiplexer->row_creation)
        mfd_modes |= BABY_STEP_ROW_CREATE;
    if (access_multiplexer->consistency_checks)
        mfd_modes |= BABY_STEP_CHECK_CONSISTENCY;
    if (access_multiplexer->commit)
        mfd_modes |= BABY_STEP_COMMIT;
    if (access_multiplexer->undo_commit)
        mfd_modes |= BABY_STEP_UNDO_COMMIT;

    handler = netsnmp_baby_steps_handler_get(mfd_modes);
    netsnmp_inject_handler(reginfo, handler);

    /*************************************************
     *
     * inject container_table helper
     */
    handler =
        netsnmp_container_table_handler_get(tbl_info,
                                            ifTable_if_ctx.container,
                                            TABLE_CONTAINER_KEY_NETSNMP_INDEX);
    netsnmp_inject_handler(reginfo, handler);

    /*************************************************
     *
     * inject row_merge helper with prefix rootoid_len + 2 (entry.col)
     */
    handler = netsnmp_get_row_merge_handler(reginfo->rootoid_len + 2);
    netsnmp_inject_handler(reginfo, handler);

    /*************************************************
     *
     * inject cache helper
     */
    if (NULL != ifTable_if_ctx.cache) {
        handler = netsnmp_cache_handler_get(ifTable_if_ctx.cache);
        netsnmp_inject_handler(reginfo, handler);
    }

    /*
     * register table
     */
    netsnmp_register_table(reginfo, tbl_info);
#endif /* NETSNMP_ENABLE_MFD_REWRITES */
}

void
ifTable_valid_columns_set(netsnmp_column_info *vc)
{
    ifTable_if_ctx.tbl_info.valid_columns = vc;
}

/**
 * @internal
 * convert the index component stored in the context to an oid
 */
int
ifTable_index_to_oid(netsnmp_index * oid_idx, ifTable_mib_index * mib_idx)
{
    int             err = SNMP_ERR_NOERROR;

    /*
     * temp storage for parsing indexes
     */
    /*
     * ifIndex(1)/InterfaceIndex/ASN_INTEGER/long(long)//l/A/w/e/R/d/H
     */
    netsnmp_variable_list var_ifIndex;

    /*
     * set up varbinds
     */
    memset(&var_ifIndex, 0x00, sizeof(var_ifIndex));
    var_ifIndex.type = ASN_INTEGER;

    /*
     * chain temp index varbinds together
     */
    var_ifIndex.next_variable = NULL;


    DEBUGMSGTL(("verbose:ifTable_index_to_oid", "called\n"));

    /*
     * ifIndex(1)/InterfaceIndex/ASN_INTEGER/long(long)//l/A/w/e/R/d/H 
     */
    snmp_set_var_value(&var_ifIndex, (u_char *) & mib_idx->ifIndex,
                       sizeof(mib_idx->ifIndex));


    err = build_oid_noalloc(oid_idx->oids, oid_idx->len, &oid_idx->len,
                            NULL, 0, &var_ifIndex);
    if (err)
        snmp_log(LOG_ERR, "error %d converting index to oid\n");

    /*
     * parsing may have allocated memory. free it.
     */
    snmp_reset_var_buffers(&var_ifIndex);

    return err;
}

/**
 * extract ifTable indexes from a netsnmp_index
 *
 * @retval SNMP_ERR_NOERROR  : no error
 * @retval SNMP_ERR_GENERR   : error
 */
int
ifTable_index_from_oid(netsnmp_index * oid_idx,
                       ifTable_mib_index * mib_idx)
{
    int             err = SNMP_ERR_NOERROR;

    /*
     * temp storage for parsing indexes
     */
    /*
     * ifIndex(1)/InterfaceIndex/ASN_INTEGER/long(long)//l/A/w/e/R/d/H
     */
    netsnmp_variable_list var_ifIndex;

    /*
     * set up varbinds
     */
    memset(&var_ifIndex, 0x00, sizeof(var_ifIndex));
    var_ifIndex.type = ASN_INTEGER;

    /*
     * chain temp index varbinds together
     */
    var_ifIndex.next_variable = NULL;


    DEBUGMSGTL(("verbose:ifTable_index_from_oid", "called\n"));

    /*
     * parse the oid into the individual index components
     */
    err = parse_oid_indexes(oid_idx->oids, oid_idx->len, &var_ifIndex);
    if (err == SNMP_ERR_NOERROR) {
        /*
         * copy out values
         */
        mib_idx->ifIndex = *((long *) var_ifIndex.val.string);
    }

    /*
     * parsing may have allocated memory. free it.
     */
    snmp_reset_var_buffers(&var_ifIndex);

    return err;
}


/*
 * ifTable_allocate_data
 *
 * Purpose: create new ifTable_data.
 */
ifTable_data   *
ifTable_allocate_data(void)
{
    /*
     * allocate memory for the context
     */
    ifTable_data   *rtn = SNMP_MALLOC_TYPEDEF(ifTable_data);

    DEBUGMSGTL(("verbose:ifTable_allocate_data", "called\n"));

    if (NULL == rtn) {
        snmp_log(LOG_ERR, "unable to malloc memory for new "
                 "ifTable_data.\n");
    }

    return rtn;
}

/*
 * ifTable_release_data
 *
 * Purpose: release ifTable data.
 */
void
ifTable_release_data(ifTable_data * data)
{
    DEBUGMSGTL(("verbose:ifTable_release_data", "called\n"));

    /*
     * release memory for the context
     */
    free(data);
}

/*
 *********************************************************************
 * @internal
 * allocate resources for a ifTable_rowreq_ctx
 */
ifTable_rowreq_ctx *
ifTable_allocate_rowreq_ctx(void *user_init_ctx)
{
    ifTable_rowreq_ctx *rowreq_ctx =
        SNMP_MALLOC_TYPEDEF(ifTable_rowreq_ctx);

    DEBUGMSGTL(("internal:ifTable_allocate_rowreq_ctx", "called\n"));

    if (NULL == rowreq_ctx) {
        snmp_log(LOG_ERR, "Couldn't allocate memory for a "
                 "ifTable_rowreq_ctx.\n");
    }

    rowreq_ctx->oid_idx.oids = rowreq_ctx->oid_tmp;

    rowreq_ctx->ifTable_data_list = NULL;
    rowreq_ctx->ifTable_reg = ifTable_if_ctx.user_ctx;

    if (SNMPERR_SUCCESS !=
        ifTable_rowreq_ctx_init(rowreq_ctx, user_init_ctx)) {
        ifTable_release_rowreq_ctx(rowreq_ctx);
        rowreq_ctx = NULL;
    }

    return rowreq_ctx;
}

/*
 * @internal
 * release resources for a ifTable_rowreq_ctx
 */
void
ifTable_release_rowreq_ctx(ifTable_rowreq_ctx * rowreq_ctx)
{
    DEBUGMSGTL(("internal:ifTable_release_rowreq_ctx", "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    ifTable_rowreq_ctx_cleanup(rowreq_ctx);

    if (rowreq_ctx->undo)
        ifTable_release_data(rowreq_ctx->undo);

    /*
     * free index oid pointer
     */
    if (rowreq_ctx->oid_idx.oids != rowreq_ctx->oid_tmp)
        free(rowreq_ctx->oid_idx.oids);

    SNMP_FREE(rowreq_ctx);
}

/**
 * @internal
 * wrapper
 */
static int
_mfd_ifTable_pre_request(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info *agtreq_info,
                         netsnmp_request_info *requests)
{
    return ifTable_pre_request(ifTable_if_ctx.user_ctx);
}

/**
 * @internal
 * wrapper
 */
static int
_mfd_ifTable_post_request(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info *agtreq_info,
                          netsnmp_request_info *requests)
{
    return ifTable_post_request(ifTable_if_ctx.user_ctx);
}

/**
 * @internal
 * wrapper
 */
static int
_mfd_ifTable_object_lookup(netsnmp_mib_handler *handler,
                           netsnmp_handler_registration *reginfo,
                           netsnmp_agent_request_info *agtreq_info,
                           netsnmp_request_info *requests)
{
    ifTable_rowreq_ctx *rowreq_ctx =
        netsnmp_container_table_extract_context(requests);

    DEBUGMSGTL(("internal:_mfd_ifTable_object_lookup", "called\n"));

    /*
     * get our context from mfd
     * ifTable_interface_ctx *if_ctx =
     *             (ifTable_interface_ctx *)reginfo->my_reg_void;
     */

    if (NULL == rowreq_ctx) {
        netsnmp_request_set_error_all(requests, SNMP_ERR_NOCREATION);
    } else {
        ifTable_row_prep(rowreq_ctx);
    }

    return MFD_SUCCESS;
}

/***********************************************************************
 *
 * GET processing
 *
 ***********************************************************************/
/*
 * @internal
 * Retrieve the value for a particular column
 */
NETSNMP_STATIC_INLINE int
_ifTable_get_column(ifTable_rowreq_ctx * rowreq_ctx,
                    netsnmp_variable_list * var, int column)
{
    int             rc = SNMPERR_SUCCESS;

    DEBUGMSGTL(("internal:_ifTable_get_column", "called\n"));


    netsnmp_assert(NULL != rowreq_ctx);

    switch (column) {

        /*
         * (INDEX) ifIndex(1)/InterfaceIndex/ASN_INTEGER/long(long)//l/A/w/e/R/d/H 
         */
    case COLUMN_IFINDEX:
        var->type = ASN_INTEGER;
        var->val_len = sizeof(long);
        (*var->val.integer) = rowreq_ctx->tbl_idx.ifIndex;
        break;

        /*
         * ifDescr(2)/DisplayString/ASN_OCTET_STR/char(char)//L/A/w/e/R/d/H 
         */
    case COLUMN_IFDESCR:
        var->type = ASN_OCTET_STR;
        rc = ifDescr_get(rowreq_ctx, (char **) &var->val.string,
                         &var->val_len);
        break;

        /*
         * ifType(3)/IANAifType/ASN_INTEGER/long(u_long)//l/A/w/E/r/d/h 
         */
    case COLUMN_IFTYPE:
        var->val_len = sizeof(u_long);
        var->type = ASN_INTEGER;
        rc = ifType_get(rowreq_ctx, (u_long *) var->val.string);
        break;

        /*
         * ifMtu(4)/INTEGER32/ASN_INTEGER/long(long)//l/A/w/e/r/d/h 
         */
    case COLUMN_IFMTU:
        var->val_len = sizeof(long);
        var->type = ASN_INTEGER;
        rc = ifMtu_get(rowreq_ctx, (long *) var->val.string);
        break;

        /*
         * ifSpeed(5)/GAUGE/ASN_GAUGE/u_long(u_long)//l/A/w/e/r/d/h 
         */
    case COLUMN_IFSPEED:
        var->val_len = sizeof(u_long);
        var->type = ASN_GAUGE;
        rc = ifSpeed_get(rowreq_ctx, (u_long *) var->val.string);
        break;

        /*
         * ifPhysAddress(6)/PhysAddress/ASN_OCTET_STR/char(char)//L/A/w/e/r/d/H 
         */
    case COLUMN_IFPHYSADDRESS:
        var->type = ASN_OCTET_STR;
        rc = ifPhysAddress_get(rowreq_ctx, (char **) &var->val.string,
                               &var->val_len);
        break;

        /*
         * ifAdminStatus(7)/INTEGER/ASN_INTEGER/long(u_long)//l/A/W/E/r/d/h 
         */
    case COLUMN_IFADMINSTATUS:
        var->val_len = sizeof(u_long);
        var->type = ASN_INTEGER;
        rc = ifAdminStatus_get(rowreq_ctx, (u_long *) var->val.string);
        break;

        /*
         * ifOperStatus(8)/INTEGER/ASN_INTEGER/long(u_long)//l/A/w/E/r/d/h 
         */
    case COLUMN_IFOPERSTATUS:
        var->val_len = sizeof(u_long);
        var->type = ASN_INTEGER;
        rc = ifOperStatus_get(rowreq_ctx, (u_long *) var->val.string);
        break;

        /*
         * ifLastChange(9)/TICKS/ASN_TIMETICKS/u_long(u_long)//l/A/w/e/r/d/h 
         */
    case COLUMN_IFLASTCHANGE:
        var->val_len = sizeof(u_long);
        var->type = ASN_TIMETICKS;
        rc = ifLastChange_get(rowreq_ctx, (u_long *) var->val.string);
        break;

        /*
         * ifInOctets(10)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h 
         */
    case COLUMN_IFINOCTETS:
        var->val_len = sizeof(u_long);
        var->type = ASN_COUNTER;
        rc = ifInOctets_get(rowreq_ctx, (u_long *) var->val.string);
        break;

        /*
         * ifInUcastPkts(11)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h 
         */
    case COLUMN_IFINUCASTPKTS:
        var->val_len = sizeof(u_long);
        var->type = ASN_COUNTER;
        rc = ifInUcastPkts_get(rowreq_ctx, (u_long *) var->val.string);
        break;

        /*
         * ifInNUcastPkts(12)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h 
         */
    case COLUMN_IFINNUCASTPKTS:
        var->val_len = sizeof(u_long);
        var->type = ASN_COUNTER;
        rc = ifInNUcastPkts_get(rowreq_ctx, (u_long *) var->val.string);
        break;

        /*
         * ifInDiscards(13)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h 
         */
    case COLUMN_IFINDISCARDS:
        var->val_len = sizeof(u_long);
        var->type = ASN_COUNTER;
        rc = ifInDiscards_get(rowreq_ctx, (u_long *) var->val.string);
        break;

        /*
         * ifInErrors(14)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h 
         */
    case COLUMN_IFINERRORS:
        var->val_len = sizeof(u_long);
        var->type = ASN_COUNTER;
        rc = ifInErrors_get(rowreq_ctx, (u_long *) var->val.string);
        break;

        /*
         * ifInUnknownProtos(15)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h 
         */
    case COLUMN_IFINUNKNOWNPROTOS:
        var->val_len = sizeof(u_long);
        var->type = ASN_COUNTER;
        rc = ifInUnknownProtos_get(rowreq_ctx, (u_long *) var->val.string);
        break;

        /*
         * ifOutOctets(16)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h 
         */
    case COLUMN_IFOUTOCTETS:
        var->val_len = sizeof(u_long);
        var->type = ASN_COUNTER;
        rc = ifOutOctets_get(rowreq_ctx, (u_long *) var->val.string);
        break;

        /*
         * ifOutUcastPkts(17)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h 
         */
    case COLUMN_IFOUTUCASTPKTS:
        var->val_len = sizeof(u_long);
        var->type = ASN_COUNTER;
        rc = ifOutUcastPkts_get(rowreq_ctx, (u_long *) var->val.string);
        break;

        /*
         * ifOutNUcastPkts(18)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h 
         */
    case COLUMN_IFOUTNUCASTPKTS:
        var->val_len = sizeof(u_long);
        var->type = ASN_COUNTER;
        rc = ifOutNUcastPkts_get(rowreq_ctx, (u_long *) var->val.string);
        break;

        /*
         * ifOutDiscards(19)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h 
         */
    case COLUMN_IFOUTDISCARDS:
        var->val_len = sizeof(u_long);
        var->type = ASN_COUNTER;
        rc = ifOutDiscards_get(rowreq_ctx, (u_long *) var->val.string);
        break;

        /*
         * ifOutErrors(20)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h 
         */
    case COLUMN_IFOUTERRORS:
        var->val_len = sizeof(u_long);
        var->type = ASN_COUNTER;
        rc = ifOutErrors_get(rowreq_ctx, (u_long *) var->val.string);
        break;

        /*
         * ifOutQLen(21)/GAUGE/ASN_GAUGE/u_long(u_long)//l/A/w/e/r/d/h 
         */
    case COLUMN_IFOUTQLEN:
        var->val_len = sizeof(u_long);
        var->type = ASN_GAUGE;
        rc = ifOutQLen_get(rowreq_ctx, (u_long *) var->val.string);
        break;

        /*
         * ifSpecific(22)/OBJECTID/ASN_OBJECT_ID/oid(oid)//L/A/w/e/r/d/h 
         */
    case COLUMN_IFSPECIFIC:
        var->type = ASN_OBJECT_ID;
        rc = ifSpecific_get(rowreq_ctx, (oid **) & var->val.string,
                            &var->val_len);
        break;

    }

    return rc;
}

int
_mfd_ifTable_get_values(netsnmp_mib_handler *handler,
                        netsnmp_handler_registration *reginfo,
                        netsnmp_agent_request_info *agtreq_info,
                        netsnmp_request_info *requests)
{
    ifTable_rowreq_ctx *rowreq_ctx =
        netsnmp_container_table_extract_context(requests);
    netsnmp_table_request_info *tri;
    u_char         *old_string;
    void            (*dataFreeHook) (void *);
    int             rc;

    DEBUGMSGTL(("internal:_mfd_ifTable_get_values", "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    for (; requests; requests = requests->next) {
        /*
         * save old pointer, so we can free it if replaced
         */
        old_string = requests->requestvb->val.string;
        dataFreeHook = requests->requestvb->dataFreeHook;
        if (NULL == requests->requestvb->val.string) {
            requests->requestvb->val.string = requests->requestvb->buf;
            requests->requestvb->val_len =
                sizeof(requests->requestvb->buf);
        } else if (requests->requestvb->buf ==
                   requests->requestvb->val.string) {
            if (requests->requestvb->val_len !=
                sizeof(requests->requestvb->buf))
                requests->requestvb->val_len =
                    sizeof(requests->requestvb->buf);
        }

        /*
         * get column data
         */
        tri = netsnmp_extract_table_info(requests);
        if (NULL == tri)
            continue;

        rc = _ifTable_get_column(rowreq_ctx, requests->requestvb,
                                 tri->colnum);
        if (rc) {
            if (MFD_SKIP == rc) {
                requests->requestvb->type = ASN_PRIV_RETRY;
                rc = SNMP_ERR_NOERROR;
            }
        } else if (NULL == requests->requestvb->val.string) {
            snmp_log(LOG_ERR, "NULL varbind data pointer!\n");
            rc = SNMP_ERR_GENERR;
        }
        if (rc)
            netsnmp_request_set_error(requests, rc);

        /*
         * if the buffer wasn't used previously for the old data (i.e. it
         * was allcoated memory)  and the get routine replaced the pointer,
         * we need to free the previous pointer.
         */
        if (old_string && (old_string != requests->requestvb->buf) &&
            (requests->requestvb->val.string != old_string)) {
            if (dataFreeHook)
                (*dataFreeHook) (old_string);
            else
                free(old_string);
        }
    }                           /* for results */

    return SNMP_ERR_NOERROR;
}

/***********************************************************************
 *
 * SET processing
 *
 ***********************************************************************/

/*----------------------------------------------------------------------
 *
 * SET: Syntax checks
 *
 *---------------------------------------------------------------------*/
/*
 * @internal
 * Check the syntax for a particular column
 */
NETSNMP_STATIC_INLINE int
_ifTable_check_column(ifTable_rowreq_ctx * rowreq_ctx,
                      netsnmp_variable_list * var, int column)
{
    int             rc = SNMPERR_SUCCESS;

    DEBUGMSGTL(("internal:_ifTable_check_column", "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    switch (column) {

        /*
         * ifAdminStatus(7)/INTEGER/ASN_INTEGER/long(u_long)//l/A/W/E/r/d/h 
         */
    case COLUMN_IFADMINSTATUS:
        /** special case: we are using exernal storage w/smaller data size
         ** for storage, so we can't use sizeof on data context. So we
         ** just check that it's the expected size. The enum tests below
         ** will ensure that there is no data overflow. */
        rc = netsnmp_check_vb_type_and_size(var, ASN_INTEGER, sizeof(u_long));
        if (SNMPERR_SUCCESS == rc) {

            /*
             * check that the value is one of defined enums 
             */
            if (1 && (*var->val.integer != IFADMINSTATUS_UP)
                && (*var->val.integer != IFADMINSTATUS_DOWN)
                && (*var->val.integer != IFADMINSTATUS_TESTING)
                ) {
                rc = SNMP_ERR_WRONGVALUE;
            }
        }
        if (SNMPERR_SUCCESS == rc) {
            rc = ifAdminStatus_check_value(rowreq_ctx,
                                           *((u_long *) var->val.string));
            if ((MFD_SUCCESS != rc) && (MFD_NOT_VALID_EVER != rc)
                && (MFD_NOT_VALID_NOW != rc)) {
                snmp_log(LOG_ERR,
                         "bad rc %d from ifAdminStatus_check_value\n", rc);
                rc = SNMP_ERR_GENERR;
            }
        }
        break;

    default:    /** We shouldn't get here */
        rc = SNMP_ERR_GENERR;
        snmp_log(LOG_ERR, "unknown column in _ifTable_check_column\n");
    }

    return rc;
}

int
_mfd_ifTable_check_objects(netsnmp_mib_handler *handler,
                           netsnmp_handler_registration *reginfo,
                           netsnmp_agent_request_info *agtreq_info,
                           netsnmp_request_info *requests)
{
    ifTable_rowreq_ctx *rowreq_ctx =
        netsnmp_container_table_extract_context(requests);
    netsnmp_table_request_info *tri;
    int             rc;

    DEBUGMSGTL(("internal:_mfd_ifTable_check_objects", "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    for (; requests; requests = requests->next) {

        /*
         * get column number from table request info, and check that column
         */
        tri = netsnmp_extract_table_info(requests);
        if (NULL == tri)
            continue;

        rc = _ifTable_check_column(rowreq_ctx, requests->requestvb,
                                   tri->colnum);
        if (rc) {
            netsnmp_request_set_error(requests, rc);
            break;
        }

    }                           /* for results */

    return rc;
}



/*----------------------------------------------------------------------
 *
 * SET: check dependencies
 *
 *---------------------------------------------------------------------*/
/*
 * @internal
 * Check dependencies wrapper
 */
static int
_mfd_ifTable_check_dependencies(netsnmp_mib_handler *handler,
                                netsnmp_handler_registration *reginfo,
                                netsnmp_agent_request_info *agtreq_info,
                                netsnmp_request_info *requests)
{
    ifTable_rowreq_ctx *rowreq_ctx =
        netsnmp_container_table_extract_context(requests);
    DEBUGMSGTL(("internal:_mfd_ifTable_check_dependencies", "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    return ifTable_check_dependencies(rowreq_ctx);
}

/*----------------------------------------------------------------------
 *
 * SET: Undo setup
 *
 *---------------------------------------------------------------------*/
/**
 * @internal
 * undo setup
 */
int
_mfd_ifTable_undo_setup(netsnmp_mib_handler *handler,
                        netsnmp_handler_registration *reginfo,
                        netsnmp_agent_request_info *agtreq_info,
                        netsnmp_request_info *requests)
{
    ifTable_rowreq_ctx *rowreq_ctx =
        netsnmp_container_table_extract_context(requests);
    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * allocate undo context
     */
    rowreq_ctx->undo = ifTable_allocate_data();
    if (NULL == rowreq_ctx->undo) {
        /** msg already logged */
        return SNMP_ERR_RESOURCEUNAVAILABLE;
    }

    return ifTable_undo_setup(rowreq_ctx);
}

/**
 * @internal
 * undo setup
 */
int
_mfd_ifTable_undo_cleanup(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info *agtreq_info,
                          netsnmp_request_info *requests)
{
    ifTable_rowreq_ctx *rowreq_ctx =
        netsnmp_container_table_extract_context(requests);
    int             rc = MFD_SUCCESS;

    netsnmp_assert(NULL != rowreq_ctx);

    if (rowreq_ctx->undo)
        rc = MFD_SUCCESS;

    /*
     * call user cleanup
     */
    rc = ifTable_undo_cleanup(rowreq_ctx);

    /*
     * release undo context, if needed
     */
    if (rowreq_ctx->undo)
        ifTable_release_data(rowreq_ctx->undo);


    /*
     * clear set flags
     */
    rowreq_ctx->set_flags = 0;

    return rc;
}

/*----------------------------------------------------------------------
 *
 * SET: Set values
 *
 *---------------------------------------------------------------------*/
/*
 * @internal
 * Set the value for a particular column
 */
NETSNMP_STATIC_INLINE int
_ifTable_set_column(ifTable_rowreq_ctx * rowreq_ctx,
                    netsnmp_variable_list * var, int column)
{
    int             rc = SNMPERR_SUCCESS;

    DEBUGMSGTL(("internal:_ifTable_set_column", "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    switch (column) {

        /*
         * ifAdminStatus(7)/INTEGER/ASN_INTEGER/long(u_long)//l/A/W/E/r/d/h 
         */
    case COLUMN_IFADMINSTATUS:
        if (var->val_len != sizeof(u_long)) {
            rc = MFD_ERROR;
            snmp_log(LOG_ERR,
                     "varbind size of %d does not match expected size %d\n",
                     var->val_len, sizeof(u_long));
            break;
        }
        rowreq_ctx->set_flags |= FLAG_IFADMINSTATUS;
        rc = ifAdminStatus_set(rowreq_ctx, *((u_long *) var->val.string));
        break;

    }


    return rc;
}

int
_mfd_ifTable_set_values(netsnmp_mib_handler *handler,
                        netsnmp_handler_registration *reginfo,
                        netsnmp_agent_request_info *agtreq_info,
                        netsnmp_request_info *requests)
{
    ifTable_rowreq_ctx *rowreq_ctx =
        netsnmp_container_table_extract_context(requests);
    netsnmp_table_request_info *tri;
    int             rc = SNMP_ERR_NOERROR;

    DEBUGMSGTL(("internal:_mfd_ifTable_set_values", "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    rowreq_ctx->set_flags = 0;
    for (; requests; requests = requests->next) {
        /*
         * set column data
         */
        tri = netsnmp_extract_table_info(requests);
        if (NULL == tri)
            continue;

        rc = _ifTable_set_column(rowreq_ctx,
                                 requests->requestvb, tri->colnum);
        if (MFD_SUCCESS != rc)
            netsnmp_set_request_error(agtreq_info, requests, rc);

    }                           /* for results */

    return rc;
}

/*----------------------------------------------------------------------
 *
 * SET: commit
 *
 *---------------------------------------------------------------------*/
/**
 * @internal
 * commit the values
 */
int
_mfd_ifTable_commit(netsnmp_mib_handler *handler,
                    netsnmp_handler_registration *reginfo,
                    netsnmp_agent_request_info *agtreq_info,
                    netsnmp_request_info *requests)
{
    ifTable_rowreq_ctx *rowreq_ctx =
        netsnmp_container_table_extract_context(requests);
    netsnmp_assert(NULL != rowreq_ctx);
    return ifTable_commit(rowreq_ctx);
}

int
_mfd_ifTable_undo_commit(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info *agtreq_info,
                         netsnmp_request_info *requests)
{
    ifTable_rowreq_ctx *rowreq_ctx =
        netsnmp_container_table_extract_context(requests);
    netsnmp_assert(NULL != rowreq_ctx);
    return ifTable_undo_commit(rowreq_ctx);
}

/*----------------------------------------------------------------------
 *
 * SET: Undo
 *
 *---------------------------------------------------------------------*/
/**
 * @internal
 * undo the value for a particular column
 */
NETSNMP_STATIC_INLINE int
_ifTable_undo_column(ifTable_rowreq_ctx * rowreq_ctx,
                     netsnmp_variable_list * var, int column)
{
    int             rc = SNMPERR_SUCCESS;

    DEBUGMSGTL(("internal:_ifTable_undo_column", "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    switch (column) {

        /*
         * ifAdminStatus(7)/INTEGER/ASN_INTEGER/long(u_long)//l/A/W/E/r/d/h 
         */
    case COLUMN_IFADMINSTATUS:
        rc = ifAdminStatus_undo(rowreq_ctx);
        break;

    }

    return rc;
}

int
_mfd_ifTable_undo_values(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info *agtreq_info,
                         netsnmp_request_info *requests)
{
    ifTable_rowreq_ctx *rowreq_ctx =
        netsnmp_container_table_extract_context(requests);
    netsnmp_table_request_info *tri;
    int             rc = SNMP_ERR_NOERROR;

    DEBUGMSGTL(("internal:_mfd_ifTable_undo_values", "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    for (; requests; requests = requests->next) {
        /*
         * set column data
         */
        tri = netsnmp_extract_table_info(requests);
        if (NULL == tri)
            continue;

        _ifTable_undo_column(rowreq_ctx, requests->requestvb, tri->colnum);

    }                           /* for results */

    return rc;
}

/***********************************************************************
 *
 * DATA ACCESS
 *
 ***********************************************************************/
/**
 * @internal
 */
static int
_cache_load(netsnmp_cache * cache, void *vmagic)
{
    DEBUGMSGTL(("internal:ifTable:_cache_load", "called\n"));

    if ((NULL == cache) || (NULL == cache->magic)) {
        snmp_log(LOG_ERR, "invalid cache for ifTable_cache_load\n");
        return -1;
    }

    /** should only be called for an invalid or expired cache */
    netsnmp_assert((0 == cache->valid) || (1 == cache->expired));

    /*
     * call user code
     */
    return ifTable_cache_load((netsnmp_container *) cache->magic);
}

/**
 * @internal
 */
static void
_cache_item_free(ifTable_rowreq_ctx * rowreq_ctx, void *context)
{
    DEBUGMSGTL(("internal:ifTable:_cache_item_free", "called\n"));

    if (NULL == rowreq_ctx)
        return;

    ifTable_release_rowreq_ctx(rowreq_ctx);
}

/**
 * @internal
 */
static void
_cache_free(netsnmp_cache * cache, void *magic)
{
    netsnmp_container *container;

    DEBUGMSGTL(("internal:ifTable:_cache_free", "called\n"));

    if ((NULL == cache) || (NULL == cache->magic)) {
        snmp_log(LOG_ERR, "invalid cache in ifTable_cache_free\n");
        return;
    }

    container = (netsnmp_container *) cache->magic;

    /*
     * call user code
     */
    ifTable_cache_free(container);

    /*
     * free all items. inefficient, but easy.
     */
    CONTAINER_CLEAR(container,
                    (netsnmp_container_obj_func *) _cache_item_free, NULL);
}

/**
 * @internal
 * initialize the iterator container with functions or wrappers
 */
void
_ifTable_container_init(ifTable_interface_ctx * if_ctx)
{
    DEBUGMSGTL(("internal:ifTable:_ifTable_container_init", "called\n"));

    /*
     * set up the cache
     */
    if_ctx->cache = netsnmp_cache_create(30,    /* timeout in seconds */
                                         _cache_load, _cache_free,
                                         ifTable_oid, ifTable_oid_size);

    if (NULL == if_ctx->cache) {
        snmp_log(LOG_ERR, "error creating cache for ifTable\n");
        return;
    }

    if_ctx->cache->flags = NETSNMP_CACHE_DONT_INVALIDATE_ON_SET;

    ifTable_container_init(&if_ctx->container, if_ctx->cache);
    if (NULL == if_ctx->container)
        if_ctx->container =
            netsnmp_container_find("ifTable:table_container");
    if (NULL == if_ctx->container) {
        snmp_log(LOG_ERR, "error creating container in "
                 "ifTable_container_init\n");
        return;
    }
    if_ctx->cache->magic = (void *) if_ctx->container;
}
