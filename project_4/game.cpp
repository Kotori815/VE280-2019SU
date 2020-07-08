#include <iostream>
#include "quarto.h"
#include "piece.h"
#include "pool.h"
#include "square.h"
#include "board.h"
#include "player.h"
#include "exceptions.h"

using namespace std;

enum WIN {DRAW, ONE, TWO};

int main(int argc, char* argv[]){

    Board board;
    Pool pool;
    WIN win = DRAW;

    Player *plyr1, *plyr2;

    if (*argv[1] == 'h') plyr1 = getHumanPlayer(&board, &pool);
    if (*argv[1] == 'm') plyr1 = getMyopicPlayer(&board, &pool, atoi(argv[3]));
    if (*argv[2] == 'h') plyr2 = getHumanPlayer(&board, &pool);
    if (*argv[2] == 'm') plyr2 = getMyopicPlayer(&board, &pool, atoi(argv[3]));

    for(int round = 0; round < 16; round++){

        cout << board.toString() << endl;
        cout << endl;
        cout << pool.toString() << endl;
        cout << endl;
        
        if (round % 2 == 1){

            cout << "Player " << (round % 2 + 1) << "'s turn to select a piece:" << endl;
            Piece & p = plyr2->selectPiece();

            cout << "Player " << (2 - round % 2) << "'s turn to select a square:" << endl;
            Square & sq = plyr1->selectSquare(p);

            board.place(p, sq);
            if (board.isWinning(p, sq)){
                if (2 - round % 2 == 1) win = ONE;
                else win = TWO;
                break;
            }
        } else {
            cout << "Player " << (round % 2 + 1) << "'s turn to select a piece:" << endl;
            Piece & p = plyr1->selectPiece();
            cout << "Player " << (2 - round % 2) << "'s turn to select a square:" << endl;
            Square & sq = plyr2->selectSquare(p);
            board.place(p, sq);
            if (board.isWinning(p, sq)){
                if (2 - round % 2 == 1) win = ONE;
                else win = TWO;
                break;
            }
        }
    }

    cout << board.toString() << endl;
    cout << endl;

    switch (win){
    case DRAW:
        cout << "It is a draw." << endl;
        break;
    case ONE:
        cout << pool.toString() << endl;
        cout << endl;
        cout << "Player 1 has won!" << endl;
        break;
    case TWO:
        cout << pool.toString() << endl;
        cout << endl;
        cout << "Player 2 has won!" << endl;
        break;
    default:
        break;
    }

    return 0;
}