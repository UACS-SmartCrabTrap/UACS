<<<<<<< HEAD
function [ ZerosOut,TimeOut,unBaised ] = IF_Zero_Crossings( waveIn, TimeIn )
=======
function [ ZerosOut,TimeOut ] = IF_Zero_Crossings( waveIn, TimeIn )
>>>>>>> b5f3578fcb7ae52303ff9f73a1f8f7fb84b6bf0e
%Input: Csv vectors defining singals 
%Output: Indicies of zero crossings, and times at which they occured 

waveMean = mean(waveIn);
unBaised = waveIn-waveMean;
%Find DC of signal and unbais the wave 

%Find the original level of the signal
if unBaised(1) > 0
   
    Level = 1;
else
    Level = 0;
end


%To find zero crossing find when wave transitions from 0->1
%fill array with those transition points
%will pick the positive point
j = 1;
for i = 2:length(unBaised)
<<<<<<< HEAD
    if (Level == 0 && (unBaised(i) >= 0.00001))
        ZerosOut(j) = i;
        Level = 1;
        j = j+1;
    elseif (Level == 1 && (unBaised(i) <= -0.00001))
=======
    if (Level == 0 && (unBaised(i) >= 0.00095))
        ZerosOut(j) = i;
        Level = 1;
        j = j+1;
    elseif (Level == 1 && (unBaised(i) <= -0.0095))
>>>>>>> b5f3578fcb7ae52303ff9f73a1f8f7fb84b6bf0e
        ZerosOut(j) = i-1;
        Level = 0;
        j = j+1;
    end
end

%Indicies of zero crossings for Y-axis array same as X-axis array
%Puts correct times values into array for coordinating arrays 

j = 1; 
for i = 1:length(ZerosOut)
    TimeOut(j) = TimeIn(ZerosOut(i)); 
    j = j+1; 
end


end

