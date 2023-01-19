# Saper game in C


## Controls:

* Arrow keys - move around map

* Space - uncover current box

* F key - flag current box

<br />
<br />

## To run file type in terminal:

```bash
   gcc main.c saper.c -o main -std=c11 -Wall -Wextra -Werror -xc -lncurses
```
```bash
./main hight width mines
```
>You can also add --slim so your game will be narrow

<br />
<br />

## Ncurses

You also need to download ncurses library

```bash
  sudo apt-get install libncurses5-dev libncursesw5-dev
```
<br />
<br />

Game created by Leon Lepkowski