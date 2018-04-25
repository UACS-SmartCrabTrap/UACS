function [ H,W ] = DTFT( h,N )
%UNTITLED13 Summary of this function goes here
%   Detailed explanation goes here

N = fix(N);
L = length(h); 
h = h(:);

if(N<L)
    error('Data Samples cannot exceed freq samples');
end

W = (2*pi/N)*[0:(N-1)]';
mid = ceil(N/2) + 1;
W(mid:N) = W(mid:N) - 2*pi;

W = fftshift(W);
H = (fftshift(fft(h,N))); 



end

