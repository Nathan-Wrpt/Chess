#include "Board.h"

Board::Board(Colour player1, Colour player2) : Player1(player1), Player2(player2) {

    // Initialize the board
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i][j] = nullptr;
        }
    }

    // Initialize the pieces vector for each player
    pieces[0] = {
        new Rook(Colour::WHITE, 1),
        new Knight(Colour::WHITE, 1),
        new Bishop(Colour::WHITE, 1),
        new Queen(Colour::WHITE, 1),
        new King(Colour::WHITE, 1),
        new Bishop(Colour::WHITE, 1),
        new Knight(Colour::WHITE, 1),
        new Rook(Colour::WHITE, 1),
    };
    for (int i = 0; i < NBCOL; i++){
        pieces[0].push_back(new Pawn(Colour::WHITE, 1, "\u2659"));
    }

    pieces[1] = {
        new Rook(Colour::BLACK, 1, "\u265C"),
        new Knight(Colour::BLACK, 1, "\u265E"),
        new Bishop(Colour::BLACK, 1, "\u265D"),
        new Queen(Colour::BLACK, 1, "\u265B"),
        new King(Colour::BLACK, 1, "\u265A"),
        new Bishop(Colour::BLACK, 1, "\u265D"),
        new Knight(Colour::BLACK, 1, "\u265E"),
        new Rook(Colour::BLACK, 1, "\u265C"),
    };
    for (int i = 0; i < NBCOL; i++){
        pieces[1].push_back(new Pawn(Colour::BLACK, 1, "\u265F"));
    }

    // Place the pieces on the board
    for(int i = 0; i < 8; i++){
        board[0][i] = pieces[0][i];
        board[1][i] = pieces[0][i + NBCOL];
        board[6][i] = pieces[1][i + NBCOL];
        board[7][i] = pieces[1][i];
    }

    for (int i = 0; i < NBCOL; i++){
        enpassantw[i] = 0;
    }
    for (int i = 0; i < NBCOL; i++){
        enpassantb[i] = 0;
    }
    // Those arrays will track the en passant possibilities for each pawn (enpassantw[0] will be set to 1 for one if the a1 pawn moved 2 squares forward, etc.)
}

int Board::getnocapture() const {
    return nocapture;
}

void Board::setnocapture(int nocapture) {
    this->nocapture = nocapture;
}

Piece * Board::getPiece(int x, int y) const {
    return board[x][y];
}

void Board::setPiece(int x, int y, Piece * piece) {
    board[x][y] = piece;
}

void Board::display() const {
    string space5 = string(5,' ');
    cout << endl;
    cout << "     a     b     c     d     e     f     g     h    "<< endl;
    cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    for (int i(NBCOL-1);i>=0;i--) {
            cout << i+1 << " "; // numérotation ligne dans affichage
            for (int j(0);j<NBCOL;j++) {
                    cout << "|" ;
                    if (board[i][j]) { 
                    cout << "  ";
                    board[i][j]-> display();
                    cout << "  ";
                    }
                    else 
                            cout << space5;  // 2 ascii spaces
            }
            cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+";
            cout << endl;
    }
}

