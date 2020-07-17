#include "generic_parkinglot.h"
#include <iostream>
#include <time.h>
using namespace std;
Vehicle::Vehicle(){
    //to randomly determine the type of the coming vehicle
    T[0]="Van";T[1]="Car";T[2]="MotorBike";T[3]="Bike";
    type=rand()%4;

}
int Vehicle::Getprice(){
    int ratio[4]={7,5,2,1};
    return ratio[type]*parking_duration;
}
void Vehicle::Arrival_ticket(){
    cout<<"==========================IN======================="<<endl;
    cout<<"Time of arrival: "<<ctime(&arrival_time);
    cout<<"Type of the vehicle: "<<T[type]<<endl;
    cout<<"The available empty slot: "<<"floor->"<<floor<<";"<<"slot->"<<slot<<"["<<T[type]<<"]"<<endl;
    cout<<"==========================IN======================="<<endl<<endl;
}
void Vehicle::Depart_ticket() {
    cout<<"                                                    ===============OUT==============="<<endl;
    cout<<"                                                    Time spent in the parking lot: "<<parking_duration<<endl;
    cout<<"                                                    Type of the vehicle: "<<T[type]<<endl;
    cout<<"                                                    Price :"<<Getprice()<<endl;
    cout<<"                                                    ===============OUT==============="<<endl<<endl;
}
bool Vehicle::leave(){
    if((time(NULL)-arrival_time)>=parking_duration)
        return true;
    return false;
}

//parkinglot
Parkinglot::Parkinglot() {
    //I actually design a very small parking lot so that it can show more situations
    //index [0],[1],[2],[3] means the total slot for different vehicles;
    for(int i=0;i<4;i++){
        slot[0][i]=2;slot[1][i]=1;
    }
}
void Parkinglot::inVehicle(Vehicle v){
    slot[v.Getfloor()-1][v.Gettype()]--;
    vehicle.push_back(v);
}
void Parkinglot::outVehicle(vector<Vehicle>::iterator it) {
    slot[(*it).Getfloor()-1][it->Gettype()]++;
    vehicle.erase(it);
}
void Parkinglot::outVehicles(){
    vector<Vehicle>::iterator it;
    for(it=vehicle.begin();it!=vehicle.end();it++){
        if((*it).leave()){
            outVehicle(it);
            (*it).Depart_ticket();
        }
    }
}
bool Parkinglot::ifempty(Vehicle v) {


    if (slot[0][v.Gettype()]!=0 || slot[1][v.Gettype()]!=0){
        v.SetArrival_time();
        if(slot[0][v.Gettype()]!=0){
            v.Setfloor(1);
            v.Setslot(3-slot[0][v.Gettype()]);
        }
        else{
            v.Setfloor(2);
            v.Setslot(2-slot[1][v.Gettype()]);
        }
        inVehicle(v);
        v.Arrival_ticket();
        return true;
    }
    return false;

}

