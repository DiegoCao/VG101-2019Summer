function y=Initialize(num,pro,width,letter, Left_pro)
%g: time for green light o: time for orange light r: time for red light
%n:number of cars. p:probablities carss the road w: width
%car.x, car.y is the postion of four corners of one car
%car.speed is the speed of one car
y=struct('direction','0','turning','0','angle','0','cross','0',...
    'runlight','0','type','0','plate',[],'x',[],'y',[],'length','0','width'...
    ,'0','speed','0','out','0','carplot',[],'Vangle','0');
y=repmat(y,[1 num]);
Normalspeed=1;
roadLength=200;
w=width;
Carlength=[8,10];
Carwidth=[5,6];
%DirectionA=[1,2];    Direction: which lane of the road the car is in.
%DirectionB=[4,5];  
%DirectionC=[7,8];
%DirectionD=[10,11];
Carplate=makePlate(letter,num);
Right_lane=[9,10,11,12];% the lane to turn left
Left_lane=[1,2,3,4];
for i=1:num
    y(i).plate=Carplate(i);
    randnum=randperm(100,1);
    if randnum<Left_pro*100
        y(i).direction=Left_lane(randperm(4,1));
    else
        y(i).direction=Right_lane(randperm(4,1));
    end
    y(i).angle=0;
    y(i).cross=0;  %0indicates not evenin;1 indicates before cross: 2: waiting at cross. 3: at cross move 4: passcross 5: out
    y(i).type=randperm(4,1);
    y(i).runlight=0;
     % here a function needs
    y(i).width=Carwidth(randperm(2,1));   
    switch y(i).width
        case 5
            y(i).length=Carlength(1);
        case 6
            y(i).length=Carlength(2);
    end   
    y(i).speed=Normalspeed;
    y(i).out=0;
    y(i).cposition=[0,0];
    randinum=randperm(100,1);
    switch y(i).direction
        case 1
            y(i).turning=3;
        case 9
            if randperm(5,1)<=2
                y(i).turning=2;
            else 
                y(i).turning=1;
            end
        case 2
            y(i).turning=6;
        case 10
            %y(i).turning=DirectionB(randperm(2,1));
            if randperm(5,1)<=2
                y(i).turning=5;
            else 
                y(i).turning=4;
            end
        case 3
            y(i).turning=9;
        case 11
            %y(i).turning=DirectionC(randperm(2,1));
            if randperm(5,1)<=2
                y(i).turning=8;
            else 
                y(i).turning=7;
            end
        case 4
            y(i).turning=12;
        case 12
            %y(i).turning=DirectionD(randperm(2,1));
            if randperm(5,1)<=2
                y(i).turning=11;
            else 
                y(i).turning=10;
            end
    end
    if mod(y(i).turning,3)==0
        y(i).Vangle=pi/120;
    elseif mod(y(i).turning,3)==2
        y(i).Vangle=pi/20;
    end
    
    if randinum < (100*pro)
        y(i).runlight=1; %可能需要精确写一个函数
    else
        y(i).runlight=0;
    end
    switch y(i).direction
        case 1
            y(i).x=[-roadLength,-roadLength,-roadLength+y(i).length,-roadLength+y(i).length];
            y(i).y=[-(w-y(i).width)/2,-(w+y(i).width)/2,-(w+y(i).width)/2,-(w-y(i).width)/2];
        case 2
            y(i).x=[roadLength,roadLength,roadLength-y(i).length,roadLength-y(i).length];
            y(i).y=[(w-y(i).width)/2,(w+y(i).width)/2,(w+y(i).width)/2,(w-y(i).width)/2];
        case 3
            y(i).x=[(w-y(i).width)/2,(w+y(i).width)/2,(w+y(i).width)/2,(w-y(i).width)/2];
            y(i).y=[-roadLength,-roadLength,-roadLength+y(i).length,-roadLength+y(i).length];
        case 4
            y(i).x=[-(w-y(i).width)/2,-(w+y(i).width)/2,-(w+y(i).width)/2,-(w-y(i).width)/2];
            y(i).y=[roadLength,roadLength,roadLength-y(i).length,roadLength-y(i).length];
        case 9
            y(i).x=[-roadLength,-roadLength,-roadLength+y(i).length,-roadLength+y(i).length];
            y(i).y=[-(w-y(i).width)/2-w,-(w+y(i).width)/2-w,-(w+y(i).width)/2-w,-(w-y(i).width)/2-w];
        case 10
            y(i).x=[roadLength,roadLength,roadLength-y(i).length,roadLength-y(i).length];
            y(i).y=[(w-y(i).width)/2+w,(w+y(i).width)/2+w,(w+y(i).width)/2+w,(w-y(i).width)/2+w];
        case 11
            y(i).x=[(w-y(i).width)/2+w,(w+y(i).width)/2+w,(w+y(i).width)/2+w,(w-y(i).width)/2+w];
            y(i).y=[-roadLength,-roadLength,-roadLength+y(i).length,-roadLength+y(i).length];           
        case 12
            y(i).x=[-(w-y(i).width)/2-w,-(w+y(i).width)/2-w,-(w+y(i).width)/2-w,-(w-y(i).width)/2-w];
            y(i).y=[roadLength,roadLength,roadLength-y(i).length,roadLength-y(i).length];
    end
end   
end