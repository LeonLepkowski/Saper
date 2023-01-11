void start(int a, int b, int c);
void setup_board(char board[MAX_ROWS][MAX_COLS], int sap[MAX_ROWS][MAX_COLS], int rows, int cols, int mines);
void draw_board(char board[MAX_ROWS][MAX_COLS], int rows, int cols, int row, int col, int slim, int sap[MAX_ROWS][MAX_COLS]);
void update_board(char board[MAX_ROWS][MAX_COLS], int sap[MAX_ROWS][MAX_COLS], int to[MAX_ROWS][MAX_COLS], int rows, int cols, int* row, int* col, char action);
void gen(int i, int j, int sap[MAX_ROWS][MAX_COLS]);
int czy_koniec(int b_flagi, char board[MAX_ROWS][MAX_COLS]);
void saper(int a, int b, char board[MAX_ROWS][MAX_COLS], int sap[MAX_ROWS][MAX_COLS], int to[MAX_ROWS][MAX_COLS]);
bool sprawdz(int a, int b, int sap[MAX_ROWS][MAX_COLS], char board[MAX_ROWS][MAX_COLS]);
void colors(char board[MAX_ROWS][MAX_COLS], int i, int j, int sap[MAX_ROWS][MAX_COLS]);
void colors_slim(char board[MAX_ROWS][MAX_COLS], int i, int j, int sap[MAX_ROWS][MAX_COLS]);
void zero_move(int i, int j, int sap[MAX_ROWS][MAX_COLS], int board[MAX_ROWS][MAX_COLS], int rows, int cols);

void GameOver()
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

void wygrana()
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