bool Board::incheck(Colour turn) {
    Square kingpos(0, 0);
    bool kingposfound = false;
    // Iterate over the board to find the king's position
    for (int i = 0; i < NBCOL; i++){
        for (int j = 0; j < NBCOL; j++){
            if (board[i][j] != nullptr && board[i][j]->getName() == (turn == Colour::WHITE ? "\u2654" : "\u265A")){
                kingpos.setX(j);
                kingpos.setY(i);
                kingposfound = true;
            }
        }
    }
    if(kingposfound == false) return false;
    // Iterate over the board to find the opponent's pieces and check if they can attack the king
    for (int i = 0; i < NBCOL; i++){
        for (int j = 0; j < NBCOL; j++){
            if (board[i][j] != nullptr && board[i][j]->getColour() != turn){
                Square origin(j, i);
                //check if the move is possible
                if(movepiece(origin, kingpos, board[i][j]->getColour(), false, true)){
                    cout << "Piece " << board[i][j]->getName() << " at " << origin.tostring() << " can capture the king at " << kingpos.tostring() << endl;
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::willputincheck(Square origin, Square dest, Colour turn) {

    Piece * piece = board[origin.getX()][origin.getY()];
    Piece * piece2 = board[dest.getX()][dest.getY()];
    board[dest.getX()][dest.getY()] = piece;
    board[origin.getX()][origin.getY()] = nullptr;

    // Call incheck on the fictive board
    bool check = incheck(turn);

    // Undo the move
    board[origin.getX()][origin.getY()] = piece;
    board[dest.getX()][dest.getY()] = piece2;
    
    return check;
}

char Board::askwhichpiecewanted() {
    char piecewanted;
    cout << "Other side reached ! Which piece do you want ?" << endl;
    cout << "Q. Queen" << endl;
    cout << "R. Rook" << endl;
    cout << "B. Bishop" << endl;
    cout << "N. Knight" << endl;
    cin >> piecewanted;
    while(piecewanted != 'Q' && piecewanted != 'R' && piecewanted != 'B' && piecewanted != 'N') {
        cout << "Invalid input, please enter a valid input" << endl;
        cin >> piecewanted;
    }
    return piecewanted;
}

bool Board::transformpieceifothersidereached() {
    for (int i = 0; i < NBCOL; i++){
        if (board[0][i] != nullptr && board[0][i]->getColour() == Colour::BLACK){
            if (board[0][i]->getName() == "\u265F"){
                int piecewanted = askwhichpiecewanted();
                switch (piecewanted){
                    case 'Q':
                        board[0][i] = new Queen(Colour::BLACK, 1, "\u265B");
                        break;
                    case 'R':
                        board[0][i] = new Rook(Colour::BLACK, 1, "\u265C");
                        break;
                    case 'B':
                        board[0][i] = new Bishop(Colour::BLACK, 1, "\u265D");
                        break;
                    case 'N':
                        board[0][i] = new Knight(Colour::BLACK, 1, "\u265E");
                        break;
                }
                return true;
            }
        }
        if (board[7][i] != nullptr && board[7][i]->getColour() == Colour::WHITE){
            if (board[7][i]->getName() == "\u2659"){
                int piecewanted = askwhichpiecewanted();
                switch (piecewanted){
                    case 'Q':
                        board[7][i] = new Queen(Colour::WHITE, 1);
                        break;
                    case 'R':
                        board[7][i] = new Rook(Colour::WHITE, 1);
                        break;
                    case 'B':
                        board[7][i] = new Bishop(Colour::WHITE, 1);
                        break;
                    case 'N':
                        board[7][i] = new Knight(Colour::WHITE, 1);
                        break;
                }
                return true;
            }
        }
    }
    return false;
}

bool Board::littlecastle(Colour turn) {
    int i;
    turn == Colour::WHITE ? i = 0 : i = 7;
    if(board[i][7] == nullptr || (board[i][7]->getName() != "\u2656" && board[i][7]->getName() != "\u265C") || ((board[i][7]->getName() == "\u2656" || board[i][7]->getName() == "\u265C") && board[i][7]->getColour() == turn && board[i][7]->getFirstMove() == false)){  
        //Rook moved
        return false;
    }
    if(board[i][5] != nullptr || board[i][6] != nullptr){
        //Path not clear
        return false;
    }
    if(incheck(turn)){
        // Player is in check
        return false;
    }
    if(board[i][4] == nullptr || (board[i][4]->getName() != "\u265A" && board[i][4]->getName() != "\u2654") || ((board[i][4]->getName() == "\u265A" || board[i][4]->getName() == "\u2654") && board[i][4]->getColour() == turn && board[i][4]->getFirstMove() == false)){
        // King moved
        return false;
    }
    //save the king and the rook
    Piece * king = board[i][4];
    Piece * rook = board[i][7];
    //Perform the move
    board[i][6] = board[i][4];
    board[i][4] = nullptr;
    board[i][5] = board[i][7];
    board[i][7] = nullptr;

    // Check if the player is in check in that new position
    if(incheck(turn)){
        // Player is in check, undo the move
        board[i][4] = king;
        board[i][7] = rook;
        board[i][6] = nullptr;
        board[i][5] = nullptr;
        return false;
    }

    cout << "Castle !" << endl;
    return true;
}

bool Board::bigcastle(Colour turn) {
    int i;
    turn == Colour::WHITE ? i = 0 : i = 7;
    if(board[i][0] == nullptr || (board[i][0]->getName() != "\u2656" && board[i][0]->getName() != "\u265C") || ((board[i][0]->getName() == "\u2656" || board[i][0]->getName() == "\u265C") && board[i][0]->getColour() == turn && board[i][0]->getFirstMove() == false)){
        //Rook moved
        return false;
    }
    if(board[i][1] != nullptr || board[i][2] != nullptr || board[i][3] != nullptr){
        //Path not clear
        return false;
    }
    if(incheck(turn)){
        // Player is in check
        return false;
    }
    if(board[i][4] == nullptr || (board[i][4]->getName() != "\u265A" && board[i][4]->getName() != "\u2654") || ((board[i][4]->getName() == "\u265A" || board[i][4]->getName() == "\u2654") && board[i][4]->getColour() == turn && board[i][4]->getFirstMove() == false)){
        // King moved
        return false;
    }

    //Save the king and the rook
    Piece * king = board[i][4];
    Piece * rook = board[i][0];

    //Perform the move
    board[i][2] = board[i][4];
    board[i][4] = nullptr;
    board[i][3] = board[i][0];
    board[i][0] = nullptr;

    //Check if the player is in check
    if(incheck(turn)){
        //Player is in check, undo the move
        board[i][4] = king;
        board[i][0] = rook;
        board[i][2] = nullptr;
        board[i][3] = nullptr;
        return false;
    }

    cout << "Big Castle !" << endl;

    return true;
}

bool Board::checkmate(Colour turn) {
    // Iterate over all the pieces of the player and check if a move is possible
    for (int i = 0; i < NBCOL; i++){
        for (int j = 0; j < NBCOL; j++){
            if (board[i][j] != nullptr && board[i][j]->getColour() == turn){
                for (int k = 0; k < NBCOL; k++){
                    for (int l = 0; l < NBCOL; l++){
                        if (movepiece(Square(j, i), Square(l, k), turn, false)){
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool Board::pat(Colour turn) {
    // If no move possible and not in check : pat
    if(!incheck(turn) && checkmate(turn)){
        return true;
    }
    // If no moves possible for both players : pat
    if(checkmate(turn) && checkmate((turn == Colour::WHITE ? Colour::BLACK : Colour::WHITE))){
        return true;
    }
    return false;
}

bool Board::movepiece(Square origin, Square dest, Colour turn, bool actualmove, bool checktest) {

    // if origin or dest are not valid squares, return false
    if (origin.validsquare() == false || dest.validsquare() == false){
        if(actualmove) cout << "Invalid move" << endl;
        return false;
    }

    // if origin is empty, return false
    if (board[origin.getX()][origin.getY()] == nullptr){
        if(actualmove) cout << "No piece at this position" << endl;
        return false;
    }

    // if dest = origin, return false
    if (origin.getX() == dest.getX() && origin.getY() == dest.getY()){
        if(actualmove) cout << "You must move the piece" << endl;
        return false;
    }

    // Check for a diagonal move for pawns
    if((board[origin.getX()][origin.getY()]->getName() == "\u2659" || board[origin.getX()][origin.getY()]->getName() == "\u265F") && origin.getY() != dest.getY()){
        if(board[dest.getX()][dest.getY()] == nullptr && !(turn == Colour::WHITE ? enpassantb[dest.getY()] == 1 && dest.getX() == 5 : enpassantw[dest.getY()] == 1 && dest.getX() == 2)){ 
            if(actualmove) cout << "Pawns can only move diagonally to capture a piece" << endl;
            return false;
        }
    }
    // check for en passant and delete the pawn that was captured
    if((board[origin.getX()][origin.getY()]->getName() == "\u2659" || board[origin.getX()][origin.getY()]->getName() == "\u265F") && origin.getY() != dest.getY() && board[dest.getX()][dest.getY()] == nullptr){
        if(turn == Colour::WHITE && enpassantb[dest.getY()] == 1 && dest.getX() == 5){
            if(actualmove){
                cout << "En passant !" << endl;
                cout << "Piece captured: " << board[dest.getX() - 1][dest.getY()]->getName() << endl;
                nocapture = 0;
                board[dest.getX() - 1][dest.getY()] = nullptr;
            }
        }
        if(turn == Colour::BLACK && enpassantw[dest.getY()] == 1 && dest.getX() == 2){
            if(actualmove){
                cout << "En passant !" << endl;
                cout << "Piece captured: " << board[dest.getX() + 1][dest.getY()]->getName() << endl;
                nocapture = 0;
                board[dest.getX() + 1][dest.getY()] = nullptr;
            }
        }
    }

    // Check for a move for pawn if there is a piece in front of it
    if ((board[origin.getX()][origin.getY()]->getName() == "\u2659" || board[origin.getX()][origin.getY()]->getName() == "\u265F") && abs(origin.getX() - dest.getX()) >= 1 && origin.getY() == dest.getY() && board[dest.getX()][dest.getY()] != nullptr){
        if(actualmove) cout << "Pawns can't capture a piece in front of them" << endl;
        return false;
    }

    // Check if the player is moving his own piece
    if (board[origin.getX()][origin.getY()]->getColour() != turn){
        if(actualmove) cout << "You can only move your own pieces" << endl;
        return false;
    }

    // Check if the origin square is empty
    Piece * piece = board[origin.getX()][origin.getY()];
    if (piece == nullptr){
        if(actualmove) cout << "No piece at this position" << endl;
        return false;
    }

    if (piece->possiblemove(origin, dest) == false){
        if(actualmove) cout << "Impossible move" << endl;
        return false;
    }
    if (board[dest.getX()][dest.getY()] != nullptr && board[dest.getX()][dest.getY()]->getColour() == piece->getColour()){
        if(actualmove) cout << "A piece of the same colour is already at this position" << endl;
        return false;
    }

    //Check if the path is clear (except for knights)
    if (piece->getName() != "\u265E" && piece->getName() != "\u2658"){
        int x = origin.getX();
        int y = origin.getY();
        while (x != dest.getX() || y != dest.getY()){
            if (x < dest.getX()){
                x++;
            }
            if (x > dest.getX()){
                x--;
            }
            if (y < dest.getY()){
                y++;
            }
            if (y > dest.getY()){
                y--;
            }
            if ((x != dest.getX() || y != dest.getY()) && board[x][y] != nullptr){
                if(actualmove) cout << "The path is not clear" << endl;
                return false;
            }
        }
    }

    // Check if the move will put the player in check (i added the chektest parameter to avoid recursion when testing check state)
    if (!checktest && willputincheck(origin, dest, turn)){
        if(actualmove) cout << "This move would put you in check" << endl;
        return false;
    }

    // Move the piece if not a simulation
    if(actualmove) {
        if (board[dest.getX()][dest.getY()] != nullptr){
        cout << "Piece captured: " << board[dest.getX()][dest.getY()]->getName() << endl;
        board[dest.getX()][dest.getY()] = nullptr;
        nocapture = 0;
        }else{
            nocapture++;
        }
        board[dest.getX()][dest.getY()] = piece;
        board[origin.getX()][origin.getY()] = nullptr;
        cout << "Piece moved from " << origin.tostring() << " to " << dest.tostring() << endl;
    }

    // enpassant arrays update
    if(actualmove){
        for (int i = 0; i < NBCOL; i++){
            enpassantw[i] = 0;
            enpassantb[i] = 0;
        }
    }

    // put 1 in the corresponding enpassant array if the pawn moved 2 squares forward
    if (piece->getName() == "\u2659" && abs(origin.getX() - dest.getX()) == 2 && actualmove){
        enpassantw[origin.getY()] = 1;
    }
    if (piece->getName() == "\u265F" && abs(origin.getX() - dest.getX()) == 2 && actualmove){
        enpassantb[origin.getY()] = 1;
    }

    //if the moved piece is a pawn, a rook, or the king, set firstmove to false
    if (actualmove && (piece->getName() == "\u2659" || piece->getName() == "\u265F" || piece->getName() == "\u265C" || piece->getName() == "\u2656" || piece->getName() == "\u265A" || piece->getName() == "\u2654")){
        piece->setFirstMove(false);
    }
    return true;

}

void Board::canonicallyprintboard(string score) {
    string boardstring = "";
    // Canonical names for the pieces
    string canonicalnameswhites[6] = {"wR", "wN", "wB", "wQ", "wK", "wP"};
    string canonicalnamesblacks[6] = {"bR", "bN", "bB", "bQ", "bK", "bP"};
    // Unicode names for the pieces
    string whitenames[6] = {"\u2656", "\u2658", "\u2657", "\u2655", "\u2654", "\u2659"};
    string blacknames[6] = {"\u265C", "\u265E", "\u265D", "\u265B", "\u265A", "\u265F"};
    // Iterate over the board and add the pieces to the string
    for (int i = 0; i < NBCOL; i++){
        for (int j = 0; j < NBCOL; j++){
            if (board[i][j] == nullptr){
                boardstring += ",";
            }else{
                for (int k = 0; k < 6; k++){
                    if (board[i][j]->getName() == whitenames[k]){
                        boardstring += canonicalnameswhites[k];
                    }
                    if (board[i][j]->getName() == blacknames[k]){
                        boardstring += canonicalnamesblacks[k];
                    }
                }
                boardstring += ",";
            }
        }
    }
    boardstring += " ";
    // Add the score to the string
    boardstring += score;
    cout << boardstring << endl;
}