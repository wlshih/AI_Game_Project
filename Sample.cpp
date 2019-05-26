
#include "STcpClient.h"
#include "minimax.h"

std::vector<std::vector<int>> GetStep(std::vector<std::vector<int>>& board, bool is_black) {
	std::vector<std::vector<int>> step;

	Minimax m(is_black);
	m.buildTree(board);
	m.printStep();
	step = m.getSteplist();

	return step;
}

int main() {
	int id_package;
	std::vector<std::vector<int>> board, step;
	bool is_black;
	while (true) {
		if (GetBoard(id_package, board, is_black))
			break;

		step = GetStep(board, is_black);
		SendStep(id_package, step);
	}
}
