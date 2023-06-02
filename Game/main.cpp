#include <iostream>
#include <vector>
#include<algorithm>
#include <string>
#include <math.h>
#include <sstream>
#include <bits/stdc++.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

//#include <time.h>
//using namespace sf;
using namespace std;


int money = 150;
int selected=-1;
sf::RenderWindow window(sf::VideoMode(800, 550), "PVZ");
sf::Vector2u w = window.getSize();
sf::Vector2f mouse;
int n=5,m=10;
bool lost;


//custom texture for better scalling depending on window size
class Texture{
public:
    Texture(){

    }
    sf::Vector2f resolution;
    sf::Vector2f size;
    sf::Texture texture;
    Texture(std::string path,int resX,int resY,sf::RenderWindow &window){
        if (!texture.loadFromFile(path))  std::cerr << "Could not load texture " <<path << std::endl;
        this->resolution = sf::Vector2f(resX,resY);
        this->size =  sf::Vector2f (window.getSize().x/resolution.x,window.getSize().y/resolution.y );
    }
    Texture(std::string path,int resX,int resY,int moveX,int moveY,sf::RenderWindow &window){
        if (!texture.loadFromFile(path,sf::IntRect(moveX,moveY,resX,resY)))  std::cerr << "Could not load texture " <<path << std::endl;
        this->resolution = sf::Vector2f(resX,resY);
        this->size =  sf::Vector2f (window.getSize().x/resolution.x,window.getSize().y/resolution.y );
    }
};
//main structure
class Transform {
public:
    sf::Sprite sprite;
    sf::Vector2f position = sf::Vector2f ();
    float health;
    sf::Vector2f size;
    Transform *parent;

    Transform() {}
    bool cross(sf::Vector2f a){
        return (a.x > position.x && a.x < position.x + size.x && a.y > position.y && a.y < position.y + size.y);
    }
    bool cross(Transform a) {
        sf::Vector2f d = a.position + sf::Vector2f (a.size.x/2.0,a.size.y/2.0) - position -  sf::Vector2f (size.x/2.0,size.y/2.0);
        return 2 * abs(d.x) < size.x + a.size.x && 2 * abs(d.y)  < size.x + a.size.y;
    }
    void setTexture(Texture &t,float sx,float sy=0){//texture size, 1 / world size = actual size
        sprite.setTexture(t.texture);
        size = sf::Vector2f (sx,sy);

        if (sy ==0) {
            sprite.setScale(t.size.x * sx, t.size.x * sx);
            size.y = sx;
        }
        else if   (sx == 0){
            sprite.setScale(t.size.y * sy, t.size.y * sy);
            size.x = sy;
        }
        else sprite.setScale(t.size.x *sx,t.size.y *sy);
    }
    virtual void draw( sf::RenderWindow &window,sf::Vector2u w){
        sprite.setPosition( w.x * position.x,w.y * position.y);
        window.draw(sprite);
    }
};
class Zombie : public Transform{
public:
    float speed,attackSpeed;
    int line;
    bool onPlant;
    float time;
    Transform *tur;
    void update(float t) {
        if(!onPlant) position.x -= speed * t / 1000.0;
        else{
            time += t;
            if(time >= attackSpeed) {
                tur->health -= 1;
                time = 0;
            }
        }
        if (position.x < 0.05) lost = true;
        onPlant = false;
    }
};
const int maxZombies = 100;
const int waves = 4;
class ZombieMenager{
public:
    float time;
    Zombie exampleZombies[1];
    Zombie zombies[maxZombies];
    bool linesTaken[5];
    int count;

    int summonCount[waves] {1,2,4,4};
    int summonTime[waves] {10000,5000,2000, 200};
    int summonCounter;
    void update(float t){
        time += t;
        for(int i=0;i<count;i++) {
            zombies[i].update(t);
            if(zombies[i]. health <= 0)
                i = Remove(i);
        }
        if (summonCounter >= waves) return;
        if (time > summonTime[summonCounter]) {
            for (int i=0;i<summonCount[summonCounter];i++)
//should summon not on the same line to do
                Summon(0,rand()%5);
            summonCounter++;
            time = 0;
        }
    }
    int Remove(int n){
        for (int i=n;i<count;i++) zombies[i] = zombies[i+1];
        count --;
        for (int i=0;i<5;i++) linesTaken[i] = false;
        for (Zombie z:zombies)  linesTaken[z.line] = true;
        return n-1;
    }
    void Summon(int type,int line){
        zombies[count] = exampleZombies[type];
        zombies[count].position.x = 1.1;
        zombies[count].position.y = 0.5 + line * 0.1;
        zombies[count].line = line;
        linesTaken[line] = true;
        count++;
    }
    void draw(){
        for(int i=0;i<count;i++){
            zombies[i].draw(window,w);
        }
    }
};

