#include "SFML/Graphics.hpp"
#include "Button.hpp"

class Menu
{
	protected:
		sf::RenderWindow* window;
		sf::Sprite sprite;
		sf::Texture tex;
		Button* button;
		int state = -1;
	public:
		Menu(sf::RenderWindow* window)
		{
			this->window = window;
			tex.loadFromFile("MenuBackground.png");
			sprite.setTexture(tex);
			button = new Button(this->window, 0, sf::Vector2f(400, 200));
		}
		~Menu()
		{
			delete button;
		}
		void draw()
		{
			button->draw();
		}
		void update()
		{
			button->update();
			
		}
		int getState()
		{
			return state;
		}
};
