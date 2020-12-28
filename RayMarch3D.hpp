#ifndef RAYMARCH_3D_H
#define RAYMARCH_3D_H

#include <stddef.h>
#include "MathVectors.hpp"
#include <iostream>

typedef struct
{
    uint8_t r,g,b;
}RGB;

// typedef struct
// {
//     double x,y,z;
// }Vec3;

struct ListNode
{
    void * data;
    ListNode * nextNode;
};

struct Object
{
    double dest;
    RGB color;
    double (*destFunc)(Vec3 point);
};

const double NEAR = 0.0001;

static ListNode * firstObjectNode;

ListNode * getNodeDataPtr(size_t nodeNo);
ListNode * addNode(void * data);

Object * getNearestObjectDest(Vec3 & point);
RGB traceRay(double maxRayLength, Vec3 & startPoint, Vec3 & tracingNorm, Vec3 & lightPos, double lightPower);

double getLight(double maxRayLength, Vec3 & startPoint, Vec3 tracingNorm, Vec3 & lightPos, double lightPower);

double dot(Vec3 & a, Vec3 & b);

Vec3 getNormal(Vec3 & p);

#endif