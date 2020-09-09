# The Othello Game
This game is a board game that can be played with two players on an 8x8 board (64 squares). There are 64 discs colored black on one side and white on the other. In this game, players take turns placing discs, with one side being black, and the other being white (players take turns placing disks on the board with their assigned color facing up). Play begins with each player having two pieces on the board.

The overall game rules are as follows:

• The board is set up initially with two black discs (i.e. a disc with black side uppermost)
placed on squares e4 and d5 and two white discs on d4 and e5.

• Black always plays first with players then taking alternate turns.

• At each turn a player must place a disc with their color face up on one of the empty
squares of the board, adjacent to an opponent's disc such that one or more straight lines
(horizontal, vertical or diagonal) are formed from the newly placed disc, through one or
more of the opponent's discs and up to other discs of their own color already on the
board. All the intervening discs of the opponent's color are flipped to the color of the
newly laid disc.

• Discs may be flipped from one color to the other but once played are not moved from
one square to another or removed from the board.

• Players may not pass unless there is no valid move available to them in which case they
must pass.

• Play continues until neither player is able to move, usually when all 64 squares have
been played.

The game ends when neither player can make a valid move, at which point the player who
controls the most discs wins the game.

# Minimax Algorithm
The state space of the game can be decided by selecting the cut-off for the search tree (2^b). For the sake of the running time, "4" is chosen as the cut-off value for the minimax algorithm (red box). Also, different heuristics for different agents (blue boxes) are used. The nodes are counted everytime when the minimax function is visited (green box).

![GitHub Logo](/desc_imgs/1.jpg)

![GitHub Logo](/desc_imgs/2.jpg)

# Heuristics

Heuristic 1 (red box) is trying to take the corners as many as possible because the chance that flipping the many coins depends on the corner coins.

Heuristic 2 (blue box) is trying to maximize its coin number on the board by substracting the computer’s coins and enemy’s coins.

![GitHub Logo](/desc_imgs/3.jpg)
