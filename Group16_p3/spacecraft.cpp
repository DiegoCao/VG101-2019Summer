//
// Created by Dell on 2019/7/27.
//
#include "Curve.h"
#include "p3.h"
#include "spacecraft.h"
Spacecraft::Spacecraft(Vec cen) {
    lag=rand()%20;
    const double a=1;
    center=cen;
    size=a;
    state_z=0;

    arr[0]=new Quad(1,.0,.0,{-1.5*a+cen.getX(),-3*a+cen.getY()},{-1.5*a+cen.getX(),3*a+cen.getY()},{1.5*a+cen.getX(),3*a+cen.getY()},{1.5*a+cen.getX(),-3*a+cen.getY()});

    arr[1]=new Quad(.57,.878,1.0,{cen.getX()-0.25*a,cen.getY()},{cen.getX()-0.25*a,cen.getY()+0.75*a},{cen.getX()+0.25*a,cen.getY()+0.75*a},{cen.getX()+0.25*a,cen.getY()});

    arr[2]=new class::Rectangle(.87,.61,.325,{cen.getX()-1.5*a,cen.getY()},{cen.getX()-1.5*a,cen.getY()-3*a},{cen.getX()-3.5*a,cen.getY()-3*a});
    arr[3]=new class::Rectangle(.87,.61,.325,{cen.getX()+1.5*a,cen.getY()},{cen.getX()+1.5*a,cen.getY()-3*a},{cen.getX()+3.5*a,cen.getY()-3*a});

    arr[4]=new class::Rectangle(.7,.77,.53,{cen.getX(),cen.getY()+5*a},{cen.getX()-1.5*a,cen.getY()+3*a},{cen.getX()+1.5*a,cen.getY()+3*a});

    Vec vec[4]={{cen.getX(),cen.getY()-9*a},{cen.getX()-a,cen.getY()-5*a},{cen.getX(),cen.getY()-4*a},{cen.getX()+a,cen.getY()-5*a}};
    arr[5]=new GradientCurve(4,vec);

    arr[6]=new Quad(0,0,0.5,{cen.getX()-1.25*a,cen.getY()-3*a},{cen.getX()-1.5*a,cen.getY()-5*a},{cen.getX()+1.5*a,cen.getY()-5*a},{cen.getX()+1.25*a,cen.getY()-3*a});



    for (int i=0;i<7;i++)
    {
        arr[i]->setAnchor(cen);
    }

}
void Spacecraft::move(Vec dir) {
    for(int i=0;i<7;i++)
        arr[i]->move(dir);
}
void Spacecraft::rotate(double angle) {
    for(int i=0;i<7;i++)
        arr[i]->rotate(angle);
}
void Spacecraft::zoom() {
    double k=1;
    if (size>0.7 && state_z ==0)
    {   size*=0.99;
        k=0.99;
    }
    else if (size<=1.5)
    {
        state_z=1;
        size*=1.01;
        k=1.01;
    }
    else state_z=0;


    for (int i=0;i<7;i++)
        arr[i]->zoom(k);
}
void Spacecraft::draw(){
    if(lag!=0){
        for (int i=0;i<7;i++)
            zoom();
        lag--;
    }
    for (int i=0;i<7;i++)
        arr[i]->draw();
    zoom();

}