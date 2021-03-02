#include "MazeGame.h"

// constructor
MazeGame::MazeGame(int row, int col, int num)
	: r(row), c(col), mazeNumbering(num),
	workerRow(0), workerCol(0)
{
	maze = new char*[r];
	visited = new bool*[r];
	initVisited = new bool*[r];

	for (int i = 0; i < r; i++) {
		maze[i] = new char[c];
		visited[i] = new bool[c];
		initVisited[i] = new bool[c];
	}
	// initialization
	visitedClear(visited);
	visitedClear(initVisited);
}

// destructor
MazeGame::~MazeGame()
{
	for (int i = 0; i < r; i++) {
		delete[] visited[i];
		delete[] maze[i];
	}
	delete[] maze;
	delete[] visited;
}

// Execute the program
void MazeGame::run()
{
	string stateOfMaze;	// maze state variable
	string temp;
	string saveBoxPath;	// save Box->Target BFS path(upper case)

	// input MazeState
	for (int i = 0; i < r; i++) {
		cin >> temp;
		stateOfMaze += temp;
	}

	// check maze state
	if (setMazeState(stateOfMaze)) {

		// save initialization visited array
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++)
				initVisited[i][j] = visited[i][j];
		}

		int saveBoxRow = boxRow;	// save initial index of box
		int saveBoxCol = boxCol;
		int saveWorkerRow = workerRow;	// save initial index of worker
		int saveWorkerCol = workerCol;

		cout << "Maze #" << mazeNumbering << endl;

		saveBoxPath = findBfsPathBox();	// first BFS

		if (saveBoxPath != "Impossible.") {

			// Initialization
			for (int i = 0; i < r; i++) {
				for (int j = 0; j < c; j++)
					visited[i][j] = initVisited[i][j];
			}

			string result = findBfsPathWorker(saveBoxPath, saveBoxRow, saveBoxCol,
				saveWorkerRow, saveWorkerCol);	// second BFS

			if (result == "") cout << "Impossible." << endl << endl;
			else {
				cout << result << endl << endl;
			}
		}
		else cout << "Impossible." << endl << endl;
	}
}

// Make Maze
bool MazeGame::setMazeState(string state)
{
	bool nomal = true;	// create maze?

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {

			switch (state[c*i + j]) {

			case '#': {	maze[i][j] = '#';	visited[i][j] = 1; break; }
			case '.': { maze[i][j] = '.'; break; }
			case 'S': { maze[i][j] = 'S';
				workerRow = i;
				workerCol = j;
				break;
			}
			case 'B': { maze[i][j] = 'B'; visited[i][j] = 1;
				boxRow = i;
				boxCol = j;
				break;
			}
			case 'T': { maze[i][j] = 'T';
				targetRow = i;
				targetCol = j;
				break;
			}
			default: {
				cout << "Maze #" << mazeNumbering <<" error : error maze" << endl;
				nomal = false;	// creating maze fail
				break;
			}
			}
			if (!nomal) break;
		}
		if (!nomal) {
			break;
		}
	}
	return nomal;
}

// check push possible
bool MazeGame::push(int row, int col, int drow, int dcol)
{
	// beyond the array range
	if (row + drow >= r || col + dcol >= c ||
		row + drow < 0 || col + dcol < 0)
		return false;
	// WALL
	else if (maze[row + drow][col + dcol] == '#')
		return false;

	else if (maze[row + drow][col + dcol] == '.' ||
		maze[row + drow][col + dcol] == 'T')
		return true;
}

// check walk possible
bool MazeGame::walk(int row, int col, int drow, int dcol)
{
	// beyond the array range
	if (row + drow >= r || col + dcol >= c ||
		row + drow < 0 || col + dcol < 0)
		return false;
	// WALL and BOX
	else if (maze[row + drow][col + dcol] == '#' ||
		maze[row + drow][col + dcol] == 'B')
		return false;

	else if (maze[row + drow][col + dcol] == '.')
		return true;
}

