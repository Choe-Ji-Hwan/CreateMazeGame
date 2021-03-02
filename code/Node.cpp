#include "Node.h"

// constructor
Node::Node(std::string pa, int row, int col)
{
	path = pa;
	curRow = row;
	curCol = col;
}

// default constructor
Node::Node() {}

// copy constructor
Node::Node(Node & n) {
	path = n.path;
	curRow = n.curRow;
	curCol = n.curCol;
}
