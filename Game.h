#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <regex>
#include "Board.h"

using namespace std;

/**
 * @brief The Game class represents a chess game.
 * 
 * This class manages the chess game, including the board and player moves.
 */
class Game {
private:
    Board board; /**< The chess board for the game. */

public:
    /**
     * @brief Constructs a new Game object.
     * 
     * Initializes the game with an empty board.
     */
    Game();

    /**
     * @brief Starts the chess game.
     * 
     * This method is responsible for controlling the flow of the game,
     * including handling player moves and determining game outcomes.
     * It is kinda simple, go check the code if more details are needed.
     */
    void play();

    /**
     * @brief Checks if the input command is valid.
     * 
     * @param cmd The input command to check.
     * @return True if the command is valid, false otherwise.
     */
    bool is_valid_input(string const &cmd);

    /**
     * @brief Checks if the input command represents a valid short castling move.
     * 
     * @param cmd The input command to check.
     * @return True if the command represents a valid short castling move, false otherwise.
     */
    bool is_valid_input_short_castling(string const &cmd);

    /**
     * @brief Checks if the input command represents a valid long castling move.
     * 
     * @param cmd The input command to check.
     * @return True if the command represents a valid long castling move, false otherwise.
     */
    bool is_valid_input_long_castling(string const &cmd);
};

#endif // GAME_H
