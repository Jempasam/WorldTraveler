#include "Items.h"

std::string Item::basename="nonameitem";

std::string& Item::getName()
{

}
sf::Texture& Item::getTexture()
{
    std::cout<<"ERROR: Virtual method getTexture not overriden!\n";
}
void Item::draw(sf::RenderTarget &target,Pair_int pos,Pair_int size)
{
    std::cout<<"ERROR: Virtual method draw not overriden\n!";
}
void Item::useAt(Position target,Terrain &terrain)
{
    quantity--;
}
Item::Item()
{
    quantity=1;
}
Item::Item(int m_quantity)
{
    quantity=m_quantity;
}




sf::Texture& ItemTile::getTexture()
{
    return generated::blocks[tile.b.material][tile.b.shape].texture;
}
void ItemTile::draw(sf::RenderTarget &target,Pair_int pos,Pair_int size)
{
    if(tile.b.material!=0)
        drawTexture(target,generated::blocks[tile.b.material-1][tile.b.shape].texture,pos,size);

    if(tile.b.over_material!=0)
        drawTexture(target,generated::blocks[tile.b.over_material-1][tile.b.over_shape].texture,pos,size);
}
void ItemTile::useAt(Position target,Terrain &terrain)
{
    Tile &tileselected=terrain.getTile(target.x,target.y);

    if(tileselected.b.material==0)
    {
        tileselected=tile;
        quantity--;
    }
}
Item* ItemTile::clone()
{
    ItemTile *newItemTile=new ItemTile(tile);
    newItemTile->quantity=quantity;
    return newItemTile;
}
ItemTile::ItemTile(Tile m_tile) : Item()
{
    tile=m_tile;
}
