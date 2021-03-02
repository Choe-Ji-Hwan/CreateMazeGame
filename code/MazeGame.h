#pragma once
#include <iostream>
#include "Node.h"
#include "queueLnk.cpp"
using namespace std;

class MazeGame {
public:
	
	MazeGame(int row, int col, int num);	// constructor
	~MazeGame();							// destructor

	void run();		// Execute the program
	bool setMazeState(string state);	// Make Maze

	bool push(int row, int col, int drow, int dcol);	// Check push possible
	bool walk(int row, int col, int drow, int dcol);	// Check walk possible

	// First find (Box)->(Target) minimum path
	string findBfsPathBox();

	// Second find (Worker)->(before Box Arrival cell) minimum path
	string findBfsPathWorker(string boxMove, int pBoxRow, int pBoxCol, 
		int pWorkerRow, int pWorkerCol);

	// findBfsPathWorker's sub function (actual BFS saved)
	string findBfsPathWorkerSub(int tRow, int tCol);

	// Use only two-dimensional 'visited' arrays for initialization
	void visitedClear(bool**& map);

private:

	// Maze state
	int r;					// row«‡(y)
	int c;					// columnø≠(x)
	int mazeNumbering;		// number of maze

	// Maze information
	char** maze;			// maze information
	bool** visited;			// visit information
	bool** initVisited;		// copy visit information

	// Worker information(index)
	int workerRow;
	int workerCol;

	// Target information(index)
	int targetRow;
	int targetCol;

	// Box information(index)
	int boxRow;
	int boxCol;
};