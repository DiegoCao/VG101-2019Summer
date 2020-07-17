function car=detectDistance(car,carin)
safe_Distance=[5,4,3,0.8];
Normalspeed=1;
Speed1=0.4;
Speed2=0.2;
Speed3=0.1;
Speed4=0;
%car.cposition,[x,y] calculates the center position of one car.
for i=1:carin
    car(i).cposition(1)=mean(car(i).x)/2;
    car(i).cposition(2)=mean(car(i).y)/2;
end
for i=1:carin
    if car(i).cross==1||car(i).cross==2||car(i).cross==3||car(i).cross==4
        j=i+1;
        if car(i).direction==car(j).direction&&car(i).direction<5
            switch car(i).direction
                case 9
                    distance=car(i).cposition(1)-car(j).cposition(1);
                case 10
                    distance=car(j).cposition(1)-car(i).cposition(1);
                case 11
                    distance=car(i).cposition(2)-car(j).cposition(2);
                case 12
                    distance=car(j).cposition(2)-car(i).cposition(2);
            end
            if distance <=((car(i).length+car(j).length)/2+safe_Distance(1))...
                    &&distance>=((car(i).length+car(j).length)/2+safe_Distance(2))
                car(j).speed=Speed1;
                disp('slow down 1');
                break;
            elseif distance< ((car(i).length+car(j).length)/2+safe_Distance(2))...
                    &&distance>=((car(i).length+car(j).length)/2+safe_Distance(3))
                car(j).speed=Speed2;
                disp('slow down 2');
                break;
            elseif distance< ((car(i).length+car(j).length)/2+safe_Distance(3))...
                    &&distance>=((car(i).length+car(j).length)/2+safe_Distance(4))
                car(j).speed=Speed3;
                disp('slow down 3');
                break;
            elseif distance< ((car(i).length+car(j).length)/2+safe_Distance(4))...
                    &&distance>=0
                car(j).speed=Speed4;
                disp('stop');
                break;
            elseif distance>((car(i).length+car(j).length)/2+safe_Distance(1))
                car(j).speed=Normalspeed;
                
            end
        end
        
    end
end

end




