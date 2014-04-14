#include "Mob.h"

Mob::Mob()
{

}

void Mob::movement()
{

}

void Mob::render()
{
    glPushMatrix();
    glTranslatef(pos.x,pos.y,0);///move player

    glRotatef((pitch*radToDeg-90),0,0,1);

    glCallList(getModelID());

    glPopMatrix();
}
