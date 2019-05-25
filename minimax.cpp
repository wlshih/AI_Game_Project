#include "minimax.h"

int Node::evaulationFunction(bool is_black){
	int score = 0;
	if(is_black){
		for(int i=0;i<black.size();i++){
			if(black[i].first <= 4){score+=black[i].first;}
			else{score+=10;}
		}
		for(int i=0;i<white.size();i++){
			if(white[i].first >= 3){score-=(7-white[i].first;)}
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
			if(white[i].first >= 3){score+=(7-white[i].first;)}
			else{score+=10;}
		}
		(white.size()-black.size())*5;
	}
	return score;
}

void Node::getBlack() {
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
	else perror("color not set");
}

// generate all posible steps of a piece and store to list
void Node::genSteps(int r, int c) {
	// move
	if((r-1) >= 0 && board[r-1][c] == 0) {

	}
	if((r+1) <= 7 && board[r+1][c] == 0) {

	}
	if((c-1) >= 0 && board[r][c-1] == 0) {

	}
	if((c+1) <= 7 && board[r][c+1] == 0) {

	}
	// hop
}


void Minimax::buildTree(std::vector<std::vector<int>> s) {
	root = Node(s);
}

int Minimax::maxVal(Node n) {
	// if()
}

int Minimax::minVal(Node n) {

}

bool Minimax::terminal(std::vector<std::vector<int>> s) {
	bool white = 0; // if all whites are in left green area
	bool black = 0; // if all blacks are in right green area
	for(int i=0; i<8; i++) {
		for(int j=0; j<6; j++) {
			if(s[i][j] == 1) black = 1;
		}
	}
	for(int i=0; i<8; i++) {
		for(int j=2; j<8; j++) {
			if(s[i][j] == 2) white = 1;
		}
	}

	return (white || black);
}

// int main() {
// 	return 0;
// }