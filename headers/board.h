#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <map>

#include <SFML/Graphics.hpp>

enum class Mult {
    NRM,
    TW,
    TL,
    DW,
    DL
};


// later add [G -> green in console]
const std::map<Mult, sf::Color> mult_to_colour = {{Mult::NRM, sf::Color::White}, {Mult::DL, sf::Color::Green},
                                    {Mult::DW, sf::Color::Blue}, {Mult::TL, sf::Color::Yellow},
                                    {Mult::TW, sf::Color::Red }};


const std::map<char, Mult> colour_to_mult = {{'_', Mult::NRM}, {'G', Mult::DL},
                                    {'B', Mult::DW}, {'Y', Mult::TL},
                                    {'R', Mult::TW}};



struct Cell {
    char l;
    Mult m;
};

class Board {
public:
    explicit Board( size_t n_r = 15,
                    std::size_t n_c = 15,
					const std::string& source = "source/default_board.txt") : rows(n_r, std::vector<Cell>(n_c)),
                                                             cols(n_c, std::vector<Cell>(n_r)), n_rows(n_r), n_cols(n_c) {
        LoadBoardFromFile(source);
    }   

    const size_t GetSizeRows() const {
        return n_rows;
    }

    const size_t GetSizeColumns() const {
        return n_cols;
    }

    sf::Color GetColor(size_t i, size_t j) {
        return mult_to_colour.at(rows[i][j].m);
    }
    

private:
    std::vector<std::vector<Cell>> rows;
    std::vector<std::vector<Cell>> cols;
    size_t n_rows;
    size_t n_cols;
    

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