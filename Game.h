#ifndef GAME_H
#define GAME_H

#define PI 3.14159265359

#include "SDL.h"
#include "SDL_opengl.h"


#include "Camera.h"
#include "Text.h"
#include "Player.h"
#include "ObjectLoader.h"
#include "Map.h"
#include "Mob.h"
#include "Ammo.h"
#include "Obstacle.h"

//#include "Constants.h"

class Game
{
    public:
        Game();
        void init();
        void start();
        void stop();


    protected:
    private:
        ObjectLoader objLoad;
        std::vector<Obstacle*> obstacles;
        std::vector<Mob*> mobs;


        bool debugMode = false;
        int width = 800, height = 600;
        float startX,startY;
        float disc =0;
        SDL_Event event;
        Uint32 startTime;
        ///Objects
        Camera camera;
        Text text;
        Player player;
        Map gameMap;
        Mob evilPing;
        Ammo ammoUsing;
        Ammo explode;
        Obstacle obst;

        ///Buttons
        int arrowKeys;


        ///END Buttons
        bool isRunning,focusPlayer;

        void update();
        void render();
        void debug();
        void readKeyPress(SDL_Event*);
        void setupGame();

        float dist_Point_to_Line( Vec2 P, Vec2 l1, Vec2 l2);
};

#endif // GAME_H
