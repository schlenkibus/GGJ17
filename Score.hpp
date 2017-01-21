#include "SFML/Graphics.hpp"

class Score
{
	protected:
		sf::Font font;
		sf::Text text;
		sf::Clock scoreTimer;
		sf::RenderWindow* window;
		sf::Time start, end, curr;
		bool running;
	public:
		Score(sf::RenderWindow* window)
		{
			start = scoreTimer.getElapsedTime();
			running = true;
			this->window = window;
			font.loadFromFile("Aloha.ttf");
			text.setCharacterSize(72);
			text.setColor(sf::Color::Black);
			/*text.setOutlineThickness(3.4f);
			text.setOutlineColor(sf::Color::Black);*/
			text.setFont(font);
			text.setPosition(600, 100);
			text.setString("TEST");
		}
		//~Score();
		void update()
		{
			if(running)
			{
			}
		}
		void draw()
		{
			window->draw(text);
		}
		void setEnd()
		{
			end = scoreTimer.getElapsedTime();
			running = false;
		}
};
