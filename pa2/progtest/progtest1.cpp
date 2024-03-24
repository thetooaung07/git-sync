#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
#endif /* __PROGTEST__ */

using namespace std;

struct LandLot {
    LandLot(const std::string &, const std::string &, const std::string &, unsigned int, std::string);
    LandLot(const string &,  const string &);
    LandLot(const string &, unsigned int);
    std::string city;
    std::string address;
    std::string region;
    unsigned int id;
    std::string owner;
};

LandLot::LandLot(const std::string &, const std::string &, const std::string &,
                 unsigned int, std::string) {}


class CIterator
{
  public:
    CIterator();
    ~CIterator();

    bool                     atEnd                         () const;
    void                     next                          ();
    std::string              city                          () const;
    std::string              addr                          () const;
    std::string              region                        () const;
    unsigned                 id                            () const;
    std::string              owner                         () const;
  private:
    // todo


};

CIterator::CIterator() {}
CIterator::~CIterator(){}


bool         CIterator::atEnd () const{ return true;}
void         CIterator::next  ()      {};
std::string  CIterator::city  () const{ return "";};
std::string  CIterator::addr  () const{ return "";};
std::string  CIterator::region() const{ return "";};
unsigned     CIterator::id    () const{ return 1;};
std::string  CIterator::owner () const{ return "";};

class CLandRegister
{
  public:
    bool                     add                           ( const std::string    & city,
                                                             const std::string    & addr,
                                                             const std::string    & region,
                                                             unsigned int           id );

    bool                     del                           ( const std::string    & city,
                                                             const std::string    & addr );

    bool                     del                           ( const std::string    & region,
                                                             unsigned int           id );

    bool                     getOwner                      ( const std::string    & city,
                                                             const std::string    & addr,
                                                             std::string          & owner ) const;

    bool                     getOwner                      ( const std::string    & region,
                                                             unsigned int           id,
                                                             std::string          & owner ) const;

    bool                     newOwner                      ( const std::string    & city,
                                                             const std::string    & addr,
                                                             const std::string    & owner );

    bool                     newOwner                      ( const std::string    & region,
                                                             unsigned int           id,
                                                             const std::string    & owner );

    size_t                   count                         ( const std::string    & owner ) const;

    CIterator                listByAddr                    () const;

    CIterator                listByOwner                   ( const std::string    & owner ) const;
  private:
   vector<LandLot *> landlots;
   vector<LandLot *> sort_by_city;
   vector<LandLot *> sort_by_region;

   bool find_by_city(const LandLot, std::vector<LandLot * >::const_iterator &city_idx)const;
   bool find_by_region(const LandLot, std::vector<LandLot * >::const_iterator &region_idx)const;
};


bool compare_city(const LandLot *a, const LandLot &b ) {
    return (a->city < b.city);
}

bool compare_region(const LandLot *a, const LandLot &b) {
    return (a->region < b.region);
}

bool CLandRegister::find_by_city(const LandLot lot,
                                 vector<LandLot *>::const_iterator &city_idx) const {

    city_idx = lower_bound(sort_by_city.begin(), sort_by_city.end(), lot, compare_city);

    cout<< "Hello" << endl;
    return (city_idx != sort_by_city.end() && (*city_idx)->city == lot.city && (*city_idx)->address == lot.address);
}



bool CLandRegister::find_by_region(const LandLot lot,
                                   std::vector<LandLot *>::const_iterator &region_idx) const {
    region_idx = lower_bound(sort_by_region.begin(), sort_by_region.end(), lot, compare_region);
    return (region_idx != sort_by_region.end() && (*region_idx)->region == lot.region && (*region_idx)->id == lot.id);
}


