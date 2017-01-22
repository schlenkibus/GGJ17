#include "SFML/Graphics.hpp"

class Front
{
	protected:
		sf::RenderWindow* window;	
		sf::Sprite sprite1, sprite2, sprite3;
		std::vector<sf::Texture*> textures; 
		int currStep;
	public:
	Front(sf::RenderWindow* w)
	{
		window = w;
		currStep = 0;
		sf::Texture temp;
		temp.loadFromFile("testFrontwaves.png");
		textures.emplace_back(new sf::Texture(temp));
		/*temp.loadFromFile("WaterParticle2.png");
		textures.emplace_back(new sf::Texture(temp));
		temp.loadFromFile("WaterParticle3.png");
		textures.emplace_back(new sf::Texture(temp));
		temp.loadFromFile("WaterParticle4.png");
		textures.emplace_back(new sf::Texture(temp));
		temp.loadFromFile("WaterParticle5.png");
		textures.emplace_back(new sf::Texture(temp));*/


		sprite1.setTexture(*textures[0]);
		sprite2.setTexture(*textures[0]);
		sprite3.setTexture(*textures[0]);
		sprite2.setPosition(-1244, 700-105);		
		sprite1.setPosition(0, 700-105);
		sprite3.setPosition(1244, 700-105);
	}
	~Front()
	{
		for(auto u: textures)
		{
			delete u;
		}
	}
	void update()
	{
		if(sprite1.getPosition().x < -1245)
			sprite1.setPosition(1244, 700-105);
		if(sprite2.getPosition().x < -1245)
			sprite2.setPosition(1244, 700-105);
		if(sprite3.getPosition().x < -1245)
			sprite3.setPosition(1244, 700-105);

		sprite1.move(-4, 0);
		sprite2.move(-4, 0);
		sprite3.move(-4, 0);
	}
	void draw()
	{
		window->draw(sprite1);
		window->draw(sprite2);
		window->draw(sprite3);
	}
};
