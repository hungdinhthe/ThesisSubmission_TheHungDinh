//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2022.1 (win64) Build 3526262 Mon Apr 18 15:48:16 MDT 2022
//Date        : Sun Oct 16 23:28:52 2022
//Host        : MSI running 64-bit major release  (build 9200)
//Command     : generate_target neorv32SoC_wrapper.bd
//Design      : neorv32SoC_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module neorv32SoC_wrapper
   (clk_100MHz,
    eth_ref_clk,
    gpio_o_0,
    mdio_rtl_0_mdc,
    mdio_rtl_0_mdio_io,
    resetn_0,
    rmii_rtl_0_crs_dv,
    rmii_rtl_0_rx_er,
    rmii_rtl_0_rxd,
    rmii_rtl_0_tx_en,
    rmii_rtl_0_txd,
    uart0_rxd_i_0,
    uart0_txd_o_0);
  input clk_100MHz;
  output eth_ref_clk;
  output [7:0]gpio_o_0;
  output mdio_rtl_0_mdc;
  inout mdio_rtl_0_mdio_io;
  input resetn_0;
  input rmii_rtl_0_crs_dv;
  input rmii_rtl_0_rx_er;
  input [1:0]rmii_rtl_0_rxd;
  output rmii_rtl_0_tx_en;
  output [1:0]rmii_rtl_0_txd;
  input uart0_rxd_i_0;
  output uart0_txd_o_0;

  wire clk_100MHz;
  wire eth_ref_clk;
  wire [7:0]gpio_o_0;
  wire mdio_rtl_0_mdc;
  wire mdio_rtl_0_mdio_i;
  wire mdio_rtl_0_mdio_io;
  wire mdio_rtl_0_mdio_o;
  wire mdio_rtl_0_mdio_t;
  wire resetn_0;
  wire rmii_rtl_0_crs_dv;
  wire rmii_rtl_0_rx_er;
  wire [1:0]rmii_rtl_0_rxd;
  wire rmii_rtl_0_tx_en;
  wire [1:0]rmii_rtl_0_txd;
  wire uart0_rxd_i_0;
  wire uart0_txd_o_0;

  IOBUF mdio_rtl_0_mdio_iobuf
       (.I(mdio_rtl_0_mdio_o),
        .IO(mdio_rtl_0_mdio_io),
        .O(mdio_rtl_0_mdio_i),
        .T(mdio_rtl_0_mdio_t));
  neorv32SoC neorv32SoC_i
       (.clk_100MHz(clk_100MHz),
        .eth_ref_clk(eth_ref_clk),
        .gpio_o_0(gpio_o_0),
        .mdio_rtl_0_mdc(mdio_rtl_0_mdc),
        .mdio_rtl_0_mdio_i(mdio_rtl_0_mdio_i),
        .mdio_rtl_0_mdio_o(mdio_rtl_0_mdio_o),
        .mdio_rtl_0_mdio_t(mdio_rtl_0_mdio_t),
        .resetn_0(resetn_0),
        .rmii_rtl_0_crs_dv(rmii_rtl_0_crs_dv),
        .rmii_rtl_0_rx_er(rmii_rtl_0_rx_er),
        .rmii_rtl_0_rxd(rmii_rtl_0_rxd),
        .rmii_rtl_0_tx_en(rmii_rtl_0_tx_en),
        .rmii_rtl_0_txd(rmii_rtl_0_txd),
        .uart0_rxd_i_0(uart0_rxd_i_0),
        .uart0_txd_o_0(uart0_txd_o_0));
endmodule
