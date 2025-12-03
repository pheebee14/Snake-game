#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>

/*
    Enum class for movement.
*/

struct Coordinates {
    int row;
    int column;
};

struct Snake_body {
    std::vector<Coordinates> segments;
};

std::vector<std::vector<char>> build_board(const int& row, const int& columns);
void print_board(const std::vector<std::vector<char>>& given_board);
void draw_snake(std::vector<std::vector<char>>& given_board, Snake_body& segments, int& rows, int& columns);
void snake_movement();

int main () {
    int rows {20};
    int columns {20};
    int initial_size {3};

    /*
    SAVE FOR SESSION ON LAST HOUR: FIGURE OUT HOW TO IMPLEMENT VECTOR OF COORDINATES THROUGH STRUCT,
    AND PASS THIS AS THE SNAKE'S BODY?
    */

    std::vector<std::vector<char>> board {build_board(rows, columns)};
    
    Snake_body segments;
    segments.segments.resize(initial_size);

    for (int i = 0; i < initial_size; i++){
        segments.segments[i].row = rows / 2;
        segments.segments[i].column = (columns / 2) - i;
    }

        while(true){
        std::vector<std::vector<char>> frame = board;

        draw_snake(frame, segments, rows, columns);

        print_board(frame);

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

void draw_snake(std::vector<std::vector<char>>& given_board, Snake_body& segments, int& rows, int& columns){
    for (auto& member_body : segments.segments){
        given_board[member_body.row][member_body.column] = 'o';
    }
}

void snake_movement(){
    // Using enum class for movement, produce switch cases for movement.
}