bool CLandRegister::add(const std::string &city, const std::string &addr,
                        const std::string &region, unsigned int id) {

    LandLot *newLandlot = new LandLot(city, addr, region, id, "");

    vector<LandLot *>::const_iterator city_idx, region_idx;


    if(find_by_city(*newLandlot, city_idx) || find_by_region(*newLandlot, region_idx )) {
        delete newLandlot;
        return false;
    }





    return true;

}
bool CLandRegister::del(const std::string &city, const std::string &addr) {}
bool CLandRegister::del(const std::string &region, unsigned int id) {}
bool CLandRegister::getOwner(const std::string &region, unsigned int id,
                             std::string &owner) const {}
bool CLandRegister::getOwner(const std::string &city, const std::string &addr,
                             std::string &owner) const {}
bool CLandRegister::newOwner(const std::string &region, unsigned int id,
                             const std::string &owner) {
    vector<LandLot *>::const_iterator region_idx;

    LandLot lot("", "" , region, id, owner);

   if(!find_by_region(lot, region_idx)){
        return false;
   };

    (*region_idx)->owner = owner;

    return true;

}
bool CLandRegister::newOwner(const std::string &city, const std::string &addr,
                             const std::string &owner) {

    vector<LandLot *>::const_iterator city_idx;

    LandLot lot(city, addr, "", 0, owner);





    if(!find_by_city(lot, city_idx)){
        return false;
    };

    cout << "Given City " << city << "-" << addr <<  endl;
    cout << "Result City " << (*city_idx)->city << "-" <<(*city_idx)->address <<  (*city_idx)->owner<< endl;

    (*city_idx)->owner = owner;



    return true;
}
size_t CLandRegister::count(const std::string &owner) const {}
CIterator CLandRegister::listByAddr() const {}
CIterator CLandRegister::listByOwner(const std::string &owner) const {}



