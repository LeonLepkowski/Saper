#include "saper.h"

void gen(int i, int j, int sap[MAX_ROWS][MAX_COLS]);
void saper(int a, int b, char board[MAX_ROWS][MAX_COLS], int sap[MAX_ROWS][MAX_COLS], int to[MAX_ROWS][MAX_COLS]);
void colors(char board[MAX_ROWS][MAX_COLS], int i, int j, int sap[MAX_ROWS][MAX_COLS]);
void colors_slim(char board[MAX_ROWS][MAX_COLS], int i, int j, int sap[MAX_ROWS][MAX_COLS]);

void start(int a, int b, int c)
{
    MAX_ROWS = a;
    MAX_COLS = b;
    MINES = c;
}

void setup_board(char board[MAX_ROWS][MAX_COLS], int sap[MAX_ROWS][MAX_COLS], int to[MAX_ROWS][MAX_COLS], int rows, int cols, int mines)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            board[i][j] = '+';
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sap[i][j] = 0;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            to[i][j] = 0;
        }
    }

    int mines_placed = 0;
    while (mines_placed < mines) {
        int row = rand() % rows;
        int col = rand() % cols;
        if (sap[row][col] != 9) {
            sap[row][col] = 9;
            gen(row, col, sap);
            mines_placed++;
        }
    }
}

