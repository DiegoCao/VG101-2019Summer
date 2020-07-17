//
// Created by Dell on 2019/7/24.
//
#ifndef P3_COMBINE_GROUP_H
#define P3_COMBINE_GROUP_H
#include "p3.h"


class Group:public Figure{
protected:
    int parklot;
    Vec center;
    int direction;  // 1 from left to right： 2 from
    int Parkornot; //0 : not park, 1:
    int inornot;
    int rotateState;
    int carstate;
    int ParkPlot;//record
    double angle;
    //Vec V;
    double max_V;
    Vec Linear_V;
    double VNUM;
    Vec acceleration;
    double Angle_V;
    int parktime;   // the time that the object stay or not
public:
    Group();
    Group(double i_angle, double i_max_V, double i_Linear_V);
    void setAcceleration(double a){acceleration=a;}
    Vec getAcceleration(){return this->acceleration;}
    int getRotate(){return rotateState;}
    void setRotate(int n){rotateState=n;}
    int getDirection(){return direction;}
    double getMaxV(){return max_V;}
    void setMaxV(double maxV){max_V=maxV;}
    void setAngleV(double V){Angle_V=V;}
    double getAngleV(){return Angle_V;}
    void setVNUM(double v){VNUM=v;}
    void setLinearV(double V){Linear_V={V*cos(angle*M_PI/180),V*sin(angle*M_PI/180)};}
    double getangle(){return angle;}
    double getVNUM(){return VNUM;}
    Vec getLinearV(){return Linear_V;}

    virtual void draw(){};
    Vec getGroupCenter(){return center;}
    void setGroupCenter(Vec c){center=c;}
    void setParklot(int n){parklot=n;}
    int getParklot(){return parklot;}
    void setState(int n){carstate=n;}
    int getCarstate(){return carstate;}
    int getParktime(){ return parktime;}
    ~Group(){};
};


class UFO:public Group{
private:
    Circle* circ; SemiCircle* semi, *windows;
    Quad* quad; Ellipses* elli; UFOCurve* curv;
    Vec cen;
    int type;
    double time; Vec state1,state2,state_c;
public:
    UFO(Vec _cen);
    ~UFO();
    void draw();
    void move(Vec dir);
    void rotate(double angle);
    void spin();
    void zoom(double k);
    double get_t();
    Vec get_cen(){return cen;};
};
class ShiningStar{
private:
    Vec pos;
    double transparency;
    int state;
    int time;
    int size;
public:
    ShiningStar(Vec center,double size,int isnew=0);
    void draw();
    bool isdead();
};
class Teleport:public Group{
private:
    std::vector<ShiningStar> A;
    Vec vertex[8];
    int colorstate;
    int state[8];
    int count_step;
    int stop;
    int time;
    double r,g,b;
    double size;
    int lag;
    void changevertex();
    void addstar();
    void deletestar();
public:
    Teleport(Vec c);
    void draw();
    virtual void move(Vec dir){if(dir.getX()==0)return;};
    virtual void rotate(double a){if (a==0) return;};
};

#endif //P3_COMBINE_GROUP_H
