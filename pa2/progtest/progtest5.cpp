#ifndef __PROGTEST__
#include <cassert>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <memory>
#include <functional>
#endif /* __PROGTEST__ */

using namespace std;

class CComponent {
public:
    virtual ~CComponent() {}
    virtual ostream & printInfo(ostream &os, bool isLast) const = 0;
};

class CComputer {
public:
    CComputer(string name) : mComputerName(name) {}

    template<typename T>
    CComputer &addComponent(const T &data) {
        componentArr.push_back(make_unique<T>(data));
        return *this;
    }

    CComputer *copy() const {
        CComputer *temp = new CComputer(mComputerName);
        for (const auto &compPtr : componentArr) {
            temp->componentArr.push_back(unique_ptr<CComponent>());
        }
        temp->addressArr = addressArr;
        return temp;
    }

    CComputer &addAddress(const string &address) {
        addressArr.push_back(address);
        return *this;
    }


    ostream & printInfo(ostream  &os, bool isLast) const {
        if(isLast) os <<  "+-";
        else os << "\\";
        os<< "Host: " << mComputerName << "\n";

        for (auto it = componentArr.begin(); it!= componentArr.end(); it++) {
            if (it == prev(componentArr.end()) || isLast) {
                os << "  +-";
                (*it)->printInfo(os, true);
            }else {
                os << "| +-";
                (*it)->printInfo(os, false);
            }
        }


        return os;
    }


    ostream &printInfo(ostream &os) const {
        os << "Host: " << mComputerName << "\n";

        for (auto it = componentArr.begin(); it != componentArr.end(); it++) {
            if(it == componentArr.end()) {
                os << "  +-";
                (*it)->printInfo(os, true);
            }else{
                os<< "| +-";
                (*it)->printInfo(os, false);
            }
        }

        return os;
    }

    friend ostream &operator<<(ostream &os, const CComputer &computer) {
        return computer.printInfo(os);
    }


    string mComputerName;
    vector<string> addressArr;
    vector<unique_ptr<CComponent>> componentArr;
};


class CNetwork {

private:
    string mName;
    map<string, shared_ptr<CComputer>> network;

public:
    explicit CNetwork(string name):mName(name) {};

//    To Implement
    CNetwork & addComputer(const CComputer & data){
        network.insert(make_pair(data.mComputerName, data.copy()));
        return *this;
    }


    CComputer * findComputer(string name) {
        auto res =  network.find(name);
        if(res == network.end())return NULL;
        else return network[name].get();
    }

    ostream & printInfo(ostream & os) const {
        os << "Network: " << mName << "\n";
        int count  = 0;
        for (auto it = network.begin(); it != network.end() && count<= network.size() ; it++, count++ ) {
            if(count == network.size() || it == network.end()){
                it->second->printInfo(os, true);
            }  else  it->second->printInfo(os, false);
        }
        return os;
    }

    friend ostream & operator<<(ostream &os, const CNetwork & network){
        return network.printInfo(os);
    }

};
class CCPU: public CComponent {

private:
    int mCores;
    int mFreq;
public:
CCPU(int cores, int freq): mCores(cores), mFreq(freq) {};


ostream & printInfo(ostream & os, bool isLast) const override{

    if(isLast){
        os << "\\-";
    }else{
        os<< "+-";
    }
    os<< "CPU, "<< mCores <<" cores @ "<< mFreq <<"MHz";
    return os;


}

CCPU* copy() {
    return new CCPU(mCores, mFreq);
}

};






class CMemory: public CComponent {

private:
    int mMemSize;
public:
    CMemory(int size): mMemSize(size){};
    ostream & printInfo(ostream & os, bool isLast) const override{
        if(isLast){
            os << "\\-";
        }else{
            os<< "+-";
        }
        os<< "Memory, "<< mMemSize <<" MiB";
        return os;

    }

