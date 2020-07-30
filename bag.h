#pragma once
#include <unordered_map>
#include <chrono>
#include <random>

class Bag {
    std::unordered_map<char, std::size_t> bags_of_letters { //дефолтный мешок букв
                {'a', 9}, {'e', 12}, {'i', 9}, {'o', 8}, {'u', 4}, {'l', 4},
                {'n' , 6}, {'s',4}, {'t', 6}, {'r', 8}, {'d', 4}, {'g', 3},
                {'b', 2}, {'c', 2}, {'m', 2}, {'p', 2},
                {'f', 2}, {'h', 2}, {'v', 2}, {'w', 2}, {'y',2},
                {'k', 1}, {'j', 1}, {'x', 1}, {'q', 1}, {'z', 1} };
public:
    
    void Decrease(char c) {
        bags_of_letters[c]--;
    }

    void Increase(char c) {
        bags_of_letters[c]++;
    }

    char GenerateLetter() {
        char ch = GenerateChar();
        while (!bags_of_letters.at(ch)) {
            ch = GenerateChar();
        }
        return ch;
    }

private:
//генерировать по одному символу - херня идея, не эффективно
    char GenerateChar(){
        std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<> dist(0,25);    
        return 'a' + (char)dist(rng);
    }
};