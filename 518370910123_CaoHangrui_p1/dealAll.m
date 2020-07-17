function Plate=dealAll(Length, array)
Plate=[];
m=nchoosek(array, Length);
for i=1:length(m)
    Plate=[Plate,dealString(Length, m(i,1:end))];
    disp(dealString(Length, m(i,1:end)));
end
end

function char=dealString(N,array)
rst=producePerm(array,length(array),1);
char=strings([1,length(rst)/N]);
for i=1:length(rst)/N
    char(i)=rst(N*i-N+1:N*i);
end
end


function [rst,cnt]=producePerm(array, size, N)
    if N == size
        rst=array;
    else     
        rst='';
        for i = N:size
            temp=array(i);
            array(i)=array(N);
            array(N)=temp;    
            rev=producePerm(array, size, N+1);
            rst=[rev,rst];
            temp=array(i);
            array(i)=array(N);
            array(N)=temp;
        end
    end
    
end   
