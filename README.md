# ENGG1340_Group_Project

1. Team Members:

  - MOREL, Hugo Louis M (UID: 3035919755; GitHub: @hmorel)
  
  - Nip, Hok Leung (UID: 303; GitHub: @niphl)


2. Description of the project

  - Title: 
  
Minesweeper game
  
  - Rules: 
  
In Minesweeper, mines are scattered throughout a board, which is divided into cells with coordinates.
Cells have three states: uncovered, covered (C) and flagged (F). 
A covered cell is blank and clickable, while an uncovered cell is exposed. 
Flagged cells are those marked by the player to indicate a potential mine location.
Player choose whether to uncover of flag a cell and then enters its coordinates.
If a player uncovers a mined cell, the game ends, as there is only 1 life per game. 
Otherwise, the uncovered cell displays either a number, indicating the number of mines diagonally and/or adjacent to it, or a blank tile (or "0"), and all adjacent non-mined cells will automatically be uncovered. 
Flagged cells are still considered covered, and a player can choose to uncover them.
The first cell choice in any game will never be a mine.
To win the game, players must uncover all non-mine cells. Flagging all the mined cells is not required.

  - Features:
  
    - Text-based display of board state, and text-based input for flagging and uncovering cells.
    - Player options for game initialization which will affect the board size and number of mines. Will include preset options (Beginner, Intermediate, Expert) and also a custom option. 

    - Save the game when quitting, and have the option to load it again after opening the program or starting a new game.
    - Player statistics (Win rate for different difficulties, average number of cells uncovered)
    - Board State of last 10 games played (Final board state can be viewed. If games are not complete, we can let players load them and finish the game).
