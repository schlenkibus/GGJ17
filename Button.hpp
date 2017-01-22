#include "SFML/Graphics.hpp"

class Button
{
	protected:
		sf::RenderWindow* window;
		sf::Sprite sprite;
		sf::Texture tex;
		sf::Font font;
		sf::Text text;
		sf::FloatRect mouse, button;
	public:
		Button(sf::RenderWindow* window, int type, sf::Vector2f pos)
		{	
			this->window = window;
			tex.loadFromFile("button.png");
			font.loadFromFile("Aloha.ttf");
			text.setFont(font);
			if(type == 0)
				text.setString("Play");
			if(type == 1)
				text.setString("Credits");
			if(type == 2)
				text.setString("Exit");
			sprite.setTexture(tex);
			sprite.setPosition(pos.x, pos.y);
			text.setPosition(pos.x, pos.y);
			button.height = sprite.getGlobalBounds().height;
			button.width = sprite.getGlobalBounds().width;
			button.left = sprite.getGlobalBounds().left;
			button.top = sprite.getGlobalBounds().top;
		}
		void update()
		{
			mouse.left =  sf::Mouse::getPosition(*window).x;
        		mouse.top =  sf::Mouse::getPosition(*window).y;
			if(mouse.intersects(button))
			{
				sprite.setColor(sf::Color::Red);
				return;
			}
			//sprite.setColor(sf::Color::White);
		}
		void draw()
		{
			window->draw(sprite);
			window->draw(text);
		}
};
