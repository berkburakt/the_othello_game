# The Othello Game
# Minimax Algorithm
The state space of the game can be decided by the select the cut-off for the search tree (2^b). For the sake of the speed, I choosed 4 as my cut-off value for the minimax algorithm (red box). And I used different heuristics for different agent (blue boxes). I count the nodes everytime when I visit the minimax function (green box).

![GitHub Logo](/desc_imgs/1.jpg)

![GitHub Logo](/desc_imgs/2.jpg)

# Heuristics

I choose my heuristic 1 (red box) as I assigned corner values for every position in my board. This heuristic is trying to take the corners as many as possible because the chance that flipping the many coins is depending on the corner coins.
I choose my heuristic 2 (blue box) as I substract the computer’s coins and enemy’s coins and returned the value. This heuristic is trying to maximize its coin number on the board.

![GitHub Logo](/desc_imgs/3.jpg)
