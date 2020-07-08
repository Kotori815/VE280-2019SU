#include "square.h"
#include "quarto.h"

using namespace std;

const char VName[] = {'A', 'B', 'C', 'D'};
const char Hname[] = {'1', '2', '3', '4'};
const string em = "empty";

Square::Square(Vaxis V, Haxis H): v(V), h(H), p(nullptr){}

Vaxis Square::getV() const{
    return v;
}

void Square::setV(Vaxis V){
    v = V;
}

Haxis Square::getH() const{
    return h;
}

void Square::setH(Haxis H){
    h = H;
}

const Piece & Square::getPiece() const{
    if (isEmpty()) {
        SquareException expt = SquareException(*this, em);
        throw expt;
    }
    return *p;
}

void Square::setPiece(const Piece *P){
    p = P;
}

bool Square::isEmpty() const{
    return (!p);
}

bool Square::isOnFirstDiagonal() const{
    return ((int)v == (int)h);
}

bool Square::isOnSecondDiagonal() const{
    return (((int)v + (int)h) == N - 1);
}

std::string Square::toString() const{
    char out[2];
    out[0] = VName[v];
    out[1] = Hname[h];
    return out;
}