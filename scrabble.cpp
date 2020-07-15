#include <iostream>
#include <vector>
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


class Board {
public:
    explicit Board( std::size_t n_rows = 15,
                    std::size_t n_cols = 15,
                    const std::string& source = "default") : rows(n_rows, std::vector<Cell>(n_cols)),
                                                             cols(n_cols, std::vector<Cell>(n_rows)) {
        if (source != "default")
            LoadBoardFromFile(source);
        else
            MakeBoard(default_board);

    }

    void PrintBoard(){
        for (const auto& x : rows) {
            for (auto z : x) {
                switch (z.m) {
                    case Mult::NRM:
                        std::cout << '_' << ' ';
                        break;
                    case Mult::DL:
                        std::cout << "G ";
                        break;
                    case Mult::DW:
                        std::cout << "B ";
                        break;
                    case Mult::TL:
                        std::cout << "Y ";
                        break;
                    case Mult::TW:
                        std::cout << "R ";
                        break;
                    default:
                        break;
                }
            }
            std::cout << std::endl;
        }
    }


private:
    std::vector<std::vector<Cell>> rows;
    std::vector<std::vector<Cell>> cols;

    void LoadBoardFromFile(const std::string& source) {
    }

    void MakeBoard(const std::vector<std::vector<Mult>>& board) {
        for (size_t row = 0; row < board.size(); row++){
            for (size_t col = 0; col < board[0].size(); col++){
                rows[row][col].m = board[row][col];
                cols[col][row].m = board[col][row];
            }
        }
    }

    const std::vector<std::vector<Mult>> default_board{
            {Mult::TW, Mult::NRM, Mult::NRM, Mult::DL, Mult::NRM, Mult::NRM, Mult::NRM, Mult::TW, Mult::NRM, Mult::NRM, Mult::NRM, Mult::DL, Mult::NRM, Mult::NRM, Mult::TW},
            {Mult::NRM, Mult::DW, Mult::NRM, Mult::NRM, Mult::NRM, Mult::TL, Mult::NRM, Mult::NRM, Mult::NRM, Mult::TL, Mult::NRM, Mult::NRM, Mult::NRM, Mult::DW, Mult::NRM},
            {Mult::NRM, Mult::NRM, Mult::DW, Mult::NRM, Mult::NRM, Mult::NRM, Mult::DL, Mult::NRM, Mult::DL, Mult::NRM, Mult::NRM, Mult::NRM, Mult::DW, Mult::NRM, Mult::NRM},
            {Mult::DL, Mult::NRM, Mult::NRM, Mult::DW, Mult::NRM, Mult::NRM, Mult::NRM, Mult::DL, Mult::NRM, Mult::NRM, Mult::NRM, Mult::DW, Mult::NRM, Mult::NRM, Mult::DL},
            {Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::DW, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::DW, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM},
            {Mult::NRM, Mult::TL, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::TL, Mult::NRM},
            {Mult::NRM, Mult::NRM, Mult::DL, Mult::NRM, Mult::NRM, Mult::NRM, Mult::DL, Mult::NRM, Mult::DL, Mult::NRM, Mult::NRM, Mult::NRM, Mult::DL, Mult::NRM, Mult::NRM},
            {Mult::TW, Mult::NRM, Mult::NRM, Mult::DL, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::DL, Mult::NRM, Mult::NRM, Mult::TW},
            {Mult::NRM, Mult::NRM, Mult::DL, Mult::NRM, Mult::NRM, Mult::NRM, Mult::DL, Mult::NRM, Mult::DL, Mult::NRM,Mult::NRM, Mult::NRM, Mult::DL, Mult::NRM, Mult::NRM},
            {Mult::NRM, Mult::TL, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::TL, Mult::NRM},
            {Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::DW, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM, Mult::DW, Mult::NRM, Mult::NRM, Mult::NRM, Mult::NRM},
            {Mult::DL, Mult::NRM, Mult::NRM, Mult::DW, Mult::NRM, Mult::NRM, Mult::NRM, Mult::DL, Mult::NRM, Mult::NRM, Mult::NRM, Mult::DW, Mult::NRM, Mult::NRM, Mult::DL},
            {Mult::NRM, Mult::NRM, Mult::DW, Mult::NRM, Mult::NRM, Mult::NRM, Mult::DL, Mult::NRM, Mult::DL, Mult::NRM, Mult::NRM, Mult::NRM, Mult::DW, Mult::NRM, Mult::NRM},
            {Mult::NRM, Mult::DW, Mult::NRM, Mult::NRM, Mult::NRM, Mult::TL, Mult::NRM, Mult::NRM, Mult::NRM, Mult::TL, Mult::NRM, Mult::NRM, Mult::NRM, Mult::DW, Mult::NRM},
            {Mult::TW, Mult::NRM, Mult::NRM, Mult::DL, Mult::NRM, Mult::NRM, Mult::NRM, Mult::TW, Mult::NRM, Mult::NRM, Mult::NRM, Mult::DL, Mult::NRM, Mult::NRM, Mult::TW}
    };
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