#ifndef __PROGTEST__
static void test0 ()
{
  CLandRegister x;
  std::string owner;

  assert ( x . add ( "Prague", "Thakurova", "Dejvice", 12345 ) );
  assert ( x . add ( "Prague", "Evropska", "Vokovice", 12345 ) );
  assert ( x . add ( "Prague", "Technicka", "Dejvice", 9873 ) );
  assert ( x . add ( "Plzen", "Evropska", "Plzen mesto", 78901 ) );
  assert ( x . add ( "Liberec", "Evropska", "Librec", 4552 ) );


  CIterator i0 = x . listByAddr ();
  assert ( ! i0 . atEnd ()
           && i0 . city () == "Liberec"
           && i0 . addr () == "Evropska"
           && i0 . region () == "Librec"
           && i0 . id () == 4552
           && i0 . owner () == "" );
  i0 . next ();
  assert ( ! i0 . atEnd ()
           && i0 . city () == "Plzen"
           && i0 . addr () == "Evropska"
           && i0 . region () == "Plzen mesto"
           && i0 . id () == 78901
           && i0 . owner () == "" );
  i0 . next ();
  assert ( ! i0 . atEnd ()
           && i0 . city () == "Prague"
           && i0 . addr () == "Evropska"
           && i0 . region () == "Vokovice"
           && i0 . id () == 12345
           && i0 . owner () == "" );
  i0 . next ();
  assert ( ! i0 . atEnd ()
           && i0 . city () == "Prague"
           && i0 . addr () == "Technicka"
           && i0 . region () == "Dejvice"
           && i0 . id () == 9873
           && i0 . owner () == "" );
  i0 . next ();
  assert ( ! i0 . atEnd ()
           && i0 . city () == "Prague"
           && i0 . addr () == "Thakurova"
           && i0 . region () == "Dejvice"
           && i0 . id () == 12345
           && i0 . owner () == "" );
  i0 . next ();
  assert ( i0 . atEnd () );

  assert ( x . count ( "" ) == 5 );
  CIterator i1 = x . listByOwner ( "" );
  assert ( ! i1 . atEnd ()
           && i1 . city () == "Prague"
           && i1 . addr () == "Thakurova"
           && i1 . region () == "Dejvice"
           && i1 . id () == 12345
           && i1 . owner () == "" );
  i1 . next ();
  assert ( ! i1 . atEnd ()
           && i1 . city () == "Prague"
           && i1 . addr () == "Evropska"
           && i1 . region () == "Vokovice"
           && i1 . id () == 12345
           && i1 . owner () == "" );
  i1 . next ();
  assert ( ! i1 . atEnd ()
           && i1 . city () == "Prague"
           && i1 . addr () == "Technicka"
           && i1 . region () == "Dejvice"
           && i1 . id () == 9873
           && i1 . owner () == "" );
  i1 . next ();
  assert ( ! i1 . atEnd ()
           && i1 . city () == "Plzen"
           && i1 . addr () == "Evropska"
           && i1 . region () == "Plzen mesto"
           && i1 . id () == 78901
           && i1 . owner () == "" );
  i1 . next ();
  assert ( ! i1 . atEnd ()
           && i1 . city () == "Liberec"
           && i1 . addr () == "Evropska"
           && i1 . region () == "Librec"
           && i1 . id () == 4552
           && i1 . owner () == "" );
  i1 . next ();
  assert ( i1 . atEnd () );

  assert ( x . count ( "CVUT" ) == 0 );
  CIterator i2 = x . listByOwner ( "CVUT" );
  assert ( i2 . atEnd () );

  assert ( x . newOwner ( "Prague", "Thakurova", "CVUT" ) );
  assert ( x . newOwner ( "Dejvice", 9873, "CVUT" ) );
  assert ( x . newOwner ( "Plzen", "Evropska", "Anton Hrabis" ) );
  assert ( x . newOwner ( "Librec", 4552, "Cvut" ) );
  assert ( x . getOwner ( "Prague", "Thakurova", owner ) && owner == "CVUT" );
  assert ( x . getOwner ( "Dejvice", 12345, owner ) && owner == "CVUT" );
  assert ( x . getOwner ( "Prague", "Evropska", owner ) && owner == "" );
  assert ( x . getOwner ( "Vokovice", 12345, owner ) && owner == "" );
  assert ( x . getOwner ( "Prague", "Technicka", owner ) && owner == "CVUT" );
  assert ( x . getOwner ( "Dejvice", 9873, owner ) && owner == "CVUT" );
  assert ( x . getOwner ( "Plzen", "Evropska", owner ) && owner == "Anton Hrabis" );
  assert ( x . getOwner ( "Plzen mesto", 78901, owner ) && owner == "Anton Hrabis" );
  assert ( x . getOwner ( "Liberec", "Evropska", owner ) && owner == "Cvut" );
  assert ( x . getOwner ( "Librec", 4552, owner ) && owner == "Cvut" );
  CIterator i3 = x . listByAddr ();
  assert ( ! i3 . atEnd ()
           && i3 . city () == "Liberec"
           && i3 . addr () == "Evropska"
           && i3 . region () == "Librec"
           && i3 . id () == 4552
           && i3 . owner () == "Cvut" );
  i3 . next ();
  assert ( ! i3 . atEnd ()
           && i3 . city () == "Plzen"
           && i3 . addr () == "Evropska"
           && i3 . region () == "Plzen mesto"
           && i3 . id () == 78901
           && i3 . owner () == "Anton Hrabis" );
  i3 . next ();
  assert ( ! i3 . atEnd ()
           && i3 . city () == "Prague"
           && i3 . addr () == "Evropska"
           && i3 . region () == "Vokovice"
           && i3 . id () == 12345
           && i3 . owner () == "" );
  i3 . next ();
  assert ( ! i3 . atEnd ()
           && i3 . city () == "Prague"
           && i3 . addr () == "Technicka"
           && i3 . region () == "Dejvice"
           && i3 . id () == 9873
           && i3 . owner () == "CVUT" );
  i3 . next ();
  assert ( ! i3 . atEnd ()
           && i3 . city () == "Prague"
           && i3 . addr () == "Thakurova"
           && i3 . region () == "Dejvice"
           && i3 . id () == 12345
           && i3 . owner () == "CVUT" );
  i3 . next ();
  assert ( i3 . atEnd () );

  assert ( x . count ( "cvut" ) == 3 );
  CIterator i4 = x . listByOwner ( "cVuT" );
  assert ( ! i4 . atEnd ()
           && i4 . city () == "Prague"
           && i4 . addr () == "Thakurova"
           && i4 . region () == "Dejvice"
           && i4 . id () == 12345
           && i4 . owner () == "CVUT" );
  i4 . next ();
  assert ( ! i4 . atEnd ()
           && i4 . city () == "Prague"
           && i4 . addr () == "Technicka"
           && i4 . region () == "Dejvice"
           && i4 . id () == 9873
           && i4 . owner () == "CVUT" );
  i4 . next ();
  assert ( ! i4 . atEnd ()
           && i4 . city () == "Liberec"
           && i4 . addr () == "Evropska"
           && i4 . region () == "Librec"
           && i4 . id () == 4552
           && i4 . owner () == "Cvut" );
  i4 . next ();
  assert ( i4 . atEnd () );

  assert ( x . newOwner ( "Plzen mesto", 78901, "CVut" ) );
  assert ( x . count ( "CVUT" ) == 4 );
  CIterator i5 = x . listByOwner ( "CVUT" );
  assert ( ! i5 . atEnd ()
           && i5 . city () == "Prague"
           && i5 . addr () == "Thakurova"
           && i5 . region () == "Dejvice"
           && i5 . id () == 12345
           && i5 . owner () == "CVUT" );
  i5 . next ();
  assert ( ! i5 . atEnd ()
           && i5 . city () == "Prague"
           && i5 . addr () == "Technicka"
           && i5 . region () == "Dejvice"
           && i5 . id () == 9873
           && i5 . owner () == "CVUT" );
  i5 . next ();
  assert ( ! i5 . atEnd ()
           && i5 . city () == "Liberec"
           && i5 . addr () == "Evropska"
           && i5 . region () == "Librec"
           && i5 . id () == 4552
           && i5 . owner () == "Cvut" );
  i5 . next ();
  assert ( ! i5 . atEnd ()
           && i5 . city () == "Plzen"
           && i5 . addr () == "Evropska"
           && i5 . region () == "Plzen mesto"
           && i5 . id () == 78901
           && i5 . owner () == "CVut" );
  i5 . next ();
  assert ( i5 . atEnd () );

  assert ( x . del ( "Liberec", "Evropska" ) );
  assert ( x . del ( "Plzen mesto", 78901 ) );
  assert ( x . count ( "cvut" ) == 2 );
  CIterator i6 = x . listByOwner ( "cVuT" );
  assert ( ! i6 . atEnd ()
           && i6 . city () == "Prague"
           && i6 . addr () == "Thakurova"
           && i6 . region () == "Dejvice"
           && i6 . id () == 12345
           && i6 . owner () == "CVUT" );
  i6 . next ();
  assert ( ! i6 . atEnd ()
           && i6 . city () == "Prague"
           && i6 . addr () == "Technicka"
           && i6 . region () == "Dejvice"
           && i6 . id () == 9873
           && i6 . owner () == "CVUT" );
  i6 . next ();
  assert ( i6 . atEnd () );

  assert ( x . add ( "Liberec", "Evropska", "Librec", 4552 ) );
}

