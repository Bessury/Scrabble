#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

struct Direction {
    bool down = false;
    bool right = false;
    bool left = false;
    bool up = false;           
};


std::pair<int,int> Move(const Direction& m) {
    int x = 0, y = 0; 
    if (m.left) x--;
    if (m.right) x++;
    if (m.up) y--;
    if (m.down) y++;
    return {x,y};
}


void Test() {
    sf::Font font;
    std::string source = "/mnt/c/Users/nimak/Git/Scrabble/fonts/OpenSans-Regular.ttf";
    if (!font.loadFromFile(source)) {
        throw std::invalid_argument("Cannot load file : " + source);
    }
    sf::Text position;
    position.setPosition(350, 0);
    position.setFont(font);
    position.setCharacterSize(15);
    position.setFillColor(sf::Color::White);


    const size_t WIN_SIZE_X = 1000;
    const size_t WIN_SIZE_Y = 1000;
    sf::RenderWindow window(sf::VideoMode(WIN_SIZE_X, WIN_SIZE_Y), "SFML works!");
    auto colour = sf::Color::Black;
    float dx = 2.;
    float dy = 2.;

    Direction dir;
    float rad = 75;
    sf::CircleShape circle(rad);
	circle.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Right)
                    dir.right = true;
                else if (event.key.code == sf::Keyboard::Down)
                    dir.down = true;
                else if (event.key.code == sf::Keyboard::Left)
                    dir.left = true;
                else if (event.key.code == sf::Keyboard::Up) 
                    dir.up = true;        
                break;
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Right)
                    dir.right = false;
                else if (event.key.code == sf::Keyboard::Down)
                    dir.down = false;
                else if (event.key.code == sf::Keyboard::Up)
                    dir.up = false;
                else if (event.key.code == sf::Keyboard::Left)
                    dir.left = false;    
                break;
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }
     
        window.clear(colour);

        auto m = Move(dir);
        
        if (m.first || m.second) {
            rad -= 0.02;
            circle.setRadius(rad);
            if (circle.getPosition().x + dx*m.first > 0 && 
            circle.getPosition().y + dy*m.second > 0 &&
            circle.getPosition().x + dx*m.first < 900 &&
            circle.getPosition().y + dy*m.second < 800) {
                circle.move(m.first * dx, m.second * dy);
                
            }
        }

        

        position.setString("x = " + std::to_string(circle.getPosition().x) + ", y = " + std::to_string(circle.getPosition().y));    
        window.draw(circle);
        window.draw(position);
        window.display();
    
    }
}



int main() {
    Test();
    return 0;
}