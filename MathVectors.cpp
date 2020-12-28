#include "MathVectors.hpp"

Vec2
Vec2::operator *=(const Vec2 & a)
{
    Vec2 res;
    res.x = this->x *= a.x;
    res.y = this->y *= a.y;
    return res;
};

Vec2
Vec2::operator /=(const Vec2 & a)
{
    Vec2 res;
    res.x = this->x /= a.x;
    res.y = this->y /= a.y;
    return res;
};

Vec2
Vec2::operator /=(double a)
{
    Vec2 res;
    res.x = this->x /= a;
    res.y = this->y /= a;
    return res;
};

Vec2
Vec2::operator /(double a)
{
    Vec2 res;
    res.x = this->x / a;
    res.y = this->y / a;
    return res;
};

Vec2
Vec2::operator +=(const Vec2 & a)
{
    Vec2 res;
    res.x = this->x += a.x;
    res.y = this->y += a.y;
    return res;
};

Vec2 
Vec2::operator -=(double a)
{
    return {this->x -= a, this->y -= a};
};

Vec2 
Vec2::operator -=(const Vec2 & a)
{
    return {this->x -= a.x, this->y -= a.y};
};

Vec2
Vec2::operator *(const Vec2 & a)
{
    Vec2 res;
    res.x = this->x * a.x;
    res.y = this->y * a.y;
    return res;
};

Vec2
Vec2::operator *(double a)
{
    return {this->x *a, this->y * a};
};

Vec2
Vec2::operator /(const Vec2 & a)
{
    Vec2 res;
    res.x = this->x / a.x;
    res.y = this->y / a.y;
    return res;
};

Vec2
Vec2::operator =(const Vec2 & a)
{
    this->x = a.x;
    this->y = a.y;
    return *this;
};

Vec2
Vec2::operator -(const Vec2 & a)
{
    Vec2 res;
    res.x = this->x - a.x;
    res.y = this->y - a.y;
    return res;
};

Vec2
Vec2::operator +(const Vec2 & a)
{
    Vec2 res;
    res.x = this->x + a.x;
    res.y = this->y + a.y;
    return res;
};

bool
Vec2::operator ==(double a)
{
    if(this->x == a && this->y == a) return true;
    else return false;
};

bool
Vec2::operator ==(const Vec2 & a)
{
    if(this->x == a.x && this->y == a.y) return true;
    else return false;
};

double
Vec2::length()
{
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
};

double
Vec2::dest(const Vec2 & a)
{
    return sqrt(pow(a.x - this->x, 2) + pow(a.y - this->y, 2));
};

double
Vec2::angle()
{
    double angle = abs(atan(this->y / this->x));
    if(isnan(angle))
    {
        if(y == 0)
        {
            angle = 0;
        } else if(y > 0)
        {
            angle = M_PI_4;
        } else if(y < 0)
        {
            angle = M_PI + M_PI_4;
        };
    } else
    {
        if(angle == 0 && y == 0)
        {
            if(x > 0)
            {
                angle = 0;
            } else if(x < 0)
            {
                angle = M_PI;
            };
        } else
        {
            if(x < 0 && y > 0)
            {
                angle = (M_PI - angle);
            } else if(x < 0 && y < 0)
            {
                angle = M_PI + angle;
            } else if(x > 0 && y < 0)
            {
                angle = M_PI + (M_PI - angle);
            };
        };
    };
    return angle;
};

Vec2
Vec2::normalized()
{
    double len = this->length();
    Vec2 norm;
    norm.x = this->x / len;
    norm.y = this->y / len;
    return norm;
};






Vec3
Vec3::operator *=(const Vec3 & a)
{
    Vec3 res;
    res.x = this->x *= a.x;
    res.y = this->y *= a.y;
    res.z = this->z *= a.z;
    return res;
};

Vec3
Vec3::operator /=(const Vec3 & a)
{
    Vec3 res;
    res.x = this->x /= a.x;
    res.y = this->y /= a.y;
    res.z = this->z /= a.z;
    return res;
};

Vec3
Vec3::operator /=(double a)
{
    Vec3 res;
    res.x = this->x /= a;
    res.y = this->y /= a;
    res.y = this->z /= a;
    return res;
};

