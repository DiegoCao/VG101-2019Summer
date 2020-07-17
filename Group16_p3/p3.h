//
// Created by zhanhuizhou on 2019-07-21.
//

#ifndef P3_P3_H
#define P3_P3_H
#include "p3.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#elif _WIN32
#include <windows.h>
#include <GL/freeglut.h>
#else
#include <GL/freeglut.h>
#endif
#include <math.h>
#include <vector>
//vector
class Vec{
private:
    double x,y;
public:
    Vec(double x_=0,double y_=0){
        x=x_;y=y_;
    }
    double getX() {return x;}
    double getY() {return y;}
    void set(double x_, double y_){
        x=x_; y=y_;
    }
    //
    Vec operator+ (Vec v){
        return Vec(x+v.getX(),y+v.getY());
    }
    Vec operator- (Vec v){
        return Vec(x-v.getX(),y-v.getY());
    }
    Vec operator* (double k){
        return Vec(k*x,k*y);
    }
    double operator* (Vec v){
        return x*v.getX()+y*v.getY();
    }
    Vec operator<<(double a){
        double the=a*M_PI/180;
        double x_=x*cos(the)-y*sin(the);
        double y_=y*cos(the)+x*sin(the);
        return Vec(x_,y_);
    }
    Vec operator>> (double a){
        return *this<<(-a);
    }
    double operator< (Vec v){
        double dot=v.getX()*x+v.getY()*y;
        double norm1=sqrt(x*x+y*y),norm2=sqrt(v.getX()*v.getX()+v.getY()*v.getY());
        return acos(dot/(norm2*norm1));
    }
};


//abstract base class
class Figure{
protected:
    Vec anchor;

public:
    //Figure() : anchor(0,0) {};
    Vec getAnchor() {return anchor;}
    //Vec getCenter(){return center;}
    //Vec setCenter(Vec a){return a;}
    void setAnchor(Vec a) {anchor=a;}

    virtual void move(Vec dir)=0;
    virtual void rotate(double angle) =0;
    //virtual ~Figure();
    //
};


//inherited abstract class 1
class ColoredFigure:public Figure{
protected:
    double r,g,b;
public:
    ColoredFigure(){};
    virtual void draw()=0;
    virtual void zoom(double k) =0;
    void Paint(double newr, double ng, double nb){r=newr;g=ng;b=nb;}
    virtual ~ColoredFigure(){};
};
//inherited abstract class 2



class Circle:public ColoredFigure {
private:
    Vec cen;
    double ra;
public:
    Circle();
    Circle(double red,double green,double blue,Vec center,double radius);
    void setCircle(double red,double green,double blue,Vec center,double radius);
    void draw();
    void move(Vec dir);
    void rotate(double angle);
    void zoom(double k);
    Vec get_cen();
    ~Circle();
};
class SemiCircle:public ColoredFigure{
private:
    //直径的两个端点
    Vec p[2];
public:
    SemiCircle();
    SemiCircle(double red,double green,double blue,Vec pt1, Vec pt2);
    void draw();
    void move(Vec dir);
    void rotate(double angle);
    void zoom(double k);
    Vec getp0();
    //~SemiCircle();
};
class Rectangle:public ColoredFigure{
private:
    Vec p[3];
public:
    Rectangle(double red,double green,double blue,Vec pt1,Vec pt2,Vec pt3);
    void draw();
    void move(Vec dir);
    void rotate(double angle);
    void zoom(double k);
};
class Quad:public ColoredFigure{
private:
    //四个顶点
    Vec p[4];
    double RotateAngle;
public:
    Quad();
    Quad(double red,double green,double blue,Vec pt1,Vec pt2,Vec pt3,Vec pt4);
    void changeValue(Vec pt1,Vec pt2,Vec pt3,Vec pt4){p[0]=pt1,p[1]=pt2;p[2]=pt3;p[3]=pt4;};
    void draw();
    void move(Vec dir);
    void rotate(double angle);
    void zoom(double k);
    void setAngle(double angle){RotateAngle=angle;}
    void setOnepoint(int num, Vec a){if(num<4&&num>-1){p[num]=a;}}
    void onePointadd(int num,Vec a){p[num]=p[num]+a;}
    double getAngle(){return RotateAngle;}
    Vec getp0();
    Vec getpnum(int num){return p[num];}
};


class Ellipses:public ColoredFigure{
private:
    //四个顶点
    Vec cen,p1,p2,p3; // 端点
    double a,b; // 长轴 短轴

public:
    Ellipses();
    Ellipses(double red,double green,double blue,Vec pt0,double a, double b);
    void draw();
    void move(Vec dir);
    void rotate(double angle);
    void zoom(double k);
    double geta();
    Vec get_p3();
};


class Elli:public ColoredFigure{
private:
    Vec p[2];
    double a;
    double b;
public:
    Elli();
    Elli(double red, double green, double blue, Vec pt1,Vec pt2,double a,double b);
    virtual void draw();
    void move(Vec dir);
    void rotate(double angle);
    void zoom(double k);
};

class Poly:public ColoredFigure{
private:
    Vec **point;
    int num;
    Vec cen;
public:
    Poly();
    Poly(int s,double red, double green, double blue);
    void addPoly(int news);
    void draw();
    void zoom(double k);
    void move(Vec dir);
    void rotate(double angle);
    ~Poly();
};

class Semielli:public Elli{

private:
    Vec p[2];
    double a;
    double b;
public:
    Semielli();
    Semielli(double red, double green, double blue,Vec pt1,Vec pt2,double a, double b);
    void draw();
};


class newPoly:public ColoredFigure{
private:
    std::vector<Vec>points;
public:
    newPoly(Vec *a, int num, double red, double green, double blue);
    void draw();
    void move(Vec dir);
    void rotate(double k);
    void zoom(double k);
};

class Rect:public Quad{
public:
    Rect(double color[3],Vec cen, double halfwidth, double halflength){r=color[0];g=color[1];b=color[2];
        changeValue({cen.getX()-halflength,cen.getY()-halfwidth},{cen.getX()-halflength,cen.getY()+halfwidth},{cen.getX()+halflength,cen.getY()+halfwidth},{cen.getX()+halflength,cen.getY()-halfwidth});
    }
};

class UFOCurve:public ColoredFigure{
private:
    //axis(two points), alpha
    Vec p1,p0;
    double alpha;
public:
    UFOCurve();
    UFOCurve(double red,double green,double blue,Vec pt0,Vec pt1, double _alpha);
    void move(Vec dir);
    void rotate(double angle);
    void draw();
    void zoom(double k);
    Vec get_p3(){return p0;};
};

class Triangle:public ColoredFigure{
private:
    Vec p[3];
public:
    Triangle(double red,double green,double blue,Vec pt1,Vec pt2,Vec pt3);
    void draw();
    void move(Vec dir);
    void rotate(double angle);
    void zoom(double k);
    void movepoint(int num,Vec a);
};

#endif //P3_P3_H
