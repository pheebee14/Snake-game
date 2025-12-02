#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>

std::vector<std::vector<char>> build_board(const int& row, const int& columns);
void print_board(const std::vector<std::vector<char>>& given_board);
void draw_snake(std::vector<std::vector<char>>& given_board, const int& row, const int& columns)

struct Coordinates {
    int row;
    int column;
}

int main () {
    int rows = 20;
    int columns = 20;

    std::vector<std::vector<char>> board = build_board(rows, columns);

        while(true){
        print_board(board);
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        std::system("clear");
        }

    return 0;
}

std::vector<std::vector<char>> build_board(const int& row, const int& columns) {

    std::vector<std::vector<char>> matrix;
    for (int i = 0; i < row; i++){
        std::vector<char> row_or_column;
        for (int j = 0; j < columns; j++){
            if (i == 0 || i == row - 1 || j == 0 || j == columns - 1){
                row_or_column.push_back('#');
            } else {
                row_or_column.push_back(' ');
            }
        }

        matrix.push_back(row_or_column);
    }

    return matrix;
}

void print_board(const std::vector<std::vector<char>>& given_board){
    for (int i = 0; i < given_board.size(); i++){
        for (int j = 0; j < given_board[0].size(); j++){
            std::cout << given_board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void draw_snake(std::vector<std::vector<char>>& given_board, const int& row, const int& columns){

}