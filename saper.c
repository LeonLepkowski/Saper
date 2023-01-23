#include "saper.h"

void colors(char board[INDEX][INDEX], int i, int j, int sap[INDEX][INDEX], int slim)
{
    char* a = " ";
    if (slim == 1)
        a = "";

    if (board[i][j] == '1' || board[i][j] == '2' || board[i][j] == '3' || board[i][j] == '4' || board[i][j] == '5' || board[i][j] == '6' || board[i][j] == '7') {
        attron(COLOR_PAIR(sap[i][j]));
        printw("%s%c", a, board[i][j]);
        attroff(COLOR_PAIR(sap[i][j]));
    } else if (board[i][j] == 'F') {
        attron(COLOR_PAIR(6));
        printw("%s%c", a, board[i][j]);
        attroff(COLOR_PAIR(6));
    } else if (board[i][j] == '0') {
        printw(" %s", a);
    } else if (board[i][j] == '8') {
        printw("%s%c", a, board[i][j]);
    } else if (board[i][j] == '@') {
        attron(COLOR_PAIR(8));
        printw("%s@", a);
        attroff(COLOR_PAIR(8));
    } else
        printw("%s%c", a, board[i][j]);
}

void saper(int a, int b, char board[INDEX][INDEX], int sap[INDEX][INDEX], int to[INDEX][INDEX], int MAX_ROWS, int MAX_COLS)
{
    int p[16] = { 1, 1, -1, -1, -1, 1, 1, -1, 1, 0, 0, 1, -1, 0, 0, -1 };
    if (sap[a][b] == 0) {
        for (int k = 0; k < 16; k += 2) {
            if (a + p[k] >= 0 && a + p[k] < MAX_ROWS && b + p[k + 1] >= 0 && b + p[k + 1] < MAX_COLS) {
                if (board[a + p[k]][b + p[k + 1]] == '+') {
                    if (sap[a + p[k]][b + p[k + 1]] == 0 && to[a + p[k]][b + p[k + 1]] == 0) {
                        to[a + p[k]][b + p[k + 1]] = 1;
                        saper(a + p[k], b + p[k + 1], board, sap, to, MAX_ROWS, MAX_COLS);
                    }
                    board[a + p[k]][b + p[k + 1]] = sap[a + p[k]][b + p[k + 1]] + '0';
                }
            }
        }
    }
    if (board[a][b] != 'F')
        board[a][b] = sap[a][b] + '0';
}

void setup_board(char board[INDEX][INDEX], int sap[INDEX][INDEX], int to[INDEX][INDEX], int rows, int cols)
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
}

void draw_board(char board[INDEX][INDEX], int row, int col, int slim, int sap[INDEX][INDEX], int MAX_ROWS, int MAX_COLS, int MINES)
{
    erase();

    int flags = 0;
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (board[i][j] == 'F')
                flags += 1;
        }
    }
    mvprintw(0, 2, "[%2i]\n", MINES - flags);
    for (int i = 0; i < MAX_ROWS; i++) {
        printw(" ");

        for (int j = 0; j < MAX_COLS; j++) {
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

void update_board(char board[INDEX][INDEX], int sap[INDEX][INDEX], int to[INDEX][INDEX], int* row, int* col, char action, int MAX_ROWS, int MAX_COLS, int MINES)
{
    int flags = 0;
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (board[i][j] == 'F')
                flags += 1;
        }
    }

    if (action == 'f' && board[*row][*col] == '+' && flags != MINES) {
        board[*row][*col] = 'F';
    } else if (action == 'f' && board[*row][*col] == 'F') {
        board[*row][*col] = '+';
        // } else if (action == ' ' && board[*row][*col] >= '0' && board[*row][*col] < 9 + '0') {
        //     new_function(board, sap, *row, *col, to);
    } else if (action == ' ' && board[*row][*col] != 'F') {
        saper(*row, *col, board, sap, to, MAX_ROWS, MAX_COLS);
    }
}

