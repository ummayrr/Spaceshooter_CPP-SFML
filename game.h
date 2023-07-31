#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <time.h>
#include <iostream>
#include "menu.h"
using namespace std;
#include "player.h"
#include "Bomb.h"
#include "beam.h"
#include "enemy.h"
#include "level.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "lives.h"
#include "HighScore.h"
#include "badge.h"

const char title[] = "Spaceshooter";
using namespace sf;

class Game {
public:
    Sprite background; //Game background sprite
    Texture bg_texture;
    Player* p; //player
    // add other game attributes
Texture explosionTexture;
Sprite explosionSprite;

    Level* levels[3];
    Level* currentLevel;
    int currentLevelIndex;
	
    Lives* lives;
    Texture heartTexture;
    Sprite hearts[3];
    float timeSinceLastHit;
string enteredName;
int phases[3] = {3, 3, 6};
Clock hitClock;

    bool shake; 
    Clock shakeClock; 
Sound firesound;
Sound monsterbeam;
	SoundBuffer buffer;

	SoundBuffer buffer2;
Sound destroyed;
SoundBuffer buffer3;

    Texture playerShipOriginal;
    Texture playerShipUpRight;
    Texture playerShipUpLeft;
    Texture playerShipDownLeft;
	Texture playerShipDownRight;
	Texture playerShipDown;
	Texture playerShipLeft;
	Texture playerShipRight;
	    Monster* monster;
    bool monsterDefeated;
	int monsterhits;
	bool musicStarted;

const int MENU = 0;
const int PLAYING = 1;
const int PAUSED = 2;
    float delay; // delay between key presses
    static const int GAME_OVER = 3; // game over state
const int HIGH_SCORES = 4;
const int INSTRUCTIONS=5;
    Dragon* dragon;
    sf::Clock dragonClock;
    float dragonInterval;
int dragonhits;
    Menu menu;
    int gameState;
    Menu pauseMenu; // pause menu
    sf::Font font;
    sf::Text gameOverText; // text to display when game is over
    HighScore highScore;
string playerName;
	Sprite background1;
	Sprite background2;
bool nameEntered;
bool highScoreAdded;
float dragonDelay=2.0f;
    int score;

    Text scoreText;
    sf::Clock monsterClock;
Music music;
    Badge goldBadge{"../img/gold.png"};
    Badge silverBadge{"../img/silver.png"};
    Badge bronzeBadge{"../img/bronze.png"};
Clock explosionClock;
bool explode;
	Game(): highScore("../assets/highscores.txt") 
		{
        p = new Player("../img/player_ship.png");
        bg_texture.loadFromFile("../img/b.jpg");
        //background.setTexture(bg_texture);
        //background.setScale(2, 1.5);
		background1.setTexture(bg_texture);
background2.setTexture(bg_texture);
background1.setPosition(0, 0); //set the first sprite at the top
background2.setPosition(0, -780); //set the second sprite above the first one
buffer.loadFromFile("../audio/shot.wav");
firesound.setBuffer(buffer);

buffer2.loadFromFile("../audio/beam.wav");
monsterbeam.setBuffer(buffer2);

buffer3.loadFromFile("../audio/destroyed.wav");
monsterbeam.setBuffer(buffer3);
explosionTexture.loadFromFile("../img/explosion.png");
explosionSprite.setTexture(explosionTexture);
        playerShipOriginal.loadFromFile("../img/player_ship.png");
        playerShipUpRight.loadFromFile("../img/1.png");
        playerShipUpLeft.loadFromFile("../img/2.png");
		playerShipDownRight.loadFromFile("../img/3.png");
        playerShipDownLeft.loadFromFile("../img/4.png");
        playerShipDown.loadFromFile("../img/5.png");
        playerShipRight.loadFromFile("../img/6.png");
		playerShipLeft.loadFromFile("../img/7.png");
		
        levels[0] = new Level1();
        levels[1] = new Level2();
        levels[2] = new Level3();
        currentLevelIndex = 0;
        currentLevel = levels[currentLevelIndex];
        lives = new Lives();

        heartTexture.loadFromFile("../img/heart.png");
        for (int i = 0; i < 3; i++) {
            hearts[i].setTexture(heartTexture);
            hearts[i].setPosition(700 - i * 50 + 20 , 10);
        }
    timeSinceLastHit=0;
shake=false;
        gameState = MENU;
delay=0.2;
		musicStarted=true;
         pauseMenu.options[1].setString("High Scores");		
		        font.loadFromFile("../assets/AstroSpace-eZ2Bg.ttf");
				

		        gameOverText.setFont(font);
        gameOverText.setString("Game Over");
        gameOverText.setCharacterSize(48);
		
		    score = 0;

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 10);

