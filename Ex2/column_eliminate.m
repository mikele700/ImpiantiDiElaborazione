%COLUMN ELIMINATE
%
%Script per eliminare le colonne a varianza nulla
%

A=xlsread("EsercizioPCA_CLustering_versStudenti.xlsx");
V=var(A);
i=find(~V);
A(:,i)=[];
xlswrite("EsercizioPCA_CLustering_versStudenti_new.xlsx",A);
