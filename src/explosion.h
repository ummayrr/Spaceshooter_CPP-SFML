class Explosion {
public:
    Sprite sprite;
    Texture texture;
    int frame;
    float frameTime;
    float timeSinceLastFrame;

    Explosion(string filename) {
        texture.loadFromFile(filename);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 64, 64));
        frame = 0;
        frameTime = 0.1;
        timeSinceLastFrame = 0;
    }

void update(float deltaTime) {
    timeSinceLastFrame += deltaTime;
    if (timeSinceLastFrame > frameTime) {
        frame++;
        if (frame >= 7) {
            frame = 0;
        }
        int x = frame * 64;
        sprite.setTextureRect(IntRect(x, 0, 64, 64));
        timeSinceLastFrame = 0;

        // Add debug output
        std::cout << "Explosion update: frame = " << frame << std::endl;
    }
}

};
