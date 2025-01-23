# MARIO CLONE - CS202

## Introduction

This project is done as a required project of the CS202 course. It aims to replicate core and some additional gameplay mechanics of the game Super Mario Brothers, including, but not limited to deafeating enemies, avoiding projectiles, item collision, hidden level, etc.

## Technologies used

- Language: C++, Python
- Libraries: raylib
- Tools: VSCode (Makefile), Visual Studio

## How to run the project

### For Mac and Linux

1. Clone the repository

2. Install raylib and VSCode

3. Copy and paste the content of the include and lib folder.
After installing raylib, you need to find the ```lib``` and ```include``` folders, copy and paste them to the project ```lib``` and ```include``` folders, respectively.

On Linux, it is usually located at ```/usr/local/lib/```
and ```/usr/local/include```. You can use this command to find it:
```bash
pkg-config --cflags raylib
pkg-config --libs raylib
```

On OS X, if you install raylib via Homebrew, it is usually located at ```/opt/homebrew/Cellar```.

4. Open a terminal in the repository, use ```make clean && make && bin/main``` to clean the build folder, build and run the binary file.

## Features not required but implemented

- Dynamic background, camera interpolation.
- Powerup animation, question block animations.
- Fireballs (limit spamming to 2 balls)
- Flag pulling animtion, fade out animation.
- Lakitu's projectiles.
