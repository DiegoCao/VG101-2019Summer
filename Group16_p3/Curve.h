//
// Created by Dell on 2019/7/27.
//
#include "p3.h"
#ifndef P3_COMBINE_CURVE_H
#define P3_COMBINE_CURVE_H
class Curve:public ColoredFigure{
protected:
    int num_vertex;
    Vec *arr_vertex;
public:
    Curve(double red,double green,double blue,int num_input,Vec *arr_input);
    virtual void draw();
    void move(Vec dir);
    void rotate(double angle);
    virtual void zoom(double k);
};

class GradientCurve:public Curve{
private:
    int log;
    int changestate;
public:
    GradientCurve(int num_input, Vec *arr_input):Curve(0,0,0,num_input,arr_input){log=0,changestate=0;}
    void draw();
    void zoom(double k);
};
#endif //P3_COMBINE_CURVE_H
