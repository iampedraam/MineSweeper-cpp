#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

int order;
void printBoard(int size);
void initializeBoard(int size);
string board[33][33]; //easy: 21*21 - medium: 33*33 with lines
int boardSize;
void generateMine(int mines, int mineArraySize);
bool mine[16][16];
void gameplay();
int minesRemained;
int mineArraySize;
int row, coloumn;
bool checkMine(int r, int c);
bool lose = false;
int checkNeighbor(int r, int c);

int main() {

	srand(time(0));

	do {
		cout << "1- Play Game\n2- Exit\n\n";

		cin >> order;
		if (order > 2 || order < 1) {
			cout << "Wrong order number has been entered. enter 1 or 2.\n\n";
			system("pause");
		}
		system("cls");
	} while (order > 2 || order < 1);


	switch (order) {

	case 1:
		do {
			cout << "Difficulty level:\n1- Easy (10*10 / 10 mines) \n2- Medium (16*16 / 40 mines)\n\n";
			cin >> order;
			if (order > 2 || order < 1) {
				cout << "Wrong difficulty number is entered. Enter correct order number.\n\n";
				system("pause");
			}
			system("cls");
		} while (order > 2 || order < 1);
		break;
	case 2:
		system("pause");
		break;
	}

	if (order == 1) {
		boardSize = 21;
		minesRemained = 10;
		mineArraySize = 10;
		initializeBoard(boardSize);
		generateMine(minesRemained, mineArraySize);
		while (minesRemained > 0 && lose == false) {
			gameplay();
		}
	}
	else if (order == 2) {
		boardSize = 33;
		minesRemained = 40;
		mineArraySize = 16;
		initializeBoard(boardSize);
		generateMine(minesRemained, mineArraySize);
		while (minesRemained > 0 && lose == false) {
			gameplay();
			system("cls");
		}
	}


	//result
	if (lose) {
		cout << "\n\nYOU LOST THE GAME!\n\n";
	}
	else {
		cout << "\n\nYOU WIN THE GAME!\n\n";
	}

	return 0;
}




void initializeBoard(int size) {

	int numR = 1, numC = 1;

	for (int row = 0; row < size; row++) {

		for (int col = 0; col < size; col++) {

			if (row == 0 && col == 0) {
				board[row][col] = " ";
			}
			else if (col % 2 != 0) {
				if (row < 20 && col == 1) {
					board[row][col] = "  | ";
				}
				else {
					board[row][col] = " | ";
				}
			}
			else if (row == 0 && col % 2 == 0) {
				board[row][col] = to_string(numR);
				numR++;
			}
			else if (row % 2 != 0) {
				board[row][col] = "-";
			}
			else if (col == 0 && row % 2 == 0) {
				board[row][col] = to_string(numC);
				numC++;
			}
			else {
				board[row][col] = "?";
			}
		}
	}

}


void printBoard(int size) {

	for (int i = 0; i < size; i++) {

		for (int j = 0; j < size; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
	
}


void generateMine(int mines, int mineArraySize) {

	int i = 0, j = 0;
	int count = 0;

	while (count < mines) {

		i = rand() % mineArraySize;
		j = rand() % mineArraySize;
		if (count == 0) {
			mine[i][j] = true;
			count++;
		}
		else {
			if (mine[i][j]) {
				continue;
			}
			else {
				mine[i][j] = true;
				count++;
			}
		}
	}
}


bool checkMine(int r, int c) {

	if (mine[r][c]) {
		return true;
	}
	else {
		return false;
	}
}


int checkNeighbor(int r, int c) {

	int neighborMines = 0;

	if (mine[r + 1][c])
		neighborMines++;
	if (mine[r - 1][c])
		neighborMines++;
	if (mine[r][c + 1])
		neighborMines++;
	if (mine[r][c - 1])
		neighborMines++;
	if (mine[r + 1][c + 1])
		neighborMines++;
	if (mine[r + 1][c - 1])
		neighborMines++;
	if (mine[r - 1][c + 1])
		neighborMines++;
	if (mine[r - 1][c - 1])
		neighborMines++;


	return neighborMines;
}


void gameplay() {

	do {
		cout << "Bombs remaining: " << minesRemained << endl << endl;

		printBoard(boardSize);

		cout << "\n\n1- Choose a unit\n2- Insert a flag (to defuse mine)\n";
		cin >> order;

		if (order > 2 || order < 1) {
			cout << "wrong number entered.\n";
			system("pause");
			system("cls");
		}

	} while (order > 2 || order < 1);

	do {
		cout << "\nwhich unit? (first enter row number, then enter coloumn number)\n";
		cin >> row >> coloumn;
		system("cls");
		if (row < 1 || row>10 || coloumn < 1 || coloumn>10) {

			cout << "\nWrong row or coloumn (or both) has been entered.\n";
			system("pause");
			system("cls");

			cout << "Bombs remaining: " << minesRemained << endl << endl;

			printBoard(boardSize);
			cout << endl;
			if (order == 1) {
				cout << "Choose unit:";
			}
			else if (order == 2) {
				cout << "Insert flag:";
			}
		}
	} while (row < 1 || row>10 || coloumn < 1 || coloumn>10);

	row -= 1;
	coloumn -= 1;

	switch (order) {

	case 1: //choose unit
		if (checkMine(row, coloumn)) { //player loses
			lose = true;
			system("cls");
			break;
		}
		else { //continue game
			if (row > 0 && coloumn > 0) {
				board[row * 2 + 2][coloumn * 2 + 2] = to_string(checkNeighbor(row, coloumn));
			}
			else if (row == 0) {
				board[row + 2][coloumn * 2 + 2] = to_string(checkNeighbor(row, coloumn));
			}
			else if (coloumn == 0) {
				board[row * 2 + 2][coloumn + 2] = to_string(checkNeighbor(row, coloumn));
			}
		}
		break;
	case 2: //defuse bomb
		if (checkMine(row, coloumn)) {
			mine[row][coloumn] = false;
			minesRemained--;
			if (row > 0 && coloumn > 0) {
				board[row * 2 + 2][coloumn * 2 + 2] = "#";
			}
			else if (row == 0) {
				board[row + 2][coloumn * 2 + 2] = "#";
			}
			else if (coloumn == 0) {
				board[row * 2 + 2][coloumn + 2] = "#";
			}
		}
		else {
			if (row > 0 && coloumn > 0) {
				board[row * 2 + 2][coloumn * 2 + 2] = "#";
			}
			else if (row == 0) {
				board[row + 2][coloumn * 2 + 2] = "#";
			}
			else if (coloumn == 0) {
				board[row * 2 + 2][coloumn + 2] = "#";
			}
		}
		system("cls");
		break;
	}
}