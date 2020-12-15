#include <iostream>
#include <cstdio>
#include <string>
#include <chrono>
#include <ctime>
#include "sudoku.h"

using namespace std;
using namespace  std::chrono;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============" << "\n\n";

  cout << "Calling load_board():" << '\n';
  load_board("easy.dat", board);

  cout << '\n' << "Displaying Sudoku board with display_board():" << '\n';
  display_board(board);
  cout << "Done!" << "\n\n";

  cout << "=================== Question 1: Is board complete? ===================" << "\n\n";

  load_board("easy.dat", board);
  
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << "\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << "\n\n";

  cout << "=================== Question 2: Is move valid? ===================" << "\n\n";

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);
 
  // WRONG as same number in column
  cout << "Putting '6' into A2 is ";
  if (!make_move("A2", '6', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // WRONG as same number in row
  cout << "Putting '3' into F5 is ";
  if (!make_move("F5", '3', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // WRONG as same number in square
  cout << "Putting '7' into G5 is ";
  if (!make_move("G5", '7', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);
 

  cout << "=================== Question 3: Saving our board ===================" << "\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board))
    cout << "Save board to 'easy-copy.dat' successful." << '\n';
  else
    cout << "Save board failed." << '\n';
  cout << '\n';

  cout << "=================== Question 4: Solving the Sudoku ===================" << "\n\n";

  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << '\n';
    display_board(board);
  } else 
    cout << "A solution cannot be found." << '\n';
  cout << "\n";

  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << '\n';
    display_board(board);
  } else 
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  cout << "=================== Question 5: Investigating 3 other boards  ===================" << "\n\n";

  /*===============================Mystery 1 board===============================*/
  load_board("mystery1.dat", board);

  auto start_timer1 = high_resolution_clock::now();
  if (solve_board(board)) {
    cout << "The Mystery1 board has a solution:" << '\n';
    display_board(board);
  } else 
    cout << "A solution cannot be found." << '\n';
  cout << '\n';
  auto stop_timer1 = high_resolution_clock::now();
  auto duration_timer1 = duration_cast<milliseconds>(stop_timer1 - start_timer1);
  cout << "Finished computation of Mystery1 in: " << duration_timer1.count() << " ms.\n\n\n";

  /*===============================Mystery 2 board===============================*/
  load_board("mystery2.dat", board);

  auto start_timer2 = high_resolution_clock::now();
  if (solve_board(board)) {
    cout << "The Mystery2 board has a solution:" << "\n";
    display_board(board);
  } else 
    cout << "A solution cannot be found." << '\n';
  cout << '\n';
  auto stop_timer2 = high_resolution_clock::now();
  auto duration_timer2 = duration_cast<milliseconds>(stop_timer2 - start_timer2);
  cout << "Finished computation of Mystery2 in: " << duration_timer2.count() << " ms.\n\n\n";
  
  /*===============================Mystery 3 board===============================*/
  load_board("mystery3.dat", board);

  auto start_timer3 = high_resolution_clock::now();
  if (solve_board(board)) {
    cout << "The Mystery3 board has a solution:" << '\n';
    display_board(board);
  } else 
    cout << "A solution cannot be found." << '\n';
  cout << '\n';
  auto stop_timer3 = high_resolution_clock::now();
  auto duration_timer3 = duration_cast<milliseconds>(stop_timer3 - start_timer3);
  cout << "Finished computation of Mystery3 in: " << duration_timer3.count() << " ms.\n\n\n";
  
  return 0;
  
  }
