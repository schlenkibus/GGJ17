#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include <cstdlib>
#include <random>
#include "waveSprites.hpp"
#include "Score.hpp"
#include "wassserPartikel.hpp"
#include "frontWaves.hpp"

enum CATEGORY_BITS
{
    BODY1_CATEGORY_BITS = 0x00000001,
    BODY2_CATEGORY_BITS = 0x00000002,
    BODY3_CATEGORY_BITS = 0x00000004,
};

//GLOBAL STUFF
b2Vec2 normaleWelle[6];

//Please dont judge me

b2Vec2 Gravity(0.f, 198.1f);
b2World World(Gravity);
float boardPos = 0;
bool down = true;

#define SCALE 1
#define acc 1.5
#define randMaxX 40
sf::Vector2f minMove(20, 10);
b2Body* CreateBox(b2World& World, int MouseX, int MouseY) //Board
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(MouseX, MouseY);
	BodyDef.type = b2_dynamicBody;
	b2Body* Body = World.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((200)/SCALE, (5)/SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.0125f; //Fläche ist 4000 -> 50kg
	FixtureDef.friction = 0.2f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
	std::cout << "Wippe created" << std::endl;
	return Body;
}

b2Body* CreateStatic(b2World& World, int x, int y)
{
	b2PolygonShape Shape;
  	Shape.Set(normaleWelle, 6);

	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(x, y);
	BodyDef.type = b2_staticBody;
	b2Body* Body = World.CreateBody(&BodyDef);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 2.f; 
	FixtureDef.friction = 1.f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
	return Body;
}

void addForceBoard(float x, float y, b2Body* board, b2Body* player1, b2Body* player2)
{
	board->ApplyForce(b2Vec2(x*75, y*75), board->GetWorldCenter(), true);
}

void addRandomForce(b2Body* board)
{
	int random_force = std::rand()%50+300;
	int random_dir = rand() % 4;
	b2Vec2 temp;
	switch(random_dir)
	{
		case 0:
			//up;
			temp.y = -random_force*board->GetMass()*2;
		break;
		case 1:
			temp.y = random_force*board->GetMass()*2;
			//down;
		break;
		case 2:
			if(board->GetTransform().p.x >= randMaxX + 622)
				random_force = random_force * -1;
			temp.x = random_force*board->GetMass()*20;
			//left;
		break;
		case 3:
			if(board->GetTransform().p.x <= -randMaxX + 622)
				random_force = random_force * -1;
			temp.x = -random_force*board->GetMass()*20;
			//right
		break;
	}
	board->ApplyForce(temp, board->GetWorldCenter(), true);
}

