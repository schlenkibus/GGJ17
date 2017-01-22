#include "SFML/Graphics.hpp"

class UI
{
	protected:
		sf::RenderWindow* window;
		sf::Texture texReady, texCharging;
		sf::Sprite sprite;
	public:
		UI(sf::RenderWindow* window)
		{
			texReady.loadFromFile("JumpReady.png");
			texCharging.loadFromFile("JumpCharging.png");
			sprite.setPosition(50, 50);
			sprite.setTexture(texCharging);
			this->window = window;
		}
		void setReady(bool ready)
		{
			if(ready)
				sprite.setTexture(texReady);
			else
				sprite.setTexture(texCharging);
		}
		void draw()
		{
			window->draw(sprite);
		}
};