// First find Box->Target minimum path
// Save path in uppercase (assume pushed)
string MazeGame::findBfsPathBox()
{
	int direction[4][2];
	char wordDirec[4][2];

	// The relative positions of the Box and Target 
	// allow you to obtain the minimum of several paths.

	// If it is skewed up to the left
	if (targetRow <= boxRow && targetCol <= boxCol) {
		direction[0][0] = 0;	direction[0][1] = -1;
		direction[1][0] = -1;	direction[1][1] = 0;
		direction[2][0] = 0;	direction[2][1] = 1;
		direction[3][0] = 1;	direction[3][1] = 0;

		wordDirec[0][0] = 'w';	wordDirec[0][1] = 'W';
		wordDirec[1][0] = 'n';	wordDirec[1][1] = 'N';
		wordDirec[2][0] = 'e';	wordDirec[2][1] = 'E';
		wordDirec[3][0] = 's';	wordDirec[3][1] = 'S';
	}
	// If it is skewed down to the left
	else if (targetRow >= boxRow && targetCol <= boxCol) {
		direction[0][0] = 1;	direction[0][1] = 0;
		direction[1][0] = 0;	direction[1][1] = -1;
		direction[2][0] = -1;	direction[2][1] = 0;
		direction[3][0] = 0;	direction[3][1] = 1;

		wordDirec[0][0] = 's';	wordDirec[0][1] = 'S';
		wordDirec[1][0] = 'w';	wordDirec[1][1] = 'W';
		wordDirec[2][0] = 'n';	wordDirec[2][1] = 'N';
		wordDirec[3][0] = 'e';	wordDirec[3][1] = 'E';
	}
	// If it is skewed up to the right
	else if (targetRow <= boxRow && targetCol >= boxCol) {
		direction[0][0] = 0;	direction[0][1] = 1;
		direction[1][0] = -1;	direction[1][1] = 0;
		direction[2][0] = 0;	direction[2][1] = -1;
		direction[3][0] = 1;	direction[3][1] = 0;

		wordDirec[0][0] = 'e';	wordDirec[0][1] = 'E';
		wordDirec[1][0] = 'n';	wordDirec[1][1] = 'N';
		wordDirec[2][0] = 'w';	wordDirec[2][1] = 'W';
		wordDirec[3][0] = 's';	wordDirec[3][1] = 'S';
	}
	// If it is skewed down to the right
	else if (targetRow >= boxRow && targetCol >= boxCol) {
		direction[0][0] = 1;	direction[0][1] = 0;
		direction[1][0] = 0;	direction[1][1] = 1;
		direction[2][0] = -1;	direction[2][1] = 0;
		direction[3][0] = 0;	direction[3][1] = -1;

		wordDirec[0][0] = 's';	wordDirec[0][1] = 'S';
		wordDirec[1][0] = 'e';	wordDirec[1][1] = 'E';
		wordDirec[2][0] = 'n';	wordDirec[2][1] = 'N';
		wordDirec[3][0] = 'w';	wordDirec[3][1] = 'W';
	}

	// node for queue
	Node temp("", boxRow, boxCol);
	Node cur("", boxRow, boxCol);

	// BFS (Box)->(Target)
	Queue<Node> q;
	visited[boxRow][boxCol] = 1;

	q.enqueue(temp);

	while (!q.empty()) {
		cur = q.getFront();
		boxRow = cur.curRow;
		boxCol = cur.curCol;
		q.dequeue();

		if (visited[targetRow][targetCol] == 1) {
			return cur.path;
		}
		// four-direction check
		for (int i = 0; i < 4; i++) {
			temp = cur;
			int drow = direction[i][0];
			int dcol = direction[i][1];

			if (push(cur.curRow, cur.curCol, drow, dcol)) {
				temp.path += wordDirec[i][1];	// accumulating path
				temp.curRow = boxRow + drow;
				temp.curCol = boxCol + dcol;

				// visited check
				if (visited[temp.curRow][temp.curCol] == 0) {
					visited[temp.curRow][temp.curCol] = 1;
					if (visited[targetRow][targetCol] == 1) {
						boxRow = cur.curRow;
						boxCol = cur.curCol;
						q.clear();
						// find
						return temp.path;
					}
					q.enqueue(temp);
				}
			}
		}

	}
	return "Impossible.";
}

