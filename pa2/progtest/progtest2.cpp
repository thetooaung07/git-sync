#ifndef _PROGTEST_
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cstdint>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include <compare>
#include <stdexcept>
#endif /* _PROGTEST_ */


using namespace std;

class CBigInt
{
public:
    // default constructor
    // copying/assignment/destruction


//    eg/ 1234

    CBigInt() : m_isNegative(false) {}
    CBigInt(const int num) {
        m_isNegative = num < 0;
        int tempNum = abs(num);
        while (tempNum  > 0) {
            m_digits.push_back(tempNum % 10);
            tempNum /= 10;
        }

        std::reverse(m_digits.begin(), m_digits.end());

//        for (size_t i = 0; i < m_digits.size(); ++i) {
//            cout << m_digits.at(i) << "-";
//        }
    }
    CBigInt(const string & str){}

    CBigInt(const char * str) {
        string s(str);

    }

    CBigInt(const CBigInt& other){}
    CBigInt& operator=(const CBigInt& other) {
        if (this != &other) { // Check for self-assignment
            // Copy the digits from the other object
            m_digits = other.m_digits;
            m_isNegative = other.m_isNegative;
        }
        return *this;
    }
    ~CBigInt(){}




    // operator +, any combination {CBigInt/int/string} + {CBigInt/int/string}

//124566 + 20


    CBigInt operator + (const CBigInt& other) const {



        for (size_t i = 0; i < m_digits.size(); ++i) {
            cout << m_digits.at(i) << "-";
        }
        cout << endl;
        for (size_t i = 0; i < other.m_digits.size(); ++i) {
            cout << other.m_digits.at(i) << "-";
        }
        cout << endl;



        CBigInt result;
        int carry = 0;
        int maxLength = max(m_digits.size(), other.m_digits.size());

        for (int i = maxLength - 1; i >= 0; --i) {

            cout << "At Index " << i << endl;
            cout << "Loop exec " << m_digits[i] << " + " << other.m_digits[i] << " = " << carry << "-" << endl;


            int sum = carry;
            if(i <= m_digits.size()) sum+=m_digits[i];
            if(i <= other.m_digits.size()) sum+=other.m_digits[i];
            carry = sum / 10;

            result.m_digits.push_back(sum % 10);
        }


        reverse(result.m_digits.begin(), result.m_digits.end());
//
//        // Adjust the sign of the result based on the signs of the operands
//        if (m_isNegative && other.m_isNegative)
//            result.m_isNegative = true;
//        else if (m_isNegative && !other.m_isNegative)
//            result.m_isNegative = true;  // Depends on the actual numbers' magnitude
//        else if (!m_isNegative && other.m_isNegative)
//            result.m_isNegative = true;  // Depends on the actual numbers' magnitude

        cout << "Return result"  << endl;
        for (size_t i = 0; i < result.m_digits.size(); ++i) {
            cout << result.m_digits.at(i) << "-";
        }


        return result;

    }

    CBigInt& operator += (int num)  {
        CBigInt temp(num);
        *this  =  *this + temp;
        cout << "+ = =>" << *this << "<= end" << endl;
        return *this;
    }




    // operator *, any combination {CBigInt/int/string} * {CBigInt/int/string}
    // operator +=, any of {CBigInt/int/string}
    // operator *=, any of {CBigInt/int/string}
    // comparison operators, any combination {CBigInt/int/string} {<,<=,>,>=,==,!=} {CBigInt/int/string}
    // output operator <<
    // input operator >>

    friend ostream& operator<<(std::ostream& os, const CBigInt& bigint) {
        if (bigint.m_isNegative)
            os << "-";

        for (int i = bigint.m_digits.size() - 1; i >= 0; --i) {
            os << bigint.m_digits[i];
        }

        return os;
    }
private:

    vector<int> m_digits;
    bool m_isNegative;

    // todo
};

#ifndef _PROGTEST_
static bool equal ( const CBigInt & x, const char val [] )
{
    std::ostringstream oss;
    oss << x;
    return oss . str () == val;
}

