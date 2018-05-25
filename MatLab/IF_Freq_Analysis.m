%========================================
% IF_Signal_Freq_Analysis
% Module reads in .csv file exported from Agilent Waveforms software
% Author: Ivonne Fajardo
% Last Edited: 5/10/2018 
%========================================

%Read in .csv file from Agilent Discovery 2
%Ignore first 11 lines: parameter information not data
data = csvread('SSpsocsharedpower_gain_lpfout.csv', 11, 0); 

%Determine size of incoming data file 
%r = number of rows, c = number of columns 
[r,c] = size(data);

%     Data column 1: time measurements 
%     Data column 2: Channel 1 data
%     Data column 3: Channel 2 data 

time = data(:,1);
channel1 = data(:,2);
channel2 = data(:,3);

%============== Calculations ==================================================================================

%     IF_Zero_Crossings: Find zero crossings after DC bias removed
%     In:   Signal data in Volts, time data in s
%     Out:  Voltages interpreted as '0' , times of zero crossings, channel voltages 0V biased 
%     function [ ZerosOut,TimeOut, unBaisedV ] = IF_Zero_Crossings( waveIn, TimeIn )


[chan1_zeros, chan1_zeroTime, chan1_notBiased] = IF_Zero_Crossings(channel1, time);
[chan2_zeros, chan2_zeroTime, chan2_notBiased] = IF_Zero_Crossings(channel2, time);

%     IF_FrequencyCalcs: Use zero crossing data to find frequencies 
%     In:   Time (s) of signal zero crossings from IF_Zero_Crossings(waveIn, TimeIn)
%     Out:  The frequencies in the signal, and approx. time of frequency change 
%     function [ FrequencyOut, timeChange ] = IF_FrequencyCalcs( TimeIn )


[chan1_frequencies, chan1_freqTime] = IF_FrequencyCalcs(chan1_zeroTime); 
[chan2_frequencies, chan2_freqTime] = IF_FrequencyCalcs(chan2_zeroTime);


%     adjacentAverage: Take average of adjacent frequencies 
%                       if very close together in magnitude or time  
%     In:   Frequencies of signal and time changes from IF_FrequencyCalcs( TimeIn )
%     Out:  Average of frequencies in the signal, and approx. time of frequency change 
%     function [ avgFreq, avgTime ] = adjacentAverage( inFreq, inTime )


[chan1_freqAvg , chan1_timeAvg] = adjacentAverage(chan1_frequencies,  chan1_freqTime);
[chan2_freqAvg , chan2_timeAvg] = adjacentAverage(chan2_frequencies,  chan2_freqTime);


%     freqChange: Filter out frequency changes inside a hysterisis band 
%     In:   Average frequencies of signal and time changes from adjacentAverage( inFreq, inTime )
%     Out:  Filtered average frequencies and time of frequency change   
%     function [ changeFreq , changeTime ] = freqChange( freqsIn, timesIn )


[ chan1_filterAvg, chan1_timeChange ] = freqChange( chan1_freqAvg , chan1_timeAvg );
[ chan2_filterAvg, chan2_timeChange ] = freqChange(chan2_freqAvg , chan2_timeAvg );

%Channel 1 Discrete Time Fourier Transform
[z1,w1] = DTFT(channel1,length(channel1));

%Channel 2 Discrete Time Fourier Transform
[z2,w2] = DTFT(chan2_notBiased,length(chan2_notBiased));


%=================== Plots =======================================================================

% Figure 1
figure('Name','Channel 1(V) v. Time(s)') 
plot(time, channel1)

% Figure 2
figure('Name','Channel 2(V) v. Time(s)') 
plot(time, channel2)

% Figure 3
figure('Name', 'Channel 1 DFT')
plot((w1*5000000)/(2*pi),log10(abs(z1))); 
xlabel('Frequencies Hz');
ylabel('Magnitude')

% Figure 4
figure('Name', 'Channel 2 DFT')
plot((w2*5000000)/(2*pi),log10(abs(z2))); 
xlabel('Frequencies Hz');
ylabel('Magnitude')





