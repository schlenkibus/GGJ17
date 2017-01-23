#include "SFML/Graphics.hpp"
#include <memory>
#include <vector>
#include <list>

//typedef std::shared_ptr<sf::Texture> spTexture;
typedef std::vector<sf::Texture*> vecTextures;

class BackgroundSprites
{
    private:
        vecTextures textures;
        sf::Sprite sprites[6];
        sf::RenderWindow* window;
    public:
        BackgroundSprites(sf::RenderWindow* window)
        {
            this->window = window;
            sf::Texture* temp = new sf::Texture;
            temp->loadFromFile("Cloud1.png");
            textures.emplace_back(temp);
            temp->loadFromFile("Cloud2.png");
            textures.emplace_back(temp);
            temp->loadFromFile("island.png");
            textures.emplace_back(temp);
            temp->loadFromFile("boat.png");
            textures.emplace_back(temp);
            temp->loadFromFile("wind1.png");
            textures.emplace_back(temp);
            temp->loadFromFile("wind2.png");
            textures.emplace_back(temp);
            short z;
            for(auto u: textures)
            {
              sprites[z].setTexture(*u);
            }
            sprites[0].setPosition(500,100);
            sprites[1].setPosition(1500, 130);
            sprites[2].setPosition(1300, 179);
            sprites[3].setPosition(1400, 240);
            sprites[4].setPosition(1300, 400);
            sprites[5].setPosition(300, 300);
        }
        ~BackgroundSprites()
        {
            for(auto u: sprites)
            {
              //  delete u;
            }
        }
        void update()
        {
            for(auto u: sprites)
            {
                if(u.getPosition().x < -500)
                {
                    u.setPosition(1600, u.getPosition().y);
                }
                sprites[0].move(-0.5f, 0);
                sprites[1].move(-0.75f, 0);
                sprites[2].move(-1, 0);
                sprites[3].move(-3, 0);
                sprites[4].move(-5, 0);
                sprites[5].move(-6, 0);
            }
        }
        void draw()
        {
            for(auto u: sprites)
            {
                window->draw(u);
            }
        }
        
};