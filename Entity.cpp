#include "Entity.h"

namespace global
{
}

BigEntity::BigEntity() : Entity(),hitbox(position)
{

}
BigEntity::BigEntity(EntityHitbox m_hitbox) : Entity(),hitbox(m_hitbox)
{
}
LivingEntity::LivingEntity(char m_type) : BigEntity()
{
    type=m_type;
    stats.weight=generated::animaltypes[m_type].stats.weight;
    livingstats.maxhealth=generated::animaltypes[m_type].stats.health;
    health=livingstats.maxhealth;
    livingstats.speed=generated::animaltypes[m_type].stats.speed;
    hitbox=generated::animaltypes[m_type].hitbox;
}