ZombieMenager zm;

class Bullet : public Transform{
public:
    float speed,dmg;
    int index;
    float time = 0;
    int sun=0;
    void update(float t){
        time += t;
        if (sun > 0) {
            if (time < 450)
            position.y -= speed * t / 1000.0;
            else if (time < 1000)
                position.y += speed * t / 1000.0;

        }
        else
        position.x += speed * t / 1000.0;
    }
};
const int bulletMax = 15;

class Turret : public Transform{
public:
    float shootSpeed;
    Bullet bullet;
    Bullet bullets[bulletMax];
    int bCount = 0;
    float time;
    int line;
    void update(float t){
        time += t;

        if (shootSpeed != 0 && time > shootSpeed) {
            time = 0;
            if (bCount < bulletMax) {
                if (zm.linesTaken[line] || bullet.sun > 0) {

                    bullets[bCount] = bullet;
                    bullets[bCount].index = bCount;
                    bullets[bCount].position = position + sf::Vector2f(size.x / 2.0, size.y / 2.0);
                    if (bullet.sun > 0)
                        bullets[bCount].position += sf::Vector2f(((rand() % 100) / 100.0 - 0.5) / float(m), 0);
                    bCount++;
                }
            }
        }
        for(int i=0;i<bulletMax;i++){
            bullets[i].update(t);
            if (bullets[i].sun > 0){
                if (bullets[i].time > 10000) {
                   i= RemoveBullet(i);
                }
                else if (bullets[i].cross(mouse))
                {
                    money += bullets[i].sun;
                    i =RemoveBullet(i);
                }
            }

            else if(bullets[i].position.x > 1  ||bullets[i].position.y < 0 ) {

                i=RemoveBullet(i);
            }
            else{
                for ( int z=0;z<zm.count;z++)
                    //to redo for whole zombie collision
                    if(bullets[i].cross(zm.zombies[z])){
                        i= RemoveBullet(i);
                        zm.zombies[z].health -= bullets[i].dmg;
                    }

            }

        }
    }
    int RemoveBullet(int n){
        for (int i=n;i<bCount;i++)
        {
            bullets[i] = bullets[i+1];
            bullets[i].index = i;
        }
        bCount --;
        return n-1;
    }
    void draw(sf::RenderWindow &window,sf::Vector2u w){
        Transform::draw(window,w);
        for(int i=0;i<bulletMax;i++){
            bullets[i].draw(window,w);
        }
    }
};
class Shop : public Transform{
public:
    int cost;
    int plantIndex;
    Turret plant;
};
class MapTile : public Transform{
public:
    bool taken;
    Turret turret;
    int line;
    void update(float t){
        if(turret.health<=0) taken = false;
        if (taken) turret.update(t);
    }
    void draw(sf::RenderWindow &window,sf::Vector2u w){
        if (taken) turret.draw(window,w);
    }
};

class Text{
public:
    Texture tex[10];
    Transform trans[4];
    int value;
    float sx,sy;
    Text(float px,float py,float sx, float sy=0){
        this->sx = sx;
        this->sy = sy;
        for(int y=0;y<2;y++)
        for(int x=0;x<5;x++)
            //335 200
            if(y*5+x+1 == 10)
            tex[0]  = Texture("numbers.png",355/5,100,71*x,100*y,window);
        else
            tex[y*5+x+1]  = Texture("numbers.png",355/5,100,71*x,100*y,window);

        for(int i=0;i<4;i++)
            trans[i].position =sf::Vector2f( px + i * sx/4.0,py);
    }
    void setValue(int v){
        value = v;
        for(int i=0;i<std::to_string(v).length();i++)
            trans[3-i].setTexture(tex[int (floor (v/(pow(10,i)))) % 10],sx/4.0,sy);
    }
    void draw(){
        for (int i=0;i<std::to_string(value).length();i++)
            trans[3-i].draw(window,w);
    }
};



