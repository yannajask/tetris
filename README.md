# Tetris

Tetris in C++!

<img src=img/tetris.gif width=400>

## Building

### Install Dependencies

You will need to install `ncursesw` (ncurses wide) as a dependency.

#### Mac

```
$ brew install ncurses
```

#### Linux
```
$ sudo apt-get install libncursesw5-dev
```

#### Windows

Currently no support for ncurses on Windows - intend to add PDCurses support eventually

### Compiling

In the root directory, type:

```
$ make
```

## Usage

In the root directory, type:

```
$ ./tetris
```

### Controls

- <kbd>←</kbd>, <kbd>→</kbd>, <kbd>↓</kbd> to move right, left, soft drop
- <kbd>A</kbd>, <kbd>D</kbd> to rotate counterclockwise and clockwise
- <kbd>SPACE</kbd> to hard drop
- <kbd>Q</kbd> to quit
