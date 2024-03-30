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


struct SLandlot {

    // Constructors
    SLandlot(const string &city, const string &address);

    SLandlot(const string &region, const unsigned int id);

    SLandlot(const string &city, const string &address, const string &region,
             unsigned int id, const string &owner = "");

    // Member functions
    bool changeOwnerName(const string &owner);

    bool increaseSID();

    static unsigned int index;
    string m_city, m_addr, m_region, m_owner, m_owner_lower;
    unsigned int m_id, s_id;
};

// Constructor definitions

SLandlot::SLandlot(const string &city, const string &address) : m_city(city), m_addr(address) {}

SLandlot::SLandlot(const string &region, const unsigned int id) : m_region(region), m_id(id) {}

SLandlot::SLandlot(const string &city, const string &address, const string &region,
                   unsigned int id, const string &owner)
        : m_city(city), m_addr(address), m_region(region), m_id(id), m_owner(owner), m_owner_lower(owner) {
    s_id = index++;
    transform(m_owner_lower.begin(), m_owner_lower.end(), m_owner_lower.begin(), ::tolower);
}



// Member function definitions
bool SLandlot::changeOwnerName(const string &owner) {
    this->m_owner = owner;
    this->m_owner_lower = owner;
    transform(m_owner_lower.begin(), m_owner_lower.end(), m_owner_lower.begin(), ::tolower);
    return true;
}

bool SLandlot::increaseSID() {
    s_id = ++index;
    return true;
}

unsigned int SLandlot::index = 0;


struct Owner {
    string name;
    vector<SLandlot *> m_landlots;

    // Constructor
    Owner(const string &name);
};

// Constructor definition
Owner::Owner(const string &name) : name(name) {
    transform(this->name.begin(), this->name.end(), this->name.begin(), ::tolower);
}


class CIterator {
public:
    bool atEnd() const;

    void next();

    std::string city() const;

    std::string addr() const;

    std::string region() const;

    unsigned int id() const;

    std::string owner() const;

    CIterator(const vector<SLandlot *> data, unsigned int id = 0) : m_lots(data), index(id) {};

private:
    const vector<SLandlot *> m_lots;
    size_t index;
};

bool CIterator::atEnd() const {
    return index >= m_lots.size();
};

void CIterator::next() {
    index++;
};

string CIterator::city() const {
    return m_lots.at(index)->m_city;
};

string CIterator::addr() const { return m_lots.at(index)->m_addr; }

string CIterator::region() const { return m_lots.at(index)->m_region; }

unsigned CIterator::id() const { return m_lots.at(index)->m_id; }

std::string CIterator::owner() const { return m_lots.at(index)->m_owner; }


class CLandRegister {
public:
    CLandRegister();

    ~CLandRegister();

    bool add(const std::string &city,
             const std::string &addr,
             const std::string &region,
             unsigned int id);

    bool del(const std::string &city,
             const std::string &addr);

    bool del(const std::string &region,
             unsigned int id);

    bool getOwner(const std::string &city,
                  const std::string &addr,
                  std::string &owner) const;

    bool getOwner(const std::string &region,
                  unsigned int id,
                  std::string &owner) const;

    bool newOwner(const std::string &city,
                  const std::string &addr,
                  const std::string &owner);

    bool newOwner(const std::string &region,
                  unsigned int id,
                  const std::string &owner);

    size_t count(const std::string &owner) const;

    CIterator listByAddr() const;

    CIterator listByOwner(const std::string &owner) const;

    void print_arr();

private:
    std::vector<SLandlot *> city_arr;
    std::vector<SLandlot *> region_arr;
    std::vector<Owner> owner_arr;   

    bool findByCity(const string &city, const string &addr) const;

    bool findByRegion(const string &region, unsigned int id) const;

    bool findByOwner(const string &owner, const vector<Owner>::const_iterator &idx) const;
};

bool compareCity(const SLandlot *l, const SLandlot *r) {
    if (l->m_city == r->m_city) return l->m_addr < r->m_addr;
    return l->m_city < r->m_city;
}

bool compareRegion(const SLandlot *l, const SLandlot *r) {
    if (l->m_region == r->m_region) return l->m_id < r->m_id;
    return l->m_region < r->m_region;
}

