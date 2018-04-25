function [ FrequencyOut, timeChange ] = IF_FrequencyCalcs( TimeIn )
%Input: Vector of time of all zero crossings
%Output: Frequency of signal and time at which it changed 


%check frequency of wave every 1/2 cycle 
frequencyOld = 0; 
j = 1; 
for i = 1:2:length(TimeIn)- 2
    period = TimeIn(i+2) - TimeIn(i);
    frequencyNew = 1 / period;
    
    %record any changes in frequency 
    %added hysterisis band of 1kHZ
    if(abs(frequencyNew - frequencyOld) > 1 && frequencyNew > 30)
        frequencyOld = frequencyNew;
        FrequencyOut(j) = frequencyNew;
        timeChange(j) = TimeIn(i);
        j = j+1;
    end
    
end


end

