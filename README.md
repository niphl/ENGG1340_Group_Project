# ENGG1340_Group_Project

1. Team Members:

  - MOREL, Hugo Louis M (UID: 3035919755; GitHub: @hmorel)
  
  - Nip, Hok Leung (UID: 3035957240; GitHub: @niphl)


2. Description of the project

  - Title: 
  
    Minesweeper
  
  - Rules: 
  
    In Minesweeper, mines are scattered throughout a board, which is divided into cells with coordinates.
    Cells have three states: uncovered, covered (C) and flagged (F). 
    A covered cell is blank and clickable, while an uncovered cell is exposed. 
    Flagged cells are those marked by the player to indicate a potential mine location.
    Player choose whether to uncover of flag a cell and then enters its coordinates.
    If a player uncovers a mined cell, the game ends, as there is only 1 life per game. 
    Otherwise, the uncovered cell displays either a number, indicating the number of mines diagonally and/or adjacent to it, or a blank tile (or "0"), and     all adjacent non-mined cells will automatically be uncovered. 
    Flagged cells are still considered covered, and a player can choose to uncover them.
    The first cell choice in any game will never be a mine.
    To win the game, players must uncover all non-mine cells. Flagging all the mined cells is not required.

  - Features:
    - After the player's first move, the board will be set up with mines randomly placed, satisying code requirement (1).
    - Text-based display of board state, and text-based input for flagging and uncovering cells. The state of the game will be stored using the array data structure, satisfying requirement (2).
    - Player options for game initialization which will affect the board size and number of mines. Will include preset options (Beginner, Intermediate, Expert) and also a custom option. 
    - Player statistics (Win rate for different difficulties, average number of cells uncovered) will be saved to a file, satisfying requirement (4). We will also use dynamic memory allocation (requirement (3)) to create an arbitrarily large array containing statistics from each game, that we will load in and calculate so the player may view them view.
    - The Board State of last 10 games played will be saved to a file, satisfying requirement (4). The player can view the final board state if the games are complete, and load them to finish them if they are incomplete.
    - Save the game when quitting, and have the option to load it again after opening the program or starting a new game.
    - The game will have a main menu, where the player can navigate to and back from the following menus: Main game, settings, player stats and recent game history. Each of these will use different functions, which will be stored in their own files for organization, satisfying requirement (5).

