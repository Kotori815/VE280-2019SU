#include <iostream>
#include "quarto.h"
#include "piece.h"
#include "pool.h"
#include "square.h"
#include "board.h"
#include "player.h"
#include "exceptions.h"

#include <cassert>

using namespace std;

int main(){
    
    // Piece test
    /*
    cout << "Piece test" << endl;
    Piece piece1 = {SHORT, BEIGE, SQUARE, SOLID};
    Piece piece2 = {SHORT, SEPIA, SQUARE, HOLLOW};
    cout << piece1.toString() << " " << piece2.toString() << endl;
    cout << 1 << piece1.compareHeight(piece2) << endl;
    cout << 0 << piece1.compareColor(piece2) << endl;
    cout << 1 << piece1.compareShape(piece2) << endl;
    cout << 0 << piece1.compareTop(piece2) << endl;
    */

    // Pool test
    /*
    cout << "Pool test" << endl;
    Pool pool1;
    //piece1 = pool1.getUnusedPiece(SHORT, BEIGE, SQUARE, SOLID);
    //piece2 = pool1.getUnusedPiece("SEQH");
    //pool1.getUnusedPiece("SEQH").setUsed(1);
    cout << pool1.toString() << endl;
    */

    // Square test
    /*
    Square sq = Square(B,H2);
    Piece piece1 = {SHORT, BEIGE, SQUARE, SOLID};
    cout << sq.isEmpty() << endl;
    cout << sq.toString() << endl;
    sq.setPiece(&piece1);
    cout << &sq.getPiece() << endl;
    cout << "FD: " << sq.isOnFirstDiagonal() << " SD: " << sq.isOnSecondDiagonal() << endl;
    */
    
    // Board test
    
    Pool pool;
    Board board;

    //Piece p;
    Piece &p = pool.getUnusedPiece("SBCH");
    //Square sq;
    Square &sq = board.getEmptySquare("A1");
    
    board.place(p ,sq);

    cout << pool.toString() << endl;
    cout << board.toString() << endl;
    

/* 
    Player *pl = getMyopicPlayer(&board, &pool, 3);
        
    cout << "select piece" << endl;
    Piece p ;
    p = pl->selectPiece();
    cout << p.toString() << p.isUsed() << endl;
    
    cout << "select square" << endl;
    Square sq;
    sq = pl->selectSquare(p);
    cout << p.isUsed() << sq.isEmpty() << endl;

    board.place(p,sq);

    cout << p.isUsed() << sq.isEmpty() << endl;

    cout <<pool.toString() << endl;
    cout << board.toString() << endl;
   */
    return 0;
}