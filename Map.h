#ifndef MAP_H
#define MAP_H

#include <vector>

#include "Actor.h"
#include "Obstacle.h"

class Map : public Obstacle
{
    public:
        Map();
        void render();
        std::vector<Obstacle*> obstacles;
    protected:
    private:
};

#endif // MAP_H
