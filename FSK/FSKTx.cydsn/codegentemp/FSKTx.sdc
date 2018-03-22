# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\sdysart\Documents\UACS\UACS\FSK\FSKTx.cydsn\FSKTx.cyprj
# Date: Thu, 22 Mar 2018 11:14:19 GMT
#set_units -time ns
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {HighF_OneCLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 857 1713} -nominal_period 35666.666666666664 [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {LowF_OneCLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 941 1881} -nominal_period 39208.333333333328 [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {HighF_ZeroCLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 1047 2093} -nominal_period 43583.333333333328 [list [get_pins {ClockBlock/dclk_glb_2}]]
create_generated_clock -name {LowF_ZeroCLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 1107 2215} [list [get_pins {ClockBlock/dclk_glb_3}]]


# Component constraints for C:\Users\sdysart\Documents\UACS\UACS\FSK\FSKTx.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\sdysart\Documents\UACS\UACS\FSK\FSKTx.cydsn\FSKTx.cyprj
# Date: Thu, 22 Mar 2018 11:14:12 GMT
