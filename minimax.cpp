#include "minimax.h"

int Node::utilityFunction(bool is_black) {
	int score = 0;
	if (is_black) {
		if (black[0].first >= 6) 
			score = INT_MAX;
		else
			score = INT_MIN;
		
	}
	else {
		if (white[0].first <= 1)
			score = INT_MAX;
		else
			score = INT_MIN;
	}
	val = score; // store to node
	return score;
}
int Node::evaluationFunction(bool is_black){
	int score = 0;
	if(is_black){
		for(int i=0;i<black.size();i++){
			if(black[i].first <= 4){score+=black[i].first;}
			else{score+=10;}
		}
		for(int i=0;i<white.size();i++){
			if(white[i].first >= 3){score-=(7-white[i].first);}
			else{score-=10;}
		}
		(black.size()-white.size())*5;
	}
	else{
		for(int i=0;i<black.size();i++){
			if(black[i].first <= 4){score-=black[i].first;}
			else{score-=10;}
		}
		for(int i=0;i<white.size();i++){
			if(white[i].first >= 3){score+=(7-white[i].first);}
			else{score+=10;}
		}
		(white.size()-black.size())*5;
	}
	val = score; // store to node
	return score;
}

bool Node::terminal() {
	if (this->white.size() == 0 || this->black.size() == 0)
		return false;

	bool white = 1; // if all whites are in left green area
	bool black = 1; // if all blacks are in right green area
	for(int i=0; i<8; i++) {
		for(int j=0; j<6; j++) {
			if(board[i][j] == 1) black = 0;
		}
	}
	for(int i=0; i<8; i++) {
		for(int j=2; j<8; j++) {
			if(board[i][j] == 2) white = 0;
		}
	}

	return (white || black);
}

void Node::getBlack() {
	black.clear();
	for(int r=0; r<8; r++) {
		for(int c=0; c<8; c++) {
			if(board[r][c] == 1) {
				std::pair<int, int> tmp;
				tmp.first = r;
				tmp.second = c;
				black.push_back(tmp);
			}
		}
	}
}

void Node::getWhite() {
	white.clear();
	for(int r=0; r<8; r++) {
		for(int c=0; c<8; c++) {
			if(board[r][c] == 2) {
				std::pair<int, int> tmp;
				tmp.first = r;
				tmp.second = c;
				white.push_back(tmp);
			}
		}
	}
}

// generate all children of next step
void Node::genChildren() {
	std::cout << "genChildren" << black.size() << "," << white.size() << std::endl;
	if(color == 1) { // black
		for(int i=0; i<black.size(); i++) {
			genSteps(black[i].first, black[i].second);
		}
	}
	else if (color == 2) { // white
		for(int i=0; i<white.size(); i++) {
			genSteps(white[i].first, white[i].second);
		}
	}
	else std::cerr << "my color not set\n";

	printf("color(%d):%d, depth:%d\n", color, depth);
	// for(std::vector<Node*>::iterator it=child.begin(); it!=child.end(); it++) {
	// 	printBoard(*it);
	// }
}