	        highScore.loadHighScores();
        nameEntered = false;
		highScoreAdded = false;

        monster = new Monster(50.0f, 50.0f);
        monsterDefeated = false;
		monsterhits=0;
		
		        dragon = new Dragon(250.0f, 50.0f, p);
        dragonInterval = generateRandomInterval();
 dragonhits=0;
 explode=false;
 }
 
     float generateRandomInterval() {
        return 1 + rand() % 100;
    }

 
bool checkIntersection(Sprite s1, Sprite s2)
{
    float s1PositionX = s1.getPosition().x;
    float s1PositionY = s1.getPosition().y;
    float s2PositionX = s2.getPosition().x;
    float s2PositionY = s2.getPosition().y;
    float s1SizeX = s1.getTexture()->getSize().x;
    float s1SizeY = s1.getTexture()->getSize().y;
    float s2SizeX = s2.getTexture()->getSize().x;
    float s2SizeY = s2.getTexture()->getSize().y;

    if (s1PositionX < s2PositionX + s2SizeX &&
        s1PositionX + s1SizeX > s2PositionX &&
        s1PositionY < s2PositionY + s2SizeY &&
        s1PositionY + s1SizeY > s2PositionY) {
        return true;
    }
    return false;
}


void checkCollisions() {
    for (int i = 0; i < currentLevel->enemyCount; i++) {
        if (!monster->isOnScreen && currentLevel->showEnemies==true && currentLevel->enemies[i]->isAlive) {
            for (int j = 0; j < p->bullet->fireCount; j++) {
                if (checkIntersection(p->bullet->fireSprites[j], currentLevel->enemies[i]->sprite)) {
                    currentLevel->removeEnemy(i);
                                        score += currentLevel->enemies[i]->score;
					if (!checkIntersection(p->bullet->fireSprites[j], p->sprite)) {
                        for (int k = j; k < p->bullet->fireCount - 1; k++) {
                            p->bullet->fireSprites[k] = p->bullet->fireSprites[k + 1];
                        }
                        p->bullet->fireCount--;
                        j--;
                    }
                }
            }
        }

        // Check for collision between the bomb and the player ship
        if (currentLevel->enemies[i]->bomb != nullptr && currentLevel->showEnemies) {
            if (checkIntersection(currentLevel->enemies[i]->bomb->sprite, p->sprite)) {
                // Handle collision between bomb and player ship
            if (timeSinceLastHit > 0.5) {
                    
                    explosionClock.restart();
                hitClock.restart();

                p->resetPosition();

				destroyed.play();
                lives->decreaseLives();
				p->resetPosition();
							shake=1;
		shakeClock.restart();
                std::cout << "Lives: " << lives->getLives() << std::endl;
                timeSinceLastHit = 0;
            }      
            }
        }
		
		
		        if (monster->isOnScreen && !monsterDefeated) {
            for (int j = 0; j < p->bullet->fireCount; j++) {
                if (checkIntersection(p->bullet->fireSprites[j], monster->sprite)) {
                    monsterhits++;
					score=score+5;
                    if (monsterhits >= 8) {
                        monsterDefeated = true;
                        monster->isOnScreen = false;
                       monsterhits=0;
					}
                    for (int k = j; k < p->bullet->fireCount - 1; k++) {
                        p->bullet->fireSprites[k] = p->bullet->fireSprites[k + 1];
                    }
                    p->bullet->fireCount--;
                    j--;
                }
                if (checkIntersection(p->sprite, monster->sprite)) {
            			            if (timeSinceLastHit > 0.5) {
				destroyed.play();
				lives->decreaseLives();
				p->resetPosition();
							shake=1;
		shakeClock.restart();
                std::cout << "Lives: " << lives->getLives() << std::endl;
                timeSinceLastHit = 0;
			
			}
        }
							  for (int i = 0; i < monster->fireCount; i++) {
					                if (checkIntersection(p->sprite, (monster->fireSprites[i]))) {
            			            if (timeSinceLastHit > 1) {
				destroyed.play();
				lives->decreaseLives();
				p->resetPosition();
							shake=1;
		shakeClock.restart();
                std::cout << "Lives: " << lives->getLives() << std::endl;
                timeSinceLastHit = 0;
									}
			}
        }
    }
				}
				}
				
				if(dragon->isOnScreen)
				{
							  for (int i = 0; i < dragon->fireCount; i++) {
					                if (checkIntersection(p->sprite, (dragon->fireSprites[i]))) {
            			            if (timeSinceLastHit > 1) {
				destroyed.play();
				lives->decreaseLives();
				p->resetPosition();
							shake=1;
		shakeClock.restart();
                std::cout << "Lives: " << lives->getLives() << std::endl;
                timeSinceLastHit = 0;
									}
			}
        }

         for (int j = 0; j < p->bullet->fireCount; j++) {
                if (checkIntersection(p->bullet->fireSprites[j], dragon->sprite)) {
                    dragonhits++;
					score=score+10;
                    if (monsterhits >= 5) {
                       dragon->isOnScreen=false;
                        monster->isOnScreen = false;
                       dragonhits=0;
					}
                    for (int k = j; k < p->bullet->fireCount - 1; k++) {
                        p->bullet->fireSprites[k] = p->bullet->fireSprites[k + 1];
                    }
                    p->bullet->fireCount--;
                    j--;
                }

}
				}
	
	    for (int i = 0; i < currentLevel->enemyCount; i++) {
			      if( currentLevel->showEnemies && currentLevel->enemies[i]->isAlive)
					{
        if (checkIntersection(p->sprite, currentLevel->enemies[i]->sprite)) {
			            if (timeSinceLastHit > 0.5) {
				destroyed.play();
				lives->decreaseLives();
				p->resetPosition();
							shake=1;
		shakeClock.restart();
                std::cout << "Lives: " << lives->getLives() << std::endl;
                timeSinceLastHit = 0;
            }  
        }
		}
	}
}

