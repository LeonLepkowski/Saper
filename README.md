# Saper game in C
Minesweeper is a logic puzzle video game genre generally played on personal computers. The game features a grid of clickable squares, with hidden "mines" scattered throughout the board.

## Controls:

* Arrow keys - move around map

* Space key - uncover current box

* F key - flag current box

<br />

## To compile file type in terminal:

```bash
   gcc main.c saper.c -o main -std=c11 -Wall -Wextra -Werror -xc -lncurses
```

## To run it type:
```bash
   ./main [command]
```
> There are 3 different difficulties: --beginner, --intermediate and --expert.
> You can also use --custom, where you put 3 numbers after, which are width, hight and number of mines.

<br />

## Ncurses

You also need to download ncurses library to compile the file

```bash
  sudo apt-get install libncurses5-dev libncursesw5-dev
```
<br />
<br />

Game created by Leon Lepkowski