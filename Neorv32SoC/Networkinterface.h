 /** 
 **************************************************************
 * @file thesis/Neorv32SoC/NetworkInterface.h
 * @author The Hung Dinh - 46787185
 * @date 21102022
 * @brief MAC connect to FreeRTOS TCP/IP
 * REFERENCE: NEORV32 Software library
 *            FreeRTOS-plus-TCP
 ***************************************************************
 */

#ifndef NETWORKINTERFACE_H		/* prevent circular inclusions */
#define NETWORKINTERFACE_H		/* by using protection macros */

/* neorv32 HAL*/
#include "axiethernet.h"

#include <neorv32.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "list.h"

/* FreeRTOS+TCP includes. */
#include "FreeRTOS_IP.h"

extern NetworkBufferDescriptor_t pxNetworkBuffers[ ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS ];

BaseType_t xNetworkInterfaceInitialise( void );
BaseType_t xNetworkInterfaceOutput( NetworkBufferDescriptor_t * const pxNetworkBuffer,
                                    BaseType_t xReleaseAfterSend );
void vNetworkInterfaceAllocateRAMToBuffers( NetworkBufferDescriptor_t pxNetworkBuffers[ ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS ] );
BaseType_t xGetPhyLinkStatus( void );

#endif