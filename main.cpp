


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

class Student {
public:
    void set_index(int index) { // setter
        if (index > 9999 && index < 1000000)
            index_ = index;
    }
    void set_name(string name, string surname) { // setter
        name_ = name;
        surname_ = surname;
    }
    void dispay_summary(){
        cout << name_ << endl << surname_ << endl << index_<<endl << "grades: ";
        for (int i =0;i<grades.size();i++)
            cout << grades[i] << " ";
        cout << endl;
    }
    void add_grade(float g){
        if (g<=5 && g>=2)
            grades.push_back((float)g);
        else cout << "Wrong grade";
    }
    float mean_grade(){
        float sum = 0;
        for (int i =0;i<grades.capacity();i++)
            sum +=  grades[i];
        return sum / (float)grades.capacity();
    }
    bool passed(){
        bool two = false;
        for (int i =0;i<grades.capacity();i++)
            if (grades[i] == 2)
                if(two) return false;
                else two = true;
        return true;
    }
//private:
    string name_;
    string surname_;
    int index_;
    vector<float> grades;
};
class Complex{
public:
    Complex(float real=0,float imaginary=0){
        a = real;
        b = imaginary;
    }
    void set_re(float real){
        a = real;
    }
    void set_im(float imaginary){
        b = imaginary;
    }
    float read_re(){
        return a;
    }
    float read_im(){
        return b;
    }
    Complex add(Complex adder)
    {
        return Complex(a + adder.read_re(),b + adder.read_im());
    }
    void print(){
        cout << a << " + " << b << "i";
    }
private:
        float a,b;
};
void FinalAssigment1(){
    Student s = Student();
    s.set_index(123721);
    s.set_name("Andrzej","Kowalski");
    s.add_grade(4);
    s.add_grade(2);
    s.add_grade(3);
    s.add_grade(4);
    s.add_grade(2);
    s.dispay_summary();
    cout <<"Mean grade: " << s.mean_grade()<<endl;
    cout <<"Passed: " << s.passed()<<endl;

    Complex a(1.0, -2.0); // creates 1-2i
    Complex b(3.14); // creates 3.14

    b.set_im(-5);

    Complex c = a.add(b);

    c.print();
}

//bonus not done
class Time{
public:
public:
    float seconds;
    string general;
public:
    Time(float seconds=0)
    {
        setSeconds(seconds);
    }
    Time operator+ (Time t) {
        Time o = Time(this->seconds + t.seconds);
        return o;
    }
    Time operator- (Time t) {
        Time o = Time(this->seconds - t.seconds);
        return o;
    }
    Time operator* (float s) {
        return Time(this->seconds * s);
    }
    friend ostream &operator<<(ostream &str, Time t){
        str << t.general;
        return str;
    }
    friend istream &operator>>(istream &str, Time &t){
        string g;
        str >> g;
        t.setGeneral(g);
        return str;
    }
    operator int(){
        return this->seconds;
    }
    void setSeconds(float s){
        seconds = s;
        general =  to_string ((int)(seconds/3600.0)) + "h:" +to_string ((int)(seconds/60)%60) + "m:" +to_string((int)seconds%60) + "s" ;
    }
    void setGeneral(string s){
        general = s;
        seconds = 0;
        string t;
        int m = 2;
        for (int i=0;i<general.length();i++){
            if (general[i] == 'h' || general[i] =='m'|| general[i] =='s'){
                seconds += pow(60,m) * stoi(t);
                m -= 1;
                t="";
            }
            if (std::isdigit(general[i]))
                t += general[i];
            if(s[i] == 's') break;
        }
    }
    int toSeconds(){
        float second;
        string t;
        int m = 2;
        for (int i=0;i<general.length();i++){
            if (general[i] == 'h' || general[i] =='m'|| general[i] =='s'){
                second += pow(60,m) * stoi(t);
                m -= 1;
                t="";
            }
            if (std::isdigit(general[i]))
                t += general[i];
            if(general[i] == 's') break;
        }
        seconds = second;
        return second;
   }
};
class Item{
public:
    string name;
    float unp;
    char vat;
    int amount;
    float net,gross;
    Item(string name,float unp, char vat, int amount){
        this->name = name;
        this->unp = unp;
        this->vat = vat;
        this->amount = amount;
        float v = 0;
        if (vat == 'A') v = 1.23;
        else if(vat == 'B') v = 1.08;
        this->net = unp * amount;
        this->gross = ceil (net * v * 100)/100.0;
    }
    friend ostream &operator<<(ostream &str, Item it){

        str << it.name<<"\t| " << it.unp <<"  " << it.vat <<"\t| " << it.amount<<"\t| " << it.net <<"\t| "<<it.gross<<endl;
        return str;
    }
};
class Invoice{
public:
    string seller,buyer;
    vector<Item> items;
    Invoice(string seller,string buyer){
        this->seller = seller;
        this->buyer = buyer;
    }
    void add_item(Item i){
        items.push_back(i);
    }
    friend ostream &operator<<(ostream &str, Invoice inv){
        float net = 0,total = 0;
        cout << "------------------VAT invoice--------------------------" << endl;
        cout << "=======================================================" << endl;
        cout << "Seller:\t" << inv.seller << "\tBuyer:" << inv.buyer << endl << endl;
        cout << "\t\t  u.p. VAT\t  amt.\t  net\t  total"<<endl;
        for (int i=0;i<inv.items.size();i++){
            str <<i <<". " <<inv.items[i];
            net += inv.items[i].net;
            total += ceil(inv.items[i].gross*100)/100.0;
        }
        cout << endl << "------------------------------------------ TOTAL ------" << endl;
        cout <<"\t\t\t\t\t" << net << " | " << total<<endl << endl;
        return str;
    }
};
void FinalAssigment2(){
    Time t1(200);
    cout << t1 << endl; // displays 03m:20s
    Time t2;
    cin >> t2; // user enters 10h:12m:01s

    Time t3 = t2 - t1; // 10h:8m:41s
    int t3s = t3; // 36521
    cout << t3s;

    Invoice inv("7770003699", "0123456789");
    inv.add_item(Item("M3 screw", 0.37, 'A', 100));
    inv.add_item(Item("2 mm drill", 2.54, 'B', 2));
    std::cout << inv << std::endl;
}

