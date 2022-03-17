#ifndef TEXTURE_H
#define TEXTURE_H

#include <SFML/Graphics.hpp>
#include <array>

namespace global
{
    extern char animationFrame;
    extern char frameTime;
}
class AnimatedTexture
{
    public:
        std::array<sf::Texture,3> texs;
};

#endif // TEXTURE_H
