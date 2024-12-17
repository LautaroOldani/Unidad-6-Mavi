#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib> 
#include <ctime>   


class Enemy {
private:
    sf::CircleShape shape;
    float posX, posY;
    float velocityX, accelerationX; 
    bool isMRU; 

public:
    Enemy(float x, float y, float v, float a, bool mru)
        : posX(x), posY(y), velocityX(v), accelerationX(a), isMRU(mru) {
        shape.setRadius(20.f);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(posX, posY);
    }

    void update(float deltaTime) {
        if (isMRU) {
            
            posX += velocityX * deltaTime;
        }
        else {
            
            posX += velocityX * deltaTime + 0.5f * accelerationX * deltaTime * deltaTime;
            velocityX += accelerationX * deltaTime;
        }

        
        if (posX > 800) posX = -40.f;

        shape.setPosition(posX, posY);
    }

    bool isHit(float mouseX, float mouseY) {
        
        return shape.getGlobalBounds().contains(mouseX, mouseY);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }
};


class Game {
private:
    sf::RenderWindow window;
    std::vector<Enemy> enemies;
    int score;

public:
    Game() : window(sf::VideoMode(800, 600), "Wild Physics"), score(0) {
        srand(static_cast<unsigned>(time(0))); 
        
        for (int i = 0; i < 5; ++i) {
            float x = static_cast<float>(rand() % 800);
            float y = static_cast<float>(rand() % 600);
            float v = static_cast<float>(rand() % 100 + 50); 
            float a = static_cast<float>(rand() % 50 - 25);  
            bool isMRU = rand() % 2 == 0; 
            enemies.emplace_back(x, y, v, a, isMRU);
        }
    }

    void run() {
        sf::Clock clock;

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        float mouseX = static_cast<float>(event.mouseButton.x);
                        float mouseY = static_cast<float>(event.mouseButton.y);
                        handleMouseClick(mouseX, mouseY);
                    }
                }
            }

            
            float deltaTime = clock.restart().asSeconds();

            
            for (auto& enemy : enemies) {
                enemy.update(deltaTime);
            }

           
            window.clear(sf::Color::Black);
            for (auto& enemy : enemies) {
                enemy.draw(window);
            }

           
            sf::Font font;
            if (font.loadFromFile("arial.ttf")) {
                sf::Text scoreText("Score: " + std::to_string(score), font, 20);
                scoreText.setFillColor(sf::Color::White);
                scoreText.setPosition(10.f, 10.f);
                window.draw(scoreText);
            }

            window.display();
        }
    }

    void handleMouseClick(float mouseX, float mouseY) {
        for (auto it = enemies.begin(); it != enemies.end(); ++it) {
            if (it->isHit(mouseX, mouseY)) {
                score += 10; 
                enemies.erase(it); 
                break;
            }
        }
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}

