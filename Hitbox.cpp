#include "Hitbox.h"

namespace global
{
    Pair<float> null_pos=Pair<float>(0,0);
}

EntityHitbox::EntityHitbox() : Hitbox(),position(global::null_pos)
{
}
EntityHitbox::EntityHitbox(Pair<float> m_position)
{
    position=m_position;
}
bool EntityHitbox::doCollideWith(const Point &point)
{
    if(position.x+a.x<=point.x && point.x<=position.x+b.x&&
       position.y+a.y<=point.y && point.y<=position.y+b.y)return true;
    else return false;
}
bool EntityHitbox::doCollideWith(const Hitbox &hitbox)
{
    if(position.x+b.x<=hitbox.a.x && hitbox.b.x<=position.x+a.x&&
       position.y+b.y<=hitbox.a.y && hitbox.b.y<=position.y+a.y)return true;
    else return false;
}
bool EntityHitbox::doCollideWith(const EntityHitbox &ehitbox)
{
    if(position.x+b.x<=ehitbox.position.x+ehitbox.a.x && ehitbox.b.x<=ehitbox.position.x+position.x+a.x&&
       position.y+b.y<=ehitbox.position.y+ehitbox.a.y && ehitbox.b.y<=ehitbox.position.y+position.y+a.y)return true;
    else return false;
}
bool EntityHitbox::doCollideWith(Direction direction,const std::vector<std::vector<Tile>> &tiles)
{
    switch(direction)
    {
    case up:
        for(int i=position.x+a.x; i<=int(position.x+b.x); i++)
            if(tiles[i][position.y+a.y].b.material!=0)return true;
        break;
    case down:
        for(int i=position.x+a.x; i<=int(position.x+b.x); i++)
            if(tiles[i][position.y+b.y].b.material!=0)return true;
        break;
    case right:
        for(int i=position.y+a.y; i<=int(position.y+b.y); i++)
            if(tiles[position.x+b.x][i].b.material!=0)return true;
        break;
    case left:
        for(int i=position.y+a.y; i<=int(position.y+b.y); i++)
            if(tiles[position.x+a.x][i].b.material!=0)return true;
        break;
    }
    return false;
}
