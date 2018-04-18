%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% File: FindZeroCrossings.m
% Author: Julian Salazar
% Date: 4/11/18
% Edits:
%     4/17 - Added comment and function description (Julian Salazar)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% function: FindZeroCrossings()
% parameters: A (The desired array we want to analyze)
% returns: ZC (An array of indices telling where the given array A crosses the
%              the x-axis)
% description: The following function takes in an array A and checks for state
%              changes as it moves from being above the x-axis to being below,
%              and vice-versa. It stores the index where the array changed
%              states and stores it in array ZC
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function ZC = FindZeroCrossings(A)

	%The following conditionals find out whether the input array starts above
	% the x-axis or below it.
	%I begin at index 1000 because the input array used in my application would
	% be one made by a moving average filter. I wait to start finding zero
	% crossing at index 1000 to make sure the ring buffer in the Moving Average
	% Filter was fully propagated.
	if A(1000) > 0
		Level = 1; % 1 Indicates value in A(i) is above x-axis
	else
		Level = 0; % 0 Indicates value in A(i) is below x-axis
	end
    
	j = 1; %iterator for ZC array as it will likely be different size than A
	
	for i = 1001:length(A)
	
		%Conditionals check values in A(i) for transitions above and below the
		% x-axis. If there is a transition, it is stored in array ZC
		if (Level == 0) && (A(i) >= 0) %Below to above transition
			ZC(j) = i;
			Level = 1;
			j = j+1;
		elseif (Level == 1) && (A(i) <= 0) %Above to below transition
			ZC(j) = i;
			Level = 0;
			j = j+1;
		end
		
	end

end %end FindZeroCrossings()