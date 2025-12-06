#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <ctime>
#include <ncurses.h>
#include <string>

// Scroll wheel issue (fix soon).

enum Direction 
{
    up,
    down,
    left,
    right,
    pause,
    none
};

struct Coordinates {
    int row;
    int column;
};

struct Snake_body {
    std::vector<Coordinates> segments;
};

std::vector<std::vector<char>> build_board(const int& row, const int& columns);
void print_board(const std::vector<std::vector<char>>& given_board);
bool can_draw_snake(std::vector<std::vector<char>>& given_board, Snake_body& segments, int& rows, int& columns);
void snake_movement(Direction& current_dir, int& ch, Snake_body& segments);
void spawn_food(std::vector<std::vector<char>>& given_board, int& rows, int& columns);

int main () {

    srand(static_cast<unsigned int>(time(0)));

    int rows {20};
    int columns {20};
    int initial_size {3};
    std::string start_game;

    std::vector<std::vector<char>> board {build_board(rows, columns)};
    
    Snake_body segments;
    segments.segments.resize(initial_size);
    Direction current_dir {none};

    std::cout << "Welcome to snake." << std::endl;
    std::cout << "*********************" << std::endl;
    while(start_game != "OK"){
        std::cout << "Ready to start? (OK): ";
        std::cin >> start_game;
    }

    initscr();
    raw();
    noecho();

    int ch;
    bool eliminated = false;
    int score = 0;

    for (int i = 0; i < initial_size; i++){
        segments.segments[i].row = rows / 2;
        segments.segments[i].column = (columns / 2) - i;
    }

        while(!eliminated){
            std::vector<std::vector<char>> frame = board;

            bool Valid_drawing = can_draw_snake(frame, segments, rows, columns);
            if (!Valid_drawing){
                break;
            }
            spawn_food(frame, rows, columns);
            print_board(frame);
            refresh();
            snake_movement(current_dir, ch, segments);

            std::string current_score = "CURRENT SCORE: " + std::to_string(score);

            mvprintw(frame.size() + 1, 0, "P to pause game! WASD to move!");
            mvprintw(frame.size() + 2, 0, ("%s", current_score.c_str()));

            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }

    endwin();

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
            mvaddch(i, j * 2, given_board[i][j]);
        }
    }
}

bool can_draw_snake(std::vector<std::vector<char>>& given_board, Snake_body& segments, int& rows, int& columns){
    for (auto& member_body : segments.segments){
        if (given_board[member_body.row][member_body.column] == '#'){
            return false;
        } else {
            given_board[member_body.row][member_body.column] = 'o';
        }
    }

    return true;
}

void snake_movement(Direction& current_dir, int& ch, Snake_body& segments){
    ch = getch();

    switch(ch){
        case 'w': case 'W': current_dir = up; break;
        case 'a': case 'A': current_dir = left; break;
        case 's': case 'S': current_dir = down; break;
        case 'd': case 'D': current_dir = right; break;
        case 'p': case 'P': current_dir = pause; break;
        default: break;
    }

    Coordinates Previous_Part = segments.segments[0];

    switch(current_dir){
        case up: segments.segments[0].row--; break;
        case down: segments.segments[0].row++; break;
        case left: segments.segments[0].column--; break;
        case right: segments.segments[0].column++; break;
        case pause: break;
        default: break;
    }

    for (int i = 1; i < segments.segments.size(); i++){
        Coordinates Current_part = segments.segments[i];
        segments.segments[i] = Previous_Part;
        Previous_Part = Current_part;
    }
}

void spawn_food(std::vector<std::vector<char>>& given_board, int& rows, int& columns){
    // fix snake spawn food function, add more onto it.
    int random_row = rand() % (rows - 2) + 1;
    int random_column = rand() % (columns - 2) + 1;

    if (given_board[random_row][random_column] == ' '){
        given_board[random_row][random_column] = 'A';
    }
}
