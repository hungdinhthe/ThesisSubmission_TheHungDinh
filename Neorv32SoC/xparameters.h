 /** 
 **************************************************************
 * @file thesis/Neorv32SoC/xparameters.h
 * @author The Hung Dinh - 46787185
 * @date 21102022
 * @brief hardware design module assigned configuration
 * REFERENCE: NEORV32SoC block design
 ***************************************************************
 */

#ifndef XPARAMETERS_H   /* prevent circular inclusions */
#define XPARAMETERS_H   /* by using protection macros */

/* Definitions for bus frequencies */
#define XPAR_CPU_M_AXI_DP_FREQ_HZ 100000000
/******************************************************************/

/* Canonical definitions for bus frequencies */
/******************************************************************/

#define XPAR_CPU_CORE_CLOCK_FREQ_HZ 100000000

/******************************************************************/

 
/* Definitions for sleep timer configuration */
#define XSLEEP_TIMER_IS_DEFAULT_TIMER
 
/******************************************************************/
/* Definitions for driver BRAM */
#define XPAR_XBRAM_NUM_INSTANCES 3U

/* Definitions for peripheral AXI_BRAM_CTRL_0 */
#define XPAR_AXI_BRAM_CTRL_0_DEVICE_ID 0U
#define XPAR_AXI_BRAM_CTRL_0_DATA_WIDTH 32U
#define XPAR_AXI_BRAM_CTRL_0_ECC 0U
#define XPAR_AXI_BRAM_CTRL_0_FAULT_INJECT 0U
#define XPAR_AXI_BRAM_CTRL_0_CE_FAILING_REGISTERS 0U
#define XPAR_AXI_BRAM_CTRL_0_UE_FAILING_REGISTERS 0U
#define XPAR_AXI_BRAM_CTRL_0_ECC_STATUS_REGISTERS 0U
#define XPAR_AXI_BRAM_CTRL_0_CE_COUNTER_WIDTH 0U
#define XPAR_AXI_BRAM_CTRL_0_ECC_ONOFF_REGISTER 0U
#define XPAR_AXI_BRAM_CTRL_0_ECC_ONOFF_RESET_VALUE 0U
#define XPAR_AXI_BRAM_CTRL_0_WRITE_ACCESS 0U
#define XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR 0x80000000U
#define XPAR_AXI_BRAM_CTRL_0_S_AXI_HIGHADDR 0x8003FFFFU
#define XPAR_AXI_BRAM_CTRL_0_S_AXI_CTRL_BASEADDR 0xFFFFFFFFU  
#define XPAR_AXI_BRAM_CTRL_0_S_AXI_CTRL_HIGHADDR 0xFFFFFFFFU  


/******************************************************************/

/* Canonical definitions for peripheral AXI_BRAM_CTRL_0 */
#define XPAR_BRAM_0_DEVICE_ID 0U
#define XPAR_BRAM_0_DATA_WIDTH 32U
#define XPAR_BRAM_0_ECC 0U
#define XPAR_BRAM_0_FAULT_INJECT 0U
#define XPAR_BRAM_0_CE_FAILING_REGISTERS 0U
#define XPAR_BRAM_0_UE_FAILING_REGISTERS 0U
#define XPAR_BRAM_0_ECC_STATUS_REGISTERS 0U
#define XPAR_BRAM_0_CE_COUNTER_WIDTH 0U
#define XPAR_BRAM_0_ECC_ONOFF_REGISTER 0U
#define XPAR_BRAM_0_ECC_ONOFF_RESET_VALUE 0U
#define XPAR_BRAM_0_WRITE_ACCESS 0U
#define XPAR_BRAM_0_BASEADDR 0x80000000U
#define XPAR_BRAM_0_HIGHADDR 0x8003FFFFU
#define XPAR_BRAM_0_CTRL_BASEADDR 0xFFFFFFFFU  
#define XPAR_BRAM_0_CTRL_HIGHADDR 0xFFFFFFFEU  

/******************************************************************/

/* Definitions for driver EMACLITE */
#define XPAR_XEMACLITE_NUM_INSTANCES 1

