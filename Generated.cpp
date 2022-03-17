#include "Generated.h"

namespace generated
{
    std::vector<std::vector<BlockType>> blocks;
    std::vector<BlockType*> fillerBlock;
    std::vector<BlockType*> overBlock;
    std::vector<BlockType*> itemBlock;
    std::vector<AnimalType> animaltypes;
    std::vector<Material> materials;
    std::vector<Atom> atoms;
    std::vector<Molecule> molecules;
    std::vector<Action> energies;

    sf::Texture blockmap;
}
Action generateAction()
{
    Action ret;
    ret.probability=getRandNumBetween(1,120);
    ret.actiontype=getRandEnum<Action_type>();
    ret.angle=getRandEnum<Angle>();
    ret.value1=(float)getRandNumBetween(0,20000)/20000;
    ret.value2=(float)getRandNumBetween(0,20000)/20000;
    return ret;
}
Condition generateCondition()
{
    Condition ret;
    ret.angle=getRandEnum<Angle>();
    ret.value1=getRandEnum<Value_type>();
    ret.value2=(float)getRandNumBetween(0,20000)/20000;
    ret.sign=getRandEnum<Sign>();
    ret.inverted=(bool)getRandNumBetween(0,1);
    return ret;
}
void generateAtoms(int number)
{
    for(int i=0;i<number;i++)
    {
        Atom newAtom;
        newAtom.color=sf::Color(getRandomNumber(255),
                                                   getRandomNumber(255),
                                                   getRandomNumber(255),
                                                   255);
        if(getRandomNumber(3)==1)
            newAtom.color.a=getRandNumBetween(50,255);

        int ifNum=getRandNumBetween(0,3);
        for(int y=0;y<ifNum;y++)
            newAtom.conditions.push_back(generateCondition());

        int thenNum=getRandNumBetween(0,2);
        for(int y=0;y<thenNum;y++)
            newAtom.actions.push_back(generateAction());

        newAtom.maxChainReaction=getRandNumBetween(1,30);

        generated::atoms.push_back(newAtom);
    }
}
void generateMolecules(int number)
{
    for(int i=0;i<number;i++)
    {
        Molecule newMolecules;
        std::vector<int> atoms;

        //SEARCH ATOM COMBINAISON
        int atomnumber;
        bool isClone;
        do
        {
            atomnumber=getRandNumBetween(1,3);
            isClone=false;
            for(int y=0;y<atomnumber;y++)
            {
                atoms.push_back(getRandNumBetween(0,generated::atoms.size()-1));
            }
            for(int y=0;y<generated::molecules.size();y++)
            {
                if(atoms.size()==generated::molecules[y].components.size())
                {
                    isClone=true;
                    for(int u=0; u<atoms.size() && u<generated::molecules[y].components.size() ;u++)
                    {
                        if(atoms[u]!=generated::molecules[y].components[u])
                        {
                            isClone=false;
                            break;
                        }
                    }
                    if(isClone)
                    {
                        atoms.clear();
                    }
                }
            }
        }
        while(isClone);

        //ADD COMPONENTS TO MATERIAL
        newMolecules.components=atoms;

        //ADD COLOR TO MATERIAL
        int red=0,green=0,blue=0,alpha=0,maxChainReaction=0;
        for(int y=0;y<atoms.size();y++)
        {
            red+=generated::atoms[atoms[y]].color.r;
            green+=generated::atoms[atoms[y]].color.g;
            blue+=generated::atoms[atoms[y]].color.b;
            alpha+=generated::atoms[atoms[y]].color.a;
            maxChainReaction+=generated::atoms[atoms[y]].maxChainReaction;
        }
        newMolecules.color.r=red/atoms.size(); newMolecules.color.g=green/atoms.size();
        newMolecules.color.b=blue/atoms.size(); newMolecules.color.a=alpha/atoms.size();
        newMolecules.maxChainReaction=maxChainReaction/atoms.size();

        //MAKE CONDITIONS AND ACTIONS LIST
        std::vector<Condition> conditions;
        std::vector<Action> actions;
        for(int iatom=0;iatom<atoms.size();iatom++)
        {
            Atom &atom=generated::atoms[atoms[iatom]];

            for(int iif=0;iif<atom.conditions.size();iif++)
            {
                conditions.push_back(atom.conditions[iif]);
            }
            for(int ithen=0;ithen<atom.actions.size();ithen++)
            {
                actions.push_back(atom.actions[ithen]);
            }
        }

        int intnum;//number of interactions
        if(conditions.size()/2>actions.size())intnum=conditions.size()/2;
        else intnum=actions.size();

        for(int inti=0;inti<intnum;inti++)
        {
            Interaction newInteraction;
            if(conditions.size()>0)
                newInteraction.conditions1=conditions[(inti*2)%conditions.size()];
            if(conditions.size()>1)
                newInteraction.conditions2=conditions[(inti*2+1)%conditions.size()];
            if(actions.size()>0)
                newInteraction.actions=actions[actions.size()-(inti%actions.size())-1];
            newMolecules.interactions.push_back(newInteraction);
        }

        generated::molecules.push_back(newMolecules);
    }
}
BlockType generateBlock(const int &matId, const int &shapId)
{
    sf::RenderTexture drawtex;
    drawtex.create(64,64);
    drawtex.clear(sf::Color::Transparent);

    Material &material=generated::materials[matId];
    BlockShape &shape=resources::shapes[shapId];
    BlockType newBlock;
    newBlock.size=shape.size;

    int colornum=0;
    for(int partI=0;partI<shape.parts.size();partI++)
    {
        BlockShapePart &part=shape.parts[partI];
        if(getRandomNumber(100)<part.probability)
        {
            int number=getRandNumBetween(part.numberRange.x,part.numberRange.y);
            for(int numI=0;numI<number;numI++)
            {
                if(part.doColor)
                {
                    sf::Color color=sf::Color( material.colors[colornum].r,
                                               material.colors[colornum].g,
                                               material.colors[colornum].b,
                                               material.colors[colornum].a
                                            );
                    color.r+=getRandNumBetween(part.redRange.x,part.redRange.y);
                    color.g+=getRandNumBetween(part.greenRange.x,part.greenRange.y);
                    color.b+=getRandNumBetween(part.blueRange.x,part.blueRange.y);
                    color.a+=getRandNumBetween(part.transpRange.x,part.transpRange.y);
                    colornum++; if(colornum>=material.colors.size())colornum=0;

                    drawTexture(drawtex,
                                part.texture[ getRandomNumber(part.texture.size()-1) ],
                                Pair_int( getRandNumBetween(part.xOffsetRange.x,part.xOffsetRange.y),
                                          getRandNumBetween(part.yOffsetRange.x,part.yOffsetRange.y) ),
                                Pair_int(64,64),
                                color
                                );
                }
                else
                {
                    sf::Color color=sf::Color(255,255,255,255);
                    color.r+=getRandNumBetween(part.redRange.x,part.redRange.y);
                    color.g+=getRandNumBetween(part.greenRange.x,part.greenRange.y);
                    color.b+=getRandNumBetween(part.blueRange.x,part.blueRange.y);
                    color.a+=getRandNumBetween(part.transpRange.x,part.transpRange.y);

                    drawTexture(drawtex,
                                part.texture[ getRandomNumber(part.texture.size()-1) ],
                                Pair_int( getRandNumBetween(part.xOffsetRange.x,part.xOffsetRange.y),
                                          getRandNumBetween(part.yOffsetRange.x,part.yOffsetRange.y) ),
                                Pair_int(64,64),
                                color
                                );
                }
            }
        }
    }
    drawtex.display();
    newBlock.texture=drawtex.getTexture();
    newBlock.isBlock=shape.isBlock;
    newBlock.isItem=shape.isItem;
    newBlock.isOver=shape.isOver;
    newBlock.material=matId;
    newBlock.shape=shapId;
    newBlock.hardness=material.hardness;

    return newBlock;
}
void generateBlocks()
{
    sf::RenderTexture blockmap;
    blockmap.create(generated::materials.size()*64,resources::shapes.size()*64);
    blockmap.clear(sf::Color::Transparent);

    sf::RenderTexture drawtex;drawtex.create(64,64);
    for(int matI=0;matI<generated::materials.size();matI++)
    {
        std::vector<BlockType> blocks;
        for(int shI=0;shI<resources::shapes.size();shI++)
        {
            blocks.push_back(generateBlock(matI,shI));
            drawTexture(blockmap,blocks.back().texture,Pair_int(matI*64,shI*64),Pair_int(64,64));
        }
        generated::blocks.push_back(blocks);
    }
    blockmap.display();
    generated::blockmap=blockmap.getTexture();
}
void generateEnergies(int number)
{
    for(int i=0; i<number; i++)
        generated::energies.push_back(generateAction());
}
void createPointeBlockList()
{
    for(int i=0;i<generated::blocks.size();i++)
    {
        for(int y=0;y<generated::blocks[i].size();y++)
        {
            if(generated::blocks[i][y].isBlock)generated::fillerBlock.push_back(&generated::blocks[i][y]);
            if(generated::blocks[i][y].isOver)generated::overBlock.push_back(&generated::blocks[i][y]);
            if(generated::blocks[i][y].isItem)generated::itemBlock.push_back(&generated::blocks[i][y]);
        }
    }
}
void generateMaterials(int num)
{
    for(int i=0;i<num;i++)
    {
        Material newMaterial;
        int colornumber=getRandNumBetween(1,3);
        for(int y=0;y<colornumber;y++)
        {
            newMaterial.colors.push_back(sf::Color(getRandomNumber(255),
                                                   getRandomNumber(255),
                                                   getRandomNumber(255),
                                                   255));
            if(getRandomNumber(3)==1)
                newMaterial.colors[newMaterial.colors.size()-1].a=getRandNumBetween(50,255);
        }
        newMaterial.hardness=getRandNumBetween(5,20);
        generated::materials.push_back(newMaterial);
    }
}

