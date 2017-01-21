#include "SFML/Graphics.hpp"
#include <vector>
class WaveSprites //Class for front stuff
{
	protected:
		sf::RenderWindow* window;	
		sf::Sprite sprite;
		std::vector<sf::Texture*> textures; 
		int currStep;
	public:
	WaveSprites(sf::RenderWindow* w)
	{
		window = w;
		currStep = 0;
		sf::Texture temp;
		temp.loadFromFile("animationAllWave1.png");
		textures.emplace_back(new sf::Texture(temp));
		temp.loadFromFile("animationAllWave2.png");
		textures.emplace_back(new sf::Texture(temp));
		temp.loadFromFile("animationAllWave3.png");
		textures.emplace_back(new sf::Texture(temp));
		temp.loadFromFile("animationAllWave4.png");
		textures.emplace_back(new sf::Texture(temp));
		temp.loadFromFile("animationAllWave5.png");
		textures.emplace_back(new sf::Texture(temp));

		sprite.setTexture(*textures[0]);

		sprite.setPosition(0, 347);
	}
	~WaveSprites()
	{
		for(auto u: textures)
		{
			delete u;
		}
	}
	void update()
	{
		currStep++;
		if(currStep <= 12 && currStep != 0) 
			sprite.setTexture(*textures[0]);
		else if(currStep >= 13 && currStep <= 24)
			sprite.setTexture(*textures[1]);
		else if(currStep >= 25 && currStep <= 36)
			sprite.setTexture(*textures[2]);
		else if(currStep >= 37 && currStep <= 48)
			sprite.setTexture(*textures[3]);
		else if(currStep >= 49 && currStep <= 60)
			sprite.setTexture(*textures[4]);
		if(currStep >= 60) //1 sec
		{
			currStep = 0;
		}
	}
	void draw()
	{
		window->draw(sprite);
	}
	protected:
	
};
