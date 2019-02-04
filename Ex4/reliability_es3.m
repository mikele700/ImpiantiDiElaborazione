function [ r ] = reliability_es3( l,t )
%RELIABILITY
% 
 
    r=0;
    p=[0 0 0 0 2/70 16/56 20/28 1 1];
    R=exp(-1*l.*t);
  
    for i=0:8
        r=r+p(i+1)*nchoosek(8,i).*R.^i.*(1-R).^(8-i);
    end

end





