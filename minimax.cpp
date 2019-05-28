#include "minimax.h"

static Timer t;

int Node::utilityFunction(bool is_black) {
	int score = 0;
	int black_cnt = 0;
	int white_cnt = 0;

	std::vector<std::pair<int, int>>::iterator it;
	for (it = black.begin(); it != black.end(); it++) {
		if ((*it).second >= 6) black_cnt++;
	}
	for (it = white.begin(); it != white.end(); it++) {
		if ((*it).second <= 1) white_cnt++;
	}

	// compare number of pieces in the green area
	if (black_cnt > white_cnt) score = (is_black) ? INT_MAX : INT_MIN;
	else if (black_cnt < white_cnt) score = (is_black) ? INT_MIN : INT_MAX;
	else score = evaluationFunction(is_black);

	this->val = score; // store to node
	//printf("Uscore:%d\n", val);
	return score;
}
int Node::evaluationFunction(bool is_black){


	// (1) basic score(white zone): black(7, 0)->(0, 7), white(7, 7)->(0, 0)
	//     move front +2, move side +1
	// (2) in green zone, get 50
	// (3) final score = my score - enemy score

	int white_score = 0;
	int black_score = 0;
	const int slope = 5;
	for (int i = 0; i < black.size(); i++) {
		if (black[i].second >= 6) {
			black_score += 50;
		}
		else {
			black_score += (7 - black[i].first) + slope * black[i].second;
		}
	}
	for (int i = 0; i < white.size(); i++) {
		if (white[i].second <= 1) {
			white_score += 50;
		}
		else {
			white_score += white[i].first + slope * (7 - white[i].second);
		}
	}

	//black_score += black.size() * 10;
	//white_score += white.size() * 10;

	if (is_black) return (black_score - white_score);
	else return (white_score - black_score);

/*

	//////////////////////////////////////////////////////////////////////////////////////
	// How to get score                                                                 //
	//                                                                                  //
	// (1)Get in green zone, get  100								                    //
	// (2)moving forward but stil not get in green zone, get  10                        //
	// (3)eat enemy, get  10                                                            //
	// (4)get close to left side(for Black: row 0,1,2 ; for White row 5,6,7), get  5    //
	//////////////////////////////////////////////////////////////////////////////////////

	const int goal_score = 100;
	const int moving_forward_score = 10;
	const int eat_score = 10;
	const int left_score = 5;

	// playing as Black
	if (is_black) {
		for (int i = 0; i < black.size(); i++) {
			if (black[i].second <= 5) { score += black[i].second*moving_forward_score; }
			else { score += goal_score; }
			if (black[i].first <= 2) { score += left_score; }
		}
		for (int i = 0; i < white.size(); i++) {
			if (white[i].second >= 2) { score -= (7 - white[i].second)*moving_forward_score; }
			else { score -= goal_score; }
			if (white[i].first >= 5) { score -= left_score; }
		}
		score += (black.size() - white.size()) * eat_score;
	}
	// playing as White
	else {
		for (int i = 0; i < black.size(); i++) {
			if (black[i].second <= 5) { score -= black[i].second*moving_forward_score; }
			else { score -= goal_score; }
			if (black[i].first <= 2) { score -= left_score; }
		}
		for (int i = 0; i < white.size(); i++) {
			if (white[i].second >= 2) { score += (7 - white[i].second)*moving_forward_score; }
			else { score += goal_score; }
			if (white[i].first <= 2) { score -= left_score; }
		}
		score += (white.size() - black.size()) * eat_score;
	}
	this->val = score; // store evluation value to node
	return score;*/
}

