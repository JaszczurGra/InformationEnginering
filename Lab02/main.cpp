#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;
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
int main(){
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
