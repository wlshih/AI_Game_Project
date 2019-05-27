#include "minimax.h"

int Node::utilityFunction(bool is_black) {
	int score = 0;
	if (is_black) {
		if (black[0].first >= 6) score = INT_MAX;
		else score = INT_MIN;	
	}
	else {
		if (white[0].first <= 1) score = INT_MAX;
		else score = INT_MIN;
	}
	val = score; // store to node
	//printf("Uscore:%d\n", val);
	return score;
}
int Node::evaluationFunction(bool is_black){
	int score = 0;
	if(is_black){
		for(int i=0;i<black.size();i++){
			if(black[i].second <= 4){score+=black[i].second;}
			else{score+=10;}
		}
		for(int i=0;i<white.size();i++){
			if(white[i].second >= 3){score-=(7-white[i].second);}
			else{score-=10;}
		}
		(black.size()-white.size())*5;
	}
	else{
		for(int i=0;i<black.size();i++){
			if(black[i].second <= 4){score-=black[i].second;}
			else{score-=10;}
		}
		for(int i=0;i<white.size();i++){
			if(white[i].second >= 3){score+=(7-white[i].second);}
			else{score+=10;}
		}
		(white.size()-black.size())*5;
	}
	val = score; // store to node
	//printf("Escore:%d\n", val);
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
	/*for (int i = 0; i < black.size(); i++) {
		printf("(%d, %d) ", black[i].first, black[i].second);
	}
	printf(" -black\n");*/
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
	/*for (int i = 0; i < white.size(); i++) {
		printf("(%d, %d) ", white[i].first, white[i].second);
	}
	printf(" -white\n");*/
}

// generate all children of next step
void Node::genChildren() {
	//printf("genChildren%d,%d\n", black.size(), white.size());
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
	//printBoard(this);
	//printf("color:%d, child:%d, depth:%d\n", color, child.size(), depth);
	// for(std::vector<Node*>::iterator it=child.begin(); it!=child.end(); it++) {
	// 	printBoard(*it);
	// }
}

// generate all posible steps of a piece and store to list
// move/hop up + down + left + right
void Node::genSteps(int r, int c) {
	// move up
	//printf("genSteps\n");
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

	// hop(r, c);
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
	std::stack<hop_node> hop_node_stack;
	hop_node temp_hop_node(r, c, this->board, this->step);
	hop_node_stack.push(temp_hop_node);

	while (!hop_node_stack.empty()) {
		std::vector<std::vector<int>> curBoard;
		std::vector<std::vector<int>> curStep;
		std::vector<std::vector<int>> tempBoard;
		std::vector<std::vector<int>> tempStep;
		int curR, curC;
		curR = hop_node_stack.top().r; // row of the expanding node 
		curC = hop_node_stack.top().c; // col of the expanding node
		curBoard = hop_node_stack.top().board;
		curStep = hop_node_stack.top().step;

		//test if hop up is ok
		if (curR - 2 >= 0 && board[curR - 1][curC] != 0 && board[curR - 2][curC] == 0) {
			//assigne value to temp from current
			tempBoard = curBoard;
			tempStep = curStep;
			//update tempBoard
			tempBoard[curR - 2][curC] = this->color;
			if (tempBoard[curR - 1][curC] != this->color) { tempBoard[curR - 1][curC] = 0; }
			//update tempStep
			std::vector<int> pos = { curR - 2, curC };
			tempStep.push_back(pos);
			//create hop_node & put it into hop_node_stack
			hop_node temp(curR - 2, curC, tempBoard, tempStep);
			hop_node_stack.push(temp);
		}

		//test if hop down is ok
		if ((curR + 2) <= 7 && board[curR + 1][curC] != 0 && board[curR + 2][curC] == 0) {
			//assigne value to temp from current
			tempBoard = curBoard;
			tempStep = curStep;
			//update tempBoard
			tempBoard[curR + 2][curC] = this->color;
			if (tempBoard[curR + 1][curC] != this->color) { tempBoard[curR + 1][curC] = 0; }
			//update tempStep
			std::vector<int> pos = { curR + 2, curC };
			tempStep.push_back(pos);
			//create hop_node & put it into hop_node_stack
			hop_node temp(curR + 2, curC, tempBoard, tempStep);
			hop_node_stack.push(temp);
		}

		//test if hop left is ok
		if (curC - 2 >= 0 && board[curR][curC - 1] != 0 && board[curR][curC - 2] == 0) {
			//assigne value to temp from current
			tempBoard = curBoard;
			tempStep = curStep;
			//update tempBoard
			tempBoard[curR][curC - 2] = this->color;
			if (tempBoard[curR][curC - 1] != this->color) { tempBoard[curR][curC - 1] = 0; }
			//update tempStep
			std::vector<int> pos = { curR, curC - 2 };
			tempStep.push_back(pos);
			//create hop_node & put it into hop_node_stack
			hop_node temp(curR, curC - 2, tempBoard, tempStep);
			hop_node_stack.push(temp);
		}

		//test if hop right is ok
		if (curC + 2 <= 7 && board[curR][curC + 1] != 0 && board[curR][curC + 2] == 0) {
			//assigne value to temp from current
			tempBoard = curBoard;
			tempStep = curStep;
			//update tempBoard
			tempBoard[curR][curC + 2] = this->color;
			if (tempBoard[curR][curC + 1] != this->color) { tempBoard[curR][curC + 1] = 0; }
			//update tempStep
			std::vector<int> pos = { curR, curC + 2 };
			tempStep.push_back(pos);
			//create hop_node & put it into hop_node_stack
			hop_node temp(curR, curC + 2, tempBoard, tempStep);
			hop_node_stack.push(temp);
		}
		
		//create child node by hop_node_stack's top;
		Node *n = new Node(curBoard);
		n->step = curStep;
		n->color = (color == 1) ? 2 : 1;
		n->depth = depth + 1;
		this->child.push_back(n);
		//pop off stack top
		hop_node_stack.pop();
	}
}



