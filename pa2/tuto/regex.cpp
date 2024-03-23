//
// Created by Thet Oo Aung on 29/02/2024.
//


#include "cassert"
#include "iostream"

class SimpleRegex {
public:
    SimpleRegex(const std::string &pattern) {
        mPattern = pattern;
    }

    bool matchImpl(size_t patternIdx, const std::string &word,
                   size_t wordIdx) const {
        if (patternIdx == mPattern.size() && wordIdx == word.size())
            return true;
        if (patternIdx < mPattern.size()) {
            char patChar = mPattern[patternIdx];
            char wordChar = word[wordIdx];
            if (patChar == '*') {
                if (matchImpl(patternIdx + 1, word, wordIdx + 1)) return true;
                //if()
            }
        }
    }


    bool match(const std::string &word) const {

        if (mPattern.size() != word.size()) return false;
        size_t idx = 0;
        const char wildcard = '.';
        for (; idx < mPattern.size(); idx++) {
            if (idx >= word.size()) return false;
            if (mPattern[idx] == wildcard) continue;
            if (mPattern[idx] != word[idx])return false;
        }

        return true;
    }

private:
    std::string mPattern;
};


int main() {
    SimpleRegex reg{"H...o"};
    assert(reg.match("Hello") == true);
    assert(reg.match("Holoo") == true);
    assert(reg.match("Holox") == true);
    assert(reg.match("Holoooo") == true);
}