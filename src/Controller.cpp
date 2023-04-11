#include "Controller.h"
const auto EXIT = "exit";


Controller::Controller() : m_board() ,m_chess(START_BOARD)
{}

// =================================================================
void Controller::run()
{
	auto playerTurn = PlayerColor::White;
	//string board = "##########K###############################R#############r#r#####";
	int codeResponse = 0;
	string res = m_chess.getInput();
	while (res != "exit")
	{
		/*
		codeResponse value :
		Illegal movements :
		11 - there is not piece at the source
		12 - the piece in the source is piece of your opponent
		13 - there one of your pieces at the destination
		21 - illegal movement of that piece
		31 - this movement will cause you checkmate

		legal movements :
		41 - the last movement was legal and cause check
		42 - the last movement was legal, next turn
		*/
		{
			codeResponse = m_board.getCodeResponse(res, playerTurn);
			if (codeResponse == CodeRes::LegalMove || codeResponse == CodeRes::CheckMateOnMOpponent)
				playerTurn = playerTurn == PlayerColor::White? PlayerColor::Black : PlayerColor::White;

		}

		m_chess.setCodeResponse(codeResponse);
		res = m_chess.getInput();
	}
	cout << endl << "Exiting " << endl;
}