Vec3
Vec3::operator /(double a)
{
    Vec3 res;
    res.x = this->x / a;
    res.y = this->y / a;
    res.y = this->z / a;
    return res;
};

Vec3
Vec3::operator +=(const Vec3 & a)
{
    Vec3 res;
    res.x = this->x += a.x;
    res.y = this->y += a.y;
    res.y = this->z += a.z;
    return res;
};

Vec3 
Vec3::operator -=(double a)
{
    return {this->x -= a, this->y -= a, this->z -= a};
};

Vec3 
Vec3::operator -=(const Vec3 & a)
{
    return {this->x -= a.x, this->y -= a.y, this->z -= a.z};
};

Vec3
Vec3::operator *(const Vec3 & a)
{
    Vec3 res;
    res.x = this->x * a.x;
    res.y = this->y * a.y;
    res.z = this->z * a.z;
    return res;
};

Vec3
Vec3::operator *(double a)
{
    return {this->x *a, this->y * a, this->z * a};
};

Vec3
Vec3::operator /(const Vec3 & a)
{
    Vec3 res;
    res.x = this->x / a.x;
    res.y = this->y / a.y;
    res.y = this->z / a.z;
    return res;
};

Vec3
Vec3::operator =(const Vec3 & a)
{
    this->x = a.x;
    this->y = a.y;
    this->z = a.z;
    return *this;
};

Vec3
Vec3::operator -(const Vec3 & a)
{
    Vec3 res;
    res.x = this->x - a.x;
    res.y = this->y - a.y;
    res.z = this->z - a.z;
    return res;
};

Vec3
Vec3::operator +(const Vec3 & a)
{
    Vec3 res;
    res.x = this->x + a.x;
    res.y = this->y + a.y;
    res.z = this->z + a.z;
    return res;
};

bool
Vec3::operator ==(double a)
{
    if(this->x == a && this->y == a && this->z == a) return true;
    else return false;
};

bool
Vec3::operator ==(const Vec3 & a)
{
    if(this->x == a.x && this->y == a.y  && this->z == a.z) return true;
    else return false;
};

double
Vec3::length()
{
    return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
};

double
Vec3::dest(const Vec3 & a)
{
    return sqrt(pow(a.x - this->x, 2) + pow(a.y - this->y, 2) + pow(a.z - this->z, 2));
};

double
Vec3::angleYX()
{
    double angle = abs(atan(this->y / this->x));
    if(isnan(angle))
    {
        if(y == 0)
        {
            angle = 0;
        } else if(y > 0)
        {
            angle = M_PI_4;
        } else if(y < 0)
        {
            angle = M_PI + M_PI_4;
        };
    } else
    {
        if(angle == 0 && y == 0)
        {
            if(x > 0)
            {
                angle = 0;
            } else if(x < 0)
            {
                angle = M_PI;
            };
        } else
        {
            if(x < 0 && y > 0)
            {
                angle = (M_PI - angle);
            } else if(x < 0 && y < 0)
            {
                angle = M_PI + angle;
            } else if(x > 0 && y < 0)
            {
                angle = M_PI + (M_PI - angle);
            };
        };
    };
    return angle;
};

double
Vec3::angleZY()
{
    double angle = abs(atan(this->z / this->y));
    if(isnan(angle))
    {
        if(this->z == 0)
        {
            angle = 0;
        } else if(this->z > 0)
        {
            angle = M_PI_4;
        } else if(this->z < 0)
        {
            angle = M_PI + M_PI_4;
        };
    } else
    {
        if(angle == 0 && this->z == 0)
        {
            if(x > 0)
            {
                angle = 0;
            } else if(x < 0)
            {
                angle = M_PI;
            };
        } else
        {
            if(this->y < 0 && this->z > 0)
            {
                angle = (M_PI - angle);
            } else if(this->y < 0 && this->z < 0)
            {
                angle = M_PI + angle;
            } else if(this->y > 0 && this->z < 0)
            {
                angle = M_PI + (M_PI - angle);
            };
        };
    };
    return angle;
};

Vec3
Vec3::normalized()
{
    double len = this->length();
    Vec3 norm;
    norm.x = this->x / len;
    norm.y = this->y / len;
    norm.z = this->z / len;
    return norm;
};