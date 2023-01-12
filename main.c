#include <ncurses.h>
#include "saper.h"

int MAX_ROWS, MAX_COLS, MINES;

int main(int argc, char* argv[])
{
    MAX_ROWS = strtol(argv[1], NULL, 10);
    MAX_COLS = strtol(argv[2], NULL, 10);
    MINES = strtol(argv[3], NULL, 10);
    int slim = 0;
    if (argc == 5)
        if (strcmp(argv[4], "--slim") == 0)
            slim = 1;

    start(MAX_ROWS, MAX_COLS, MINES);

    // Seed the random number generator
    srand(time(0));

    // Initialize ncursed
    initscr();

    if (MINES >= MAX_COLS * MAX_ROWS) {
        printw("TOO MUCH BOMBS\n\n");
        // Wait for the user to press a key before exiting
        printw("Press any key to exit...\n");
        getch();

        // Clean up ncursed
        endwin();
        return 0;
    }

    // Iinitialize colors
    start_color();
    init_pair(1, COLOR_BLUE, A_NORMAL);
    init_pair(2, COLOR_GREEN, A_NORMAL);
    init_pair(3, COLOR_RED, A_NORMAL);
    init_pair(4, COLOR_CYAN, A_NORMAL);
    init_pair(5, COLOR_MAGENTA, A_NORMAL);
    init_pair(6, COLOR_YELLOW, A_NORMAL);
    init_pair(7, COLOR_WHITE, A_NORMAL);
    init_pair(8, COLOR_BLACK, COLOR_RED);

    // Enable the use of arrow keys
    keypad(stdscr, TRUE);

    // Set up the board
    char board[MAX_ROWS][MAX_COLS];
    int rows = MAX_ROWS;
    int cols = MAX_COLS;
    int mines = MINES;
    int move = 0;

    int b_flagi;
    int sap[MAX_ROWS][MAX_COLS];
    int to[MAX_ROWS][MAX_COLS];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            to[i][j] = 0;
        }
    }

    setup_board(board, sap, rows, cols, mines);

    // Main game loop
    int row, col;

    getyx(stdscr, row, col);
    while (1 != 0) {
        move = uncovered(board);
        // Draw the board
        draw_board(board, rows, cols, row, col, slim, sap);

        // Get the user's action
        printw("Enter action (' ' = reveal, f = mark as mine, arrow keys = move cursor): ");

        int action = wgetch(stdscr);

        // Handle arrow key input
        if (action == KEY_LEFT && col > 0) {
            col--;
        } else if (action == KEY_RIGHT && col < cols - 1) {
            col++;
        } else if (action == KEY_UP && row > 0) {
            row--;
        } else if (action == KEY_DOWN && row < rows - 1) {
            row++;
        }

        if (action == ' ' && sap[row][col] == 9 && move == 0) {
            zero_move(row, col, sap, board, rows, cols);
            move = 1;
        }

        // Update the board
        if (action == ' ') {
            if (sprawdz(row, col, sap, board)) {
                draw_board(board, rows, cols, row, col, slim, sap);
                // Wait for the user to press a key before exiting
                printw("Press any key to exit...\n");
                getch();

                // Clean up ncursed
                endwin();
                return 0;
            }
        }
        update_board(board, sap, to, rows, cols, &row, &col, action);
        if (czy_koniec(b_flagi, board) == MAX_COLS * MAX_ROWS - MINES) {
            draw_board(board, rows, cols, row, col, slim, sap);
            wygrana();
            // Wait for the user to press a key before exiting
            printw("Press any key to exit...\n");
            getch();

            // Clean up ncursed
            endwin();
            return 0;
        }
    }
}