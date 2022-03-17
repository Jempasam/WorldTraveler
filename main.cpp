#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Terrain.h"
#include "Display.h"
#include "Resources.h"
#include "Entity.h"
#include "Player.h"
void debugAtom()
{
    for(int i=0;i<generated::atoms.size();i++)
        {
            drawSquare(global::window,Pair_int(i%20*50,i/20*50),Pair_int(50,50),generated::atoms[i].color);

            for(int y=0;y<generated::atoms[i].conditions.size();y++)
                drawText(global::window,resources::chartexmap,intToString((int)generated::atoms[i].conditions[y].value1),Pair_int(i%20*50,i/20*50+y*15),15);

            for(int y=0;y<generated::atoms[i].actions.size();y++)
                drawText(global::window,resources::chartexmap,intToString((int)generated::atoms[i].actions[y].actiontype),Pair_int(i%20*50+35,i/20*50+y*15),15);
        }
}
int main()
{
    srand(time(NULL));rand();
    Terrain terrain(5000,1000);
    /*global::testure.loadFromFile("1.png");
    generated::textures.push_back(sf::Texture());
    generated::textures[0].loadFromFile("1.png");
    Block newBlock;
    newBlock.texture=&generated::textures[0];
    newBlock.hardness=10;
    generated::blocks.push_back({newBlock});*/

    loadBlockShapes();
    generateAtoms(50);
    generateMolecules(150);
    generateMaterialsWithMolecules(420);
    for(int i=0;i<10;++i)
    {
        generateBlock(0,0).texture.copyToImage().saveToFile("lol/a"+intToString(i)+".png");
    }

    generateBlocks();
    createPointeBlockList();
    /*std::ifstream l("C:/Users/Sam/Desktop/CodeJeu/samlib/list.txt");
    std::string line;int i=0;
    while(std::getline(l,line))
    {
        generated::fillerBlock[i]->texture.copyToImage().saveToFile("C:/Users/Sam/AppData/Roaming/.minecraft/resourcepacks/Random/assets/minecraft/textures/block/"+line);
        ++i;
    }
    l.close();l.open("C:/Users/Sam/Desktop/CodeJeu/samlib/list2.txt");
    i=0;
    while(std::getline(l,line))
    {
        generated::itemBlock[i]->texture.copyToImage().saveToFile("C:/Users/Sam/AppData/Roaming/.minecraft/resourcepacks/Random/assets/minecraft/textures/item/"+line);
        ++i;
    }
    l.close();l.open("C:/Users/Sam/Desktop/CodeJeu/samlib/list4.txt");
    i=0;
    while(std::getline(l,line))
    {
        generated::overBlock[i]->texture.copyToImage().saveToFile("C:/Users/Sam/AppData/Roaming/.minecraft/resourcepacks/Random/assets/minecraft/textures/block/"+line);
        ++i;
    }
    l.close();l.open("C:/Users/Sam/Desktop/CodeJeu/samlib/list5.txt");
    i=0;
    while(std::getline(l,line))
    {
        generated::overBlock[i]->texture.copyToImage().saveToFile("C:/Users/Sam/AppData/Roaming/.minecraft/resourcepacks/Random/assets/minecraft/textures/particle/"+line);
        ++i;
    }
    std::ofstream lang("C:/Users/Sam/AppData/Roaming/.minecraft/resourcepacks/Random/assets/minecraft/lang/en_us.json");
    l.close();l.open("C:/Users/Sam/Desktop/CodeJeu/samlib/list3.txt");
    std::getline(l,line);
    lang<<"{\n";
    while(std::getline(l,line))
    {
        std::string word="";
        int n=(rand()%7+1);
        for(int i=0;i<n;i++)
        {
            word.push_back("bcdfghjklmnpqrstvwxz"[rand()%20]);
            word.push_back("aeiouy"[rand()%6]);
        }
        word[0]+='A'-'a';
        lang<<"\""<<line<<"\":\""<<word<<"\",\n";
    }
    lang<<"}";
    std::cout<<"["<<generated::itemBlock.size()<<"]";*/
    int zoom=32;
    int jump=1;

    sf::Texture back;back.loadFromFile("back.png");
    sf::Texture back2;back2.loadFromFile("back2.png");
    resources::inventorycase.loadFromFile("inventorycase.png");
    resources::chartexmap.loadFromFile("charmap.png");

    AnimalType newType;
    newType.standingtex.texs[0].loadFromFile("player_s1.png");
    newType.standingtex.texs[1].loadFromFile("player_s2.png");
    newType.standingtex.texs[2].loadFromFile("player_s3.png");
    newType.walkingtex.texs[0].loadFromFile("player_w1.png");
    newType.walkingtex.texs[1].loadFromFile("player_w2.png");
    newType.walkingtex.texs[2].loadFromFile("player_w3.png");
    newType.attackingtex.texs[0].loadFromFile("player_a1.png");
    newType.attackingtex.texs[1].loadFromFile("player_a2.png");
    newType.attackingtex.texs[2].loadFromFile("player_a3.png");
    newType.stats.health=20;newType.stats.speed=10;newType.stats.weight=0.15;
    newType.hitbox.a=Pair<float>(1,0.375);newType.hitbox.b=Pair<float>(2,3);
    generated::animaltypes.push_back(newType);

    Player player=Player(0);
    player.stats.drag=0.15;
    player.stats.weight=0.15;
    player.stats.bouncyness=0.1;
    player.velocity=Pair<float>(1,-1);
    player.size=Pair<int>(3,3);
    terrain.registerLivingEntity(player);

    for(int i=0;i<10;i++)
    {
        ItemTile newItem=ItemTile(Tile(rand()*29.99/RAND_MAX,rand()*4.99/RAND_MAX));newItem.quantity=1000;
        player.inventory.cases[i][7].setItem(new ItemTile(newItem));
    }

    PairF pos=PairF(2500,920);
    Pair_int disp_size,disp_pos;
    bool alreadyClicked=false;

    sf::Event event;
    sf::Clock clock;
    global::window.create(sf::VideoMode(1024,512),"Terrarialike");
    regenerateWindowConfig(global::window);

    //terrain.generateWorld(20,0.5,0.15,5,20);
    terrain.generateWorld(9,0.5,0.15,20,10);

    Terrain meteor_terrain(Pair_int(300,100));
    meteor_terrain.generateWorld(3,0.5,0.5,5,50);

    terrain.collide(meteor_terrain);

    sf::Texture meteor=meteor_terrain.drawPlanet();
    sf::Texture planet=terrain.drawPlanet();

    global::window.setMouseCursorVisible(false);

    for(int i=0; i<1000; i++)
    {
        if(terrain.getTile(5000,i).b.material!=0)
        {
            player.position=Pair<float>(5000,i-1);
            break;
        }
    }

    while(global::window.isOpen())
    {
        sf::sleep(sf::seconds(0.04-clock.getElapsedTime().asSeconds()));
        clock.restart();

        while(global::window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                global::window.close();
            if (event.type == sf::Event::Resized)
            {
                global::window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                regenerateWindowConfig(global::window);
            }
            if(event.type==sf::Event::MouseWheelMoved)
            {
                player.moveSlotSelection(event.mouseWheel.delta*-1);
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(player.velocity.x>-0.5)
                player.velocity.x-=0.2;
            player.livingAnimaton=LivingEntity::walking;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if(player.velocity.x<0.5)
                player.velocity.x+=0.2;
            player.livingAnimaton=LivingEntity::walking;
        }
        else
        {
            player.livingAnimaton=LivingEntity::standing;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)/*&&terrain.getTile(player.position.x+player.hitbox.a.x+(player.hitbox.b.x-player.hitbox.a.x)/2, player.position.y+player.hitbox.b.y+0.5).material!=0*/)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                terrain.getLivingEntity(0).velocity=Pair<float>(-2,-1.5);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                player.velocity=Pair<float>(2,-1.5);
            else
                player.velocity.y=-1.8;

            player.livingAnimaton=LivingEntity::walking;
        }

        if(player.position.x<0)player.position.x=5000+player.position.x;
        if(player.position.x>5000)player.position.x=player.position.x-5000;

        pos=player.position;pos.x+=1.5;pos.y+=1.5;
        disp_size.x=global::window.getSize().y*2,global::window.getSize().y;
        disp_size.y=global::window.getSize().y;
        disp_pos.x=-int(global::window.getSize().y*2-global::window.getSize().x)/2;
        disp_pos.y=0;

        drawTexture(global::window,back,
                    disp_pos,disp_size,
                    sf::Color(150,150,150,255));

        /*if(player.position.y>550&&600)
            drawTexture(global::window,back2,
                    disp_pos,disp_size,
                    sf::Color(150,150,150,(player.position.y-550)*255/50));
        if(player.position.y>600)
            drawTexture(global::window,back2,
                    disp_pos,disp_size,
                    sf::Color(150,150,150,255));*/

        Pair_int blockpos=terrain.dispPosToRealPos(pos, zoom, Pair_int((sf::Mouse::getPosition(global::window).x-disp_pos.x)*2048/disp_size.x, (sf::Mouse::getPosition(global::window).y-disp_pos.y)*1024/disp_size.y));

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&!alreadyClicked)
        {
            int mousex=sf::Mouse::getPosition(global::window).x;
            int mousey=sf::Mouse::getPosition(global::window).y;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)&&
               mousex<global::window.getSize().y&&mousey<global::window.getSize().y/10*8)
            {
                InventoryCase &caseclicked=player.inventory.cases[mousex*9.99/global::window.getSize().y][mousey*79.99/global::window.getSize().y/8];
                player.holdeditem.swap(caseclicked);
                alreadyClicked=true;
            }
            else if(mousex<global::window.getSize().y&&mousey<global::window.getSize().y/10)
            {
                InventoryCase &caseclicked=player.inventory.cases[mousex*9.99/global::window.getSize().y][7];
                player.holdeditem.swap(caseclicked);
                alreadyClicked=true;
            }
            else if(player.holdeditem.isFilled())
            {
                player.holdeditem.useItem(Position(blockpos.x,blockpos.y),terrain);
            }
            else if(player.inventory.cases[player.selectedSlot][7].isFilled())
            {
                player.inventory.cases[player.selectedSlot][7].useItem(Position(blockpos.x,blockpos.y),terrain);
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            terrain.breakTile(blockpos.x,blockpos.y);global::window.getSize().y;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        {
            terrain.getTile(blockpos.x,blockpos.y).c.type=1;
            terrain.getTile(blockpos.x,blockpos.y).c.level=250;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        {
            terrain.getTile(blockpos.x,blockpos.y).c.type=2;
            terrain.getTile(blockpos.x,blockpos.y).c.level=250;
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Middle))
        {
            player.holdeditem.setItem(new ItemTile(terrain.getTile(blockpos.x,blockpos.y)));
            player.holdeditem.getItem().quantity=1000;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            terrain.tickInteraction(blockpos.x,blockpos.y,0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        {
            Tile &tile=terrain.getTile(blockpos.x,blockpos.y);
            std::cout<<"["<<(int)tile.c.level<<":"<<(int)tile.c.type<<"]\n";
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            terrain.tickWorldInteraction();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            terrain.pushTile(blockpos.x,blockpos.y,Direction::up,10);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            planet=terrain.drawPlanet();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))zoom+=2;
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add))zoom-=2;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))jump++;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)&&jump>1)jump--;
        Pair_int dispblockpos=terrain.realPosToDispPos(pos,zoom,blockpos);
        dispblockpos.x=dispblockpos.x*disp_size.x/2048+disp_pos.x;dispblockpos.y=dispblockpos.y*disp_size.y/1024+disp_pos.y;

        terrain.fastDrawCenteredAt(pos,zoom,jump);
        terrain.display();
        drawTexture(global::window,terrain.rendtex.getTexture(),
                    disp_pos,disp_size);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
        {
            player.displayInventory(global::window,DispPos(0,0),global::window.getSize().y);
        }
        else player.displayInventoryBar(global::window,PairI(0,0),global::window.getSize().y);

        if(player.holdeditem.isFilled())
                player.holdeditem.drawCase(global::window,
                                                dispblockpos,
                                                disp_size.y/zoom
                                                );

        else drawSquare(global::window,dispblockpos,Pair_int(disp_size.x/zoom/2,disp_size.y/zoom),sf::Color(0,255,255,80));

        if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))alreadyClicked=false;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
        {
            Tile &tilean=terrain.getTile(blockpos.x,blockpos.y);
            if(tilean.b.material>0)
                drawTexture(global::window,generated::blocks[tilean.b.material-1][tilean.b.shape].texture,Pair_int(0,0),Pair_int(100,100));
            else drawText(global::window,resources::chartexmap,"r",Pair_int(0,0),100);
            if(tilean.b.over_material>0)
                drawTexture(global::window,generated::blocks[tilean.b.over_material-1][tilean.b.over_shape].texture,Pair_int(0,100),Pair_int(100,100));
            else drawText(global::window,resources::chartexmap,"r",Pair_int(0,100),100);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
        {
            drawTexture(global::window,meteor,Pair_int(0,0),Pair_int(global::wHeight,global::wHeight));
            drawTexture(global::window,planet,Pair_int(global::wWidth-global::wHeight,0),Pair_int(global::wHeight,global::wHeight));
        }
        global::window.display();

        terrain.tickPhysic();
        terrain.tickSplitedWorldInteraction(100);
        terrain.tickTime();

        global::frameTime++;
        if(global::frameTime>10)
        {
            global::frameTime=0;
            global::animationFrame++;
            if(global::animationFrame>2)global::animationFrame=0;
        }
    }
    return 0;
}
