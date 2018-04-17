function ZC = FindZeroCrossings(A)


if A(1000) > 0
    Level = 1;
else
    Level = 0;
end
    
j = 1;
for i = 1001:length(A)
    if (Level == 0) && (A(i) >= 0)
        ZC(j) = i;
        Level = 1;
        j = j+1;
    elseif (Level == 1) && (A(i) <= 0)
        ZC(j) = i;
        Level = 0;
        j = j+1;
    end
end

end