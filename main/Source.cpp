//Berk Burak Taþdemir - 2152171

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;

int search(vector<vector<int>> &board, pair<int, int> pos, int player) {
	vector<pair<int, int>> turnMaster;
	vector<pair<int, int>> turn;

	if (pos.first < 0 || pos.first > 7 || pos.second < 0 || pos.second > 7 || board[pos.first][pos.second] != 0)
		return 0;

	turnMaster.push_back(make_pair(pos.first, pos.second));

	//Search East
	for (int i = pos.second + 1; i < 8; i++) {
		if (board[pos.first][i] == 0) {
			break;
		} else if (board[pos.first][i] != player) {
			turn.push_back(make_pair(pos.first, i));
		}
		else {
			turnMaster.insert(turnMaster.end(), turn.begin(), turn.end());
			break;
		}
	}

	turn.clear();

	//Search West
	for (int i = pos.second - 1; i >= 0; i--) {
		if (board[pos.first][i] == 0) {
			break;
		} else if (board[pos.first][i] != player) {
			turn.push_back(make_pair(pos.first, i));
		}
		else {
			turnMaster.insert(turnMaster.end(), turn.begin(), turn.end());
			break;
		}
	}

	turn.clear();

	//Search North
	for (int i = pos.first - 1; i >= 0; i--) {
		if (board[i][pos.second] == 0) {
			break;
		} else if (board[i][pos.second] != player) {
			turn.push_back(make_pair(i, pos.second));
		}
		else {
			turnMaster.insert(turnMaster.end(), turn.begin(), turn.end());
			break;
		}
	}

	turn.clear();

	//Search South
	for (int i = pos.first + 1; i < 8; i++) {	
		if (board[i][pos.second] == 0) {
			break;
		} else if (board[i][pos.second] != player) {
			turn.push_back(make_pair(i, pos.second));
		}
		else {
			turnMaster.insert(turnMaster.end(), turn.begin(), turn.end());
			break;
		}
	}

	turn.clear();

	int counter = 1;

	//Search NorthEast
	for (int i = pos.first - 1; i >= 0; i--) {
		if (pos.second + counter > 7)
			break;
		if (board[i][pos.second + counter] == 0) {
			break;
		}
		else if (board[i][pos.second + counter] != player) {
			turn.push_back(make_pair(i, pos.second + counter));
		}
		else {
			turnMaster.insert(turnMaster.end(), turn.begin(), turn.end());
			break;
		}
		counter++;
	}

	counter = 1;
	turn.clear();

	//Search NorthWest
	for (int i = pos.first - 1; i >= 0; i--) {
		if (pos.second - counter < 0)
			break;
		if (board[i][pos.second - counter] == 0) {
			break;
		}
		else if (board[i][pos.second - counter] != player) {
			turn.push_back(make_pair(i, pos.second - counter));
		}
		else {
			turnMaster.insert(turnMaster.end(), turn.begin(), turn.end());
			break;
		}
		counter++;
	}

	counter = 1;
	turn.clear();

	//Search SouthEast
	for (int i = pos.first + 1; i < 8; i++) {
		if (pos.second + counter > 7)
			break;
		if (board[i][pos.second + counter] == 0) {
			break;
		}
		else if (board[i][pos.second + counter] != player) {
			turn.push_back(make_pair(i, pos.second + counter));
		}
		else {
			turnMaster.insert(turnMaster.end(), turn.begin(), turn.end());
			break;
		}
		counter++;
	}

	//Search SouthWest
	for (int i = pos.first + 1; i < 8; i++) {
		if (pos.second - counter < 0)
			break;
		if (board[i][pos.second - counter] == 0) {
			break;
		}
		else if (board[i][pos.second - counter] != player) {
			turn.push_back(make_pair(i, pos.second - counter));
		}
		else {
			turnMaster.insert(turnMaster.end(), turn.begin(), turn.end());
			break;
		}
		counter++;
	}

	if (turnMaster.size() > 1)
		for (pair<int, int> p : turnMaster)
			board[p.first][p.second] = player;
	else
		return 0;
	return 1;
}

int score(vector<vector<int>> board, int player) {
	int total = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) 
			if (board[i][j] == player)
				total++;
	return total;
}

void getMoveList(vector<vector<int>> board, vector<pair<int, int>> &moves, int player) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			vector<vector<int>> tempBoard = board;
			if (search(tempBoard, make_pair(i, j), player)) {
				moves.push_back(make_pair(i, j));
			}
		}
	}
}

bool gameOver(vector<vector<int>> board) {
	vector<pair<int, int>> playerMoves, enemyMoves;
	getMoveList(board, playerMoves, 1);
	getMoveList(board, enemyMoves, 2);
	return true ? (playerMoves.empty() && enemyMoves.empty()) : false;
}

