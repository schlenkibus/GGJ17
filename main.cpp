#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include <cstdlib>
#include <random>
<<<<<<< HEAD
#include "waveSprites.hpp"
#include "Score.hpp"

enum CATEGORY_BITS
{
    BODY1_CATEGORY_BITS = 0x00000001,
    BODY2_CATEGORY_BITS = 0x00000002,
    BODY3_CATEGORY_BITS = 0x00000004,
};

//GLOBAL STUFF
b2Vec2 normaleWelle[5];
=======
>>>>>>> 870d670cdceda4ae1305d297952016fe83bcefac

//Please dont judge me

b2Vec2 Gravity(0.f, 98.1f);
b2World World(Gravity);
<<<<<<< HEAD
=======

>>>>>>> 870d670cdceda4ae1305d297952016fe83bcefac
float boardPos = 0;
bool down = true;

#define SCALE 1
#define acc 1.5
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
	FixtureDef.friction = 1.3f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
	std::cout << "Wippe created" << std::endl;
	return Body;
}

b2Body* CreateStatic(b2World& World, int x, int y)
{
<<<<<<< HEAD
	b2PolygonShape Shape;
  	Shape.Set(normaleWelle, 5);

=======
>>>>>>> 870d670cdceda4ae1305d297952016fe83bcefac
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(x, y);
	BodyDef.type = b2_staticBody;
	b2Body* Body = World.CreateBody(&BodyDef);
<<<<<<< HEAD
	//Shape.SetAsArray(normaleWelle, 5);//((1)/SCALE, (1)/SCALE);
=======
	b2PolygonShape Shape;
	Shape.SetAsBox((1)/SCALE, (1)/SCALE);
>>>>>>> 870d670cdceda4ae1305d297952016fe83bcefac
	b2FixtureDef FixtureDef;
	FixtureDef.density = 2.f; 
	FixtureDef.friction = 1.f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
	std::cout << "Fixed point created" << std::endl;
	return Body;
}

<<<<<<< HEAD
void addForceBoard(float x, float y, b2Body* board, b2Body* player1, b2Body* player2)
{
	board->ApplyForce(b2Vec2(x*75, y*75), board->GetWorldCenter(), true);
=======
void moveOrigin(b2Joint* j, float x, float y, b2Body* fix, b2Body* board, b2RevoluteJointDef* jointDef)
{
	//b2Vec2 boardPos(board->GetTransform().p.x, board->GetTransform().p.y);
	//b2Vec2 temp(fix->GetTransform().p.x + x, fix->GetTransform().p.y);
	//fix->SetTransform(temp ,fix->GetAngle());
	jointDef->bodyA = board;
	jointDef->bodyB = fix;
	std::cout << "Body A " << jointDef->bodyA << std::endl;
	std::cout << "Body B "<< jointDef->bodyB  << std::endl;
	jointDef->localAnchorA.Set(x,0);
  	jointDef->localAnchorB.Set(0,0);
	jointDef->collideConnected = false;
	World.DestroyJoint(j);
	j = World.CreateJoint( jointDef );
>>>>>>> 870d670cdceda4ae1305d297952016fe83bcefac
}

int main()
{
<<<<<<< HEAD
	normaleWelle[0].Set(-50,  70);
	normaleWelle[1].Set(-20,  15);
	normaleWelle[2].Set( 20, 0);
	normaleWelle[3].Set( 50,  -2);
	normaleWelle[4].Set(90,  50);
	sf::Sprite SpriteWippe, SpritePlayer1, SpritePlayer2;
	sf::RenderWindow window(sf::VideoMode(1244, 700), "BOX2D",  sf::Style::Close);
	WaveSprites sprites(&window);
	Score score(&window);
	sf::Event event;
	sf::Texture GroundTexture, BoxTexture;
	
	b2Body* board = CreateBox(World, 622, 350);
	b2Body* fix = CreateStatic(World, 622, board->GetPosition().y + 5);
	
	//Player 1 /75x131
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(530/SCALE, 200/SCALE);
=======
	sf::Sprite SpriteWippe, SpritePlayer1, SpritePlayer2;
	sf::RenderWindow window(sf::VideoMode(1244, 700), "BOX2D",  sf::Style::Close);
	sf::Event event;
	b2Joint* joint;
	b2RevoluteJointDef* jointDef = new b2RevoluteJointDef();
	sf::Texture GroundTexture, BoxTexture;
	
	b2Body* board = CreateBox(World, 622, 350);
	b2Body* fix = CreateStatic(World, 622, board->GetPosition().y);
	jointDef->bodyA = board;
	jointDef->bodyB = fix;
	jointDef->collideConnected = false;
	jointDef->localAnchorA.Set(0, 0);
	jointDef->localAnchorB.Set(0, 0);
	joint = World.CreateJoint(jointDef);
	
	//Player 1 /75x131
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(530/SCALE, 00/SCALE);
>>>>>>> 870d670cdceda4ae1305d297952016fe83bcefac
	BodyDef.type = b2_dynamicBody;
	BodyDef.position.Set(530.f, 2.0f);
	//BodyDef.gravityScale = 3.0f;
	b2Body* Player1 = World.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((37.5f)/SCALE, (133)/SCALE);
	b2FixtureDef FixtureDef;
<<<<<<< HEAD
	FixtureDef.density = 0.2f;
	FixtureDef.friction = 0.5f;
	FixtureDef.filter.categoryBits = BODY1_CATEGORY_BITS;
	FixtureDef.filter.maskBits = BODY1_CATEGORY_BITS | BODY2_CATEGORY_BITS;
=======
	FixtureDef.density = 0.1f;
	FixtureDef.friction = 0.5f;
>>>>>>> 870d670cdceda4ae1305d297952016fe83bcefac
	FixtureDef.shape = &Shape;
	Player1->CreateFixture(&FixtureDef);
	//Player 2
	b2BodyDef BodyDef2;
<<<<<<< HEAD
	BodyDef2.position = b2Vec2(630/SCALE, 200/SCALE);
=======
	BodyDef2.position = b2Vec2(630/SCALE, 00/SCALE);
>>>>>>> 870d670cdceda4ae1305d297952016fe83bcefac
	BodyDef2.type = b2_dynamicBody;
	//BodyDef2.gravityScale = 3.0f;
	b2Body* Player2 = World.CreateBody(&BodyDef2);

	b2PolygonShape Shape2;
	Shape2.SetAsBox((37.5f)/SCALE, (133)/SCALE);
	b2FixtureDef FixtureDef2;
<<<<<<< HEAD
	FixtureDef2.density = 0.2f;
	FixtureDef2.friction = 0.5f;
	FixtureDef2.shape = &Shape2;
	FixtureDef2.filter.categoryBits = BODY3_CATEGORY_BITS;
   	FixtureDef2.filter.maskBits = BODY3_CATEGORY_BITS | BODY1_CATEGORY_BITS;
=======
	FixtureDef2.density = 0.1f;
	FixtureDef2.friction = 0.5f;
	FixtureDef2.shape = &Shape2;
>>>>>>> 870d670cdceda4ae1305d297952016fe83bcefac
	Player2->CreateFixture(&FixtureDef2);
	
	//Massdata
	b2MassData PlayerMass;
	PlayerMass.mass = 90;
	PlayerMass.center = b2Vec2(0, 131);

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
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			Player1->ApplyForce( b2Vec2(-impulse,0), Player1->GetWorldCenter() , true);
		}
<<<<<<< HEAD
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			Player1->ApplyForce( b2Vec2(0,Player1->GetMass() * 600), Player1->GetWorldCenter() , true);
=======
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			Player1->ApplyForce( b2Vec2(0,-20), Player1->GetWorldCenter() , true);
>>>>>>> 870d670cdceda4ae1305d297952016fe83bcefac
		}
		//Player 2
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			Player2->ApplyForce( b2Vec2(impulse,0), Player2->GetWorldCenter() , true);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			Player2->ApplyForce( b2Vec2(-impulse,0), Player2->GetWorldCenter() , true);
		}
