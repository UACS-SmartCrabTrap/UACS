%----------------------------------
% FSK Correlators Delay Math Model
%           Low F (100Hz)
%----------------------------------

fl = 140;
fh = 175;

A = 2 * pi() * fh;
B = 2 * pi() * fl;

d = linspace((1E-9), (50E-3),200);

X = A .* d;
Y = B .* d;

Diff = cos(Y) - cos(X);
DiffPrime = A*sin(X) - B*sin(Y);

figure(1)
plot(d, Diff)
hold on
plot(d, DiffPrime);
title('Correlation Difference and Difference Derivative v. Delay Time');
xlabel('Delay (s)');
ylabel('Correlation Difference (Hz)');
legend('Diff', 'DiffPrime');

%to find delay times, find maximum, or smallest from group of maximums 
%F = max frequency Value 
%I = index of max value
%therefore
%d(I) will give Delay Time to cause max difference 
[F, I] = max(Diff); 

%WILL ONLY GIVE 1 VALUE
%WILL ALSO CHECK DERIVATIVE MAX AND MINS
%MATLAB IS 1 INDEXED, ARGHGHGHG

%first check values, when the diff > 1
[r,c] = size(Diff);
maxDim = 11; 
maxThresh = 1.5; 
%until we have 10 data points or less and we don't go over a gain of 2
while(maxDim > 10 && maxThresh <= 2)
    over1 = linspace(0,0,2); 
    over1Delay = linspace(0,0,2); 
    indicies = linspace(0,0,2); 
    j = 1; 
    for i = 1 : 1 : c
        if(Diff(i) > maxThresh)
          over1(j) = Diff(i);  
          over1Delay(j) = d(i);
          indicies(j) = i; 
          j = j+1;     

        end   

    end
    [rtrash, maxDim] = size(over1Delay); 
    maxThresh = maxThresh + 0.2; 
    %over1
end

%now find the spread of the max diff values
%might not be need, too much optimization 
[smallestMax, iSmall] = min(over1);

[biggestMax, iBig] = max(over1);

over1Delay(iSmall);
over1Delay(iBig);

b = indicies(iSmall);
me = d(b);

%over1 = all of the gains over 1 
%over1Delay = the d values of the gains that are over1



[r,c] = size(DiffPrime);
hysBand = 100; 
diffZeros = linspace(0,0,30); 

j = 1;
for i = 1 : 1 : c
    if((DiffPrime(i) < hysBand) && (DiffPrime(i) > -hysBand))
    
      diffZeros(j) = d(i);
      j = j+1;     
    
    end   
    
end
 


