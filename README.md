#                                                                 Spaceshooter

## Description:
 A classic game where you control a spaceship and fight and score against hordes of enemies and monsters. You can upgrade your ship, collect power-
ups and use special abilities to defeat the bosses. This game is created with C++ and SFML using Object Oriented Programming techniques and features smooth graphics and sound effects.

## Features:

The game is primarily designed to utilize Object Oriented Programming concepts. Therefore it relies very little on the pre-defined SFML features of graphics, but the core mathematical procedures in the code, which produce the visuals and the animations.

- Three huges levels with variety of phases and enemies, with difficulty increase in each level.
- Boss fights, including Monsters, Dragons and a secret boss.
- Scoring functionality, the highscores are saved using File Handling utilizng fstream library. The top 3 positions are awarded medals which can are displayed when they are playing the game.

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

