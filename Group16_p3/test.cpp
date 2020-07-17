#ifdef __APPLE__
#include <GLUT/glut.h>
#elif _WIN32
#include <windows.h>
#include <GL/freeglut.h>
#else
#include <GL/freeglut.h>
#endif
#include "p3.h"
#include "car.h"
#include "Park.h"
#include "spacecraft.h"
#include <iostream>
void TimeStep(int n)
{
    glutTimerFunc(n, TimeStep, n); glutPostRedisplay();
}
class Parkinglot{
private:
    int n;
public:
    Parkinglot(){std::cout<<"Please enter the number of cars:"<<std::endl;std::cin>>n;}
    int getnum(){return n;}
};
void MyTestFunction()
{
    using namespace std;


    glClear(GL_COLOR_BUFFER_BIT);
    static int initnum=0;
    if(initnum==0){
        cout<<"please enter the possible parking lots num: 12 or 16"<<endl;
        cin>>initnum;
        while(initnum!=12&&initnum!=16){
            cout<<"please reinput"<<endl;
            cin.clear();
            cin>>initnum;
        }
    }
    static Park aa(initnum);
    if(aa.getALLcar()==0){aa.in_loop(initnum);}
    else if(aa.getALLcar()==1){aa.out_loop(initnum);}
    aa.draw();
    glFlush();
}

int main(int argc,char *argv[]){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutInitWindowSize(1400,900);
    glutCreateWindow("My Spacecraft");
    glClearColor(0,0,0,0);
    //important
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-120,120,-80,80);
    //important
    glutDisplayFunc(MyTestFunction);
    glClear(GL_COLOR_BUFFER_BIT);
    glutTimerFunc(25, TimeStep, 25);
    glutMainLoop();
}