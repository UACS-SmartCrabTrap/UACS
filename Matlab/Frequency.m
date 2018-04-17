function AvgFreq = Frequency(Time, ZeroCrossings)

for i = 1:length(ZeroCrossings)-1
    HalfPeriod = Time(ZeroCrossings(i+1)) - Time(ZeroCrossings(i));
    Freq(i) = 1/HalfPeriod;
end

AvgFreq = Freq;