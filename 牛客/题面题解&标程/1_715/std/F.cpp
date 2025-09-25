#include<bits/stdc++.h>
using namespace std;
typedef long double db;
const db pi=acos(db(-1));
struct Point3D
{
    db x,y,z;
    Point3D() {}
    Point3D(db x,db y,db z):x(x),y(y),z(z) {}
    Point3D operator * (const Point3D& t)const { return Point3D(y*t.z-z*t.y,z*t.x-x*t.z,x*t.y-y*t.x); }
    Point3D operator - (const Point3D& t)const { return Point3D(x-t.x,y-t.y,z-t.z); }
    db operator | (const Point3D& t)const { return x*t.x+y*t.y+z*t.z; }
    db len()const { return sqrt((*this)|(*this)); }
    db angle(const Point3D& p)const { return atan2(((*this)*p).len(),(*this)|p); }
};
db areaOfCapsIntersection(db a,db b,db c)
{
    db s=(a+b+c)/2;
    db k=sqrt((sin(s-a)*sin(s-b)*sin(s-c)/sin(s)));
    db A=2*atan(k/sin(s-a));
    db B=2*atan(k/sin(s-b));
    db C=2*atan(k/sin(s-c));
    db T=A+B+C-pi;
    db S1=2*B*(1-cos(a));
    db S2=2*A*(1-cos(b));
    return S1+S2-2*T;
}
int solve()
{
    db r,d;
    Point3D s,t;
    scanf("%Lf%Lf%Lf%Lf%Lf%Lf%Lf%Lf",&r,&d,&s.x,&s.y,&s.z,&t.x,&t.y,&t.z);
    db res=0,b=d/r,c=s.angle(t);
    if(b<pi/2)res+=2*c*sin(b)+2*pi*(1-cos(b));
    else
    {
        res+=4*pi;
        if(b+c/2<pi)res-=areaOfCapsIntersection(pi-b,pi-b,c);
    }
    return 0*printf("%.18Lf\n",res*r*r);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)solve();
    return 0;
}
