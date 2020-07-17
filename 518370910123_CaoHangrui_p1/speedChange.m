function car=speedChange(car,carin)
%for i=1:carin
%   carnum(car(i).direction)=carnum(car(i).direction)+1;
%end
LabelA=[];
car2label=[];
car3label=[];
car4label=[];
car5label=[];
car6label=[];
car7label=[];
car8label=[];
car9label=[];
car10label=[];
car11label=[];
car12label=[];
car13label=[];
car14label=[];
car15label=[];
car16label=[];
for i=1:carin
    car(i).cposition(1)=mean(car(i).x);
    car(i).cposition(2)=mean(car(i).y);
end

for i=1:carin
    if car(i).cross~=0&&car(i).cross~=5
    switch car(i).direction
        case 1
            LabelA=[LabelA,i];
        case 2
            car2label=[car2label,i];
        case 3
            car3label=[car3label,i];
        case 4
            car4label=[car4label,i];
        case 5
            car5label=[car5label,i];
        case 6
            car6label=[car6label,i];
        case 7
            car7label=[car7label,i];          %Through searching, this warning will matter so much, so I skip this.
        case 8
            car8label=[car8label,i];
        case 9
            car9label=[car9label,i];
        case 10
            car10label=[car10label,i];
        case 11
            car11label=[car11label,i];
        case 12
            car12label=[car12label,i];
        case 13
            car13label=[car13label,i];
        case 14
            car14label=[car14label,i];
        case 15
            car15label=[car15label,i];
        case 16
            car16label=[car16label,i];
    end
    end
end
car=changeV(car,LabelA);
car=changeV(car,car2label);
car=changeV(car,car3label);
car=changeV(car,car4label);
car=changeV(car,car5label);
car=changeV(car,car6label);
car=changeV(car,car7label);
car=changeV(car,car8label);
car=changeV(car,car9label);
car=changeV(car,car10label);
car=changeV(car,car11label);
car=changeV(car,car12label);
car=changeV(car,car13label);
car=changeV(car,car14label);
car=changeV(car,car15label);
car=changeV(car,car16label);
end
%the changeV function will deal the velocity change of one car, according
%to the distance between itself and the car infront of it.
function car=changeV(car,label)

FastV=2.6;
V=2;
NormalV=1.4;
V1=0.7;
V2=0.4;
V3=0.2;
V4=0;
Safety=[6,8,12,16,20,2];
if length(label)==1
    car(label(1)).speed=FastV;
elseif length(label)>1
    
    for i=1:length(label)-1
        if i==1
            car(label(i)).speed=FastV;
        end
        j=i+1;
        distance=norm(car(label(i)).cposition-car(label(j)).cposition);
        Length_distance=(car(label(i)).length+car(label(j)).length)/2;
        if distance<=Length_distance+Safety(1)&&distance>Length_distance+Safety(6)
            car(label(j)).speed=V3;
        elseif distance<=Length_distance+Safety(6)
            car(label(j)).speed=V4; 
        elseif distance>Length_distance+Safety(1)&&...
                distance<=Length_distance+Safety(2)
            car(label(j)).speed=V2;
        elseif distance>Length_distance+Safety(2)&&...
                distance<=Length_distance+Safety(3)
            car(label(j)).speed=V1;
        elseif distance>Length_distance+Safety(3)&&...
                distance<=Length_distance+Safety(4)
            car(label(j)).speed=NormalV;
        elseif distance>Length_distance+Safety(4)&&distance<Length_distance+Safety(5)
            car(label(j)).speed=V;
        elseif distance>Length_distance+Safety(5)
            car(label(j)).speed=FastV;
        end
    end
end
end

    



