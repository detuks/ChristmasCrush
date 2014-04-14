#include "Camera.h"

Camera::Camera()
{
    mX = 0;
    mY = 0;
}


void Camera::update()
{
    ///doesnt let mouse outside
    float pitch = 0;
    SDL_GetMouseState(&mX,&mY);//800,600
    if(mX>790)
        SDL_WarpMouse(mX-5,mY);
    else if( mY<10)
        SDL_WarpMouse(mX,mY+5);
    else if(mX<10)
        SDL_WarpMouse(mX+5,mY);
    else if(mY>590)
        SDL_WarpMouse(mX,mY-5);
    if(mouseCorner())
    {
        float a = 800/2-mX;
        float b = 600/2-mY;
        if(a>0 && b> 0)
        {
            pitch = atan(b/a);
        }
        else if(a<0 && b>0)
        {
            pitch =PI + atan(b/a);
        }
        else if(a<0 && b<0)
        {
            pitch =PI + atan(b/a);
        }
        else if(a>0 && b<0)
        {
            pitch =2*PI +  atan(b/a);
        }

        update(pitch,15);
    }
}

bool Camera::mouseCorner()
{
    if(mX<15 || mX > 800-15)
        return true;
    if(mY < 15 || mY > 600-15)
        return true;
    return false;
}

void Camera::update(float rad, int speed)
{
    pos.x+=speed*cos(rad);
    pos.y+=speed*sin(rad);

    glTranslatef(speed*cos(rad),speed*sin(rad),0);
}

void Camera::setFocusAt(Actor *actor)
{
    glTranslatef(-pos.x,-pos.y,0);
    pos.x=380-actor->pos.x;
    pos.y=280-actor->pos.y;
    glTranslatef(pos.x,pos.y,0);
}
