#pragma once
#include "SFML/Graphics.hpp"

class Front2
{
protected:
	int speed;
	sf::RenderWindow* window;
	sf::Texture tex1, tex2, tex3, tex4, tex5;
	sf::Sprite s1, s2, s3;
	int step;
public:
	Front2(sf::RenderWindow* w)
	{
		step = 0;
		tex1.loadFromFile("WaveDunkel1.png");
		tex2.loadFromFile("WaveDunkel2.png");
		tex3.loadFromFile("WaveDunkel3.png");
		tex4.loadFromFile("WaveDunkel4.png");
		tex5.loadFromFile("WaveDunkel5.png");
		speed = 1;
		s1.setTexture(tex1);
		s2.setTexture(tex1);
		s3.setTexture(tex1);
		s2.setPosition(-1470, 700-250);		
		s1.setPosition(00, 700-250);
		s3.setPosition(1470, 700-250);
		window = w;
	}
	void update()
	{	
		step++;
		if(step > 0 && step <= 12)
		{
			s1.setTexture(tex1);
			s2.setTexture(tex1);
			s3.setTexture(tex1);
		}
		else if(step > 12 && step <= 24)
		{
			s1.setTexture(tex2);
			s2.setTexture(tex2);
			s3.setTexture(tex2);
		}
		else if(step > 24 && step <= 36)
		{
			s1.setTexture(tex3);
			s2.setTexture(tex3);
			s3.setTexture(tex3);
		}
		else if(step > 36 && step <= 48)
		{
			s1.setTexture(tex4);
			s2.setTexture(tex4);
			s3.setTexture(tex4);
		}
		else if(step > 48 &&step <= 60)
		{
			s1.setTexture(tex5);
			s2.setTexture(tex5);
			s3.setTexture(tex5);
		}
		else if( step > 60)
		{
			step = 0;
		}

		if(s1.getPosition().x < -1470)
			s1.setPosition(1470, 700-250);
		if(s2.getPosition().x < -1470)
			s2.setPosition(1470, 700-250);
		if(s3.getPosition().x < -1470)
			s3.setPosition(1470, 700-250);

		s1.move(-speed, 0);
		s2.move(-speed, 0);
		s3.move(-speed, 0);
	}
	void draw()
	{
		window->draw(s1);
		window->draw(s2);
		window->draw(s3);
	}
};
