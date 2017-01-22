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
		}
		~Qualle()
		{

		}
		void draw()
		{
			window->draw(shape);
		}
		void update()
		{
			if(shape.getPosition().x <= 
			shape.move(-2, 0);
		}
}:
