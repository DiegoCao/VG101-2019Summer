

#include "p3.h"
Circle::Circle(){
    r=.7;g=.2;b=.5; cen=Vec(0,0);ra=1.0;
}
Circle::Circle(double red,double green,double blue,Vec center,double radius){
    r=red;g=green;b=blue;cen=center;ra=radius;
    this->setAnchor(cen);
}
void Circle::setCircle(double red,double green,double blue,Vec center,double radius){
    r=red;g=green;b=blue;cen=center;ra=radius;
}
void Circle::draw(){
    int n=100;
    glColor3f(r,g,b);
    glBegin(GL_POLYGON);
    for(int i=0;i<n;i++)
    {
        glVertex2f(ra*cos(2*M_PI*i/n)+cen.getX(),ra*sin(2*M_PI*i/n)+cen.getY());
    }
    glEnd();
}
void Circle::move(Vec dir){
    cen=cen+dir;
}
void Circle::rotate(double angle){
    cen=getAnchor()+((cen-getAnchor())>>angle);
}
void Circle::zoom(double k){
    cen=getAnchor()+(cen-getAnchor())*k;
    ra *=k;
}
Vec Circle::get_cen() {return cen;}
Circle::~Circle(){}


SemiCircle::SemiCircle(){
    r=.7;g=.2;b=.5; p[0]=Vec(0,0);p[1]=Vec(0,0);
}
SemiCircle::SemiCircle(double red, double green, double blue, Vec pt1, Vec pt2){
    r=red;g=green;b=blue;p[0]=pt1;p[1]=pt2;
}
void SemiCircle::draw(){
    int n=100;
    Vec cen=(p[0]+p[1])*(0.5);
    double dx=(p[0].getX()-p[1].getX());
    double dy=(p[0].getY()-p[1].getY());
    double ra=sqrt(dx*dx+dy*dy)*(0.5);
    double initial_angel=atan((p[0].getY()-p[1].getY())/(p[0].getX()-p[1].getX()));
    if (p[1].getX()<p[0].getX()) initial_angel+= M_PI;
    glColor3f(r,g,b);
    glBegin(GL_POLYGON);
    for(int i=0;i<n;i++)
    {
        glVertex2f(ra*cos(M_PI*i/n+initial_angel)+cen.getX(),ra*sin(M_PI*i/n+initial_angel)+cen.getY());
    }
    glEnd();
}
void SemiCircle::move(Vec dir) {
    for (int i=0;i<2;i++)
        p[i]=p[i]+dir;
}
void SemiCircle::rotate(double angle) {
    for (int i=0;i<2;i++)
        p[i]=getAnchor()+((p[i]-getAnchor())>>angle);
}
void SemiCircle::zoom(double k) {
    for (int i=0;i<2;i++)
        p[i]=getAnchor()+(p[i]-getAnchor())*k;
}
Vec SemiCircle::getp0(){return Vec(p[0].getX()/2+p[1].getX()/2, p[0].getY()/2+p[1].getY()/2);}

Rectangle::Rectangle(double red, double green, double blue, Vec pt1, Vec pt2, Vec pt3) {
    r=red;g=green;b=blue;p[0]=pt1;p[1]=pt2;p[2]=pt3;
}
void Rectangle::draw(){
    glColor3f(r,g,b);
    glBegin(GL_TRIANGLE_STRIP);
    for (int i=0;i<3;i++)
        glVertex2f(p[i].getX(),p[i].getY());
    glEnd();
}
void Rectangle::move(Vec dir){
    for (int i=0;i<3;i++)
        p[i]=p[i]+dir;
}
void Rectangle::rotate(double angle){
    for (int i=0;i<3;i++)
        p[i]=getAnchor()+((p[i]-getAnchor())<<angle);
}
void Rectangle::zoom(double k) {
    for (int i=0;i<3;i++)
        p[i]=getAnchor()+((p[i]-getAnchor())*k);
}
Quad::Quad() {

}
Quad::Quad(double red, double green, double blue, Vec pt1, Vec pt2, Vec pt3, Vec pt4) {
    r=red;g=green;b=blue;
    p[0]=pt1;p[1]=pt2;p[2]=pt3;p[3]=pt4;

}
void Quad::draw(){
    glColor3f(r,g,b);
    glBegin(GL_QUADS);
    for(int i=0;i<4;i++)
        glVertex2f(p[i].getX(),p[i].getY());
    glEnd();
}
void Quad::move(Vec dir){
    for(int i=0;i<4;i++)
        p[i]=p[i]+dir;
}
void Quad::rotate(double angle){
    for(int i=0;i<4;i++)
    {p[i]=getAnchor()+((p[i]-getAnchor())>>angle);}
    this->RotateAngle=-(M_PI*angle/180)+this->RotateAngle;


}
void Quad::zoom(double k) {
    for (int i = 0; i < 4; i++)
        p[i] = getAnchor() + (p[i] - getAnchor()) * k;
}

