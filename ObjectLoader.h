#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H



#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

#include <SDL_image.h>
#define GL_UNSIGNED_INT_8_8_8_8 0x8035
#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Camera.h"
#include "Text.h"
#include "Player.h"
#include "Map.h"
#include "Mob.h"
#include "Ammo.h"
#include "Obstacle.h"

class ObjectLoader
{
    public:
        ObjectLoader();
        void loadObject(const char* filename, std::vector<Obstacle*> *obstacles, std::vector<Mob*> *mobs, float *sx,float *sy);
        unsigned int loadTexture(const char* filename);
        int texture;
        std::string temp;
        int obCount =0;
        Map gameMap;
        Mob evilPing;
        Mob evilPingM;
        Obstacle block1;
        Obstacle block2;

        Obstacle bl[50];
        Obstacle bl2;



    protected:
    private:
        std::vector<std::string*> coord;

};

#endif // OBJECTLOADER_H
