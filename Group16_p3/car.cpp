//
// Created by Dell on 2019/7/23.
//

#include "car.h"
#include "p3.h"
#include "Group.h"

#include <iostream>
#define TRUCKNUM 7
truck::truck() {
    carfig[0]=new Quad(0.5,0.2,0.3,Vec{2,0},Vec(2,4),Vec{6,4},Vec{8,0});
    carfig[1]=new Quad(0.2,0.1,0.8,Vec{-8,-4},Vec{-6,0},Vec{8,0},Vec{8,-4});
    carfig[2]=new Circle(0.7,0.7,0.7,{-2,-4},1.5);
    carfig[3]=new Circle(0.7,0.7,0.7,{4,-4},1.5);
    carfig[4]=new Circle(0,0,0,{-2,-4},0.8);
    carfig[5]=new Circle(0,0,0,{4,-4},0.8);
    carfig[6]=new Quad(1,0.8,0.6,{-6,0},{-6,1},{-5.6,1},{-5.6,1});

}
truck::truck(Vec ce) {
    double color1[2][3]={{0,1,0.8},{1,0,1}};
    int colornum=rand()%2;
    double color2[2][3]={{0.2,1,.4},{0,.8,.6}};


    carfig[0]=new Quad(color1[colornum][0],color1[colornum][1],color1[colornum][2],Vec{2,0},Vec(2,4),Vec{6,4},Vec{8,0});
    carfig[1]=new Quad(color2[colornum][0],color2[colornum][1],color2[colornum][2],Vec{-8,-4},Vec{-6,0},Vec{8,0},Vec{8,-4});
    carfig[2]=new Circle(0.7,0.7,0.7,{-2,-4},1.5);
    carfig[3]=new Circle(0.7,0.7,0.7,{4,-4},1.5);
    carfig[4]=new Circle(0,0,0,{-2,-4},0.8);
    carfig[5]=new Circle(0,0,0,{4,-4},0.8);
    carfig[6]=new Quad(1,0.8,0.6,{-5,0},{-5,3},{-4,3},{-4,0});
    carflag=new Quad(0.8,1,1,{-6,2},{-5,3},{-5,1},{-5,1});
    center={0,0};
    for(int i=0;i<TRUCKNUM;i++){carfig[i]->move(ce);}
    carflag->move(ce);
    center=center+ce;
    setAnchor(center);
    carstate=0;rotateState=0;
    VNUM=0.2;
    angle=0;
}
void truck::move(Vec a) {
    for(int i=0;i<TRUCKNUM;i++){carfig[i]->move(a);}
    center=center+a;
    carflag->move(a);
}
void truck::draw() {

    parktime++;
    int temp=parktime%30;
    if(temp>=0&&temp<10){carflag->setOnepoint(0,{carflag->getpnum(1).getX()-1*cos(angle),carflag->getpnum(1).getY()-1*sin(angle)});}
    else if(temp>=10&&temp<20){carflag->setOnepoint(0,{(carflag->getpnum(1).getX()+carflag->getpnum(2).getX())/2-1*cos(angle),(carflag->getpnum(1).getY()+carflag->getpnum(2).getY())/2-1*sin(angle)});}
    else{carflag->setOnepoint(0,{carflag->getpnum(2).getX()-1*cos(angle),carflag->getpnum(2).getY()-1*sin(angle)});}
    for(int i=0;i<TRUCKNUM;i++){
        carfig[i]->draw();
    }
    carflag->draw();

}
void truck::rotate(double a) {
    for(int i=0;i<TRUCKNUM;i++){carfig[i]->rotate(a);
    }
    carflag->rotate(a);
    angle=(angle-a);

    if(angle>=360){angle=angle-360;}
    setGroupCenter((carfig[0]->getAnchor())+((getGroupCenter()-carfig[0]->getAnchor())>>a));
   // std::cout<<angle<<std::endl;
}
void truck::setAnchor(Vec a)  {
    for(int i=0;i<TRUCKNUM;i++){carfig[i]->setAnchor(a);}
    carflag->setAnchor(a);

}
void truck::moveByv() {
    setLinearV(VNUM);
    for(int i=0;i<TRUCKNUM;i++){carfig[i]->move(Linear_V);}
    carflag->move(Linear_V);
    //std::cout<<Linear_V.getX()<<"  "<<Linear_V.getY()<<std::endl;
    center=center+Linear_V;
}
truck::~truck() {

}

