function car=initializeCrosscar(car,Crosscar,carin,Passcar)
CLabel=zeros(1,Crosscar+Passcar);
NormalV=2;
num=0;
for i=1:carin
    if car(i).cross==3||car(i).cross==4
        num=num+1;
        CLabel(num)=i;
        switch mod(car(i).turning,3)
            case 1   % the go straight car
                car(i).speed=NormalV;
            case 2
                car(i).Vangle=pi/20;
            case 0
                car(i).Vangle=pi/120;
        end
    end
end