% Noise after each step
% Raw Data in Pool
subplot(2,1,1)
plot(Times13,outhfraw)
title('HF Out of Ocean Noise Raw')
xlabel('Time (s)') % x-axis label
ylabel('Voltage (V)') % y-axis label

% % No Data after Gain 1
subplot(2,1,2)
plot(Times13,outhfgain)
title('HF Out of Ocean Noise after Gain')
xlabel('Time (s)') % x-axis label
ylabel('Voltage (V)') % y-axis label

% 
% % No Data after Gain 2
% plot(noiseGainTimes,noiseGain2)
% title('Gain 2 Noise')
% xlabel('Time (s)') % x-axis label
% ylabel('Voltage (V)') % y-axis label
% 
% % No Data after Filter 1
% plot(noisefiltertimes,lowpassnoise)
% title('Low Pass Filter Noise')
% xlabel('Time (s)') % x-axis label
% ylabel('Voltage (V)') % y-axis label
% 
% % No Data after Filter 2
% plot(noisefiltertimes,highpassnoise)
% title('High Pass Filter Noise')
% xlabel('Time (s)') % x-axis label
% ylabel('Voltage (V)') % y-axis label
% 
% % No Data PWM 
% plot(noisepsocTimes,noisepwm)
% title('PWM Recon Noise')
% xlabel('Time (s)') % x-axis label
% ylabel('Voltage (V)') % y-axis label
% 
% % No Data DemodOut
% plot(noisepsocTimes,noisedemod)
% title('Demod Noise')
% xlabel('Time (s)') % x-axis label
% ylabel('Voltage (V)') % y-axis label

% 1st Round of Data
% plot(raw1_5Time,raw1_5)
% title('Raw Data at 1.5 ft')
% xlabel('Time (s)') % x-axis label
% ylabel('Voltage (V)') % y-axis label
% 
% 
% % 2nd Round of Data
% plot(Times,gain11ft)
% title('1st Gain Stage at 1 ft')
% xlabel('Time (s)') % x-axis label
% ylabel('Voltage (V)') % y-axis label
% 
% plot(Times,gain21ft)
% title('2nd Gain Stage at 1 ft')
% xlabel('Time (s)') % x-axis label
% ylabel('Voltage (V)') % y-axis label
% 
% 
% % 3rd Round of Data
% plot(Times,lowpass1ft)
% title('1st Filter: Low Pass Filter at 1 ft')
% xlabel('Time (s)') % x-axis label
% ylabel('Voltage (V)') % y-axis label
% 
% plot(Times,highpass1ft)
% title('2nd Filter: High Pass Filter at 1 ft')
% xlabel('Time (s)') % x-axis label
% ylabel('Voltage (V)') % y-axis label
% % 
% 
% % 4th Round of Data
% plot(Times,comp1ft)
% title('Reconstructed Signal 1 ft')
% xlabel('Time (s)') % x-axis label
% ylabel('Voltage (V)') % y-axis label
% % 
% plot(Times,demod1ft)
% title('Demod Out 1 ft')
% xlabel('Time (s)') % x-axis label
% ylabel('Voltage (V)') % y-axis label