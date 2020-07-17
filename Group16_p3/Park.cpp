//
// Created by Dell on 2019/7/28.
//

#include "Park.h"
#include <random>       // std::default_random_engine
#include <chrono>
#include <iostream>
#include <algorithm>
#include "time.h"
#include<cstdlib>
const double criteria[3][10]={{-37,-17,3,23,43,63,0,0,0,0},{-57,-37,-17,3,23,43,63,83,0,0},{0,0,0,0,0,0,0,0,0,0}};
double outanchor[2]={65,85};
Vec Invec[3]={{-69,-40},{-87,-40},{-107,-40}};
Vec Invec2[3]={{-69,15},{-87,15},{-107,25}};


const Vec init1[2][8]={{{-50,-45},{-30,-45},{-10,-45},{10,-45},{30,-45},{50,-45},{0,0},{0,0}},{{-70,-45},{-50,-45},{-30,-45},{-10,-45},{10,-45},{30,-45},{50,-45},{70,-45}}};
const Vec init2[2][8]={{{-50,45},{-30,45},{-10,45},{10,45},{30,45},{50,45},{0,0},{0,0}},{{-70,45},{-50,45},{-30,40},{-10,45},{10,45},{30,45},{50,45},{70,45}}};



void createRand(int a[4],int num){
    srand((unsigned)time(NULL));
    int count=0;
    int max=num/4;
    for(int i=1;i<4;i++){
        a[i]=rand()%(max-1)+2;
        count+=a[i];
    }
    a[0]=num-count;

}


