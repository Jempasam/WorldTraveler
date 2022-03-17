#ifndef DISPLAY_H
#define DISPLAY_H

#include "SFML/Graphics.hpp"

namespace global
{
    extern sf::RenderWindow window;
    extern sf::Texture nullTex;
    extern int wHeight;
    extern int wWidth;
    extern int mapXCoord;
    extern sf::Texture testure;
}

void generateWindowConfig();
void regenerateWindowConfig(sf::RenderWindow &WINDOW);

#endif // DISPLAY_H
