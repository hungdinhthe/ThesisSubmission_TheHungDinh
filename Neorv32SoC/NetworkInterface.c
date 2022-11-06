 /** 
 **************************************************************
 * @file thesis/Neorv32SoC/NetworkInterface.c
 * @author The Hung Dinh - 46787185
 * @date 21102022
 * @brief MAC connect to FreeRTOS TCP/IP
 * REFERENCE: NEORV32 Software library
 *            FreeRTOS-plus-TCP
 ***************************************************************
 */


/* neorv32 HAL*/
#include "axiethernet.h"

#include <neorv32.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "list.h"

/* FreeRTOS+TCP includes. */
#include "FreeRTOS_IP.h"

/* If ipconfigETHERNET_DRIVER_FILTERS_FRAME_TYPES is set to 1, then the Ethernet
 * driver will filter incoming packets and only pass the stack those packets it
 * considers need processing. */
#if ( ipconfigETHERNET_DRIVER_FILTERS_FRAME_TYPES == 0 )
	#define ipCONSIDER_FRAME_FOR_PROCESSING( pucEthernetBuffer )    eProcessBuffer
#else
	#define ipCONSIDER_FRAME_FOR_PROCESSING( pucEthernetBuffer )    eConsiderFrameForProcessing( ( pucEthernetBuffer ) )
#endif

// Network interface Initiailization
BaseType_t xNetworkInterfaceInitialise( void )
{
	BaseType_t xReturn;
	int Status;

	// EMAC initial
	neorv32_uart0_print("Emaclite initial start.\r\n");
	
	Status = EmacLiteInitial(EMAC_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		neorv32_uart0_print("Emaclite initial Failed\r\n");
		xReturn = pdFAIL;
		return xReturn;
	}

	neorv32_uart0_print("Successfully initial Emaclite\r\n");
	xReturn = pdPASS;

	return xReturn;
}

// Send Ethernet frame
BaseType_t xNetworkInterfaceOutput( NetworkBufferDescriptor_t * const pxNetworkBuffer,
									BaseType_t xReleaseAfterSend )
{
	
	XEmacLite_Send(&EmacLiteInstance, (u8 *)pxNetworkBuffer->pucEthernetBuffer, pxNetworkBuffer->xDataLength);

	/* Call the standard trace macro to log the send event. */
	iptraceNETWORK_INTERFACE_TRANSMIT();

	if( xReleaseAfterSend != pdFALSE )
	{

		vReleaseNetworkBufferAndDescriptor( pxNetworkBuffer );
	}

	return pdTRUE;
}

	#define BUFFER_SIZE ( ipTOTAL_ETHERNET_FRAME_SIZE + ipBUFFER_PADDING )
	#define BUFFER_SIZE_ROUNDED_UP ( ( BUFFER_SIZE + 7 ) & ~0x07UL )
	static uint8_t ucBuffers[ ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS ][ BUFFER_SIZE_ROUNDED_UP ];


/* Next provide the vNetworkInterfaceAllocateRAMToBuffers() function, which
simply fills in the pucEthernetBuffer member of each descriptor. */
void vNetworkInterfaceAllocateRAMToBuffers( NetworkBufferDescriptor_t pxNetworkBuffers[ ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS ] )
{
	BaseType_t x;

	for( x = 0; x < ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS; x++ )
	{
		/* pucEthernetBuffer is set to point ipBUFFER_PADDING bytes in from the
		beginning of the allocated buffer. */
		pxNetworkBuffers[ x ].pucEthernetBuffer = &( ucBuffers[ x ][ ipBUFFER_PADDING ] );

		/* The following line is also required, but will not be required in
		future versions. */
		*( ( uint32_t * ) &ucBuffers[ x ][ 0 ] ) = ( uint32_t ) &( pxNetworkBuffers[ x ] );
	}
}

// Get the PHY device status
BaseType_t xGetPhyLinkStatus( void )
{
	// EmacLitePhyDetect(XEmacLite *InstancePtr);
	return pdFALSE;
}
