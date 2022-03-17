#include "Player.h"

Player::Player(char m_type) : LivingEntity(m_type)
{

}

void Player::displayInventoryBar(sf::RenderTarget &target,DispPos pos,int width)
{
    float casesize=width/10;
    for(int i=0;i<10;i++)
    {
        if(selectedSlot==i)
            drawTexture(target,resources::inventorycase,PairI(pos.x+i*casesize,pos.y),PairI(casesize,casesize),sf::Color(100,255,255));
        else
            drawTexture(target,resources::inventorycase,PairI(pos.x+i*casesize,pos.y),PairI(casesize,casesize));
        if(inventory.cases[i][7].isFilled())
        {
            inventory.cases[i][7].getItem().draw(target,PairI(pos.x+(i+0.1)*casesize,pos.y+0.1*casesize),PairI(casesize*0.8,casesize*0.8));
            drawText(target,resources::chartexmap,IntToString(inventory.cases[i][7].getItem().quantity),PairI(pos.x+(i+0.1)*casesize,pos.y+0.7*casesize),casesize*0.2);
        }

    }
}
void Player::displayInventory(sf::RenderTarget &target,DispPos pos,int width)
{
    float casesize=width/10;
    for(int y=0;y<8;y++)
    for(int x=0;x<10;x++)
    {
        if(y==7&&selectedSlot==x)
            drawTexture(target,resources::inventorycase,PairI(pos.x+x*casesize,pos.y+y*casesize),PairI(casesize,casesize),sf::Color(100,255,255));
        else drawTexture(target,resources::inventorycase,PairI(pos.x+x*casesize,pos.y+y*casesize),PairI(casesize,casesize));
        if(inventory.cases[x][y].isFilled())
        {
            inventory.cases[x][y].getItem().draw(target,PairI(pos.x+(x+0.1)*casesize,pos.y+(y+0.1)*casesize),PairI(casesize*0.8,casesize*0.8));
            drawText(target,resources::chartexmap,IntToString(inventory.cases[x][y].getItem().quantity),PairI(pos.x+(x+0.1)*casesize,(pos.y+0.7+y)*casesize),casesize*0.2);
        }
    }
}

void Player::moveSlotSelection(char offset)
{
    selectedSlot+=offset;
    if(selectedSlot<0)selectedSlot=9;
    else if(selectedSlot>9)selectedSlot=0;
}
