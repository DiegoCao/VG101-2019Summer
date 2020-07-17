//
// Created by Dell on 2019/7/28.
//

#ifndef P3_COMBINE_PARK_H
#define P3_COMBINE_PARK_H

#include "Group.h"
#include "car.h"
#include "spacecraft.h"
class Park{
private:
    std::vector<Quad>Frame;
    std::vector<Rect>Lots;
    std::vector<Rect>Obstacle;
    std::vector<Spacecraft>rockets;
    std::vector<truck>Cars;
    std::vector<UFO>ufos;
    std::vector<Teleport>teles;
    std::vector<Rect>Barrier;
    int alltime;
    int detectin;
    int detectout;
    int In;
    int Out;
    int allcarin;
    int carstate;
    int MoveInlabel;
    int outcar;
    int carnum;int UFOnum; int Craftnum;int doornum;
public:
    Park(int num);
    void one_loop(int num);
    void in_loop(int num);
    void out_loop(int num);
    void draw();
    int getALLcar(){return allcarin;}
    ~Park(){Frame.clear();Lots.clear();}
};
#endif //P3_COMBINE_PARK_H
