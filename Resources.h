#ifndef RESOURCES_H
#define RESOURCES_H

#include "SimpleClasses.h"
#include "Conversion.h"
#include "SimpleFunction.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>

using uchar=unsigned char;

class BlockShapePart
{
    public:
    std::vector<sf::Texture> texture;

    bool doColor=true;

    Pair<char> transpRange;
    Pair<char> redRange;
    Pair<char> greenRange;
    Pair<char> blueRange;

    Pair<int> xOffsetRange;
    Pair<int> yOffsetRange;

    Pair<int> numberRange;

    uchar probability=100;
    char hardness=30;

    BlockShapePart();
    BlockShapePart(std::vector<sf::Texture> m_texture);
};
class BlockShape
{
    public:
    std::vector<BlockShapePart> parts;

    char size=1;
    bool isBlock,isOver,isItem;

    BlockShape();
};

void loadBlockShapes();
void loadMaterials();


namespace resources
{
    extern std::vector<BlockShape> shapes;
    extern sf::Texture inventorycase;
    extern sf::Texture chartexmap;
}

#endif // RESOURCES_H
