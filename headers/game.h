#pragma once
#include <unordered_map>
#include <vector>
#include <set>
#include <stdexcept>
#include <string>
#include <fstream>
#include "/mnt/c/Users/nimak/Git/Scrabble/headers/player.h"

class Game {
public:
	Game() {
		LoadDictFromFile();
	}
		
	size_t GetSizeDict() {
	 	return set_of_words_.size();
	}
private:
    
    std::vector<Player> players;  
    std::set<std::string> set_of_words_;

    const std::unordered_map<char, std::size_t> scores {
            {'a',1}, {'e',1}, {'i',1}, {'o',1}, {'u',1}, {'l',1},
            {'n',1}, {'s',1}, {'t',1}, {'r',1},
            {'d',2}, {'g',2},
            {'b',3}, {'c',3}, {'m',3}, {'p',3},
            {'f',4}, {'h',4}, {'v',4}, {'w',4}, {'y',4},
            {'k',5},
            {'j',8}, {'x',8},
            {'q',10}, {'z',10}};


    void LoadDictFromFile(const std::string& source = "def_word_list.txt"){
		std::ifstream fin(source);
        if(!fin.is_open()) {
            throw std::logic_error("LoadDictFromFile: File can't be opened");
        } else{
            std::string word;
            while (fin >> word){
                set_of_words_.insert(word);
            }
        }

    }

};