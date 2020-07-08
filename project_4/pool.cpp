#include "pool.h"
#include "quarto.h"

using namespace std;

Pool::Pool(){
    for (int i= 0; i < NP; i++){
        pieces[i] = Piece((Height)(i / 8 % 2), (Color)(i / 4 % 2), (Shape)(i /2 % 2), (Top)(i % 2));
        pieces[i].setUsed(0);
    }
}

Piece & Pool::getUnusedPiece(int index){
    if (pieces[index].Piece::isUsed()) {
        UsedPieceException expt = UsedPieceException(pieces[index]);
        throw expt;
    }
    return pieces[index];
}

Piece & Pool::getUnusedPiece(Height h, Color c, Shape s, Top t){
    int index = 8 * h + 4 * c + 2 * s + t;
    return Pool::getUnusedPiece(index);
}

Piece & Pool::getUnusedPiece(const std::string &in){
    if (in.length() > 4){
        InvalidInputException expt = InvalidInputException(in);
            throw expt;
    }
    int para[4];
    for (int i = 0; i < N; i++){
        bool isFound = 0;
        for (int j = 0; j < 2; j++){
            if (ALLCODE[i][j] == in[i]){
                para[i] = j;
                isFound = 1;
                break;
            }
        }
        if (!isFound){
            InvalidInputException expt = InvalidInputException(in);
            throw expt;
        }
    }
    return Pool::getUnusedPiece((Height)para[0], (Color)para[1], (Shape)para[2], (Top)para[3]);
}

std::string Pool::toString() const{
    string out="Available:\n";
    string temp1, temp2;
    string tp;
    for (int i = 0; i < NP; i++){
        if (!pieces[i].Piece::isUsed()){
            tp = pieces[i].toString();
            temp1.append(tp.substr(0,2) + " ");
            temp2.append(tp.substr(2,2) + " ");
        }
    }
    out.append(temp1 + "\n" + temp2);
    return out;
}