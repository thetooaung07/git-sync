//
// Created by Thet Oo Aung on 12/03/2024.
//

#include "iostream"
#include "cassert"
using namespace std;

class CCar {

public:
    CCar(const string & rz, const string & owner, int age){
     m_Rz = rz;
     m_Owner = owner;
     m_Age = age;
    }




private:
    string m_Rz;
    string m_Owner;
    int    m_Age;
};

class CGarage {
public:
    CGarage        ( void );
    bool addCar    ( const CCar & c  );
    bool delCar    ( const string & rz );
    void sortCars  ( void );
    void printCars ( void ) const;

private:
    static const size_t CAR_MAX = 100;

    CCar    db[CAR_MAX];
    size_t  dbLen;

};


CGarage::CGarage(void) {
    dbLen = 0;
}


bool  CGarage::addCar    ( CCar &car ) {
    if(dbLen >= CAR_MAX) {return false;}
    for (size_t i = 0; i < dbLen ; ++i) {
        if(db[i].m_Rz != rz){
            return false;
        }
    }
    db[dbLen++] = car;
    return false;

}


bool CGarage::delCar    ( const string & rz ) {
    for (size_t i = 0; i < dbLen ; ++i) {
        if(db[i].m_Rz == rz ) {
            db[i] = db[--dbLen];
            return true;
        }
    }

    return false;

}
void CGarage::sortCars  ( void ) {
    for (size_t i = 0; i < dbLen; ++i) {
        int minIndex = i;

        for (int j = i+ 1; j < dbLen ; ++j) {
            if(db[j].m_Age  < db[minIndex].m_Age)
                minIndex = j;

            TCar temp = db[minIndex];
            db[minIndex] = db[i];
            db[i]  = temp;
        }

    }
}
void CGarage::printCars ( void ) const {
    cout << "-------------------------------" <<  endl;

    for (int i = 0; i < dbLen; ++i) {
            cout << db[i].m_Rz << " " << db[i].m_Owner << " " << db[i].m_Age << endl;
    }
}



int main( void ) {
    CGarage g;

    assert      (g.addCar ( "DEF-123-123", "James", 1));
    assert      (g.addCar ( "ABC-123-123", "John Smith", 3));
    assert      (g.addCar ( "GHJ-123-123", "Smith Smith", 8));
    g.printCars           ();
    g.sortCars            ();
    g.printCars           ();
    assert      (g.delCar ("GHJ-123-123"));
    g.printCars           ();

    return 0;
}