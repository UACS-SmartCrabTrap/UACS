%========================================
% IF_Signal_Freq_Analysis
% Module reads in .csv file exported from Agilent Waveforms software
% Author: Ivonne Fajardo
% Last Edited: 4/17/2018 
%========================================

%read the number data only



data = csvread('3_gain1_gain2 (1).csv', 11, 0); 


%r = number of rows, c = number of columns 
[r,c] = size(data);

%column 1 = time, column2 = channel1, column3 = channel3 
time = data(:,1);
channel1 = data(:,2);
channel2 = data(:,3);

figure(3) 
plot(time, channel1)
figure(4) 
plot(time, channel2)

%find zero crossings 
%function [ ZerosOut,TimeOut ] = IF_Zero_Crossings( waveIn, TimeIn )
[chan1_zeros, chan1_zeroTime, chan1_notBiased] = IF_Zero_Crossings(channel1, time);
[chan2_zeros, chan2_zeroTime, chan2_notBiased] = IF_Zero_Crossings(channel2, time);

%Discrete Time Fourier Transform 
[z,w] = DTFT(channel1,length(channel1));
figure(1)
plot((w*5000000)/(2*pi),log10(abs(z))); 
xlabel('Frequencies Hz');
ylabel('Magnitude')

[z,w] = DTFT(chan2_notBiased,length(chan2_notBiased));
figure(2)
plot((w*5000000)/(2*pi),log10(abs(z))); 
xlabel('Frequencies Hz');
ylabel('Magnitude')


%find frequencies 
%function [ FrequencyOut, timeChange ] = IF_FrequencyCalcs( TimeIn )
[chan1_frequencies, chan1_freqTime] = IF_FrequencyCalcs(chan1_zeroTime); 
[chan2_frequencies, chan2_freqTime] = IF_FrequencyCalcs(chan2_zeroTime);



%average out frequencies 
[chan1_freqAvg , chan1_timeAvg] = adjacentAverage(chan1_frequencies,  chan1_freqTime);
[chan2_freqAvg , chan2_timeAvg] = adjacentAverage(chan2_frequencies,  chan2_freqTime);


%find the changes in average frequencies 

[ chan1_avgFreq, chan1_avgTime ] = freqChange( chan1_freqAvg , chan1_timeAvg );
[ chan2_avgFreq, chan2_avgTime ] = freqChange(chan2_freqAvg , chan2_timeAvg );






