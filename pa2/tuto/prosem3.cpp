//
// Created by Thet Oo Aung on 18/03/2024.
//

// Operator Overloading

#include "iostream"
#include "cstring"
#include "utility"

class CStr { ;
public:
    CStr ( const char  * source = ""){
        size = strlen(source);
        data = new char[size + 1];
        strncpy(data, source, size + 1);

    }


    CStr ( int number ){
        char buffer [15];
        snprintf(buffer, 15, "%d", number);
        set(buffer, strlen(buffer));
    };


    CStr ( double number  ){
        char buffer [15];
        snprintf(buffer, 15, "%e", number);
        set(buffer, strlen(buffer));
    };

    CStr & operator =  (const CStr & other) {
        if(this  == & other) return *this;
        this->~CStr();
        set(other.data,other.size);
    }

    CStr(CStr && other ){
        size = other.size;
        data = other.data;

        other.size = 0;
        other.data = nullptr;
    }

    CStr & operator = ( CStr && other) {
        using std::swap;
        if(this  == & other) return *this;
        this->~CStr();
        set(other.data,other.size);
    }



    ~CStr(){
        delete[] data;
    }

    friend std::ostream & operator << (std::ostream & os , const CStr & str) {
        return os << str.data;
    }





private:

   void set (char * str , size_t size) {
        size = strlen(str);
        data = new char[size + 1];
        strncpy(data, str, size + 1);
    }


    char * data;
    size_t size;
};



int  main() {
    CStr a(10);
    CStr b;


    std::cout << a << std::endl;
    std::cout << b  << std::endl;



    b = std::move(a) ;

    std::cout << b  << std::endl;


    return 0;
}