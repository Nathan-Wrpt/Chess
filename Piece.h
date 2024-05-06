#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <string>
#include "Square.h"

using namespace std;

/**
 * @brief Enum representing the color of a chess piece.
 */
enum class Colour {WHITE, BLACK, BLANK};

/**
 * @brief Represents a chess piece.
 */
class Piece{
private:
    string name; /**< The name of the piece (represented by its emoji). */
    Colour colour; /**< The color of the piece. */
    bool alive; /**< Indicates whether the piece is alive or captured. */
    bool firstmove; /**< Indicates whether the piece has moved yet (only useful for the king, the rooks, and the pawns). */

public:
    /**
     * @brief Constructor for the Piece class.
     * @param name The name of the piece.
     * @param colour The color of the piece.
     * @param alive Indicates whether the piece is alive (default is true).
     * @param firstmove Indicates whether the piece has moved yet (default is true).
     */
    Piece(string name, Colour colour, bool alive = true, bool firstmove = true);
    

    /**
     * @brief Get the name of the piece.
     * @return The name of the piece.
     */
    string getName() const;

    /**
     * @brief Get the color of the piece.
     * @return The color of the piece.
     */
    Colour getColour() const;

    /**
     * @brief Check if the piece is alive.
     * @return True if the piece is alive, false otherwise.
     */
    bool isAlive() const;

    /**
     * @brief Get whether it's the piece's first move.
     * @return True if it's the piece's first move, false otherwise.
     */
    bool getFirstMove() const;

    /**
     * @brief Set the name of the piece.
     * @param name The new name of the piece.
     */
    void setName(string name);

    /**
     * @brief Set the color of the piece.
     * @param colour The new color of the piece.
     */
    void setColour(Colour colour);

    /**
     * @brief Set whether the piece is alive or not.
     * @param alive True if you want the piece alive, false otherwise.
     */
    void setAlive(bool alive);

    /**
     * @brief Set whether it's the piece's first move.
     * @param firstmove True if piece's first move, false otherwise.
     */
    void setFirstMove(bool firstmove);

    /**
     * @brief Check if a move from one square to another is possible for this piece.
     * @param origin The square where the piece currently is.
     * @param dest The square where the piece is attempting to move.
     * @return True if the move is possible (not taking into account other pieces), only based on the piece's movement rules on the board if it was empty.
     */
    virtual bool possiblemove(Square origin, Square dest) = 0;

    /**
     * @brief Display the piece
     */
    void display();
};

/**
 * @brief Represents a pawn chess piece.
 */
class Pawn : public Piece{
public:
    /**
     * @brief Constructor for the Pawn class.
     * @param colour The color of the pawn.
     * @param alive Indicates whether the pawn is alive.
     * @param name The name of the pawn (default is the Unicode character for a pawn).
     */
    Pawn(Colour colour, bool alive, string name = "\u2659");

    /**
     * @brief Check if a move from one square to another is possible for this pawn.
     * @param origin The square where the pawn currently is.
     * @param dest The square where the pawn is attempting to move.
     * @return True if the move is possible, false otherwise.
     */
    bool possiblemove(Square origin, Square dest) override;
};

/**
 * @brief Represents a rook chess piece.
 */
class Rook : public Piece{
public:
    /**
     * @brief Constructor for the Rook class.
     * @param colour The color of the rook.
     * @param alive Indicates whether the rook is alive.
     * @param name The name of the rook (default is the Unicode character for a rook).
     */
    Rook(Colour colour, bool alive, string name = "\u2656");

    /**
     * @brief Check if a move from one square to another is possible for this rook.
     * @param origin The square where the rook currently is.
     * @param dest The square where the rook is attempting to move.
     * @return True if the move is possible, false otherwise.
     */
    bool possiblemove(Square origin, Square dest) override;
};

/**
 * @brief Represents a knight chess piece.
 */
class Knight : public Piece{
public:
    /**
     * @brief Constructor for the Knight class.
     * @param colour The color of the knight.
     * @param alive Indicates whether the knight is alive.
     * @param name The name of the knight (default is the Unicode character for a knight).
     */
    Knight(Colour colour, bool alive, string name = "\u2658");

    /**
     * @brief Check if a move from one square to another is possible for this knight.
     * @param origin The square where the knight currently is.
     * @param dest The square where the knight is attempting to move.
     * @return True if the move is possible, false otherwise.
     */
    bool possiblemove(Square origin, Square dest) override;
};

/**
 * @brief Represents a bishop chess piece.
 */
class Bishop : public Piece{
public:
    /**
     * @brief Constructor for the Bishop class.
     * @param colour The color of the bishop.
     * @param alive Indicates whether the bishop is alive.
     * @param name The name of the bishop (default is the Unicode character for a bishop).
     */
    Bishop(Colour colour, bool alive, string name = "\u2657");

    /**
     * @brief Check if a move from one square to another is possible for this bishop.
     * @param origin The square where the bishop currently is.
     * @param dest The square where the bishop is attempting to move.
     * @return True if the move is possible, false otherwise.
     */
    bool possiblemove(Square origin, Square dest) override;
};

/**
 * @brief Represents a queen chess piece.
 */
class Queen : public Piece{
public:
    /**
     * @brief Constructor for the Queen class.
     * @param colour The color of the queen.
     * @param alive Indicates whether the queen is alive.
     * @param name The name of the queen (default is the Unicode character for a queen).
     */
    Queen(Colour colour, bool alive, string name = "\u2655");

    /**
     * @brief Check if a move from one square to another is possible for this queen.
     * @param origin The square where the queen currently is.
     * @param dest The square where the queen is attempting to move.
     * @return True if the move is possible, false otherwise.
     */
    bool possiblemove(Square origin, Square dest) override;
};

/**
 * @brief Represents a king chess piece.
 */
class King : public Piece{
public:
    /**
     * @brief Constructor for the King class.
     * @param colour The color of the king.
     * @param alive Indicates whether the king is alive.
     * @param name The name of the king (default is the Unicode character for a king).
     */
    King(Colour colour, bool alive, string name = "\u2654");

    /**
     * @brief Check if a move from one square to another is possible for this king.
     * @param origin The square where the king currently is.
     * @param dest The square where the king is attempting to move.
     * @return True if the move is possible, false otherwise.
     */
    bool possiblemove(Square origin, Square dest) override;
};

#endif // PIECE_H