void gen(int i, int j, int sap[INDEX][INDEX], int MAX_ROWS, int MAX_COLS)
{
    int p[16] = { 1, 1, -1, -1, -1, 1, 1, -1, 1, 0, 0, 1, -1, 0, 0, -1 };

    for (int k = 0; k < 16; k += 2) {
        if (i + p[k] < MAX_ROWS && j + p[k + 1] < MAX_COLS && i + p[k] >= 0 && j + p[k + 1] >= 0 && sap[i + p[k]][j + p[k + 1]] != 9)
            sap[i + p[k]][j + p[k + 1]] += 1;
    }
}

int czy_koniec(char board[INDEX][INDEX], int MAX_ROWS, int MAX_COLS)
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

bool sprawdz(int a, int b, int sap[INDEX][INDEX], char board[INDEX][INDEX], int MAX_ROWS, int MAX_COLS)
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

int uncovered(char board[INDEX][INDEX], int MAX_ROWS, int MAX_COLS)
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
    init_color(COLOR_BLUE, 140, 600, 900);
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
    int a = 0;
    printw("Press ENTER to exit...\n");
    while(a != '\n'){
        a = getch();
    }
    endwin();
}

bool too_much_bombs(int MAX_ROWS, int MAX_COLS, int MINES)
{
    if (MINES >= MAX_ROWS * MAX_COLS) {
        printf("TOO MUCH BOMBS!, TRY VALUE OF MINES LOWER THAN %i...\n\n", MAX_ROWS * MAX_COLS);

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

bool new_function(char board[INDEX][INDEX], int sap[INDEX][INDEX], int i, int j, int to[INDEX][INDEX], int MAX_ROWS, int MAX_COLS)
{
    int p[16] = { 1, 1, -1, -1, -1, 1, 1, -1, 1, 0, 0, 1, -1, 0, 0, -1 };
    int flags = 0;
    for (int k = 0; k < 16; k += 2) {
        if (i + p[k] < MAX_ROWS && j + p[k + 1] < MAX_COLS && i + p[k] >= 0 && j + p[k + 1] >= 0 && board[i + p[k]][j + p[k + 1]] == 'F')
            flags += 1;
    }
    if (flags == sap[i][j]) {
        for (int k = 0; k < 16; k += 2) {
            if (i + p[k] < MAX_ROWS && j + p[k + 1] < MAX_COLS && i + p[k] >= 0 && j + p[k + 1] >= 0) {
                if (sprawdz(i + p[k], j + p[k + 1], sap, board, MAX_ROWS, MAX_COLS))
                    return true;
                saper(i + p[k], j + p[k + 1], board, sap, to, MAX_ROWS, MAX_COLS);
            }
        }
    }
    return false;
}

char* input(char* argv[])
{
    char* temp;
    if (strcmp(argv[1], "--slim") == 0) {
        temp = argv[1];
        argv[1] = argv[2];
        argv[2] = argv[3];
        argv[3] = argv[4];
    } else if (strcmp(argv[2], "--slim") == 0) {
        temp = argv[2];
        argv[2] = argv[3];
        argv[3] = argv[4];
    } else if (strcmp(argv[3], "--slim") == 0) {
        temp = argv[3];
        argv[3] = argv[4];
    } else
        temp = argv[4];
    return temp;
}

void bombs_generator(int i, int j, int sap[INDEX][INDEX], int MAX_ROWS, int MAX_COLS, int MINES)
{

    int mines_placed = 0;
    while (mines_placed < MINES) {
        int row = rand() % MAX_ROWS;
        int col = rand() % MAX_COLS;
        if (row != i || col != j) {
            if (sap[row][col] != 9) {
                sap[row][col] = 9;
                gen(row, col, sap, MAX_ROWS, MAX_COLS);
                mines_placed++;
            }
        }
    }
}