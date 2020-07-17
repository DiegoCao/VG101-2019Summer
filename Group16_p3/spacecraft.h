//
// Created by Dell on 2019/7/27.
//
#include "Group.h"
#ifndef P3_COMBINE_SPACECRAFT_H
#define P3_COMBINE_SPACECRAFT_H
class Spacecraft:public Group{
private:
    ColoredFigure *arr[7];
    double size;
    int state_z;
    int lag;
    void zoom();
public:
    Spacecraft(Vec center);
    void draw();
    void move(Vec dir);
    void rotate(double angle);
};
#endif //P3_COMBINE_SPACECRAFT_H
