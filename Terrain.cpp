#include "Terrain.h"
#include <iostream>

void BigEntity::tickPhysic(Terrain &Terrain)
{
    velocity.y+=stats.weight;

    Pair<float> adrag=Pair<float>(stats.drag*velocity.x*-1,stats.drag*velocity.y*-1);

    velocity.x+=adrag.x;
    velocity.y+=adrag.y;

    if(-0.05<velocity.x&&velocity.x<0.05)velocity.x=0;
    if(-0.05<velocity.y&&velocity.y<0.05)velocity.y=0;

    move(velocity,Terrain);
}
const float pi=3.1415926535;
bool BigEntity::move(Pair<float> &velocity,Terrain &terrain)
{
    Pair<int> from,to;

    if(velocity.x>0)
    {
        from.x=int(position.x+hitbox.b.x);          from.y=int(position.y+hitbox.a.y);
        to.x=int(position.x+hitbox.b.x+velocity.x); to.y=int(position.y+hitbox.b.y);

        bool doBreak=false;
        bool doCollide=false;
        for(int x=from.x;x<=to.x;x++)
        {
            for(int y=from.y;y<=to.y;y++)
            {
                if(terrain.getTile(x,y).b.material!=0)
                {
                    doCollide=true;
                    position.x=float(int(x))-0.01-hitbox.b.x;
                    doBreak=true;
                    velocity.x=-velocity.x*stats.bouncyness;
                    break;
                }
            }
            if(doBreak)break;
        }
        if(!doCollide)position.x+=velocity.x;
    }
    else if(velocity.x<0)
    {
        from.x=int(position.x+hitbox.a.x+velocity.x);          from.y=int(position.y+hitbox.a.y);
        to.x=int(position.x+hitbox.a.x); to.y=int(position.y+hitbox.b.y);

        bool doBreak=false;
        bool doCollide=false;
        for(int x=to.x;x>=from.x;x--)
        {
            for(int y=from.y;y<=to.y;y++)
            {
                if(terrain.getTile(x,y).b.material!=0)
                {
                    doCollide=true;
                    position.x=float(int(x))+1.01-hitbox.a.x;
                    doBreak=true;
                    velocity.x=-velocity.x*stats.bouncyness;
                    break;
                }
            }
            if(doBreak)break;
        }
        if(!doCollide)position.x+=velocity.x;
    }

    if(velocity.y>0)
    {
        from.y=int(position.y+hitbox.b.y);          from.x=int(position.x+hitbox.a.x);
        to.y=int(position.y+hitbox.b.y+velocity.y); to.x=int(position.x+hitbox.b.x);

        bool doBreak=false;
        bool doCollide=false;
        for(int y=from.y;y<=to.y;y++)
        {
            for(int x=from.x;x<=to.x;x++)
            {
                if(terrain.getTile(x,y).b.material!=0)
                {
                    doCollide=true;
                    position.y=float(y)-0.01-hitbox.b.y;
                    doBreak=true;
                    velocity.y=-velocity.y*stats.bouncyness;
                    break;
                }
            }
            if(doBreak)break;
        }
        if(!doCollide)position.y+=velocity.y;
    }
    else if(velocity.y<0)
    {
        from.y=int(position.y+hitbox.a.y+velocity.y);          from.x=int(position.x+hitbox.a.x);
        to.y=int(position.y+hitbox.a.y); to.x=int(position.x+hitbox.b.x);

        bool doBreak=false;
        bool doCollide=false;
        for(int y=to.y;y>=from.y;y--)
        {
            for(int x=from.x;x<=to.x;x++)
            {
                if(terrain.getTile(x,y).b.material!=0)
                {
                    doCollide=true;
                    position.y=float(int(y))+1.01-hitbox.a.y;
                    doBreak=true;
                    velocity.y=-velocity.y*stats.bouncyness;
                    break;
                }
            }
            if(doBreak)break;
        }
        if(!doCollide)position.y+=velocity.y;
    }
}
ActionToDo::ActionToDo(Action &m_action, int m_x,int m_y,unsigned char m_chainlength):actiontodo(&m_action),x(m_x),y(m_y),chainlength(m_chainlength)
{
}
void Terrain::collide(Terrain &t)
{
    int width=tiles.size();
    int height=tiles[0].size();
    int pos=getRandNumBetween(0,width-1);

    for(int i=0; i<t.tiles.size(); i++)
    {
        int y;
        for(y=0; y<height; y++)
        {
            if(getTile(pos+i,y).b.material!=0)break;
        }
        int h=t.tiles[0].size()-1;
        for(; y>=0; y--)
        {
            getTile(pos+i,y)=t.getTile(i,h);
            h--;
            if(h<0)break;
        }
    }
}
Tile& Terrain::getTile(int x,int y)
{
    if(x<0)x=size.x+x;
    else if(x>=size.x)x=x-size.x;

    if(y<0)y=0;
    else if(y>=size.y)y=size.y-1;

    return tiles[x][y];
}
void Terrain::addLivingEntity(LivingEntity &newEntity)
{
    animals.push_back(new LivingEntity(newEntity));
}
void Terrain::registerLivingEntity(LivingEntity &newEntity)
{
    animals.push_back(&newEntity);
}
void Terrain::unregisterLivingEntity(LivingEntity &newEntity)
{
    for(int i=0;i<animals.size();i++)
    {
        if(animals[i]==&newEntity)animals.erase(animals.begin()+i);
    }
}
void Terrain::removeLivingEntity(int index)
{
    if(animals[index]->isDynamic)delete animals[index];
    animals.erase(animals.begin()+index);
}

