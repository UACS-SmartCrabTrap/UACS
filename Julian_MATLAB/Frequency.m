%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% File: Frequency.m
% Author: Julian Salazar
% Date: 4/11/18
% Edits:
%     4/17 - Added comment and function description (Julian Salazar)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% function: Frequency()
% parameters: Time (An array of times)
%			  ZeroCrossings (An array of indices telling at what times a given
%                            signal crosses the x-axis)
% returns: AvgFreq (A scalar value giving an approximation of the frequency of
%                   a signal)
% description: The Frequency function is used in conjunction with the
%              ZeroCrossings function. The Time parameter for this function
%              should be the corresponding time array given with the signal of
%              interest and necessarily should be the same length. So, the
%              ZeroCrossings indices retrieved from the signal give the times
%              at which our signal crosses the x-axis. Every crossing with the
%              x-axis should indicate a half cycle, or half period. The
%              function accumulates each half period value by finding the
%              difference in time between each zero crossing. The half-periods
%              are then multiplied by 2 to get the full period and then stored
%              into an array as the corresponding frequency. The array of
%              frequencies is averaged and then returned as the output.
% Note: The function doesn't wait for a full cycle of the signal to occur to
%       estimate the frequency. It estimates the frequency by assuming the
%       signal spends an equal amount of time above and below the x-axis. Even
%       if this were not the case, averaging out the values should give a close
%       estimate of the actual frequency.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function AvgFreq = Frequency(Time, ZeroCrossings)

	for i = 1:length(ZeroCrossings)-1
		HalfPeriod = Time(ZeroCrossings(i+1)) - Time(ZeroCrossings(i));
		Freq(i) = 1/(HalfPeriod*2);
	end

	AvgFreq = mean(Freq);
end %end Frequency()