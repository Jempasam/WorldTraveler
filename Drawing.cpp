#include "Drawing.h"

void drawTexture(sf::RenderTarget &target,const sf::Texture &texture,Pair_int pos,Pair_int size,const sf::BlendMode &blend)
{
    sf::VertexArray sprite=sf::VertexArray(sf::Quads,4);

    sprite[0].position=sf::Vector2f(pos.x,pos.y);
        sprite[0].texCoords=sf::Vector2f(0,0);
    sprite[1].position=sf::Vector2f(pos.x+size.x,pos.y);
        sprite[1].texCoords=sf::Vector2f(texture.getSize().x,0);
    sprite[2].position=sf::Vector2f(pos.x+size.x,pos.y+size.y);
        sprite[2].texCoords=sf::Vector2f(texture.getSize().x,texture.getSize().y);
    sprite[3].position=sf::Vector2f(pos.x,pos.y+size.y);
        sprite[3].texCoords=sf::Vector2f(0,texture.getSize().y);

    sf::RenderStates rendstate(&texture); rendstate.blendMode=blend;
    target.draw(sprite,rendstate);
}
void drawTexture(sf::RenderTarget &target,const AnimatedTexture &texture,Pair_int pos,Pair_int size)
{
    sf::VertexArray sprite=sf::VertexArray(sf::Quads,4);

    sprite[0].position=sf::Vector2f(pos.x,pos.y);
        sprite[0].texCoords=sf::Vector2f(0,0);
    sprite[1].position=sf::Vector2f(pos.x+size.x,pos.y);
        sprite[1].texCoords=sf::Vector2f(texture.texs[global::animationFrame].getSize().x,0);
    sprite[2].position=sf::Vector2f(pos.x+size.x,pos.y+size.y);
        sprite[2].texCoords=sf::Vector2f(texture.texs[global::animationFrame].getSize().x,
                                         texture.texs[global::animationFrame].getSize().y);
    sprite[3].position=sf::Vector2f(pos.x,pos.y+size.y);
        sprite[3].texCoords=sf::Vector2f(0,texture.texs[global::animationFrame].getSize().y);

    target.draw(sprite,&texture.texs[global::animationFrame]);
}
void fillTextArray(std::vector<sf::Vertex> &vertexvector,std::string filler,DispPos pos,int size)
{
    int offset=0;
    float height=0;
    for(int i=0;i<filler.size();i++)
    {
        if('a'<=filler[i]&&filler[i]<='z')
        {
            offset=filler[i]-88;
        }
        else if('A'<=filler[i]&&filler[i]<='Z')
        {
            offset=filler[i]-56;
            height=0.2;
        }
        else if('1'<=filler[i]&&filler[i]<='9')
        {
            offset=filler[i]-49;
        }
        else
        {
            switch(filler[i])
            {
            case '0':
                offset=46;
                break;
            case '.':
                offset=36;
                break;
            case ',':
                offset=37;
                break;
            case '>':
                offset=40;
                break;
            case '<':
                offset=41;
                break;
            case '(':
                offset=42;
                break;
            case ')':
                offset=43;
                break;
            case '[':
                offset=44;
                break;
            case ']':
                offset=45;
                break;
            case ' ':
                offset=-1;
            };
        }
        if(offset!=-1)
        {
            vertexvector.push_back(sf::Vertex(sf::Vector2f(pos.x+i*size, pos.y+0-size*height),sf::Vector2f(offset*32,0)));
            vertexvector.push_back(sf::Vertex(sf::Vector2f(pos.x+(i+1)*size, pos.y+0-size*height),sf::Vector2f(offset*32+31,0)));
            vertexvector.push_back(sf::Vertex(sf::Vector2f(pos.x+(i+1)*size, pos.y+size),sf::Vector2f(offset*32+31,32)));
            vertexvector.push_back(sf::Vertex(sf::Vector2f(pos.x+i*size, pos.y+size),sf::Vector2f(offset*32,32)));
        }
    }
}
void drawText(sf::RenderTarget &target,const sf::Texture &texture,std::string filler,DispPos pos,int size)
{
    std::vector<sf::Vertex> text;
    fillTextArray(text,filler,pos,size);
    target.draw(&text[0],text.size(),sf::Quads,&texture);
}
void drawTexture(sf::RenderTarget &target,const sf::Texture &texture,Pair_int pos,Pair_int size,sf::Color color)
{
    sf::VertexArray sprite=sf::VertexArray(sf::Quads,4);

    sprite[0].position=sf::Vector2f(pos.x,pos.y);
        sprite[0].texCoords=sf::Vector2f(0,0);
        sprite[0].color=color;
    sprite[1].position=sf::Vector2f(pos.x+size.x,pos.y);
        sprite[1].texCoords=sf::Vector2f(texture.getSize().x,0);
        sprite[1].color=color;
    sprite[2].position=sf::Vector2f(pos.x+size.x,pos.y+size.y);
        sprite[2].texCoords=sf::Vector2f(texture.getSize().x,texture.getSize().y);
        sprite[2].color=color;
    sprite[3].position=sf::Vector2f(pos.x,pos.y+size.y);
        sprite[3].texCoords=sf::Vector2f(0,texture.getSize().y);
        sprite[3].color=color;

    target.draw(sprite,&texture);
}
void drawSquare(sf::RenderTarget &target,Pair_int pos,Pair_int size,sf::Color color)
{
    sf::VertexArray sprite=sf::VertexArray(sf::Quads,4);

    sprite[0].position=sf::Vector2f(pos.x,pos.y);
        sprite[0].color=color;
    sprite[1].position=sf::Vector2f(pos.x+size.x,pos.y);
        sprite[1].color=color;
    sprite[2].position=sf::Vector2f(pos.x+size.x,pos.y+size.y);
        sprite[2].color=color;
    sprite[3].position=sf::Vector2f(pos.x,pos.y+size.y);
        sprite[3].color=color;

    target.draw(sprite);
}
void eraseSquare(sf::RenderTarget &target,Pair_int pos,Pair_int size)
{
    sf::VertexArray sprite=sf::VertexArray(sf::Quads,4);

    sprite[0].position=sf::Vector2f(pos.x,pos.y);
        sprite[0].color=sf::Color::Transparent;
    sprite[1].position=sf::Vector2f(pos.x+size.x,pos.y);
        sprite[1].color=sf::Color::Transparent;
    sprite[2].position=sf::Vector2f(pos.x+size.x,pos.y+size.y);
        sprite[2].color=sf::Color::Transparent;
    sprite[3].position=sf::Vector2f(pos.x,pos.y+size.y);
        sprite[3].color=sf::Color::Transparent;

    target.draw(sprite,sf::BlendNone);
}