Vec Quad::getp0()
{
    return p[0];
}

Elli::Elli(double red,double green,double blue,Vec pt1,Vec pt2, double aa, double bb){
    r=red;g=green;b=blue;p[0]=pt1;p[1]=pt2;a=aa;b=bb;
}
void Elli::draw(){
    int n=3600;
    Vec cen=(p[0]+p[1])*(0.5);
    double initial_angel=atan((p[0].getY()-p[1].getY())/(p[0].getX()-p[1].getX()));
    glColor3f(r, g, b);
    if (p[1].getX()<p[0].getX()) initial_angel+= M_PI;
    glBegin(GL_POLYGON); Vec ref;
    double dx,dy;
    for (int i = 0; i < n; i++)
    {
        dx=a * cos( M_PI * i / n)+cen.getX();
        dy=b * sin( M_PI * i / n)+cen.getY();
        ref=Vec(dx,dy);
        ref = cen + ((ref - cen) >> (-180*initial_angel/M_PI));
        glVertex2f(ref.getX(),ref.getY());
    }
    glEnd();
}
void Elli::move(Vec dir){p[0]=p[0]+dir;p[1]=p[1]+dir;}
void Elli::rotate(double angle){
    for(int i=0;i<2;i++)
        p[i]=getAnchor()+((p[i]-getAnchor())>>angle);
}
void Elli::zoom(double k){
    a=a*k;b=b*k;
    for (int i = 0; i < 2; i++){
        p[i] = getAnchor() + (p[i] - getAnchor()) * k;}
}


Poly::Poly(int s, double red, double green, double blue){
    num=s;
    r=red;
    g=green;
    b=blue;
    point=new Vec*[num];
    double angle=0;
    for(int i=0;i<num;i++){
        point[i]=new Vec;
        *point[i]=Vec{10*cos(angle),10*sin(angle)};
        angle=angle+(2*M_PI)/num;
    }

    cen=Vec{0,0};
}
void Poly::draw() {
    glColor3f(r,g,b);
    glBegin(GL_POLYGON);
    for(int i=0;i<num;i++)
        glVertex2f(point[i]->getX(),point[i]->getY());
    glEnd();
}
void Poly::zoom(double k){
    for (int i = 0; i < num; i++){
        *point[i] = getAnchor() + (*point[i] - getAnchor()) * k;}
}
void Poly::rotate(double angle) {
    for(int i=0;i<2;i++)
        *point[i]=getAnchor()+((*point[i]-getAnchor())>>angle);
}
void Poly::addPoly(int news){
    for(int i=0;i<num;i++){
        delete point[i];
    }
    delete [] point;
    num=news;
    point=new Vec*[num];
    double angle=0;
    for(int i=0;i<num;i++){
        point[i]=new Vec;
        *point[i]=Vec{10*cos(angle),10*sin(angle)};
        angle=angle+(2*M_PI)/num;
    }
}
void Poly::move(Vec dir){
    for(int i=0;i<num;i++){
        *point[i]=*point[i]+dir;
    }
}
Poly::~Poly() {
    for(int i=0;i<num;i++){
        delete point[i];
    }
    delete [] point;
}

newPoly::newPoly(Vec *a, int num, double red, double green, double blue){
    for(int i=0;i<num;i++){
        this->points.push_back(a[i]);
    }
    r=red;
    g=green;b=blue;

}

void newPoly::draw(){
    glColor3f(r,g,b);
    glBegin(GL_POLYGON);
    for (unsigned int i=0;i<points.size();i++){
        glVertex2f(points[i].getX(),points[i].getY());
    }
    glEnd();
}
void newPoly::rotate(double k) {
    for(unsigned int i=0;i<points.size();i++){
        points[i]=getAnchor()+((points[i]-getAnchor())>>k);
    }
}
void newPoly::move(Vec dir) {
    for(unsigned int i=0;i<points.size();i++){points[i]=points[i]+dir;}
}
void newPoly::zoom(double k) {
    for (unsigned int i = 0; i < points.size(); i++)
        points[i] = getAnchor() + (points[i] - getAnchor()) * k;
}

