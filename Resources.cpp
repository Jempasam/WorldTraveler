#include "Resources.h"

namespace resources
{
    std::vector<BlockShape> shapes;
    sf::Texture inventorycase;
    sf::Texture chartexmap;
}

BlockShapePart::BlockShapePart()
{
    transpRange=Pair<char>(255,255);

    redRange=Pair<char>(255,255);
    greenRange=Pair<char>(255,255);
    blueRange=Pair<char>(255,255);

    xOffsetRange=Pair<int>(0,0);
    yOffsetRange=Pair<int>(0,0);
    numberRange=Pair<int>(1,1);

    char Probability=100;
}
BlockShapePart::BlockShapePart(std::vector<sf::Texture> m_texture) : BlockShapePart()
{
    texture=m_texture;
}
BlockShape::BlockShape()
{
    size=1;
}
void loadBlockShapes()
{
    std::ifstream file;
    std::string LINE;
    int block=1;

    file.open("resources/blocks/"+IntToString(block)+".txt");
    while(file)
    {
        BlockShape newShape;

        std::getline(file,LINE);
        std::vector<std::string> typeSplit=explode(LINE," ");
        newShape.isBlock=StringToInt(typeSplit[0]);
        newShape.isOver=StringToInt(typeSplit[1]);
        newShape.isItem=StringToInt(typeSplit[2]);

        std::getline(file,LINE);
        newShape.size=StringToInt(LINE);

        while(std::getline(file,LINE))
        {
            std::vector<std::string> splited;
            BlockShapePart newPart;

            splited=explode(LINE," ");
            newPart.redRange=Pair<char>( StringToInt(splited[0]),StringToInt(splited[1]) );

            std::getline(file,LINE); splited=explode(LINE," ");
            newPart.greenRange=Pair<char>( StringToInt(splited[0]),StringToInt(splited[1]) );

            std::getline(file,LINE); splited=explode(LINE," ");
            newPart.blueRange=Pair<char>( StringToInt(splited[0]),StringToInt(splited[1]) );

            std::getline(file,LINE); splited=explode(LINE," ");
            newPart.transpRange=Pair<char>( StringToInt(splited[0]),StringToInt(splited[1]) );


            std::getline(file,LINE); splited=explode(LINE," ");
            newPart.xOffsetRange=Pair<int>( StringToInt(splited[0]),StringToInt(splited[1]) );

            std::getline(file,LINE); splited=explode(LINE," ");
            newPart.yOffsetRange=Pair<int>( StringToInt(splited[0]),StringToInt(splited[1]) );

            std::getline(file,LINE); splited=explode(LINE," ");
            newPart.numberRange=Pair<int>( StringToInt(splited[0]),StringToInt(splited[1]) );


            std::getline(file,LINE);
            newPart.doColor=StringToInt(LINE);
            std::getline(file,LINE);
            newPart.probability=StringToInt(LINE);

            while(std::getline(file,LINE))
            {
                if(LINE=="//")break;
                newPart.texture.push_back(sf::Texture());
                newPart.texture[newPart.texture.size()-1].loadFromFile("resources/blocks/"+LINE+".png");
            }
            newShape.parts.push_back(newPart);
        }
        resources::shapes.push_back(newShape);
        block++;
        file.close();
        file.open("resources/blocks/"+IntToString(block)+".txt");
    }
}
/*void loadMaterials()
{
    std::ifstream file;
    std::string LINE;
    int material=1;

    file.open("resources/materials/"+IntToString(material)+".txt");
    while(file)
    {
        Material newMaterial;

        std::getline(file,LINE);
        newMaterial.hardness=StringToInt(LINE);

        while(std::getline(file,LINE))
        {
            if(LINE=="//")break;
            sf::Color newColor;
            newColor.r=StringToInt(LINE);
            std::getline(file,LINE);newColor.g=StringToInt(LINE);
            std::getline(file,LINE);newColor.b=StringToInt(LINE);
            std::getline(file,LINE);newColor.a=StringToInt(LINE);

            newMaterial.colors.push_back(newColor);
        }
        resources::materials.push_back(newMaterial);
        material++;
        file.close();
        file.open("resources/materials/"+IntToString(material)+".txt");
    }
}*/