void checkAddonCollisions() {
    for (int i = 0; i < p->addonCount; i++) {
        if (checkIntersection(p->sprite, p->addons[i]->sprite)) {
            if (p->addons[i]->type == "PowerUp") {
                  p->powerUp = true;
				  p->invulnerable=true;
    p->powerUpClock.restart();
            } else if (p->addons[i]->type == "Fire") {
                p->fireAdd=true;
				p->fireAddClock.restart();
            }
			else if (p->addons[i]->type == "Danger")
			{
			            if (timeSinceLastHit > 0.5) {
				lives->decreaseLives();
				p->resetPosition();
							shake=1;
		shakeClock.restart();
                std::cout << "Lives: " << lives->getLives() << std::endl;
                timeSinceLastHit = 0;
            }
		}			
			else if (p->addons[i]->type == "LivesAddon")
			{
				if(lives->getLives()<3)
                lives->increaseLives();
            }

            // Remove the addon from the array
            for (int j = i; j < p->addonCount - 1; j++) {
                p->addons[j] = p->addons[j + 1];
            }
            p->addonCount--;
            i--;
        }
    }
}




            // if (timeSinceLastHit > 0.5) {
                // lives->decreaseLives();
                // std::cout << "Lives: " << lives->getLives() << std::endl;
                // timeSinceLastHit = 0;
            // }      

 

    void nextLevel() {
        currentLevelIndex++;
        if (currentLevelIndex < 3) {
            currentLevel = levels[currentLevelIndex];
        }
		else
		{
gameState=GAME_OVER;
        }
    }
	
