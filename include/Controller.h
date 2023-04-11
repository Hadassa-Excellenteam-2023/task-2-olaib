#pragma once
#include "Board.h"
#include "Chess.h"

class Controller {
public:
	Controller();
	void run();
private:
	Chess m_chess;
	Board m_board;
};