#ifndef TILE_H
#define TILE_H

struct Block
{
    char material=0;
    char shape=0;
    char over_material=0;
    char over_shape=0;
    char structure=0;
};
class Cloud
{
    public:
    unsigned char type=0;
    unsigned char level=0;
};
class Tile
{
    public:
    Block b;
    Cloud c;

    Tile();
    Tile(char m_material,char m_shape);
};
extern Tile emptytile;
extern Block emptyblock;
extern Cloud emptycloud;

#endif // TILE_H
