# Chess Game

<img src="https://i.pinimg.com/736x/3c/4f/18/3c4f1886e5b1d47f3126703fd20f56b7.jpg" class="mx-auto text-center" alt="chess board" width="200" height="200">

## Description
 This is a simple console-based chess game written in C++. The game board is displayed on the console and the player is prompted to enter a source square and a destination square using a letter and a number. The pieces are represented by letters: R (rook), B (bishop), K (king), Q (queen), P (pawn), with uppercase letters representing white pieces and lowercase letters representing black pieces. The game verifies that the move is legal and possible, and returns a response code based on the move.


## Usage
To start the game, run the main.py file and follow the on-screen instructions. Enter the source and destination squares using the format "letter number", e.g. "f3f6" to move the pawn from f3 to f6. The game will verify that the move is legal and display the updated board.

## Response Codes
The game returns the following response codes based on the move:

- 11: No piece in source square
- 12: Piece in source square belongs to opposing player
- 13: Destination square already occupied by current player's piece
- 12: Illegal move for the piece
- 31: Move puts current player in check (illegal move)
- 42: Normal move (no check)
- 41: Move puts opposing player in check (legal move)
