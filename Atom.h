#ifndef ATOM_H
#define ATOM_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "SimpleClasses.h"

enum class Value_type{pressure,energy,matiere,allways,TOP};
enum class Sign{equal,greater,smaller,TOP};
enum class Action_type{create_energy,absorb_energy,move,create_matiere,absorb_matiere,push,swap,pull,create_matiere2,TOP};
enum class Angle{up,down,side,center,all,notdown,notup,notside,notcenter,right,left,TOP};
enum class Direction{up,down,right,left,center,TOP};

Direction toDirection(const Angle &angle);
Direction invert(const Direction &direction);
PairI toCoord(const Direction &direction);

struct Condition
{
    bool inverted;

    Value_type value1;
    Angle angle;
    Sign sign;
    float value2;
};
struct Action
{
    Action_type actiontype;
    Angle angle;
    float value1;
    float value2;
    unsigned char probability;
};

struct Interaction
{
    Condition conditions1;
    Condition conditions2;
    Action actions;
};

struct Atom
{
    sf::Color color;
    std::vector<Condition> conditions;
    std::vector<Action> actions;
    int maxChainReaction;
};

struct Molecule
{
    sf::Color color;
    std::vector<Interaction> interactions;
    std::vector<int> components;
    int maxChainReaction;
};
bool test(int value1,Sign,int value2);
#endif // ATOM_H