void Minimax::buildTree(std::vector<std::vector<int>> state) {
	root = Node(state);
	root.color = (is_black) ? 1 : 2;
	int max_val = maxVal(&root, INT_MIN, INT_MAX);
	std::vector<Node*>::iterator it;
	for(it=root.child.begin(); it!=root.child.end(); it++) {
		//printf("%d ", (*it)->val);
		if((*it)->val == max_val) {
			step_list = (*it)->step;
		}
	}
	///
	printf("\nchild #:%d\n", root.child.size());
	printf("max_val:%d\n", max_val);
	//printBoard(&root);
}

int Minimax::maxVal(Node *n, int alpha, int beta) {
	n->getBlack();
	n->getWhite();
	if (n->terminal()) { 
		return n->utilityFunction(is_black);;
	}
	if (cutoff_test(n)) {
		return n->evaluationFunction(is_black);
	}
	n->genChildren();
	int value = INT_MIN;
	for (int i = 0; i < n->child.size(); i++) {
		value = std::max(value, minVal(n->child[i], alpha, beta));
		if (value >= beta) {
			n->val = value;
			return value;
		}
		alpha = std::max(value, alpha);
	}
	n->val = value; // store to node
	//printf("maxValue:%d\n", value);
	return value;
}
int Minimax::minVal(Node *n, int alpha, int beta) {
	n->getBlack();
	n->getWhite();
	if (n->terminal()) {
		return n->utilityFunction(is_black);;
	}
	if (cutoff_test(n)) {
		return n->evaluationFunction(is_black);
	}
	n->genChildren();
	int value = INT_MAX;
	for (int i = 0; i < n->child.size(); i++) {
		value = std::min(value, maxVal(n->child[i], alpha, beta));
		if (value <= alpha) {
			n->val = value;
			return value;
		}
		beta = std::min(value, beta);
	}
	n->val = value; // store to node
	//printf("minValue:%d\n", value);
	return value;
}

bool Minimax::cutoff_test(Node *n) {
	return (n->depth >= Depth) ? true : false;
}

std::vector<std::vector<int>> Minimax::getSteplist() {
	return step_list;
}


/****** for debugging ******/

std::vector<std::vector<int>> testBoard() {
	std::vector<std::vector<int>> ret;
	std::vector<int> tmp(8, 0);
	for(int i=0; i<8; i++) {
		ret.push_back(tmp);
	}
	ret[0][0] = 1; ret[2][0] = 1; ret[4][0] = 1; ret[6][0] = 1;
	ret[1][1] = 1; ret[3][1] = 1; ret[5][1] = 1;
	ret[2][2] = 1; ret[4][2] = 1;
	ret[7][7] = 2; ret[5][7] = 2; ret[3][7] = 2; ret[1][7] = 2;
	ret[6][6] = 2; ret[4][6] = 2; ret[2][6] = 2;
	ret[5][5] = 2; ret[3][5] = 2;
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
	printf("steplist#:%d\n", step_list.size());
	std::vector<std::vector<int>>::iterator it;
	for(it=step_list.begin(); it!=step_list.end(); it++) {
		printf("(%d, %d) ", (*it)[0], (*it)[1]);
	}
	printf("\n");
}
