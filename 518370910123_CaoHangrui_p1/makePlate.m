function Book=makePlate(str,num)
Book=strings([1,num]);
for i=1:num
    tempplate=production(str,0);
    if contains(Book,tempplate)
        tempplate=production(str,0);
    end
    Book(i)=tempplate;
end
end


function rst=production(str,digit)
if digit==5
    rst=' ';
elseif digit<5&&digit>0
    digit=digit+1;   
    a=str(randperm(length(str),1));
    for i=1:length(str)
        if str(i)==a
            str(i)='';
            break;
        end
    end
    rev=production(str,digit);
    rst=[rev,a];   
elseif digit==0
    digit=digit+1;
    FirstLetter=str(randperm(length(str),1));
    while isletter(FirstLetter)==0
        FirstLetter=str(randperm(length(str),1));
        
    end
    a=str(randperm(length(str),1));
    for i=1:length(str)
        if str(i)==a
            str(i)='';
            break;
        end
    end
    rev=production(str,digit);
    rst=[FirstLetter,'',rev,a];
end
end
