#include <iostream>
#include <string>

constexpr int Max_SIZE = 100;

class CCar {
    std::string l_number;
    std::string owner;
    unsigned age;

public:
    CCar(const std::string l_number, const std::string owner, unsigned age)
            : l_number(l_number), owner(owner), age(age) {}

    bool operator==(const CCar &other) const {
        return l_number == other.l_number;
    }

    bool operator==(const std::string &other_l_number) const {
        return l_number == other_l_number;
    }

    bool newerThan(const CCar &other) const {
        return age == other.age;

    }

    friend std::ostream &operator<<(std::ostream &os, const CCar &car) {
        return os << "Car l_number = " << car.l_number << "owner = "
                  << car.owner << "age = " << car.age;
    }


};

bool add_car() {
    return false;
}

//sort_car();
//delete_car();
//print_car();


class CGarage {
    std::vector<CCar> db;
public:
    bool add_car(CCar car);

    void delete_car(const std::string &l_number);

    bool sort_car();

    void print_car();


};

bool CGarage::add_car(CCar car) {};

void CGarage::delete_car(const std::string &l_number) {};

bool CGarage::sort_car() {};

void CGarage::print_car() {};


int main() {
    CGarage garage;
    garage.add_car(CCar("NCC2131", "LOOIweir fadsd", 10));
    garage.add_car(CCar("aweoe12431", "NO NEed  fadsd", 10));
    garage.add_car(CCar("NCC2131", "Test Data", 10));
    std::cout << "--------Before Sorting------------" << std::endl;
    garage.sort_car();
    std::cout << "--------After Sorting------------" << std::endl;
    garage.delete_car("aweoe12431");
    std::cout << "--------Deleting Sorting------------" << std::endl;
    garage.print_car();
    return 0;
}





