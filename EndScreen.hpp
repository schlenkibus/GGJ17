#pragma once
#include "SFML/Graphics.hpp"
#include "Button.hpp"

class EndScreen
{
	protected:
		sf::RenderWindow* window;
		Button* ende;
		sf::Font font;
		sf::Text text;
		bool active;
	public:
		EndScreen(sf::RenderWindow* w, sf::String scoreText)
		{
			font.loadFromFile("Aloha.ttf");
			text.setFont(font);
			text.setPosition(100, 100);
			text.setString(scoreText);
			active = false;
			window = w;
			ende = new Button(window, 2, sf::Vector2f(100, 200));
		}
		void activate()
		{
			active = true;
		}
		int update() //returns 0 if close
		{
			if(active)
			{
				ende->update();
				if(ende->getPressed())
					return 0;
			}
			return 1;
		}
		void draw()
		{
			if(active)
			{
				window->draw(text);
				ende->draw();
							
			}
		}
};
