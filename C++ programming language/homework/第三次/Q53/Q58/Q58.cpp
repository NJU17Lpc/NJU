#include<iostream>
#include<fstream>
#include<string>
const int Osuccess = 0;
const int Xsuccess = 1;
const int Dogfall = 2;
const int notEnd = 3;
using namespace std;


class Chess {
private:
	string type;
public:
	Chess() :type("") {}
	Chess(string type) :type(type) {}
	virtual string getType() { return type; }
};

class ChessX :public Chess {
public:
	ChessX() :Chess("X") {}
};

class ChessO :public Chess {
public:
	ChessO() :Chess("O") {}
};

class Board {
private:
	Chess*** board;
	int height;
	int width;
	int winLength;
	int chessNum;
	int checkRes() {
		if (height == 1 && width == 1) {
			if (board[0][0]->getType() == "X")
				return Xsuccess;
			else
				return Osuccess;
		}

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (board[i][j]->getType() == "") { continue; }
				for (int k = j+1; k < j+winLength && k<width; k++) {

					string a = board[i][k]->getType();
					string b = board[i][k - 1]->getType();
					if ((board[i][k]->getType() != board[i][k - 1]->getType())) {
						break;
					}
					else {
						if (k == j+winLength - 1) {
							if (board[i][j]->getType() == "X")
								return Xsuccess;
							else
								return Osuccess;
						}
					}
				}
			}
		}

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (board[i][j]->getType() == "") { continue; }

				for (int k = i+1; k < i+winLength && k<height; k++) {
					string a = board[k][j]->getType();
					string b = board[k-1][j]->getType();

					if ((board[k][j]->getType() != board[k-1][j]->getType())) {
						break;
					}
					else {
						if (k == i+winLength - 1) {
							if (board[i][j]->getType() == "X")
								return Xsuccess;
							else
								return Osuccess;
						}
					}
				}
			}
		}

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (board[i][j]->getType() == "") { continue; }

				for (int x = i+1, y=j+1; x < i+winLength && x<height && y < j + winLength && y < width; x++, y++) {
					if ((board[x][y]->getType() != board[x - 1][y-1]->getType())) {
						break;
					}
					else {
						if (x == i+winLength - 1) {
							if (board[i][j]->getType() == "X")
								return Xsuccess;
							else
								return Osuccess;
						}
					}
				}
			}
		}

		bool filled = true;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (board[i][j]->getType() == "") {
					filled = false;
				}
			}
		}
		if (filled) {
			return Dogfall;
		}
		//if (chessNum == width * height) {
		//	return Dogfall;
		//}

		return notEnd;
	}
public:
	Board(int m, int n):height(m), width(m), winLength(n),chessNum(0) {
		board = new Chess**[m];
		for (int i = 0; i < m; i++) {
			board[i] = new Chess*[m];
			for (int j = 0; j < m; j++) {
				board[i][j] = new Chess();
			}
		}

	}

	int addChess(int type, int m, int n) {
		if ((*board[m][n]).getType() == "") {
			switch (type) {
			case 0: {
				board[m][n] = new ChessO();
				chessNum++;
				break;
			}
			case 1: {
				board[m][n] = new ChessX();
				chessNum++;
				break;
			}
			default:
				cout << "not valid chess type" << endl;
				break;
			}
			
		}
		else {
			cout << "(" << m << "," << n << ")这个位置已经有棋子"<<endl;
		}
		return checkRes();
	}

};


int main() {
	//string s;
	//ofstream outfile("E:\\input.txt", ios::app);
	//for (int i = 0; i < 20; i++) {
	//	getline(cin, s);
	//	outfile << s << endl;
	//}
	//outfile << endl << endl;

	int m, n;
	int res;
	cin >> m >> n;
	Board b(m, n);
	while (true) {
		cin >> m >> n;
		res = b.addChess(0, m, n);
		if (res != notEnd) { break; }
		cin >> m >> n;
		res = b.addChess(1, m, n);
		if (res != notEnd) { break; }
	}
	if (res == Osuccess) {
		cout << "O Success";
	}
	else if (res == Xsuccess) {
		cout << "X Success";
	}
	else if (res = Dogfall) {
		cout << "Dogfall";
	}
	else {
		cout << "not a result";
	}
	return 0;
}