#ifndef ITEMS_H
#define ITEMS_H

#include "Generated.h"
#include "SimpleClasses.h"
#include "Tile.h"
#include "Terrain.h"

class Item
{
    public:
        virtual std::string& getName();
        virtual sf::Texture& getTexture();
        virtual void draw(sf::RenderTarget &target,Pair_int pos,Pair_int size);
        virtual void useAt(Position target,Terrain &terrain);
        virtual Item* clone() = 0;

        Item();
        Item(int m_quantity);

        int quantity=0;

    private:
        static std::string basename;
};
class ItemTile : public Item
{
    public:
        sf::Texture& getTexture();
        void useAt(Position target,Terrain &terrain);
        void draw(sf::RenderTarget &target,Pair_int pos,Pair_int size);
        Item* clone();

        ItemTile(Tile m_tile);

        Tile tile;
};

#endif // ITEMS_H
