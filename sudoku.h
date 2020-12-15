/* Header file for Sudoku.cpp */
#ifndef SUDOKU_H
#define SUDOKU_H

#include <string>
#include <iostream>
using namespace std;

/* Function to load sudoku board */
void load_board(const char* filename, char board[9][9]);

/* Function to display sudoku board appropriately */
void display_board(const char board[9][9]);

/* Function to check the sudoku board is complete (not necessarily with correct answers) */
bool is_complete(char board[9][9]);

/* Function to check if a move on the board is valid */
bool make_move(string position, char digit, char board[9][9]);

/* Function to save the sudoku board to a data file */
bool save_board(const char* filename, char board[9][9]);

/* Function to solve sudoku board recursively */
bool solve_board(char board[9][9]);

#endif
