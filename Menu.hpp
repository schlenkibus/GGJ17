#include "SFML/Graphics.hpp"
#include "Button.hpp"
#include "FrontWave2.hpp"

class Menu
{
	protected:
		sf::RenderWindow* window;
		sf::Sprite sprite, logoSprite;
		sf::Texture tex;
		sf::Texture logo;
		Button* startButton, *endButton, *creditsButton;
		int state = -1;
	public:
		Menu(sf::RenderWindow* window)
		{
			this->window = window;
			tex.loadFromFile("MenuBackground.png");
			logo.loadFromFile("Title.png");
			sprite.setTexture(tex);
			logoSprite.setTexture(logo);
			logoSprite.setScale(0.5f, 0.5f);
			logoSprite.setPosition(400, 0);
			startButton = new Button(this->window, 0, sf::Vector2f(200, 200));
			creditsButton = new Button(this->window, 1, sf::Vector2f(200, 300));
			endButton = new Button(this->window, 2, sf::Vector2f(200, 400));
		}
		~Menu()
		{
			delete startButton;
			delete endButton;
			delete creditsButton;
		}
		void draw()
		{
			window->draw(sprite);
			window->draw(logoSprite);
			startButton->draw();
			endButton->draw();
			creditsButton->draw();
			
		}
		void update()
		{
			startButton->update();
			if(startButton->getPressed())
			{
				state = 0;
			}
			endButton->update();
			if(endButton->getPressed())
			{
				state = 1;
			}
			creditsButton->update();
			if(creditsButton->getPressed())
			{
				state = 2;
			}		
		}
		int getState()
		{
			return state;
		}
};
