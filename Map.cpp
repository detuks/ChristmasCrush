#include "Map.h"

Map::Map()
{
    obstacles.push_back(this);
}


void Map::render()
{
    glPushMatrix();
    glTranslatef(pos.x,pos.y,0);///move player

    glCallList(getModelID());
    glPopMatrix();
}


