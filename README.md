# ENGG1340_Group_Project

1. Team Members:

  - MOREL, Hugo Louis M (UID: 3035919755; GitHub: @hmorel)
  
  - NIP, Hok Leung (UID: 3035957240; GitHub: @niphl)


2. Description of the project

  - Title: 
  
    Minesweeper
    
  - Description:
  
    - This is a text-based version of the single-player puzzle game minesweeper. The objective is to uncover the whole board, while not uncovering any mines by mistake.
    - As the player uncovers cells in the board, they receive clues about where the hidden mines are, as uncovered cells will tell the player how many mines are adjacent to them.
    - If a cell containing a mine is uncovered, the player loses. If all the cells without mines are uncovered, the player wins.
    - A number of helpful features such as flagging (to show where mines are) and various auto-uncovering features or flag based uncovering features make the gameplay smoother and faster.
  
  - Rules: 
  
    - In Minesweeper, mines are scattered throughout a board, which is divided into cells with coordinates.
    - Cells have three states: uncovered(0-8), covered (.) and flagged (F). 
    - A covered cell is blank and provides no information, while an uncovered cell indicates the number of mines adjacent to it.
    - Flagged cells are those marked by the player to indicate a potential mine location.
    - Player choose whether to uncover of flag a cell and then enters its coordinates.
    - If a player uncovers a mined cell, the game ends, as there is only 1 life per game. 
    - Flagged cells are still considered covered, and a player can choose to uncover them.
    - The first cell choice all adjacent cells will never be a mine.
    - To win the game, players must uncover all non-mine cells. Flagging all the mined cells is not required.
    - In the knightsweeper special game mode, cells are considered adjacent if they are a knights move away from each other.

  - Features:
    - After the player's first move, the board will be set up with mines randomly placed, satisying code requirement 1 (Random game sets or events).
    - Struct to capture the state of the game. Some member variables are ints for info on the game such as difficulty, seed, board size, number of mines. Some member variables are arrays used for information on the board such as where the mines are, and where the player has uncovered/flagged, satisfying code requirement 2 (Data structures for storing game status).
    - Dynamic memory management used in the array to record every move the player has made throughout the game. When the array is full, it will expand. Satisfies coding requirement 3 (dynamic memory management).
    - The member variables of the board, including the player's move history, is saved to a file after each move. The game can then be loaded back again via file input, even if the player suddenly closes the game. This satisfies coding requirement 4 (file input output).
    - Program code is organized into 3 files: main.cpp, involving main menu functions, boardFunctions.cpp includes 2 functions used for playing the game, and main.h which is the header file for main, and also contains the board struct and all its member functions used for playing the game. This satisfies coding requirement 5 (multiple files)
    - Extra feature to improve clarity of the game: Coloured text for mines in various cells 
    - Extra feature for more customization: Custom board size options/mines!
    - Extra feature for smoother gameplay: If a newly uncovered cell has no mines next to it, all cells adjacent to it are automatically uncovered.
    - Extra creative and fun gamemode 'Knightsweeper' where the rules are different: Cells are only adjacent if they are a knights move away from each other!
    - Flags: Players can place flags to track where mines are.
    - Advanced flagging feature for smoother gameplay: If the number of mines adjacent to the number of flags, clicking that cell will automatically uncover all cells next to it, for faster/smoother gameplay.
    - Advanced flagging feature for smoother gameplay: Two options for flagging, switching to flagging mode completely, or quick flagging for 1 turn only by inserting an 'f' in front of the move the player makes.
    - Save the game when quitting, and have the option to load it again after losing (not available in original minesweeper).
    - Interactive tutorial to guide players on the basics on how to play the game (Does not teach advanced flagging features)
    - The game will have a main menu, where the player can navigate to and back from the following menus.

3. Compilation and Execution Instructions
  - 1. Download the ZIP containing the files, and extract it onto your desktop, or any other working directory.
  - 2. In the terminal, navigate to the working directory containing the files, and run the command 'make minesweeper'
  - 3. Run the command './minesweeper' on the terminal to play the game.
