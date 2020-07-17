#include <iostream>
#include <vector>
#include <time.h>
#include <queue>
#include "generic_parkinglot.h"
using namespace std;
int main() {

    Parkinglot pl;
    //在停车场外排队的车
    queue<Vehicle> q;
    bool flag=1;
    time_t start=time(NULL);
    time_t interval=2;//每过5秒钟来一辆车；
    //first vehicle;
    while(time(NULL)-start<60){
        //每过五秒，生成一辆车，放入queue中
        if ((time(NULL)-start)%interval==0 && flag==1){
            flag=0;
            Vehicle v;
            q.push(v);
        }
        if ((time(NULL)-start)%interval!=0)
            flag=1;

        pl.outVehicles();
        if (!q.empty() && pl.ifempty(q.front()))
            q.pop();
        if (!q.empty() && (time(NULL)-start)%interval==0 && flag==1)
            cout<<"Parking lot is full and "<<q.size()<<" vehicle is(are) waiting....."<<endl;

        cout.flush();
    }
    cout<<"==============END=============";
}