#include <iostream>
#include <string>

using namespace std;

class Base {
public: 
    Base(int v): value_(v) {}
    virtual string ToString() const { return "base"; }
protected:
    int value_;
};

class Number: public Base {
public: 
    Number(int v): Base(v) {}
    string ToString() const { return "number"; }
};

class Op: public Base {
public: 
    Op(int v, const Base & b1, const Base & b2): Base(v), base1_(b1), base2_(b2) {
        cout << b1.ToString() << endl;
        cout << base1_.ToString() << endl;
        cout << b2.ToString() << endl;
        cout << base2_.ToString() << endl;
    }
    string ToString() const { return "op"; }
private:
   const Base & base1_, & base2_;
};

int main() {
    Base base(1);
    //cout << base.ToString() << endl;
    Number number(2);
    //cout << number.ToString() << endl;
    Op op(3, number, number);

    Base & base2 = number;
    //cout << base2.ToString() << endl;
}
