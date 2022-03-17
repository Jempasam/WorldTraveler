#include "Atom.h"

Direction toDirection(const Angle &angle)
{
    switch(angle)
    {
        case Angle::up: return Direction::up;
        case Angle::down: return Direction::down;
        case Angle::side:
            switch(rand()%2)
            {
                case 0: return Direction::right;
                case 1: return Direction::left;
            }
        case Angle::center: return Direction::center;
        case Angle::all: return getRandEnum<Direction>();
        case Angle::notdown:
            switch(rand()%4)
            {
                case 0: return Direction::up;
                case 1: return Direction::left;
                case 2: return Direction::right;
                case 3: return Direction::center;
            }
        case Angle::notup:
            switch(rand()%4)
            {
                case 0: return Direction::down;
                case 1: return Direction::left;
                case 2: return Direction::right;
                case 3: return Direction::center;
            }
        case Angle::notside:
            switch(rand()%3)
            {
                case 0: return Direction::up;
                case 1: return Direction::down;;
                case 2: return Direction::center;
            }
        case Angle::notcenter:
            switch(rand()%4)
            {
                case 0: return Direction::down;
                case 1: return Direction::left;
                case 2: return Direction::right;
                case 3: return Direction::up;
            }
        case Angle::right: return Direction::right;
        case Angle::left: return Direction::left;
        default: return Direction::center;
    }
}
Direction invert(const Direction &direction)
{
    switch(direction)
    {
        case Direction::up: return Direction::down;
        case Direction::down: return Direction::up;
        case Direction::left: return Direction::right;
        case Direction::right: return Direction::left;
        case Direction::center: return Direction::center;
    }
}
PairI toCoord(const Direction &direction)
{
    switch(direction)
    {
        case Direction::up: return {0,-1};
        case Direction::down: return {0,1};
        case Direction::left: return {-1,0};
        case Direction::right: return {1,0};
        case Direction::center: return {0,0};
    }
}
bool test(int value1,Sign sign,int value2)
{
    switch(sign)
    {
    case Sign::equal:
        if(value1==value2)return true;
        break;
    case Sign::greater:
        if(value1>value2)return true;
        break;
    case Sign::smaller:
        if(value1<value2)return true;
        break;

    }
    return false;
}
