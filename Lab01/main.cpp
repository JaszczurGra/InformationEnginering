#include <iostream>
#include <vector>
#include<algorithm>
#include <string>
#include <math.h>

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
        cout << "Name: "<<name_ << endl <<"Surname: "<< surname_ << endl << "Index: "<<index_<<endl << "Grades: ";
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
        cout << a << " + " << b << "i" << endl;
    }
private:
        float a,b;
};
int main(){
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
    cout <<"Passed: " <<( s.passed() ? "Yes" : "No" )<<endl;

    cout << endl;

    Complex a(1.0, -2.0); // creates 1-2i
    Complex b(3.14); // creates 3.14

    b.set_im(-5);

    Complex c = a.add(b);

    c.print();
    return 0;
}

