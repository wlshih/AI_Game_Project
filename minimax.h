#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>
#include <stack>
#include "timer.h"

constexpr auto Depth = 3;
constexpr auto Hop_max = 5;
constexpr auto Time_lim = 3.9;
class Node {
public:
	std::vector<std::vector<int>> board;
	std::vector<std::vector<int>> step; // step list
	std::vector<std::pair<int, int>> black, white;
	std::vector<Node*> child;
	int color; // 0: undefined, 1: black, 2: white
	int depth; // root == 0
	int val;
	bool leaf;
public:
	Node() : color(0), depth(0), val(0), leaf(0) {}
	Node(std::vector<std::vector<int>> state) {
		board = state;
		color = 0;
		depth = 0;
		val = 0;
		leaf = 0;
	}
	int utilityFunction(bool is_black);
	int evaluationFunction(bool is_black);
	bool terminal();
	void getBlack();	// get positions of all black pieces
	void getWhite();	// get positions of all white pieces
	void genChildren();	// generate all posible child and store it in child list
	void genSteps(int, int);	// generate all posible steps of a piece
	void hop(int, int);
	void setVal(bool is_black); // set value
	void calChildVal(bool is_black);
	void sortChildVal(bool is_max);
	bool isLeaf();
};

struct HopNode {
	int r;
	int c;
	std::vector<std::vector<int>> board;
	std::vector<std::vector<int>> step; // step list
	HopNode(int r, int c, std::vector<std::vector<int>> board, std::vector<std::vector<int>> step) {
		this->r = r;
		this->c = c;
		this->board = board;
		this->step = step;
	}
};


class Minimax {
private:
	Node root;
	bool is_black;
	std::vector<std::vector<int>> step_list;

public:
	Minimax(int is_black) : is_black(is_black) {}
	void buildTree(std::vector<std::vector<int>> state);
	int maxVal(Node* n, int alpha, int beta);
	int minVal(Node* n, int alpha, int beta);
	bool cutoff_test(Node* n);
	std::vector<std::vector<int>> getSteplist();
	void releaseTree();
	void releaseChild(Node* n);
	void printStep(); // debug
};

bool cmpMin(Node* n1, Node* n2);
bool cmpMax(Node* n1, Node* n2);

/****** for debugging ******/
std::vector<std::vector<int>> testBoard();
void printBoard(Node* n);