// generate all posible steps of a piece and store to list
// move/hop up + down + left + right
void Node::genSteps(int r, int c) {
	// move up
	if((r-1) >= 0 && board[r-1][c] == 0) {
		Node* n = new Node(board);
		n->board[r][c] = 0;
		n->board[r-1][c] = color;

		std::vector<int> pos = {r, c};
		n->step.push_back(pos);
		pos[0]--;
		n->step.push_back(pos);

		n->color = (color == 1) ? 2 : 1;
		n->depth = depth + 1;

		child.push_back(n);
	}
	// move down
	if((r+1) <= 7 && board[r+1][c] == 0) {
		Node* n = new Node(board);
		n->board[r][c] = 0;
		n->board[r+1][c] = color;

		std::vector<int> pos = {r, c};
		n->step.push_back(pos);
		pos[0]++;
		n->step.push_back(pos);

		n->color = (color == 1) ? 2 : 1;
		n->depth = depth + 1;

		child.push_back(n);
	}
	// move left
	if((c-1) >= 0 && board[r][c-1] == 0) {
		Node* n = new Node(board);
		n->board[r][c] = 0;
		n->board[r][c-1] = color;

		std::vector<int> pos = {r, c};
		n->step.push_back(pos);
		pos[1]--;
		n->step.push_back(pos);

		n->color = (color == 1) ? 2 : 1;
		n->depth = depth + 1;

		child.push_back(n);
	}
	// move right
	if((c+1) <= 7 && board[r][c+1] == 0) {
		Node* n = new Node(board);
		n->board[r][c] = 0;
		n->board[r][c+1] = color;

		std::vector<int> pos = {r, c};
		n->step.push_back(pos);
		pos[1]++;
		n->step.push_back(pos);

		n->color = (color == 1) ? 2 : 1;
		n->depth = depth + 1;

		child.push_back(n);
	}
	/*// hop up
	if((r-2) >= 0 && board[r-1][c] != 0 && board[r-2][c] == 0) {
		Node* n = new Node(board);
		n->board[r][c] = 0;
		n->board[r-2][c] = color;
		n->board[r-1][c] = (n->board[r-1][c] == color) ? color : 0; // eat

		std::vector<int> pos = {r, c};
		n->step.push_back(pos);
		pos[0] -= 2;
		n->step.push_back(pos);
 
		n->color = (color == 1) ? 2 : 1;
		n->depth = depth + 1;

		child.push_back(n);

		hop(r-2, c);
	}
	// hop down
	if((r+2) <= 7 && board[r+1][c] != 0 && board[r+2][c] == 0) {
		Node* n = new Node(board);
		n->board[r][c] = 0;
		n->board[r+2][c] = color;
		n->board[r+1][c] = (n->board[r+1][c] == color) ? color : 0; // eat

		std::vector<int> pos = {r, c};
		n->step.push_back(pos);
		pos[0] += 2;
		n->step.push_back(pos);
 
		n->color = (color == 1) ? 2 : 1;
		n->depth = depth + 1;

		child.push_back(n);

		hop(r+2, c);
	}
	// hop left
	if((c-2) >= 0 && board[r][c-1] != 0 && board[r][c-2] == 0) {
		Node* n = new Node(board);
		n->board[r][c] = 0;
		n->board[r][c-2] = color;
		n->board[r][c-1] = (n->board[r][c-1] == color) ? color : 0; // eat

		std::vector<int> pos = {r, c};
		n->step.push_back(pos);
		pos[1] -= 2;
		n->step.push_back(pos);
 
		n->color = (color == 1) ? 2 : 1;
		n->depth = depth + 1;

		child.push_back(n);

		hop(r, c-2);
	}
	// hop right
	if((c+2) >= 0 && board[r][c+1] != 0 && board[r][c+2] == 0) {
		Node* n = new Node(board);
		n->board[r][c] = 0;
		n->board[r][c+2] = color;
		n->board[r][c+2] = (n->board[r][c+1] == color) ? color : 0; // eat

		std::vector<int> pos = {r, c};
		n->step.push_back(pos);
		pos[1] += 2;
		n->step.push_back(pos);
 
		n->color = (color == 1) ? 2 : 1;
		n->depth = depth + 1;

		child.push_back(n);

		hop(r, c+2, n);
	}*/
}

void Node::hop(int r, int c) {
	// hop up
	if((r-2) >= 0 && board[r-1][c] != 0 && board[r-2][c] == 0) {

	}
	// hop down
	if((r+2) <= 7 && board[r+1][c] != 0 && board[r+2][c] == 0) {
		
	}
	// hop left
	if((c-2) >= 0 && board[r][c-1] != 0 && board[r][c-2] == 0) {
		
	}
	// hop right
	if((c+2) >= 0 && board[r][c+1] != 0 && board[r][c+2] == 0) {
		
	}
}


bool Minimax::cutoff_test(Node *n) {
	if (n->depth > Depth) {
		return true;
	}
	else
		return false;
}

void Minimax::buildTree(std::vector<std::vector<int>> state) {
	root = Node(state);
	root.color = (is_black) ? 1 : 2;
	int max_val = maxVal(&root);
	std::vector<Node*>::iterator it;
	for(it=root.child.begin(); it!=root.child.end(); it++) {
		if((*it)->val == max_val) {
			step_list = (*it)->step;
		}
	}
	///
	std::cout << root.child.size() << std::endl;
	std::cout << max_val << std::endl;
	printBoard(&root);
}

int Minimax::maxVal(Node *n) {
	if (n->terminal()) { 
		return n->utilityFunction(is_black);;
	}
	if (cutoff_test(n)) {
		return n->evaluationFunction(is_black);
	}
	n->genChildren();
	int value = INT_MIN;
	for (int i = 0; i < n->child.size(); i++) {
		value = std::max(value, minVal(n->child[i]));
	}
	return value;
}
int Minimax::minVal(Node *n) {
	if (n->terminal()) {
		return n->utilityFunction(is_black);;
	}
	if (cutoff_test(n)) {
		return n->evaluationFunction(is_black);
	}
	n->genChildren();
	int value = INT_MAX;
	for (int i = 0; i < n->child.size(); i++) {
		value = std::min(value, maxVal(n->child[i]));
	}
	return value;
}

std::vector<std::vector<int>> Minimax::getSteplist() {
	return step_list;
}


// int main() {
// 	Minimax m(1); // black
// 	m.buildTree(testBoard());
// 	m.printStep();


// 	return 0;
// }

/****** for debugging ******/

std::vector<std::vector<int>> testBoard() {
	std::vector<std::vector<int>> ret;
	std::vector<int> tmp(8, 0);
	for(int i=0; i<8; i++) {
		ret.push_back(tmp);
	}
	ret[0][0] = 1;
	ret[7][7] = 2;
	return ret;
}
void printBoard(Node* n) {
	printf("- - - - - - - - -\n");
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			printf("%d ", n->board[i][j]);
		}
		printf("\n");
	}
	printf("- - - - - - - - -\n");
}
void Minimax::printStep() {
	std::vector<std::vector<int>>::iterator it;
	for(it=step_list.begin(); it!=step_list.end(); it++) {
		printf("(%d, %d) ", (*it)[0], (*it)[1]);
	}
	printf("\n");
}
