 /** 
 **************************************************************
 * @file thesis/Neorv32SoC/main.c
 * @author The Hung Dinh - 46787185
 * @date 21102022
 * @brief NEORV32 embedded system Interrupt and Ethernet MAC setup 
 * 			and testing.
 * REFERENCE: NEORV32 Software library
 * 			  Xilinx Emaclite Standalone Driver
 ***************************************************************
 */

#include "axiethernet.h"

#include <neorv32.h>

int main()
{
	int Status;

  	// initialize the neorv32 runtime environment - manage all CPU interrrupts
	neorv32_rte_setup();

	// UART setup for console
	neorv32_uart0_setup(BAUD_RATE, PARITY_NONE, FLOW_CONTROL_NONE);
	neorv32_uart0_print("Ethernet MAC Initialize.\r\n");

	neorv32_uart0_print("Emaclite PHY loopback payload test.\r\n");
	
  	// Ethernet MAC initial and testing
	Status = EmacLiteInitial(EMAC_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		neorv32_uart0_print("Emaclite initial Failed.\r\n");
		return XST_FAILURE;
	}

	neorv32_uart0_print("Successfully initial Emaclite with payload test from 0 to 1500.\r\n");

	//FreeRTOS
	//In developing
}
