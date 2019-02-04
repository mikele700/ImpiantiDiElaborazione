function [ y ] = reliability_es4( r,n )
%RELIABILITY_ES4 
%  

    y=0;
    for i=0:(n-3)
   
     y=y+nchoosek(n,i)*(r^(n-i))*(1-r)^i;
    
    end



end

