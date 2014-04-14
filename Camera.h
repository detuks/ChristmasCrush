#ifndef CAMERA_H
#define CAMERA_H

#include "SDL.h"
#include "SDL_opengl.h"
#include <math.h>

#define PI 3.14159265359

#include "Actor.h"

class Camera
{
    public:
        Vec2 pos;
        int mX,mY;
        Camera();
        void update();
        void update(float rad, int speed);
        void setFocusAt(Actor *actor);
    protected:
    private:
        bool mouseCorner();
};

#endif // CAMERA_H
