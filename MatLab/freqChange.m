function [ changeFreq , changeTime ] = freqChange( freqsIn, timesIn )
%Finds the changes in frequency and records the frequeny and time occured

i = 1;
j = 2;
k = 1;
while( j < length(freqsIn) )
    
    %increments j until the frequencies are not equal
    while((freqsIn(j) - freqsIn(i) < 1) && j < length(freqsIn) )
        j = j + 1; 
    end
    
    %breaks out then frequency at j not equal to frequency at i
    %recording new freq
    
    changeFreq(k) = freqsIn(j);
    changeTime(k) = timesIn(j);
    k = k+1;
    %update indicies to keep checking frequencies
    i = j;
    j = j+1;
    
    
end




end

