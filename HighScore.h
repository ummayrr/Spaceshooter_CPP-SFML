#include <fstream>


class HighScore
{
public:
    static const int MAX_SCORES = 10;
    struct ScoreEntry {
        string name;
        int score;
    };

    ScoreEntry highScores[MAX_SCORES];
    string fileName;

    void sortScores() {
    // descending
    for (int i = 0; i < MAX_SCORES - 1; i++) {
        for (int j = i + 1; j < MAX_SCORES; j++) {
            if (highScores[j].score > highScores[i].score) {
                swap(highScores[i], highScores[j]);
            }
        }
    }
}

 HighScore(const string& file) : fileName(file) {
//empty values
    for (int i = 0; i < MAX_SCORES; i++) {
        highScores[i].name = "";
        highScores[i].score = 0;
    }

    loadHighScores();
}

void loadHighScores()
{
//empty
    for (int i = 0; i < 5; i++)
    {
        highScores[i].name = "";
        highScores[i].score = 0;
    }

    ifstream file(fileName);
    if (file.is_open())
    {
        for (int i = 0; i < 5 && !file.eof(); i++)
        {
            file >> highScores[i].name >> highScores[i].score;
        }
        file.close();
    }

    sortScores();
}


  void saveHighScores() {
    ofstream file(fileName);
    if (file.is_open()) {
        for (int i = 0; i < MAX_SCORES; i++) {
            // Only write non-empty positions to the file
            if (highScores[i].name != "" || highScores[i].score != 0) {
                file << highScores[i].name << " " << highScores[i].score << endl;
            }
        }
        file.close();
    }
}

	
    bool isHighScore(int score) const {
    return score > highScores[MAX_SCORES - 1].score;
}

    int getPlayerPosition(const string& name) const
    {
        for (int i = 0; i < 10; i++)
        {
            if (highScores[i].name == name)
            {
                return i + 1;
            }
        }
        return -1;
    }

void addHighScore(const string& name, int score) {

    bool nameExists = false;
    for (int i = 0; i < MAX_SCORES; i++) {
        if (highScores[i].name == name) {
            nameExists = true;
//update
            if (score > highScores[i].score) {
                highScores[i].score = score;
            }
            break;
        }
    }

    if (!nameExists) {
        int pos = -1;
        for (int i = 0; i < MAX_SCORES; i++) {
            if (highScores[i].name == "" && highScores[i].score == 0) {
                pos = i;
                break;
            }
        }

//add new if pos doesnt exist
        if (pos != -1) {
            highScores[pos].name = name;
            highScores[pos].score = score;
        } else {
//last position
            highScores[MAX_SCORES - 1].name = name;
            highScores[MAX_SCORES - 1].score = score;
        }
    }

    sortScores();
    saveHighScores();
}

void displayHighScores(sf::RenderWindow& window) {
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../img/scorebackground.jpg");

    sf::Sprite background(backgroundTexture);
    background.setScale(1,2);
    window.draw(background);

    sf::Font font;
    font.loadFromFile("../assets/AstroSpace-eZ2Bg.ttf");

     sf::Texture goldBadgeTexture;
     goldBadgeTexture.loadFromFile("../img/gold.png");
     sf::Texture silverBadgeTexture;
     silverBadgeTexture.loadFromFile("../img/silver.png");
     sf::Texture bronzeBadgeTexture;
     bronzeBadgeTexture.loadFromFile("../img/bronze.png");

     for (int i = 0; i < MAX_SCORES; i++) {

         sf::Sprite badge;
         if (i == 0) {
             badge.setTexture(goldBadgeTexture);
         } else if (i == 1) {
             badge.setTexture(silverBadgeTexture);
         } else if (i == 2) {
             badge.setTexture(bronzeBadgeTexture);
         }

         // set badge position
         badge.setPosition(50, 0 + i * 75);

         if (i < 3) {
             window.draw(badge);
         }

        sf::Text text;
        text.setFont(font);
        if (highScores[i].name != "" || highScores[i].score != 0) {
            text.setString(to_string(i + 1) + ". " + highScores[i].name + " " + to_string(highScores[i].score));
        } else {
            text.setString(to_string(i + 1) + ". ?");
        }
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition(100, 20 + i * 75);
        window.draw(text);
    }

    window.display();
}

};