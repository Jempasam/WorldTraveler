#include "Tile.h"

Tile::Tile()
{
}
Tile::Tile(char m_material,char m_shape)
{
    b.material=m_material;
    b.shape=m_shape;
}

Tile emptytile(0,0);
Block emptyblock;
Cloud emptycloud;
