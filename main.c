#include "saper.h"
#include <ncurses.h>

int MAX_ROWS, MAX_COLS, MINES;

int main(int argc, char* argv[])
{
    MAX_ROWS = strtol(argv[1], NULL, 10);
    MAX_COLS = strtol(argv[2], NULL, 10);
    MINES = strtol(argv[3], NULL, 10);

    start(MAX_ROWS, MAX_COLS, MINES);
    if (too_much_bombs(MAX_ROWS, MAX_COLS, MINES))
        return 0;

    int slim = 0;
    if (argc == 5)
        if (strcmp(argv[4], "--slim") == 0)
            slim = 1;

    initscr();
    curs_set(0);
    initialize_colors();
    keypad(stdscr, TRUE);
    srand(time(FALSE));

    char board[MAX_ROWS][MAX_COLS];
    int rows = MAX_ROWS;
    int cols = MAX_COLS;
    int mines = MINES;
    int b_flagi;
    int sap[MAX_ROWS][MAX_COLS];
    int to[MAX_ROWS][MAX_COLS];
    int row, col;
    
    setup_board(board, sap, to, rows, cols, mines);
    getyx(stdscr, row, col);

    while (1 != 0) {
        draw_board(board, rows, cols, row, col, slim, sap);

        int action = wgetch(stdscr);

        if (action == KEY_LEFT && col > 0) {
            col--;
        } else if (action == KEY_RIGHT && col < cols - 1) {
            col++;
        } else if (action == KEY_UP && row > 0) {
            row--;
        } else if (action == KEY_DOWN && row < rows - 1) {
            row++;
        }

        if (uncovered(board) == 0 && action == ' ' && sap[row][col] == 9) {
            zero_move(row, col, sap, board, rows, cols);
        }

        if (action == ' ' && sprawdz(row, col, sap, board)) {
            draw_board(board, rows, cols, row, col, slim, sap);
            gameover();
            end();
            return 0;
        }
        update_board(board, sap, to, rows, cols, &row, &col, action);

        if (czy_koniec(b_flagi, board) == MAX_COLS * MAX_ROWS - MINES) {
            draw_board(board, rows, cols, row, col, slim, sap);
            win();
            end();
            return 0;
        }
    }
}