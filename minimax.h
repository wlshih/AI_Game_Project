#include <cstdio>
#include <vector>
#include <algorithm>

constexpr auto Depth = 4;
class Node {
public:
	std::vector<std::vector<int>> board;
	std::vector<std::vector<int>> step; // step list
	std::vector<std::pair<int, int>> black, white;
	std::vector<Node*> child;
	int color; // 0: undefined, 1: black, 2: white
	int depth; // root == 0
public:
	Node(std::vector<std::vector<int>> s) {
		board = s;
		color = 0;
		depth = 0;
	}
	int utilityFunction(bool is_black);
	int evaulationFunction(bool is_black);
	bool terminal();
	void getBlack();	// get positions of all black pieces
	void getWhite();	// get positions of all white pieces
	void genChildren();	// generate all posible child and store it in child list
	void genSteps(int, int);	// generate all posible steps of a piece
	void hop(int, int, Node);
};

class Minimax {
private:
	Node root;
	bool is_black;

public:
	void buildTree(std::vector<std::vector<int>> s);
	int maxVal(Node n);
	int minVal(Node n);
};