    CMemory * copy() {
        return new CMemory(mMemSize);
    }

};
class CDisk : public CComponent{

private:
    bool isMagnetic;
    int mSize; //gb
    vector <pair<int , string>> partArr;

public:
    static int const MAGNETIC = 1;
    static int const SSD = 2;

    CDisk(int type, int size): mSize(size) {
        if(type == 1) {
            isMagnetic = true;
        }else isMagnetic = false;
    }

    CDisk & addPartition (int size, string dir) {
        partArr.emplace_back(make_pair(size, dir));
        return *this;
    }

    ostream & printInfo(ostream & os, bool isLast) const override{return os;};

    CDisk * copy() {
        int isMag = 0;
        if(isMagnetic) isMag = 1;
        else isMag = 0;

        auto * temp = new CDisk(isMag, mSize);
        for(auto & i : partArr){
            temp->partArr.push_back(i);
        }
        return temp;
    }
};

#ifndef __PROGTEST__
template<typename T_>
std::string toString ( const T_ & x )
{
    std::ostringstream oss;
    oss << x;
    return oss . str ();
}

int main ()
{



    CNetwork n ( "FIT network" );
    n . addComputer (
            CComputer ( "progtest.fit.cvut.cz" ) .
                    addAddress ( "147.32.232.142" ) .
                    addComponent ( CCPU ( 8, 2400 ) ) .
                    addComponent ( CCPU ( 8, 1200 ) ) .
                    addComponent ( CDisk ( CDisk::MAGNETIC, 1500 ) .
                    addPartition ( 50, "/" ) .
                    addPartition ( 5, "/boot" ).
                    addPartition ( 1000, "/var" ) ) .
                    addComponent ( CDisk ( CDisk::SSD, 60 ) .
                    addPartition ( 60, "/data" )  ) .
                    addComponent ( CMemory ( 2000 ) ).
                    addComponent ( CMemory ( 2000 ) ) ) .
            addComputer (
            CComputer ( "courses.fit.cvut.cz" ) .
                    addAddress ( "147.32.232.213" ) .
                    addComponent ( CCPU ( 4, 1600 ) ) .
                    addComponent ( CMemory ( 4000 ) ).
                    addComponent ( CDisk ( CDisk::MAGNETIC, 2000 ) .
                    addPartition ( 100, "/" )   .
                    addPartition ( 1900, "/data" ) ) ) .
            addComputer (
            CComputer ( "imap.fit.cvut.cz" ) .
                    addAddress ( "147.32.232.238" ) .
                    addComponent ( CCPU ( 4, 2500 ) ) .
                    addAddress ( "2001:718:2:2901::238" ) .
                    addComponent ( CMemory ( 8000 ) ) );

    cout << "Seg Fault after this" << endl;


    assert ( toString ( n ) ==
             "Network: FIT network\n"
             "+-Host: progtest.fit.cvut.cz\n"
             "| +-147.32.232.142\n"
             "| +-CPU, 8 cores @ 2400MHz\n"
             "| +-CPU, 8 cores @ 1200MHz\n"
             "| +-HDD, 1500 GiB\n"
             "| | +-[0]: 50 GiB, /\n"
             "| | +-[1]: 5 GiB, /boot\n"
             "| | \\-[2]: 1000 GiB, /var\n"
             "| +-SSD, 60 GiB\n"
             "| | \\-[0]: 60 GiB, /data\n"
             "| +-Memory, 2000 MiB\n"
             "| \\-Memory, 2000 MiB\n"
             "+-Host: courses.fit.cvut.cz\n"
             "| +-147.32.232.213\n"
             "| +-CPU, 4 cores @ 1600MHz\n"
             "| +-Memory, 4000 MiB\n"
             "| \\-HDD, 2000 GiB\n"
             "|   +-[0]: 100 GiB, /\n"
             "|   \\-[1]: 1900 GiB, /data\n"
             "\\-Host: imap.fit.cvut.cz\n"
             "  +-147.32.232.238\n"
             "  +-2001:718:2:2901::238\n"
             "  +-CPU, 4 cores @ 2500MHz\n"
             "  \\-Memory, 8000 MiB\n" );
    CNetwork x = n;



    auto c = x . findComputer ( "imap.fit.cvut.cz" );




    assert ( toString ( *c ) ==
             "Host: imap.fit.cvut.cz\n"
             "+-147.32.232.238\n"
             "+-2001:718:2:2901::238\n"
             "+-CPU, 4 cores @ 2500MHz\n"
             "\\-Memory, 8000 MiB\n" );



    c -> addComponent ( CDisk ( CDisk::MAGNETIC, 1000 ) .
            addPartition ( 100, "system" ) .
            addPartition ( 200, "WWW" ) .
            addPartition ( 700, "mail" ) );



    assert ( toString ( x ) ==
             "Network: FIT network\n"
             "+-Host: progtest.fit.cvut.cz\n"
             "| +-147.32.232.142\n"
             "| +-CPU, 8 cores @ 2400MHz\n"
             "| +-CPU, 8 cores @ 1200MHz\n"
             "| +-HDD, 1500 GiB\n"
             "| | +-[0]: 50 GiB, /\n"
             "| | +-[1]: 5 GiB, /boot\n"
             "| | \\-[2]: 1000 GiB, /var\n"
             "| +-SSD, 60 GiB\n"
             "| | \\-[0]: 60 GiB, /data\n"
             "| +-Memory, 2000 MiB\n"
             "| \\-Memory, 2000 MiB\n"
             "+-Host: courses.fit.cvut.cz\n"
             "| +-147.32.232.213\n"
             "| +-CPU, 4 cores @ 1600MHz\n"
             "| +-Memory, 4000 MiB\n"
             "| \\-HDD, 2000 GiB\n"
             "|   +-[0]: 100 GiB, /\n"
             "|   \\-[1]: 1900 GiB, /data\n"
             "\\-Host: imap.fit.cvut.cz\n"
             "  +-147.32.232.238\n"
             "  +-2001:718:2:2901::238\n"
             "  +-CPU, 4 cores @ 2500MHz\n"
             "  +-Memory, 8000 MiB\n"
             "  \\-HDD, 1000 GiB\n"
             "    +-[0]: 100 GiB, system\n"
             "    +-[1]: 200 GiB, WWW\n"
             "    \\-[2]: 700 GiB, mail\n" );




    assert ( toString ( n ) ==
             "Network: FIT network\n"
             "+-Host: progtest.fit.cvut.cz\n"
             "| +-147.32.232.142\n"
             "| +-CPU, 8 cores @ 2400MHz\n"
             "| +-CPU, 8 cores @ 1200MHz\n"
             "| +-HDD, 1500 GiB\n"
             "| | +-[0]: 50 GiB, /\n"
             "| | +-[1]: 5 GiB, /boot\n"
             "| | \\-[2]: 1000 GiB, /var\n"
             "| +-SSD, 60 GiB\n"
             "| | \\-[0]: 60 GiB, /data\n"
             "| +-Memory, 2000 MiB\n"
             "| \\-Memory, 2000 MiB\n"
             "+-Host: courses.fit.cvut.cz\n"
             "| +-147.32.232.213\n"
             "| +-CPU, 4 cores @ 1600MHz\n"
             "| +-Memory, 4000 MiB\n"
             "| \\-HDD, 2000 GiB\n"
             "|   +-[0]: 100 GiB, /\n"
             "|   \\-[1]: 1900 GiB, /data\n"
             "\\-Host: imap.fit.cvut.cz\n"
             "  +-147.32.232.238\n"
             "  +-2001:718:2:2901::238\n"
             "  +-CPU, 4 cores @ 2500MHz\n"
             "  \\-Memory, 8000 MiB\n" );
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
