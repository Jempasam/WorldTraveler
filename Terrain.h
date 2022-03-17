#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "SimpleClasses.h"

#include "Tile.h"
#include "Drawing.h"
#include "Display.h"
#include "Generated.h"
#include "Entity.h"

#include <cmath>
#include <vector>
#include <list>

extern sf::BlendMode blendCorrect;
class ActionToDo
{
    public:
    Action *actiontodo;
    int x,y;
    unsigned char chainlength;
    ActionToDo(Action &m_action, int m_x,int m_y,unsigned char m_chainlength);
};
Pair_int getAngleCoord(float angle,float distance);
class Terrain
{
    public:
        Pair_int size;

        Terrain(Pair_int m_size);
        Terrain(int m_x=5000,int m_y=1000);
        void display();
        void collide(Terrain &t);
        void drawCenteredAt(PairF center,int zoom=10);
        void fastDrawCenteredAt(PairF center,int zoom=10,const int jump=1);
        Pair_int dispPosToRealPos(PairF center,int zoom,Pair_int dispPos);
        Pair_int realPosToDispPos(PairF center,int zoom,Pair_int dispPos);
        void tickPhysic();
        bool testCondition(int x,int y,int pressure,Condition &condition);
        void useAction(int x,int y,int chainlength,Action &action);
        void tickInteraction(int x,int y,int p,int chainlength=0);
        void tickEnergy(int x,int y) ;
        void tickWorldEnergy();
        sf::Texture drawPlanet();
        void tickZoneEnergy(int x1,int y1,int x2,int y2);
        void addLivingEntity(LivingEntity &newEntity);
        void generateWorld(int age,float chunkwidth=0.4,float chunkheight=0.15,int simNum=5,int endSimNum=20);
        void addGroundChunk(float chunkwidth,float chunkheight,const std::vector<BlockType*> &unders,const std::vector<BlockType*> &overs);
        void addGroundChunk(float chunkwidth,float chunkheight);
        void equalize();
        void registerLivingEntity(LivingEntity &newEntity);
        void unregisterLivingEntity(LivingEntity &newEntity);
        void removeLivingEntity(int index);
        Tile& getTile(int x,int y);
        void tickZoneInteraction(int x1,int y1,int x2,int y2);
        void tickWorldInteraction();
        void tickSplitedWorldInteraction(int number=10);
        bool pushTile(int x,int y,Direction direction,char strenght);
        bool pullTile(int x,int y,Direction direction,char strenght);
        void uncrustBlock(int x,int y);
        void moveBlock(int x,int y,int x2,int y2);
        void breakBlock(int x,int y);
        void moveTile(int x,int y,int x2,int y2);
        void breakTile(int x,int y);
        void doActionInBuffer();
        void doActionInBuffer(int number);
        void doModification();
        LivingEntity& getLivingEntity(int index);
        void tickTime();

        sf::RenderTexture rendtex;

    private:
        int simulationState=0;
        std::vector<ActionToDo> actionstodo;
        std::vector<std::vector<Tile>> tiles;
        PairF oldcenter;
        int oldzoom=-1;
        int time=0;
        int maxinteration;
        bool ticksplitedmode=true;
        std::vector<LivingEntity*> animals;
};

#endif // TERRAIN_H
