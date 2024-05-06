#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>
#include "Square.h"
#include "Piece.h"

#define NBCOL 8
#define NBJOUEUR 2

using namespace std;

/**
 * @brief Represents a player in the chess game.
 */
class Player {
private:
    Colour name; /**< The color of the player. */
public:
    /**
     * @brief Constructor for the Player class.
     * @param name The color of the player.
     */
    Player(Colour name) : name(name) {}

    /**
     * @brief Get the color of the player.
     * @return The color of the player.
     */
    Colour getName() const { return name; }

    /**
     * @brief Set the color of the player.
     * @param name The new color of the player.
     */
    void setName(Colour name) { this->name = name; }
};

/**
 * @brief Represents a chess board.
 */
class Board {
private:
    vector<Piece *> pieces[NBJOUEUR]; /**< Array of vectors to store the pieces for each player. */
    Piece * board[NBCOL][NBCOL]; /**< 2D array representing the board. */
    Player Player1; /**< Player 1. */
    Player Player2; /**< Player 2. */
    int enpassantw[NBCOL]; /**< Array to track en passant moves for white pieces. */
    int enpassantb[NBCOL]; /**< Array to track en passant moves for black pieces. */
    int nocapture; /**< Number of moves since the last capture. */
public:
    /**
     * @brief Constructor for the Board class.
     * @param player1 The color of player 1 (default is white).
     * @param player2 The color of player 2 (default is black).
     */
    Board(Colour player1 = Colour::WHITE, Colour player2 = Colour::BLACK);

    /**
     * @brief getter for the nocapture attribute
     */
    int getnocapture() const;

    /**
     * @brief setter for the nocapture attribute
     * @param nocapture The new value for the nocapture attribute
     */
    void setnocapture(int nocapture);

    /**
     * @brief Get the piece at the specified position on the board.
     * @param x The x-coordinate of the position.
     * @param y The y-coordinate of the position.
     * @return A pointer to the piece at the specified position, or nullptr if no piece is present.
     */
    Piece * getPiece(int x, int y) const;

    /**
     * @brief Set the piece at the specified position on the board.
     * @param x The x-coordinate of the position.
     * @param y The y-coordinate of the position.
     * @param piece A pointer to the piece to be placed at the specified position.
     */
    void setPiece(int x, int y, Piece * piece);

    /**
     * @brief Display the current state of the board.
     */
    void display() const;

    /**
     * @brief Checks if the specified player is in check. Implementation : determines the king's position and iterates over all the pieces of the opponent to check if they can attack the king.
     * 
     * @param turn The color of the player to check.
     * @return True if the player is in check, false otherwise.
     */
    bool incheck(Colour turn);

    /**
     * @brief Checks if making a move from the origin square to the destination square puts the player in check. (based on incheck method)
     * 
     * @param origin The origin square of the move.
     * @param dest The destination square of the move.
     * @param turn The color of the player making the move.
     * @return True if the move puts the player in check, false otherwise.
     */
    bool willputincheck(Square origin, Square dest, Colour turn);

    /**
     * @brief Asks which piece the player wants to promote a pawn to.
     * 
     * @return The character representing the chosen piece.
     */
    char askwhichpiecewanted();

    /**
     * @brief Transforms a pawn to another piece if it reached the other side of the board. Implementation : Checks on the last rows of the board if there is a pawn.
     * 
     * @return True if the transformation is successful, false otherwise.
     */
    bool transformpieceifothersidereached();
    
    /**
     * @brief Performs a little castle move for the specified player if it can be done.
     * 
     * @param turn The color of the player performing the move.
     * @return True if the little castle move is successful, false otherwise.
     */
    bool littlecastle(Colour turn);

    /**
     * @brief Performs a big castle move for the specified player.
     * 
     * @param turn The color of the player performing the move.
     * @return True if the big castle move is successful, false otherwise.
     */
    bool bigcastle(Colour turn);

    /**
     * @brief Checks if the specified player is in checkmate. Implementation : iterates over all the pieces of the player and checks if there is a move that can be made.
     * (That could result in a situation where the player isn't in check but the function returns true, but that case will be handled by the pat function before.)
     * 
     * @param turn The color of the player to check for checkmate.
     * @return True if the player is in checkmate, false otherwise.
     */
    bool checkmate(Colour turn);

    /**
     * @brief Checks if the specified player is in a stalemate position (draw), using checkmate function
     * 
     * @param turn The color of the player to check for stalemate.
     * @return True if the game is in a stalemate position, false otherwise.
     */
    bool pat(Colour turn);

    /**
     * @brief Moves a piece from the origin square to the destination square if the move is valid. Check the code for more details.
     * 
     * @param origin The origin square of the piece.
     * @param dest The destination square to move the piece to.
     * @param turn The color of the player making the move.
     * @param actualmove Whether this move is actual or just for testing, so that the board is not modified.
     * @param checktest Whether this move is for checking if the player is in check (to avoid recursion with willputincheck).
     * @return True if the move is successful, false otherwise.
     */
    bool movepiece(Square origin, Square dest, Colour turn, bool actualmove, bool checktest = false);

    /**
     * @brief Prints the board canonically followed by the match score.
     * 
     * @param score The score to display along with the board.
     */
    void canonicallyprintboard(string score);

};

#endif
