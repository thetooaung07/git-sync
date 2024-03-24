//
// Created by Thet Oo Aung on 14/03/2024.
//
#include "cassert"
#include "sstream"
#include "exception"

//using lli = long long int;


class fraction {
public:
    fraction(long num = 0 , long den =1);


    fraction  operator +  (const fraction & rhs) const;
    bool operator == (int oth) const;


    fraction  operator -  (const fraction & rhs) const;
    fraction  operator -  () const;
    fraction  operator *  (const fraction & rhs) const;
    fraction  operator /  (const fraction & rhs) const;
private:
     long m_num, m_den;
};



fraction::fraction(long num, long den) : m_num(num) , m_den(den) {

    if(m_den == 0) throw std::invalid_argument("FUH bad den");
 //   simplify();
}


bool fraction::operator ==  (const fraction & oth) const  {
    return  m_num/ m_den == oth.m_num && m_num % m_den == 0;
}

fraction fraction::operator + (const fraction &rhs) const  {
    return fraction{
            m_num * rhs.m_den + rhs.m_num *m_den, m_den * rhs.m_den
    };
}



int main(void) {

    fraction f1;
    fraction f2(5);
    fraction f3 = f2 + f1;

    assert(f3 == 5);
    assert(f3 == f3);
    assert(f3 == f3);

    //    assert(f1  f2 == f2);
//    assert(f1 + f2 == f2);


    return 0;
}