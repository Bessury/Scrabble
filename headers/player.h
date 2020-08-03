#pragma once

#include <string>
#include <vector>
#include <string>

#include "/mnt/c/Users/nimak/Git/Scrabble/headers/bag.h"


const size_t HAND_SIZE = 6;

class Player {
private:
    std::string name {};
    size_t score {0};
    std::vector<std::string> history_words {};
    std::vector<char> set_of_letters {}; //maybe array<HAND_SIZE>
public:
    Player(std::string n, Bag& bag) : name(std::move(n)) { // пока что для теста передаем мешок, как параметр
        for (size_t i = 0; i < HAND_SIZE; i++) { 
            char c = bag.GenerateLetter();
            bag.Decrease(c);
            set_of_letters.push_back(c);
        } 
    }

    void AddWordToHistory(const std::string& str) {
        history_words.push_back(str);
    }

    void ChangeName(const std::string& str) {
        name = str;
    }
};