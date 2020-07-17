function [Light,Lightplot]=lightState(t, red, orange, green,width,Lightstate,Lightplot)
Light=Lightstate;
roadLength=200;
cycle=red+orange+green;
caltime=mod(t,cycle);
if caltime==green
    delete(Lightplot(1));
    delete(Lightplot(2));
    Lightplot(1)=plot(-2*width,-2*width,'go','MarkerFaceColor','y','MarkerSize',6);
    Lightplot(2)=plot(2*width,2*width,'go','MarkerFaceColor','y','MarkerSize',6);
    Light(1)=2;
    Light(2)=2;
elseif  caltime == (orange+green)
    delete(Lightplot(1));
    delete(Lightplot(2));
    Lightplot(1)=plot(2*width,2*width,'yo','MarkerFaceColor','r','MarkerSize',6);
    Lightplot(2)=plot(-2*width,-2*width,'yo','MarkerFaceColor','r','MarkerSize',6);
    Light(1)=3;
    Light(2)=3;
elseif caltime==0&&t~=0
    Lightplot(1)=plot(2*width,2*width,'ro','MarkerFaceColor','g','MarkerSize',6);
    Lightplot(2)=plot(-2*width,-2*width,'ro','MarkerFaceColor','g','MarkerSize',6);
    hold on;
    Light(1)=1;
    Light(2)=1;
elseif t==0
    Lightplot(1)=plot(-2*width,-2*width,'go','MarkerFaceColor','g','MarkerSize',6);
    Lightplot(2)=plot(2*width,2*width,'go','MarkerFaceColor','g','MarkerSize',6);
    Light(1)=1;
    Light(2)=1;
end
if caltime>=0&&caltime<red
    plot(-2*width,2*width,'ro','MarkerFaceColor','r','MarkerSize',6);
    plot(2*width,-2*width,'ro','MarkerFaceColor','r','MarkerSize',6);
    hold on;
    Light(3)=3;
    Light(4)=3;
elseif caltime>=red && caltime< (red+green)
    plot(-2*width,2*width,'go','MarkerFaceColor','g','MarkerSize',6);
    plot(2*width,-2*width,'go','MarkerFaceColor','g','MarkerSize',6);
    hold on;
    Light(3)=1;
    Light(4)=1;
else
    plot(-2*width,2*width,'yo','MarkerFaceColor','y','MarkerSize',6);
    plot(2*width,-2*width,'yo','MarkerFaceColor','y','MarkerSize',6);
    hold on;
    Light(3)=2;
    Light(4)=2;
end
axis ([-roadLength roadLength -roadLength roadLength]);
end


