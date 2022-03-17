#ifndef DRAWING_H
#define DRAWING_H

#include <SFML/Graphics.hpp>

#include "SimpleClasses.h"
#include "Texture.h"

void drawTexture(sf::RenderTarget &target,const sf::Texture &texture,Pair_int pos,Pair_int size,const sf::BlendMode &blend=sf::BlendAlpha);
void drawTexture(sf::RenderTarget &target,const AnimatedTexture &texture,Pair_int pos,Pair_int size);
void drawTexture(sf::RenderTarget &target,const sf::Texture &texture,Pair_int pos,Pair_int size,sf::Color color);
void drawSquare(sf::RenderTarget &target,Pair_int pos,Pair_int size,sf::Color color);
void eraseSquare(sf::RenderTarget &target,Pair_int pos,Pair_int size);
void fillArray(std::vector<sf::Vertex> vertexvector,std::string filler,DispPos pos,int size);
void drawText(sf::RenderTarget &target,const sf::Texture &texture,std::string filler,DispPos pos,int size);

#endif // DRAWING_H
