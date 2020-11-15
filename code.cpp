// Tic Tac Toe Game

#include<bits/stdc++.h>
#include <unistd.h>
using namespace std;

int inf = 1e9;

/*
	player2 is human
	player1 is computer

*/

int Player2 = -1;
int Player1 = 1;
int board[][3] = { { 1, -1, -1} ,
	{0, 1, 0} ,
	{0, 0, 0}
};


//function declaration

int evaluate (int state[][3]);
bool wins(int state[][3] , int player);
bool game_over(int state[][3]);
vector<pair<int , int>>  empty_cells(int state[][3]);
bool valid_move(int x , int y);
bool set_move(int x , int y , int player);
vector<int> minimax(int state[][3] , int depth , int player);
void clean();
void render(int state[][3] , char player1_choice , char player2_choice );
void player1_turn(char player1_choice , char player2_choice );
void player2_turn(char player1_choice , char player2_choice );




int evaluate (int state[][3]) {
	if (wins(state , Player1)) {
		return 1;
	} else if (wins(state , Player2)) {
		return -1;
	} else {
		return 0;
	}
}



bool wins(int state[][3] , int player) {
	int win_state[8][3] = {{state[0][0], state[0][1], state[0][2]},
		{state[1][0], state[1][1], state[1][2]},
		{state[2][0], state[2][1], state[2][2]},
		{state[0][0], state[1][0], state[2][0]},
		{state[0][1], state[1][1], state[2][1]},
		{state[0][2], state[1][2], state[2][2]},
		{state[0][0], state[1][1], state[2][2]},
		{state[2][0], state[1][1], state[0][2]}
	};

	int win_move[3] = {player, player, player};
	for (int i = 0; i < 8; ++i) {
		bool flag = true;
		for (int j = 0; j < 3; j++) {
			if (win_move[j] != win_state[i][j]) {
				flag = false;
				break;
			}
		}

		if (flag) {
			return true;
		}
	}
	return false;

}

bool game_over(int state[][3]) {
	return (wins(state , Player1) || wins(state , Player2) );
}

vector<pair<int , int>>  empty_cells(int state[][3]) {
	vector<pair<int , int> > cells;

	for (int x = 0 ; x < 3 ; x++) {
		for (int y = 0 ; y < 3 ; y++) {
			if (state[x][y] == 0) {
				cells.push_back({x , y});
			}
		}
	}

	return cells;
}

bool valid_move(int x , int y) {
	if (board[x][y] == 0) {
		return true;
	}

	return false;
}

bool set_move(int x , int y , int player) {
	if (valid_move(x , y)) {
		board[x][y] = player;
		return true;
	} else return false;
}

vector<int> minimax(int state[][3] , int depth , int player) {
	std::vector<int> best(3 , -1);

	if (player == Player1) {
		best[2] = -1 * inf;
	} else {
		best[2] =  inf;
	}


	if (depth == 0 || game_over(state)) {
		best[2] = evaluate(state);
		return best;
	}

	std::vector<pair<int , int>> cells = empty_cells(state);

	for (int i = 0 ; i < (int)cells.size() ; i++) {
		int x = cells[i].first;
		int y = cells[i].second;

		state[x][y] = player;



		if (wins(state , Player1)) {
			state[x][y] = 0;
			best[0] = x;
			best[1] = y;
			best[2] = inf;
			return best;

		}



		vector<int> score = minimax(state , depth - 1 , -1 * player);

		state[x][y] = 0;
		score[0] = x; score[1] = y;

		if (player == Player1) {
			if (score[2] > best[2]) {
				for (int j = 0 ; j < 3; j++) {
					best[j] = score[j];
				}
			}

		} else {
			if (score[2] < best[2]) {
				for (int j = 0 ; j < 3; j++) {
					best[j] = score[j];
				}

			}
		}

	}

	return best;

}


void clean() {
	system("clear");
}

void render(int state[][3] , char player1_choice , char player2_choice ) {
	map<int , char> chars;
	chars.insert({ -1 , player2_choice});
	chars.insert({1 , player1_choice});
	chars.insert({0 , ' '});


	string str_line = "---------------";

	cout << "\n" << str_line << "\n";

	for (int i = 0 ; i < 3; i++) {
		for (int j = 0; j < 3 ; j++) {
			cout << "| " << chars[state[i][j]] << " |";
		}
		cout << "\n" << str_line << "\n";
	}

	cout << "\n";


}

void player1_turn(char player1_choice , char player2_choice ) {
	int depth = 0;
	for (int i = 0 ; i < 3; i++) {
		for (int j = 0 ; j < 3; j++) {
			if (board[i][j] == 0) {
				depth++;
			}
		}
	}

	if (depth == 0 || game_over(board)) {
		return;
	}

	clean();
	cout << "Player1 turn [" << player1_choice << "]\n";
	render(board , player1_choice , player2_choice );

	int x , y;
	if (depth == 9) {
		// we can choose any
		srand(time(0));
		x = rand();
		x = x % 3;
		y = rand();
		y = y % 3;

	} else {
		std::vector<int> move = minimax(board , depth , Player1 );
		x = move[0];
		y = move[1];

	}

	set_move(x , y , Player1);
	// time.sleep(1);
	sleep(1);


}

void player2_turn(char player1_choice , char player2_choice ) {
	int depth = 0;
	for (int i = 0 ; i < 3; i++) {
		for (int j = 0 ; j < 3; j++) {
			if (board[i][j] == 0) {
				depth++;
			}
		}
	}

	if (depth == 0 || game_over(board)) {
		return;
	}


	cout << "Player2 turn [" << player2_choice << "]\n";
	render(board , player1_choice , player2_choice);



	int move = -1;

	while (move < 1 || move > 9) {
		cout << "Use numpad (1..9)\n";
		cin >> move;

		bool flag = true;

		int x = 0 , y = 0;
		for (x = 0; x < 3; x++) {

			for (y = 0 ; y < 3; y++) {
				if (3 * x + y + 1 == move ) {

					flag = false;
					break;

				}

			}
			if (!flag)break;
		}

		bool can_move = set_move(x , y , Player2);

		if (!can_move) {
			cout << "not possible\n";
			move = -1;
		}

	}


}


int main() {

	clean();
	char player1_choice = 'X';
	char player2_choice = 'O';

	system("clear");


	player1_turn(player1_choice , player2_choice);



	while ((int)((empty_cells(board)).size()) > 0 and !(game_over(board)) ) {

		player2_turn(player1_choice , player2_choice);
		player1_turn(player1_choice , player2_choice);
	}

	if (wins(board , Player2)) {
		clean();
		cout << "Player2 turn [" << player2_choice << "]\n";
		render(board , player1_choice , player2_choice );
		printf("Player2 WIN!\n");

	} else if (wins(board , Player1)) {
		clean();
		cout << "Player1 turn [" << player1_choice << "]\n";
		render(board , player1_choice , player2_choice );
		cout << "Player1 WIN!\n";
	} else {
		clean();
		render(board , player1_choice , player2_choice );
		cout << "DRAW!\n";
	}



	return 0;
}