string getUserName(sf::RenderWindow &window)
{
	    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../img/menu.jpg");

    // create background sprite
    sf::Sprite background(backgroundTexture);
    // draw background
    std::string name;
    sf::Font font;
    font.loadFromFile("../assets/AstroSpace-eZ2Bg.ttf");
    sf::Text text("", font);
    text.setCharacterSize(56);
    text.setFillColor(sf::Color::White);
    text.setPosition(100, 250);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b' && name.size() > 0)
                    name.erase(name.size() - 1, 1);
                else if (event.text.unicode < 128 && event.text.unicode != '\b')
                    name += static_cast<char>(event.text.unicode);
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    return name;
                }
            }
        }
        text.setString("Get onboard today\n \t Enter your\n \t\tName: " + name);
        window.clear();
		    window.draw(background);

        window.draw(text);
        window.display();
    }
    return name;
}


void Instructions(sf::RenderWindow &window)
{
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../img/menu.jpg");

    // create background sprite
    sf::Sprite background(backgroundTexture);
    // draw background
    sf::Font font;
    font.loadFromFile("../assets/AstroSpace-eZ2Bg.ttf");
    sf::Text text("", font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(20, 10);

    std::string instructions = "The player of the game controls a spaceship in an enemy \nfilled space field. The goal is to destroy the enemy ships\n, which include (i) invaders, (ii) monsters \nand (iii) dragon.\nYou can move player ship in all directions. \nFires are shot automatically. The spaceship is destroyed\n in case of\n a collision with an object (enemy ships)\n or impact with a bomb fired by\n the enemy ship. Similarly, the dragon appears after a random\n interval whereby its position is fixed\t, however, it could\n fire in 3 directions (downwards, right-downwards\n and left-downwards). The direction of the fire\n would also be decided on the basis\n of the position of the spaceship i.e.\n the dragon would fire in the zone\n where the spaceship is currently located.\n On the other hand, the monster’s vertical position\n is fixed however it can move in left and right directions. The\n monster will throw a beam of lightning\n on the spaceship after regular\n intervals.\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tHave fun.";

    text.setString(instructions);
    window.clear();
    window.draw(background);

    window.draw(text);
    window.display();
}




    void start_game() {
        srand(time(0));
        RenderWindow window(VideoMode(780, 780), title);
        Clock clock;
		Clock clock2;
        float timer = 0;
        while (window.isOpen()) {
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;
            //cout<<time<<endl;
            Event e;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                    window.close(); //close the game
            }
			         if (gameState == MENU) {
                // handle menu input
                if (clock2.getElapsedTime().asSeconds() > delay) {
                    if (Keyboard::isKeyPressed(Keyboard::Up)) {
                        menu.moveUp();
                        clock2.restart();
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Down)) {
                        menu.moveDown();
                        clock2.restart();
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Return)) {
                    int selected = menu.select();
                    if (selected == 0) { // "Start Game" option
                        gameState = PLAYING;
                    }
					if (selected==1) //resume game 
						gameState=PLAYING;
					
if (selected == 2) { // "Show High Score" option
    gameState = HIGH_SCORES;
}
if(selected==3)
	gameState=INSTRUCTIONS;
if(selected==4)
{
	musicStarted=false;
	music.openFromFile("../audio/music.ogg");
	menu.toggleMusic();
    if (!musicStarted) {
        music.play();
        musicStarted = true;
    }
}
									if(selected==5)
					                    window.close(); //close the game
                }
				

            } 
			
			
				           if (gameState == PLAYING && nameEntered==false)
            {
                 playerName=getUserName(window);				
                nameEntered = true;
           }
		
					else if (gameState == PLAYING && nameEntered==true)
					{
            if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
			{
                p->move("l"); // Player will move to left
                p->sprite.setTexture(playerShipOriginal);
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
			{
                p->move("r"); //player will move to right
                p->sprite.setTexture(playerShipOriginal);
			} 
			 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//If up key is pressed
			 {
				p->move("u"); //playet will move upwards
                p->sprite.setTexture(playerShipOriginal);
			 }
			if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
			{
                p->move("d"); //player will move downwards
                p->sprite.setTexture(playerShipOriginal);
			}


   	if ( (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ) 
			
                p->sprite.setTexture(playerShipUpRight);
               
	
			if ( (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) )
		
                p->sprite.setTexture(playerShipUpLeft);
                
	

			else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D))
			{
                 p->sprite.setTexture(playerShipDownRight);		
                 p->move("dr");
			}
 
else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A))
{
                 p->sprite.setTexture(playerShipDownLeft);
                 p->move("dl");
}

