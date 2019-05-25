#include <cstdio>
#include <vector>
#include <list>

class Node {
public:
	std::vector<std::vector<int>> board;
	std::vector<std::vector<int>> step;
	std::vector<std::pair<int, int>> black, white;
	std::list<Node> child;
	int color; // 0: undefined, 1: black, 2: white
public:
	Node(std::vector<std::vector<int>> s) {
		int ismin = 0;
		board = s;
	}
	int evaulationFunction(bool is_black);
	void getBlack();	// get positions of all black pieces
	void getWhite();	// get positions of all white pieces
	void genChildren();	// generate all posible child and store it in child list
	void genSteps(int, int);
};

class Minimax {
private:
	Node root;
public:
	void buildTree(std::vector<std::vector<int>> s);
	int maxVal(Node n);
	int minVal(Node n);
	bool terminal(std::vector<std::vector<int>> s);
};
