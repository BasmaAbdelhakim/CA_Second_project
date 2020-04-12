/*
 * SYSTIC_config.h
 *
 *  Created on: 12 Mar 2020
 *      Author: Basma Abdelhakim
 */

#ifndef SYSTIC_CONFIG_H_
#define SYSTIC_CONFIG_H_

/*************************************************************************************************
 * Due to hardware limitation the only available option for SYS_TIC_CLKSRC is :
 *    CLKSRC_AHB_8
 ************************************************************************************************/
#define SYS_TIC_CLKSRC         CLKSRC_AHB_8


/*************************************************************************************************
 * The options for SYS_TIC_INT_STATUS field is the following :
 *    1.TIC_ENABLE_INT
 *    2.TIC_DISABLE_INT
 ************************************************************************************************/
#define SYS_TIC_INT_STATUS     TIC_ENABLE_INT


#endif /* SYSTIC_CONFIG_H_ */