UFOCurve::UFOCurve(){}
UFOCurve::UFOCurve(double red,double green,double blue,Vec pt0,Vec pt1, double _alpha)
{
    r=red; g=green; b=blue; p0=pt0; p1=pt1;alpha=_alpha;
}
void UFOCurve::move(Vec dir){
    p1=p1+dir;
    p0=p0+dir;
}
void UFOCurve::rotate(double angle){
    p1 = getAnchor() + ((p1 - getAnchor()) >> angle);
    p0 = getAnchor() + ((p0 - getAnchor()) >> angle);
}
void UFOCurve::zoom(double k){
    p1 = getAnchor() + (p1 - getAnchor()) * k;
    p0 = getAnchor() + (p0 - getAnchor()) * k;
}
void UFOCurve::draw(){
    glColor3f(r, g, b);

    glBegin(GL_LINE_STRIP);
    Vec ref;
    for (int i=-360; i<360; ++i)
    {
        ref=p1-p0;
        ref=p0+ ((ref) >> -alpha*i/360);

        if(fabs((getAnchor()-ref)<(p0-p1))<2*M_PI/3)
            glVertex2f(ref.getX(),ref.getY());
    }
    glEnd();
}

Ellipses::Ellipses(){}
Ellipses::Ellipses(double red, double green, double blue, Vec pt0, double _a, double _b)
{
    r = red;g = green;b = blue;
    cen = pt0; a=_a; b=_b;
    Vec deltapt(a,0.0), ver(0.0,b);
    p1 = cen - deltapt;
    p2 = cen + deltapt;
    p3 = cen + ver;
}

void Ellipses::draw()
{
    int n = 3600;
    double dx, dy;
    double initial_angle = atan((p2.getY() - p1.getY()) / (p2.getX() - p1.getX()));

    glColor3f(r, g, b);
    glBegin(GL_POLYGON); Vec ref;

    for (int i = 0; i < n; i++)
    {

        dx=a * cos(2* M_PI * i / n)+cen.getX();
        dy=b * sin(2 * M_PI * i / n)+cen.getY();
        ref=Vec(dx,dy);

        ref = cen + ((ref - cen) >> (-180*initial_angle/M_PI));

        glVertex2f(ref.getX(),ref.getY());

    }
    glEnd();
}
void Ellipses::move(Vec dir)
{
    p1=p1+dir; p2=p2+dir; cen=cen+dir;p3=p3+dir;
}
void Ellipses::rotate(double angle)
{
    p1 = getAnchor() + ((p1 - getAnchor()) >> angle);
    p2 = getAnchor() + ((p2 - getAnchor()) >> angle);
    p3 = getAnchor() + ((p3 - getAnchor()) >> angle);
    cen = getAnchor() + ((cen - getAnchor()) >> angle);
}
void Ellipses::zoom(double k)
{
    p1 = getAnchor() + (p1 - getAnchor()) * k;
    p2 = getAnchor() + (p2 - getAnchor()) * k;
    p3 = getAnchor() + (p3 - getAnchor()) * k;
    cen = getAnchor() + (cen - getAnchor()) * k;
    a*=k;
    b=b*k;
}
double Ellipses::geta()
{
    return a;
}
Vec Ellipses::get_p3()
{
    return p3;
}


Triangle::Triangle(double red, double green, double blue, Vec pt1, Vec pt2, Vec pt3) {
    r=red;g=green;b=blue;p[0]=pt1;p[1]=pt2;p[2]=pt3;
}
void Triangle::draw(){
    glColor3f(r,g,b);
    glBegin(GL_POLYGON);
    for (int i=0;i<3;i++)
        glVertex2f(p[i].getX(),p[i].getY());
    glEnd();
}
void Triangle::move(Vec dir){
    for (int i=0;i<3;i++)
        p[i]=p[i]+dir;
}
void Triangle::rotate(double angle){
    for (int i=0;i<3;i++)
        p[i]=getAnchor()+((p[i]-getAnchor())<<angle);
}
void Triangle::zoom(double k) {
    for (int i=0;i<3;i++)
        p[i]=getAnchor()+((p[i]-getAnchor())*k);
}

void Triangle::movepoint(int num, Vec a) {
    p[num]=p[num]+a;
}