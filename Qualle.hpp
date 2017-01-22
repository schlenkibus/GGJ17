#include "SFML/Graphics.hpp"

class Qualle
{
	protected:
		sf::RenderWindow* window;
		sf::Texture tex;
		sf::Sprite sprite;
	public:
		Qualle(sf::RenderWindow* window)
		{
			this->window = window;
			tex.loadFromFile("Qualle.png");
			sprite.setTexture(tex);
			sprite.setPosition(1333, 550);
		}
		~Qualle()
		{

		}
		void draw()
		{
			window->draw(sprite);
		}
		void update()
		{
			if(sprite.getPosition().x >= 30)		
				sprite.move(-2, 0);
			else
				sprite.move(-2000, 0);
		}
};