<<<<<<< HEAD
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			Player2->ApplyForce( b2Vec2(0,Player2->GetMass() * 600), Player2->GetWorldCenter() , true);
		}
		//Point system
		if(Player1->GetTransform().p.y >= 600 || Player2->GetTransform().p.y >= 600)
		{
			//Game Over
=======
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			Player2->ApplyForce( b2Vec2(0,-20), Player2->GetWorldCenter() , true);
>>>>>>> 870d670cdceda4ae1305d297952016fe83bcefac
		}
		//TEMP 
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
<<<<<<< HEAD
			std::cout << "jump with force: " << board->GetMass() * 600  * 1000<< std::endl;
			addForceBoard(0, board->GetMass() * -600, board, Player1, Player2);
		}
=======
			if(boardPos < 70 && down)
			{
				moveOrigin(joint, boardPos++, 0, fix, board, jointDef);
			}
			else if(boardPos >= 70 && down)
			{
				moveOrigin(joint, boardPos++, 0, fix, board, jointDef);
				down = false;
			}
			else if(boardPos <= -10 && !down)
			{
				down = true;
			}
			else
			{
				moveOrigin(joint, boardPos--, 0, fix, board, jointDef);
			}
		}

>>>>>>> 870d670cdceda4ae1305d297952016fe83bcefac
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
<<<<<<< HEAD
		sprites.update();
		score.update();
		//fixPunktS.setPosition(Player1->GetWorldCenter().x, Player1->GetWorldCenter().y);
		//window.draw(fixPunktS);		
		sprites.draw();
		score.draw();

		for(int i = 0; i < 5; i++)
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
=======
		//Debug
		//fixPunktS.setPosition(joint->GetBodyB()->GetWorldCenter().x, joint->GetBodyB()->GetWorldCenter().y);
		//fixPunktS.setPosition(Player1->GetWorldCenter().x, Player1->GetWorldCenter().y);
		//window.draw(fixPunktS);		
		window.draw(bigWave);
		window.display();
	}
	delete jointDef;
>>>>>>> 870d670cdceda4ae1305d297952016fe83bcefac
	return 0;
}