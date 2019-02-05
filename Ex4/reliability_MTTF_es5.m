%scrip per calcolare tramite l'MTTF il failure rate e quindi la reliability

MTTF=[ 5000; %processing unit
       2500; %remote terminal
       1000; %ahrs
       1000; %ins
       300;  %doppler
       10000; %bus
       ];
   
lambda=1./MTTF;
Rm=exp(-lambda*1);

Rsys=(1-(1-Rm(1))^2)*((1-(1-Rm(6))^2))^2*(1-(1-Rm(2))^2)*(1-(1-Rm(4)))*(Rm(5)*(1-(1-Rm(3))^3));


%calcolo la coverage
Rsys_noproc =((1-(1-Rm(6))^2))^2*(1-(1-Rm(2))^2)*(1-(1-Rm(4)))*(Rm(5)*(1-(1-Rm(3))^3));
Rproc_mod= 0.99999/Rsys_noproc;
c=(Rproc_mod-Rm(1))/((1-Rm(1))*Rm(1));

 