//na dysk C: zainstalowac https://www.sfml-dev.org/download/sfml/2.5.1/ GCC 7.3.0 MinGW (DW2) - 32-bit lub GCC 7.3.0 MinGW (DW2) - 64-bit zaleznie od systemu
//Idk czm mouse::lelf sie odpala przy klikaniu a
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
void FinalAssigment4(){
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
}

void FinalAssigment5(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Maze");
    int width=100,height=50;
    CustomRectangleShape player (sf::Vector2f(50,50),sf::Vector2f(100,100),sf::Vector2f(1500,1500));
    player.setFillColor(sf::Color(50,150,30));
    player.setBounds(0,0,window.getSize().x,window.getSize().y);

    vector<CustomRectangleShape> map;
    for (int i=0;i<10;i++){
        CustomRectangleShape r(sf::Vector2f(width,height),sf::Vector2f(rand() % (window.getSize().x-width) +width/2.0, rand() % (window.getSize().y-height) + height/2.0),sf::Vector2f(1500,1500));
        r.setFillColor(sf::Color(200,200,200));
        r.setBounds(0,0,window.getSize().x,window.getSize().y);
       map.push_back(r);
    }
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
        sf::Keyboard::Key keys[4]{sf::Keyboard::W,sf::Keyboard::S,sf::Keyboard::A,sf::Keyboard::D};
        for (int i=0;i<4;i++)
        if (sf::Keyboard::isKeyPressed(keys[i]))
            player.moveInDirection(elapsed,keys[i]);

        window.clear(sf::Color::Black);

        for(auto &rec :map) window.draw(rec);
        window.draw(player);
        window.display();
    }
}

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
int main(){
    sf::RenderWindow window(sf::VideoMode(800, 550), "Maze");
    sf::Vector2u w = window.getSize();



   //425x425
   sf::Texture wall = loadTexture("wall.jpg");
   //1134x1134
   sf::Texture grass = loadTexture("grass.png");
   //277x379
   sf::Texture p = loadTexture("player.png");

   Player player (sf::Vector2f(w.x/2.0,w.y/2.0),350);
   player.setBounds(0,0,window.getSize().x,window.getSize().y);
   player.setTexture(window.getSize(),p,277,12);
   player.height *= 379/277.0;
   player.spriteTrans.y *= 379/277.0;




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
        sf::Keyboard::Key keys[4]{sf::Keyboard::W,sf::Keyboard::S,sf::Keyboard::A,sf::Keyboard::D};
        for (int i=0;i<4;i++)
        if (sf::Keyboard::isKeyPressed(keys[i]))
            player.moveInDirection(elapsed,keys[i],map);

        window.clear(sf::Color::Black);
        for(auto s :bg) window.draw(s);
        for(auto s :map) window.draw(s.getSprite());
        window.draw(player.getSprite());
        window.display();
    }
    return 0;
}

