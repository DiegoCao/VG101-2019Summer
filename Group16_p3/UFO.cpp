#include "p3.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#elif _WIN32
#include <windows.h>
#include <GL/freeglut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <time.h>
#include <math.h>

#define R 4.2
#define D 0.1 * R
using namespace std;

#include "Group.h"
#include "p3.h"
UFO::UFO(Vec _cen)
{
    cen = _cen;
    time = 0.0;
    circ = new Circle[12];
    semi = new SemiCircle[1];
    windows = new SemiCircle[12];
    elli = new Ellipses[1];
    curv = new UFOCurve[4];
    type = -1;
    state1 = Vec{cen.getX(),cen.getY()+R};
    for (int i = 0; i < 12; ++i)
    {
        circ[i] = Circle(0.75, .5*sin(time+i+20), .0, {cen.getX(),cen.getY()+R*0.099}, R * 0.099);
        circ[i].setAnchor({cen.getX(), cen.getY() + R});
        circ[i].rotate(60 * i);

        windows[i] = SemiCircle(1.0, 0.8, 0.2, {cen.getX()-R*0.1,cen.getY()+R*0.44},{cen.getX()+R*0.1,cen.getY()+R*0.32});
        windows[i].setAnchor({cen.getX(), cen.getY() + 0.1*R});
        windows[i].rotate(60 * i);
    }

    semi[0] = SemiCircle(0.7, 0.7, 0.77, {cen.getX()-R, cen.getY()}, {cen.getX()+R, cen.getY()});
    //semi[0].move(cen);

    elli[0] = Ellipses(0.3, 0.7, 0.0, cen, R * 2, R * 0.5);

    for (int i = 2; i < 4; ++i)
    {
        curv[i] = UFOCurve(1.0, i / 4, 0.4, {cen.getX() + (elli[0].get_p3() - cen).getX() , cen.getY() + (elli[0].get_p3() - cen).getY() + D *R}, cen, 70);
        curv[i].move({0.0, -i * 0.1 * R});
    }
    for (int i = 0; i < 2; ++i)
    {
        curv[i] = UFOCurve(0.0, i / 4, 1.0,{cen.getX() - (elli[0].get_p3() - cen).getX(), cen.getY() - (elli[0].get_p3() - cen).getY() - D * R}, cen, 70);
        curv[i].move({0.0, +i * 0.1 * R});
    }
}

void UFO::move(Vec dir)
{
    for (int i = 0; i < 12; ++i)
    {
        circ[i].move(dir);
        windows[i].move(dir);
        if (i == 0)
            semi[0].move(dir), elli[0].move(dir);
        if (i<4)
            curv[i].move(dir);
    }
    cen = cen + dir;
    state1=state1+dir;
}

// everytime before rotate: setAnchor
void UFO::rotate(double angle)
{

    for (int i = 0; i < 12; ++i)
    {
        /*  circ[i].setAnchor(getAnchor());
         circ[i].rotate(angle); */

        //if (i<3){
        /*  windows[i].setAnchor(getAnchor());
         windows[i].rotate(angle); */
        //}

        if (i == 0)
        {
            semi[0].setAnchor(getAnchor());
            semi[0].rotate(angle);
            elli[0].setAnchor(getAnchor());
            elli[0].rotate(angle);
        }

        if (i < 2)
        {
            curv[i].setAnchor(getAnchor());
            curv[i].rotate(angle);
        }
        if (i >= 2 && i < 4)
        {
            curv[i].setAnchor(getAnchor());
            curv[i].rotate(angle);
        }
    }

    cen = getAnchor() + ((cen - getAnchor()) >> angle);
    //state1 = getAnchor() + ((state1 - getAnchor()) >> angle);
}

void UFO::spin()
{
    setAnchor(state1);
    rotate(1);
    Vec ref({1.0, 0.0});
    //double beta = ((elli[0].get_p3() - cen) < ref);
    for (int i = 0; i < 2; ++i)
    {
        curv[i].setAnchor(cen);
        curv[i].rotate(10);
    }
    for (int i = 2; i < 4; ++i)
    {
        curv[i].setAnchor(cen);
        curv[i].rotate(10);
    }

}

void UFO::zoom(double k)
{

    for (int i = 0; i < 12; ++i)
    {
        circ[i].setAnchor(getAnchor());
        circ[i].zoom(k);

        windows[i].setAnchor(getAnchor());
        windows[i].zoom(k);

        elli[0].setAnchor(getAnchor());
        elli[0].zoom(k);

        if (i < 4)
        {
            curv[i].setAnchor(getAnchor());
            curv[i].zoom(k);
        }
    }

    cen = getAnchor() + (cen - getAnchor()) * k;
    state1 = getAnchor() + (state1 - getAnchor()) * k;
}

void UFO::draw()
{
    spin();
    Vec ref;
    ref = ((elli[0].get_p3()-cen)*1.5+cen);

    for (int i = 0; i < 4; ++i)
        curv[i].draw();

    elli[0].draw();
    semi[0].draw();

    for (int i = 0; i < 12; ++i)
    {
        if (((windows[i].getp0()- ref) < (cen - ref)) > -M_PI * 1.2 / 4 && ((windows[i].getp0() - ref) < (cen - ref)) < M_PI * 1.2 / 4)
            windows[i].draw();
    }
    for (int i = 0; i < 12; ++i)
    {
        if ((fabs((circ[i].get_cen() - ref) < (cen - ref))) < M_PI * 1.6 / 4)
            circ[i].draw();
    }
    time = time + 0.01;
}

double UFO::get_t() { return time; }

UFO::~UFO()
{

}