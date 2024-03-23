//
// Created by Thet Oo Aung on 29/02/2024.
//
#include "cassert"
#include "string"


class MyString {
public :
    MyString(std::string s) {
        mData = s;
    }

    void SetString(const std::string &s) {
        mData = s;
    }

    bool StartWith(const std::string &prefix) const {
        return mData.compare(0, sizeof(prefix) - 1, prefix) == 0;
    }


private:
    std::string mData;
};

int main() {
    MyString str("Hello");
    str.SetString("Hello Thet Oo Aung");
    return 0;
}