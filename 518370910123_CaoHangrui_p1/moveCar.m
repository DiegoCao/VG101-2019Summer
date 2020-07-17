function [car,carin,carout,Crosscar,Passcar]=moveCar(car,carin,carout,Crosscar,Light,width,t,rate,Passcar)   %重名有木有问题？
w=width;
roadLength=200;
time=t;
if mod(time,rate)==0&&carin<length(car)
    carin=carin+1;
    car(carin).cross=1;
end                         % 1 进入  2 等待 3 在路口 4 过路口 5 出
for i=1:carin
    switch car(i).cross
        case 0
            continue;
        case 1
            if car(i).direction==9||car(i).direction==1
                car(i).x=car(i).x+car(i).speed;
                if abs(car(i).x(3)+2*width)<car(i).speed
                    car(i).cross=2;
                end
            elseif car(i).direction==10||car(i).direction==2
                car(i).x=car(i).x-car(i).speed;
                if abs(car(i).x(3)-2*width)<car(i).speed
                    car(i).cross=2;
                end
            elseif car(i).direction==11||car(i).direction==3
                car(i).y=car(i).y+car(i).speed;
                if abs(car(i).y(3)+2*w)<car(i).speed
                    car(i).cross=2;
                end
            elseif car(i).direction==12||car(i).direction==4
                car(i).y=car(i).y-car(i).speed;
                if abs(car(i).y(3)-2*w)<car(i).speed
                    car(i).cross=2;
                end
            end
        case 2
            if car(i).direction==1||car(i).direction==2||car(i).direction==9||car(i).direction==10 
                if Light(1)==1  % greenlight
                    car(i).cross=3;
                    Crosscar=Crosscar+1;
                    %可以增加
                else
                    if car(i).runlight==0
                        car(i).cross=2;
                    else
                        car(i).cross=3;  %Come straight into the cross!!
                        Crosscar=Crosscar+1;
                    end
                end
            else
                if Light(3)==1  % greenlight
                    car(i).cross=3;
                    Crosscar=Crosscar+1;
                    %可以增加
                else
                    if car(i).runlight==0
                        car(i).cross=2;
                    else
                        car(i).cross=3;
                        Crosscar=Crosscar+1;
                        
                    end
                end
            end
        case 3
            if mod(car(i).turning,3)==1
                switch car(i).turning
                    case 1
                        car(i).x=car(i).x+car(i).speed;
                        if (car(i).x(1)-2*width)>0     %determine whether it needs to go out
                            car(i).cross=4;  % already passes
                            car(i).direction=13;
                            Crosscar=Crosscar-1;
                            Passcar=Passcar+1;
                        end
                    case 4
                        car(i).x=car(i).x-car(i).speed;
                        if (car(i).x(2)+2*width)<0
                            car(i).cross=4;
                            car(i).direction=14;
                            Crosscar=Crosscar-1;
                            Passcar=Passcar+1;
                        end
                    case 7
                        car(i).y=car(i).y+car(i).speed;
                        if (car(i).y(1)-2*width)>0
                            car(i).cross=4;
                            car(i).direction=15;
                            Crosscar=Crosscar-1;
                            Passcar=Passcar+1;
                        end
                    case 10
                        car(i).y=car(i).y-car(i).speed;
                        if (car(i).y(4)+2*width)<0
                            car(i).cross=4;
                            car(i).direction=16;
                            Crosscar=Crosscar-1;
                            Passcar=Passcar+1;
                        end
                end
            else
                [car(i),Crosscar,Passcar]=rotateCar(car(i),width,Crosscar,Passcar);
            end
        case 4 
            if car(i).direction==5||car(i).direction==13
                car(i).x=car(i).x+car(i).speed;
                if  car(i).x(3)>roadLength
                    car(i).out=1;
                    car(i).cross=5;
                    carout=carout+1;
                    Passcar=Passcar-1;
                end
            elseif car(i).direction==6||car(i).direction==14
                car(i).x=car(i).x-car(i).speed;
                if car(i).x(3)<-roadLength&&car(i).x(1)<-roadLength
                    car(i).out=1;
                    carout=carout+1;
                    car(i).cross=5;   
                    Passcar=Passcar-1;%不知道这个地方我设置的对不对啊
                end
            elseif car(i).direction==7||car(i).direction==15
                car(i).y=car(i).y+car(i).speed;
                if car(i).y(3)>roadLength
                    car(i).out=1;
                    car(i).cross=5;
                    carout=carout+1;
                    Passcar=Passcar-1;
                end
            elseif car(i).direction==8||car(i).direction==16
                car(i).y=car(i).y-car(i).speed;
                if car(i).y(3)<-roadLength
                    car(i).out=1;
                    car(i).cross=5;
                    carout=carout+1;
                    Passcar=Passcar-1;
                end
            end
        case 5
            continue;
    end
end
end
