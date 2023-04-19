


#include <iostream>
#include <vector>
#include<algorithm>
#include <string>
#include <math.h>
#include <sstream>
#include <bits/stdc++.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

//#include <time.h>
//using namespace sf;
using namespace std;

class CustomRectangleShape : public sf::RectangleShape{
public:
    sf::Vector2f size,position;
    CustomRectangleShape(sf::Vector2f size,sf::Vector2f position,sf::Vector2f speed){
        setPosition(position);
        setSize(size);
        speedX = speed.x;
        speedY = speed.y;
    }
    void animate(const sf::Time elapsed){
        sf::Vector2f pos = getPosition();
        float t = elapsed.asSeconds();
        bounce();
        setPosition(pos.x + t * speedX,pos.y + t * speedY);
    }
    void moveInDirection(const sf::Time &elapsed, const sf::Keyboard::Key &key){
        sf::Vector2f pos = getPosition();
        sf::FloatRect size =getGlobalBounds();
        float x=0,y=0;
        if(key == sf::Keyboard::S)
             y = speedY;
         else if(key == sf::Keyboard::W)
             y = -speedY;
         else if(key == sf::Keyboard::D)
             x = speedX;
         else if(key == sf::Keyboard::A)
             x=-speedX;

         x  *= elapsed.asSeconds();
         y  *= elapsed.asSeconds();
         if (getGlobalBounds().top  + y< minY ) {
            y=0;
            setPosition(pos.x,minY - size.height / 2.0);
         }
         if (getGlobalBounds().left  + x< minX ) {
             x=0;
             setPosition(minX + size.width / 2.0,pos.y);
         }
         if (getGlobalBounds().top + getGlobalBounds().height + y > maxY ){
             y=0;
             setPosition(pos.x,maxY - size.height / 2.0);
         }
         if ( getGlobalBounds().left + getGlobalBounds().width  + x> maxX ) {
             x=0;
             setPosition(maxX - size.width / 2.0,pos.y);
         }
        setPosition(pos.x + x,pos.y + y);

    }
    bool isClicked(sf::Vector2i mp) const{
        return abs( getPosition().x - mp.x + getGlobalBounds().width/2.0 ) < getGlobalBounds().width/2.0 && abs( getPosition().y  - mp.y +getGlobalBounds().height/2.0 ) < getGlobalBounds().height/2.0;                  ;
    }
    void setBounds( float minX,float minY,float maxX,float maxY){
        this->minX = minX;
        this->maxX = maxX;
        this->minY = minY;
        this->maxY = maxY;
    }
private:
    float speedX,speedY;
    float minX,minY,maxX,maxY;
    void bounce(){
        if (getGlobalBounds().top  < minY ) speedY = abs(speedY);
        if (getGlobalBounds().left < minX ) speedX = abs(speedX);
        if (getGlobalBounds().top + getGlobalBounds().height > maxY ) speedY = -abs(speedY);
        if ( getGlobalBounds().left + getGlobalBounds().width > maxX ) speedX =-abs(speedX);
    }
};
int main(){
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    int width=100,height=50;
    vector<CustomRectangleShape> rectangles;
    for (int i=0;i<10;i++){
        CustomRectangleShape r(sf::Vector2f(width,height),sf::Vector2f(rand() % (window.getSize().x-width) +width/2.0, rand() % (window.getSize().y-height) + height/2.0),sf::Vector2f(1500,1500));
        r.setFillColor(sf::Color(200,200,200));
        r.setBounds(0,0,window.getSize().x,window.getSize().y);
        rectangles.push_back(r);
    }
    int current = 0;
    sf::Clock clock;

    while (window.isOpen()) {
       sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.mouseButton.button == sf::Mouse::Left)
                for(int i=0;i<(int)rectangles.size();i++)
                    if(rectangles[i].isClicked(sf::Mouse::getPosition(window)))
                        current = i;

        }
        sf::Keyboard::Key keys[4]{sf::Keyboard::W,sf::Keyboard::S,sf::Keyboard::A,sf::Keyboard::D};
        for (int i=0;i<4;i++)
        if (sf::Keyboard::isKeyPressed(keys[i]))
            rectangles[current].moveInDirection(elapsed,keys[i]);

        window.clear(sf::Color::Black);

        for(auto &rec : rectangles) rec.setFillColor(sf::Color(200,200,200));
        rectangles[current].setFillColor(sf::Color(200,0,0));
        for(auto &rec : rectangles) window.draw(rec);

        window.display();
    }
    return 0;
}











