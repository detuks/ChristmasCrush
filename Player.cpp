#include "Player.h"

Player::Player()
{
    speed=7;
}

void Player::updatePos()
{
    oldPos =pos;

    Uint8* state=SDL_GetKeyState(NULL);
    if(state[SDLK_w])
    {
        if(state[SDLK_a] || state[SDLK_d])
            pos.y-=speed/1.5;
        else
            pos.y-=speed;
    }
    else if(state[SDLK_s])
    {
        if(state[SDLK_a] || state[SDLK_d])
            pos.y+=speed/1.5;
        else
            pos.y+=speed;
    }

    if(state[SDLK_a])
    {
        if(state[SDLK_w] || state[SDLK_s])
            pos.x-=speed/2;
        else
            pos.x-=speed;
    }
    else if(state[SDLK_d])
    {
        if(state[SDLK_w] || state[SDLK_s])
            pos.x+=speed/2;
        else
            pos.x+=speed;
    }
}

void Player::render()
{

    renderAmmo();
    glPushMatrix();
    glTranslatef(pos.x,pos.y,0);///move player

    glRotatef((pitch*radToDeg-90),0,0,1);

    glCallList(getModelID());

    glPopMatrix();



}

void Player::setPitch(int xm,int ym)
{
    float a = pos.x-xm;
    float b = pos.y-ym;
    if(a>0 && b> 0)
    {
        pitch = atan(b/a);
    }else if(a<0 && b>0)
    {
        pitch =PI + atan(b/a);
    }else if(a<0 && b<0)
    {
        pitch =PI + atan(b/a);
    }else if(a>0 && b<0)
    {
        pitch =2*PI + atan(b/a);
    }
}

void Player::setAmmoType(Ammo *am)
{
    ammoType = am;
}
void Player::shootAmmo()
{
   /// Ammo(float sp,int bumR,int dmgR,int dam, int model);
    Ammo shotAmmo(10,10,20,10,pitch,ammoType->getModelID(),ammoType->getExplodeModel());
    shotAmmo.update(pos.x-17*cos(pitch)+17*sin(pitch),pos.y-17*sin(pitch)-17*cos(pitch));
    ammo.push_back(shotAmmo);
}

void Player::renderAmmo()
{
    for (std::vector<Ammo>::iterator it = ammo.begin() ; it != ammo.end();)
    {
        if(it->frameCD < 0)
        {
            it = ammo.erase(it);
        }
        else
        {
            it->render();
            ++it;
        }

    }
}

Ammo* Player::getAmmoType()
{
    return ammoType;
}

