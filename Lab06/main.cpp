


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
    Player(sf::Vector2f position,float speed,string path) {
        setPosition(position);
        this ->speed=speed;
        sheet =  loadTexture(path);
    }


    void update(const sf::Time &elapsed, vector<BoxCollider> colliders){
        sf::Vector2f pos = getPosition();
        sf::FloatRect size =getGlobalBounds();



        float x=0,y=0;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) y = speed;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) y = -speed;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) x = speed;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) x = -speed;

         x  *= elapsed.asSeconds();
         y  *= elapsed.asSeconds();


             if(x != 0){
                 animChoosen = 4;



                dir = x/abs(x);
             }
             else animChoosen = 8;



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
    void animate(){
           //512,576     8x9characters

        if (animChoosen == 8) animFrame = 0;
           sprite.setTextureRect(sf::IntRect(animFrame % 8 * 512/8, 576/9.0 *animChoosen,dir* 512/8, 576/9.0));
           animFrame += 1;

    }
public:
    int dir;
    float speed;
    float minX,minY,maxX,maxY;
    int animFrame;
    int animChoosen = 8;
    sf::Texture sheet;
};
int main(){

    sf::RenderWindow window(sf::VideoMode(800, 550), "Platformer");
    sf::Vector2u w = window.getSize();



   //425x425
   sf::Texture wall = loadTexture("wall.jpg");
   //1134x1134
   sf::Texture grass = loadTexture("grass.png");


   Player player (sf::Vector2f(w.x/2.0,w.y/2.0),350,"playerSheet.png");
   //512,576

   player.setBounds(0,0,window.getSize().x,window.getSize().y);
   player.sprite.setTexture(player.sheet);
  // player.height *= 379/277.0;
  // player.spriteTrans.y *= 379/277.0;




   int mapS=4;
   vector<sf::Sprite> bg;
   for (int x=0;x<mapS;x++)
   for (int y=0;y<mapS;y++){
       sf::Sprite sprite;
       sprite.setTexture(grass);
       sprite.setScale((float)w.x/mapS/1134.0,(float)w.x/mapS/1134.0);
       sprite.setPosition(w.x / (float)mapS * x,  w.y / (float)mapS * y);
       bg.push_back(sprite);
   }



   int pos[]{0,0, 0,1, 1,1, 1,2, 1,3, 2,1
            , 5,0, 6,0, 4,1, 5,1, 4,2, 4,4,
            6,4,6,3};
    int wallS = 7 ;
    vector<BoxCollider> map;
    for (int i=0;i<14;i++){
        //BoxCollider a(wall,sf::Vector2f(w.x/wallS,w.x/wallS));
        BoxCollider a;
        a.setTexture(w,wall,425,wallS);
        a.setPosition(w.x/wallS * pos[i*2]+a.width/2.0, w.x/wallS * pos[i*2 + 1] + a.height/2.0);
        map.push_back(a);
    }
    sf::Clock clock;


    float time;

    while (window.isOpen()) {
       sf::Time elapsed = clock.restart();
        time += elapsed.asMilliseconds();



        if (time > 50){
            time -= 50;
            player.animate();
        }


        player.update(elapsed,map);

        //add keys to que so nothing will be skipped on low fps
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

        window.clear(sf::Color::Black);
        for(auto s :bg) window.draw(s);
        for(auto s :map) window.draw(s.getSprite());
        window.draw(player.getSprite());
        window.display();
    }
    return 0;
}













