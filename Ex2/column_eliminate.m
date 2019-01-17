%COLUMN ELIMINATE
%
%Script per eliminare le colonne a varianza nulla
%

[num,txt,raw]=xlsread("EsercizioPCA_CLustering_versStudenti.xlsx");
V=var(num);
i=find(~V);
raw(:,i)=[];
xlswrite("EsercizioPCA_CLustering_versStudenti_new.xlsx",raw);
