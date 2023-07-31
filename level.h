class Level {
public:
    static const int MAX_ENEMIES = 200;
    Enemy* enemies[MAX_ENEMIES];
    int enemyCount;
    int phase;
    bool showEnemies;
	
 Level() {
        enemyCount = 0;
        phase = 1;
    showEnemies=true;
	}
	
void removeEnemy(int index) {
    if (index >= 0 && index < enemyCount) {
//not dead
        enemies[index]->isAlive = false;
    }
}
	
	    void updateEnemies(float deltaTime) {
        bool reverseDirection = false;
        if (enemyCount > 0) {
            Enemy* firstEnemy = enemies[0];
            if (firstEnemy->positionX < 50 || firstEnemy->positionX > 750) {
                reverseDirection = true;
            }
        }

        for (int i = 0; i < enemyCount; i++) {
            enemies[i]->move(deltaTime);

            if (reverseDirection) {
                enemies[i]->directionX = -enemies[i]->directionX;
                enemies[i]->positionY += 50;
            }
        }
    }

    void addEnemy(Enemy* enemy) {
        if (enemyCount < MAX_ENEMIES) {
            enemies[enemyCount++] = enemy;
        }
    }

    virtual void nextPhase() = 0; // pure virtuallll
};