// Second find (Worker)->(before Box Arrival cell) minimum path
// Save path in lowercase representation of the orientation (assume walk)
string MazeGame::findBfsPathWorker(string boxMove, int pBoxRow, int pBoxCol, int pWorkerRow, int pWorkerCol) {

	int length = boxMove.length();	// save 
	char saveDirection;			// a variable that identifies a sequence of directions.
	int saveBoxRow = pBoxRow;
	int saveBoxCol = pBoxCol;
	string plusPath("");		// save lower case path + upper case path 

	// Initialize information (to the original location of the transferred box)
	boxRow = pBoxRow;
	boxCol = pBoxCol;

	saveDirection = 'R';	// else 'W', 'N', 'E', 'S' direction
	// 'R' mean start, 'V' mean stop

	for (int i = 0; i < length; i++) {
		if (saveDirection == 'V') break;	// impossible case
		switch (boxMove[i])
		{
		case 'W': {
			if (saveDirection == 'W') {
				// Initialize Visited Array
				for (int i = 0; i < r; i++) {
					for (int j = 0; j < c; j++)
						visited[i][j] = initVisited[i][j];
				}
				visited[saveBoxRow][saveBoxCol] = 0;

				// move
				maze[workerRow][workerCol] = '.';
				maze[pBoxRow][pBoxCol] = '.';
				workerCol -= 1;
				pBoxCol -= 1;
				maze[workerRow][workerCol] = 'S';
				maze[pBoxRow][pBoxCol] = 'B';
				// move end

				plusPath += boxMove[i];
			
				break;
			}
			else {
				// Initialize Visited Array
				for (int i = 0; i < r; i++) {
					for (int j = 0; j < c; j++)
						visited[i][j] = initVisited[i][j];
				}
				visited[saveBoxRow][saveBoxCol] = 0;
				if (!walk(pBoxRow, pBoxCol, 0, 1)) {
					saveDirection = 'V';
					break;
				}
				plusPath
					+= (findBfsPathWorkerSub(pBoxRow, pBoxCol + 1)
						+ boxMove[i]);
				saveDirection = 'W';
				// move
				maze[workerRow][workerCol] = '.';
				maze[pBoxRow][pBoxCol] = '.';
				workerCol -= 1;
				pBoxCol -= 1;
				maze[workerRow][workerCol] = 'S';
				maze[pBoxRow][pBoxCol] = 'B';
				// move end
			}
			break;
		}
		case 'N': {
			if (saveDirection == 'N') {
				// Initialize Visited Array
				for (int i = 0; i < r; i++) {
					for (int j = 0; j < c; j++)
						visited[i][j] = initVisited[i][j];
				}
				visited[saveBoxRow][saveBoxCol] = 0;

				// move
				maze[workerRow][workerCol] = '.';
				maze[pBoxRow][pBoxCol] = '.';
				workerRow -= 1;
				pBoxRow -= 1;
				maze[workerRow][workerCol] = 'S';
				maze[pBoxRow][pBoxCol] = 'B';
				// move end

				plusPath += boxMove[i];

				break;
			}
			else {
				// Initialize Visited Array
				for (int i = 0; i < r; i++) {
					for (int j = 0; j < c; j++)
						visited[i][j] = initVisited[i][j];
				}
				visited[saveBoxRow][saveBoxCol] = 0;
				if (!walk(pBoxRow, pBoxCol, 1, 0)) {
					saveDirection = 'V';
					break;
				}
				plusPath
					+= (findBfsPathWorkerSub(pBoxRow + 1, pBoxCol)
						+ boxMove[i]);
				saveDirection = 'N';
				// move
				maze[workerRow][workerCol] = '.';
				maze[pBoxRow][pBoxCol] = '.';
				workerRow -= 1;
				pBoxRow -= 1;
				maze[workerRow][workerCol] = 'S';
				maze[pBoxRow][pBoxCol] = 'B';
				// move end.

			}
			break;
		}
		case 'E': {
			// Initialize Visited Array
			if (saveDirection == 'E') {
				for (int i = 0; i < r; i++) {
					for (int j = 0; j < c; j++)
						visited[i][j] = initVisited[i][j];
				}
				visited[saveBoxRow][saveBoxCol] = 0;

				maze[workerRow][workerCol] = '.';
				maze[pBoxRow][pBoxCol] = '.';
				workerCol += 1;
				pBoxCol += 1;
				maze[workerRow][workerCol] = 'S';
				maze[pBoxRow][pBoxCol] = 'B';
				plusPath += boxMove[i];

				break;
			}
			else {
				// Initialize Visited Array
				for (int i = 0; i < r; i++) {
					for (int j = 0; j < c; j++)
						visited[i][j] = initVisited[i][j];
				}
				visited[saveBoxRow][saveBoxCol] = 0;
				if (!walk(pBoxRow, pBoxCol, 0, -1)) {
					saveDirection = 'V';
					break;
				}
				plusPath
					+= (findBfsPathWorkerSub(pBoxRow, pBoxCol - 1)
						+ boxMove[i]);
				saveDirection = 'E';
				// move
				maze[workerRow][workerCol] = '.';
				maze[pBoxRow][pBoxCol] = '.';
				workerCol += 1;
				pBoxCol += 1;
				maze[workerRow][workerCol] = 'S';
				maze[pBoxRow][pBoxCol] = 'B';
				// move end
			}
			break;
		}
		case 'S': {
			if (saveDirection == 'S') {
				// Initialize Visited Array
				for (int i = 0; i < r; i++) {
					for (int j = 0; j < c; j++)
						visited[i][j] = initVisited[i][j];
				}
				visited[saveBoxRow][saveBoxCol] = 0;

				// move
				maze[workerRow][workerCol] = '.';
				maze[pBoxRow][pBoxCol] = '.';
				workerRow += 1;
				pBoxRow += 1;
				maze[workerRow][workerCol] = 'S';
				maze[pBoxRow][pBoxCol] = 'B';
				// move end

				plusPath += boxMove[i];

				break;
			}
			else {
				// Initialize Visited Array
				for (int i = 0; i < r; i++) {
					for (int j = 0; j < c; j++)
						visited[i][j] = initVisited[i][j];
				}
				visited[saveBoxRow][saveBoxCol] = 0;
				if (!walk(pBoxRow, pBoxCol, -1, 0)) {
					saveDirection = 'V';
					break;
				}
				plusPath
					+= (findBfsPathWorkerSub(pBoxRow - 1, pBoxCol)
						+ boxMove[i]);
				saveDirection = 'S';
				// move
				maze[workerRow][workerCol] = '.';
				maze[pBoxRow][pBoxCol] = '.';
				workerRow += 1;
				pBoxRow += 1;
				maze[workerRow][workerCol] = 'S';
				maze[pBoxRow][pBoxCol] = 'B';
				// move end

			}
		default: break;
		}
		}
	}
	return plusPath;
}

