function [ avgFreq, avgTime ] = adjacentAverage( inFreq, inTime )
%takes a weighted average of a series of frequenies 

i = 1; 
j = 1;
k = 1; 

while(i < length(inFreq) - 1)
     
    runningSum = 0;
    %wait until the different is greater that 0.01s
    % && (abs(inFreq(i) - inFreq(i+j) < 200)
    while((inTime(i+j) - inTime(i) < 0) && (i+j < length(inFreq)))
        runningSum = runningSum + inFreq(i+j); 
        j = j+1;  
    end
     
    
    avgFreq(k) = runningSum / j;
    avgTime(k) = inTime(i+j); 
    k = k +1; 
    
    %DEBUGGING
    %i
    %j
    %inFreq(i+j)
    %inFreq(i)
    
    %reinitialize variables to keep working
    i = i+j+1;
    j = 0; 
    
    
    
end


end

