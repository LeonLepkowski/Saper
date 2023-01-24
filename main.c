#include "saper.h"

int main(int argc, char* argv[])
{
    int MAX_ROWS, MAX_COLS, MINES;
    // if(argc != 2 && argc != 5){
    //     printf("Try again!\n");
    //     return 0;
    // }
    if(argc == 10) return 0;

    if (strcmp(argv[1], "--beginner") == 0) {
        MAX_ROWS = 9;
        MAX_COLS = 9;
        MINES = 10;
    }

    if (strcmp(argv[1], "--intermediate") == 0) {
        MAX_ROWS = 16;
        MAX_COLS = 16;
        MINES = 40;
    }

    if (strcmp(argv[1], "--expert") == 0) {
        MAX_ROWS = 16;
        MAX_COLS = 30;
        MINES = 99;
    }

    if (strcmp(argv[1], "--custom") == 0) {
        char* a;
        char* b;
        char* c;
        MAX_ROWS = strtol(argv[2], &a, 10);
        MAX_COLS = strtol(argv[3], &b, 10);
        MINES = strtol(argv[4], &c, 10);
        if ((a[0] != '\0') || (b[0] != '\0') || (c[0] != '\0')) {
            printf("You are writing garbage\n");
            return 0;
        }
        
    }




    // char* temp;
    int slim = 0;
    // if (argc == 5) {
    //     temp = input(argv);
    //     if (strcmp(temp, "--slim") == 0)
    //         slim = 1;
    // }

    if (too_much_bombs(MAX_ROWS, MAX_COLS, MINES))
        return 0;

    initscr();
    curs_set(0);
    noecho();
    initialize_colors();
    keypad(stdscr, TRUE);
    srand(time(FALSE));

    char board[INDEX][INDEX];
    int sap[INDEX][INDEX];
    int to[INDEX][INDEX];
    int row, col;

    setup_board(board, sap, to, MAX_ROWS, MAX_COLS);
    getyx(stdscr, row, col);

    int yMAX, xMAX;
    getmaxyx(stdscr, yMAX, xMAX);
    printw("%i, %i, %i, %i\n", yMAX, xMAX, MAX_ROWS, MAX_COLS);
    if(MAX_ROWS > yMAX - 1 || MAX_COLS > xMAX/2 -1) {
        endwin();
        printf("Values are too big for your terminal to handle\n");
        return 0;
    }

    while (1 != 0) {
        draw_board(board, row, col, slim, sap, MAX_ROWS, MAX_COLS, MINES);

        int action = wgetch(stdscr);
        if(action == 27) {
            endwin();
            return 0;
        }

        if (action == KEY_LEFT && col > 0) {
            col--;
        } else if (action == KEY_RIGHT && col < MAX_COLS-1) {
            col++;
        } else if (action == KEY_UP && row > 0) {
            row--;
        } else if (action == KEY_DOWN && row < MAX_ROWS -1) {
            row++;
        }

        if (action == '8' && row > 0) {
            row--;
        } else if (action == '4' && col > 0) {
            col--;
        } else if (action == '6' && col < MAX_COLS -1) {
            col++;
        } else if (action == '2' && row < MAX_ROWS -1) {
            row++;
        } else if (action == '7') {
            if(row > 0) row--;
            if(col > 0) col--;
        } else if (action == '9') {
            if(row > 0) row--;
            if(col < MAX_COLS -1) col++;
        } else if (action == '1') {
            if (row < MAX_ROWS -1) row++;
            if (col > 0) col--;
        } else if (action == '3') {
            if (row < MAX_ROWS -1) row++;
            if (col < MAX_COLS -1) col++;
        }


        if (uncovered(board, MAX_ROWS, MAX_COLS) == 0 && (action == ' ' || action == 'f')) {
            bombs_generator(row, col, sap, MAX_ROWS, MAX_COLS, MINES);
        }

        if (action == ' ' && sprawdz(row, col, sap, board, MAX_ROWS, MAX_COLS)) {
            draw_board(board, row, col, slim, sap, MAX_ROWS, MAX_COLS, MINES);
            gameover();
            end();
            return 0;
        }

        if (action == ' ' && board[row][col] > '0' && board[row][col] < 9 + '0') {
            if (new_function(board, sap, row, col, to, MAX_ROWS, MAX_COLS)) {
                draw_board(board, row, col, slim, sap, MAX_ROWS, MAX_COLS, MINES);
                gameover();
                end();
                return 0;
            }
        }

        update_board(board, sap, to, &row, &col, action, MAX_ROWS, MAX_COLS, MINES);

        if (czy_koniec(board, MAX_ROWS, MAX_COLS) == MAX_COLS * MAX_ROWS - MINES) {
            draw_board(board, row, col, slim, sap, MAX_ROWS, MAX_COLS, MINES);
            win();
            end();
            return 0;
        }
    }
}
