#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
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
#include "Qualle.hpp"
#include "FrontWave2.hpp"
#include "FrontWave3.hpp"
#include "UI.hpp"
#include "Menu.hpp"
#include "PlayerSprite.hpp"
#include "Shark.hpp"
#include "EndScreen.hpp"
#include "Background.hpp"

enum gameState
{
	menu, intro, credits, game, close
};

gameState state;

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

bool player1dead = false;
bool player2dead = false;

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
	board->ApplyForce(b2Vec2(x*100, y*100), board->GetWorldCenter(), true);
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
	bool gameInit = true;
	bool menuInit = true;
	bool introInit = true;
	bool creditsInit = true;
	sf::RenderWindow window(sf::VideoMode(1244, 700), "BOX2D",  sf::Style::Close);
	sf::Event menuEvent;
	state = gameState::menu;
	Menu menu(&window);
	Front3 test(&window);
	Front test2(&window);
	
	//TODO Menu und Intro einfügen
	std::cout << "Start Game" << std::endl;
	sf::Music backgroundMusic;
	backgroundMusic.openFromFile("HULA.wav");
	backgroundMusic.setLoop(true);
	std::srand(std::time(0)); // use current time as seed for random generator
	//Welllelele
	normaleWelle[0].Set(-65,  75);
	normaleWelle[1].Set(-50, 40);
	normaleWelle[2].Set(-20,  15);
	normaleWelle[3].Set( 20, 0);
	normaleWelle[4].Set( 70,  0);
	normaleWelle[5].Set(100, 10);
	sf::Sprite SpriteWippe, SpritePlayer1, SpritePlayer2;
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
	BoxTexture.loadFromFile("Character.png");
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
	//Stuff
	Qualle qualle(&window);
	Front2 front2(&window);
	Front3 front3(&window);
	UI ui(&window);
	ui.setReady(false);
	sf::Clock jumpTimer;
	sf::Time lastJump;
	sf::Time currJump;
	int bonusDelay = 0;	
	bool player1inactive = false;
	bool player2inactive = false;
	bool activenow1 = true;
	bool activenow2 = true;
	bool canJump = false;

	//NEW PLAYER
	PlayerSprite animatedplayer1(&window, 1);
	animatedplayer1.setMove(false);

	//newer stuff
	Shark shark(&window);
	EndScreen endscreen(&window, "Game Over!\n Thanks for playing!");
	BackgroundSprites bgStuff(&window);
	
	while(window.isOpen() && state != gameState::close)
	{
		if(gameInit && state == gameState::game)
		{
			player1lastTime = player1MinMoveClock.getElapsedTime();	
			player2lastTime = player2MinMoveClock.getElapsedTime(); 
			lastJump = jumpTimer.getElapsedTime();
			backgroundMusic.play();
			gameInit = false;
		}
		if(introInit && state == gameState::intro)
		{
			introInit = false;
		}
		if(creditsInit && state == gameState::credits)
		{
			creditsInit = false;
		}
		if(menuInit && state == gameState::menu)
		{
			menuInit = false;
		}
		//MENU '#####################################
		while(state == gameState::menu && window.isOpen())
		{
			while(window.pollEvent(menuEvent))
			{
				if(menuEvent.type == sf::Event::Closed)
				{
					window.close();
					state = gameState::close;
				}
			}
			window.clear();
			menu.update();
			switch(menu.getState())
			{
				case 0:
					state = gameState::game;
				break;
				case 1:
					state = gameState::close;
				break;
				case 2:
					state = gameState::credits;
				break;
			}
			test.update();
			test2.update();
			menu.draw();
			test.draw();
			test2.draw();
			window.display();
		}
		//GAME ##################################
		while(state == gameState::game)
		{
			while(window.pollEvent(event))
			{
				if(event.type == sf::Event::Closed)
				{
					window.close();
					state = gameState::close;
				}
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
				if(Player1->GetTransform().p.y >= 600 && !player1dead)
				{
					shark.setPlayerPos(sf::Vector2f(Player1->GetTransform().p.x, Player1->GetTransform().p.y));
					player1dead = true;
				}				
				else if (Player2->GetTransform().p.y >= 600 && !player2dead)
				{
					shark.setPlayerPos(sf::Vector2f(Player2->GetTransform().p.x, Player2->GetTransform().p.y));
					player2dead = true;				
				}
				score.setEnd();
				endscreen.activate();
			}
			//TEMP 
			if(jumpTimer.getElapsedTime().asSeconds() - lastJump.asSeconds() > 10)
			{
				ui.setReady(true);
				canJump = true;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
			{
				ui.setReady(false);
				addForceBoard(0, board->GetMass() * -1900, board, Player1, Player2);
				canJump = false;
				lastJump = jumpTimer.getElapsedTime();
			}

			addRandomForce(board);

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
			if(animatedplayer1.getSprite()->getPosition().x- player1last.x < -minMove.x ||  
			animatedplayer1.getSprite()->getPosition().x- player1last.x > minMove.x && activenow1)
			{
				if(player1MinMoveClock.getElapsedTime().asSeconds() - player1lastTime.asSeconds() >= 2)
				{
					activenow1 = false;
					score.setBonus(-2);
					player1last = animatedplayer1.getSprite()->getPosition();
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
			bgStuff.update();
			bgStuff.draw();		
			front2.update();		
			front2.draw();
			//Handle Wippe	
			SpriteWippe.setPosition(board->GetPosition().x, board->GetPosition().y);
			SpriteWippe.setRotation(180/b2_pi * board->GetAngle());
			window.draw(SpriteWippe);
			//Player1
			animatedplayer1.setMove(activenow1);
			animatedplayer1.update();
			animatedplayer1.getSprite()->setRotation(180/b2_pi * Player1->GetAngle());
			animatedplayer1.getSprite()->setPosition(Player1->GetPosition().x , SCALE * Player1->GetPosition().y);
			window.draw(*animatedplayer1.getSprite());
			//Player2
			
			SpritePlayer2.setRotation(180/b2_pi * Player2->GetAngle());
			SpritePlayer2.setPosition(SCALE * Player2->GetPosition().x, SCALE * Player2->GetPosition().y);
			window.draw(SpritePlayer2);
			//Alles Grafische
			sprites.update();
			wasserSpritzer.update();
			score.update();
			front.update();	
			sprites.draw();
			wasserSpritzer.draw();
			qualle.update();
			shark.update();
			shark.draw();
			qualle.draw();
			score.draw();
			front3.update();
			front3.draw();
			front.draw();
			//ui.draw();
			if(endscreen.update() == 0)
				state = gameState::close;
			endscreen.draw();
			window.display();
		}
	}
	//delete jointDef;
	return 0;
}
