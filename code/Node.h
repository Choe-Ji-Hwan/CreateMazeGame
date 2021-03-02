#pragma once
#include <string>

// for Queue node (template)
class Node {
public:
	Node(std::string pa, int row, int col);	// constructor
	Node();			// default constructor 
	Node(Node& n);	// copy constructor

	std::string path;	// static path
	int curRow;			// node row
	int curCol;			// node col
};