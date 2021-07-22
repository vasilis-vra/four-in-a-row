# Four in a row game
Simple C script implementing the four in a row game in a console application

## Table of Contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Setup](#setup)
* [How to play](#how-to-play)
* [Examples](#examples)

## General info
This project is a simple console application that implements the four in a row game on a 7x7 table.    
The user can play against another user or against the computer. The computer implements a simple but competitive strategy evaluating the best possible move given the table at each point.

## Technologies
The project is created using only the C programming language.

## Setup
Open the project folder using a C IDE. Then simply build and run the application.
You can also run the console application inside the bin/Debug directory.

## How to play
To play the game you first have to specify either to play against another player (choose 1) or the computer (choose 2).   
* Playing against another player: Each player takes a turn by placing a disk symbol (\+ or \*) in a column of the table. To play you need to input a number (1 \- 7) to choose a column. Winner is the first player to have four in a row. The updated table is printed after every move.
* Playing against the computer: The player each round chooses a column (1 \- 7) as input. Then the computer chooses a move by evaluating the moves available. The updated table is printed after every move. 

##Examples
* Choosing a game mode:   
![choose-mode](https://user-images.githubusercontent.com/77937479/126626221-f71a54f5-c51d-4fb0-8fae-462038a73fc3.png)  



* Player vs Player:   
![player-player](https://user-images.githubusercontent.com/77937479/126626275-35ab5c53-fa2d-473a-945c-028a462c86ad.png)  



* Player vs Computer:   
![player-computer](https://user-images.githubusercontent.com/77937479/126626293-c9a4c574-3ba2-4b24-b8ec-5e53407f20c1.png)  


