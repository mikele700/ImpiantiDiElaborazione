function [ rel, t ] = emprel( interarrivals )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
[p,t] = cdfcalc(interarrivals);
ttf = p(2:size(p,1));
rel = 1-ttf;
plot(t, rel, '-+');
xlabel('time [s]');
ylabel('p');

end

