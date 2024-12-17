#include <SFML/Graphics.hpp>
#include <cmath> 

int main() {
    
    const int windowWidth = 800;
    const int windowHeight = 600;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Bounce");

    
    sf::CircleShape circle(20.f); 
    circle.setFillColor(sf::Color::Blue);
    float posX = windowWidth / 2.0f; 
    float posY = 0.0f;               

   
    float velocityY = 0.0f;          
    const float gravity = 500.0f;   
    const float reboundFactor = 0.7f; 
    const float groundLevel = windowHeight - circle.getRadius() * 2; 

    
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        
        float deltaTime = clock.restart().asSeconds();

       
        velocityY += gravity * deltaTime;

        
        posY += velocityY * deltaTime;

        
        if (posY >= groundLevel) {
            posY = groundLevel;                      
            velocityY = -velocityY * reboundFactor;  

            
            if (std::abs(velocityY) < 5.0f) {
                velocityY = 0.0f;
            }
        }

        
        circle.setPosition(posX, posY);

        
        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }

    return 0;
}
