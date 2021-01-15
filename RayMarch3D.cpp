#include "RayMarch3D.hpp"

ListNode * getNode(size_t nodeNo)
{
    ListNode * currNode = firstObjectNode;
    for(size_t i = 0; i < nodeNo; ++i)
    {
        if(currNode->nextNode != NULL)
        {
            currNode = currNode->nextNode;
        } else
        {
            return NULL;
        };
    };
    return currNode;
};

size_t getNodesCount()
{
    return 3;
};

ListNode * addNode(void * data)
{
    ListNode * currNode = firstObjectNode;
    if(firstObjectNode == NULL)
    {
        firstObjectNode = ( ListNode* )malloc(sizeof(ListNode));
        firstObjectNode->nextNode = NULL;
        firstObjectNode->data = data;
        return firstObjectNode;
    };
    for(;currNode->nextNode != NULL;)
    {
        currNode = currNode->nextNode;
    };
    currNode->nextNode = ( ListNode* )malloc(sizeof(ListNode));
    currNode->nextNode->nextNode = NULL;
    currNode->nextNode->data = data;
    return currNode->nextNode;
};

Object * getNearestObject(Vec3 & point)
{
    ListNode * currObjNode = firstObjectNode;
    double currObjDest;

    Object * nearestObject = ( (Object*)(currObjNode->data) );
    double nearestObjectdest = nearestObject->destFunc(point);
    for(;currObjNode != NULL;)
    {
        if( ( currObjDest = ( (Object*)(currObjNode->data) )->destFunc(point) ) < nearestObjectdest)
        {
            nearestObject = ( (Object*)(currObjNode->data) );
            nearestObjectdest = currObjDest;
        };
        currObjNode = currObjNode->nextNode;
    };
    return nearestObject;
};

RGB traceRay(double maxRayLength, Vec3 & startPoint, Vec3 & tracingNorm, Vec3 & lightPos, double lightPower)
{
    Vec3 currPoint = startPoint;
    for(double rayLength = 0.0; rayLength <= maxRayLength;)
    {
        Object * nearestObject = getNearestObject(currPoint);
        double nearestObjectDest = nearestObject->destFunc(currPoint);
        rayLength += nearestObjectDest;
        if(nearestObjectDest <= NEAR)
        {
            double light = getLight(maxRayLength - rayLength, currPoint, getNormal(currPoint), lightPos, lightPower) / 100;

            size_t r = nearestObject->color.r / light;
            if(r > 255) r = 255;

            size_t g = nearestObject->color.g / light;
            if(g > 255) g = 255;

            size_t b = nearestObject->color.b / light;
            if(b > 255) b = 255;

            return {
                        (uint8_t)(r),
                        (uint8_t)(g),
                        (uint8_t)(b)
                    };
        };
        Vec3 dCurrPoint = tracingNorm * nearestObjectDest;
        currPoint += dCurrPoint;
    };
    return {0,0,0};
};

double getLight(double maxRayLength, Vec3 & startPoint, Vec3 tracingNorm, Vec3 & lightPos, double lightPower)
{
    Vec3 currPoint = startPoint;
    double rayLength = 0.0;
    for(; rayLength <= maxRayLength;)
    {
        double nearestObjectDest = getNearestObject(currPoint)->destFunc(currPoint);
        rayLength += nearestObjectDest;
        if(nearestObjectDest <= NEAR)
        {
            tracingNorm = currPoint - lightPos;
            if(lightPos.dest(currPoint) <= lightPower)
            {
                return lightPos.dest(currPoint);
            };
        };
        Vec3 dCurrPoint = tracingNorm * nearestObjectDest;
        currPoint += dCurrPoint;
    };
    return 0;
};

// double getLight(Vec3 & point, Vec3 & lightPos)
// {
//     if( lightPos.dest( point + ( getNormal(point) * lightPos.dest(point) ) ) <= 1000 )
//     {
//         return lightPos.dest(point);
//     } else 
//     {
//         return 0;
//     };
// };

inline Vec3 getNormal(Vec3 & p)
{
    Vec3 v0 = {p.x + NEAR, p.y, p.z};
    Vec3 v1 = {p.x - NEAR, p.y, p.z};
    Vec3 v2 = {p.x, p.y + NEAR, p.z};
    Vec3 v3 = {p.x, p.y - NEAR, p.z};
    Vec3 v4 = {p.x, p.y, p.z + NEAR};
    Vec3 v5 = {p.x, p.y, p.z - NEAR};

    Vec3 res = {
            getNearestObject(v0)->destFunc(p) - getNearestObject(v1)->destFunc(p),
            getNearestObject(v2)->destFunc(p) - getNearestObject(v3)->destFunc(p),
            getNearestObject(v4)->destFunc(p) - getNearestObject(v5)->destFunc(p)
        };
    return res.normalized();
};

double dot(Vec3 & a, Vec3 & b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
};