LivingEntity& Terrain::getLivingEntity(int index)
{
    return *animals[index];
}
Terrain::Terrain(Pair_int m_size)
{
    size=m_size;
    for(int x=0;x<size.x;x++)
    {
        tiles.push_back({});
        for(int y=0;y<size.y;y++)
        {
            tiles[x].push_back(Tile());
        }
    }

    rendtex.create(2048,1024);
    rendtex.clear(sf::Color::Transparent);
}
Terrain::Terrain(int m_x,int m_y) : Terrain(Pair_int(m_x,m_y))
{
}
void Terrain::display()
{
    rendtex.display();
}
void Terrain::drawCenteredAt(PairF center,int zoom)
{
    rendtex.clear(sf::Color::Transparent);
    int xmin=int(center.x)-zoom-1, xmax=int(center.x)+zoom+1;
    int ymin=int(center.y)-zoom/2-1, ymax=int(center.y)+zoom/2+1;
    PairF offset=PairF(center.x-int(center.x),center.y-int(center.y));
    float size=2048.0/(zoom*2+1);

    for(int x=xmin;x<=xmax;x++)
    {

        for(int y=ymin;y<=ymax;y++)
        {
            if(getTile(x,y).b.material!=0)
            {
                drawTexture(rendtex,
                        generated::blocks[getTile(x,y).b.material-1][getTile(x,y).b.shape].texture,
                       Pair_int((x-offset.x-xmin-1)*size,(y-offset.y-ymin-1)*size)
                       ,Pair_int(size+1,size+1));
                       //sf::Color((x%2+y%2)*100,255,(x%4+y%4)*50,255)
            }
            if(getTile(x,y).b.over_material!=0)
            {
                drawTexture(rendtex,
                        generated::blocks[getTile(x,y).b.over_material-1][getTile(x,y).b.over_shape].texture,
                       Pair_int((x-offset.x-xmin-1)*size,(y-offset.y-ymin-1)*size)
                       ,Pair_int(size+1,size+1));
                       //sf::Color((x%2+y%2)*100,255,(x%4+y%4)*50,255)
            }
                /*drawSquare(rendtex,
                           Pair_int((x-offset.x-xmin-1)*size,(y-offset.y-ymin-1)*size)
                           ,Pair_int(size,size), sf::Color((x%2+y%2)*100,255,(x%4+y%4)*50,255));*/

            if(int(center.x)==x&&int(center.y)==y)
                drawSquare(rendtex,
                           Pair_int((x-offset.x-xmin-1)*size,(y-offset.y-ymin-1)*size),
                           Pair_int(size,size), sf::Color(255,0,0,255));
        }
    }
    for(int i=0;i<animals.size();i++)
    {
        if(xmin<animals[i]->position.x && animals[i]->position.x<xmax&&
           ymin<animals[i]->position.y && animals[i]->position.y<ymax)
        {
            sf::Texture *texture;
            if(animals[i]->livingAnimaton==LivingEntity::walking)
                texture=&generated::animaltypes[animals[i]->type].walkingtex.texs[global::animationFrame];
            else if(animals[i]->livingAnimaton==LivingEntity::standing)
                texture=&generated::animaltypes[animals[i]->type].standingtex.texs[global::animationFrame];
            else if(animals[i]->livingAnimaton==LivingEntity::attacking)
                texture=&generated::animaltypes[animals[i]->type].attackingtex.texs[global::animationFrame];

            drawTexture(
                        rendtex,
                        *texture,
                        Pair_int( (animals[i]->position.x-offset.x-xmin-1)*size,
                                  (animals[i]->position.y-offset.y-ymin-1)*size  ),
                        Pair_int(animals[i]->size.x*size, animals[i]->size.y*size)
                        );
        }
    }
    oldcenter=center;
    oldzoom=zoom;void fastDrawCenteredAt(PairF center,int zoom);
}
void Terrain::fastDrawCenteredAt(PairF center,int zoom,const int jump)
{
    std::vector<sf::Vertex> vertexs,vertexs_energy;
    rendtex.clear(sf::Color(150,150,150,0));
    int xmin=int(center.x)-zoom-1, xmax=int(center.x)+zoom+2;
    int ymin=int(center.y)-zoom/2-1, ymax=int(center.y)+zoom/2+1;
    PairF offset=PairF(center.x-int(center.x),center.y-int(center.y));

    int size2=2048.0/(zoom*2+1);
    int size=2048.0/(zoom*2+1)*jump;


    for(int x=xmin;x<=xmax;x+=jump)
    {

        for(int y=ymin;y<=ymax;y+=jump)
        {
            Pair_int pos=Pair_int((x-offset.x-xmin-1)*size2,(y-offset.y-ymin-1)*size2);
            Tile &tile=getTile(x,y);
            if(tile.b.material!=0)
            {

                vertexs.push_back(sf::Vertex( sf::Vector2f(pos.x,pos.y),
                                              sf::Vector2f((tile.b.material-1)*64,tile.b.shape*64) ));
                vertexs.push_back(sf::Vertex( sf::Vector2f(pos.x+size,pos.y),
                                              sf::Vector2f((tile.b.material-1)*64+63,tile.b.shape*64) ));
                vertexs.push_back(sf::Vertex( sf::Vector2f(pos.x+size,pos.y+size),
                                              sf::Vector2f((tile.b.material-1)*64+63,tile.b.shape*64+63) ));
                vertexs.push_back(sf::Vertex( sf::Vector2f(pos.x,pos.y+size),
                                              sf::Vector2f((tile.b.material-1)*64,tile.b.shape*64+63) ));
            }
            if(tile.b.over_material!=0)
            {
                vertexs.push_back(sf::Vertex( sf::Vector2f(pos.x,pos.y),
                                              sf::Vector2f((tile.b.over_material-1)*64,tile.b.over_shape*64) ));
                vertexs.push_back(sf::Vertex( sf::Vector2f(pos.x+size,pos.y),
                                              sf::Vector2f((tile.b.over_material-1)*64+63,tile.b.over_shape*64) ));
                vertexs.push_back(sf::Vertex( sf::Vector2f(pos.x+size,pos.y+size),
                                              sf::Vector2f((tile.b.over_material-1)*64+63,tile.b.over_shape*64+63) ));
                vertexs.push_back(sf::Vertex( sf::Vector2f(pos.x,pos.y+size),
                                              sf::Vector2f((tile.b.over_material-1)*64,tile.b.over_shape*64+63) ));
            }
            if(tile.c.type>0)
            {
                sf::Color color=sf::Color( tile.c.type%62%8*28+50, tile.c.type%62/8*28+50, tile.c.type/62*50+50,
                                          tile.c.level/10*9+25);
                vertexs_energy.push_back(sf::Vertex( sf::Vector2f(pos.x,pos.y), color));
                vertexs_energy.push_back(sf::Vertex( sf::Vector2f(pos.x+size,pos.y), color ));
                vertexs_energy.push_back(sf::Vertex( sf::Vector2f(pos.x+size,pos.y+size), color ));
                vertexs_energy.push_back(sf::Vertex( sf::Vector2f(pos.x,pos.y+size), color ));
            }

            if(int(center.x)==x&&int(center.y)==y)
                drawSquare(rendtex,
                           Pair_int((x-offset.x-xmin-1)*size,(y-offset.y-ymin-1)*size),
                           Pair_int(size,size), sf::Color(255,0,0,255));
        }
    }
    rendtex.draw(&vertexs_energy[0],vertexs_energy.size(),sf::Quads,sf::BlendNone);
    rendtex.draw(&vertexs[0],vertexs.size(),sf::Quads,&generated::blockmap);
    rendtex.draw(&vertexs_energy[0],vertexs_energy.size(),sf::Quads,sf::BlendAlpha);
    for(int i=0;i<animals.size();i++)
    {
        if(xmin<animals[i]->position.x && animals[i]->position.x<xmax&&
           ymin<animals[i]->position.y && animals[i]->position.y<ymax)
        {
            sf::Texture *texture;
            if(animals[i]->livingAnimaton==LivingEntity::walking)
                texture=&generated::animaltypes[animals[i]->type].walkingtex.texs[global::animationFrame];
            else if(animals[i]->livingAnimaton==LivingEntity::standing)
                texture=&generated::animaltypes[animals[i]->type].standingtex.texs[global::animationFrame];
            else if(animals[i]->livingAnimaton==LivingEntity::attacking)
                texture=&generated::animaltypes[animals[i]->type].attackingtex.texs[global::animationFrame];

            drawTexture(
                        rendtex,
                        *texture,
                        Pair_int( (animals[i]->position.x-offset.x-xmin-1)*size,
                                  (animals[i]->position.y-offset.y-ymin-1)*size  ),
                        Pair_int(animals[i]->size.x*size, animals[i]->size.y*size)
                        );
        }
    }
    oldcenter=center;
    oldzoom=zoom;
}
sf::Texture Terrain::drawPlanet()
{
    std::vector<sf::Vertex> vertexs,vertexs_energy;
    sf::RenderTexture rendtex;
    rendtex.create(2500,2500);
    rendtex.clear(sf::Color::Transparent);

    int width=tiles.size();
    int height=tiles[0].size();

    float b_h=1000/height;
    float b_w;

    for(int y=0; y<height;y++)
    {
        b_w=2*pi/width;
        for(int x=0; x<width; x++)
        {
            Tile &tile=getTile(x,height-y-1+height/4);
            sf::Vector2f a(1250+cos(x*b_w)*y*b_h,1250+sin(x*b_w)*y*b_h);
            sf::Vector2f b(1250+cos(x*b_w)*(y+1)*b_h,1250+sin(x*b_w)*(y+1)*b_h);
            sf::Vector2f c(1250+cos((x+1)*b_w)*(y+1)*b_h,1250+sin((x+1)*b_w)*(y+1)*b_h);
            sf::Vector2f d(1250+cos((x+1)*b_w)*y*b_h,1250+sin((x+1)*b_w)*y*b_h);

            if(tile.b.material!=0)
            {
                vertexs.push_back(sf::Vertex( a, sf::Vector2f((tile.b.material-1)*64,tile.b.shape*64)));
                vertexs.push_back(sf::Vertex( b, sf::Vector2f((tile.b.material-1)*64,tile.b.shape*64+63)));
                vertexs.push_back(sf::Vertex( c, sf::Vector2f((tile.b.material-1)*64+63,tile.b.shape*64+63)));
                vertexs.push_back(sf::Vertex( d, sf::Vector2f((tile.b.material-1)*64+63,tile.b.shape*64)));
            }
            if(tile.b.over_material!=0)
            {
                vertexs.push_back(sf::Vertex( a, sf::Vector2f((tile.b.over_material-1)*64,tile.b.shape*64)));
                vertexs.push_back(sf::Vertex( b, sf::Vector2f((tile.b.over_material-1)*64,tile.b.shape*64+63)));
                vertexs.push_back(sf::Vertex( c, sf::Vector2f((tile.b.over_material-1)*64+63,tile.b.shape*64+63)));
                vertexs.push_back(sf::Vertex( d, sf::Vector2f((tile.b.over_material-1)*64+63,tile.b.shape*64)));
            }
            if(tile.c.type>0)
            {
                sf::Color color=sf::Color( tile.c.type%62%8*28+50, tile.c.type%62/8*28+50, tile.c.type/62*50+50,
                                          tile.c.level/10*9+25);
                vertexs_energy.push_back(sf::Vertex( a, color));
                vertexs_energy.push_back(sf::Vertex( b, color));
                vertexs_energy.push_back(sf::Vertex( c, color));
                vertexs_energy.push_back(sf::Vertex( d, color));
            }
        }
    }
    rendtex.draw(&vertexs_energy[0],vertexs_energy.size(),sf::Quads,sf::BlendNone);
    rendtex.draw(&vertexs[0],vertexs.size(),sf::Quads,&generated::blockmap);
    rendtex.draw(&vertexs_energy[0],vertexs_energy.size(),sf::Quads,sf::BlendAlpha);
    rendtex.display();
    return rendtex.getTexture();
}
Pair_int Terrain::dispPosToRealPos(PairF center,int zoom,Pair_int dispPos)
{
    int xmin=int(center.x)-zoom-1;
    int ymin=int(center.y)-zoom/2-1;
    PairF offset=PairF(center.x-int(center.x),center.y-int(center.y));

    int size=2048.0/(zoom*2+1);

    return Pair_int(dispPos.x/size+xmin+offset.x+2, dispPos.y/size+ymin+offset.y+1);
}
Pair_int Terrain::realPosToDispPos(PairF center,int zoom,Pair_int realPos)
{
    int xmin=int(center.x)-zoom-1;
    int ymin=int(center.y)-zoom/2-1;
    PairF offset=PairF(center.x-int(center.x),center.y-int(center.y));
    int size=2048.0/(zoom*2+1);

    return Pair_int((realPos.x-offset.x-xmin-1)*size, (realPos.y-offset.y-ymin-1)*size);
}
void Terrain::uncrustBlock(int x,int y)
{
    getTile(x,y).b.over_material=0;
}
void Terrain::moveBlock(int x,int y,int x2,int y2)
{
    Block &block=getTile(x,y).b;
    Block &target=getTile(x2,y2).b;

    target=block;
    block=emptyblock;
}
void Terrain::breakBlock(int x,int y)
{
    Block &block=getTile(x,y).b;

    char stct=block.structure;
    block=emptyblock;

    if(stct==1)breakBlock(x+1,y);
    else if(stct==2)breakBlock(x-1,y);
    else if(stct==3)breakBlock(x,y+1);
    else if(stct==4)breakBlock(x,y-1);
}
void Terrain::moveTile(int x,int y,int x2,int y2)
{
    Tile &tile=getTile(x,y);
    Tile &target=getTile(x2,y2);

    target=tile;
    tile=emptytile;
}
void Terrain::breakTile(int x,int y)
{
    Tile &tile=getTile(x,y);

    breakBlock(x,y);
    tile=emptytile;
}
void Terrain::tickPhysic()
{
    for(int i=0;i<animals.size();i++)
    {
        animals[i]->tickPhysic(*this);
    }
}
bool Terrain::testCondition(int x,int y,int pressure,Condition &condition)
{
    int value1=0;
    switch(condition.value1)
    {
    case Value_type::pressure:
        if(test(pressure,condition.sign,condition.value2*1000))
            return condition.inverted?false:true;
        break;
    case Value_type::energy:
        if( getTile(x,y).c.type>0 && test(getTile(x,y).c.level,condition.sign,1+condition.value2*254) )
            return condition.inverted?false:true;
        break;
    case Value_type::matiere:
        if(getTile(x+1,y).b.material>0 && test(getTile(x+1,y).b.material,condition.sign,condition.value2*(generated::materials.size()-1)) )
            return condition.inverted?false:true;
        else if(getTile(x-1,y).b.material>0 && test(getTile(x-1,y).b.material,condition.sign,condition.value2*(generated::materials.size()-1)))
            return condition.inverted?false:true;
        else if(getTile(x,y+1).b.material>0 && test(getTile(x,y+1).b.material,condition.sign,condition.value2*(generated::materials.size()-1)))
            return condition.inverted?false:true;
        else if(getTile(x,y-1).b.material>0 && test(getTile(x,y-1).b.material,condition.sign,condition.value2*(generated::materials.size()-1)))
            return condition.inverted?false:true;
        else if(getTile(x,y).b.over_material>0 && test(getTile(x,y).b.over_material,condition.sign,condition.value2*(generated::materials.size()-1)))
            return condition.inverted?false:true;
        break;
    }
    return condition.inverted?true:false;
}
void Terrain::doActionInBuffer()
{
    for(int i=0;i<actionstodo.size();i++)
        useAction(actionstodo[i].x,actionstodo[i].y,actionstodo[i].chainlength,*actionstodo[i].actiontodo);
    actionstodo.clear();

    time++;
    if(time>=32399)time=0;
}
void Terrain::doActionInBuffer(int number)
{
    number=actionstodo.size()-number;
    if(number<0)number=0;

    for(int i=actionstodo.size()-1; i>=number; i--)
    {
        useAction(actionstodo[i].x,actionstodo[i].y,actionstodo[i].chainlength,*actionstodo[i].actiontodo);
        actionstodo.pop_back();
    }
}
bool Terrain::pushTile(int x,int y,Direction direction,char strenght)
{
    Pair<int> targpos=toCoord(direction);
    targpos={ x+targpos.x, y+targpos.y };

    if(getTile(targpos.x,targpos.y).b.material>0&&strenght>1)
    {
        if(pushTile(targpos.x,targpos.y,direction,strenght-1))
        {
            moveTile(x,y,targpos.x,targpos.y);
            return true;
        }
    }
    else
    {
        moveTile(x,y,targpos.x,targpos.y);
        return true;
    }
    return false;
}
bool Terrain::pullTile(int x,int y,Direction direction,char strenght)
{
    Pair<int> offset=toCoord(direction);
    for(int i=0;i<strenght;i++)
    {
        if(getTile(x,y).b.material<=0)
        {
            moveTile(x+offset.x,y+offset.y,x,y);
            x+=offset.x;
            y+=offset.y;
        }
    }
    return false;
}
void Terrain::useAction(int x,int y,int chainlength,Action &action)
{
    Direction direction=toDirection(action.angle);
    Pair<int> pos=toCoord(direction);
    pos.x+=x; pos.y+=y;

    Tile &tile=getTile(pos.x,pos.y);

    switch(action.actiontype)
    {
    case Action_type::create_energy:
    {
        int energy=1+action.value1*254;
        int level=action.value2*250;
        if(tile.c.type==0||tile.c.type==energy)
        {
            if(tile.c.level+level>255)
                tile.c.level=255;
            else
                tile.c.level+=level;
            tile.c.type=energy;
        }
        break;
    }
    case Action_type::absorb_energy:
    {
        int energy=1+action.value1*254;
        int level=action.value2*250;
        if(tile.c.type==energy)
        {
            if(tile.c.level-level<0)
            {
                tile.c.level=0;
                tile.c.type=0;
            }
            else tile.c.level-=level;
        }
        break;
    }
    case Action_type::move:
    {
        if(tile.b.material==0)
        {
            moveTile(x,y,pos.x,pos.y);
        }
        else pushTile(x,y,direction,action.value1*20);
        break;
    }
    case Action_type::create_matiere:
    {
        if(action.angle==Angle::center)
        {
            BlockType &encrusttoadd=*generated::overBlock[action.value1*(generated::overBlock.size()-1)];
            if(tile.b.over_material==encrusttoadd.material)
            {
                tile.b.material=encrusttoadd.material;
            }
            else
            {
                tile.b.over_material=encrusttoadd.material;
                tile.b.over_shape=encrusttoadd.shape;
            }
        }
        else
        {
            if(tile.b.material==0)
            {
                BlockType &blocktoadd=*generated::fillerBlock[action.value1*(generated::fillerBlock.size()-1)];
                tile.b.material=blocktoadd.material;
                tile.b.shape=blocktoadd.shape;
            }
            else
            {
                if(pushTile(pos.x,pos.y,direction,action.value2*10))
                {
                    BlockType &blocktoadd=*generated::fillerBlock[action.value1*(generated::fillerBlock.size()-1)];

                    tile.b.material=blocktoadd.material;
                    tile.b.shape=blocktoadd.shape;
                }
            }
            break;
        }
    }
    case Action_type::absorb_matiere:
    {
        breakBlock(pos.x,pos.y);
        break;
    }
    case Action_type::push:
    {
        if(tile.b.material>0)pushTile(pos.x,pos.y,direction,action.value1*30);
        break;
    }
    case Action_type::swap:
    {
        Tile oldtile=getTile(x,y);
        getTile(x,y)=tile;
        tile=oldtile;
        break;
    }
    case Action_type::pull:
    {
        pullTile(pos.x,pos.y,direction,action.value1*30);
        break;
    }
    case Action_type::create_matiere2:
    {
        if(action.angle==Angle::center)
        {
            BlockType &encrusttoadd=*generated::overBlock[action.value1*(generated::overBlock.size()-1)];
            if(tile.b.over_material==0)
            {
                tile.b.over_material=encrusttoadd.material;
                tile.b.over_shape=encrusttoadd.shape;
            }
            else if(tile.b.over_material==encrusttoadd.material)
            {
                tile.b.material=encrusttoadd.material;
            }
        }
        else
        {
            if(tile.b.material==0)
            {
                BlockType &blocktoadd=*generated::fillerBlock[action.value1*(generated::fillerBlock.size()-1)];
                tile.b.material=blocktoadd.material;
                tile.b.shape=blocktoadd.shape;
            }
            else
            {
                if(direction==Direction::left)direction==Direction::right;
                else if(direction==Direction::right)direction==Direction::left;
                else if(direction==Direction::down)direction==Direction::up;
                else if(direction==Direction::up)direction==Direction::down;

                if(pushTile(x,y,direction,action.value2*10))
                {
                    BlockType &blocktoadd=*generated::fillerBlock[action.value1*(generated::fillerBlock.size()-1)];

                    Block &b=getTile(x,y).b;
                    b.material=blocktoadd.material;
                    b.shape=blocktoadd.shape;
                }
            }
        }
        break;
    }
    }
}
void Terrain::addGroundChunk(float chunkwidth,float chunkheight,const std::vector<BlockType*> &unders,const std::vector<BlockType*> &overs)
{
    int maxheight=getRandNumBetween(size.y*0.01,size.y*chunkheight);
    int width=getRandNumBetween((size.x-1)*0.01,(size.x-1)*chunkwidth);
    int pos=getRandNumBetween(0,size.x-1);

    char overprob=getRandNumBetween(1,100);

    for(int y=0;y<width;y++)
    {
        int currentheight=(width-y)*maxheight/width;
        int blocktoadd=currentheight;
        for(int u=size.y-1;u>=0;u--)
        {
            Tile &tile=getTile(pos+y,u);
            if(tile.b.material<=0)
            {
                blocktoadd--;
                if(blocktoadd<=0)break;

                tile.b.structure=-1;

                BlockType &under=*unders[getRandomNumber(unders.size()-1)];
                tile.b.material=under.material+1;
                tile.b.shape=under.shape;

                if(getRandomNumber(100)<overprob)
                {
                    BlockType &over=*overs[getRandomNumber(overs.size()-1)];
                    tile.b.over_material=over.material+1;
                    tile.b.over_shape=over.shape;
                }
            }
        }
        blocktoadd=currentheight;
        for(int u=size.y-1;u>=0;u--)
        {
            Tile &tile=getTile(pos-y-1,u);
            if(tile.b.material<=0)
            {
                blocktoadd--;
                if(blocktoadd<=0)break;

                tile.b.structure=-1;

                BlockType &under=*unders[getRandomNumber(unders.size()-1)];
                tile.b.material=under.material+1;
                tile.b.shape=under.shape;

                if(getRandomNumber(100)<overprob)
                {
                    BlockType &over=*overs[getRandomNumber(overs.size()-1)];
                    tile.b.over_material=over.material+1;
                    tile.b.over_shape=over.shape;
                }
            }
        }
    }
}
void Terrain::addGroundChunk(float chunkwidth,float chunkheight)
{
    std::vector<BlockType*> fillers;
    repeat(i,getRandNumBetween(1,4))
        repeat(y,getRandNumBetween(1,4))
            fillers.push_back(getRandElem(generated::fillerBlock));

    std::vector<BlockType*> overs;
    repeat(i,getRandNumBetween(1,4))
        repeat(y,getRandNumBetween(1,4))
            overs.push_back(getRandElem(generated::overBlock));

    addGroundChunk(chunkwidth,chunkheight,fillers,overs);
}
void Terrain::equalize()
{
    for(int x=0;x<size.x;x+=1)
    {
        for(int y=0;y<size.y-1;y+=1)
        {
            Tile &tile=getTile(x,y);
            if(tile.b.material>0)
            {
                switch(rand()%2)
                {
                case 0:
                    if(getTile(x-1,y+1).b.material<=0)
                    {
                        for(int y2=y+1;y2<size.y-1;y2++)
                            if(getTile(x-1,y2).b.material>0)
                                {moveTile(x,y,x-1,y2-1);break;}
                    }
                    else if(getTile(x+1,y+1).b.material<=0)
                    {
                        for(int y2=y+1;y2<size.y-1;y2++)
                            if(getTile(x+1,y2).b.material>0)
                                {moveTile(x,y,x+1,y2-1);break;}
                    }
                    break;
                case 1:
                    if(getTile(x+1,y+1).b.material<=0)
                    {
                        for(int y2=y+1;y2<size.y-1;y2++)
                            if(getTile(x+1,y2).b.material>0)
                                {moveTile(x,y,x+1,y2-1);break;}
                    }
                    else if(getTile(x-1,y+1).b.material<=0)
                    {
                        for(int y2=y+1;y2<size.y-1;y2++)
                            if(getTile(x-1,y2).b.material>0)
                                {moveTile(x,y,x-1,y2-1);break;}
                    }
                    break;
                }
            }
        }
    }
}
void Terrain::generateWorld(int age,float chunkwidth,float chunkheight,int simNum,int endSimNum)
{
    for(int x=0;x<size.x;x++)
        for(int y=0;y<size.y;y++)
            getTile(x,y)=emptytile;

    sf::Event event;
    for(int i=0;i<age;i++)
    {
        while(global::window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                global::window.close();
                return;
            }
            if (event.type == sf::Event::Resized)
            {
                global::window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                regenerateWindowConfig(global::window);
            }
        }
        drawTexture(global::window,generated::blocks[0][2].texture,Pair_int(0,0),Pair_int(global::window.getSize().x,global::window.getSize().y));
        drawText(global::window,resources::chartexmap,"Age "+intToString(i),DispPos(0,global::window.getSize().y/20),global::window.getSize().y/20);

        //addGroundChunk(chunkwidth,chunkheight);
        addGroundChunk(chunkwidth,chunkheight);
        /*for(int i=0; i<5; i++)
            addGroundChunk(chunkwidth/10,chunkheight/5);*/

        //equalize();

        for(int i=0;i<simNum;i++)tickWorldInteraction();
        global::window.display();
    }
    for(int i=0;i<endSimNum;i++)
    {
        tickWorldInteraction();
        drawTexture(global::window,generated::blocks[1][2].texture,Pair_int(0,0),Pair_int(global::window.getSize().x,global::window.getSize().y));
        drawText(global::window,resources::chartexmap,"Finalizing "+intToString(i),DispPos(0,global::window.getSize().y/20),global::window.getSize().y/20);
        global::window.display();
    }
}
void Terrain::tickInteraction(int x,int y,int p,int chainlength)
{
    Tile &tile=getTile(x,y);
    Material &material=generated::materials[tile.b.material-1];
    Molecule &molecule=generated::molecules[material.molecules[time%material.molecules.size()]];

    if(chainlength>material.maxChainReaction)return;
    for(int i=0;i<molecule.interactions.size();i++)
    {
        if(testCondition(x,y,p,molecule.interactions[i].conditions1)&&testCondition(x,y,p,molecule.interactions[i].conditions2))
        {
            if(getRandNumBetween(0,100)<molecule.interactions[i].actions.probability)
                actionstodo.push_back(ActionToDo(molecule.interactions[i].actions,x,y,chainlength));
        }
    }
}
void Terrain::tickWorldInteraction()
{
    tickWorldEnergy();
    for(int y=1;y<size.y-1;y++)
    {
        for(int x=0;x<size.x;x++)
        {
            if(getTile(x,y).b.material>0)tickInteraction(x,y,0);
        }
    }
    simulationState=0;
    doActionInBuffer();
}
void Terrain::tickEnergy(int x,int y)
{
    Tile &tile=getTile(x,y);
    unsigned char &type=tile.c.type;
    unsigned char &level=tile.c.level;

    if(type>0)
    {
        Tile *target;
        switch(rand()%4)
        {
        case 0: target=&getTile(x+1,y); break;
        case 1: target=&getTile(x-1,y); break;
        case 2: target=&getTile(x,y+1); break;
        case 3: target=&getTile(x,y-1); break;
        }
        if(target->c.type==0||target->c.type==type)
        {
            if(level>0)
            {
                target->c.type=type     ;
                target->c.level+=level/2;
                level-=level/2+level%2;
            }
            else if(rand()%10==0)type=0;
        }
    }
}
void Terrain::tickWorldEnergy()
{
    for(int y=1;y<size.y-1;y++)
    {
        for(int x=0;x<size.x;x++)
        {
            if(getTile(x,y).c.type%16>0)tickEnergy(x,y);
        }
    }
}
void Terrain::tickZoneEnergy(int x1,int y1,int x2,int y2)
{
    for(int x=x1;x<=x2;x++)
    {
        for(int y=y1;y<=y2;y++)
        {
            if(getTile(x,y).c.type%16>0)tickEnergy(x,y);
        }
    }
}
void Terrain::tickTime()
{
    time++;
    if(time>=32399)time=0;
}
void Terrain::tickSplitedWorldInteraction(int number)
{
    if(ticksplitedmode)
    {
        int splitsize=tiles.size()/number;

        tickZoneEnergy(simulationState,1,simulationState+splitsize-1,size.y-1);
        tickZoneInteraction(simulationState,1,simulationState+splitsize-1,size.y-2);
        simulationState+=splitsize;
        if(simulationState>=size.x)
        {
            maxinteration=actionstodo.size()/number;
            ticksplitedmode=false;
            simulationState=0;
        }
    }
    else
    {
        doActionInBuffer(maxinteration);
        if(actionstodo.size()<=0)
        {
            ticksplitedmode=true;
            time++;
            if(time>=32399)time=0;
        }
    }
}
void Terrain::tickZoneInteraction(int x1,int y1,int x2,int y2)
{
    int p;
    for(int x=x1;x<=x2;x++)
    {
        p=0;
        for(int y=y1;y<=y2;y++)
        {
            if(getTile(x,y).b.material>0)
            {
                tickInteraction(x,y,p,0);
                p++;
            }
            else if(p>0)p--;
        }
    }
}
