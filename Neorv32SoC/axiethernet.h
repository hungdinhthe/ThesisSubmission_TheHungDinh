 /** 
 **************************************************************
 * @file thesis/Neorv32SoC/axietherent.h
 * @author The Hung Dinh - 46787185
 * @date 21102022
 * @brief MAC driver
 * REFERENCE: NEORV32 Software library
 * 			  Xilinx Emaclite Standalone Driver
 ***************************************************************
 */

#ifndef AXIETHERNET_H		/* prevent circular inclusions */
#define AXIETHERNET_H		/* by using protection macros */

#include "xemaclite_phy.h"
#include "xil_io.h"

#include <neorv32.h>


/* UART hardware constants. */
#define BAUD_RATE 19200

/*
 * Ethernet MAC parameter in xparametr.h provided for the embedded system hardware design
 */
#define INTC_DEVICE_ID		XPAR_INTC_0_DEVICE_ID
#define INTC_EMACLITE_ID	XPAR_INTC_0_EMACLITE_0_VEC_ID


int EmacLiteInitial(u16 DeviceId);
int EmacLiteSendFrame(XEmacLite *InstancePtr, u32 PayloadSize);
int EmacLiteRecvFrame(u32 PayloadSize);
void EmacLiteRecvHandler(void *CallBackRef);
void EmacLiteSendHandler(void *CallBackRef);
void EmacLiteDisableIntrSystem();
int EmacLiteSetupIntrSystem();

#endif