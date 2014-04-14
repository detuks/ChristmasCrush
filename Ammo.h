#ifndef AMMO_H
#define AMMO_H
#include "Actor.h"

class Ammo : public Actor
{
    public:
        Ammo();
        Ammo(float sp,int bumR,int dmgR,int dam,float pitc, int model,int eModel);
        int frameCD;
        bool exlploded = false;
        void render();
        void step();
        void explode();
        void setExplodeModel(int);
        int getExplodeModel();



    protected:
    private:
        float speed;
        int bumRad;
        int dmgRad;
        int damage;
        int explodeModel;
};

#endif // AMMO_H
