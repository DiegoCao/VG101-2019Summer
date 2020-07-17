function Drawroad(width, length)
roadWidth=2*width;
% We can use paneNum, Here, we set the number of panes as 1.
x=[-(length+width), -width,-width,width,width,(length+width),...
    (length+width),width,width,-width,-width,-(length+width)];
y=[width,width,(width+length),(width+length),width,width,...
    -width,-width, -(width+length), -(width+length),-width,-width];
road1=fill(x,y,[0.8,0.8,0.8]);
set(road1,{'LineStyle'},{'none'});
hold on;
plot([roadWidth/2, roadWidth/2],[roadWidth/2,width/2+length],'Linewidth',2,'Color',[0,0,0]);
hold on;
plot([roadWidth/2, (width/2+length)],[roadWidth/2,roadWidth/2],'Linewidth',2,'Color',[0,0,0]);
hold on;
plot([-roadWidth/2, -(width/2+length)],[roadWidth/2,roadWidth/2],'Linewidth',2,'Color',[0,0,0]);
plot([roadWidth/2, (width/2+length)],[roadWidth/2,roadWidth/2],'Linewidth',2,'Color',[0,0,0]);
plot([-roadWidth/2,-roadWidth/2],[-roadWidth/2, -(width/2+length)],'Linewidth',2,'Color',[0,0,0]);
plot([-roadWidth/2,-roadWidth/2],[roadWidth/2, (width/2+length)],'Linewidth',2,'Color',[0,0,0]);
plot([-roadWidth/2, -(width/2+length)],[-roadWidth/2,-roadWidth/2],'Linewidth',2,'Color',[0,0,0]);
plot([roadWidth/2, (width/2+length)],[-roadWidth/2,-roadWidth/2],'Linewidth',2,'Color',[0,0,0]);
plot([roadWidth/2,roadWidth/2],[-roadWidth/2, -(width/2+length)],'Linewidth',2,'Color',[0,0,0]);
axis equal;
     %   plot(-width/2,-width/2,'ro','MarkerFaceColor','g','MarkerSize',10);
      %  hold on;
      %  plot(width/2,width/2,'ro','MarkerFaceColor','g','MarkerSize',10);
      %  hold on;
      %  plot(-width/2,width/2,'ro','MarkerFaceColor','r','MarkerSize',10);
      %  hold on;
      %  plot(width/2,-width/2,'ro','MarkerFaceColor','r','MarkerSize',10);

plot([-(roadWidth/2),-length-width/2],[-(roadWidth/2)+(roadWidth)/(2),-(roadWidth/2)+(roadWidth)/(2)],...
    'Linewidth', 1,'LineStyle','--','color',[1 1 0]);
plot([-roadWidth/2,-length-width/2],[-roadWidth/4,-roadWidth/4],'Linewidth', 1,'LineStyle','--','color',[1 1 0]);
plot([-roadWidth/2,-length-width/2],[roadWidth/4,roadWidth/4],'Linewidth', 1,'LineStyle','--','color',[1 1 0]);
plot([-(roadWidth/2)+(roadWidth)/(2),-(roadWidth/2)+(roadWidth)/(2)],[(roadWidth/2),length+width/2],...
    'Linewidth', 1,'LineStyle','--','color',[1 1 0]);
plot([-roadWidth/4,-roadWidth/4],[roadWidth/2,length+width/2],'Linewidth', 1,'LineStyle','--','color',[1 1 0]);
plot([roadWidth/4,roadWidth/4],[roadWidth/2,length+width/2],'Linewidth', 1,'LineStyle','--','color',[1 1 0]);

plot([-(roadWidth/2)+(roadWidth)/(2),-(roadWidth/2)+(roadWidth)/(2)],[-(roadWidth/2),-length-width/2],...
    'Linewidth',1,'LineStyle','--','Color',[1 1 0]);
plot([-roadWidth/4,-roadWidth/4],[-roadWidth/2,-(length+width/2)],'Linewidth', 1,'LineStyle','--','color',[1 1 0]);
plot([roadWidth/4,roadWidth/4],[-roadWidth/2,-(length+width/2)],'Linewidth', 1,'LineStyle','--','color',[1 1 0]);
plot([(roadWidth/2),length+width/2],[-(roadWidth/2)+(roadWidth)/(2),-(roadWidth/2)+(roadWidth)/(2)],...
    'Linewidth', 1,'LineStyle','--','color',[1 1 0]);
plot([(roadWidth/2),length+width/2],[-roadWidth/4,-roadWidth/4],...
    'Linewidth', 1,'LineStyle','--','color',[1 1 0]);
plot([(roadWidth/2),length+width/2],[roadWidth/4,roadWidth/4],...
    'Linewidth', 1,'LineStyle','--','color',[1 1 0]);

axis([-1.2*length 1.2*length -1.2*length 1.2*length]);
end