void draw_board(char board[MAX_ROWS][MAX_COLS], int rows, int cols, int row, int col, int slim, int sap[MAX_ROWS][MAX_COLS])
{
    clear();

    printw(" ");
    for (int i = 0; i < cols; i++) {
        printw("  ");
    }
    printw("\n");

void setup_board(char board[MAX_ROWS][MAX_COLS], int sap[MAX_ROWS][MAX_COLS], int rows, int cols, int mines)
{
    // Initialize the board to all blank spaces
    for (int i = 0; i < rows; i++) {
        printw(" ");

        for (int j = 0; j < cols; j++) {
            if (i == row && j == col) {
                attron(A_STANDOUT);
                if(board[i][j] == '@') attron(COLOR_PAIR(9));
            }
            if (slim == 0) {
                colors(board, i, j, sap);
            } else {
                colors_slim(board, i, j, sap);
            }
            if (i == row && j == col) {
                attroff(A_STANDOUT);
                if(board[i][j] == '@') attroff(COLOR_PAIR(9));
            }
        }
        printw("\n");
    }
    printw("\n");
}

void update_board(char board[MAX_ROWS][MAX_COLS], int sap[MAX_ROWS][MAX_COLS], int to[MAX_ROWS][MAX_COLS], int rows, int cols, int* row, int* col, char action)
{
    if (action == 'f' && board[*row][*col] == '+') {
        board[*row][*col] = 'F';
    } else if (action == 'f' && board[*row][*col] == 'F') {
        board[*row][*col] = '+';
    } else if (action == ' ' && board[*row][*col] != 'F') {
        saper(*row, *col, board, sap, to);
    }
}

void gen(int i, int j, int sap[MAX_ROWS][MAX_COLS]) // Dodaje 1 wszystkim polom na około współrzędej (x,y)
{
    if (sap[i + 1][j + 1] != 9 && i + 1 < MAX_ROWS && j + 1 < MAX_COLS)
        sap[i + 1][j + 1] += 1;
    if (sap[i - 1][j - 1] != 9 && i - 1 >= 0 && j - 1 >= 0)
        sap[i - 1][j - 1] += 1;
    if (sap[i - 1][j + 1] != 9 && i - 1 >= 0 && j + 1 < MAX_COLS)
        sap[i - 1][j + 1] += 1;
    if (sap[i + 1][j - 1] != 9 && i + 1 < MAX_ROWS && j - 1 >= 0)
        sap[i + 1][j - 1] += 1;
    if (sap[i + 1][j] != 9 && i + 1 < MAX_ROWS)
        sap[i + 1][j] += 1;
    if (sap[i][j + 1] != 9 && j + 1 < MAX_COLS)
        sap[i][j + 1] += 1;
    if (sap[i - 1][j] != 9 && i - 1 >= 0)
        sap[i - 1][j] += 1;
    if (sap[i][j - 1] != 9 && j - 1 >= 0)
        sap[i][j - 1] += 1;
}

int czy_koniec(int b_flagi, char board[MAX_ROWS][MAX_COLS]) // Zlicza wyświetlone miejsca
{
    b_flagi = 0;
    for (int i = 0; i < MAX_ROWS; ++i) {
        for (int j = 0; j < MAX_COLS; ++j) {
            if (board[i][j] >= '0' && board[i][j] < 9 + '0') {
                b_flagi++;
            }
        }
    }
    return b_flagi;
}

void saper(int a, int b, char board[MAX_ROWS][MAX_COLS], int sap[MAX_ROWS][MAX_COLS], int to[MAX_ROWS][MAX_COLS])
{
    int p[16] = { 1, 1, -1, -1, -1, 1, 1, -1, 1, 0, 0, 1, -1, 0, 0, -1 };
    for (int k = 0; k < 16; k += 2) {
        if (a + p[k] >= 0 && a + p[k] < MAX_ROWS && b + p[k + 1] >= 0 && b + p[k + 1] < MAX_COLS) {
            if (board[a + p[k]][b + p[k + 1]] == '+') {
                if (sap[a + p[k]][b + p[k + 1]] == 0 && to[a + p[k]][b + p[k + 1]] == 0) {
                    to[a + p[k]][b + p[k + 1]] = 1;
                    saper(a + p[k], b + p[k + 1], board, sap, to);
                }
                if (board[a + p[k]][b + p[k + 1]] != 'F' && sap[a][b] == 0) {
                    board[a + p[k]][b + p[k + 1]] = sap[a + p[k]][b + p[k + 1]] + '0';
                }
            }
        }
    }
    board[a][b] = sap[a][b] + '0';
}

bool sprawdz(int a, int b, int sap[MAX_ROWS][MAX_COLS], char board[MAX_ROWS][MAX_COLS])
{
    if (sap[a][b] == 9 && board[a][b] != 'F') {
        for (int i = 0; i < MAX_ROWS; i++) {
            for (int j = 0; j < MAX_COLS; j++) {
                if (sap[i][j] == 9)
                    board[i][j] = '@';
            }
        }
        return true;
    }
    return false;
}

void colors(char board[MAX_ROWS][MAX_COLS], int i, int j, int sap[MAX_ROWS][MAX_COLS])
{
    if (board[i][j] == '1') {
        attron(COLOR_PAIR(1));
        printw(" %c", board[i][j]);
        attroff(COLOR_PAIR(1));
    } else if (board[i][j] == '2') {
        attron(COLOR_PAIR(2));
        printw(" %c", board[i][j]);
        attroff(COLOR_PAIR(2));
    } else if (board[i][j] == '3') {
        attron(COLOR_PAIR(3));
        printw(" %c", board[i][j]);
        attroff(COLOR_PAIR(3));
    } else if (board[i][j] == '4') {
        attron(COLOR_PAIR(4));
        printw(" %c", board[i][j]);
        attroff(COLOR_PAIR(4));
    } else if (board[i][j] == '5') {
        attron(COLOR_PAIR(5));
        printw(" %c", board[i][j]);
        attroff(COLOR_PAIR(5));
    } else if (board[i][j] == '6') {
        attron(COLOR_PAIR(6));
        printw(" %c", board[i][j]);
        attroff(COLOR_PAIR(6));
    } else if (board[i][j] == 'F') {
        attron(COLOR_PAIR(6));
        printw(" %c", board[i][j]);
        attroff(COLOR_PAIR(6));
    } else if (board[i][j] == '0') {
        printw("  ");
    } else if (board[i][j] == '8') {
        printw(" %c", board[i][j]);
    } else if (board[i][j] == '+') {
        printw(" +");
    } else if (board[i][j] == '@') {
        attron(COLOR_PAIR(8));
        printw(" @");
        attroff(COLOR_PAIR(8));
    } else
        printw(" %c", board[i][j]);
}

void colors_slim(char board[MAX_ROWS][MAX_COLS], int i, int j, int sap[MAX_ROWS][MAX_COLS])
{
    if (board[i][j] == '1') {
        attron(COLOR_PAIR(1));
        printw("%c", board[i][j]);
        attroff(COLOR_PAIR(1));
    } else if (board[i][j] == '2') {
        attron(COLOR_PAIR(2));
        printw("%c", board[i][j]);
        attroff(COLOR_PAIR(2));
    } else if (board[i][j] == '3') {
        attron(COLOR_PAIR(3));
        printw("%c", board[i][j]);
        attroff(COLOR_PAIR(3));
    } else if (board[i][j] == '4') {
        attron(COLOR_PAIR(4));
        printw("%c", board[i][j]);
        attroff(COLOR_PAIR(4));
    } else if (board[i][j] == '5') {
        attron(COLOR_PAIR(5));
        printw("%c", board[i][j]);
        attroff(COLOR_PAIR(5));
    } else if (board[i][j] == '6') {
        attron(COLOR_PAIR(6));
        printw("%c", board[i][j]);
        attroff(COLOR_PAIR(6));
    } else if (board[i][j] == 'F') {
        attron(COLOR_PAIR(6));
        printw("%c", board[i][j]);
        attroff(COLOR_PAIR(6));
    } else if (board[i][j] == '0') {
        printw(" ");
    } else if (board[i][j] == '8') {
        printw("%c", board[i][j]);
    } else if (board[i][j] == '+') {
        printw("+");
    } else if (board[i][j] == '@') {
        attron(COLOR_PAIR(8));
        printw("@");
        attroff(COLOR_PAIR(8));
    } else
        printw("%c", board[i][j]);
}

void zero_move(int i, int j, int sap[MAX_ROWS][MAX_COLS], int board[MAX_ROWS][MAX_COLS], int rows, int cols)
{
    sap[i][j] = 0;
    if (i + 1 < MAX_ROWS && j + 1 < MAX_COLS && sap[i + 1][j + 1] != 9)
        sap[i + 1][j + 1] -= 1;
    if (i - 1 >= 0 && j - 1 >= 0 && sap[i - 1][j - 1] != 9)
        sap[i - 1][j - 1] -= 1;
    if (i - 1 >= 0 && j + 1 < MAX_COLS && sap[i - 1][j + 1] != 9)
        sap[i - 1][j + 1] -= 1;
    if (i + 1 < MAX_ROWS && j - 1 >= 0 && sap[i + 1][j - 1] != 9)
        sap[i + 1][j - 1] -= 1;
    if (i + 1 < MAX_ROWS && sap[i + 1][j] != 9)
        sap[i + 1][j] -= 1;
    if (j + 1 < MAX_COLS && sap[i][j + 1] != 9)
        sap[i][j + 1] -= 1;
    if (i - 1 >= 0 && sap[i - 1][j] != 9)
        sap[i - 1][j] -= 1;
    if (j - 1 >= 0 && sap[i][j - 1] != 9)
        sap[i][j - 1] -= 1;

    if (i + 1 < MAX_ROWS && j + 1 < MAX_COLS && sap[i + 1][j + 1] == 9)
        sap[i][j] += 1;
    if (i - 1 >= 0 && j - 1 >= 0 && sap[i - 1][j - 1] == 9)
        sap[i][j] += 1;
    if (i - 1 >= 0 && j + 1 < MAX_COLS && sap[i - 1][j + 1] == 9)
        sap[i][j] += 1;
    if (i + 1 < MAX_ROWS && j - 1 >= 0 && sap[i + 1][j - 1] == 9)
        sap[i][j] += 1;
    if (i + 1 < MAX_ROWS && sap[i + 1][j] == 9)
        sap[i][j] += 1;
    if (j + 1 < MAX_COLS && sap[i][j + 1] == 9)
        sap[i][j] += 1;
    if (i - 1 >= 0 && sap[i - 1][j] == 9)
        sap[i][j] += 1;
    if (j - 1 >= 0 && sap[i][j - 1] == 9)
        sap[i][j] += 1;

    int mines_placed = 0;
    int row, col;
    while (mines_placed < 1) {
        int row = rand() % rows;
        int col = rand() % cols;
        if (sap[row][col] != 9 && row != i && col != j) {
            sap[row][col] = 9;
            gen(row, col, sap);
            mines_placed++;
        }
    }
}

int uncovered(char board[MAX_ROWS][MAX_COLS])
{
    int index = 0;
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (board[i][j] != '+')
                index++;
        }
    }
    return index;
}

