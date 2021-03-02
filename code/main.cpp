#include "MazeGame.h"

using namespace std;

int main() {
	int r, c, number = 0;
	
	while (true) {
		cin >> r >> c;
		if (r == 0 && c == 0) return 0;
		else if (r <= 20 || c <= 20) {
			MazeGame mazeTransferBox(r, c, ++number);
			mazeTransferBox.run();
		}
		else {	cout << "Error, Maybe Row or Column size exceeded" << endl; }
	}
}