function F = MovingAverage(D, FiltVal)
    
    sum = 0;
    meanOfD = mean(D);
    oldValue = meanOfD;
    for i = 1:FiltVal
        RING(i) = meanOfD;
    end
    j = 1;
    
    for i = 1:length(D)
        oldValue = RING(j);
        RING(j) = D(i);
        sum = sum + RING(j) - oldValue;
        F(i) = sum/FiltVal;
        j = j + 1;
        
        if j > FiltVal
            j = 1;
        end
    end

end