%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% File: TxBatteryLife.m
% Author: Julian Salazar
% Date: 05/07/18
% Purpose: The battery life of the tranmission circuit is dependent on how
%   long it's on every day. With constants such as the total power
%   consumption of the circuit while it is activated, we can calculate how
%   long the battery will last.
% Edits:
%   
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function BatteryLife = TxBatteryLife(OnTime) %OnTime in seconds (0-86400)

c = 675; %Battery capacity in mAh
p = 2.5; %Power consumed from active transmitter in watts
v = 9.9; %Voltage supply to the transmitter circuitry in volts
i_s = 7; %PSoC sleep current in mA
i = (p / v) * 1000; %Current draw from active transmitter in mA
s = 86400; %Seconds in a day

%Equation gives average current drawn from the circuit over a day
i_day = ( i * (OnTime/s) ) + ( i_s * ((s-OnTime)/s) );

%Gives battery life in days
BatteryLife = (c / i_day) / 24;