#include <cmath>
using namespace std;

class Level1 : public Level {
public:
    Level1() {
        createLevel1();
    }

void createLevel1() {
    int spacing = 90; // gap
    //Left side vertical enemies
    for (int i = 0; i < 4; i++) {
        addEnemy(new AlphaInvader(50, 50 + i * spacing));
    }

    //toop horizonntal enemies
    for (int i = 0; i < 5; i++) {
        addEnemy(new AlphaInvader(50 + (i + 1) * spacing, 50));
    }

    //bottom hhorizontal enemies
    for (int i = 0; i < 5; i++) {
        addEnemy(new AlphaInvader(50 + (i + 1) * spacing, 50 + 3 * spacing));
    }

    //rihhgt side vertical enemies
    for (int i = 0; i < 4; i++) {
        addEnemy(new AlphaInvader(50 + 6 * spacing, 50 + i * spacing));
    }
            
 
}










    void nextPhase() override {
        phase++;
        if (phase == 2) {
			//triangle shape
    float spacing = 55.0f; // New spacing variable

    //Top sprite
    addEnemy(new AlphaInvader(350, 50));

    //Left side sprites
    for (int i = 1; i <= 5; i++) {
        addEnemy(new AlphaInvader(350 - i * spacing, 50 + i * spacing));
    }

    //Right side sprites
    for (int i = 1; i <= 5; i++) {
        addEnemy(new AlphaInvader(350 + i * spacing, 50 + i * spacing));
    }

    //bBottom sprites
        for (int i = -2; i <= 3; i++) {
        addEnemy(new AlphaInvader(310 + i * 80, 50 + 5 * 60));
    }
        }

		else if (phase == 3)
		{
    //cross sign shape
        for (int i = 0; i < 6; i++) {
        addEnemy(new AlphaInvader(115 + i * 80, 50 + i * 40));
        addEnemy(new AlphaInvader(115 + i * 80, 290 - i * 40));
    }
    addEnemy(new AlphaInvader(580, 300));
    addEnemy(new AlphaInvader(580,45));
        }
    }
	
	
};
