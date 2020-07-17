function carplot=Acardraw(x,y,type)
%l indicates the length of the car
%w indicates the width of the car
%o indicates the center position  
%First, check whether the car has already exceeded the boundary
%Then, check whether the car has collision with other car that needs to be drawn
%Then plot car
if type==1
        carplot=fill([x(1),x(2),x(3),x(4),x(1)],[y(1),y(2),y(3),y(4),y(1)],'r');
        hold on;
elseif type==2
        carplot=fill([x(1),x(2),x(3),x(4),x(1)],[y(1),y(2),y(3),y(4),y(1)],'y');
        hold on;
elseif type==3

        carplot=fill([x(1),x(2),x(3),x(4),x(1)],[y(1),y(2),y(3),y(4),y(1)],'b');        
        hold on;
else  
    carplot=fill([x(1),x(2),x(3),x(4),x(1)],[y(1),y(2),y(3),y(4),y(1)],'k'); 
end
end