int cornerWeight(vector<vector<int>> board, int player) {
	int total = 0;
	int enemy = 2;
	if (player == 2)
		enemy = 1;
	vector<vector<int>> weights{
		{4, -3, 2, 2, 2, 2, -3, 4},
		{-3, -4, -1, -1, -1, -1, -4, -3},
		{2, -1, 1, 0, 0, 1, -1, 2},
		{2, -1, 0, 1, 1, 0, -1, 2},
		{2, -1, 0, 1, 1, 0, -1, 2},
		{2, -1, 1, 0, 0, 1, -1, 2},
		{-3, -4, -1, -1, -1, -1, -4, -3},
		{4, -3, 2, 2, 2, 2, -3, 4},
	};
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (board[i][j] == player)
				total += weights[i][j];
			else if (board[i][j] == enemy)
				total -= weights[i][j];
	return total;
}

int cost(vector<vector<int>> board, int player) {
	int enemy = 1;
	if (player == 1)
		enemy = 2;
	int playerScore = score(board, player);
	int enemyScore = score(board, enemy);
	return (playerScore - enemyScore);
}

int heuristic2(vector<vector<int>> board, int player) {
	return cost(board, player);
}

int heuristic1(vector<vector<int>> board, int player) {
	return cornerWeight(board, player);
}

int minimaxValue(vector<vector<int>> board, int orgPlayer, int curPlayer, int srcPly, int alpha, int beta, int &count) {
	count++;
	if (srcPly == 4 || gameOver(board)) {
		if (orgPlayer == 1)
			return heuristic1(board, orgPlayer);
		else
			return heuristic2(board, orgPlayer);
	}
	vector<pair<int, int>> moves;
	int enemy = 1;
	if (curPlayer == 1)
		enemy = 2;
	getMoveList(board, moves, curPlayer);
	if (moves.empty())
		return minimaxValue(board, orgPlayer, enemy, srcPly + 1, alpha, beta, count);
	else {
		int bestMoveVal = INT_MIN;
		if (orgPlayer != curPlayer)
			bestMoveVal = INT_MAX;
		for (unsigned int i = 0; i < moves.size(); i++) {
			vector<vector<int>> tempBoard = board;
			search(tempBoard, moves[i], curPlayer);
			int val = minimaxValue(tempBoard, orgPlayer, enemy, srcPly + 1, alpha, beta, count);
			if (orgPlayer == curPlayer) {
				bestMoveVal = max(bestMoveVal, val);
				alpha = max(alpha, bestMoveVal);
				if (beta <= alpha)
					break;
			} else {
				bestMoveVal = min(bestMoveVal, val);
				beta = min(beta, bestMoveVal);
				if (beta <= alpha)
					break;
			}		
		}
		return bestMoveVal;
	}
	return -1;
}

void minimaxDecision(vector<vector<int>> board, int player, pair<int, int> &pos) {
	int count = 0;
	vector<pair<int, int>> moves;
	pair<int, int> bestMove;
	int enemy = 1;
	if (player == 1)
		enemy = 2;
	getMoveList(board, moves, player);
	if (moves.empty()) {
		pos = make_pair(-1, -1);
	}
	else {
		int bestMoveVal = INT_MIN;
		bestMove = make_pair(moves[0].first, moves[0].second);
		for (unsigned int i = 0; i < moves.size(); i++) {
			
			vector<vector<int>> tempBoard = board;
			search(tempBoard, moves[i], player);
			int val = minimaxValue(tempBoard, player, enemy, 1, INT_MIN, INT_MAX, count);
			if (val > bestMoveVal) {
				bestMoveVal = val;
				bestMove = moves[i];
			}
			else if (val == bestMoveVal) {
				srand(time(NULL));
				int r = rand() % 2;
				if (r) {
					bestMoveVal = val;
					bestMove = moves[i];
				}

			}
		}
		pos = bestMove;
	}

	cout << count << " node is visited." << endl;
}

void printBoard(vector<vector<int>> board, int round, int player, char symbol, bool finish) {
	string s = "A";

	if (finish) {
		cout << "FINAL RESULT" << endl << "------------" << endl << endl;
	}
	else {
		cout << "Round " << (round + 1) << endl;
		cout << "Turn: Player " << player << " (" << symbol << ")" << endl << endl;
	}

	cout << " ";

	for (int i = 0; i < 8; i++) {
		s[0] = 'A' + i;
		cout << " " << s;
	}

	cout << endl;

	for (int i = 0; i < 8; i++) {
		cout << i + 1;
		for (int n : board[i]) {
			char c;
			if (n == 0)
				c = '.';
			else if (n == 1)
				c = 'O';
			else if (n == 2)
				c = 'X';
			cout << " " << c;
		}
		cout << endl;
	}

	cout << endl;
}

void initializeBoard(vector<vector<int>> &board) {
	board.clear();

	for (int i = 0; i < 8; i++)
		board.push_back(vector<int>(8, 0));

	board[3][3] = 2;
	board[3][4] = 1;
	board[4][3] = 1;
	board[4][4] = 2;
}