// Second find (Worker)->(before Box Arrival cell) minimum path sub function
string MazeGame::findBfsPathWorkerSub(int tRow, int tCol) {

	// node for queue
	Node temp("", workerRow, workerCol);
	Node cur("", workerRow, workerCol);

	int direction[4][2];
	char wordDirec[4][2];

	// The relative positions of the Box and Target 
	// allow you to obtain the minimum of several paths.

	// If it is skewed up to the left
	if (boxRow <= workerRow && boxCol <= workerCol) {
		direction[0][0] = 0;	direction[0][1] = -1;
		direction[1][0] = -1;	direction[1][1] = 0;
		direction[2][0] = 0;	direction[2][1] = 1;
		direction[3][0] = 1;	direction[3][1] = 0;

		wordDirec[0][0] = 'w';	wordDirec[0][1] = 'W';
		wordDirec[1][0] = 'n';	wordDirec[1][1] = 'N';
		wordDirec[2][0] = 'e';	wordDirec[2][1] = 'E';
		wordDirec[3][0] = 's';	wordDirec[3][1] = 'S';
	}
	// If it is skewed down to the left
	else if (boxRow >= workerRow && boxCol <= workerCol) {
		direction[0][0] = 1;	direction[0][1] = 0;
		direction[1][0] = 0;	direction[1][1] = -1;
		direction[2][0] = -1;	direction[2][1] = 0;
		direction[3][0] = 0;	direction[3][1] = 1;

		wordDirec[0][0] = 's';	wordDirec[0][1] = 'S';
		wordDirec[1][0] = 'w';	wordDirec[1][1] = 'W';
		wordDirec[2][0] = 'n';	wordDirec[2][1] = 'N';
		wordDirec[3][0] = 'e';	wordDirec[3][1] = 'E';
	}
	// If it is skewed up to the right
	else if (boxRow <= workerRow && boxCol >= workerCol) {
		direction[0][0] = 0;	direction[0][1] = 1;
		direction[1][0] = -1;	direction[1][1] = 0;
		direction[2][0] = 0;	direction[2][1] = -1;
		direction[3][0] = 1;	direction[3][1] = 0;

		wordDirec[0][0] = 'e';	wordDirec[0][1] = 'E';
		wordDirec[1][0] = 'n';	wordDirec[1][1] = 'N';
		wordDirec[2][0] = 'w';	wordDirec[2][1] = 'W';
		wordDirec[3][0] = 's';	wordDirec[3][1] = 'S';
	}
	// If it is skewed down to the right
	else if (boxRow >= workerRow && boxCol >= workerCol) {
		direction[0][0] = 1;	direction[0][1] = 0;
		direction[1][0] = 0;	direction[1][1] = 1;
		direction[2][0] = -1;	direction[2][1] = 0;
		direction[3][0] = 0;	direction[3][1] = -1;

		wordDirec[0][0] = 's';	wordDirec[0][1] = 'S';
		wordDirec[1][0] = 'e';	wordDirec[1][1] = 'E';
		wordDirec[2][0] = 'n';	wordDirec[2][1] = 'N';
		wordDirec[3][0] = 'w';	wordDirec[3][1] = 'W';
	}

	// node for queue
	Queue<Node> q;
	visited[workerRow][workerCol] = 1;

	q.enqueue(temp);

	while (!q.empty()) {
		if (tRow < 0 || tCol < 0 || tRow > r || tCol > c) break;
		cur = q.getFront();
		workerRow = cur.curRow;
		workerCol = cur.curCol;
		q.dequeue();

		if (visited[tRow][tCol] == 1)
			return cur.path;

		// four-direction check
		for (int i = 0; i < 4; i++) {
			temp = cur;
			int drow = direction[i][0];
			int dcol = direction[i][1];

			if (walk(cur.curRow, cur.curCol, drow, dcol)) {
				temp.path += wordDirec[i][0];	// accumulating path
				temp.curRow = workerRow + drow;
				temp.curCol = workerCol + dcol;

				// visited check
				if (visited[temp.curRow][temp.curCol] == 0) {
					visited[temp.curRow][temp.curCol] = 1;
					// find
					if (visited[tRow][tCol] == 1) {
						q.clear();
						workerRow = tRow;
						workerCol = tCol;
						return temp.path;
					}
					q.enqueue(temp);
				}
			}
		}
	}
	return "Impossible.";
}

// Use only two-dimensional 'visited' arrays for initialization
void MazeGame::visitedClear(bool **& map) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			map[i][j] = 0;
		}
	}
}