static void test1 ()
{
  CLandRegister x;
  std::string owner;

  assert ( x . add ( "Prague", "Thakurova", "Dejvice", 12345 ) );
  assert ( x . add ( "Prague", "Evropska", "Vokovice", 12345 ) );
  assert ( x . add ( "Prague", "Technicka", "Dejvice", 9873 ) );
  assert ( ! x . add ( "Prague", "Technicka", "Hradcany", 7344 ) );
  assert ( ! x . add ( "Brno", "Bozetechova", "Dejvice", 9873 ) );
  assert ( !x . getOwner ( "Prague", "THAKUROVA", owner ) );
  assert ( !x . getOwner ( "Hradcany", 7343, owner ) );
  CIterator i0 = x . listByAddr ();
  assert ( ! i0 . atEnd ()
           && i0 . city () == "Prague"
           && i0 . addr () == "Evropska"
           && i0 . region () == "Vokovice"
           && i0 . id () == 12345
           && i0 . owner () == "" );
  i0 . next ();
  assert ( ! i0 . atEnd ()
           && i0 . city () == "Prague"
           && i0 . addr () == "Technicka"
           && i0 . region () == "Dejvice"
           && i0 . id () == 9873
           && i0 . owner () == "" );
  i0 . next ();
  assert ( ! i0 . atEnd ()
           && i0 . city () == "Prague"
           && i0 . addr () == "Thakurova"
           && i0 . region () == "Dejvice"
           && i0 . id () == 12345
           && i0 . owner () == "" );
  i0 . next ();
  assert ( i0 . atEnd () );

  assert ( x . newOwner ( "Prague", "Thakurova", "CVUT" ) );
  assert ( ! x . newOwner ( "Prague", "technicka", "CVUT" ) );
  assert ( ! x . newOwner ( "prague", "Technicka", "CVUT" ) );
  assert ( ! x . newOwner ( "dejvice", 9873, "CVUT" ) );
  assert ( ! x . newOwner ( "Dejvice", 9973, "CVUT" ) );
  assert ( ! x . newOwner ( "Dejvice", 12345, "CVUT" ) );
  assert ( x . count ( "CVUT" ) == 1 );
  CIterator i1 = x . listByOwner ( "CVUT" );
  assert ( ! i1 . atEnd ()
           && i1 . city () == "Prague"
           && i1 . addr () == "Thakurova"
           && i1 . region () == "Dejvice"
           && i1 . id () == 12345
           && i1 . owner () == "CVUT" );
  i1 . next ();
  assert ( i1 . atEnd () );

  assert ( ! x . del ( "Brno", "Technicka" ) );
  assert ( ! x . del ( "Karlin", 9873 ) );
  assert ( x . del ( "Prague", "Technicka" ) );
  assert ( ! x . del ( "Prague", "Technicka" ) );
  assert ( ! x . del ( "Dejvice", 9873 ) );
}