void initialize_colors()
{
    start_color();
    init_pair(1, COLOR_BLUE, A_NORMAL);
    init_pair(2, COLOR_GREEN, A_NORMAL);
    init_pair(3, COLOR_RED, A_NORMAL);
    init_pair(4, COLOR_CYAN, A_NORMAL);
    init_pair(5, COLOR_MAGENTA, A_NORMAL);
    init_pair(6, COLOR_YELLOW, A_NORMAL);
    init_pair(7, COLOR_WHITE, A_NORMAL);
    init_pair(8, COLOR_RED, A_NORMAL);
}

void end()
{
    printw("Press any key to exit...\n");
    getch();
    endwin();
}

bool too_much_bombs(int MAX_ROWS, int MAX_COLS, int MINES)
{
    if (MINES >= MAX_COLS * MAX_ROWS) {
        printf("TOO MUCH BOMBS!, TRY VALUE OF MINES LOWER THAN %i...\n\n", MAX_COLS * MAX_ROWS);

        getch();

        return TRUE;
    }
    return FALSE;
}

void gameover()
{
    printw("\n\n\n\n");
    printw(":::    ::: ::::::::  ::::    ::: ::::::::::: :::::::::: ::::::::        ::::::::  :::::::::  :::   ::: \n");
    printw(":+:   :+: :+:    :+: :+:+:   :+:     :+:     :+:       :+:    :+:      :+:    :+: :+:    :+: :+:   :+: \n");
    printw("+:+  +:+  +:+    +:+ :+:+:+  +:+     +:+     +:+       +:+             +:+        +:+    +:+  +:+ +:+  \n");
    printw("+#++:++   +#+    +:+ +#+ +:+ +#+     +#+     +#++:++#  +#+             :#:        +#++:++#:    +#++:   \n");
    printw("+#+  +#+  +#+    +#+ +#+  +#+#+#     +#+     +#+       +#+             +#+   +#+# +#+    +#+    +#+    \n");
    printw("#+#   #+# #+#    #+# #+#   #+#+#     #+#     #+#       #+#    #+#      #+#    #+# #+#    #+#    #+#    \n");
    printw("###    ### ########  ###    #### ########### ########## ########        ########  ###    ###    ###    \n");
    printw("\n\n\n");
}

void win()
{
    printw("\n\n\n\n");
    printw(":::       ::: :::   :::  ::::::::  :::::::::      :::     ::::    :::     :::     \n");
    printw(":+:       :+: :+:   :+: :+:    :+: :+:    :+:   :+: :+:   :+:+:   :+:   :+: :+:   \n");
    printw("+:+       +:+  +:+ +:+  +:+        +:+    +:+  +:+   +:+  :+:+:+  +:+  +:+   +:+  \n");
    printw("+#+  +:+  +#+   +#++:   :#:        +#++:++#:  +#++:++#++: +#+ +:+ +#+ +#++:++#++: \n");
    printw("+#+ +#+#+ +#+    +#+    +#+   +#+# +#+    +#+ +#+     +#+ +#+  +#+#+# +#+     +#+ \n");
    printw(" #+#+# #+#+#     #+#    #+#    #+# #+#    #+# #+#     #+# #+#   #+#+# #+#     #+# \n");
    printw("  ###   ###      ###     ########  ###    ### ###     ### ###    #### ###     ### \n");
    printw("\n\n\n");
}