void generateMaterialsWithMolecules(int num)
{
    for(int i=0;i<num;i++)
    {
        Material newMaterial;
        std::vector<int> molecules;

        //SEARCH ATOM COMBINAISON
        int molecnumber;

        bool isClone;
        do
        {
            molecnumber=getRandNumBetween(1,3);
            for(int y=0;y<molecnumber;y++)
            {
                molecules.push_back(getRandNumBetween(0,generated::molecules.size()-1));
            }
            for(int y=0;y<generated::materials.size();y++)
            {
                if(molecules.size()==generated::materials[y].molecules.size())
                {
                    isClone=true;
                    for(int u=0; u<molecules.size() && u<generated::materials[y].molecules.size() ;u++)
                    {
                        if(molecules[u]!=generated::materials[y].molecules[u])
                        {
                            isClone=false;
                            break;
                        }
                    }
                    if(isClone)
                    {
                        molecules.clear();
                    }
                }
            }
        }
        while(isClone);

        //ADD COMPONENTS TO MATERIAL
        newMaterial.molecules=molecules;
        //ADD COLOR TO MATERIAL
        for(int y=0;y<molecules.size();y++)
        {
            newMaterial.colors.push_back(generated::molecules[molecules[y]].color);
            newMaterial.maxChainReaction+=generated::molecules[molecules[y]].maxChainReaction;
        }
        newMaterial.maxChainReaction/=molecules.size();

        //ADD CHAIN REACTION LENGTH

        newMaterial.hardness=getRandNumBetween(5,20);
        generated::materials.push_back(newMaterial);
    }
}
