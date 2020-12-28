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

    Object * nearestObject = ( (Object*)(currObjNode->data) );
    nearestObject->dest = nearestObject->destFunc(point);
    for(;currObjNode != NULL;)
    {
        if( ( ( (Object*)(currObjNode->data) )->dest = ( (Object*)(currObjNode->data) )->destFunc(point) ) < nearestObject->dest)
        {
            nearestObject = ( (Object*)(currObjNode->data) );
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
        rayLength += nearestObject->dest;
        if(nearestObject->dest <= NEAR)
        {
            double light = getLight(currPoint, lightPos) * lightPower;
            double colourLight = abs(1000 / ( light / ( rayLength ) ));

            return {
                        (uint8_t)(nearestObject->color.r * colourLight),
                        (uint8_t)(nearestObject->color.g * colourLight),
                        (uint8_t)(nearestObject->color.b * colourLight)
                    };
        };
        Vec3 dCurrPoint = tracingNorm * getNearestObject(currPoint)->dest;
        currPoint += dCurrPoint;
    };
    return {0,0,0};
};

double getLight(Vec3 & point, Vec3 & lightPos)
{
    if( lightPos.dest( point + ( getNormal(point) * lightPos.dest(point) ) ) <= 1000 )
    {
        return lightPos.dest(point);
    } else 
    {
        return 0;
    };
};

inline Vec3 getNormal(Vec3 & p)
{
    Vec3 v0 = {p.x + NEAR, p.y, p.z};
    Vec3 v1 = {p.x - NEAR, p.y, p.z};
    Vec3 v2 = {p.x, p.y + NEAR, p.z};
    Vec3 v3 = {p.x, p.y - NEAR, p.z};
    Vec3 v4 = {p.x, p.y, p.z + NEAR};
    Vec3 v5 = {p.x, p.y, p.z - NEAR};

    Vec3 res = {
            getNearestObject(v0)->dest - getNearestObject(v1)->dest,
            getNearestObject(v2)->dest - getNearestObject(v3)->dest,
            getNearestObject(v4)->dest - getNearestObject(v5)->dest
        };
    return res.normalized();
};

double dot(Vec3 & a, Vec3 & b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
};