#include <ctype.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define INDEX 100

void setup_board(char board[INDEX][INDEX], int sap[INDEX][INDEX], int to[INDEX][INDEX], int rows, int cols);
void draw_board(char board[INDEX][INDEX], int row, int col, int slim, int sap[INDEX][INDEX], int MAX_ROWS, int MAX_COLS, int MINES);
void update_board(char board[INDEX][INDEX], int sap[INDEX][INDEX], int to[INDEX][INDEX], int* row, int* col, char action, int MAX_ROWS, int MAX_COLS, int MINES);
int czy_koniec(char board[INDEX][INDEX], int MAX_ROWS, int MAX_COLS);
bool sprawdz(int a, int b, int sap[INDEX][INDEX], char board[INDEX][INDEX], int MAX_ROWS, int MAX_COLS);
int uncovered(char board[INDEX][INDEX], int MAX_ROWS, int MAX_COLS);
void initialize_colors();
void end();
bool too_much_bombs(int MAX_ROWS, int MAX_COLS, int MINES);
void gameover();
void win();
bool new_function(char board[INDEX][INDEX], int sap[INDEX][INDEX], int i, int j, int to[INDEX][INDEX], int MAX_ROWS, int MAX_COLS);
char* input(char* argv[]);
void bombs_generator(int i, int j, int sap[INDEX][INDEX], int MAX_ROWS, int MAX_COLS, int MINES);