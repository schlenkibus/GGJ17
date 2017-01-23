#pragma once
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
		bool pressed;
	public:
		bool getPressed()
		{
			return pressed;
		}
		Button(sf::RenderWindow* window, int type, sf::Vector2f pos)
		{	
			this->window = window;
			tex.loadFromFile("button.png");
			font.loadFromFile("Aloha.ttf");
			text.setFont(font);
			text.setCharacterSize(40);
			if(type == 0)
			{
				text.setString("Play");
				text.setPosition(pos.x + 55, pos.y + 2);
			}
			if(type == 1)
			{
				text.setString("Credits");
				text.setPosition(pos.x + 40, pos.y + 2);
			}
			if(type == 2)
			{
				text.setString("Exit");
				text.setPosition(pos.x + 55, pos.y + 2);
			}
			sprite.setTexture(tex);
			sprite.setPosition(pos.x, pos.y);

			button.height = sprite.getGlobalBounds().height;
			button.width = sprite.getGlobalBounds().width;
			button.left = sprite.getGlobalBounds().left;
			button.top = sprite.getGlobalBounds().top;
			pressed = false;
		}
		void update()
		{
			mouse.left =  sf::Mouse::getPosition(*window).x;
        		mouse.top =  sf::Mouse::getPosition(*window).y;
			mouse.height = 1;
			mouse.width = 1;
			if(button.intersects(mouse))
			{
				sprite.setColor(sf::Color(255, 255, 0));
				sprite.setScale(1.01f, 1.01f);
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					pressed = true;
				}
				return;
			}
			else
			{
				sprite.setColor(sf::Color::White);
				sprite.setScale(1.f, 1.f);
			}
		}
		void draw()
		{
			window->draw(sprite);
			window->draw(text);
		}
};
