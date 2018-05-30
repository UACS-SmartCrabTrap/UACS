%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% File: RxBatteryLife.m
% Author: Julian Salazar
% Date: 05/07/18
% Purpose: To date, the battery life of the receiver module is unknown due
%   to a few variables, most important of which is how long it will be on
%   throughout a day. This file will serve as a function to determine
%   battery life depending on these variables.
% Edits:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function BatteryLife = RxBatteryLife(OnTime) %OnTime in seconds (0-86400)

c = 1350; %Battery capacity in mAh
v = 5; %Voltage supplied from the battery
i = 22; %Current draw from the receiver module in mA
% i = 22.5; %Current draw from the receiver module with an LCD screen in mA
% v = 3.3 %Voltage supplied from the battery
% i = 17.5 %Current draw from the receiver module in mA
i_s = 1.5; %Sleep current drawn from circuit when not receiving data
s = 86400; %Seconds in a day

%Equation gives average current drawn from the circuit over a day
i_day = ( i * (OnTime/s) ) + ( i_s * ((s-OnTime)/s) );

%Gives battery life in days
BatteryLife = (c / i_day) / 24;