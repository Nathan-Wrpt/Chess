#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Represents a square on a chessboard.
 */
class Square {
private:
    int x; /**< The x-coordinate of the square. */
    int y; /**< The y-coordinate of the square. */

public:
    /**
     * @brief Constructor for the Square class.
     * @param x The x-coordinate of the square.
     * @param y The y-coordinate of the square.
     */
    Square(int x, int y);

    /**
     * @brief Get the y-coordinate of the square, for implementation reasons.
     * @return The y-coordinate of the square.
     */
    int getX() const;

    /**
     * @brief Get the x-coordinate of the square.
     * @return The x-coordinate of the square.
     */
    int getY() const;

    /**
     * @brief Set the x-coordinate of the square.
     * @param x The new x-coordinate of the square.
     */
    void setX(int x);

    /**
     * @brief Set the y-coordinate of the square.
     * @param y The new y-coordinate of the square.
     */
    void setY(int y);

    /**
     * @brief Convert the square coordinates to a string representation.
     * @return A string representation of the square coordinates.
     */
    string tostring() const;

    /**
     * @brief Check if the square is a valid square on the chessboard.
     * @return True if the square is valid, false otherwise.
     */
    bool validsquare() const;
};

#endif // SQUARE_H
