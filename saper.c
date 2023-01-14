#include "saper.h"

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

    printw("\n");

    for (int i = 0; i < rows; i++) {
        printw(" ");

        for (int j = 0; j < cols; j++) {
            if (i == row && j == col) {
                attron(A_STANDOUT);
                if (board[i][j] == '@')
                    attron(COLOR_PAIR(9));
            }
            colors(board, i, j, sap, slim);
            if (i == row && j == col) {
                attroff(A_STANDOUT);
                if (board[i][j] == '@')
                    attroff(COLOR_PAIR(9));
            }
        }
        printw("\n");
    }
    printw("\n");
}

void update_board(char board[MAX_ROWS][MAX_COLS], int sap[MAX_ROWS][MAX_COLS], int to[MAX_ROWS][MAX_COLS], int* row, int* col, char action)
{
    if (action == 'f' && board[*row][*col] == '+') {
        board[*row][*col] = 'F';
    } else if (action == 'f' && board[*row][*col] == 'F') {
        board[*row][*col] = '+';
    // } else if (action == ' ' && board[*row][*col] >= '0' && board[*row][*col] < 9 + '0') {
    //     new_function(board, sap, *row, *col, to);
    } else if (action == ' ' && board[*row][*col] != 'F') {
        saper(*row, *col, board, sap, to);
    }
}

void gen(int i, int j, int sap[MAX_ROWS][MAX_COLS]) // Dodaje 1 wszystkim polom na około współrzędej (x,y)
{
    int p[16] = { 1, 1, -1, -1, -1, 1, 1, -1, 1, 0, 0, 1, -1, 0, 0, -1 };

    for (int k = 0; k < 16; k += 2) {
        if (i + p[k] < MAX_ROWS && j + p[k + 1] < MAX_COLS && i + p[k] >= 0 && j + p[k + 1] >= 0 && sap[i + p[k]][j + p[k + 1]] != 9)
            sap[i + p[k]][j + p[k + 1]] += 1;
    }
}

int czy_koniec(char board[MAX_ROWS][MAX_COLS]) // Zlicza wyświetlone miejsca
{
    int b_flagi = 0;
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
    if(board[a][b] != 'F') board[a][b] = sap[a][b] + '0';
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

void colors(char board[MAX_ROWS][MAX_COLS], int i, int j, int sap[MAX_ROWS][MAX_COLS], int slim)
{
    char a = ' ';
    if (slim == 1)
        a = '_';

    if (board[i][j] == '1' || board[i][j] == '2' || board[i][j] == '3' || board[i][j] == '4' || board[i][j] == '5' || board[i][j] == '6' || board[i][j] == '7') {
        attron(COLOR_PAIR(sap[i][j]));
        printw("%c%c", a, board[i][j]);
        attroff(COLOR_PAIR(sap[i][j]));
    } else if (board[i][j] == 'F') {
        attron(COLOR_PAIR(6));
        printw("%c%c", a, board[i][j]);
        attroff(COLOR_PAIR(6));
    } else if (board[i][j] == '0') {
        printw(" %c", a);
    } else if (board[i][j] == '8') {
        printw("%c%c", a, board[i][j]);
    } else if (board[i][j] == '@') {
        attron(COLOR_PAIR(8));
        printw("%c@", a);
        attroff(COLOR_PAIR(8));
    } else
        printw("%c%c", a, board[i][j]);
}

void zero_move(int i, int j, int sap[MAX_ROWS][MAX_COLS], int rows, int cols)
{
    int p[16] = { 1, 1, -1, -1, -1, 1, 1, -1, 1, 0, 0, 1, -1, 0, 0, -1 };
    sap[i][j] = 0;
    for (int k = 0; k < 16; k += 2) {
        if (i + p[k] < MAX_ROWS && j + p[k + 1] < MAX_COLS && i + p[k] >= 0 && j + p[k + 1] >= 0 && sap[i + p[k]][j + p[k + 1]] != 9)
            sap[i + p[k]][j + p[k + 1]] -= 1;

        if (i + p[k] < MAX_ROWS && j + p[k + 1] < MAX_COLS && i + p[k] >= 0 && j + p[k + 1] >= 0 && sap[i + p[k]][j + p[k + 1]] == 9)
            sap[i][j] += 1;
    }

    int mines_placed = 0;
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

bool new_function(char board[MAX_ROWS][MAX_COLS], int sap[MAX_ROWS][MAX_COLS], int i, int j, int to[MAX_ROWS][MAX_COLS])
{
    int p[16] = { 1, 1, -1, -1, -1, 1, 1, -1, 1, 0, 0, 1, -1, 0, 0, -1 };
    int flags = 0;
    for (int k = 0; k < 16; k += 2) {
        if (i + p[k] < MAX_ROWS && j + p[k + 1] < MAX_COLS && i + p[k] >= 0 && j + p[k + 1] >= 0 && board[i + p[k]][j + p[k + 1]] == 'F')
            flags += 1;
    }
    if(flags == sap[i][j])
    {
        for (int k = 0; k < 16; k += 2) {
        if (i + p[k] < MAX_ROWS && j + p[k + 1] < MAX_COLS && i + p[k] >= 0 && j + p[k + 1] >= 0)
            if(sprawdz(i + p[k], j + p[k + 1], sap, board)) return true;
            saper(i +p[k], j + p[k + 1], board, sap, to);
        }
    }
    return false;
}