#ifndef HITBOX_H
#define HITBOX_H

#include <vector>
#include <iostream>

#include "SimpleClasses.h"
#include "Tile.h"


namespace global
{
    extern Pair<float> null_pos;
}

using Point=Pair<float>;
using Hitbox=Box<float>;

class EntityHitbox : public Hitbox
{
    public:
    Pair<float> position;

    EntityHitbox();
    EntityHitbox(Pair<float> m_position);
    bool doCollideWith(const Point &point);
    bool doCollideWith(const Hitbox &hitbox);
    bool doCollideWith(const EntityHitbox &ehitbox);
    enum Direction{up,down,right,left};
    bool doCollideWith(Direction direction,const std::vector<std::vector<Tile>> &tiles);
};

#endif // HITBOX_H