int main ( void )
{
//  test0 ();
//  test1 ();

    CLandRegister x;
    std::string owner;

    assert ( x . add ( "Prague", "Thakurova", "Dejvice", 12345 ) );
    assert ( x . add ( "Prague", "Evropska", "Vokovice", 12345 ) );
    assert ( x . add ( "Prague", "Technicka", "Dejvice", 9873 ) );
    assert ( x . add ( "Plzen", "Evropska", "Plzen mesto", 78901 ) );
    assert ( x . add ( "Liberec", "Evropska", "Librec", 4552 ) );

    assert ( x . newOwner ( "Prague", "Thakurova", "CVUT" ) );
    assert ( x . newOwner ( "Dejvice", 9873, "CVUT" ) );
    assert ( x . newOwner ( "Plzen", "Evropska", "Anton Hrabis" ) );
    assert ( x . newOwner ( "Librec", 4552, "Cvut" ) );

    assert ( x . getOwner ( "Prague", "Thakurova", owner ) && owner == "CVUT" );
    assert ( x . getOwner ( "Dejvice", 12345, owner ) && owner == "CVUT" );
    assert ( x . getOwner ( "Prague", "Evropska", owner ) && owner == "" );
    assert ( x . getOwner ( "Vokovice", 12345, owner ) && owner == "" );
    assert ( x . getOwner ( "Prague", "Technicka", owner ) && owner == "CVUT" );
    assert ( x . getOwner ( "Dejvice", 9873, owner ) && owner == "CVUT" );
    assert ( x . getOwner ( "Plzen", "Evropska", owner ) && owner == "Anton Hrabis" );
    assert ( x . getOwner ( "Plzen mesto", 78901, owner ) && owner == "Anton Hrabis" );
    assert ( x . getOwner ( "Liberec", "Evropska", owner ) && owner == "Cvut" );
    assert ( x . getOwner ( "Librec", 4552, owner ) && owner == "Cvut" );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */