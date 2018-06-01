# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\SPB_Data\Documents\UACSCode\HighFSKRx.cydsn\HighFSKRx.cyprj
# Date: Fri, 01 Jun 2018 05:43:45 GMT
#set_units -time ns
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {UART_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 313 627} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {Bit_Timer_Clk} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2401 4801} [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {shift_clk} -source [get_pins {ClockBlock/clk_sync}] -edges {1 16001 32001} -nominal_period 666666.66666666663 [list [get_pins {ClockBlock/dclk_glb_2}]]


# Component constraints for C:\SPB_Data\Documents\UACSCode\HighFSKRx.cydsn\TopDesign\TopDesign.cysch
# Project: C:\SPB_Data\Documents\UACSCode\HighFSKRx.cydsn\HighFSKRx.cyprj
# Date: Fri, 01 Jun 2018 05:43:37 GMT
