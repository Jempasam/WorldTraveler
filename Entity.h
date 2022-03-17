#ifndef ENTITY_H
#define ENTITY_H

#include "SimpleClasses.h"
#include "Drawing.h"
#include "Generated.h"
#include "Tile.h"

#include <iostream>

#include <SFML/Graphics.hpp>


class Terrain;

class Entity
{
    public:
        struct Stats
        {
            float weight=0.4;
            float drag=0.2;
            float speed=0.2;
            float bouncyness=1.2;
        };
        Stats stats;
        Pair<float> position;
        Pair<float> velocity;
        Pair<int> size;

};
class BigEntity : public Entity
{
    public:

        BigEntity();
        BigEntity(EntityHitbox m_hitbox);
        enum Direction{up,down,right,left};
        bool move(Pair<float> &velocity,Terrain &terrain);
        void tickPhysic(Terrain &terrain);
        EntityHitbox hitbox;
};
class LivingEntity : public BigEntity
{
    public:
        struct LivingStats
        {
            int speed=10,maxhealth=20;
        };
        bool isDynamic=false;
        LivingStats livingstats;
        int health=20;
        char type;
        enum Animation{standing,walking,attacking};
        Animation livingAnimaton=standing;

        LivingEntity(char m_type);

};

namespace global
{
}


#endif // ENTITY_H
