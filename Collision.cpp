#include "Collision.h"

Collision::Collision()
{
    //ctor
}

bool intersectCircle(Vec2 lineStart, Vec2 lineEnd, Vec2 circle, float radius)
{

    // find the closest point on the line segment to the center of the circle
    Vec2 line = lineEnd - lineStart;
    float lineLength = line.lenght();
    Vec2 lineNorm = line*(1/lineLength);
    Vec2 segmentToCircle = circle - lineStart;
    float closestPointOnSegment = segmentToCircle.dotProduct(line) / lineLength;

    // Special cases where the closest point happens to be the end points
    Vec2 closest;
    if (closestPointOnSegment < 0) closest = lineStart;
    else if (closestPointOnSegment > lineLength) closest = lineEnd;
    else closest = lineStart + line*closestPointOnSegment;

    // Find that distance.  If it is less than the radius, then we
    // are within the circle
    Vec2 distanceFromClosest = circle - closest;
    float distanceFromClosestLength = distanceFromClosest.lenght();
    if (distanceFromClosestLength > radius) return false;

    return true;
}

bool lineToCircleIntersection2(Vec2 vertex1, Vec2 vertex2,
                              Vec2 circlePosition, float radius)
{
    // Vector from point 1 to point 2
    Vec2 vertex1to2 = vertex2 - vertex1;
    // Vector from point 1 to the circle's center
    Vec2 circleToVertex1 = circlePosition - vertex1;

    float dot = vertex1to2.dotProduct(circleToVertex1);
    Vec2 proj1 = vertex1to2 * (dot / sqrtf(vertex1to2.lenght()));

    Vec2 midpt = vertex1 + proj1;
    Vec2 circleToMidpt = midpt - circlePosition;
    float distSqToCenter = sqrtf(circleToMidpt.lenght());
    if (distSqToCenter > radius * radius) return 0;
    if (distSqToCenter == radius * radius)
    {
        return false;
    }
    float distToIntersection;
    if (distSqToCenter == 0)
    {
        distToIntersection = radius;
    }
    else
    {
        distToIntersection = sqrt(radius * radius - distSqToCenter);
    }
    vertex1to2.normalize();
    vertex1to2 *= distToIntersection;

    return true;
}

float dist_Point_to_Line( Vec2 p, Vec2 l1, Vec2 l2)
{
     Vec2 v = l1 - l2;
     Vec2 w = p - l1;

     double c1 = w.dotProduct(v); ///dot(w,v);
     double c2 = v.dotProduct(v); ///dot(v,v);
     double b = c1 / c2;

     Vec2 pb = l1 + v*b;
     return sqrtf((p.x-pb.x)*(p.x-pb.x)+(pb.y-p.y)*(pb.y-p.y));
}
