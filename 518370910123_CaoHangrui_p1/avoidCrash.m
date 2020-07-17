function car=avoidCrash(car,width)
Scar=[];
S=0;
Left=0;
Leftcar=[];
for i=1:carin
    if car(i).cross==3
        if mod(car(i).turning,3)==1
            if car(i).direction==10
            S=S+1;
            Scar(S)=i;
            end
        elseif mod(car(i).turning,3)==0
            if car(i).turning==3
            Left=Left+1;
            Leftcar(Left)=i;
            end
        end
    end
end
if ~isempty(Scar)&&~isempty(Leftcar)>0
    for i=1:length(Leftcar)
        for j=1:length(Scar)
           
        end
end
