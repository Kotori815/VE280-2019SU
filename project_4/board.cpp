#include "board.h"
#include "quarto.h"
#include <iostream>
using namespace std;

const char VName[] = {'A', 'B', 'C', 'D'};
const char Hname[] = {'1', '2', '3', '4'};
const string nem = "not empty";

Board::Board(){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            grid[i][j].setV((Vaxis)i);
            grid[i][j].setH((Haxis)j);
        }
    }
}

Square & Board::getSquare(Vaxis v, Haxis h){
    return grid[v][h];
}

Square & Board::getEmptySquare(Vaxis v, Haxis h){
    if (!getSquare(v,h).isEmpty()){
        SquareException excp = SquareException(this->getSquare(v,h), nem);
        throw excp;
    }
    return this->getSquare(v,h);
}

Square & Board::getEmptySquare(const std::string &s){
    int v,h;
    bool isValid1, isValid2;
    if (s.length() > 2){InvalidInputException expt = InvalidInputException(s); throw expt;}
    for (int i = 0; i < N; i++){
        if (s[0] == VName[i]) {v = i; isValid1 = 1;}
    }
    for (int j = 0; j < N; j++){
        if (s[1] == Hname[j]) {h = j; isValid2 = 1;}
    }

    if (!(isValid1 && isValid2))
    {InvalidInputException expt = InvalidInputException(s); throw expt;}
    
    return getEmptySquare((Vaxis)v, (Haxis)h);
}

void Board::place(Piece &p, Square &sq){
    sq.setPiece(&p);
    p.setUsed(1);
}

bool Board::isWinning(const Piece &p, const Square &sq){
    Vaxis v = sq.getV();
    Haxis h = sq.getH();
    bool isSame[N][N];
    
// vertical test

    for (int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            isSame[i][j] = 0;

    for (int i=0; i < N; i++){
        if (i == h) {
            for (int j = 0; j < N; j++)
                isSame[j][i] = 1;
            continue;
        }
        
        if (getSquare(v,(Haxis)i).isEmpty()) break;
        
        else {
            const Piece & pp = getSquare(v,(Haxis)i).getPiece();
            for (int j = 0; j < N; j++){
                isSame[0][i] = p.compareHeight(pp);
                isSame[1][i] = p.compareColor(pp);
                isSame[2][i] = p.compareShape(pp);
                isSame[3][i] = p.compareTop(pp);
	        }
        }
    }

    if ((isSame[0][0] && isSame[0][1] && isSame[0][2] && isSame[0][3])
             || (isSame[1][0] && isSame[1][1] && isSame[1][2] && isSame[1][3])
             || (isSame[2][0] && isSame[2][1] && isSame[2][2] && isSame[2][3])
             || (isSame[3][0] && isSame[3][1] && isSame[3][2] && isSame[3][3])) return 1;
    
// horizon test

    for (int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            isSame[i][j] = 0;

    for (int i=0; i < N; i++){
        if (i == v) {
            for (int j = 0; j < N; j++)
                isSame[j][i] = 1;
            continue;
        }
        
        if (getSquare((Vaxis)i,h).isEmpty()) break;
        
        else {
            const Piece & pp = getSquare((Vaxis)i,h).getPiece();
            for (int j = 0; j < N; j++){
                isSame[0][i] = p.compareHeight(pp);
                isSame[1][i] = p.compareColor(pp);
                isSame[2][i] = p.compareShape(pp);
                isSame[3][i] = p.compareTop(pp);
	        }
        }
    }

    if ((isSame[0][0] && isSame[0][1] && isSame[0][2] && isSame[0][3])
             || (isSame[1][0] && isSame[1][1] && isSame[1][2] && isSame[1][3])
             || (isSame[2][0] && isSame[2][1] && isSame[2][2] && isSame[2][3])
             || (isSame[3][0] && isSame[3][1] && isSame[3][2] && isSame[3][3])) return 1;

// First Diagonal test (if applicable)

    if(sq.isOnFirstDiagonal()){

        for (int i=0; i<N; i++)
            for(int j=0; j<N; j++)
                isSame[i][j] = 0;
        
        for (int i=0; i < N; i++){
            if (i == v) {
                for (int j = 0; j < N; j++)
                    isSame[j][i] = 1;
                continue;
            }
        
            if (getSquare((Vaxis)i,(Haxis)i).isEmpty()) break;
            
            else {
                const Piece & pp = getSquare((Vaxis)i,(Haxis)i).getPiece();
                for (int j = 0; j < N; j++){
                    isSame[0][i] = p.compareHeight(pp);
                    isSame[1][i] = p.compareColor(pp);
                    isSame[2][i] = p.compareShape(pp);
                    isSame[3][i] = p.compareTop(pp);
                }
            }
        }
    }

    if ((isSame[0][0] && isSame[0][1] && isSame[0][2] && isSame[0][3])
             || (isSame[1][0] && isSame[1][1] && isSame[1][2] && isSame[1][3])
             || (isSame[2][0] && isSame[2][1] && isSame[2][2] && isSame[2][3])
             || (isSame[3][0] && isSame[3][1] && isSame[3][2] && isSame[3][3])) return 1;

// Second Diagonal test (if applicable)

    if(sq.isOnSecondDiagonal()){

        for (int i=0; i<N; i++)
            for(int j=0; j<N; j++)
                isSame[i][j] = 0;
        
        for (int i=0; i < N; i++){
            if (i == v) {
                for (int j = 0; j < N; j++)
                    isSame[j][i] = 1;
                continue;
            }
        
            if (getSquare((Vaxis)i,(Haxis)(3-i)).isEmpty()) break;
        
            else {
                const Piece & pp = getSquare((Vaxis)i,(Haxis)(3-i)).getPiece();
                for (int j = 0; j < N; j++){
                    isSame[0][i] = p.compareHeight(pp);
                    isSame[1][i] = p.compareColor(pp);
                    isSame[2][i] = p.compareShape(pp);
                    isSame[3][i] = p.compareTop(pp);
                }
            }
        }
        if ((isSame[0][0] && isSame[0][1] && isSame[0][2] && isSame[0][3])
                || (isSame[1][0] && isSame[1][1] && isSame[1][2] && isSame[1][3])
                || (isSame[2][0] && isSame[2][1] && isSame[2][2] && isSame[2][3])
                || (isSame[3][0] && isSame[3][1] && isSame[3][2] && isSame[3][3])) return 1;
    }

        return 0;
}

std::string Board::toString() const{
    string out = "    1    2    3    4\n";
    string hline = "  +----+----+----+----+";
    string temp1, temp2, temp3;

    for (int i = 0; i < N; i++){
        out.append(hline + "\n");
        switch (i)
        {
        case 0:
            temp1.append("a |");
            break;
        case 1:
            temp1.append("b |");
            break;
        case 2:
            temp1.append("c |");
            break;
        case 3:
            temp1.append("d |");
            break;
        default:
            break;
        }
        temp2.append("  |");
        for (int j = 0;j < N; j++){
            Square sq = grid[i][j];
            if (sq.isEmpty()){
                temp1.append("    |");
                temp2.append("    |");
            } else {
                temp3 = sq.Square::getPiece().Piece::toString();
                temp1.append(" " + temp3.substr(0,2) + " |");
                temp2.append(" " + temp3.substr(2,2) + " |");
                temp3.clear();
            }
        }
        out.append(temp1 + "\n" + temp2 + "\n");
        temp1.clear(); temp2.clear();
    }
    out.append(hline);
    return out;
}
