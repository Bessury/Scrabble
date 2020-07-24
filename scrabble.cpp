#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <map>
#include <set>
#include <random>
#include <chrono>
enum class Mult {
    NRM,
    TW,
    TL,
    DW,
    DL
};

const size_t HAND_SIZE = 6;


// later add [G -> green in console]
const std::map<Mult, char> mult_to_colour = {{Mult::NRM, '_'}, {Mult::DL, 'G'},
                                    {Mult::DW, 'B'}, {Mult::TL, 'Y'},
                                    {Mult::TW, 'R'}};


const std::map<char, Mult> colour_to_mult = {{'_', Mult::NRM}, {'G', Mult::DL},
                                    {'B', Mult::DW}, {'Y', Mult::TL},
                                    {'R', Mult::TW}};

struct Cell {
    char l;
    Mult m;
};

class Board {
public:
    explicit Board( std::size_t n_rows = 15,
                    std::size_t n_cols = 15,
					const std::string& source = "default_board.txt") : rows(n_rows, std::vector<Cell>(n_cols)),
                                                             cols(n_cols, std::vector<Cell>(n_rows)) {
        LoadBoardFromFile(source);
    }
    
    void PrintBoard(){
        for (const auto& x : rows) {
            std::cout <<"| ";
			for (auto z : x) {
					std::cout << mult_to_colour.at(z.m) << " ";
                }    
                std::cout <<"|"<< std::endl;
            }
            
        }
    


private:
    std::vector<std::vector<Cell>> rows;
    std::vector<std::vector<Cell>> cols;

    void LoadBoardFromFile(const std::string& source) {
		std::ifstream fin(source);
		if(!fin.is_open()) {
			throw std::logic_error("LoadBoardFromFile: File can't be opened");
		} else {
			for (size_t row = 0; row < rows.size(); row++){
				for (size_t col = 0; col < cols.size(); col++){
					char c; fin >> c;
					Mult temp = colour_to_mult.at(c);
					rows[row][col].m = temp;
					cols[col][row].m = temp;
				}
			}
		}
	}
};




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

class Player {
private:
    std::string name {};
    size_t score {0};
    std::vector<std::string> history_words {};
    std::set<char> set_of_letters {}; //maybe array<HAND_SIZE>
public:
    Player(std::string n, Bag& bag) : name(std::move(n)) { // пока что для теста передаем мешок, как параметр
        for (size_t i = 0; i < HAND_SIZE; i++) { 
            char c = bag.GenerateLetter();
            bag.Decrease(c);
            set_of_letters.insert(c);
        } 
    }

    void AddWordToHistory(const std::string& str) {
        history_words.push_back(str);
    }

    void ChangeName(const std::string& str) {
        name = str;
    }
};

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



int main() {
    Game g;
    std::cout << g.GetSizeDict();
    return 0;
}
