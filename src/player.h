#include <SFML/Graphics.hpp>
#include <string>
#include "Bullet.h"
#include "addons.h"
using namespace sf;

class Player {
public:
    Texture tex;
    Sprite sprite;
    float speed = 0.5;
    int x, y;
    Bullet* bullet;
Addons* addons[100]; 
int addonCount; // Number of active addons
float timeSinceLastDrop; 

bool powerUp;
Clock powerUpClock;
    bool invulnerable;
	
bool fireAdd;
Clock fireAddClock;	
	
    Player(std::string png_path) {
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        x = 340; y = 700;
        sprite.setPosition(x, y);
        bullet = new Bullet();
    addonCount=0;
	        timeSinceLastDrop = 0.0f; 
    powerUp = false;
    invulnerable = false;
	fireAdd=false;
	}
	
void resetPosition()
{
  
    sprite.setPosition(340, 700);
}

	void dropAddons(float deltaTime) {
    timeSinceLastDrop += deltaTime;

    if (timeSinceLastDrop >= 10.0f) { // eevery 10 sec
        timeSinceLastDrop = 0.0f;

        int randomX = rand() % 750; // randm pos for addon

        int randomAddon = rand() % 4; // randm addon
        
switch (randomAddon) {
            case 0:
                addons[addonCount] = new PowerUp(randomX, 0);
                break;
            case 1:
                addons[addonCount] = new Fire(randomX, 0);
                break;
            case 2:
                addons[addonCount] = new Danger(randomX, 0);
                break;
            case 3:
                addons[addonCount] = new LivesAddon(randomX, 0);
                break;
            default:
                break;
        }

        addonCount++; //dropped
    }
}

    ~Player() {
        delete bullet;
    }

    void wrapAround() {
        float posX = sprite.getPosition().x;
        float posY = sprite.getPosition().y;
        if (posX < 0)
            posX += 780;
        else if (posX > 780)
            posX -= 780;
        if (posY < 0)
            posY += 780;
        else if (posY > 780)
            posY -= 780;

        sprite.setPosition(posX, posY);
    }

    void move(std::string s)
	{
        float delta_x = 0, delta_y = 0;
        if (s == "l")
            delta_x = -1;
        else if (s == "r")
            delta_x = 1;
        if (s == "u")
            delta_y = -1;
        else if (s == "d")
            delta_y = 1;


if(s=="dr")
{
	delta_x=1;
delta_y=1;
}     

if(s=="dl")
{
	delta_x=-1;
delta_y=1;
} 

if(s=="ur")
{
	delta_x=1;
delta_y=-1;
}        
	 delta_x *= speed;
        delta_y *= speed;

        sprite.move(delta_x, delta_y);
    }
};