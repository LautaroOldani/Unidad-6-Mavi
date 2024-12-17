#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>

int main() {
    
    const int windowWidth = 800;
    const int windowHeight = 600;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Fast & Furious");

    sf::CircleShape circle(20.f); 
    circle.setFillColor(sf::Color::Red);
    float posX = 0; 
    float posY = windowHeight / 2.0f - circle.getRadius();
    float velocity = 100.0f; 
    const float velocityIncrement = 100.0f; 
    const float vFinal = 400.0f; 

    
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

       
        float deltaTime = clock.restart().asSeconds();

        
        posX += velocity * deltaTime;

        
        if (posX > windowWidth) {
            posX = -circle.getRadius(); 
            if (velocity < vFinal) {
                velocity += velocityIncrement; 
            }
        }

        
        circle.setPosition(posX, posY);

       
        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }

    return 0;
}
