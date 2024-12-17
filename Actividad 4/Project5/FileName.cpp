#include <SFML/Graphics.hpp>


    // Crear una ventana de 800x800
    sf::RenderWindow window(sf::VideoMode(800, 800), "Tablero de Ajedrez");

    // Definir el tamaño de cada casilla (8x8 casillas en total)
    int tileSize = 100;  // 800/8 = 100 para que el tablero ocupe toda la ventana

    // Bucle principal
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Limpiar la ventana
        window.clear();

        // Dibujar el tablero
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                // Crear un rectángulo para cada casilla
                sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));

                // Posición de la casilla
                tile.setPosition(col * tileSize, row * tileSize);

                // Alternar colores entre blanco y negro
                if ((row + col) % 2 == 0) {
                    tile.setFillColor(sf::Color::White);
                }
                else {
                    tile.setFillColor(sf::Color::Black);
                }

                // Dibujar la casilla
                window.draw(tile);
            }
        }

        // Mostrar lo que hemos dibujado en la ventana
        window.display();
    }

    return 0;
}