// set leaf and return is terminal or not
bool Node::terminal() {
	//Case 1: black, white all has pawn(s) on the board
	if (this->white.size() > 0 && this->black.size() > 0) {
		bool white_win = true; // if all whites are in left green area
		bool black_win = true; // if all blacks are in right green area
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 6; j++) {
				if (board[i][j] == 1) black_win = false;
			}
		}
		for (int i = 0; i < 8; i++) {
			for (int j = 2; j < 8; j++) {
				if (board[i][j] == 2) white_win = false;
			}
		}
		this->leaf = (white_win || black_win);
	}
	//Case 2: white has pawn(s) on the board, black don't have any pawn
	else if (this->white.size() > 0 && this->black.size() == 0) {
		bool white_win = true;
		for (int i = 0; i < 8; i++) {
			for (int j = 2; j < 8; j++) {
				if (board[i][j] == 2) white_win = false;
			}
		}
		this->leaf = white_win;
	}
	//Case 3: black has pawn(s) on the board, white don't have any pawn
	else if (this->black.size() > 0 && this->white.size() == 0) {
		bool black_win = true;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 6; j++) {
				if (board[i][j] == 1) black_win = false;
			}
		}
		this->leaf = black_win;
	}
	//case 4: Either black or white don't have any pawn on the board.
	//This case will never happen.

	return this->leaf;
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
// generate hop node first, then move
void Node::genChildren() {
	if(color == 1) { // black
		for (int i = 0; i < black.size(); i++) {
			hop(black[i].first, black[i].second);
		}
		for(int i=0; i<black.size(); i++) {
			genSteps(black[i].first, black[i].second);
		}
	}
	else if (color == 2) { // white
		for (int i = 0; i < white.size(); i++) {
			hop(white[i].first, white[i].second);
		}
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
	//printf("******\n");
	//printBoard(this);
}

void Node::hop(int r, int c) {
	std::stack<HopNode> hop_node_stack;
	
	std::vector<std::vector<int>> temp_step;
	std::vector<int> temp_pos = { r, c }; // the 0th step (current position)
	temp_step.push_back(temp_pos);
	
	HopNode temp_hop_node(r, c, this->board, temp_step);
	hop_node_stack.push(temp_hop_node);

	// push all posible moves into stack
	// and nodes from stack to child list
	while (!hop_node_stack.empty()) {
		std::vector<std::vector<int>> curBoard;
		std::vector<std::vector<int>> curStep;
		std::vector<std::vector<int>> tempBoard;
		std::vector<std::vector<int>> tempStep;
		int cnt; // count the number of hops, to limit hops
		int curR, curC; // row & col. of the expanding node 
		int preR, preC; // row & col. of the previous step
		curBoard = hop_node_stack.top().board;
		curStep = hop_node_stack.top().step;
		cnt = curStep.size() - 1;
		curR = hop_node_stack.top().r;
		curC = hop_node_stack.top().c;
		preR = (cnt == 0) ? -1 : curStep[cnt - 1][0]; // if no prev step(root), set -1
		preC = (cnt == 0) ? -1 : curStep[cnt - 1][1]; // if no prev step(root), set -1

		// pop the current hop node and expand
		hop_node_stack.pop();

		// but check the hop count, don't expand if reached the max
		// also check the timer
		if (cnt >= Hop_max || t.timeUp()) break;

		// expand hop range
		// test if hop up is ok
		if (curR - 2 >= 0 && board[curR - 1][curC] != 0 && board[curR - 2][curC] == 0
			&& ((curR - 2) != preR && curC != preC) && !t.timeUp()) {
			//assigne value to temp from current
			tempBoard = curBoard;
			tempStep = curStep;
			//update tempBoard
			tempBoard[curR][curC] = 0;
			tempBoard[curR - 2][curC] = this->color;
			tempBoard[curR - 1][curC] = (tempBoard[curR - 1][curC] == this->color) ? this->color : 0;
			//update tempStep
			std::vector<int> pos = { curR - 2, curC };
			tempStep.push_back(pos);
			//create HopNode & put it into hop_node_stack
			HopNode temp(curR - 2, curC, tempBoard, tempStep);
			hop_node_stack.push(temp);

			// push new node to child list
			Node *n = new Node(tempBoard);
			n->step = tempStep;
			n->color = this->color;
			n->depth = this->depth+1;
			this->child.push_back(n);
		}

		// test if hop down is ok
		if ((curR + 2) <= 7 && board[curR + 1][curC] != 0 && board[curR + 2][curC] == 0
			&& ((curR + 2) != preR && curC != preC) && !t.timeUp()) {
			//assigne value to temp from current
			tempBoard = curBoard;
			tempStep = curStep;
			//update tempBoard
			tempBoard[curR][curC] = 0;
			tempBoard[curR + 2][curC] = this->color;
			tempBoard[curR + 1][curC] = (tempBoard[curR + 1][curC] == this->color) ? this->color : 0;
			//update tempStep
			std::vector<int> pos = { curR + 2, curC };
			tempStep.push_back(pos);
			//create HopNode & put it into hop_node_stack
			HopNode temp(curR + 2, curC, tempBoard, tempStep);
			hop_node_stack.push(temp);

			// push new node to child list
			Node *n = new Node(tempBoard);
			n->step = tempStep;
			n->color = this->color;
			n->depth = this->depth+1;
			this->child.push_back(n);
		}

		// test if hop left is ok
		if (curC - 2 >= 0 && board[curR][curC - 1] != 0 && board[curR][curC - 2] == 0
			&& (curR != preR && (curC - 2) != preC) && !t.timeUp()) {
			//assigne value to temp from current
			tempBoard = curBoard;
			tempStep = curStep;
			//update tempBoard
			tempBoard[curR][curC] = 0;
			tempBoard[curR][curC - 2] = this->color;
			tempBoard[curR][curC - 1] = (tempBoard[curR][curC - 1] != this->color) ? this->color : 0;
			//update tempStep
			std::vector<int> pos = { curR, curC - 2 };
			tempStep.push_back(pos);
			//create HopNode & put it into hop_node_stack
			HopNode temp(curR, curC - 2, tempBoard, tempStep);
			hop_node_stack.push(temp);

			// push new node to child list
			Node *n = new Node(tempBoard);
			n->step = tempStep;
			n->color = this->color;
			n->depth = this->depth+1;
			this->child.push_back(n);
		}

		// test if hop right is ok
		if (curC + 2 <= 7 && board[curR][curC + 1] != 0 && board[curR][curC + 2] == 0
			&& (curR != preR && (curC + 2) != preC) && !t.timeUp()) {
			//assigne value to temp from current
			tempBoard = curBoard;
			tempStep = curStep;
			//update tempBoard
			tempBoard[curR][curC] = 0;
			tempBoard[curR][curC + 2] = this->color;
			tempBoard[curR][curC + 1] = (tempBoard[curR][curC + 1] != this->color) ? this->color : 0;
			//update tempStep
			std::vector<int> pos = { curR, curC + 2 };
			tempStep.push_back(pos);
			//create HopNode & put it into hop_node_stack
			HopNode temp(curR, curC + 2, tempBoard, tempStep);
			hop_node_stack.push(temp);

			// push new node to child list
			Node *n = new Node(tempBoard);
			n->step = tempStep;
			n->color = this->color;
			n->depth = this->depth+1;
			this->child.push_back(n);
		}
	}
	//printf("hop_stack size:%d\n", hop_node_stack.size());
	//printf("child_list size:%d\n", child.size());
}

void Node::setVal(bool is_black) {
	getBlack();
	getWhite();
	if (terminal()) {
		val = utilityFunction(is_black);
	}
	else {
		val = evaluationFunction(is_black);
	}
}


void Node::calChildVal(bool is_black) {
	std::vector<Node*>::iterator itr;
	for (itr = this->child.begin(); itr != child.end(); itr++) {
		(*itr)->setVal(is_black);
	}
}

void Node::sortChildVal(bool is_max) {
	if (is_max) std::sort(this->child.begin(), this->child.end(), cmpMax);
	else std::sort(this->child.begin(), this->child.end(), cmpMin);
}

bool Node::isLeaf() {
	return this->leaf;
}

//////////////////////////////////////////////////////////////////////////////////////////
//                                class Minimax                                         //
//////////////////////////////////////////////////////////////////////////////////////////

// set root
void Minimax::buildTree(std::vector<std::vector<int>> state) {
	//printf("<---14--->\n");
	t.setTime(Time_lim);

	root = Node(state);
	root.color = (is_black) ? 1 : 2;

	root.setVal(is_black);
	//printf("root val:%d\n", root.val);

	int max_val = maxVal(&root, INT_MIN, INT_MAX);
	//printf("child #:%d\n", root.child.size());

	std::vector<Node*>::iterator it;
	for(it=root.child.begin(); it!=root.child.end(); it++) {
		//printf("%d ", (*it)->val);
		if((*it)->val == max_val) {
			step_list = (*it)->step;
		}
	}
	///
	//printf("\nmax_val:%d\n", max_val);
	//printf("Timer: %fs\n", t.getElapsed());
	//printBoard(&root);
}

int Minimax::maxVal(Node *n, int alpha, int beta) {
	if (n->isLeaf() || cutoff_test(n) || t.timeUp()) {
		return n->val;
	}

	n->genChildren();
	// ordering
	n->calChildVal(this->is_black);
	n->sortChildVal(true);

	int value = INT_MIN;
	for (int i = 0; i < n->child.size(); i++) {
		value = std::max(value, minVal(n->child[i], alpha, beta));
		if (value >= beta) {
			n->val = value;
			return value;
		}
		alpha = std::max(value, alpha);
	}
	n->val = value; // store(update) to node
	//printf("maxValue:%d\n", value);
	return value;
}
int Minimax::minVal(Node *n, int alpha, int beta) {
	if (n->isLeaf() || cutoff_test(n) || t.timeUp()) {
		return n->val;
	}

	n->genChildren();
	// ordering
	n->calChildVal(this->is_black);
	n->sortChildVal(false);

	int value = INT_MAX;
	for (int i = 0; i < n->child.size(); i++) {
		value = std::min(value, maxVal(n->child[i], alpha, beta));
		if (value <= alpha) {
			n->val = value;
			return value;
		}
		beta = std::min(value, beta);
	}
	n->val = value; // store(update) to node
	//printf("minValue:%d\n", value);
	return value;
}

bool Minimax::cutoff_test(Node *n) {
	return (n->depth >= Depth) ? true : false;
}

std::vector<std::vector<int>> Minimax::getSteplist() {
	return step_list;
}

// release memory
void Minimax::releaseTree() {
	std::vector<Node*>::iterator it;
	for (it = root.child.begin(); it != root.child.end(); it++) {
		delete (*it);
	}
}

void Minimax::releaseChild(Node* n) {
	if (n->child.size() == 0) delete n;
	else {
		std::vector<Node*>::iterator it;
		for (it = n->child.begin(); it != n->child.end(); it++) {
			releaseChild(*it);
		}
		delete (*it);
	}
}
	

// sort value from low to high
bool cmpMin(Node* n1, Node* n2) {
	return (n1->val < n2->val);
}

// sort value from high to low
bool cmpMax(Node* n1, Node *n2) {
	return (n1->val > n2->val);
}

/****** for debugging ******/

std::vector<std::vector<int>> testBoard() {
	std::vector<std::vector<int>> ret;
	std::vector<int> tmp(8, 0);
	for(int i=0; i<8; i++) {
		ret.push_back(tmp);
	}
	/*ret[0][0] = 1; ret[2][0] = 1; ret[4][0] = 1; ret[6][0] = 1;
	ret[1][1] = 1; ret[3][1] = 1; ret[5][1] = 1;
	ret[2][2] = 1; ret[4][2] = 1;
	ret[7][7] = 2; ret[5][7] = 2; ret[3][7] = 2; ret[1][7] = 2;
	ret[6][6] = 2; ret[4][6] = 2; ret[2][6] = 2;
	ret[5][5] = 2; ret[3][5] = 2;*/
	ret[0][0] = 1; ret[0][7] = 1;
	ret[1][1] = 1; ret[2][1] = 1; ret[3][2] = 1;
	ret[6][4] = 1;
	ret[4][2] = 2; ret[7][0] = 2;
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
	printf("steplist: ");
	std::vector<std::vector<int>>::iterator it;
	for(it=step_list.begin(); it!=step_list.end(); it++) {
		printf("(%d, %d) ", (*it)[0], (*it)[1]);
	}
	printf("\n");
}
