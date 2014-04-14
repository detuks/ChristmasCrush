#include "Ammo.h"

Ammo::Ammo()
{
    frameCD = 69;
}

Ammo::Ammo(float sp,int bumR,int dmgR,int dam,float pitc, int model, int eModel)
{
    frameCD = 69;
    speed = sp;
    bumRad = bumR;
    dmgRad = dmgR;
    damage = dam;
    pitch = pitc;
    setModelID(model);
    setExplodeModel(eModel);
}

void Ammo::render()
{
    glPushMatrix();
    glTranslatef(pos.x,pos.y,0);

    glRotatef((pitch*radToDeg -135),0,0,1);

    glCallList(getModelID());

    glPopMatrix();
    step();
}



void Ammo::step()
{
    if(!exlploded)
    {
        pos.x-=speed*cos(pitch);
        pos.y-=speed*sin(pitch);
    }else
    {
        frameCD-=1;
    }
}

void Ammo::explode()
{
    if(frameCD != 69)
        return;
    frameCD = 20;
    exlploded = true;
    setModelID(explodeModel);
}
void Ammo::setExplodeModel(int mod)
{
    explodeModel = mod;
}

int Ammo::getExplodeModel()
{
    return explodeModel;
}