/* Definitions for peripheral AXI_ETHERNETLITE_0 */
#define XPAR_AXI_ETHERNETLITE_0_DEVICE_ID 0
#define XPAR_AXI_ETHERNETLITE_0_BASEADDR 0x40E00000
#define XPAR_AXI_ETHERNETLITE_0_HIGHADDR 0x40E0FFFF
#define XPAR_AXI_ETHERNETLITE_0_TX_PING_PONG 1
#define XPAR_AXI_ETHERNETLITE_0_RX_PING_PONG 1
#define XPAR_AXI_ETHERNETLITE_0_INCLUDE_MDIO 1
#define XPAR_AXI_ETHERNETLITE_0_INCLUDE_INTERNAL_LOOPBACK 1


/******************************************************************/

/* Canonical definitions for peripheral AXI_ETHERNETLITE_0 */
#define XPAR_EMACLITE_0_DEVICE_ID 0
#define XPAR_EMACLITE_0_BASEADDR 0x40E00000
#define XPAR_EMACLITE_0_HIGHADDR 0x40E0FFFF
#define XPAR_EMACLITE_0_TX_PING_PONG 1
#define XPAR_EMACLITE_0_RX_PING_PONG 1
#define XPAR_EMACLITE_0_INCLUDE_MDIO 1
#define XPAR_EMACLITE_0_INCLUDE_INTERNAL_LOOPBACK 1


/******************************************************************/

#define XPAR_INTC_MAX_NUM_INTR_INPUTS 2
#define XPAR_XINTC_HAS_IPR 1
#define XPAR_XINTC_HAS_SIE 1
#define XPAR_XINTC_HAS_CIE 1
#define XPAR_XINTC_HAS_IVR 1
/* Definitions for driver INTC */
#define XPAR_XINTC_NUM_INSTANCES 1

/* Definitions for peripheral MICROBLAZE_0_AXI_INTC */
#define XPAR_MICROBLAZE_0_AXI_INTC_DEVICE_ID 0
#define XPAR_MICROBLAZE_0_AXI_INTC_BASEADDR 0x41200000
#define XPAR_MICROBLAZE_0_AXI_INTC_HIGHADDR 0x4120FFFF
#define XPAR_MICROBLAZE_0_AXI_INTC_KIND_OF_INTR 0xFFFFFFFF
#define XPAR_MICROBLAZE_0_AXI_INTC_HAS_FAST 1
#define XPAR_MICROBLAZE_0_AXI_INTC_IVAR_RESET_VALUE 0x0000000000000010
#define XPAR_MICROBLAZE_0_AXI_INTC_NUM_INTR_INPUTS 2
#define XPAR_MICROBLAZE_0_AXI_INTC_NUM_SW_INTR 0
#define XPAR_MICROBLAZE_0_AXI_INTC_ADDR_WIDTH 32


/******************************************************************/

#define XPAR_INTC_SINGLE_BASEADDR 0x41200000
#define XPAR_INTC_SINGLE_HIGHADDR 0x4120FFFF
#define XPAR_INTC_SINGLE_DEVICE_ID 0
#define XPAR_MICROBLAZE_0_AXI_INTC_TYPE 0U
#define XPAR_AXI_ETHERNETLITE_0_IP2INTC_IRPT_MASK 0X000002U
#define XPAR_MICROBLAZE_0_AXI_INTC_AXI_ETHERNETLITE_0_IP2INTC_IRPT_INTR 1U

/******************************************************************/

/* Canonical definitions for peripheral MICROBLAZE_0_AXI_INTC */
#define XPAR_INTC_0_DEVICE_ID 0
#define XPAR_INTC_0_BASEADDR 0x41200000U
#define XPAR_INTC_0_HIGHADDR 0x4120FFFFU
#define XPAR_INTC_0_KIND_OF_INTR 0xFFFFFFFFU
#define XPAR_INTC_0_HAS_FAST 1U
#define XPAR_INTC_0_IVAR_RESET_VALUE 0x0000000000000010U
#define XPAR_INTC_0_NUM_INTR_INPUTS 2U
#define XPAR_INTC_0_NUM_SW_INTR 0U
#define XPAR_INTC_0_ADDR_WIDTH 32U
#define XPAR_INTC_0_INTC_TYPE 0U

#define XPAR_INTC_0_EMACLITE_0_VEC_ID 1U
#define XPAR_INTC_0_ACK_BEFORE 0 
/******************************************************************/

#endif  /* end of protection macro */
