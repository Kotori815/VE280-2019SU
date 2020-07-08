#include "player.h"
#include "quarto.h"
#include "board.h"
#include "pool.h"
#include "exceptions.h"
#include <cstring>
#include <iostream>

using namespace std;

class HumanPlayer : public Player{

public:
    HumanPlayer(Board *board, Pool *pool): Player(board, pool){}

    Piece & selectPiece(){
        while (1){
            string input;
            cout << "Enter a piece:";
            cin >> input;
            try{
                Piece & p = pool->getUnusedPiece(input);
                cout << input << " selected.\n" << endl;
                return p;
            }
            catch (InvalidInputException expt){cout << expt.what() << endl; continue;}
            catch (UsedPieceException expt){cout << expt.what() << endl; continue;}
        }
    }

    Square & selectSquare(const Piece &p){
        while (1)
        {   
            string input;
            cout << "Enter a position:";
            cin >> input;
            try{
                Square & sq = board->getEmptySquare(input);
                cout << input << " selected.\n" << endl;
                return sq;
            }
            catch (InvalidInputException expt){cout << expt.what() << endl; continue;}
            catch (SquareException expt){cout << expt.what() << endl; continue;}
        }
    }

    void initHP(Board &b0,Pool &p0){
        board = &b0;
        pool = &p0;
    }
};

Board b0;
Pool p0;

class MyopicPlayer : public Player{

    unsigned int seed;

public:
    MyopicPlayer(Board *board, Pool *pool, int s):Player(board, pool){seed = s;}

    Piece & selectPiece(){
        int nbIndex[NP];
        int unusedIndex[NP];
        int numofNB = 0;
        int numofUnused = 0;
        
        for (int i = 0; i < NP; i++){
            try{
                Piece & p = pool->getUnusedPiece((Height)(i / 8 % 2), (Color)(i / 4 % 2), (Shape)(i / 2 % 2), (Top)(i % 2));
                unusedIndex[numofUnused] = i;
                numofUnused++;
                bool isBad = 0;
                for (int v = 0; v < N; v++){
                    for (int h = 0; h < N; h++){
                        try{
                            Square & sq = board->getEmptySquare((Vaxis)v,(Haxis)h);
                            if (board->isWinning(p, sq)){
                                isBad = 1;
                            }
                        }
                        catch(SquareException expt) {continue;}
                    }
                }
                if (!isBad){
                    nbIndex[numofNB] = i;
                    numofNB++;
                }
            }
            catch(UsedPieceException expt) {continue;}
        }

        if (numofNB){
            int i = nbIndex[rand() % numofNB];
            Piece & p_chosen = pool->getUnusedPiece((Height)(i / 8 % 2), (Color)(i / 4 % 2), (Shape)(i / 2 % 2), (Top)(i % 2));
            cout << p_chosen.toString() << " selected.\n" << endl;
            return p_chosen;
        } else {
            int i = unusedIndex[rand() % numofUnused];
            Piece & p_chosen = pool->getUnusedPiece((Height)(i / 8 % 2), (Color)(i / 4 % 2), (Shape)(i / 2 % 2), (Top)(i % 2));
            cout << p_chosen.toString() << " selected.\n" << endl;
            return p_chosen;
        }
    }

    Square & selectSquare(const Piece &p){
        int emptyCoorV[NP];
        int emptyCoorH[NP];
        int numofEmpty = 0;
        for (int v = 0; v < N; v++) {
            for (int h = 0; h < N; h++) {
                try{
                    Square &sq = board->getEmptySquare((Vaxis)v,(Haxis)h);
                    emptyCoorV[numofEmpty] = v;
                    emptyCoorH[numofEmpty] = h;
                    numofEmpty++;
                    if(board->isWinning(p, sq)) {
                        cout << sq.toString() << " selected.\n" << endl;
                        return sq;
                    }
                }
                catch(SquareException expt) {continue;}
            }
        }
        int i = rand() % numofEmpty;
        Square &sq = board->getEmptySquare((Vaxis)emptyCoorV[i],(Haxis)emptyCoorH[i]);
        cout << sq.toString() << " selected.\n" << endl;
        return sq;

    }

    void initMP(Board &b0,Pool &p0, unsigned int s){
        board = &b0;
        pool = &p0;
        seed = s;
    }
};

static HumanPlayer hplyr = HumanPlayer(&b0, &p0);

Player *getHumanPlayer(Board *b, Pool *p){
    hplyr.initHP(*b,*p);
    return &hplyr;
}

static MyopicPlayer mptplyr = MyopicPlayer(&b0,&p0,0);

Player *getMyopicPlayer(Board *b, Pool *p, unsigned int s){
    srand(s);
    mptplyr.initMP(*b,*p,s);
    return &mptplyr;
}
