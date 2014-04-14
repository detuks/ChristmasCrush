#ifndef ACTOR_H
#define ACTOR_H
#define PI 3.14159265

#include <math.h>
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"

#include "Vec2.h"

class Actor
{
    public:
        Actor();
        Vec2 pos;
        Vec2 oldPos;
        float pitch;
        int health;
        int width,height;

        float radToDeg = 180/PI;

        void update(float xc,float yc);
        void setTexture(int);
        int getTexture();
        void setModelID(int);
        int getModelID();
        void loadModel(const char*);
    protected:
    private:
        unsigned int loadTexture(const char* filename,int &w,int &h);

        int texture;
        int modelID;
};

#endif // ACTOR_H
