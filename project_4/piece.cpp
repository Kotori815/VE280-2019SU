#include "piece.h"
#include "quarto.h"

using namespace std;

Piece::Piece(Height H, Color C, Shape S, Top T): h(H), c(C), s(S), t(T), used(0){}

bool Piece::compareHeight(const Piece &p) const{
    return (h == p.h);
}

bool Piece::compareColor(const Piece &p) const{
    return (c == p.c);
}

bool Piece::compareShape(const Piece &p) const{
    return (s == p.s);
}

bool Piece::compareTop(const Piece &p) const{
    return (t == p.t);
}

bool Piece::isUsed() const{
    return used;
}

void Piece::setUsed(bool u){
    used = u;
}

string Piece::toString() const{
    char out[4];
    out[0] = HCODE[h];
    out[1] = CCODE[c];
    out[2] = SCODE[s];
    out[3] = TCODE[t];
    return out;
}
