#include "iostream"
#include "iomanip"

using namespace  std;

class OverloadingTest {
public:
    OverloadingTest();

    OverloadingTest operator + (OverloadingTest t1) {
        OverloadingTest t;
        int a , b ;
        return t;
    }

    // overloading <<
    friend ostream & operator  << (ostream &os, OverloadingTest &ot) {
        return os << "Time is: " << "hello world" ;
    }

    // overloading ==
    friend bool operator == (OverloadingTest &t1, OverloadingTest &t2) {
        return false;
    }

private:


};


int main  () {
    OverloadingTest t1, t2, t3;
    t3 = t1 + t2;
    return 0;
}