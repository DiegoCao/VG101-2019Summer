function crashstate=detectCrash(car,carin,carout)
crashstate=0;

carInfo=struct('xvalue',[],'yvalue',[]);
Info=repmat(carInfo,[1 carin-carout]);
m=0;

for i=1:carin
    if car(i).cross==1||car(i).cross==2||car(i).cross==4||car(i).cross==3
        m=m+1;             %the number of the cars at the cross section
        Info(m).x=car(i).x;
        Info(m).y=car(i).y;
    end
end
for i=1:m
    for j=i+1:m
        in1=inpolygon(Info(j).x(1),Info(j).y(1),Info(i).x,Info(i).y);
        in2=inpolygon(Info(j).x(2),Info(j).y(2),Info(i).x,Info(i).y);
        in3=inpolygon(Info(j).x(3),Info(j).y(3),Info(i).x,Info(i).y);
        in4=inpolygon(Info(j).x(4),Info(j).y(4),Info(i).x,Info(i).y);
        in5=inpolygon(Info(i).x(1),Info(i).y(1),Info(j).x,Info(j).y);
        in6=inpolygon(Info(i).x(2),Info(i).y(2),Info(j).x,Info(j).y);
        in7=inpolygon(Info(i).x(3),Info(i).y(3),Info(j).x,Info(j).y);
        in8=inpolygon(Info(i).x(4),Info(i).y(4),Info(j).x,Info(j).y);
        if(in1+in2+in3+in4+in5+in6+in7+in8)>0
        crashstate=crashstate+1;
        end
    end
end
end


