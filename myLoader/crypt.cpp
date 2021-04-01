#include "isConnect.h"

std::string encrip(std::string input) {
    std::vector<char> word(input.begin(), input.end());
    // std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < (int)input.length(); i++) {
        for (int j = 0; j < (int)alphabet.length(); j++) {
            if (word[i] == alphabet[j]) {
                word[i] = alphabet[(j + 3) % 26];

                break;
            }
        }
    }
    std::string str(word.begin(), word.end());
    return str;
}

std::string decrip(std::string input) {
    std::vector<char> word(input.begin(), input.end());
    // std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < (int)input.length(); i++) {
        for (int j = 0; j < (int)alphabet.length(); j++) {
            if (word[i] == alphabet[j]) {
                word[i] = alphabet[(j - 3) % 26];
                break;
            }
        }
    }
    std::string str(word.begin(), word.end());
    return str;
}