else if (Keyboard::isKeyPressed(Keyboard::S))
{
                 p->sprite.setTexture(playerShipDown);				 
	             p->move("d");
}			


else if (Keyboard::isKeyPressed(Keyboard::D))
{
	p->sprite.setTexture(playerShipRight);
	p->move("r");
}

else if ( (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ) 
	{	
                p->sprite.setTexture(playerShipUpRight);
                p->move("ur");		
	}	

else if (Keyboard::isKeyPressed(Keyboard::A))
{
	p->sprite.setTexture(playerShipLeft);
	p->move("l");
}
	 
	 else if (Keyboard::isKeyPressed(Keyboard::Escape))
	 {
		 gameState=PAUSED;
	 }
	 
	                if (lives->getLives()==0) {
                    gameState = GAME_OVER;
                }
				
if (!Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Down) && !Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S) && !Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D) )
                         p->sprite.setTexture(playerShipOriginal);
                          

            ////////////////////////////////////////////////
            ///// Call your functions here               ///
            //////////////////////////////////////////////
        
bool allEnemiesDefeated = true;
for (int i = 0; i < currentLevel->enemyCount; i++) {
    if (currentLevel->enemies[i]->isAlive) {
        allEnemiesDefeated = false;
        break;
    }
}
if (allEnemiesDefeated) {
if (currentLevel->phase < phases[currentLevelIndex]) {
    currentLevel->nextPhase();
}
else
{
    nextLevel();
}
}
             float deltaTime = clock.restart().asSeconds();
			         timeSinceLastHit += deltaTime;

            for (int i = 0; i < currentLevel->enemyCount; i++) {
                currentLevel->enemies[i]->move(0.05);

                // Move the bomb
                if (currentLevel->enemies[i]->bomb != nullptr) {
                    currentLevel->enemies[i]->bomb->move(deltaTime);

                // Check if the bomb has gone off the screen
                if (currentLevel->enemies[i]->bomb->position.y > 780) {
                    delete currentLevel->enemies[i]->bomb;
                    currentLevel->enemies[i]->bomb = nullptr;
                }
            }
        }

        


		p->wrapAround();
p->dropAddons(deltaTime);

checkCollisions();
checkAddonCollisions();

        // Move the addons
        for (int i = 0; i < p->addonCount; i++) {
            p->addons[i]->move(deltaTime);

            if (p->addons[i]->positionY > 780) {
                // Remove the addon from the array
                for (int j = i; j < p->addonCount - 1; j++) {
                    p->addons[j] = p->addons[j + 1];
                }
                p->addonCount--;
                i--;
            }
        }
		
            // check if it's time for drgon
            if (dragonClock.getElapsedTime().asSeconds() >= dragonInterval && !((monster->isOnScreen))) {
                dragon->isOnScreen = true;
                dragonClock.restart();
                dragonInterval = generateRandomInterval();
            }

            // if more than dragon 10 seconds
            if (dragon->isOnScreen && dragonClock.getElapsedTime().asSeconds() >= 10.0f) {
                dragon->isOnScreen = false;
            }

            // dragon fire
            if (dragon->isOnScreen) {
            if (dragonClock.getElapsedTime().asSeconds() >= dragonDelay)
		            dragon->dropBomb();
				    dragon->firemove(); 

            }
			
if (dragon->isOnScreen && dragonClock.getElapsedTime().asSeconds() >= 5.0f) {
    delete dragon;
    dragon = new Dragon(250.0f, 50.0f, p); //new dragn
    dragon->isOnScreen = false;
}


		     
		//shake
        if (shake) {
            if (shakeClock.getElapsedTime().asSeconds() >= 0.2f) {
                shake = false; 

                // original view
                window.setView(window.getDefaultView());
            } 
			else 
{
                // randm view
int randomX = rand() % 20 - 10;
int randomY = rand() % 20 - 10;
sf::View view;
view.setCenter(400 + randomX, 400 + randomY);
view.setSize(800, 800);
window.setView(view);

            }
        }

