#include "SFML/Graphics.hpp"

class Shark
{
	protected:
		sf::RenderWindow* window;
		sf::Texture tex;
		sf::Sprite sprite;
		bool inAnim, shouldExit;
		sf::Vector2f goal;
		int delay;
	public:
		Shark(sf::RenderWindow* w)
		{
			delay = 0;
			inAnim = false;
			window = w;
			tex.loadFromFile("SharkBlut.png");
			sprite.setTexture(tex);
			sprite.setPosition(0, 650);
			sprite.setOrigin(150, 0);
		}
		void update()
		{
			if(inAnim)
			{
				std::cout << delay << " " << sprite.getPosition().y << std::endl;
				delay++;
				if(delay <= 30)
					sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y-9);
				else if(delay > 30 && delay < 120)
					sprite.move(0, 7);
				else if(delay >= 120)
				{
					delay = 0;
					sprite.setPosition(sprite.getPosition().x, 650);
					inAnim = false;
				}
			}
		}
		void draw()
		{
			window->draw(sprite);
		}
		void setPlayerPos(sf::Vector2f pos)
		{
			if(inAnim == false)
			{
				inAnim = true;
				goal = pos;
				sprite.setPosition(goal.x, 650);
			}
		}
};
