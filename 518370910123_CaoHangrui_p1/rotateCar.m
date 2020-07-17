function [car,Crosscar,Passcar]=rotateCar(car,width,Crosscar,Passcar)
%disp('rotate!');
w=width;
if car.Vangle==0
    return;
end
%disp(car.angle-pi/2);
if car.angle > 1.56
    switch car.turning
        case 2
            car.cross=4;
            car.direction=16;
            Crosscar=Crosscar-1;
            Passcar=Passcar+1;
        case 3
               %5,6£º 1³µµÀÓÒ×ó×ª¡­¡­
            car.cross=4;
            car.direction=7;
            Crosscar=Crosscar-1;
            Passcar=Passcar+1;
        case 5
            car.cross=4;
            car.direction=15;
            Crosscar=Crosscar-1;
            Passcar=Passcar+1;
        case 6
            car.cross=4;
            car.direction=8;
            Crosscar=Crosscar-1;
            Passcar=Passcar+1;
        case 8
            car.cross=4;
            car.direction=13;
            Crosscar=Crosscar-1;
        case 9
            car.direction=6;
            car.cross=4;
            Crosscar=Crosscar-1;
            Passcar=Passcar+1;
        case 11
            car.direction=14;
            car.cross=4;
            Crosscar=Crosscar-1;
            Passcar=Passcar+1;
        case 12
            car.direction=5;
            car.cross=4;
            Crosscar=Crosscar-1;
            Passcar=Passcar+1;
    end
else
    switch car.turning
        case 2
            car.angle = car.angle+car.Vangle;
            R1=(width-car.width)/2;
            R2=(width+car.width)/2;           
            car.x(3)=R1*sin(car.angle)-2*w;
            car.y(3)=R1*cos(car.angle)-2*w;
            car.x(4)=R2*sin(car.angle)-2*w;
            car.y(4)=R2*cos(car.angle)-2*w;
            car.x(2)=car.x(3)-car.length*cos(car.angle);
            car.y(2)=car.y(3)+car.length*sin(car.angle);
            car.x(1)=car.x(4)-car.length*cos(car.angle);
            car.y(1)=car.y(4)+car.length*sin(car.angle);
        case 3     % road 1, turn left
            R1=(width-car.width)/2+2*w;
            R2=(width+car.width)/2+2*w;
            car.angle = car.angle+car.Vangle;
            car.x(4)=R1*sin(car.angle)-2*w;
            car.y(4)=-R1*cos(car.angle)+2*w;
            car.x(3)=R2*sin(car.angle)-2*w;
            car.y(3)=-R2*cos(car.angle)+2*w;
            car.x(1)=car.x(4)-car.length*cos(car.angle);
            car.y(1)=car.y(4)-car.length*sin(car.angle);
            car.x(2)=car.x(3)-car.length*cos(car.angle);
            car.y(2)=car.y(3)-car.length*sin(car.angle);
        case 5   
            car.angle = car.angle+car.Vangle;
            R1=(width-car.width)/2;
            R2=(width+car.width)/2;
            car.x(3)=-R1*sin(car.angle)+2*w;
            car.y(3)=-R1*cos(car.angle)+2*w;
            car.x(4)=-R2*sin(car.angle)+2*w;
            car.y(4)=-R2*cos(car.angle)+2*w;
            car.x(2)=car.x(3)+car.length*cos(car.angle);
            car.y(2)=car.y(3)-car.length*sin(car.angle);
            car.x(1)=car.x(4)+car.length*cos(car.angle);
            car.y(1)=car.y(4)-car.length*sin(car.angle);
            
        case 6  % road 2, turn left 
            car.angle = car.angle+car.Vangle;
            R1=(width-car.width)/2+2*w;
            R2=(width+car.width)/2+2*w;
            car.x(3)=-R1*sin(car.angle)+2*w;
            car.y(3)=R1*cos(car.angle)-2*w;
            car.x(4)=-R2*sin(car.angle)+2*w;
            car.y(4)=R2*cos(car.angle)-2*w;
            car.x(2)=car.x(3)+car.length*cos(car.angle);
            car.y(2)=car.y(3)+car.length*sin(car.angle);
            car.x(1)=car.x(4)+car.length*cos(car.angle);
            car.y(1)=car.y(4)+car.length*sin(car.angle);
        case 8
            car.angle = car.angle+car.Vangle;
            R1=(width-car.width)/2;
            R2=(width+car.width)/2;
            car.y(2)=R1*sin(car.angle)-2*w;
            car.x(2)=2*w-R1*cos(car.angle);
            car.y(1)=R2*sin(car.angle)-2*w;
            car.x(1)=2*w-R2*cos(car.angle);
            car.x(3)=car.x(2)-car.length*sin(car.angle);
            car.y(3)=car.y(2)-car.length*cos(car.angle);
            car.x(4)=car.x(1)-car.length*sin(car.angle);
            car.y(4)=car.y(1)-car.length*cos(car.angle);
        case 9   % road 3, turn left
            car.angle = car.angle+car.Vangle;
            R1=(width-car.width)/2+2*w;
            R2=(width+car.width)/2+2*w;
            car.y(3)=R2*sin(car.angle)-2*w;
            car.x(3)=-2*w+R2*cos(car.angle);
            car.y(4)=R1*sin(car.angle)-2*w;
            car.x(4)=-2*w+R1*cos(car.angle);
            car.x(2)=car.x(3)+car.length*sin(car.angle);
            car.y(2)=car.y(3)-car.length*cos(car.angle);
            car.x(1)=car.x(4)+car.length*sin(car.angle);
            car.y(1)=car.y(4)-car.length*cos(car.angle);
        case 11
            car.angle = car.angle+car.Vangle;
            R1=(width-car.width)/2;
            R2=(width+car.width)/2;
            car.x(3)=-2*w+R1*cos(car.angle);
            car.y(3)=2*w-R1*sin(car.angle);
            car.x(4)=-2*w+R2*cos(car.angle);
            car.y(4)=2*w-R2*sin(car.angle);
            car.x(2)=car.x(3)+car.length*sin(car.angle);
            car.y(2)=car.y(3)+car.length*cos(car.angle);
            car.x(1)=car.x(4)+car.length*sin(car.angle);
            car.y(1)=car.y(4)+car.length*cos(car.angle);
        case 12
            car.angle = car.angle+car.Vangle;
            R1=(width-car.width)/2+2*w;
            R2=(width+car.width)/2+2*w;
            car.x(3)=2*w-R2*cos(car.angle);
            car.y(3)=2*w-R2*sin(car.angle);
            car.x(4)=2*w-R1*cos(car.angle);
            car.y(4)=2*w-R1*sin(car.angle);
            car.x(2)=car.x(3)-car.length*sin(car.angle);
            car.y(2)=car.y(3)+car.length*cos(car.angle);
            car.x(1)=car.x(4)-car.length*sin(car.angle);
            car.y(1)=car.y(4)+car.length*cos(car.angle);
    end
end
end

