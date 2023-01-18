#include "saper.h"

int main(int argc, char* argv[])
{

    char* temp;
    int slim = 0;
    if (argc == 5) {
        temp = input(argv);
        if (strcmp(temp, "--slim") == 0)
            slim = 1;
    }

    char* a;
    char* b;
    char* c;
    MAX_ROWS = strtol(argv[1], &a, 10);
    MAX_COLS = strtol(argv[2], &b, 10);
    MINES = strtol(argv[3], &c, 10);

    if ((a == NULL) || (a[0] != '\0') || (b == NULL) || (b[0] != '\0') || (c == NULL) || (c[0] != '\0')) {
        printf("You are writing garbage\n");
        return 0;
    }

    start(MAX_ROWS, MAX_COLS, MINES);
    if (too_much_bombs(MAX_ROWS, MAX_COLS, MINES))
        return 0;


    initscr();
    curs_set(0);
    initialize_colors();
    keypad(stdscr, TRUE);
    srand(time(FALSE));

    char board[MAX_ROWS][MAX_COLS];
    int rows = MAX_ROWS;
    int cols = MAX_COLS;
    int mines = MINES;
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
            zero_move(row, col, sap, rows, cols);
        }

        if (action == ' ' && sprawdz(row, col, sap, board)) {
            draw_board(board, rows, cols, row, col, slim, sap);
            gameover();
            end();
            return 0;
        }

        if (action == ' ' && board[row][col] > '0' && board[row][col] < 9 + '0') {
            if (new_function(board, sap, row, col, to)) {
                draw_board(board, rows, cols, row, col, slim, sap);
                gameover();
                end();
                return 0;
            }
        }

        update_board(board, sap, to, &row, &col, action);

        if (czy_koniec(board) == MAX_COLS * MAX_ROWS - MINES) {
            draw_board(board, rows, cols, row, col, slim, sap);
            win();
            end();
            return 0;
        }
    }
}