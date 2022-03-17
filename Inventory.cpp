#include "Inventory.h"

InventoryCase::InventoryCase()
{
    item=0;
}

InventoryCase::~InventoryCase()
{
    clear();
}

void InventoryCase::clear()
{
    if(item!=0)
    {
        delete item;
        item=0;
    }
}

Item& InventoryCase::getItem()
{
    return *item;
}
Item* InventoryCase::getItemAdress()
{
    return item;
}
void InventoryCase::setItem(Item *newitem)
{
    if(isFilled())clear();
    item=newitem;
}
void InventoryCase::setItemAdress(Item *newitem)
{
    item=newitem;
}
void InventoryCase::useItem(Position target,Terrain &terrain)
{
    item->useAt(target,terrain);
    if(item->quantity<=0)
    {
        clear();
    }
}
bool InventoryCase::isFilled()
{
    if(item!=0)return true;
    else return false;
}
void InventoryCase::drawCase(sf::RenderTarget &target,DispPos pos,int width)
{
    getItem().draw(target,pos,PairI(width,width));
    drawText(target,resources::chartexmap,IntToString(getItem().quantity),PairI(pos.x+0.1*width,pos.y+0.7*width),width*0.2);
}
void InventoryCase::swap(InventoryCase &invcase)
{
    Item *olditem=item;
    item=invcase.getItemAdress();
    invcase.setItemAdress(olditem);
}
void Inventory::displayInventoryBar(sf::RenderTarget &target,DispPos pos,int width)
{
    float casesize=width/10;
    for(int i=0;i<10;i++)
    {
        drawTexture(target,resources::inventorycase,PairI(pos.x+i*casesize,pos.y),PairI(casesize,casesize));
        if(cases[i][7].isFilled())
        {
            cases[i][7].getItem().draw(target,PairI(pos.x+(i+0.1)*casesize,pos.y+0.1*casesize),PairI(casesize*0.8,casesize*0.8));
        }
    }
}
void Inventory::displayInventory(sf::RenderTarget &target,DispPos pos,int width)
{

    float casesize=width/10;
    for(int y=0;y<8;y++)
    for(int x=0;x<10;x++)
    {
        drawTexture(target,resources::inventorycase,PairI(pos.x+x*casesize,pos.y+y*casesize),PairI(casesize,casesize));
        if(cases[x][y].isFilled())
        {
            cases[x][y].getItem().draw(target,PairI(pos.x+(x+0.1)*casesize,pos.y+(y+0.1)*casesize),PairI(casesize*0.8,casesize*0.8));
        }
    }
}
