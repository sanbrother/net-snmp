/*
 * Note: this file originally auto-generated by mib2c using
 *       version : 1.12 $ of : mfd-data-access.m2c,v $
 *
 * $Id$
 */
#ifndef IFXTABLE_DATA_ACCESS_H
#define IFXTABLE_DATA_ACCESS_H

#ifdef __cplusplus
extern          "C" {
#endif


    /*
     *********************************************************************
     * function declarations
     */

    /*
     *********************************************************************
     * Table declarations
     */
/**********************************************************************
 **********************************************************************
 ***
 *** Table ifXTable
 ***
 **********************************************************************
 **********************************************************************/
    /*
     * ifXTable is subid 1 of ifMIBObjects.
     * Its status is Current.
     * OID: .1.3.6.1.2.1.31.1.1, length: 9
     */


    int             ifXTable_init_data(ifXTable_registration_ptr
                                       ifXTable_reg);


    /*
     * TODO:180:o: Review ifXTable cache timeout.
     * The number of seconds before the cache times out
     */
#define IFXTABLE_CACHE_TIMEOUT   60

    int             ifXTable_row_prep(ifXTable_rowreq_ctx * rowreq_ctx);


#ifdef __cplusplus
}
#endif
#endif                          /* IFXTABLE_DATA_ACCESS_H */
