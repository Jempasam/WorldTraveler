#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <array>

#include "Items.h"
#include "Drawing.h"
#include "SimpleClasses.h"

class InventoryCase
{
    public:
    InventoryCase();
    ~InventoryCase();
    void clear();
    Item& getItem();
    Item* getItemAdress();
    void setItem(Item *newitem);
    void setItemAdress(Item *newitem);
    bool isFilled();
    void useItem(Position target,Terrain &terrain);
    void drawCase(sf::RenderTarget &target,DispPos pos,int width);
    void swap(InventoryCase &invcase);

    private:
    Item *item;
};
class Inventory
{
    public:
    std::array<std::array<InventoryCase,8>,10> cases;
    void displayInventoryBar(sf::RenderTarget &target,DispPos pos,int width);
    void displayInventory(sf::RenderTarget &target,DispPos pos,int width);
};
#endif // INVENTORY_H
