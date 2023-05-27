


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


sf::Texture loadTexture(string path){
    sf::Texture texture;
    if (!texture.loadFromFile(path))  std::cerr << "Could not load texture " <<path << std::endl;
    return texture;
}

//custom texture for better scalling depending on window size
class Texture{
public:
    sf::Vector2f resolution;
    sf::Vector2f size;
    sf::Texture texture;
    Texture(std::string path,int resX,int resY,sf::RenderWindow &window){
        if (!texture.loadFromFile(path))  std::cerr << "Could not load texture " <<path << std::endl;
        this->resolution = sf::Vector2f(resX,resY);
        this->size =  sf::Vector2f (window.getSize().x/resolution.x,window.getSize().y/resolution.y );
    }
};
//main structure
class Transform {
public:

    sf::Sprite sprite;


    Transform *parent;

    Transform() {}

    sf::Vector2f position;
    void setTexture(Texture &t,float sx,float sy=0){//texture size, 1 / world size = actual size
        sprite.setTexture(t.texture);
        if (sy ==0) sprite.setScale(t.size.x *sx,t.size.x *sx);
        else if (sx ==0) sprite.setScale(t.size.y *sy,t.size.y *sy);
        else sprite.setScale(t.size.x *sx,t.size.y *sy);
    }
    void draw( sf::RenderWindow &window){
        sprite.setPosition(window.getSize().x * position.x,window.getSize().y * position.y);
        window.draw(sprite);
    }
};


int main(){
    sf::RenderWindow window(sf::VideoMode(800, 550), "PVZ");
    sf::Vector2u w = window.getSize();


    //if we want to resamble the shape set the res to only bigger value and then use the same axis in setTexture
    Texture sqr("squere.png",124,124,window);

    list<Transform> objects;
    float n=5,m=10;
    for (int x=0;x<m;x++)
    for (int y=0;y<n;y++) {
        Transform ground;
        ground.setTexture(sqr, 1/m * 0.8, 1/n/2);
        ground.position = sf::Vector2f(1/m * 0.8 * x, 0.5 + 0.5/n*y);

        if (int(x+y)%2)        ground.sprite.setColor(sf::Color(10, 200, 30));
        else         ground.sprite.setColor(sf::Color(200, 100, 100));
        objects.push_back(ground);
    }

   // ground.sprite.setPosition(w.x/2.0,w.y/2.0);

//    Player player (sf::Vector2f(w.x/2.0,w.y/2.0),350);
//    player.setBounds(0,0,window.getSize().x,window.getSize().y);
//    player.setTexture(window.getSize(),p,512,12);
//    player.height *= 379/277.0;
//    player.spriteTrans.y *= 379/277.0;



    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
//            if(event.mouseButton.button == sf::Mouse::Left)
//                for(int i=0;i<(int)rectangles.size();i++)
//                    if(rectangles[i].isClicked(sf::Mouse::getPosition(window)))
//                        current = i;

        }
//        sf::Keyboard::Key keys[4]{sf::Keyboard::W,sf::Keyboard::S,sf::Keyboard::A,sf::Keyboard::D};
//        for (int i=0;i<4;i++)
//            if (sf::Keyboard::isKeyPressed(keys[i]))
//                player.moveInDirection(elapsed,keys[i],map);
//
//        window.clear(sf::Color::Black);
//        for(auto s :bg) window.draw(s);
//        for(auto s :map) window.draw(s.getSprite());
//        window.draw(player.getSprite());
        for (Transform t : objects)t.draw(window);
        window.display();
    }
    return 0;
}



class BoxCollider : public sf::RectangleShape{
public:

    float width,height;
    sf::Vector2f spriteTrans,s;
    sf::Sprite sprite;
    BoxCollider() = default;

    void setTexture(sf::Vector2u w,sf::Texture &t,float tsx,float wsx,float tsy=0,float wsy=0){//texture size, 1 / world size = actual size
        sprite.setTexture(t);
        if (tsy ==0){
            sprite.setScale((float)w.x/wsx/tsx,(float)w.x/wsx/tsx);
            width = w.x / wsx;
            height = width;
        }else{
            sprite.setScale((float)w.x/wsx/tsx,(float)w.y/wsy/tsy);
            width = w.x / wsx;
            height = w.y / wsy;
        }
        spriteTrans = sf::Vector2f(-width/2.0,-height/2.0);
    }
    sf::Sprite getSprite(){
        sprite.setPosition(getPosition() + spriteTrans);
        return sprite;
    }
};
class Player : public BoxCollider{
public:

    Player(sf::Vector2f position,float speed) {
        setPosition(position);
        this ->speed=speed;
    }

    void moveInDirection(const sf::Time &elapsed, const sf::Keyboard::Key &key,vector<BoxCollider> colliders){
        sf::Vector2f pos = getPosition();
        sf::FloatRect size =getGlobalBounds();
        float x=0,y=0;
        if(key == sf::Keyboard::S)
            y = speed;
        else if(key == sf::Keyboard::W)
            y = -speed;
        else if(key == sf::Keyboard::D)
            x = speed;
        else if(key == sf::Keyboard::A)
            x=-speed;

        x  *= elapsed.asSeconds();
        y  *= elapsed.asSeconds();


        for ( BoxCollider c : colliders){


            sf::Vector2f d = (c.getPosition())  - (getPosition()+ sf::Vector2f(x,y) );

            if( (abs(d.x) < ( width/2.0 + c.width / 2.0)) && (abs(d.y) < (c.height/2.0 + height/2.0)))

            {x=0;y=0;        cout << d.x << " " << d.y<< "\t"<<width  << "\t" << c.width <<endl;}

        }

        if (pos.y  + y - height/2.0< 0 || pos.y + height/2.0 + y > maxY ) y=0;
        if (pos.x  + x - width/2.0< 0 || pos.x + width/2.0+ x > maxX ) x=0;


        setPosition(pos.x + x,pos.y + y);

    }
    void setBounds( float minX,float minY,float maxX,float maxY){
        this->minX = minX;
        this->maxX = maxX;
        this->minY = minY;
        this->maxY = maxY;
    }
private:
    float speed;
    float minX,minY,maxX,maxY;
};
