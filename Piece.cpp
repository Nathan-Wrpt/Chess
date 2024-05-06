#include "Piece.h"

Piece::Piece(string name, Colour colour, bool alive, bool firstmove) : name(name), colour(colour), alive(alive), firstmove(firstmove) {}

string Piece::getName() const {
    return name;
}

Colour Piece::getColour() const {
    return colour;
}

bool Piece::isAlive() const {
    return alive;
}

bool Piece::getFirstMove() const {
    return firstmove;
}

void Piece::setName(string name) {
    this->name = name;
}

void Piece::setColour(Colour colour) {
    this->colour = colour;
}

void Piece::setAlive(bool alive) {
    this->alive = alive;
}

void Piece::setFirstMove(bool firstmove) {
    this->firstmove = firstmove;
}

void Piece::display() {
    cout << name;
}

Pawn::Pawn(Colour colour, bool alive, string name) : Piece(name, colour, alive) {}

bool Pawn::possiblemove(Square origin, Square dest) {

    // Check if the destination square is valid
    if(dest.validsquare() == false){
        return false;
    }

    // White pawns
    if (this->getColour() == Colour::WHITE){
        // Move one square forward
        if (origin.getY() == dest.getY() && origin.getX() == dest.getX() - 1){
            return true;
        }

        // Move two squares forward if it's the first move
        if (this->getFirstMove() == true && origin.getY() == dest.getY() && origin.getX() == dest.getX() - 2){
            return true;
        }

        // Capture diagonally
        if (origin.getX() == dest.getX() - 1 && origin.getY() == dest.getY() - 1){
            return true;
        }
        if (origin.getX() == dest.getX() - 1 && origin.getY() == dest.getY() + 1){
            return true;
        }
    }

    // Same for the black pawns but in the opposite direction
    if (this->getColour() == Colour::BLACK){
        // Move one square forward
        if (origin.getY() == dest.getY() && origin.getX() == dest.getX() + 1){
            return true;
        }

        // Move two squares forward if it's the first move
        if (this->getFirstMove() == true && origin.getY() == dest.getY() && origin.getX() == dest.getX() + 2){
            return true;
        }

        // Capture diagonally
        if (origin.getX() == dest.getX() + 1 && origin.getY() == dest.getY() + 1){
            return true;
        }
        if (origin.getX() == dest.getX() + 1 && origin.getY() == dest.getY() - 1){
            return true;
        }
    }
    return false;
}

Rook::Rook(Colour colour, bool alive, string name) : Piece(name, colour, alive) {}

bool Rook::possiblemove(Square origin, Square dest){
    if(dest.validsquare() == false){
        return false;
    }
    //Vertical move
    if (origin.getX() != dest.getX() && origin.getY() == dest.getY()){
        return true;
    }
    //Horizontal move
    if (origin.getX() == dest.getX() && origin.getY() != dest.getY()){
        return true;
    }
    return false;
}

Knight::Knight(Colour colour, bool alive, string name) : Piece(name, colour, alive) {}

bool Knight::possiblemove(Square origin, Square dest){

    // Check if the destination square is valid
    if(dest.validsquare() == false){
        return false;
    }
    // L-shaped move up-right
    if (origin.getX() == dest.getX() - 1 && origin.getY() == dest.getY() - 2){
        return true;
    }
    // L-shaped move up-left
    if (origin.getX() == dest.getX() + 1 && origin.getY() == dest.getY() - 2){
        return true;
    }
    // L-shaped move down-right
    if (origin.getX() == dest.getX() - 1 && origin.getY() == dest.getY() + 2){
        return true;
    }
    // L-shaped move down-left
    if (origin.getX() == dest.getX() + 1 && origin.getY() == dest.getY() + 2){
        return true;
    }
    // L-shaped move right-up
    if (origin.getX() == dest.getX() - 2 && origin.getY() == dest.getY() - 1){
        return true;
    }
    // L-shaped move right-down
    if (origin.getX() == dest.getX() - 2 && origin.getY() == dest.getY() + 1){
        return true;
    }
    // L-shaped move left-up
    if (origin.getX() == dest.getX() + 2 && origin.getY() == dest.getY() - 1){
        return true;
    }
    // L-shaped move left-down
    if (origin.getX() == dest.getX() + 2 && origin.getY() == dest.getY() + 1){
        return true;
    }
    return false;
}

Bishop::Bishop(Colour colour, bool alive, string name) : Piece(name, colour, alive) {}

bool Bishop::possiblemove(Square origin, Square dest){
    if(dest.validsquare() == false){
        return false;
    }
    // Diagonal move
    if (abs(origin.getX() - dest.getX()) == abs(origin.getY() - dest.getY())){
        return true;
    }
    return false;
}

Queen::Queen(Colour colour, bool alive, string name) : Piece(name, colour, alive) {}

bool Queen::possiblemove(Square origin, Square dest){
    if(dest.validsquare() == false){
        return false;
    }
    // Vertical move
    if (origin.getX() != dest.getX() && origin.getY() == dest.getY()){
        return true;
    }
    // Horizontal move
    if (origin.getX() == dest.getX() && origin.getY() != dest.getY()){
        return true;
    }
    // Diagonal move
    if (abs(origin.getX() - dest.getX()) == abs(origin.getY() - dest.getY())){
        return true;
    }
    return false;
}

King::King(Colour colour, bool alive, string name) : Piece(name, colour, alive) {}

bool King::possiblemove(Square origin, Square dest){
    if(dest.validsquare() == false){
        return false;
    }
    // Move one square in any direction
    if (abs(origin.getX() - dest.getX()) <= 1 && abs(origin.getY() - dest.getY()) <= 1){
        return true;
    }
    return false;
}