int main()
{
	 std::srand(std::time(0)); // use current time as seed for random generator
	//Welllelele
	normaleWelle[0].Set(-65,  75);
	normaleWelle[1].Set(-50, 40);
	normaleWelle[2].Set(-20,  15);
	normaleWelle[3].Set( 20, 0);
	normaleWelle[4].Set( 70,  0);
	normaleWelle[5].Set(100, 10);

	sf::Sprite SpriteWippe, SpritePlayer1, SpritePlayer2;
	sf::RenderWindow window(sf::VideoMode(1244, 700), "BOX2D",  sf::Style::Close);
	WaveSprites sprites(&window);
	Partikel wasserSpritzer(&window);
	Front front(&window);
	Score score(&window);
	sf::Event event;
	sf::Texture GroundTexture, BoxTexture;
	sf::Clock player1MinMoveClock, player2MinMoveClock;
	sf::Time player1lastTime, player2lastTime;
	b2Body* board = CreateBox(World, 622, 350);
	b2Body* fix = CreateStatic(World, 622, board->GetPosition().y + 5);

	//Player 1 /75x131
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(530/SCALE, 200/SCALE);
	BodyDef.type = b2_dynamicBody;
	BodyDef.position.Set(530.f, 2.0f);
	//BodyDef.gravityScale = 3.0f;
	b2Body* Player1 = World.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((37.5f)/SCALE, (133)/SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.2f;
	FixtureDef.friction = 0.2f;
	FixtureDef.filter.categoryBits = BODY1_CATEGORY_BITS;
	FixtureDef.filter.maskBits = BODY1_CATEGORY_BITS | BODY2_CATEGORY_BITS;
	FixtureDef.shape = &Shape;
	Player1->CreateFixture(&FixtureDef);
	//Player 2
	b2BodyDef BodyDef2;
	BodyDef2.position = b2Vec2(630/SCALE, 200/SCALE);
	BodyDef2.type = b2_dynamicBody;
	//BodyDef2.gravityScale = 3.0f;
	b2Body* Player2 = World.CreateBody(&BodyDef2);

	b2PolygonShape Shape2;
	Shape2.SetAsBox((37.5f)/SCALE, (133)/SCALE);
	b2FixtureDef FixtureDef2;
	FixtureDef2.density = 0.2f;
	FixtureDef2.friction = 0.2f;
	FixtureDef2.shape = &Shape2;
	FixtureDef2.filter.categoryBits = BODY3_CATEGORY_BITS;
   	FixtureDef2.filter.maskBits = BODY3_CATEGORY_BITS | BODY1_CATEGORY_BITS;
	Player2->CreateFixture(&FixtureDef2);
	
	//Massdata
	b2MassData PlayerMass;
	PlayerMass.mass = 90;
	PlayerMass.center = b2Vec2(0, 131);
	PlayerMass.I = 0;

	Player2->SetMassData(&PlayerMass);
	Player1->SetMassData(&PlayerMass);

	//SFML
	sf::Texture BigWaveTex;
	BigWaveTex.loadFromFile("BigWave.png");
	sf::Sprite bigWave;
	bigWave.setTexture(BigWaveTex);
	sf::Texture BackgroundTex;
	BackgroundTex.loadFromFile("background.png");
	sf::Sprite Background;
	Background.setPosition(0, 0);
	Background.setTexture(BackgroundTex);
	GroundTexture.loadFromFile("ground.png");
	BoxTexture.loadFromFile("box.png");
	window.setFramerateLimit(60);

	//Debug
	sf::CircleShape fixPunktS;
	fixPunktS.setPosition(fix->GetPosition().x,fix->GetPosition().y);
	fixPunktS.setRadius(5);
	fixPunktS.setFillColor(sf::Color::Red);
	//Vaiables
	float impulse;
	float impulse2;

	//Score stuff
	sf::Vector2f player1last;
	sf::Vector2f player2last;
	//INIT
	SpritePlayer2.setTexture(BoxTexture);
	SpritePlayer2.setColor(sf::Color::Blue);
	SpritePlayer2.setOrigin(37.5, 0);
	SpriteWippe.setTexture(GroundTexture); //400x10px
	SpriteWippe.setOrigin(200,10);
	SpritePlayer1.setTexture(BoxTexture); 
	SpritePlayer1.setOrigin(37.5, 0);
	bigWave.setPosition(605, 347);
	bigWave.setOrigin(bigWave.getGlobalBounds().width / 2, 0);

	player1last = SpritePlayer1.getPosition();	
	player2last = SpritePlayer2.getPosition();	
	player1lastTime = player1MinMoveClock.getElapsedTime();	
	player2lastTime = player2MinMoveClock.getElapsedTime(); 

	int bonusDelay = 0;	
	bool player1inactive = false;
	bool player2inactive = false;
	bool activenow1 = true;
	bool activenow2 = true;
	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}
		
		//How to apply force to bodys?
		impulse = Player1->GetMass() * 600;
		impulse2 = Player2->GetMass() * 600;
		//Player 1
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Player1->ApplyForce( b2Vec2(impulse,0), Player1->GetWorldCenter() , true);
			activenow1 = true;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			Player1->ApplyForce( b2Vec2(-impulse,0), Player1->GetWorldCenter() , true);
			activenow1 = true;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			Player1->ApplyForce( b2Vec2(0,Player1->GetMass() * 600), Player1->GetWorldCenter() , true);
		}
		//Player 2
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			Player2->ApplyForce( b2Vec2(impulse,0), Player2->GetWorldCenter() , true);
			activenow2 = true;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			Player2->ApplyForce( b2Vec2(-impulse,0), Player2->GetWorldCenter() , true);
			activenow2 = true;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			Player2->ApplyForce( b2Vec2(0,Player2->GetMass() * 600), Player2->GetWorldCenter() , true);
		}
		//Point system
		if(Player1->GetTransform().p.y >= 600 || Player2->GetTransform().p.y >= 600)
		{
			score.setEnd();
		}
		//TEMP 
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			addForceBoard(0, board->GetMass() * -600, board, Player1, Player2);
		}
		//if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		//{
			//std::cout << "random force" << std::endl;
			addRandomForce(board);
		//}
		//Score negative bonus
		if(SpritePlayer2.getPosition().x- player2last.x < -minMove.x ||  
		SpritePlayer2.getPosition().x- player2last.x > minMove.x && activenow2)
		{
			if(player2MinMoveClock.getElapsedTime().asSeconds() - player2lastTime.asSeconds() >= 2)
			{
				activenow2 = false;
				score.setBonus(-2);
				player2last = SpritePlayer2.getPosition();
				player2lastTime = player2MinMoveClock.getElapsedTime();
			}
		}
		if(SpritePlayer1.getPosition().x- player1last.x < -minMove.x ||  
		SpritePlayer1.getPosition().x- player1last.x > minMove.x && activenow1)
		{
			if(player1MinMoveClock.getElapsedTime().asSeconds() - player1lastTime.asSeconds() >= 2)
			{
				activenow1 = false;
				score.setBonus(-2);
				player1last = SpritePlayer1.getPosition();
				player1lastTime = player1MinMoveClock.getElapsedTime();
			}
		}
		if(activenow2 && activenow1)
		{
			if(bonusDelay >= 30)
			{
				bonusDelay = 0;
				score.setBonus(0);
			}
			else
			{
				bonusDelay++;
			}
		}
		World.Step(1/60.f, 8, 3);
		window.clear(sf::Color::Black);
		window.draw(Background);		
		//Handle Wippe	
		SpriteWippe.setPosition(board->GetPosition().x, board->GetPosition().y);
		SpriteWippe.setRotation(180/b2_pi * board->GetAngle());
		window.draw(SpriteWippe);
		//Player1 //75x131
		SpritePlayer1.setRotation(180/b2_pi * Player1->GetAngle());
		SpritePlayer1.setPosition(SCALE * Player1->GetPosition().x, SCALE * Player1->GetPosition().y);
		window.draw(SpritePlayer1);
		//Player2
		SpritePlayer2.setRotation(180/b2_pi * Player2->GetAngle());
		SpritePlayer2.setPosition(SCALE * Player2->GetPosition().x, SCALE * Player2->GetPosition().y);
		window.draw(SpritePlayer2);
		sprites.update();
		wasserSpritzer.update();
		score.update();
		front.update();
		//fixPunktS.setPosition(Player1->GetWorldCenter().x, Player1->GetWorldCenter().y);
		//window.draw(fixPunktS);		
		sprites.draw();
		wasserSpritzer.draw();
		score.draw();
		front.draw();
		for(int i = 0; i < (sizeof(normaleWelle)/sizeof(*normaleWelle)); i++)
		{
			sf::Vector2f temp;
			temp.x = normaleWelle[i].x;
			temp.y = normaleWelle[i].y;
			temp.x += 622;
			temp.y += 355;
			fixPunktS.setPosition(temp);
			window.draw(fixPunktS);
		}		
		//window.draw();
		window.display();
	}
	//delete jointDef;
	return 0;
}
