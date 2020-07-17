function car=avoidcarCrash(car,Crosscar,width,carin,Passcar)
tempcar=car;  % use a tempcar to record the function
% initialize the Crosstempcar function
CLabel=zeros(1,Crosscar+Passcar);
num=0;
% SIMULATION TO SEE the 'future states';
DetectLength=7;   % the length of the detector(for turning left and right cars£©
SLength=6;        % the length of the detector(for going straight cars)
for i=1:carin
    if tempcar(i).cross==3||car(i).cross==4      % only compare the car at cross
        num=num+1;
        CLabel(num)=i;
        if tempcar(i).turning==1
            tempcar(i).x(3)=tempcar(i).x(3)+SLength;
            tempcar(i).x(4)=tempcar(i).x(4)+SLength;
        elseif tempcar(i).turning==4
            tempcar(i).x(3)=tempcar(i).x(3)-SLength;
            tempcar(i).x(4)=tempcar(i).x(4)-SLength;
        elseif tempcar(i).turning==7
            tempcar(i).y(3)=tempcar(i).y(3)+SLength;
            tempcar(i).y(4)=tempcar(i).y(4)+SLength;
        elseif tempcar(i).turning==10
            tempcar(i).y(3)=tempcar(i).y(3)-SLength;
            tempcar(i).y(4)=tempcar(i).y(4)-SLength;
        elseif mod(tempcar(i).turning,3)~=1
            if tempcar(i).turning==3
                tempcar(i).x(3)=DetectLength*cos(tempcar(i).angle)+tempcar(i).x(3);
                tempcar(i).x(4)=DetectLength*cos(tempcar(i).angle)+tempcar(i).x(4);
                tempcar(i).y(3)=DetectLength*sin(tempcar(i).angle)+tempcar(i).y(3);
                tempcar(i).y(4)=DetectLength*sin(tempcar(i).angle)+tempcar(i).y(4);
            elseif tempcar(i).turning==2
                tempcar(i).x(3)=DetectLength*cos(tempcar(i).angle)+tempcar(i).x(3);
                tempcar(i).x(4)=DetectLength*cos(tempcar(i).angle)+tempcar(i).x(4);
                tempcar(i).y(3)=-DetectLength*sin(tempcar(i).angle)+tempcar(i).y(3);
                tempcar(i).y(4)=-DetectLength*sin(tempcar(i).angle)+tempcar(i).y(4);
            elseif tempcar(i).turning==5
                tempcar(i).x(3)=-DetectLength*cos(tempcar(i).angle)+tempcar(i).x(3);
                tempcar(i).x(4)=-DetectLength*cos(tempcar(i).angle)+tempcar(i).x(4);
                tempcar(i).y(3)=DetectLength*sin(tempcar(i).angle)+tempcar(i).y(3);
                tempcar(i).y(4)=DetectLength*sin(tempcar(i).angle)+tempcar(i).y(4);
            elseif tempcar(i).turning==6
                tempcar(i).x(3)=-DetectLength*cos(tempcar(i).angle)+tempcar(i).x(3);
                tempcar(i).x(4)=-DetectLength*cos(tempcar(i).angle)+tempcar(i).x(4);
                tempcar(i).y(3)=-DetectLength*sin(tempcar(i).angle)+tempcar(i).y(3);
                tempcar(i).y(4)=-DetectLength*sin(tempcar(i).angle)+tempcar(i).y(4);
            elseif tempcar(i).turning==8
                tempcar(i).y(3)=DetectLength*cos(tempcar(i).angle)+tempcar(i).y(3);
                tempcar(i).y(4)=DetectLength*cos(tempcar(i).angle)+tempcar(i).y(4);
                tempcar(i).x(3)=DetectLength*sin(tempcar(i).angle)+tempcar(i).x(3);
                tempcar(i).x(4)=DetectLength*sin(tempcar(i).angle)+tempcar(i).x(4);
            elseif tempcar(i).turning==9
                tempcar(i).y(3)=DetectLength*cos(tempcar(i).angle)+tempcar(i).y(3);
                tempcar(i).y(4)=DetectLength*cos(tempcar(i).angle)+tempcar(i).y(4);
                tempcar(i).x(3)=-DetectLength*sin(tempcar(i).angle)+tempcar(i).x(3);
                tempcar(i).x(4)=-DetectLength*sin(tempcar(i).angle)+tempcar(i).x(4);
            elseif tempcar(i).turning==11
                tempcar(i).y(3)=-DetectLength*cos(tempcar(i).angle)+tempcar(i).y(3);
                tempcar(i).y(4)=-DetectLength*cos(tempcar(i).angle)+tempcar(i).y(4);
                tempcar(i).x(3)=-DetectLength*sin(tempcar(i).angle)+tempcar(i).x(3);
                tempcar(i).x(4)=-DetectLength*sin(tempcar(i).angle)+tempcar(i).x(4);
            elseif tempcar(i).turning==12
                tempcar(i).y(3)=-DetectLength*cos(tempcar(i).angle)+tempcar(i).y(3);
                tempcar(i).y(4)=-DetectLength*cos(tempcar(i).angle)+tempcar(i).y(4);
                tempcar(i).x(3)=DetectLength*sin(tempcar(i).angle)+tempcar(i).x(3);
                tempcar(i).x(4)=DetectLength*sin(tempcar(i).angle)+tempcar(i).x(4); 
            end
        end
    end
end
Stoplabel=zeros(1,Crosscar+Passcar);
stopnum=0;
% then detect whether they would crash or not, and change their speed
if length(CLabel)>2
    for i=1:length(CLabel)-1
        for j=i+1:length(CLabel)
            in3=inpolygon(tempcar(CLabel(j)).x(3),tempcar(CLabel(j)).y(3),tempcar(CLabel(i)).x,tempcar(CLabel(i)).y);  
            in4=inpolygon(tempcar(CLabel(j)).x(4),tempcar(CLabel(j)).y(4),tempcar(CLabel(i)).x,tempcar(CLabel(i)).y);
            in7=inpolygon(tempcar(CLabel(i)).x(3),tempcar(CLabel(i)).y(3),tempcar(CLabel(j)).x,tempcar(CLabel(j)).y);
            in8=inpolygon(tempcar(CLabel(i)).x(4),tempcar(CLabel(i)).y(4),tempcar(CLabel(j)).x,tempcar(CLabel(j)).y);
            if  tempcar(CLabel(i)).cross==4&&tempcar(CLabel(j)).cross==4
                in1=inpolygon(tempcar(CLabel(j)).x(1),tempcar(CLabel(j)).y(1),tempcar(CLabel(i)).x,tempcar(CLabel(i)).y);
                in2=inpolygon(tempcar(CLabel(j)).x(2),tempcar(CLabel(j)).y(2),tempcar(CLabel(i)).x,tempcar(CLabel(i)).y);
                if (in1+in2)>0
                   car(CLabel(i)).speed=0;
                end 
            else       
                if (in3+in4)>(in7+in8)
                stopnum=stopnum+1;
                Stoplabel(stopnum)=CLabel(j);
                 elseif (in3+in4)<(in7+in8)
                stopnum=stopnum+1;
                Stoplabel(stopnum)=CLabel(i);
                elseif (in3+in4)==(in7+in8)&&(in8+in7+in3+in4)>0
                stopnum=stopnum+1;
                Stoplabel(stopnum)=CLabel(j);
                stopnum=stopnum+1;
                Stoplabel(stopnum)=CLabel(i);  
                end
            end
        end
    end
end

if stopnum>0
    for k=1:stopnum
        if car(Stoplabel(stopnum)).cross==3
            if mod(car(Stoplabel(stopnum)).turning,3)==1
            car(Stoplabel(stopnum)).speed=0;

            %disp(Stoplabel(stopnum));
            elseif mod(car(Stoplabel(stopnum)).turning,3)==2
            car(Stoplabel(stopnum)).Vangle=0;

           
            elseif mod(car(Stoplabel(stopnum)).turning,3)==0
            car(Stoplabel(stopnum)).Vangle=0;

            %disp(Stoplabel(stopnum)); 
            end

        end
        
    end
end
end

