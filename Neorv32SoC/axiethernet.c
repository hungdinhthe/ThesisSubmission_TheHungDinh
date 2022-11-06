 /** 
 **************************************************************
 * @file thesis/Neorv32SoC/axietherent.c
 * @author The Hung Dinh - 46787185
 * @date 21102022
 * @brief MAC driver
 * REFERENCE: NEORV32 Software library
 * 			  Xilinx Emaclite Standalone Driver
 ***************************************************************
 */

#include "xemaclite_phy.h"
#include "xil_io.h"
#include "axiethernet.h"

#include <neorv32.h>

/*
 * Set up valid local MAC addresses.
 */
u8 LocalAddress[XEL_MAC_ADDR_SIZE] =
{
	0x00, 0x0A, 0x35, 0x01, 0x02, 0x03
};

u8 SourceAddress[XEL_MAC_ADDR_SIZE] =
{
	0x01, 0x6A, 0x54, 0x11, 0xA5, 0x45
};

/*
 * MAC initialization.
 */
int EmacLiteInitial(u16 DeviceId)
{
	int Status;
	XEmacLite *EmacLiteInstPtr;
	u32 TxLength;
	XEmacLite_Config *ConfigPtr;
	// PHY address
	u32 PhyAddress = 0;

	RecvFrameLength = 0;
	EmacLiteInstPtr =&EmacLiteInstance;
	/*
	 * Initialize the EmacLite device.
	 */
	ConfigPtr = XEmacLite_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		return XST_FAILURE;
	}
	Status = XEmacLite_CfgInitialize(EmacLiteInstPtr, ConfigPtr,
						ConfigPtr->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	/*
	 * Set the MAC address.
	 */
	XEmacLite_SetMacAddress(EmacLiteInstPtr, LocalAddress);

	/*
	 * Set up the interrupt infrastructure.
	 */
	Status = EmacLiteSetupIntrSystem();
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	/*
	 * Setup the EmacLite handlers.
	 */
	XEmacLite_SetRecvHandler((EmacLiteInstPtr), (void *)(EmacLiteInstPtr),
				 (XEmacLite_Handler)EmacLiteRecvHandler);
	XEmacLite_SetSendHandler((EmacLiteInstPtr), (void *)(EmacLiteInstPtr),
				 (XEmacLite_Handler)EmacLiteSendHandler);

	/*
	 * Empty any existing receive frames.
	 */
	XEmacLite_FlushReceive(EmacLiteInstPtr);

	/*
	 * Enable the EmacLite interrupts.
	 */
	XEmacLite_EnableInterrupts(EmacLiteInstPtr);

	/*
	 * Check if there is a Tx buffer available.
	 */
	if (XEmacLite_TxBufferAvailable(EmacLiteInstPtr) != TRUE) {
		return XST_FAILURE;
	}
	/*PHY device initial testing payload 0 to 1500*/
	/*
	 * Detect the PHY device and enable the MAC Loop back
	 * in the PHY.
	 */
	PhyAddress = EmacLitePhyDetect(EmacLiteInstPtr);
	Status = EmacLiteEnablePhyLoopBack(EmacLiteInstPtr, PhyAddress);
	if (Status != XST_SUCCESS) {
		XEmacLite_DisableInterrupts(EmacLiteInstPtr);
		EmacLiteDisableIntrSystem();
		return XST_FAILURE;
	}

	/*
	 * Send/Receive frames of varying sizes and verify the data in the
	 * received frames.
	 */
	for (TxLength = 1; TxLength <= XEL_MTU_SIZE; ) {
		RecvFrameLength = 0;

		/*
		 * Send a frame.
		 */
		Status = EmacLiteSendFrame(EmacLiteInstPtr, TxLength);
		if (Status != XST_SUCCESS) {
			/*
			 * Disable the MAC Loop back in the PHY and
			 * disable/disconnect the EmacLite Interrupts.
			 */
			EmacLiteDisablePhyLoopBack(EmacLiteInstPtr, PhyAddress);
			XEmacLite_DisableInterrupts(EmacLiteInstPtr);
			EmacLiteDisableIntrSystem();
			return XST_FAILURE;
		}

		/*
		 * Wait for the frame to be transmitted and received back.
		 * As the PHY is in loopback the transmit interrupt and the
		 * receive interrupt occur simultaneously.
		 */
		while ((TransmitComplete == FALSE) && (RecvFrameLength == 0));

		/*
		 * Check the receive frame.
		 */
		Status = EmacLiteRecvFrame(TxLength++);
		if ((Status != XST_SUCCESS) && (Status != XST_NO_DATA)) {
			/*
			 * Disable the MAC Loop back in the PHY and
			 * disable/disconnect the EmacLite Interrupts.
			 */
			EmacLiteDisablePhyLoopBack(EmacLiteInstPtr, PhyAddress);
			XEmacLite_DisableInterrupts(EmacLiteInstPtr);
			EmacLiteDisableIntrSystem();
			return XST_FAILURE;
		}
	}
	EmacLiteDisablePhyLoopBack(EmacLiteInstPtr, PhyAddress);
	
	return XST_SUCCESS;

}

/**
 * Send Ethernet frame
 * XEmacInstancePtr MAC pointer
 * PayloadSize data size 
 */
