

class Level3 : public Level {
public:
    Level3() {
        createLevel3();
    }

void createLevel3() {
    int spacing = 90; // gap between enemyy
    int rows = 2;
    int columns = 6;

//filled
    for (int i = 0; i <= rows; i++) {
        for (int j = 0; j <= columns; j++) {
            addEnemy(new GammaInvader(50 + j * spacing, 50 + i * spacing));
        }
    }
 
}

    void nextPhase() override
	{
        phase++;
        if (phase == 2) {
    //triangle shape
    float spacing = 55.0f; // New spacing variable

    //Top sprite
    addEnemy(new GammaInvader(350, 50));

    //Left side sprites
    for (int i = 1; i <= 5; i++) {
        addEnemy(new GammaInvader(350 - i * spacing, 50 + i * spacing));

        // Filling the inner area of tringle
        for (int j = 1; j < i; j++) {
            addEnemy(new GammaInvader(350 - i * spacing + j * spacing + 25, 50 + i * spacing));
        }
    }

    //Right side sprites
    for (int i = 1; i <= 5; i++) {
        addEnemy(new GammaInvader(350 + i * spacing, 50 + i * spacing));

        // Filling the inner area of the triangle
        for (int j = 1; j < i; j++) {
            addEnemy(new GammaInvader(350 + i * spacing - j * spacing, 50 + i * spacing));
        }
    }
        } 
		
		else if (phase == 3)
		{
    //cross sign shape
        for (int i = 0; i < 6; i++) {
        addEnemy(new GammaInvader(115 + i * 80, 50 + i * 40));
        addEnemy(new GammaInvader(115 + i * 80, 290 - i * 40));
    }
    addEnemy(new GammaInvader(580, 300));
    addEnemy(new GammaInvader(580,45));
        }
		else if (phase==4)
		{
		  int numEnemies = 15; //boundary
  float maxRadius = 200;
  for (float radius = 100; radius <= maxRadius; radius += 90) { 
    for (int i = 0; i < numEnemies; i++) { 
      float angle = 2 * 3.14159265 * i / numEnemies; 
      float x = 350 + radius * cos(angle); 
      float y = 225 + radius * sin(angle); 
      addEnemy(new GammaInvader(x, y)); 
    }
  }
		
		}
		
		else if (phase==5)
		{
			
			int spacing = 55; // gap
int offset = 35; 

// Diamond shape enemies
int diamondHeight = 4;
int diamondWidth = 9;
int centerX = diamondWidth / 2;

for (int i = 0; i < diamondHeight; i++) {
    for (int j = centerX - i; j <= centerX + i; j++) {
        addEnemy(new GammaInvader(50 + j * spacing, 50 + i * spacing - 40 ));
    }
}

for (int i = diamondHeight - 2; i >= 0; i--) {

    for (int j = centerX - i; j <= centerX + i; j++) {
        addEnemy(new GammaInvader(50 + j * spacing , 50 + (diamondHeight * 2 - i - 1) * spacing - offset - 40));
    }
}
			
		}
		
		else if (phase==6)
		{
			int n = 7; // heart sizee in colomn
 float spacing = 69.0f; // gap

for (int i = 0; i < n; i++)
{
    for (int j = 0; j < n; j++)
    {
        if (i == 0 && (j >= n / 5 && j <= n / 2 - n / 5) || i == 0 && (j >= n / 2 + n / 5 && j <= (n - 1) - n / 5))
            addEnemy(new GammaInvader(50 + j * spacing, 50 + i * spacing));
        else if (i > 0 && i <= n / 5 && (j >= n / 5 - i && j <= n / 2 + n / 5 - i || j >= n / 2 - n / 5 + i && j <= (n - 1) - n / 5 + i))
            addEnemy(new GammaInvader(50 + j * spacing, 50 + i * spacing));
        else if ((i > n / 5 && i <= n / 2) && (j >= 0 && j <= i - n / 5 || j >= (n - 1) - (i - n / 5) && j <= n - 1))
            addEnemy(new GammaInvader(50 + j * spacing, 50 + i * spacing));
        else if (i > n / 2 && (j >= i - n / 2 && j <= (n - 1) - (i - n / 2)))
            addEnemy(new GammaInvader(50 + j * spacing, 50 + i * spacing));
    }
}
		}
    }
	
	
};