static bool equalHex ( const CBigInt & x, const char val [] )
{
    return true; // hex output is needed for bonus tests only
    // std::ostringstream oss;
    // oss << std::hex << x;
    // return oss . str () == val;
}
int main ()
{
    CBigInt a, b;
    std::istringstream is;
    a = 124566;
    a += 20;
    assert ( equal ( a, "30" ) );


    // remove later
    b = a + "400";
    assert ( equal ( b, "410" ) );
    // remove later

//
//    a *= 5;
//    assert ( equal ( a, "150" ) );
//
//
//
//    b = a + 3;
//    assert ( equal ( b, "153" ) );
//
//
//    b = a * 7;
//    assert ( equal ( b, "1050" ) );
//    assert ( equal ( a, "150" ) );
//    assert ( equalHex ( a, "96" ) );
//
//    a = 10;
//    a += -20;
//    assert ( equal ( a, "-10" ) );
//    a *= 5;
//    assert ( equal ( a, "-50" ) );
//    b = a + 73;
//    assert ( equal ( b, "23" ) );
//    b = a * -7;
//    assert ( equal ( b, "350" ) );
//    assert ( equal ( a, "-50" ) );
//    assert ( equalHex ( a, "-32" ) );
//
//    a = "12345678901234567890";
//    a += "-99999999999999999999";
//    assert ( equal ( a, "-87654321098765432109" ) );
//    a *= "54321987654321987654";
//    assert ( equal ( a, "-4761556948575111126880627366067073182286" ) );
//    a *= 0;
//    assert ( equal ( a, "0" ) );
//    a = 10;
//    b = a + "400";
//    assert ( equal ( b, "410" ) );
//    b = a * "15";
//    assert ( equal ( b, "150" ) );
//    assert ( equal ( a, "10" ) );
//    assert ( equalHex ( a, "a" ) );
//
//    is . clear ();
//    is . str ( " 1234" );
//    assert ( is >> b );
//    assert ( equal ( b, "1234" ) );
//    is . clear ();
//    is . str ( " 12 34" );
//    assert ( is >> b );
//    assert ( equal ( b, "12" ) );
//    is . clear ();
//    is . str ( "999z" );
//    assert ( is >> b );
//    assert ( equal ( b, "999" ) );
//    is . clear ();
//    is . str ( "abcd" );
//    assert ( ! ( is >> b ) );
//    is . clear ();
//    is . str ( "- 758" );
//    assert ( ! ( is >> b ) );
//    a = 42;
//    try
//    {
//        a = "-xyz";
//        assert ( "missing an exception" == nullptr );
//    }
//    catch ( const std::invalid_argument & e )
//    {
//        assert ( equal ( a, "42" ) );
//    }
//
//    a = "73786976294838206464";
//    assert ( equal ( a, "73786976294838206464" ) );
//    assert ( equalHex ( a, "40000000000000000" ) );
//    assert ( a < "1361129467683753853853498429727072845824" );
//    assert ( a <= "1361129467683753853853498429727072845824" );
//    assert ( ! ( a > "1361129467683753853853498429727072845824" ) );
//    assert ( ! ( a >= "1361129467683753853853498429727072845824" ) );
//    assert ( ! ( a == "1361129467683753853853498429727072845824" ) );
//    assert ( a != "1361129467683753853853498429727072845824" );
//    assert ( ! ( a < "73786976294838206464" ) );
//    assert ( a <= "73786976294838206464" );
//    assert ( ! ( a > "73786976294838206464" ) );
//    assert ( a >= "73786976294838206464" );
//    assert ( a == "73786976294838206464" );
//    assert ( ! ( a != "73786976294838206464" ) );
//    assert ( a < "73786976294838206465" );
//    assert ( a <= "73786976294838206465" );
//    assert ( ! ( a > "73786976294838206465" ) );
//    assert ( ! ( a >= "73786976294838206465" ) );
//    assert ( ! ( a == "73786976294838206465" ) );
//    assert ( a != "73786976294838206465" );
//    a = "2147483648";
//    assert ( ! ( a < -2147483648 ) );
//    assert ( ! ( a <= -2147483648 ) );
//    assert ( a > -2147483648 );
//    assert ( a >= -2147483648 );
//    assert ( ! ( a == -2147483648 ) );
//    assert ( a != -2147483648 );
//    a = "-12345678";
//    assert ( ! ( a < -87654321 ) );
//    assert ( ! ( a <= -87654321 ) );
//    assert ( a > -87654321 );
//    assert ( a >= -87654321 );
//    assert ( ! ( a == -87654321 ) );
//    assert ( a != -87654321 );

    return EXIT_SUCCESS;
}
#endif /* _PROGTEST_ */