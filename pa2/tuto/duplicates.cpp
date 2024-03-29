//
// Created by aungthet on 3/28/24.
//


#include "vector"

void func (std::vector<int> &vec) {
    std::set<int >s (vec.begin(), vec.end());
    vec = std::vector<int> (s.begin(), s.end());




}


int main () {


    Hashstring hs;

    hs("abc");

    return 0;
}