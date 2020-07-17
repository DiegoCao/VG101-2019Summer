//
// Created by Dell on 2019/7/23.
//

#ifndef P3_COMBINE_CAR_H
#define P3_COMBINE_CAR_H

#include <ctime>
#include "Group.h"

class truck:public Group{
private:

    ColoredFigure *carfig[8];
    Quad *carflag;
    time_t arrival_time;
    //ColoredFigure *carflag[2];
public:
    truck();
    truck(Vec ce);
    void draw();
    void move(Vec a);
    void moveByv();
    void setAnchor(Vec a);
    void rotate(double a);
    void set_arrival(){arrival_time=time(NULL);}
    time_t get_arrival(){return arrival_time;}
    ~truck();
};
class saloon:public Group{
private:
    Vec GroupAnchor;
    std::vector<ColoredFigure>carfig;
public:
    saloon();
    saloon(Vec ce);
    void draw();
    void move(Vec ce);
    void setAnchor(Vec a);
    void rotate(double angle);

};



#endif //P3_COMBINE_CAR_H
