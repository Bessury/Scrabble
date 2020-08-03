#include "/mnt/c/Users/nimak/Git/Scrabble/headers/board.h"
#include "/mnt/c/Users/nimak/Git/Scrabble/headers/bag.h"
#include "/mnt/c/Users/nimak/Git/Scrabble/headers/game.h"
#include "headers/player.h"
#include <SFML/Graphics.hpp>



int main() {
    const double WIN_SIZE_X = 1920;
    const double WIN_SIZE_Y = 1080;

    sf::Font font;
    if (!font.loadFromFile("source/fonts/OpenSans-Regular.ttf")) {
        throw std::invalid_argument("Cannot load font");
    }


    sf::Text pos_text;
    pos_text.setPosition(600, 300);
    pos_text.setCharacterSize(15);
    pos_text.setFont(font);
    pos_text.setFillColor(sf::Color::Black);

    sf::Text text;
    text.setPosition(600, 320);
    text.setCharacterSize(15);
    text.setFont(font);
    text.setFillColor(sf::Color::Black);

    sf::Texture t;
	t.loadFromFile("/mnt/c/Users/nimak/Git/Scrabble/source/images/cell.jpg");
	sf::Sprite s(t);
    sf::RenderWindow app(sf::VideoMode(WIN_SIZE_X, WIN_SIZE_Y), "Scrabble");
    Board board;
    double w = 32;

 
    sf::Text letter;
    letter.setCharacterSize(15);
    letter.setFont(font);
    letter.setFillColor(sf::Color::Black);

    while (app.isOpen()) {
        sf::Vector2i position = sf::Mouse::getPosition(app);
        int x = (position.x) / w;
		int y = (position.y) / w;

        sf::Event event;
        while (app.pollEvent(event)) {
            if (event.type  == sf::Event::Closed) {
                app.close();
                break;
            }
        }
        app.clear(sf::Color::White);
        
        for (size_t i = 0; i < board.GetSizeRows(); i++) { 
            for (size_t j = 0; j < board.GetSizeColumns(); j++ ) {
                if (i == x && y == j) 
                    s.setTextureRect(sf::IntRect(0, 0, w, w));  
                else 
                    s.setTextureRect(sf::IntRect(w, 0, w, w));
                s.setColor(board.GetColor(i,j));
                s.setPosition(i*w,j*w);
                app.draw(letter);
                app.draw(s);
            }
        }

        

        pos_text.setString("x = " + std::to_string(sf::Mouse::getPosition(app).x) + ", y = " + std::to_string(sf::Mouse::getPosition(app).y));    
        text.setString("i = " + std::to_string(x) + ", j = " + std::to_string(y));
        app.draw(pos_text);
        app.draw(text);
        app.display();
    }
}