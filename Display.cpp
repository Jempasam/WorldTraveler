#include "Display.h"

namespace global
{
    sf::RenderWindow window;
    sf::Texture nullTex;
    int wHeight;
    int wWidth;
    int mapXCoord;
    sf::Texture testure;
}

void generateWindowConfig()
{
    global::wHeight=sf::VideoMode::getDesktopMode().height/1.2;
    global::wWidth=sf::VideoMode::getDesktopMode().width/1.2;
    global::mapXCoord=(global::wWidth-global::wHeight)/2;
}
void regenerateWindowConfig(sf::RenderWindow &WINDOW)
{
    global::wHeight=WINDOW.getSize().y;
    global::wWidth=WINDOW.getSize().x;
    global::mapXCoord=(WINDOW.getSize().x-WINDOW.getSize().y)/2;
}