int main(){
    Text text(0.5,0,0.5);

    Texture sqr("squere.png",124,124,window);

    Transform background;
    background.setTexture(sqr,1,1);
    background.sprite.setColor(sf::Color(100,100,150));

    Texture defeatText("defeat.jpg",300,168,window);
    Transform defeat;
    defeat.setTexture( defeatText,1,1);

    //if we want to resamble the shape set the res to only bigger value and then use the same axis in setTexture
    MapTile map[50];
    for (int x=0;x<m;x++)
        for (int y=0;y<n;y++) {
            MapTile g;
            g.setTexture(sqr, 1/float(m) * 0.8, 1/float(n)/2);
            g.position = sf::Vector2f(1/float(m) * 0.8 * x+0.1, 0.5 + 0.5/float(n)*y);
            g.line = y;
            if (int(x+y)%2)        g.sprite.setColor(sf::Color(10, 200, 30));
            else         g.sprite.setColor(sf::Color(200, 100, 100));
            map[y * m +x] = g;
        }

    Texture nut("nut.jpg",823,1000,window);
    Texture pea("peashooter.jpg",894,894,window);
    Texture sun("sunflower.jpg",634,662,window);
    list<Shop> shop;
    Shop s;

    Turret p;
    p.setTexture(pea,0,1/float(n)/2);
    p.shootSpeed = 1000;
    Bullet peabullet;
    peabullet.setTexture(sqr,0.02);
    peabullet.speed = 0.3;
    peabullet.dmg = 1;
    p.bullet = peabullet;
    p.health = 10;
    s.setTexture(pea,0.1);
    s.cost = 100;
    s.plantIndex =0;
    s.plant = p;
    shop.push_back(s);

    p = Turret();
    p.setTexture(nut,0,1/float(n)/2);
    p.health = 100;
    s.setTexture(nut,0.1);
    s.cost = 75;
    s.plantIndex = 1;
    s.position = sf::Vector2f (0.15,0);
    s.plant = p;
    shop.push_back(s);

    p.setTexture(sun,0,1/float(n)/2);
    p.shootSpeed = 3000;
    p.health = 10;
    Bullet sunbullet;
    sunbullet.setTexture(sqr,0.035);
    sunbullet.speed = 0.05;
    sunbullet.sun = 25;
    sunbullet.sprite.setColor(sf::Color(255,255,10));
    p.bullet = sunbullet;
    s.setTexture(sun,0.1);
    s.cost = 50;
    s.plantIndex = 2;
    s.position = sf::Vector2f (0.3,0);
    s.plant = p;
    shop.push_back(s);



    Zombie basic;
    Texture z("zombie.png",1454,2329,window);
    basic.speed = 0.03;
    basic.setTexture(z,0,0.1);
    basic.health = 8;
    basic.attackSpeed = 100;
    zm.exampleZombies[0] = basic;


    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();

        sf::Event event;
        sf::Vector2u d = window.getSize();
         mouse = sf::Vector2f (sf::Mouse::getPosition(window).x / float( d.x),sf::Mouse::getPosition(window).y/ float(d.y));

        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
            if(event.mouseButton.button == sf::Mouse::Left && !lost) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    for (int i=0;i<m*n;i++) {
                        if(money >= s.cost && selected != -1)
                            if (map[i].cross(mouse)) {
                                if (!map[i].taken){
                                    map[i].taken = true;
                                    map[i].turret = s.plant;
                                    map[i].turret .position = map[i].position;
                                    map[i].turret.line = map[i].line;
                                    money -= s.cost;
                                }
                            }
                    }


                    selected = -1;

                    for (Shop sh: shop) {
                        if (sh.cross(mouse))
                            if (money >= sh.cost) {
                                s = sh;
                                selected = sh.plantIndex;
                            }
                    }

                }
            }
        }
        cout << selected << endl;
        if(lost)
        {
            defeat.draw(window,w);
            window.display();
            continue;
        }

        text.setValue(money);

        for (int z=0;z<zm.count;z++)
            for (int x=0;x<m;x++)
            {
                if(map[zm.zombies[z].line * m+x].taken)
                   // MapTile map[50];
                    if ( zm.zombies[z].cross(map[zm.zombies[z].line * m+x].turret)) {
                        zm.zombies[z].onPlant = true;
                        zm.zombies[z].tur = &map[zm.zombies[z].line * m+x].turret;
                    }
            }

        if(selected >= 0) s.position = mouse;
        for (int i=0;i<m*n;i++)  if(map[i].taken) map[i].update(elapsed.asMilliseconds());
        zm.update(elapsed.asMilliseconds());

        window.clear();
        background.draw(window,w);
        text.draw();
        for (Transform t : map)  t.draw(window, w);
        for (MapTile t : map)  t.draw(window, w);


        for (Transform t : shop)t.draw(window,w);

        zm.draw();
        if (selected >=0) s.draw(window,w);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return 0;
}



