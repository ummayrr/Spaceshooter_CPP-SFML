#                                                                 Spaceshooter

## Description:
 A classic game where you control a spaceship and fight and score against hordes of enemies and monsters. You can upgrade your ship, collect power-
ups and use special abilities to defeat the bosses. This game is created with C++ and SFML using Object Oriented Programming techniques and features smooth graphics and sound effects.

## Features:

The game is primarily designed to utilize Object Oriented Programming concepts. Therefore it relies very little on the pre-defined SFML features of graphics, but the core mathematical procedures in the code, which produce the visuals and the animations.

- Three huge levels with variety of phases with difficulty increase in each phase. The phases in each level include three types of enemies: Alpha Invaders, Beta Invaders and Gamma Invaders.
- Each phase has different shapes. Level 1 includes the preliminary shapes such as rectangle, triangle and cross sign. Level 2 includes the advanced shapes such as circle, diamond and heart. Level 3 includes the combination of both the preliminary and advanced shapes but these
shapes would be filled.
- Boss fights, including Monsters, Dragons and a secret boss. Each boss has different patterns and different kind of attacks they can damage the player with.
- Lives system, there are 3 Lives a player has, before the ship blasts.
- Player can make use of addons, which fall at random intervals from above. Included addons: Life, Danger Sign, PowerUp, Enhanced Fire. Player ship and Bullets are upgraded according to the addon gained temporarily.
- Scoring functionality, the highscores are saved using File Handling utilizng fstream library. The top 3 positions are awarded medals which can are displayed when they are playing the game.
- Many misc details and animations, such as the galaxy is a wrap-around environment for the spaceship i.e., a spaceship disappears at one corner of the screen and then reappears from the
exact opposite corner, periodic damage to the ship, and screen shake etc.
- The game features fully functional audio and sound effects. Music can be turned on or off from the menu.
- The game includes following screens:
1. Game Menu screen
2. Instructions screen
3. Main Screen for gameplay
4. Pause Screen/Functionality
5. High Score and Players Names Display
6. End screen

## Gameplay Instructions

The player of the game controls a spaceship in an enemy filled space field. The goal is to destroy
the enemy ships, avoiding a collision with any of them. The spaceship can fire bullets to destroy the objects in
the space field. The spaceship is destroyed in case of a collision with an object (enemy ships) or
impact with a bomb fired by the enemy ship. Similarly, the dragon appears after a random
interval whereby its position is fixed, however, it could fire in 3 directions (downwards,
right-downwards and left-downwards). The direction of the fire would also be decided on the
basis of the position of the spaceship i.e. the dragon would fire in the zone where the spaceship
is currently located. On the other hand, the monster’s vertical position is fixed however it can
move in left and right directions. The monster will throw a beam of lightning on the spaceship
after regular intervals.

The player can move the spaceship in any direction (right, left, up, down and diagonally). The
spaceship moves in all possible directions. As an advanced move, a player can boost the
spaceship into powerup mode, i.e. a spaceship cannot be destroyed and fire a continuous beam
of bullets instead of periodic intervals.  At the start of the game, the shape of the enemies in the space field is
randomly selected. The number of enemies will be selected on the basis of that shape. Next
level is achieved once all enemies in the current field are destroyed. The next level starts with a
different shape and an increased number of enemies in the space field. The player is awarded
three lives initially. A life is decreased if the spaceship is destroyed. The player gets points for
hitting the objects. The number of remaining lives, and the score is displayed on the top of the
screen.

## Installation:

Note: The game is optimized on WSL (Windows Subsystem for Linux) in Ubuntu environment. For the optimal experience, the game should be played in the same, if you are dependent on the compiled file using the source files.

To install this game, you need to have [SFML](https://www.sfml-dev.org/) installed on your system. You can download SFML from [here](https://www.sfml-dev.org/download.php) or use your preferred package manager. You also need to have a C++ compiler that supports C++11 or higher. 

To compile and run this game, you can use the following commands:

```bash
# Clone this repository
git clone https://github.com/ummayrr/Spaceshooter_CPP-SFML.git

# Go to the repository folder
cd Spaceshooter_CPP-SFML

# Go to the source folder
cd src

# Compile the game
g++ -c main.cpp
g++ main.o -o Spaceshooter -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

# Run the game
./Spaceshooter
```

