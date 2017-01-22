#include "SFML/Graphics.hpp"
#include <sstream>
#include <string>
class Score
{
	protected:
		sf::Font font;
		sf::Text text;
		sf::Clock scoreTimer;
		sf::RenderWindow* window;
		sf::Time start, end, curr;
		sf::String scoreStr;
		bool running;
		long score;
		short delay;
		long bonus;
		std::stringstream str;
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
			text.setString("Score: ");
			score = 0;
			delay = 0;
			bonus = 0;
		}
		//~Score();
		void update()
		{
			delay++;
			if(running && delay >= 10)
			{
				score+=bonus+1;
				str.str("");
				str << score;
				scoreStr = "Score: ";
				scoreStr += str.str();
				text.setString(scoreStr);
				delay = 0;
			}
		}
		void draw()
		{
			window->draw(text);
		}
		void setBonus(long value)
		{	
			if(value < 0)
				text.setColor(sf::Color::Red);
			else
				text.setColor(sf::Color::Green);
			bonus = value;
		}
		void setEnd()
		{
			end = scoreTimer.getElapsedTime();
			running = false;
		}
};
