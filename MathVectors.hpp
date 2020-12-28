#ifndef MATH_VECTORS_HPP
#define MATH_VECTORS_HPP

#include <math.h>

class Vec2
{   
    public:
        double x,y;
    Vec2 operator *=(const Vec2 & a);
    Vec2 operator /=(const Vec2 & a);
    Vec2 operator /=(double a);
    Vec2 operator +=(const Vec2 & a);
    Vec2 operator -=(double a);
    Vec2 operator -=(const Vec2 & a);
    Vec2 operator *(const Vec2 & a);
    Vec2 operator *(double a);
    Vec2 operator /(const Vec2 & a);
    Vec2 operator /(double a);
    Vec2 operator =(const Vec2 & a);
    Vec2 operator -(const Vec2 & a);
    Vec2 operator +(const Vec2 & a);
    bool operator ==(double a);
    bool operator ==(const Vec2 & a);
    double length();
    double dest(const Vec2 & a);
    double angle();
    Vec2 normalized();
};

class Vec3
{   
    public:
        double x,y,z;
    Vec3 operator *=(const Vec3 & a);
    Vec3 operator /=(const Vec3 & a);
    Vec3 operator /=(double a);
    Vec3 operator +=(const Vec3 & a);
    Vec3 operator -=(double a);
    Vec3 operator -=(const Vec3 & a);
    Vec3 operator *(const Vec3 & a);
    Vec3 operator *(double a);
    Vec3 operator /(const Vec3 & a);
    Vec3 operator /(double a);
    Vec3 operator =(const Vec3 & a);
    Vec3 operator -(const Vec3 & a);
    Vec3 operator +(const Vec3 & a);
    bool operator ==(double a);
    bool operator ==(const Vec3 & a);
    double length();
    double dest(const Vec3 & a);
    double angleYX();
    double angleZY();
    Vec3 normalized();
};

const Vec2 ZERO_Vec2 = {0.0,0.0};
const Vec3 ZERO_Vec3 = {0.0,0.0,0.0};

#endif