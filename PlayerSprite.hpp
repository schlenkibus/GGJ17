#include "SFML/Graphics.hpp"
	
class PlayerSprite
{
	protected:
		sf::Sprite sprite;
		sf::Texture f1, f2, f3, f4, f5, f6, f7, f8, f9 ,f10; //IDLE
		sf::Texture m1, m2, m3, m4, m5, m6, m7, m8, m9 ,m10;
		sf::RenderWindow* window;
		int step;
		enum moveDir
		{
			left, right, idle
		};
		moveDir dir;
	public:
		PlayerSprite(sf::RenderWindow* window, int type)
		{
			dir = moveDir::idle;
			step = 0;
			if(type == 1)
			{
				f1.loadFromFile("Perso1Standing0.png");
				f2.loadFromFile("Perso1Standing1.png");
				f3.loadFromFile("Perso1Standing2.png");
				f4.loadFromFile("Perso1Standing3.png");
				f5.loadFromFile("Perso1Standing4.png");
				f6.loadFromFile("Perso1Standing5.png");
				f7.loadFromFile("Perso1Standing6.png");
				f8.loadFromFile("Perso1Standing7.png");
				f9.loadFromFile("Perso1Standing8.png");
				f10.loadFromFile("Perso1Standing9.png");
				m1.loadFromFile("Perso1Moving0.png");
				m2.loadFromFile("Perso1Moving1.png");
				m3.loadFromFile("Perso1Moving2.png");
				m4.loadFromFile("Perso1Moving3.png");
				m5.loadFromFile("Perso1Moving4.png");
				m6.loadFromFile("Perso1Moving5.png");
				m7.loadFromFile("Perso1Moving6.png");
				m8.loadFromFile("Perso1Moving7.png");
				m9.loadFromFile("Perso1Moving8.png");
				m10.loadFromFile("Perso1Moving9.png");
			}
			if(type == 2)
			{
				f1.loadFromFile("Perso2Standing0.png");
				f2.loadFromFile("Perso2Standing1.png");
				f3.loadFromFile("Perso2Standing2.png");
				f4.loadFromFile("Perso2Standing3.png");
				f5.loadFromFile("Perso2Standing4.png");
				f6.loadFromFile("Perso2Standing5.png");
				f7.loadFromFile("Perso2Standing6.png");
				f8.loadFromFile("Perso2Standing7.png");
				f9.loadFromFile("Perso2Standing8.png");
				f10.loadFromFile("Perso2Standing9.png");
				m1.loadFromFile("Perso2Moving0.png");
				m2.loadFromFile("Perso2Moving1.png");
				m3.loadFromFile("Perso2Moving2.png");
				m4.loadFromFile("Perso2Moving3.png");
				m5.loadFromFile("Perso2Moving4.png");
				m6.loadFromFile("Perso2Moving5.png");
				m7.loadFromFile("Perso2Moving6.png");
				m8.loadFromFile("Perso2Moving7.png");
				m9.loadFromFile("Perso2Moving8.png");
				m10.loadFromFile("Perso2Moving9.png");
			}
			sprite.setOrigin(121.5f, -10);
			sprite.setScale(0.77f, 0.77f);
			this->window = window;
		}
		void update()
		{	
			step = step + 2;
			if(dir == idle)
			{
				if(step > 0 && step <= 10)
					sprite.setTexture(f1);
				else if(step > 10 && step <= 20)
					sprite.setTexture(f2);
				else if(step > 20 && step <= 30)
					sprite.setTexture(f3);
				else if(step > 30 && step <= 40)
					sprite.setTexture(f4);
				else if(step > 40 &&step <= 50)
					sprite.setTexture(f5);
				else if(step > 50 &&step <= 60)
					sprite.setTexture(f6);
				else if(step > 60 &&step <= 70)
					sprite.setTexture(f7);
				else if(step > 70 &&step <= 80)
					sprite.setTexture(f8);
				else if(step > 80 &&step <= 90)
					sprite.setTexture(f9);
				else if(step > 90 &&step <= 100)
					sprite.setTexture(f10);
				else if( step > 100)
					step = 0;
			}
			else if( dir == left || dir == right)
			{
				step++;
				step++;
				if(step > 0 && step <= 20)
					sprite.setTexture(m1);
				else if(step > 20 && step <= 40)
					sprite.setTexture(m2);
				else if(step > 40 && step <= 60)
					sprite.setTexture(m3);
				else if(step > 60 && step <= 80)
					sprite.setTexture(m4);
				else if(step > 80 &&step <= 100)
					sprite.setTexture(m5);
				else if(step > 100 &&step <= 120)
					sprite.setTexture(m6);
				else if(step > 120 &&step <= 140)
					sprite.setTexture(m7);
				else if(step > 140 &&step <= 160)
					sprite.setTexture(m8);
				else if(step > 160 &&step <= 180)
					sprite.setTexture(m9);
				else if(step > 180 &&step <= 200)
					sprite.setTexture(m10);
				else if( step > 200)
					step = 0;
			}
		}
		sf::Sprite* getSprite()
		{
			return &sprite;
		}
		void setMove(bool t)
		{
			if(t)
				dir = moveDir::left;
			else
			 	dir = moveDir::idle;
		}
};
