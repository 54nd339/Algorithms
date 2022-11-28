#include <bits/stdc++.h>
using namespace std;

#define WIN 1000
#define	DRAW 0
#define LOSS -1000

#define AI_MARKER 'O'
#define PLAYER_MARKER 'X'
#define EMPTY_SPACE '-'

vector<vector<pair<int, int>>> winningStates = {
    // Horizontal
    {{0, 0}, {0, 1}, {0, 2}},
    {{1, 0}, {1, 1}, {1, 2}},
    {{2, 0}, {2, 1}, {2, 2}},
    // Vertical
    {{0, 0}, {1, 0}, {2, 0}},
    {{0, 1}, {1, 1}, {2, 1}},
    {{0, 2}, {1, 2}, {2, 2}},
    // Diagonal
    {{0, 0}, {1, 1}, {2, 2}},
    {{0, 2}, {1, 1}, {2, 0}}
};

void printState(int state) {
	if (WIN == state) { cout << "WIN" << endl; }
	else if (DRAW == state) { cout << "DRAW" << endl; }
	else if (LOSS == state) { cout << "LOSS" << endl; }
}
void printBoard(char board[3][3]) {
	cout << endl;
	cout << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
	cout << "----------" << endl;
	cout << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
	cout << "----------" << endl;
	cout << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl << endl;
}

// Get all available legal moves (spaces that are not occupied)
vector<pair<int, int>> getEmptySpaces(char board[3][3]) {
	vector<pair<int, int>> spaces;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] != AI_MARKER && board[i][j] != PLAYER_MARKER)
				spaces.push_back(make_pair(i, j));
		}
	}
	return spaces;
}
// Check if a position is occupied
bool isOccupied(char board[3][3], pair<int, int> pos) {
	vector<pair<int, int>> spaces = getEmptySpaces(board);
	for (auto it : spaces) {
        if (it == pos) return false;
    }
	return true;
}
// Get all board positions occupied by the given marker
vector<pair<int, int>> getOccupiedSpaces(char board[3][3], char marker) {
	vector<pair<int, int>> occupied;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (marker == board[i][j])
                occupied.push_back(make_pair(i, j));
		}
	}
	return occupied;
}
// Check if the board is full
bool isFull(char board[3][3]) {
	vector<pair<int, int>> spaces = getEmptySpaces(board);
	return (0 == spaces.size());
}
// Check if the game has been won
bool checkWin(vector<pair<int, int>> occupied) {
	bool res;
	for (int i = 0; i < winningStates.size(); i++) {
		res = true;
		vector<pair<int, int>> curr_win_state = winningStates[i];
		for (int j = 0; j < 3; j++) {
			if (!(find(begin(occupied), end(occupied), curr_win_state[j]) != end(occupied))) {
				res = false; break;
			}
		}
		if (res) break;
	}
	return res;
}
// Check if someone has won or lost
int getBoardState(char board[3][3], char marker) {
	char opponent = marker == PLAYER_MARKER ? AI_MARKER : PLAYER_MARKER;
	
    vector<pair<int, int>> occupied = getOccupiedSpaces(board, marker);
	bool is_won = checkWin(occupied);
	if (is_won) return WIN;

	occupied = getOccupiedSpaces(board, opponent);
	bool is_lost = checkWin(occupied);
	if (is_lost) return LOSS;

	return DRAW;
}

// Apply the minimax game optimization algorithm
pair<int, pair<int, int>> minimax_optimization(char board[3][3], char marker, int depth, int alpha, int beta) {
	// Initialize best move
	pair<int, int> best_move = make_pair(-1, -1);
	int best_score = (marker == AI_MARKER) ? LOSS : WIN;

	// If we hit a terminal state (leaf node), return the best score and move
	if (isFull(board) || DRAW != getBoardState(board, AI_MARKER)) {
		best_score = getBoardState(board, AI_MARKER);
		return make_pair(best_score, best_move);
	}

	vector<pair<int, int>> spaces = getEmptySpaces(board);
	for (auto it : spaces) {
		pair<int, int> curr_move = it;
		board[curr_move.first][curr_move.second] = marker;

		// Maximizing player's turn
		if (marker == AI_MARKER) {
			int score = minimax_optimization(board, PLAYER_MARKER, depth + 1, alpha, beta).first;
			// Get the best scoring move
			if (best_score < score) {
				best_score = score - depth * 10;
				best_move = curr_move;

				// Check if this branch's best move is worse than the best
				// option of a previously search branch. If it is, skip it
				alpha = max(alpha, best_score);
				board[curr_move.first][curr_move.second] = EMPTY_SPACE;
				if (beta <= alpha) break;
			}

		} // Minimizing opponent's turn
		else {
			int score = minimax_optimization(board, AI_MARKER, depth + 1, alpha, beta).first;

			if (best_score > score) {
				best_score = score + depth * 10;
				best_move = curr_move;

				// Check if this branch's best move is worse than the best
				// option of a previously search branch. If it is, skip it
				beta = min(beta, best_score);
				board[curr_move.first][curr_move.second] = EMPTY_SPACE;
				if (beta <= alpha) break;
			}

		}
		board[curr_move.first][curr_move.second] = EMPTY_SPACE; // Undo move
	}
	return make_pair(best_score, best_move);
}
// Check if the game is finished
bool isOver(char board[3][3]) {
	if (isFull(board)) return true;
    if (getBoardState(board, AI_MARKER) != DRAW) return true;
	return false;
}

int main() {
	char board[3][3] = { EMPTY_SPACE };
	cout << "********************************\n\n\tTic Tac Toe AI\n\n********************************" << endl << endl;
	cout << "Player = X\t AI Computer = O" << endl << endl;
	printBoard(board);

	while (!isOver(board)) {
		int row, col;
		cout << "Enter Row Col: ";
		cin >> row >> col;
		cout << endl << endl;

		if (isOccupied(board, make_pair(row, col))) {
			cout << "The position (" << row << ", " << col << ") is occupied. Try another one..." << endl;
			continue;
		}
		else
            board[row][col] = PLAYER_MARKER;

		pair<int, pair<int, int>> ai_move = minimax_optimization(board, AI_MARKER, 0, LOSS, WIN);
		board[ai_move.second.first][ai_move.second.second] = AI_MARKER;
		printBoard(board);
	}

	cout << "********** GAME OVER **********" << endl << endl;
	int player_state = getBoardState(board, PLAYER_MARKER);
	cout << "PLAYER "; printState(player_state);

	return 0;
}