%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% File: MovingAverage.m
% Author: Julian Salazar
% Date: 4/11/18
% Edits:
%     4/17 - Added comment and function description (Julian Salazar)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% function: MovingAverage()
% parameters: D (An array the user would like the filter applied two)
%             FiltVal (Dictates the size of the ring buffer used. Larger
%                      FiltVals give 'smoother' wave, but typically reduces
%                      amplitude)
% returns: F (The array D after the filter is applied. Same length as 'D')
% description: Implements a moving average filter given some array (D). The
%     code makes use of a ring buffer. The ring buffer is propagated with array
%     values and will give the average value held in the buffer and store that
%     average value to a new array (F)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function F = MovingAverage(D, FiltVal)
	
    sum = 0;
    meanOfD = mean(D);
	j = 1; %iterator for the ring buffer
	
	%Initializes ring buffer with the mean value of the input array
    for i = 1:FiltVal
        RING(i) = meanOfD;
    end
    
    for i = 1:length(D) %i iterates along the arrays D and F
	
	    %The following lines simply store the value held in RING(j) to a
		% variable and replace it with the next value in array D. A running sum
		% adds the new ring buffer value and subtracts the old one to give a
		% cummulative sum of values held in the buffer. By dividing the ring
		% buffer size, we get the mean value of the values held in the buffer
		% and store them in the return array, F.
        oldValue = RING(j);
        RING(j) = D(i);
        sum = sum + RING(j) - oldValue;
        F(i) = sum/FiltVal;
		
		%Resets ring buffer index back to 1 once we exceed its desired size
		j = j + 1;
        if j > FiltVal
            j = 1;
        end
    end

end %end MovingAverage()