#ifndef GENERATED_H
#define GENERATED_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "Resources.h"
#include "Drawing.h"
#include "SimpleClasses.h"
#include "Hitbox.h"
#include "Atom.h"



class AnimalType
{
    public:
        AnimatedTexture standingtex;
        AnimatedTexture walkingtex;
        AnimatedTexture attackingtex;
        struct Stats
        {
            int health=20;
            float speed=10;
            float weight=20;
        };
        Stats stats;
        EntityHitbox hitbox;
};
class BlockType
{
    public:
    sf::Texture texture;
    bool isBlock,isOver,isItem;
    int material,shape;
    int hardness;
    int size;
};
class Material
{
    public:
    std::vector<sf::Color> colors;
    std::vector<int> molecules;
    int maxChainReaction;
    uchar hardness=30;
};
namespace generated
{
    extern std::vector<std::vector<BlockType>> blocks;
    extern std::vector<BlockType*> fillerBlock;
    extern std::vector<BlockType*> overBlock;
    extern std::vector<BlockType*> itemBlock;
    extern std::vector<Atom> atoms;
    extern std::vector<Molecule> molecules;
    extern std::vector<AnimalType> animaltypes;
    extern sf::Texture blockmap;
    extern std::vector<Material> materials;
    extern std::vector<Action> energies;
}
BlockType generateBlock(const int &matId, const int &shapId);
void generateBlocks();
void generateAtoms(int number);
void generateMaterials(int num);
void generateMolecules(int num);
void createPointeBlockList();
void generateMaterialsWithMolecules(int num);

#endif // GENERATED_H
