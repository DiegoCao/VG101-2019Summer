//
// Created by Dell on 2019/7/27.
//
#include "p3.h"

#include "Curve.h"
Curve::Curve(double red, double green, double blue, int num_input, Vec *arr_input) {
    r=red;g=green;b=blue;num_vertex=num_input;
    arr_vertex=new Vec[num_input+3];
    for (int i=0;i<num_vertex;i++)
        arr_vertex[i]=arr_input[i];
    for (int i=0;i<3;i++)
        arr_vertex[num_vertex+i]=arr_vertex[i];
}
void Curve::draw(){
    glColor3f(r,g,b);
    glBegin(GL_POLYGON);
    const int nod=40;
    for(int n=0;n<num_vertex;n++){
        for(int i=0;i!=nod;i++) {
            float t = (float) i / nod;
            float it = 1.0 - t;
            //样条曲线三个参数
            float b0 = it * it * it / 6.0f;
            float b1 = (3 * t * t * t - 6 * t * t + 4) / 6.0f;
            float b2 = (-3 * t * t * t + 3 * t * t + 3 * t + 1) / 6.0f;
            float b3 = t * t * t / 6.0f;

            float x = b0 * arr_vertex[n].getX() + b1 * arr_vertex[n+1].getX() + b2 * arr_vertex[n+2].getX() + b3 * arr_vertex[n+3].getX();
            float y = b0 * arr_vertex[n].getY() + b1 * arr_vertex[n+1].getY() + b2 * arr_vertex[n+2].getY() + b3 * arr_vertex[n+3].getY();

            glVertex2f(x, y);
        }
    }
    glEnd();

}
void Curve::move(Vec dir){
    for(int i=0;i<num_vertex+3;i++)
        arr_vertex[i]=arr_vertex[i]+dir;
}
void Curve::rotate(double angle){
    for(int i=0;i<num_vertex+3;i++)
        arr_vertex[i]=getAnchor()+((arr_vertex[i]+getAnchor())<<angle);
}
void Curve::zoom(double k){
    for(int i=0;i<num_vertex+3;i++)
        arr_vertex[i]=getAnchor()+((arr_vertex[i]-getAnchor())*k);
}

void GradientCurve::draw(){
    //实现动态渐变色。state为了每一帧的渐变，changestate使得形成渐变的动画
    glBegin(GL_POLYGON);
    const int nod=40;
    int state=0;
    int p=log;
    int count=nod*(num_vertex);
    for(int n=0;n<num_vertex;n++){
        for(int i=0;i!=nod;i++) {
            float t = (float) i / nod;
            float it = 1.0 - t;
            //样条曲线三个参数
            float b0 = it * it * it / 6.0f;
            float b1 = (3 * t * t * t - 6 * t * t + 4) / 6.0f;
            float b2 = (-3 * t * t * t + 3 * t * t + 3 * t + 1) / 6.0f;
            float b3 = t * t * t / 6.0f;

            float x = b0 * arr_vertex[n].getX() + b1 * arr_vertex[n+1].getX() + b2 * arr_vertex[n+2].getX() + b3 * arr_vertex[n+3].getX();
            float y = b0 * arr_vertex[n].getY() + b1 * arr_vertex[n+1].getY() + b2 * arr_vertex[n+2].getY() + b3 * arr_vertex[n+3].getY();

            if (p<count && state==0)
                p++;
            else if(p>0){
                state=1;
                p--;
            }
            else state=0;


            glColor3f(1,1-float(p)/count,float(p)/count);
            glVertex2f(x, y);
        }
    }
    glEnd();
    if (log<count && changestate==0)
        log+=10;
    else if(log>0){
        changestate=1;
        log-=10;
    }
    else changestate=0;
}
void GradientCurve::zoom(double k) {
    for(int i=0;i<num_vertex+3;i++)
        arr_vertex[i]=getAnchor()+((arr_vertex[i]-getAnchor())*k);

    arr_vertex[0]=getAnchor()+((arr_vertex[0]-getAnchor())*sqrt(k));
    arr_vertex[num_vertex]=getAnchor()+((arr_vertex[num_vertex]-getAnchor())*sqrt(k));
}
