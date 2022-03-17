#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Inventory.h"

class Player : public LivingEntity
{
    public:
    Player(char m_type);
    void displayInventoryBar(sf::RenderTarget &target,DispPos pos,int width);
    void displayInventory(sf::RenderTarget &target,DispPos pos,int width);
    void moveSlotSelection(char offset);
    Inventory inventory;
    char selectedSlot=0;

    InventoryCase holdeditem;
};


#endif // PLAYER_H