string fireDirection; 
if (Keyboard::isKeyPressed(Keyboard::Left))
    fireDirection = "u";
else if (Keyboard::isKeyPressed(Keyboard::Right))
    fireDirection = "u";
else if (Keyboard::isKeyPressed(Keyboard::D))
    fireDirection = "r";
else if (Keyboard::isKeyPressed(Keyboard::A))
    fireDirection = "l";
else if (Keyboard::isKeyPressed(Keyboard::S))
    fireDirection = "d";
else if (!Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Down) && !Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S) && !Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D))
    fireDirection = "u";
else if (Keyboard::isKeyPressed(Keyboard::Up))
    fireDirection = "u";
else if (Keyboard::isKeyPressed(Keyboard::Down))
    fireDirection = "u";

if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Up))
    fireDirection = "ul";
else if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Up))
    fireDirection = "ur";
else if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::S))
    fireDirection = "dl";
else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::S))
    fireDirection = "dr";

		if(timeSinceLastHit<0.1)
		{
		p->sprite.setTexture(explosionTexture);
destroyed.play();
		}

		if(timeSinceLastHit==0.1)
		{
		p->sprite.setTexture(playerShipOriginal);
                            p->resetPosition();

		}
  if (p->powerUp)
  {
    if (p->powerUpClock.getElapsedTime().asSeconds() >= 5) {
        p->powerUp = false;
		p->invulnerable=false;
    }
  }
  
    if (p->fireAdd)
  {
    if (p->fireAddClock.getElapsedTime().asSeconds() >= 5) {
        p->fireAdd = false;
    }
  }
  
  if (p->powerUp) {
p->bullet->firePowerUp(time,p->sprite,0.6);
    p->bullet->firemovePowerUp(0.5);
  }
else if(p->fireAdd)
{
p->bullet->fireAddEffect(time, p->sprite, fireDirection);
p->bullet->firemove();
}
 else
 {
p->bullet->fire(time, p->sprite, fireDirection);
    p->bullet->firemove();
}
        scoreText.setString("Score: " + to_string(score));

            if (currentLevelIndex == 0 || currentLevelIndex == 1) {
                if (currentLevel->phase == 3 && !monsterDefeated) {
                    monster->isOnScreen = true;
                    currentLevel->showEnemies = false;
                }
				if (currentLevelIndex == 2)
				{
					if (currentLevel->phase == 6 && !monsterDefeated) {
                    monster->isOnScreen = true;
                    currentLevel->showEnemies = false;
                }
            }
			}

            if (monsterDefeated && currentLevelIndex < 3) {
                currentLevel->nextPhase();
                monsterDefeated = false;
                currentLevel->showEnemies = true;
            }
			
            if (monster->isOnScreen)
			{
                monster->move(0.015);
               currentLevel->showEnemies = false;
            }



            for (int i = 0; i < currentLevel->enemyCount; i++) {
                if (!monster->isOnScreen) {
		                    currentLevel->enemies[i]->move(deltaTime);
                }
            }


			}

		
