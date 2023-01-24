#include "saper.h"

int main()
{
    initscr();
    curs_set(0);
    noecho();
    initialize_colors();
    keypad(stdscr, TRUE);
    srand(time(FALSE));

    int MAX_ROWS = 9, MAX_COLS = 9, MINES = 10;

    int yMAX, xMAX;
    getmaxyx(stdscr, yMAX, xMAX);

    WINDOW* menuwin = newwin(5, 12, yMAX / 2 - 5, xMAX / 2 - 5);
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);

    keypad(menuwin, true);
    char* choices[] = { "New game", "Options", "Exit game" };
    int choice;
    int highlight = 0;
    int difficulty = 0;

    while (1) {
        while (1) {
            while (1) {
                box(menuwin, 0, 0);
                title_name(xMAX);
                for (int i = 0; i < 3; i++) {
                    erase();
                    // wrefresh(menuwin);
                    if (i == highlight)
                        wattron(menuwin, A_REVERSE);
                    mvwprintw(menuwin, i + 1, 1, choices[i]);
                    wattroff(menuwin, A_REVERSE);
                }
                choice = wgetch(menuwin);
                switch (choice) {
                case KEY_UP:
                    highlight--;
                    if (highlight == -1)
                        highlight = 0;
                    break;
                case KEY_DOWN:
                    highlight++;
                    if (highlight == 3)
                        highlight = 2;
                    break;
                default:
                    break;
                }
                if (choice == 10)
                    break;
            }
            printw("Your choice was: %s\n", choices[highlight]);

            if (strcmp(choices[highlight], "Options") == 0) {
                erase();
                options(&MAX_ROWS, &MAX_COLS, &MINES, &difficulty);
            }
            refresh();
            if (strcmp(choices[highlight], "Exit game") == 0) {
                endwin();
                return 0;
            }

            if (strcmp(choices[highlight], "New game") == 0) {
                break;
            }
        }
        erase();
        if (too_much_bombs(MAX_ROWS, MAX_COLS, MINES))
            return 0;

        char board[INDEX][INDEX];
        int sap[INDEX][INDEX];
        int to[INDEX][INDEX];
        int row, col;
        int slim = 0;

        setup_board(board, sap, to, MAX_ROWS, MAX_COLS);
        getyx(stdscr, row, col);

        while (1 != 0) {
            draw_board(board, row, col, slim, sap, MAX_ROWS, MAX_COLS, MINES);

            int action = wgetch(stdscr);
            if(action == 27) {
                erase();
                break;
            }
            if (action == KEY_LEFT) {
                col--;
                if (col == -1)
                    col = MAX_COLS - 1;
            } else if (action == KEY_RIGHT) {
                col++;
                if (col == MAX_COLS)
                    col = 0;
            } else if (action == KEY_UP) {
                row--;
                if (row == -1)
                    row = MAX_ROWS - 1;
            } else if (action == KEY_DOWN) {
                row++;
                if (row == MAX_ROWS)
                    row = 0;
            }
            if (uncovered(board, MAX_ROWS, MAX_COLS) == 0 && (action == ' ' || action == 'f')) {
                bombs_generator(row, col, sap, MAX_ROWS, MAX_COLS, MINES);
            }

            if (action == ' ' && sprawdz(row, col, sap, board, MAX_ROWS, MAX_COLS)) {
                draw_board(board, row, col, slim, sap, MAX_ROWS, MAX_COLS, MINES);
                gameover();
                end();
                clear();
                erase();
                break;
                // return 0;
            }

            if (action == ' ' && board[row][col] > '0' && board[row][col] < 9 + '0') {
                if (new_function(board, sap, row, col, to, MAX_ROWS, MAX_COLS)) {
                    draw_board(board, row, col, slim, sap, MAX_ROWS, MAX_COLS, MINES);
                    gameover();
                    end();
                    clear();
                    erase();
                    break;
                    // return 0;
                }
            }

            update_board(board, sap, to, &row, &col, action, MAX_ROWS, MAX_COLS, MINES);

            if (czy_koniec(board, MAX_ROWS, MAX_COLS) == MAX_COLS * MAX_ROWS - MINES) {
                draw_board(board, row, col, slim, sap, MAX_ROWS, MAX_COLS, MINES);
                win();
                end();
                erase();
                clear();
                break;
                // return 0;
            }
        }
    }
}
