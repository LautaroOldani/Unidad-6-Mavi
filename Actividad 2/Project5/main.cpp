#include <SFML/Graphics.hpp>
#include <cmath> 

int main() {
    
    const int windowWidth = 800;
    const int windowHeight = 600;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Space");

    
    sf::CircleShape circle(20.f);
    circle.setFillColor(sf::Color::Green);
    float posX = windowWidth / 2.0f; 
    float posY = windowHeight / 2.0f; 

    
    float velocityX = 0.0f; 
    float accelerationX = 0.0f; 
    const float maxSpeed = 300.0f; 
    const float accelerationRate = 200.0f; 
    const float decelerationRate = 150.0f; 

    
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        
        float deltaTime = clock.restart().asSeconds();

        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            accelerationX = accelerationRate;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            accelerationX = -accelerationRate;
        }
        else {
            
            if (std::abs(velocityX) > 0.1f) { 
                accelerationX = (velocityX > 0 ? -decelerationRate : decelerationRate);
            }
            else {
                velocityX = 0.0f; 
                accelerationX = 0.0f;
            }
        }

        
        velocityX += accelerationX * deltaTime;

        
        if (velocityX > maxSpeed) velocityX = maxSpeed;
        if (velocityX < -maxSpeed) velocityX = -maxSpeed;

        
        posX += velocityX * deltaTime;

       
        if (posX < 0) posX = 0;
        if (posX > windowWidth - circle.getRadius() * 2) posX = windowWidth - circle.getRadius() * 2;

        
        circle.setPosition(posX, posY);

        
        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }

    return 0;
}
