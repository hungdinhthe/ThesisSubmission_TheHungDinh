/******************************************************************************
* Copyright (C) 2009 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xemaclite_PHY.h
*
* MAC PHY control.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 2.00a ktn  04/13/09 First release
* 3.03a bss  09/01/12 Moved the declarations of RecvFrameLength
*		      TransmitComplete, EmacLiteInstance,
*		      TxFrame[XEL_MAX_FRAME_SIZE], RxFrame[XEL_MAX_FRAME_SIZE];
* 		      to xemaclite_PHY_util.c for fixing C++ compilation
*		      errors
* </pre>
*
******************************************************************************/
#ifndef XEMACLITE_PHY_H
#define XEMACLITE_PHY_H

/***************************** Include Files *********************************/

#include "xparameters.h"
#include "xemaclite.h"
#include <neorv32.h>

/************************** Constant Definitions ****************************/

#define PHY_REG0_OFFSET		0 /* Register 0 of PHY device */
#define PHY_REG1_OFFSET 	1 /* Register 1 of PHY device */

#define PHY_REG0_RESET_MASK	0x8000  /* Reset Phy device */
#define PHY_REG0_LOOPBACK_MASK	0x4000  /* Loopback Enable in Phy */
#define PHY_REG0_SPD_100_MASK	0x2000  /* Speed of 100Mbps for Phy */

#define PHY_REG1_DETECT_MASK	0x1808	/* Mask to detect PHY device */

#define EMACLITE_PHY_DELAY_SEC	4/* Amount of time to delay waiting on
					 * PHY to reset.
					 */

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define EMAC_DEVICE_ID		XPAR_EMACLITE_0_DEVICE_ID

/***************** Macros (Inline Functions) Definitions *********************/

/**************************** Type Definitions ******************************/

/************************** Function Prototypes *****************************/

/*
 * Utility functions implemented in xemaclite_PHY_util.c
 */
void EmacLitePhyDelay(unsigned int Seconds);
u32 EmacLitePhyDetect(XEmacLite *InstancePtr);
int EmacLiteEnablePhyLoopBack(XEmacLite *InstancePtr, u32 PhyAddress);
int EmacLiteDisablePhyLoopBack(XEmacLite *InstancePtr, u32 PhyAddress);

/************************** Variable Definitions ****************************/
/*
 * Set up valid local MAC addresses. This loop back test uses the LocalAddress
 * both as a source and destination MAC address.
 */

extern XEmacLite EmacLiteInstance;	/* Instance of the EmacLite */

/*
 * Buffers used for Transmission and Reception of Packets. These are declared
 * as global so that they are not a part of the stack.
 */
extern u8 TxFrame[XEL_MAX_FRAME_SIZE];
extern u8 RxFrame[XEL_MAX_FRAME_SIZE];

extern volatile u32 RecvFrameLength;	/* Indicates the length of the
					 * Received packet
					 */
extern volatile int TransmitComplete;	/* Flag to indicate that the
					 * Transmission is complete
					 */

#endif /* XEMACLITE_PHY_H */
