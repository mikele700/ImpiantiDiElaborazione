function [ n ] = samplesize( x, s )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
n=((100*1.96*s)/(0.5*x))^2

end