else if (gameState == PAUSED) {
                
				pauseMenu.options[0].setString("Resume");
				pauseMenu.options[2].setString("Quit");
				// handle pause menu input
                if (clock2.getElapsedTime().asSeconds() > delay) {
                    if (Keyboard::isKeyPressed(Keyboard::Up)) {
                        pauseMenu.moveUp();
                        clock2.restart();
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Down)) {
                        pauseMenu.moveDown();
                        clock2.restart();
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Return)) {
                    int selected = pauseMenu.select();
                    if (selected == 0) { // "Resume" 
                        gameState = PLAYING;
                    } else if (selected == 1) { // "Restart" 
                        // restart game
                    } else if (selected == 2) { // "Exit" 
                        window.close();
                    }
                }
            }



            window.clear(Color::Black);
			
            if (gameState == MENU) {
                menu.draw(window);
            } else if (gameState == PLAYING) {
				
				            window.clear(Color::Black);

 //window.draw(background); // setting background
	float bgSpeed = 200;
	background1.move(0, bgSpeed * time); //move the first sprite down
	background2.move(0, bgSpeed * time); //move the second sprite down
	
//reset
	if (background1.getPosition().y > 780)
	{
		background1.setPosition(0, -780);
	}
	if (background2.getPosition().y > 780)
	{
		background2.setPosition(0, -780);
	}
	window.draw(background1);  
	window.draw(background2);  

 
            window.draw(p->sprite); 

        for (int i = 0; i < p->bullet->fireCount; i++) {
            window.draw(p->bullet->fireSprites[i]); 
			firesound.play();
        }
		
		            if (monster->isOnScreen) {
                window.draw(monster->sprite);
            for (int i = 0; i < monster->fireCount; i++) {
                window.draw(monster->fireSprites[i]); 
		  }
            monster->firemove(); 

                }
            
			
			else {
                for (int i = 0; i < currentLevel->enemyCount; i++) {
                    if (currentLevel->enemies[i]->isAlive && currentLevel->showEnemies==1)
                        window.draw(currentLevel->enemies[i]->sprite);
            if (currentLevel->enemies[i]->bomb != nullptr && currentLevel->showEnemies==1) {
                window.draw(currentLevel->enemies[i]->bomb->sprite);
            }
                }
            }
		
        // for (int i = 0; i < currentLevel->enemyCount; i++) {
			    // if (currentLevel->enemies[i]->isAlive) 
            // window.draw(currentLevel->enemies[i]->sprite);


        // }

        for (int i = 0; i < lives->getLives(); i++) {
            hearts[i].setScale(0.75,0.75);
			window.draw(hearts[i]);
        }

        for (int i = 0; i < p->addonCount; i++) {
            window.draw(p->addons[i]->sprite); 
        }

        window.draw(scoreText);
        if (!playerName.empty())
        {
        for (int i = 0; i < 3; i++)
        {
            if (playerName == highScore.highScores[i].name)
            {
                sf::Sprite* badgeSprite;
                switch (i)
                {
                case 0:
                    badgeSprite = &goldBadge.sprite;
                    break;
                case 1:
                    badgeSprite = &silverBadge.sprite;
                    break;
                case 2:
                    badgeSprite = &bronzeBadge.sprite;
                    break;
                }
                badgeSprite->setPosition(15, 40);
                window.draw(*badgeSprite);
                break;
            }
        }

		}
		
		if (dragon->isOnScreen) {
    window.draw(dragon->sprite);

    // Make other enemies disappear
    for (int i = 0; i < currentLevel->enemyCount; i++) {
        currentLevel->showEnemies = false;
    }
    for (int i = 0; i < dragon->fireCount; i++) {
        window.draw(dragon->fireSprites[i]); 
    }

} 
else {
    // Make other enemies reappear
    for (int i = 0; i < currentLevel->enemyCount; i++) {
        currentLevel->showEnemies = true;
    }
}


            
			}
			
			
			else if (gameState == PAUSED) {
                pauseMenu.draw(window);
            }
           
		   else if (gameState == HIGH_SCORES) {
    highScore.displayHighScores(window);

    // handle user input to return to menu
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        gameState = MENU;
    }
}

else if (gameState==INSTRUCTIONS)
{
	Instructions(window);
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        gameState = MENU;
    }
}
else if (gameState == GAME_OVER)
{
         if (!playerName.empty() && !highScoreAdded && highScore.isHighScore(score)) {
        highScore.addHighScore(playerName, score);
        highScoreAdded = true;
    }
	
	   
            window.clear(Color::Black);
			 window.draw(background); // setting background
 gameOverText.setPosition(100.0f,350.0f);
 gameOverText.setCharacterSize(100);
 gameOverText.setFillColor(sf::Color::Red);
     scoreText.setCharacterSize(48);
  scoreText.setPosition(300.0f,10.0f); 
scoreText.setFillColor(sf::Color::Green);  
		 window.draw(scoreText);
                window.draw(gameOverText);
            }
			
            window.display(); //Displying all the sprites
 
	 }
    }
};