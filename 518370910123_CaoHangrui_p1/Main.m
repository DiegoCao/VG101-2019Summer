% the main function
clearvars;
clc;
disp('if you notice the animation is not very smooth, press Ctrl+C, and type in clf, clearvars in command line');

disp('note: the width of the road should be larger than twice of the width of the car');
level=input('input the difficulty level you want: if you want easy, input 1, if you want difficult, input 2\n');
Light=[0,0,0,0];
roadLength=200;
if(level==2)
    [green,orange,red, pro, num, width,letter, Left_pro]=getInput();
    t=0;
else
    green=100;
    orange=80;
    red=10;
    num=30;
    width=30;
    letter='ASFGH45QWB';
    pro=1;
    Left_pro=0.4;
    t=0;
end
car=Initialize(num,pro,width,letter,Left_pro);       %First, Initialize the functions
carin=0;
Crosscar=0;
Passcar=0;
carout=0;
const_time=0.05;
Lightplot=[0,0,0,0];
disp('Suggestions: if want to see the car automatically slow down, choose the fast mode (super ');
Ratechoose= input('you want fast, medium or slow car producing rate? super fast, enter 1, fast enter 2, medium enter 3, slow, enter 4\n');
switch Ratechoose
    case 1
        rate=15;
    case 2
        rate=20;
    case 4
        rate=30;
    case 3
        rate=25;
end
Drawroad(2*width,roadLength);
Lightplot(1)=plot(-2*width,-2*width,'go','MarkerFaceColor','g','MarkerSize',6);
Lightplot(2)=plot(2*width,2*width,'go','MarkerFaceColor','g','MarkerSize',6);
Lightplot(3)=plot(-2*width,2*width,'ro','MarkerFaceColor','r','MarkerSize',6);
Lightplot(4)=plot(2*width,-2*width,'ro','MarkerFaceColor','r','MarkerSize',6);
axis([-roadLength roadLength -roadLength roadLength]);
while(1)
    car=initializeCrosscar(car,Crosscar,carin,Passcar);   % Initialize all the cars at cross, for the avoidcarcrash simulation
    car=avoidcarCrash(car,Crosscar,width,carin,Passcar);  
    [car,carin,carout,Crosscar,Passcar]=moveCar(car,carin,carout,Crosscar,Light,width,t,rate,Passcar);
    for i=1:carin
        if ~isempty(car(i).carplot)
            delete(car(i).carplot);   % delete the car that has been plotted
        end
    end
    car=Plotcar(car,carin);
    [Light,Lightplot]=lightState(t,red, orange, green, width, Light,Lightplot);
    crash=detectCrash(car,carin,carout);
    if  crash >0
        pause;
        disp('Game over,you lose!');
        break;
    end
    if carout==length(car)
        disp('Congratulations! you win this game!');
        break;
    end
    %red, orange, green, width, Lightstate
    car=speedChange(car,carin);
    t=t+1;
    pause(0.01);
    
end

disp('For those who run the red lights, their plates are');
m=0;
    for i=1:carin
        
        if car(i).cross>=3&&car(i).runlight==1
            fprintf('%s ',car(i).plate);
            m=m+1;
        end
    end
if m==0
       disp('No car run red lights!');
end
if crash>0
    clf;
    x=imread('Youlose.jpg');
    axis([-roadLength roadLength -roadLength roadLength]);
    imshow(x);
 
end
if carout==length(car)
    clf;
    disp('you win!');
    x=imread('Youwin.jpg');
    imshow(x);
end