

class Level2 : public Level {
public:
    Level2() {
        createLevel2();
    }

void createLevel2()
{
		    int numEnemies = 16; //boundary
    float radius = 200; 

    for (int i = 0; i < numEnemies; i++) {
        float angle = 2 * 3.14159265 * i / numEnemies; 
        float x = 350 + radius * cos(angle); 
        float y = 225 + radius * sin(angle); 
        addEnemy(new BetaInvader(x, y));
    }
 
}

    void nextPhase() override
	{
        phase++;
        if (phase == 2) {
    int spacing = 55; //gap
    int offset = 35; // more gap

    // diamond shape enemies
    int diamondHeight = 5;
    int diamondWidth = 10;
    int centerX = diamondWidth / 2;

    for (int i = 0; i < diamondHeight; i++) {
        addEnemy(new BetaInvader(50 + (centerX - i) * spacing, 50 + i * spacing - 40 ));
        addEnemy(new BetaInvader(50 + (centerX + i) * spacing, 50 + i * spacing - 40));
    }

    for (int i = diamondHeight - 2; i >= 0; i--) {
        addEnemy(new BetaInvader(50 + (centerX - i) * spacing , 50 + (diamondHeight * 2 - i - 1) * spacing - offset - 40));
        addEnemy(new BetaInvader(50 + (centerX + i) * spacing , 50 + (diamondHeight * 2 - i - 1) * spacing - offset - 40));
    }
        } 
		
		else if (phase == 3)
		{
              int n = 7; // heart size
    float spacing = 69.0f; // gap

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == 0 && (j >= n / 5 && j <= n / 2 - n / 5) || i == 0 && (j >= n / 2 + n / 5 && j <= (n - 1) - n / 5))
                addEnemy(new BetaInvader(50 + j * spacing, 50 + i * spacing));
            else if (i > 0 && i <= n / 5 && (j == n / 5 - i || j == n / 2 + n / 5 - i || j == n / 2 - n / 5 + i || j == (n - 1) - n / 5 + i))
                addEnemy(new BetaInvader(50 + j * spacing, 50 + i * spacing));
            else if ((i > n / 5 && i <= n / 2) && (j == 0 || j == n - 1))
                addEnemy(new BetaInvader(50 + j * spacing, 50 + i * spacing));
            else if (i > n / 2 && (j == i - n / 2 || j == (n - 1) - (i - n / 2)))
                addEnemy(new BetaInvader(50 + j * spacing, 50 + i * spacing));
        }
    }
        }
    }
	
	
};
