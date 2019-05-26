#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>

constexpr auto Depth = 2;
class Node {
public:
	std::vector<std::vector<int>> board;
	std::vector<std::vector<int>> step; // step list
	std::vector<std::pair<int, int>> black, white;
	std::vector<Node*> child;
	int color; // 0: undefined, 1: black, 2: white
	int depth; // root == 0
	int val;
public:
	Node() : color(0), depth(0), val(0) {}
	Node(std::vector<std::vector<int>> state) {
		board = state;
		color = 0;
		depth = 0;
		val = 0;
	}
	int utilityFunction(bool is_black);
	int evaluationFunction(bool is_black);
	bool terminal();
	void getBlack();	// get positions of all black pieces
	void getWhite();	// get positions of all white pieces
	void genChildren();	// generate all posible child and store it in child list
	void genSteps(int, int);	// generate all posible steps of a piece
	void hop(int, int);
};

class Minimax {
private:
	Node root;
	bool is_black;
	std::vector<std::vector<int>> step_list;

public:
	Minimax(int is_black) : is_black(is_black) {}
	void buildTree(std::vector<std::vector<int>> state);
	int maxVal(Node* n);
	int minVal(Node* n);
	bool cutoff_test(Node* n);
	std::vector<std::vector<int>> getSteplist();
	void printStep(); // debug
};

/****** for debugging ******/
std::vector<std::vector<int>> testBoard();
void printBoard(Node* n);
