#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "Actor.h"
#include "Ammo.h"



class Player : public Actor
{
    public:
        Player();
        void updatePos();
        void render();
        void setPitch(int,int);
        void setAmmoType(Ammo *am);
        void shootAmmo();
        void renderAmmo();

        Ammo* getAmmoType();

        std::vector<Ammo> ammo;

    protected:
    private:
        int speed;
        Ammo *ammoType;
};

#endif // PLAYER_H
