# Saper game in C
Minesweeper is a logic puzzle video game genre generally played on personal computers. The game features a grid of clickable squares, with hidden "mines" scattered throughout the board.

## Controls:

* Arrow keys (or hjkl) - move around map

* Space key - uncover current box

* F key - flag current box

<br />

## To compile file type in terminal:

```bash
   make
```

You can also specify some parameters:
```bash
   make CC=clang EXE=minesweeper
```

Binary will be placed in _build folder

## To clear `_build` directory type:

```bash
   make clean
```

## To install type:

```bash
   make install
```

Default location: `/usr/local/bin`

You can change it by adding `PREFIX` argument. Game will be installed to `<PREFIX>/bin`

```bash
   make install PREFIX=~./local
```

## To uninstall type:

```bash
   make uninstall
```

## To run it type:
```bash
   saper [command]
```
> There are 3 different difficulties: --beginner, --intermediate and --expert.
> You can also use --custom, where you put 3 numbers, which are: width, hight and number of mines.

<br />

## Ncurses

You also need to download ncurses library to compile the file

```bash
   sudo apt-get install libncurses5-dev libncursesw5-dev
```
<br />
<br />

Game created by Leon Lepkowski
