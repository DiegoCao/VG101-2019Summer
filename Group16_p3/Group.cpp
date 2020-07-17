//
// Created by Dell on 2019/7/24.
//


#include "Group.h"
#include <iostream>
#include <time.h>
using namespace std;
Group::Group() {
    max_V=4;
    //angle=0;
}


Teleport::Teleport(Vec c){
    colorstate=0;
    lag=rand()%50;
    time=0;
    stop=0;
    count_step=0;
    center=c;
    size=10;
    vertex[0]={1,2};vertex[1]={1,3};vertex[2]={2,4};vertex[3]={3,4};
    vertex[4]={4,3};vertex[5]={4,2};vertex[6]={3,1};vertex[7]={2,1};

    state[0]=1;state[1]=2;state[2]=4;state[3]=5;
    state[4]=7;state[5]=8;state[6]=10;state[7]=11;

    //每个周期有10个星星
    for (int i=0;i<5;i++){
        A.push_back(ShiningStar(center,size));
    }
    double color[4][3]={{0,0.5,1},{0.5,0.5,1},{0.5,0.5,0.5},{0,1,0.5}};
    int index=rand()%4;
    r=color[index][0];g=color[index][1];b=color[index][2];
}
void Teleport::changevertex() {
    Vec direction[12]={{0,0.05},{0,0.05},{0,0.05},{0.05,0},{0.05,0},{0.05,0},{0,-0.05},{0,-0.05},{0,-0.05},{-0.05,0},{-0.05,0},{-0.05,0}};
    for (int i=0;i<8;i++)
        vertex[i]=vertex[i]+direction[state[i]];
    count_step++;
    if (count_step%20==0){
        stop=8;
        for(int i=0;i<8;i++)
            state[i]=(state[i]+1)%12;
    }
}
void Teleport::draw(){
    Vec temp_vertex[8];
    //move to the center;
    for(int i=0;i<8;i++)
        temp_vertex[i]=vertex[i]+center-Vec{2.5,2.5};
    //change to the target size;
    for (int i=0;i<8;i++)
        temp_vertex[i]=center+(temp_vertex[i]-center)*size*(0.33333);


    glColor3f(r,g,b);
    glBegin(GL_POLYGON);
    for(int i=0;i<8;i++){
        glVertex2f(temp_vertex[i].getX(),temp_vertex[i].getY());
    }
    glEnd();

    while(lag!=0){
        changevertex();
        lag--;
    }

    if(stop!=0)
        stop--;
    else
        changevertex();

    time++;

    std::vector<ShiningStar>::iterator it;
    for(it=A.begin();it!=A.end();it++){
        it->draw();
    }

    deletestar();

    //每过五个单位时间加个星星。
    if(time%30==0)
        addstar();

    if(r>0 && g<1 && b<1 && colorstate==0){
        r-=0.005;g+=0.005;b+=0.005;
    }
    else if (r<1 && g>0 && b>0){
        colorstate=1;r+=0.005;g-=0.005;b-=0.005;
    }
    else colorstate=0;

}
void Teleport::addstar(){
    A.push_back(ShiningStar(center,size,1));
}
void Teleport::deletestar(){
    std::vector<ShiningStar>::iterator it;
    for(it=A.begin();it!=A.end();it++){
        if(it->isdead())
            A.erase(it);
    }

}

ShiningStar::ShiningStar(Vec center,double size_,int isnew){
    if (isnew==0)
        transparency=double(rand())/RAND_MAX;
    else
        transparency=0;
    size=size_;
    state=1;
    time=0;
    double s=size*0.66;
    double x_;double y_;
    x_=center.getX()+double(rand())/RAND_MAX*s-s/2;
    y_=center.getY()+double(rand())/RAND_MAX*s-s/2;
    pos=Vec(x_,y_);
}
void ShiningStar::draw(){
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );
    glColor4f(1,1,1,transparency);
    glPointSize(0.2*size);
    glBegin(GL_POINTS);
    glVertex2f(pos.getX(),pos.getY());
    glEnd();

    if (transparency<=1 && state==1){
        transparency+=0.01;}
    else if (transparency>0){
        state=0;
        transparency-=0.01;
    }
    else
        state=1;
    time++;
    glDisable(GL_BLEND);
}
bool ShiningStar::isdead() {
    if (transparency<0)
        return true;
    return false;
}