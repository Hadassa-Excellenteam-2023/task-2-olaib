#include "Controller.h"
const auto EXIT = "exit";

// m_chess(m_board.getStringBoard not working ): - "string too long" exception so you should add the 
//																	board in 2 c-tors as param
Controller::Controller() :m_board(START_BOARD),
	//m_chess(m_board.getStringBoard())
	m_chess(START_BOARD)
{}

// =================================================================
void Controller::run()
{
	auto playerTurn = PlayerColor::White;
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
		try {
			codeResponse = m_board.getCodeResponse(res, playerTurn);
			if (codeResponse == CodeRes::LegalMove || codeResponse == CodeRes::CheckMateOnMOpponent)
				playerTurn = playerTurn == PlayerColor::White ? PlayerColor::Black : PlayerColor::White;


			m_chess.setCodeResponse(codeResponse);
		}
		catch (std::invalid_argument e) {
		}
		res = m_chess.getInput();
	}
	cout << endl << "Exiting " << endl;
}