const double deltalength=10;
Park::Park(int num) {
    double hlength[3]={80,100,120};
    double halfwidth=55;

    double fwid=1;
    int label=0;
    const double lotlength=20;
    if(num==12){label=0;}
    else if(num==16)label=1;
    else if(num==20)label=2;
    Quad a(1,1,1,{-hlength[label]-fwid-deltalength,-halfwidth-fwid},{-hlength[label]-fwid-deltalength,halfwidth+fwid},{-hlength[label]-deltalength,halfwidth},{-hlength[label]-deltalength,-halfwidth});
    Quad b(1,1,1,{-hlength[label]-fwid-deltalength,halfwidth},{-hlength[label]-fwid-deltalength,halfwidth+fwid},{hlength[label]+fwid-lotlength+deltalength,halfwidth+fwid},{hlength[label]+fwid-lotlength+deltalength,halfwidth});
    Quad c(1,1,1,{hlength[label]+deltalength,-halfwidth-fwid},{hlength[label]+deltalength,halfwidth+fwid},{hlength[label]+fwid+deltalength,halfwidth+fwid},{deltalength+hlength[label]+fwid,-halfwidth-fwid});
    Quad d(1,1,1,{-hlength[label]-fwid+lotlength-deltalength,-halfwidth-fwid},{-hlength[label]-fwid+lotlength-deltalength,-halfwidth},{hlength[label]+fwid+deltalength,-halfwidth},{deltalength+hlength[label]+fwid,-halfwidth-fwid});
    double Bcolor[3]={1,0.4,0.4};
    Rect e(Bcolor,{-hlength[label]+7-deltalength,-halfwidth},1,10);
    e.setAnchor({-hlength[label]-deltalength,-halfwidth});
    Rect f(Bcolor,{hlength[label]-7+deltalength,halfwidth},1,10);
    f.setAnchor({hlength[label]+deltalength,halfwidth});
    Barrier.push_back(e);Barrier.push_back(f);
    double ocolor[3]={0.8,0.8,0.8};

    Rect p(ocolor,{0,0},5,hlength[label]-20);
    Obstacle.push_back(p);
    const double lwid=8;
    const double lotsize[2]={12,0.5};
    for(int i=0;i<(int)(num/2)+1;i++){
        double color[3]={0.8,0.8,0.8};
        Rect m(color,{-hlength[label]+(i+1)*lotlength,-halfwidth+lwid},lotsize[0],lotsize[1]);
        Rect n(color,{-hlength[label]+(i+1)*lotlength,halfwidth-lwid},lotsize[0],lotsize[1]);
        //std::cout<<"done"<<std::endl;
        Lots.push_back(m);
        Lots.push_back(n);
    }
    Frame.push_back(a);Frame.push_back(b);Frame.push_back(c);Frame.push_back(d);
    srand((unsigned)time(NULL));
    int alloarray[4]={0,0,0,0};
    createRand(alloarray,num);
    std::vector<int>plotallo;

    for(int i=0;i<num;i++){plotallo.push_back(i);}
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle (plotallo.begin(),plotallo.end(), std::default_random_engine(seed));
    int allo=0;
    for(int i=0;i<alloarray[0];i++){
        truck temp({-hlength[label]+4-deltalength,-halfwidth-20-10});
        temp.setParklot(plotallo[allo]);
        temp.rotate(-90);
        temp.move({2,0});
        Cars.push_back(temp);
        allo++;
    }
    for(int i=0;i<alloarray[1];i++){
        Vec ufomove;
        if(plotallo[allo]>=num/2){ufomove=init2[label][plotallo[allo]-num/2];
            ufomove={ufomove.getX(),ufomove.getY()-3.8};
        }
        else ufomove=init1[label][plotallo[allo]];

        UFO temp(ufomove);
        ufos.push_back(temp);
        allo++;
    }
    for(int i=0;i<alloarray[2];i++){
        Vec ufomove;
        if(plotallo[allo]>=num/2)ufomove=init2[label][plotallo[allo]-num/2];
        else ufomove=init1[label][plotallo[allo]];

        Spacecraft temp(ufomove);
        rockets.push_back(temp);
        allo++;
    }
    for(int i=0;i<alloarray[3];i++){
        Vec ufomove;
        if(plotallo[allo]>=num/2)ufomove=init2[label][plotallo[allo]-num/2];
        else ufomove=init1[label][plotallo[allo]];
        Teleport temp(ufomove);
        teles.push_back(temp);
        allo++;
    }


    In=0;
    Out=0;
    allcarin=0;
    MoveInlabel=-1;
    detectin=1;
    detectout=1;
    outcar=-1;
    alltime=0;

}
void Park::draw() {
    for(unsigned int i=0;i<Frame.size();i++){Frame[i].draw();}
    for(unsigned int i=0;i<Lots.size();i++){Lots[i].draw();}
    for(unsigned int i=0;i<Barrier.size();i++){Barrier[i].draw();}
    for(int i=0;i<(int)teles.size();i++){teles[i].draw();}
    for(unsigned int i=0;i<Cars.size();i++){Cars[i].draw();}
    for(int i=0;i<(int)ufos.size();i++){ufos[i].draw();}
    for(int i=0;i<(int)rockets.size();i++){rockets[i].draw();}
    for(int i=0;i<(int)Obstacle.size();i++){Obstacle[i].draw();}

}
void Park::in_loop(int num) {
    if(Cars.size()==0)return;

    int numlabel;
    if(num==12){numlabel=0;}if(num==14){numlabel=2;}if(num==16){numlabel=1;}  //sorry about yahang..
    int n=(num/2);
    alltime++;

    if(detectin==1&&MoveInlabel<(int)Cars.size()){

        detectin=0;
        MoveInlabel++;
        if(MoveInlabel==(int)Cars.size()){
            //std::cout<<"allcarin";
            allcarin=1;
            return;
        }
        time_t arrivaltime=time(NULL);
        Cars[MoveInlabel].set_arrival();
        using namespace std;
        std::cout<<"===============IN============="<<std::endl;
        std::cout<<"Time of arrival: "<<ctime(&arrivaltime);
        cout<<"Type of the vehicle: "<<"truck"<<endl;
        cout<<"Nums of Slot left :"<<Cars.size()-MoveInlabel<<endl;
        cout<<"The available empty slot label ["<<Cars[MoveInlabel].getParklot()+1<<"]"<<endl;
        cout<<"===============IN============="<<endl<<endl;
        Barrier[0].setAngle(0);
        Cars[MoveInlabel].setState(1);
    }

    if(Cars[MoveInlabel].getRotate()==0)
    {   Cars[MoveInlabel].moveByv();
        if(Cars[MoveInlabel].getGroupCenter().getY()>-65&&In==0&&Cars[MoveInlabel].getCarstate()==1){
            Cars[MoveInlabel].setVNUM(0);
            Barrier[0].rotate(-1);
            if(Barrier[0].getAngle()>=M_PI/2){
                // std::cout<<"Barrier angle"<<Barrier[0].getAngle()<<std::endl;
                In=1;
                Cars[MoveInlabel].setState(2);
            }
        }
        if(MoveInlabel==(int)Cars.size()){return;}
        if(Cars[MoveInlabel].getCarstate()==2){
            Cars[MoveInlabel].setVNUM(0.5);
            if(Cars[MoveInlabel].getParklot()>=n&&Cars[MoveInlabel].getGroupCenter().getY()>20){
                Cars[MoveInlabel].setVNUM(0);
                Cars[MoveInlabel].setAnchor(Invec2[numlabel]);   // the car that goes to the row on top
                Cars[MoveInlabel].setRotate(1);
            }
            else if(Cars[MoveInlabel].getParklot()<n&&Cars[MoveInlabel].getGroupCenter().getY()>-45){
                Cars[MoveInlabel].setVNUM(0);
                Cars[MoveInlabel].setAnchor(Invec[numlabel]);
                Cars[MoveInlabel].setRotate(1);
            }
        }
        else if(Cars[MoveInlabel].getCarstate()==3){
            if(Barrier[0].getAngle()>0){Barrier[0].rotate(1);}

            if((Cars[MoveInlabel].getParklot()<n)&&Cars[MoveInlabel].getGroupCenter().getX()>criteria[numlabel][Cars[MoveInlabel].getParklot()]){
                Cars[MoveInlabel].setRotate(2);
                Cars[MoveInlabel].setAnchor({criteria[numlabel][Cars[MoveInlabel].getParklot()],-40});
                Cars[MoveInlabel].setAngleV(-0.5);
            }
            else if(Cars[MoveInlabel].getParklot()>=n&&Cars[MoveInlabel].getGroupCenter().getX()>criteria[numlabel][Cars[MoveInlabel].getParklot()-n]){
                Cars[MoveInlabel].setRotate(2);
                Cars[MoveInlabel].setAngleV(0.5);
                Cars[MoveInlabel].setAnchor({criteria[numlabel][Cars[MoveInlabel].getParklot()-n],45});  //the car that goes the top row
            }
        }
        else if(Cars[MoveInlabel].getCarstate()==5){
            detectin=1;
            In=0;
        }

    }
    else if(Cars[MoveInlabel].getRotate()!=0){
        if(Cars[MoveInlabel].getRotate()==1){
            Cars[MoveInlabel].rotate(1);
            if(Cars[MoveInlabel].getangle()<=0){
                Cars[MoveInlabel].setState(3);
                Cars[MoveInlabel].setRotate(0);
                Cars[MoveInlabel].setVNUM(0.5);
            }
        }
        else{
            if(Barrier[0].getAngle()>0){Barrier[0].rotate(1);}
            Cars[MoveInlabel].rotate(Cars[MoveInlabel].getAngleV());
            if(Cars[MoveInlabel].getangle()>=90&&(Cars[MoveInlabel].getParklot()<n)){
                Cars[MoveInlabel].setAngleV(0);
                Cars[MoveInlabel].setState(5);
                Cars[MoveInlabel].setRotate(0);
                Cars[MoveInlabel].setVNUM(0);

            }
            else if(Cars[MoveInlabel].getangle()<=-90&&(Cars[MoveInlabel].getParklot()>=n)){
                Cars[MoveInlabel].setAngleV(0);
                Cars[MoveInlabel].setState(5);
                Cars[MoveInlabel].setRotate(0);
                Cars[MoveInlabel].setVNUM(0);


            }
        }
    }
    if(num<0){return;}
}
void Park::out_loop(int num){
    if(allcarin==0)return;
    int n=num/2;
    int numlabel=0;
    if(num==12){numlabel=0;}if(num==14){numlabel=2;}if(num==16){numlabel=1;}
    alltime++;   // outcar: the label for the outcar
    if(outcar>=(int)Cars.size()){
        return;
    }

    if(detectout==1){
        detectout=0;
        outcar++;
        if(outcar>=(int)Cars.size()){
            return;
        }

        detectout=0;
        Barrier[1].setAngle(0);
        Cars[outcar].setRotate(1);
        if(Cars[outcar].getParklot()<n){
            //std::cout<<"loop in";
            Cars[outcar].setAnchor({criteria[numlabel][Cars[outcar].getParklot()],-40});
        }
        else if(Cars[outcar].getParklot()>=n){
            //std::cout<<"loop2 in";
            Cars[outcar].setAnchor({criteria[numlabel][Cars[outcar].getParklot()-n],40});
        }
    }
    if(Cars[outcar].getRotate()==0){
        switch (Cars[outcar].getCarstate()) {
            case 10:
                Cars[outcar].moveByv();
                if(Cars[outcar].getGroupCenter().getX()>outanchor[numlabel]){
                    Cars[outcar].setRotate(2);
                    if(Cars[outcar].getParklot()>=n){Cars[outcar].setAnchor({outanchor[numlabel],40});}
                    else if(Cars[outcar].getParklot()<n){Cars[outcar].setAnchor({outanchor[numlabel],-10});}
                }
                break;
            case 11:
                Cars[outcar].moveByv();
                if(Cars[outcar].getGroupCenter().getY()>40&&Barrier[1].getAngle()>=-M_PI_2){
                   // std::cout<<"Barii ange"<<Barrier[1].getAngle()<<std::endl;// the variable needs to be change.
                    Barrier[1].rotate(1);
                    Cars[outcar].setVNUM(0);
                }
                else if(Cars[outcar].getGroupCenter().getY()>40&&Barrier[1].getAngle()<=-M_PI_2){
                    Cars[outcar].setVNUM(0.5);
                    if(Cars[outcar].getGroupCenter().getY()>70){
                        Cars[outcar].setState(12);
                    }
                }
                break;
            case 12:
                Cars[outcar].moveByv();
                if(Barrier[1].getAngle()<=0){Barrier[1].rotate(-1);}
                if(Cars[outcar].getGroupCenter().getY()>90){Cars[outcar].setState(13);}
                break;
            case 13:
                if(Barrier[1].getAngle()<=0){Barrier[1].rotate(-1);}
                else{detectout=1;
                    using namespace std;
                    time_t parking_time=time(NULL)-Cars[outcar].get_arrival();
                    cout<<"                         ===============OUT==============="<<endl;
                    int price=10*parking_time;
                    cout<<"                         Time spent in the parking lot: "<<parking_time<<" h"<<endl;
                    cout<<"                         Type of the vehicle: truck"<<endl;
                    cout<<"                         Price :"<<price<<" RMB"<<endl;
                    cout<<"                         ===============OUT==============="<<endl<<endl;
                }
        }
    }
    else if(Cars[outcar].getRotate()!=0){
        if(Cars[outcar].getRotate()==1){
            //std::cout<<"done";
            if(Cars[outcar].getParklot()<n) {
                Cars[outcar].rotate(1);
                if (Cars[outcar].getangle() <= 0) {
                    Cars[outcar].setState(10);
                    Cars[outcar].setRotate(0);
                    Cars[outcar].setVNUM(0.5);
                }
            }
            else if(Cars[outcar].getParklot()>=n){
                Cars[outcar].rotate(-1);
                if (Cars[outcar].getangle() >=0) {
                    Cars[outcar].setState(10);
                    Cars[outcar].setRotate(0);
                    Cars[outcar].setVNUM(0.5);
                }
            }
        }
        else if(Cars[outcar].getRotate()==2){
            if(Cars[outcar].getParklot()<n){
                Cars[outcar].rotate(-1);
                if(Cars[outcar].getangle()>=90){
                    Cars[outcar].setState(11);
                    Cars[outcar].setVNUM(0.5);
                    Cars[outcar].setRotate(0);
                }
            }
            else if(Cars[outcar].getParklot()>=n){
                Cars[outcar].rotate(-1);
                if(Cars[outcar].getangle()>=90){
                    Cars[outcar].setState(11);
                    Cars[outcar].setVNUM(0.5);
                    Cars[outcar].setRotate(0);
                }
            }

        }
    }
    if(num<0)return;
}
