int EmacLiteSendFrame(XEmacLite *XEmacInstancePtr, u32 PayloadSize)
{
	u8 *FramePtr;
	int Index;
	int Status;

	/*
	 * Set the Complete flag to false.
	 */
	TransmitComplete = FALSE;

	/*
	 * Assemble the frame with a destination address and the source address.
	 */
	FramePtr = (u8 *)TxFrame;
	*FramePtr++ = LocalAddress[0];
	*FramePtr++ = LocalAddress[1];
	*FramePtr++ = LocalAddress[2];
	*FramePtr++ = LocalAddress[3];
	*FramePtr++ = LocalAddress[4];
	*FramePtr++ = LocalAddress[5];

	/*
	 * Fill in the source MAC address.
	 */
	*FramePtr++ = LocalAddress[0];
	*FramePtr++ = LocalAddress[1];
	*FramePtr++ = LocalAddress[2];
	*FramePtr++ = LocalAddress[3];
	*FramePtr++ = LocalAddress[4];
	*FramePtr++ = LocalAddress[5];

	/*
	 * Set up the type/length field - be sure its in network order.
	 */
    *((u16 *)FramePtr) = Xil_Htons(PayloadSize);
    FramePtr++;
	FramePtr++;

	/*
	 * Now fill in the data field with known values so we can verify them
	 * on receive.
	 */
	for (Index = 0; Index < PayloadSize; Index++) {
		*FramePtr++ = (u8)Index;
	}

	/*
	 * Now send the frame.
	 */
	Status = XEmacLite_Send(XEmacInstancePtr, (u8 *)TxFrame,
			    PayloadSize + XEL_HEADER_SIZE);

	return  Status;
}

/**
 * Receive Ethernet frame
 * PayloadSize data size 
 */
int EmacLiteRecvFrame(u32 PayloadSize)
{
	u8 *FramePtr;

	/*
	 * This assumes MAC does not strip padding or CRC.
	 */
	if (RecvFrameLength != 0) {
		int Index;

		/*
		 * Verify length, which should be the payload size.
		 */
		if ((RecvFrameLength- (XEL_HEADER_SIZE + XEL_FCS_SIZE)) !=
				PayloadSize) {
			return XST_LOOPBACK_ERROR;
		}

		/*
		 * Verify the contents of the Received Frame.
		 */
		FramePtr = (u8 *)RxFrame;
		FramePtr += XEL_HEADER_SIZE;	/* Get past the header */

		for (Index = 0; Index < PayloadSize; Index++) {
			if (*FramePtr++ != (u8)Index) {
				return XST_LOOPBACK_ERROR;
			}
		}
	}

	return XST_SUCCESS;
}

/**
 * MAC receive interrupt handler
 * CallBackRef interrupt reference
 */
void EmacLiteRecvHandler(void *CallBackRef)
{
	XEmacLite *XEmacInstancePtr;

	/*
	 * Convert the argument to something useful.
	 */
	XEmacInstancePtr = (XEmacLite *)CallBackRef;

	/*
	 * Handle the Receive callback.
	 */
	RecvFrameLength = XEmacLite_Recv(XEmacInstancePtr, (u8 *)RxFrame);
	
	// // Ethernet MAC source filter
	// u8 *FramePtr;
	// FramePtr = (u8 *)RxFrame;
	// FramePtr += XEL_MAC_ADDR_SIZE;	/* Get past the header */

	// for (int Index = 0; Index < XEL_MAC_ADDR_SIZE; Index++) {
	// 		if (*FramePtr++ != (u8)SourceAddress) {
				
	// 			//Discard caket
	// 		}
	// 	}
	// // Send packet to TCP/IP stack
}

/**
 * MAC send interrupt handler
 * CallBackRef interrupt reference
 */
void EmacLiteSendHandler(void *CallBackRef)
{
	XEmacLite *XEmacInstancePtr;

	/*
	 * Convert the argument to something useful.
	 */
	XEmacInstancePtr = (XEmacLite *)CallBackRef;

	/*
	 * Handle the Transmit callback.
	 */
	TransmitComplete = TRUE;

}

/**
 * MAC interrupt setup with NEORV32 external interrupt controller
 */
int EmacLiteSetupIntrSystem()
{

	// check if XIRQ unit is implemented at all
	if (neorv32_xirq_available() == 0) {
		neorv32_uart0_printf("XIRQ not synthesized!\n");
		return XST_FAILURE;
	}

	int err_cnt = 0;

	// initialize XIRQ controller
	err_cnt = neorv32_xirq_setup();

	// check if setup went fine
	if (err_cnt) {
		neorv32_uart0_printf("Error during XIRQ setup!\n");
		return XST_FAILURE;
	}


	// install handler functions for XIRQ channel 0
	err_cnt += neorv32_xirq_install(0, XEmacLite_InterruptHandler); // handler function for channel 0

	// check if installation went fine
	if (err_cnt) {
		neorv32_uart0_printf("Error during XIRQ install!\n");
		return XST_FAILURE;
	}

	// allow XIRQ to trigger CPU interrupt
	neorv32_xirq_global_enable();

	// enable global interrupts
	neorv32_cpu_eint();

	return XST_SUCCESS;
}

/**
 * MAC disable interrupt 
 */
void EmacLiteDisableIntrSystem()
{
	/*
	 * Disconnect and disable the interrupts for the EmacLite device.
	 */
	neorv32_xirq_global_disable();

}
