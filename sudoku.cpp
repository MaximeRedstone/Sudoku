/* Implementation file for sudoku */

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <string>
#include "sudoku.h"


using namespace std;
using std::string;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";
  
  ifstream in(filename);
  if (!in)
    cout << "Failed!" << '\n';
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << '\n';
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/*=================== Question 1: Is board complete? ===================*/

/* Function to check if a Sudoku board is complete */
/* (not necessarily valid) */
bool is_complete(char board[9][9]) {
  int row = 0;
  bool answer = true;
  while (row < 9) {
    for (int n=0; n<9; n++) {
      if (isdigit(board[row][n]) == 0 || board[row][n] > 57 || board[row][n] < 49) {
	answer = false;
      }
    }
    row++;
  }
  return answer;
}

/*=================== Question 2: Is move valid? ===================*/

/* Helper function to check if digit is already in row */
bool in_row(int row, char digit, char board[9][9]) {  
  for (int count = 0; count < 9; count++) {
    // position in array is position on screen minus 1
    if (board[row - 1][count] == digit) {
      return true;
    }
  }
  return false;
}

/* Helper function to check if digit is already in column */
bool in_column(int column, char digit, char board[9][9]) {
  for (int count = 0; count < 9; count++) {
    // position in array is position on screen minus 1
    if (board[count][column - 1] == digit) {
      return true;
    }
  }
  return false;
}

/* Function returning rows or columns of a square in Sudoku board */
/* Based on an input position */
void get_square_coordinates(int array[3], int coordinate) {

  if (coordinate % 3 == 0) {
    array[0] = coordinate - 2;
    array[1] = coordinate - 1;
    array[2] = coordinate;
  }
  else if (coordinate % 3 == 2) {
    array[0] = coordinate - 1;
    array[1] = coordinate;
    array[2] = coordinate + 1;
  }
  else if (coordinate % 3 == 1) {
    array[0] = coordinate;
    array[1] = coordinate + 1;
    array[2] = coordinate + 2;
  }
  
}
/* Helper function to check if digit is already in square. */
/* Here we use the different remainders of numbers 1 to 9 by 3 */
bool in_square(int row, int column, char digit, char board[9][9]) {

  // 3x3 square of interest
  int other_column[3], other_row[3];
  get_square_coordinates(other_column, column);
  get_square_coordinates(other_row, row);

  // Check all positions in 3x3 square for digit
  for (int count_row = 0; count_row < 3; count_row++) {
    for (int count_column = 0; count_column < 3; count_column++) {
      if (board[other_row[count_row] - 1][other_column[count_column] - 1] == digit) {
	return true;
      }
    }
  }
  return false;
}

/* Helper function to check if the move is allowed - without changing value on board */
bool move_allowed(string position, char digit, char board[9][9]) {

  // checking the input row is in range (A - I)
  int row_position;
  if (position.at(0) >= 'a' && position.at(0) <= 'i')
    row_position = (int) position.at(0) - 96;
  else if (position.at(0) >= 'A' && position.at(0) <= 'I')
    row_position = (int) position.at(0)- 64;
  else {
    return false;
  }

  // and input column (1 - 9)
  int column_position = (int) position.at(1) - 48;
  if (column_position < 0 && column_position > 9) {
    return false;
  }

  // and input digit (1 - 9)
  if (digit < 49 && digit > 57) {
    return false;
  }

  /* checking the digit at this position is valid */
  if (in_row(row_position, digit, board) == false && in_column(column_position, digit, board) == false && in_square(row_position, column_position, digit, board) == false) {
    //cout << " Digit that works is: " << static_cast<int>(digit) << endl;
    return true;
  }
  return false;
}

/* Function to check if move is valid */
bool make_move(string position, char digit, char board[9][9]) {
  
  // assign row and column position based on user input
  int row_position;
  if (position.at(0) >= 'a' && position.at(0) <= 'i')
    row_position = (int) position.at(0) - 96;
  else if (position.at(0) >= 'A' && position.at(0) <= 'I')
    row_position = (int) position.at(0)- 64;
  
  int column_position = (int) position.at(1) - 48;

  // modify value on board if valid
  if (move_allowed(position, digit, board)) {
      board[row_position - 1][column_position - 1] = digit;
      return true;
  }
  return false;
}

/*=================== Question 3: Saving our board ===================*/

/* Function to save the board to a file */
bool save_board(const char* filename, char board[9][9]) {

  // Check output stream failed
  ofstream out(filename);
  if (!out){
    cout << "Failed!" << '\n';
    return false;
  }

  // Write digit or dot to file
  int row = 0;
  while (row < 9) {
    for (int n=0; n<9; n++) {
      assert(board[row][n] == '.' || isdigit(board[row][n]));
      out << board[row][n];
  }
    out << endl;
    row++;
  }

  if (row != 9) {
    return false;
  }
  out.close();

  return true;
}

/*=================== Question 4: Solving the Sudoku ===================*/

/* Function to solve the Sudoku (recursive) */
bool solve_board(char board[9][9]) {

  // quit if board is finished
  if (is_complete(board) == true) {
    return true;
  }

  string column_names = "123456789";
  string row_names = "ABCDEFGHI";
  
  for (int row_count = 0; row_count < 9; row_count++) {
     for (int column_count = 0; column_count < 9; column_count++) {

       // Go through all the cells on the board
       string coordinates;
       coordinates.append(row_names, row_count, 1);
       coordinates.append(column_names, column_count, 1);
       
       // Check if digit exists
       if (board[row_count][column_count] == '.') {
	 
	 // If does not exist then attempt finding a solution
	 for (char digit = 49; digit <= 57; digit++) {
	   
	    // If move allowed, place digit
	    if (move_allowed(coordinates, digit, board)) {
	      board[row_count][column_count] = digit;
	      // If board solved, quit
	      if (solve_board(board))
		return true;
	    }
	    // If not allowed then put dot in cell
	    board[row_count][column_count] = '.';
	 }
	 // If all 9 numbers not allowed, then previous number must be wrong.
	 // Exit that recursion and try other number
	 return false;
       }
     }
  }
  display_board(board);
  return false;
}