bool compareOwner(const Owner &l, const Owner &r) {
    return l.name < r.name;
}

bool compareSID(const SLandlot *l, const SLandlot *r) {
    return l->s_id < r->s_id;
}

//void CLandRegister::print_arr() {
//    cout << "--------------City Arr-----------" << endl;
//    for (auto i = city_arr.begin(); i < city_arr.end(); ++i) {
//        cout << (*i)->m_city  << (*i)->m_owner << endl;
//    }
//
//    cout << "----------Region Arr-------------" << endl;
//
//    for (auto i = region_arr.begin(); i < region_arr.end(); ++i) {
//        cout << (*i)->m_region << endl;
//    }
//
//}

// Helper Function

bool CLandRegister::findByCity(const string &city, const string &addr) const {
<<<<<<< HEAD
    SLandlot *temp = new SLandlot(city, addr);
    auto city_itr = lower_bound(city_arr.begin(), city_arr.end(), temp, compareCity);
    delete temp;
    if (city_itr != city_arr.end()) {
        if ((*city_itr)->m_city == city && (*city_itr)->m_addr == addr)
=======
    SLandlot * temp = new SLandlot(city,addr);
    auto city_itr = lower_bound(city_arr.begin(), city_arr.end(), temp, compareCity);
    delete temp;
    if(city_itr != city_arr.end()) {
        if((*city_itr)->m_city == city && (*city_itr)->m_addr == addr)
>>>>>>> 561722c25b112a94b46cb6ecc585028034295dfc
            return true;

    }
    return false;
}

bool CLandRegister::findByRegion(const string &region, unsigned int id) const {


    SLandlot *temp = new SLandlot(region, id);
    auto region_iter = lower_bound(region_arr.begin(), region_arr.end(), temp,
                                   compareRegion);
    delete temp;
    if (region_iter != region_arr.end()) {
        if ((*region_iter)->m_region == region && (*region_iter)->m_id == id)
            return true;
    }
    return false;
}

bool CLandRegister::findByOwner(const string &owner, const vector<Owner>::const_iterator &idx) const {
    Owner temp(owner);
    if (idx != owner_arr.end()) {
        if (temp.name == (*idx).name) return true;
    }
    return false;
}

/* CLandRegister Class Definition
 * */

CLandRegister::CLandRegister() {};

CLandRegister::~CLandRegister() {

    for (auto i: city_arr)
        delete i;
};

bool CLandRegister::add(const std::string &city, const std::string &addr, const std::string &region, unsigned int id) {

    if (findByCity(city, addr) || findByRegion(region, id)) {
        return false;
    }
    SLandlot *landlot = new SLandlot(city, addr, region, id);
    auto city_iter = lower_bound(city_arr.begin(), city_arr.end(), landlot,
                                 compareCity);
    auto region_iter = lower_bound(region_arr.begin(), region_arr.end(), landlot,
                                   compareRegion);
    Owner temp = Owner("");
    auto owner_iter = lower_bound(owner_arr.begin(), owner_arr.end(), temp, compareOwner);

    if (!findByOwner("", owner_iter)) {
        owner_iter = owner_arr.insert(owner_iter, Owner(""));
    }

    city_arr.insert(city_iter, landlot);
    region_arr.insert(region_iter, landlot);
    owner_iter->m_landlots.push_back(landlot);
    return true;
}

bool CLandRegister::del(const std::string &city,
                        const std::string &addr) {

<<<<<<< HEAD
    if (!findByCity(city, addr)) return false;

    SLandlot *temp = new SLandlot(city, addr);
=======
    if(!findByCity(city, addr)) return false;

    SLandlot * temp = new SLandlot(city, addr);
>>>>>>> 561722c25b112a94b46cb6ecc585028034295dfc
    auto city_iter = lower_bound(city_arr.begin(), city_arr.end(), temp,
                                 compareCity);

    temp->m_region = (*city_iter)->m_region;
    temp->m_id = (*city_iter)->m_id;

    auto region_iter = lower_bound(region_arr.begin(), region_arr.end(), temp,
                                   compareRegion);

    Owner tempOwner = Owner((*city_iter)->m_owner_lower);
    auto owner_iter = lower_bound(owner_arr.begin(), owner_arr.end(), tempOwner,
                                  compareOwner);

    temp->s_id = (*city_iter)->s_id;
    auto innerOwnerIter = lower_bound(owner_iter->m_landlots.begin(), owner_iter->m_landlots.end(), temp, compareSID);

    delete temp;
    delete (*city_iter);
    city_arr.erase(city_iter);
    region_arr.erase(region_iter);
    owner_iter->m_landlots.erase(innerOwnerIter);

    return true;
};

bool CLandRegister::del(const std::string &region,
                        unsigned int id) {


    if (!findByRegion(region, id)) return false;

    SLandlot *temp = new SLandlot(region, id);


    auto region_iter = lower_bound(region_arr.begin(), region_arr.end(), temp,
                                   compareRegion);

    temp->m_city = (*region_iter)->m_city;
    temp->m_addr = (*region_iter)->m_addr;

    auto city_iter = lower_bound(city_arr.begin(), city_arr.end(), temp,
                                 compareCity);

    Owner tempOwner = Owner((*region_iter)->m_owner_lower);
    auto owner_iter = lower_bound(owner_arr.begin(), owner_arr.end(), tempOwner,
                                  compareOwner);

    temp->s_id = (*region_iter)->s_id;
    auto innerOwnerIter = lower_bound(owner_iter->m_landlots.begin(), owner_iter->m_landlots.end(), temp, compareSID);


    delete temp;
    delete (*region_iter);
    region_arr.erase(region_iter);
    city_arr.erase(city_iter);
    owner_iter->m_landlots.erase(innerOwnerIter);

    return true;

};

bool CLandRegister::getOwner(const std::string &city,
                             const std::string &addr,
                             std::string &owner) const {

    if (!findByCity(city, addr))return false;


    SLandlot *temp = new SLandlot(city, addr);
    auto city_iter = lower_bound(city_arr.begin(), city_arr.end(), temp,
                                 compareCity);

    owner = (*city_iter)->m_owner;
    delete temp;
    return true;
};

bool CLandRegister::getOwner(const std::string &region,
                             unsigned int id,
                             std::string &owner) const {

    if (!findByRegion(region, id))return false;


    SLandlot *temp = new SLandlot(region, id);
    auto region_iter = lower_bound(region_arr.begin(), region_arr.end(), temp,
                                   compareRegion);

    owner = (*region_iter)->m_owner;
    delete temp;
    return true;
};

bool CLandRegister::newOwner(const std::string &city,
                             const std::string &addr,
                             const std::string &owner) {
    if (!findByCity(city, addr)) { return false; }

    SLandlot *temp = new SLandlot(city, addr);

    auto city_iter = lower_bound(city_arr.begin(), city_arr.end(), temp,
                                 compareCity);

    Owner newOwner = Owner(owner);

    if (newOwner.name == (*city_iter)->m_owner_lower) {
        delete temp;
        return false;
    }

    // landlots in old owner
    Owner oldOwner = (*city_iter)->m_owner;
    auto owner_iter = lower_bound(owner_arr.begin(), owner_arr.end(), oldOwner,
                                  compareOwner);

    temp->s_id = (*city_iter)->s_id;
    auto inner_owner_iter = lower_bound(owner_iter->m_landlots.begin(), owner_iter->m_landlots.end(), temp,
                                        compareSID);

    (*city_iter)->changeOwnerName(owner);
    owner_iter->m_landlots.erase(inner_owner_iter);


    auto new_owner_iter = lower_bound(owner_arr.begin(), owner_arr.end(), newOwner,
                                      compareOwner);

    if (!findByOwner(owner, new_owner_iter)) {
        new_owner_iter = owner_arr.insert(new_owner_iter, newOwner);
    }

    (*city_iter)->increaseSID();
    new_owner_iter->m_landlots.push_back(*city_iter);

    delete temp;
    return true;
};

bool CLandRegister::newOwner(const std::string &region,
                             unsigned int id,
                             const std::string &owner) {


    if (!findByRegion(region, id)) { return false; }

    SLandlot *temp = new SLandlot(region, id);

    auto region_iter = lower_bound(region_arr.begin(), region_arr.end(), temp,
                                   compareRegion);

    Owner newOwner = Owner(owner);

    if (newOwner.name == (*region_iter)->m_owner_lower) {
        delete temp;
        return false;
    }

    // landlots in old owner
    Owner oldOwner = (*region_iter)->m_owner;
    auto owner_iter = lower_bound(owner_arr.begin(), owner_arr.end(), oldOwner,
                                  compareOwner);

    temp->s_id = (*region_iter)->s_id;
    auto inner_owner_iter = lower_bound(owner_iter->m_landlots.begin(), owner_iter->m_landlots.end(), temp,
                                        compareSID);

    (*region_iter)->changeOwnerName(owner);
    owner_iter->m_landlots.erase(inner_owner_iter);


    auto new_owner_iter = lower_bound(owner_arr.begin(), owner_arr.end(), newOwner,
                                      compareOwner);

    if (!findByOwner(owner, new_owner_iter)) {
        new_owner_iter = owner_arr.insert(new_owner_iter, newOwner);
    }

    (*region_iter)->increaseSID();
    new_owner_iter->m_landlots.push_back(*region_iter);

    delete temp;
    return true;

};

size_t CLandRegister::count(const std::string &owner) const {

    Owner temp = Owner(owner);
    auto owner_iter = lower_bound(owner_arr.begin(), owner_arr.end(), temp, compareOwner);
    if (findByOwner(owner, owner_iter)) {
        return owner_iter->m_landlots.size();
    }
    return 0;

};

CIterator CLandRegister::listByAddr() const {
    return CIterator(city_arr);
};

CIterator CLandRegister::listByOwner(const std::string &owner) const {
    Owner temp = Owner(owner);

    auto owner_iter = lower_bound(owner_arr.begin(), owner_arr.end(), temp,
                                  compareOwner);

    if (findByOwner(owner, owner_iter)) {
        return CIterator(owner_iter->m_landlots);
    }


    // point to an end
    return CIterator(city_arr, city_arr.size());

};

#ifndef __PROGTEST__

static void test0() {
    CLandRegister x;
    std::string owner;

    assert (x.add("Prague", "Thakurova", "Dejvice", 12345));
    assert (x.add("Prague", "Evropska", "Vokovice", 12345));
    assert (x.add("Prague", "Technicka", "Dejvice", 9873));
    assert (x.add("Plzen", "Evropska", "Plzen mesto", 78901));
    assert (x.add("Liberec", "Evropska", "Librec", 4552));
    CIterator i0 = x.listByAddr();
    assert (!i0.atEnd()
            && i0.city() == "Liberec"
            && i0.addr() == "Evropska"
            && i0.region() == "Librec"
            && i0.id() == 4552
            && i0.owner() == "");
    i0.next();
    assert (!i0.atEnd()
            && i0.city() == "Plzen"
            && i0.addr() == "Evropska"
            && i0.region() == "Plzen mesto"
            && i0.id() == 78901
            && i0.owner() == "");
    i0.next();
    assert (!i0.atEnd()
            && i0.city() == "Prague"
            && i0.addr() == "Evropska"
            && i0.region() == "Vokovice"
            && i0.id() == 12345
            && i0.owner() == "");
    i0.next();
    assert (!i0.atEnd()
            && i0.city() == "Prague"
            && i0.addr() == "Technicka"
            && i0.region() == "Dejvice"
            && i0.id() == 9873
            && i0.owner() == "");
    i0.next();
    assert (!i0.atEnd()
            && i0.city() == "Prague"
            && i0.addr() == "Thakurova"
            && i0.region() == "Dejvice"
            && i0.id() == 12345
            && i0.owner() == "");
    i0.next();
    assert (i0.atEnd());

    assert (x.count("") == 5);
    CIterator i1 = x.listByOwner("");
    assert (!i1.atEnd()
            && i1.city() == "Prague"
            && i1.addr() == "Thakurova"
            && i1.region() == "Dejvice"
            && i1.id() == 12345
            && i1.owner() == "");
    i1.next();
    assert (!i1.atEnd()
            && i1.city() == "Prague"
            && i1.addr() == "Evropska"
            && i1.region() == "Vokovice"
            && i1.id() == 12345
            && i1.owner() == "");
    i1.next();
    assert (!i1.atEnd()
            && i1.city() == "Prague"
            && i1.addr() == "Technicka"
            && i1.region() == "Dejvice"
            && i1.id() == 9873
            && i1.owner() == "");
    i1.next();
    assert (!i1.atEnd()
            && i1.city() == "Plzen"
            && i1.addr() == "Evropska"
            && i1.region() == "Plzen mesto"
            && i1.id() == 78901
            && i1.owner() == "");
    i1.next();
    assert (!i1.atEnd()
            && i1.city() == "Liberec"
            && i1.addr() == "Evropska"
            && i1.region() == "Librec"
            && i1.id() == 4552
            && i1.owner() == "");
    i1.next();
    assert (i1.atEnd());

    assert (x.count("CVUT") == 0);
    CIterator i2 = x.listByOwner("CVUT");
    assert (i2.atEnd());

    assert (x.newOwner("Prague", "Thakurova", "CVUT"));
    assert (x.newOwner("Dejvice", 9873, "CVUT"));
    assert (x.newOwner("Plzen", "Evropska", "Anton Hrabis"));
    assert (x.newOwner("Librec", 4552, "Cvut"));
    assert (x.getOwner("Prague", "Thakurova", owner) && owner == "CVUT");
    assert (x.getOwner("Dejvice", 12345, owner) && owner == "CVUT");
    assert (x.getOwner("Prague", "Evropska", owner) && owner == "");
    assert (x.getOwner("Vokovice", 12345, owner) && owner == "");
    assert (x.getOwner("Prague", "Technicka", owner) && owner == "CVUT");
    assert (x.getOwner("Dejvice", 9873, owner) && owner == "CVUT");
    assert (x.getOwner("Plzen", "Evropska", owner) && owner == "Anton Hrabis");
    assert (x.getOwner("Plzen mesto", 78901, owner) && owner == "Anton Hrabis");
    assert (x.getOwner("Liberec", "Evropska", owner) && owner == "Cvut");
    assert (x.getOwner("Librec", 4552, owner) && owner == "Cvut");
    CIterator i3 = x.listByAddr();
    assert (!i3.atEnd()
            && i3.city() == "Liberec"
            && i3.addr() == "Evropska"
            && i3.region() == "Librec"
            && i3.id() == 4552
            && i3.owner() == "Cvut");
    i3.next();
    assert (!i3.atEnd()
            && i3.city() == "Plzen"
            && i3.addr() == "Evropska"
            && i3.region() == "Plzen mesto"
            && i3.id() == 78901
            && i3.owner() == "Anton Hrabis");
    i3.next();
    assert (!i3.atEnd()
            && i3.city() == "Prague"
            && i3.addr() == "Evropska"
            && i3.region() == "Vokovice"
            && i3.id() == 12345
            && i3.owner() == "");
    i3.next();
    assert (!i3.atEnd()
            && i3.city() == "Prague"
            && i3.addr() == "Technicka"
            && i3.region() == "Dejvice"
            && i3.id() == 9873
            && i3.owner() == "CVUT");
    i3.next();
    assert (!i3.atEnd()
            && i3.city() == "Prague"
            && i3.addr() == "Thakurova"
            && i3.region() == "Dejvice"
            && i3.id() == 12345
            && i3.owner() == "CVUT");
    i3.next();
    assert (i3.atEnd());
    assert (x.count("cvut") == 3);
    CIterator i4 = x.listByOwner("cVuT");
    assert (!i4.atEnd()
            && i4.city() == "Prague"
            && i4.addr() == "Thakurova"
            && i4.region() == "Dejvice"
            && i4.id() == 12345
            && i4.owner() == "CVUT");
    i4.next();
    assert (!i4.atEnd()
            && i4.city() == "Prague"
            && i4.addr() == "Technicka"
            && i4.region() == "Dejvice"
            && i4.id() == 9873
            && i4.owner() == "CVUT");
    i4.next();
    assert (!i4.atEnd()
            && i4.city() == "Liberec"
            && i4.addr() == "Evropska"
            && i4.region() == "Librec"
            && i4.id() == 4552
            && i4.owner() == "Cvut");
    i4.next();
    assert (i4.atEnd());

    assert (x.newOwner("Plzen mesto", 78901, "CVut"));
    assert (x.count("CVUT") == 4);
    CIterator i5 = x.listByOwner("CVUT");
    assert (!i5.atEnd()
            && i5.city() == "Prague"
            && i5.addr() == "Thakurova"
            && i5.region() == "Dejvice"
            && i5.id() == 12345
            && i5.owner() == "CVUT");
    i5.next();
    assert (!i5.atEnd()
            && i5.city() == "Prague"
            && i5.addr() == "Technicka"
            && i5.region() == "Dejvice"
            && i5.id() == 9873
            && i5.owner() == "CVUT");
    i5.next();
    assert (!i5.atEnd()
            && i5.city() == "Liberec"
            && i5.addr() == "Evropska"
            && i5.region() == "Librec"
            && i5.id() == 4552
            && i5.owner() == "Cvut");
    i5.next();
    assert (!i5.atEnd()
            && i5.city() == "Plzen"
            && i5.addr() == "Evropska"
            && i5.region() == "Plzen mesto"
            && i5.id() == 78901
            && i5.owner() == "CVut");
    i5.next();
    assert (i5.atEnd());

    assert (x.del("Liberec", "Evropska"));
    assert (x.del("Plzen mesto", 78901));
    assert (x.count("cvut") == 2);
    CIterator i6 = x.listByOwner("cVuT");
    assert (!i6.atEnd()
            && i6.city() == "Prague"
            && i6.addr() == "Thakurova"
            && i6.region() == "Dejvice"
            && i6.id() == 12345
            && i6.owner() == "CVUT");
    i6.next();
    assert (!i6.atEnd()
            && i6.city() == "Prague"
            && i6.addr() == "Technicka"
            && i6.region() == "Dejvice"
            && i6.id() == 9873
            && i6.owner() == "CVUT");
    i6.next();
    assert (i6.atEnd());

    assert (x.add("Liberec", "Evropska", "Librec", 4552));
}

static void test1() {
    CLandRegister x;
    std::string owner;

    assert (x.add("Prague", "Thakurova", "Dejvice", 12345));
    assert (x.add("Prague", "Evropska", "Vokovice", 12345));
    assert (x.add("Prague", "Technicka", "Dejvice", 9873));
    assert (!x.add("Prague", "Technicka", "Hradcany", 7344));
    assert (!x.add("Brno", "Bozetechova", "Dejvice", 9873));
    assert (!x.getOwner("Prague", "THAKUROVA", owner));
    assert (!x.getOwner("Hradcany", 7343, owner));
    CIterator i0 = x.listByAddr();
    assert (!i0.atEnd()
            && i0.city() == "Prague"
            && i0.addr() == "Evropska"
            && i0.region() == "Vokovice"
            && i0.id() == 12345
            && i0.owner() == "");
    i0.next();
    assert (!i0.atEnd()
            && i0.city() == "Prague"
            && i0.addr() == "Technicka"
            && i0.region() == "Dejvice"
            && i0.id() == 9873
            && i0.owner() == "");
    i0.next();
    assert (!i0.atEnd()
            && i0.city() == "Prague"
            && i0.addr() == "Thakurova"
            && i0.region() == "Dejvice"
            && i0.id() == 12345
            && i0.owner() == "");
    i0.next();
    assert (i0.atEnd());

    assert (x.newOwner("Prague", "Thakurova", "CVUT"));
    assert (!x.newOwner("Prague", "technicka", "CVUT"));
    assert (!x.newOwner("prague", "Technicka", "CVUT"));
    assert (!x.newOwner("dejvice", 9873, "CVUT"));
    assert (!x.newOwner("Dejvice", 9973, "CVUT"));
    assert (!x.newOwner("Dejvice", 12345, "CVUT"));
    assert (x.count("CVUT") == 1);
    CIterator i1 = x.listByOwner("CVUT");
    assert (!i1.atEnd()
            && i1.city() == "Prague"
            && i1.addr() == "Thakurova"
            && i1.region() == "Dejvice"
            && i1.id() == 12345
            && i1.owner() == "CVUT");
    i1.next();
    assert (i1.atEnd());

    assert (!x.del("Brno", "Technicka"));
    assert (!x.del("Karlin", 9873));
    assert (x.del("Prague", "Technicka"));
    assert (!x.del("Prague", "Technicka"));
    assert (!x.del("Dejvice", 9873));
}

int main(void) {
    test0();
    test1();
    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */