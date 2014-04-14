#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Actor.h"
#include "Collision.h"

class Obstacle : public Actor
{
    public:
        Obstacle();
        Vec2 c1,c2,c3,c4;
        void updateColVec();
        void render();
        bool collision(Actor *pos, float radius);

        float lineToCircle(Vec2 lineStart, Vec2 lineEnd, Vec2 circle, float radius);
        float dist_Point_to_Line( Vec2 p, Vec2 l1, Vec2 l2);

    protected:
    private:
};

#endif // OBSTACLE_H
