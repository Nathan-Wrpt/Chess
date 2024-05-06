#include "Game.h"

Game::Game() : board(Colour::WHITE, Colour::BLACK) {}

void Game::play() {
    string input;
    bool white_turn = true;
    string score;

    while (true) {
        // Display the board
        board.display();
        if(board.incheck(white_turn ? Colour::WHITE : Colour::BLACK)){
            cout << "Check" << endl;
        }
        // Display the current player
        cout << "Player " << (white_turn ? "White" : "Black") << ", enter your move: ";
        cin >> input;

        // Check for special commands
        if (input == "/quit") {
            cout << "Game abandoned by " << (white_turn ? "White" : "Black") << " player. Score: ?-?" << endl;
            score = "?-?";
            break;
        } else if (input == "/resign") {
            cout << "Game ended by " << (white_turn ? "White" : "Black") << " player's resignation. Score: ";
            score = (white_turn ? "0-1" : "1-0");
            cout << score << endl;
            break;
        } else if (input == "/draw") {
            cout << "Game ended by mutual agreement for a draw. Score: 1/2 - 1/2" << endl;
            score = "1/2-1/2";
            break;
        } else if (!is_valid_input(input) && !is_valid_input_short_castling(input) && !is_valid_input_long_castling(input)) {
            cout << "Invalid input. Please enter a valid move." << endl;
            continue;
        }

        // Execute the move
        bool moved = false;
        if (is_valid_input(input)) {
            Square origin(input[0] - 'a', input[1] - '1');
            Square dest(input[2] - 'a', input[3] - '1');
            moved = board.movepiece(origin, dest, (white_turn ? Colour::WHITE : Colour::BLACK), true);

        } else if (is_valid_input_short_castling(input)) {
            moved = board.littlecastle((white_turn ? Colour::WHITE : Colour::BLACK));

        } else if (is_valid_input_long_castling(input)) {
            moved = board.bigcastle((white_turn ? Colour::WHITE : Colour::BLACK));
        }
        if(!moved){
            cout << "Invalid move" << endl;
            continue;
        }
        
        board.transformpieceifothersidereached();

        // Check for stalemate or checkmate
        if (board.pat((white_turn ? Colour::BLACK : Colour::WHITE))) {
            board.display();
            cout << "Game ended in stalemate. Score: 1/2 - 1/2" << endl;
            score = "1/2-1/2";
            break;
        }
        if (board.checkmate((white_turn ? Colour::BLACK : Colour::WHITE))) {
            board.display();
            cout << "Player " << (white_turn ? "White" : "Black") << " wins by checkmate! Score: ";
            score = (white_turn ? "1-0" : "0-1");
            cout << score << endl;
            break;
        }
        // Switch to the next player
        white_turn = !white_turn;

        // Check if no captures have been done in the last 100 moves
        if (board.getnocapture() >= 100) {
            cout << "Game ended in a draw due to 100-moves rule. Score: 1/2 - 1/2" << endl;
            score = "1/2-1/2";
            break;
        }
    }
    board.canonicallyprintboard(score);
}

bool Game::is_valid_input(string const & cmd) {
    regex movePattern("[a-h][1-8][a-h][1-8]");
    return regex_match(cmd, movePattern);
}

bool Game::is_valid_input_short_castling(string const & cmd) {
    regex movePattern("(O|o|0)-(O|o|0)");
    return regex_match(cmd, movePattern);
}

bool Game::is_valid_input_long_castling(string const & cmd) {
    regex movePattern("(O|o|0)-(O|o|0)-(O|o|0)");
    return regex_match(cmd, movePattern);
}