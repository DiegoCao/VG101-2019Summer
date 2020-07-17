//
// Created by zhanhuizhou on 2019-07-29.
//

#ifndef NORMAL_PARKING_LOT_GENERIC_PARKINGLOT_H
#define NORMAL_PARKING_LOT_GENERIC_PARKINGLOT_H
#include <string>
#include <vector>
#include <time.h>
#include <string>
using namespace std;

class Vehicle{
private:
    int type;
    string T[4];
    time_t arrival_time;
    time_t parking_duration;
    int floor;
    int slot;
    int Getprice();
public:
    Vehicle(); //随机生成
    void Setfloor(int f){floor=f;}
    void Setslot(int s){slot=s;}
    void SetArrival_time(){arrival_time=time(NULL);parking_duration=rand()%10+5;};
    int Gettype(){return type;}
    int Getfloor(){return floor;}
    bool leave();
    void Arrival_ticket();
    void Depart_ticket();
};

class Parkinglot{
private:
    vector<Vehicle> vehicle;
    //2层楼，4种车型剩余车位
    int slot[2][4];
    void inVehicle(Vehicle v);
    void outVehicle(vector<Vehicle>::iterator it);
public:
    Parkinglot();
    bool ifempty(Vehicle v); //检验是否有车辆出去
    void outVehicles();
};
#endif //NORMAL_PARKING_LOT_GENERIC_PARKINGLOT_H