void AImove(vector<vector<int>> &board, int player) {
	pair<int, int> pos;

	map<int, char> reverseMapBoard = {
		{0, 'A'},
		{1, 'B'},
		{2, 'C'},
		{3, 'D'},
		{4, 'E'},
		{5, 'F'},
		{6, 'G'},
		{7, 'H'}
	};
	vector<pair<int, int>> moves;
	vector<vector<int>> tempBoard = board;
	getMoveList(tempBoard, moves, player);
	if (!moves.empty()) {
		auto t1 = chrono::high_resolution_clock::now();

		minimaxDecision(board, player, pos);
		search(board, pos, player);
		cout << "Played posiiton: " << (pos.first + 1) << reverseMapBoard[pos.second] << endl << endl;

		auto t2 = std::chrono::high_resolution_clock::now();

		float duration = chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

		std::cout << "AI executuion time: " << duration / 1000000.0 << " seconds." << endl << endl;
	}
	else
		cout << "Player " << player << " should pass this round." << endl << endl;	
}

void readFile(vector<vector<int>> &board) {
	ifstream file;
	file.open("board.txt");
	std::string str;
	board.clear();
	while (getline(file, str)) {
		vector<int> v;
		for (int i = 0; i < str.length(); i++) {
			char c;
			if (str[i] == ' ')
				c = '0';
			else if (str[i] == 'O')
				c = '1';
			else if (str[i] == 'X')
				c = '2';
			v.push_back((c - '0'));
		}
		board.push_back(v);
	}
	file.close();
}

void writeFile(vector<vector<int>> board) {
	ofstream myfile("board.txt");
	if (myfile.is_open())
	{
		for (vector<int> v : board) {
			string str = "";
			for (int c : v) {
				char tmp;
				if (c == 0)
					tmp = ' ';
				else if (c == 1)
					tmp = 'O';
				else if (c == 2)
					tmp = 'X';
				str += tmp;
			}
			myfile << str << endl;
		}
		myfile.close();
	}
}

void writeResult(vector<string> str) {
	ofstream myfile("result.txt");
	if (myfile.is_open()) {
		for(string s : str)
			myfile << s << endl;
	}
	myfile.close();
}

int main() {
	map<char, int> mapBoard = {
		{'A', 0},
		{'B', 1},
		{'C', 2},
		{'D', 3},
		{'E', 4},
		{'F', 5},
		{'G', 6},
		{'H', 7}
	};

	pair<int, int> pos;

	vector<vector<int>> board;

	vector<string> str;

	int round = 0, scorePlayer1 = 0, scorePlayer2 = 0, player, n = 1;
	char symbol, input[3], selection[2];

	cout << "(1) Player vs Computer" << endl;
	cout << "(2) Computer vs Computer" << endl;
	cout << "(3) Computer vs Computer (100 run)" << endl;
	cout << "(4) Tournament" << endl;

	cin.getline(selection, sizeof(selection));

	if (selection[0] == '3')
		n = 100;

	for (int i = 0; i < n; i++) {
		auto t3 = chrono::high_resolution_clock::now();

		initializeBoard(board);

		writeFile(board);

		while (!gameOver(board)) {

			if (!(round % 2)) {
				player = 1;
				symbol = 'O';
			}
			else {
				player = 2;
				symbol = 'X';
			}

			printBoard(board, round, player, symbol, false);

			if (player == 2) {
				if (selection[0] == '1' || selection[0] == '2' || selection[0] == '3') {
					AImove(board, 2);
				}
				else if (selection[0] == '4') {
					readFile(board);
					AImove(board, 2);
					writeFile(board);
				}
				round++;
			}
			else {
				if (selection[0] == '1') {
					cout << endl << "Please enter a coordinate (Ex: 3D): ";
					cin.getline(input, sizeof(input));
					if (input[1] >= 'A' && input[1] <= 'H' && input[0] >= '1' && input[0] <= '8') {
						pos = make_pair(input[0] - '1', mapBoard[input[1]]);
						vector<pair<int, int>> movesPlayer1;
						vector<vector<int>> tempBoard = board;
						getMoveList(tempBoard, movesPlayer1, 1);
						if (!movesPlayer1.empty()) {
							if (search(tempBoard, pos, player)) {
								search(board, pos, player);
								round++;
							}
							else
								cout << "Please enter a valid coordinate." << endl;
						}
						else {
							cout << "Player " << player << " should pass this round." << endl;
							round++;
						}
					}
					else
						cout << "Please enter a valid coordinate." << endl;
				}
				else if (selection[0] == '2' || selection[0] == '3') {
					AImove(board, 1);
					round++;
				}
				else if (selection[0] == '4') {
					cout << "Opponent is being waited. Press any key to continue if the opponent made a move.";
					char tmp[2];
					cin.getline(tmp, sizeof(tmp));
					round++;
				}
			}
		}

		printBoard(board, round, player, symbol, true);

		scorePlayer1 = score(board, 1);
		scorePlayer2 = score(board, 2);

		string s = "";

		if (scorePlayer1 > scorePlayer2)
			s = "Player 1 wins! (O)";
		else if (scorePlayer2 > scorePlayer1)
			s = "Player 2 wins! (X)";
		else
			s = "Tie!";

		std::cout << s << endl;

		str.push_back(s);

		auto t4 = std::chrono::high_resolution_clock::now();

		float duration = chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();

		std::cout << "Whole game duration: " << duration / 1000000.0 << " seconds." << endl << endl;
	}

	writeResult(str);

	system("pause");
	return 0;
}