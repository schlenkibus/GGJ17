#include "SFML/Graphics.hpp"

class Intro
{
protected:
	sf::Texture t1, t2, t3, t4, t5, t6;
	sf::Sprite sprite;
	sf::RenderWindow* window;
public:
	Intro(sf::RenderWindow* window)
	{
		this->window = window;
		t3.loadFromFile("Intro3.png");
	}
};
