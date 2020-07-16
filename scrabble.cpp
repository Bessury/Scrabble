#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <unordered_map>

enum class Mult {
    NRM,
    TW,
    TL,
    DW,
    DL
};


struct Cell {
    char l;
    Mult m;
};
/*
 maybe we should use constuction like this std::map<Mult, char> colour_mult = {{Mult::NRM, '_'}, {Mult::DL, 'G'} ...
 to easy convert ?
*/
char MultToCharColour(Mult m){
    switch (m) {
		case Mult::NRM:
			return '_';
		case Mult::DL:
			return 'G';
		case Mult::DW:
			return 'B';
		case Mult::TL:
			return 'Y';
		case Mult::TW:
			return 'R';
		default:
			throw std::invalid_argument("MultToCharColour");
	}
}


Mult ColourChartoMult (char c) {
    switch (c) {
		case '_':
			return Mult::NRM;
		case 'G':
			return Mult::DL;
		case 'B':
			return Mult::DW;
		case 'Y':
			return Mult::TL;
		case 'R':
			return Mult::TW;
		default:
			throw std::invalid_argument("ColourChartoMult");
	}
}

class Board {
public:
    explicit Board( std::size_t n_rows = 15,
                    std::size_t n_cols = 15,
					const std::string& source = "default_board.txt") : rows(n_rows, std::vector<Cell>(n_cols)),
                                                             cols(n_cols, std::vector<Cell>(n_rows)) {
        if (source != "default")
            LoadBoardFromFile(source);
        else
            LoadBoardFromFile(source);

    }

    void PrintBoard(){
        for (const auto& x : rows) {
            std::cout <<"| ";
			for (auto z : x) {
					std::cout << MultToCharColour(z.m) << " ";
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
			throw std::logic_error("UploadDictFromFile: File can't be opened");
		} else {
			for (size_t row = 0; row < rows.size(); row++){
				for (size_t col = 0; col < cols.size(); col++){
					char c; fin >> c;
					Mult temp = ColourChartoMult(c);
					rows[row][col].m = temp;
					cols[col][row].m = temp;
				}
			}
		}
	}
};



class Game {
private:
    std::unordered_map<char, std::size_t> bags_of_letters {
            {'a', 9}, {'e', 12}, {'i', 9}, {'o', 8}, {'u', 4}, {'l', 4},
            {'n' , 6}, {'s',4}, {'t', 6}, {'r', 8}, {'d', 4}, {'g', 3},
            {'b', 2}, {'c', 2}, {'m', 2}, {'p', 2},
            {'f', 2}, {'h', 2}, {'v', 2}, {'w', 2}, {'y',2},
            {'k', 1}, {'j', 1}, {'x', 1}, {'q', 1}, {'z', 1} };

    const std::unordered_map<char, std::size_t> scores{
            {'a',1}, {'e',1}, {'i',1}, {'o',1}, {'u',1}, {'l',1},
            {'n',1}, {'s',1}, {'t',1}, {'r',1},
            {'d',2}, {'g',2},
            {'b',3}, {'c',3}, {'m',3}, {'p',3},
            {'f',4}, {'h',4}, {'v',4}, {'w',4}, {'y',4},
            {'k',5},
            {'j',8}, {'x',8},
            {'q',10}, {'z',10}
    };

};



int main() {
    Board b;
    b.PrintBoard();

    return 0;
}
