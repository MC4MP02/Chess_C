#ifndef Piece_hpp
#define Piece_hpp

#include <stdio.h>
//#include <vector>
#include "../GraphicManager.h"
#include "GameInfo.h"
using namespace std;

typedef enum {
    CPT_King,
    CPT_Queen,
    CPT_Rook,
    CPT_Bishop,
    CPT_Knight,
    CPT_Pawn,
    CPT_EMPTY
} ChessPieceType;

typedef enum {
    CPC_Black,
    CPC_White,
    CPC_NONE
} ChessPieceColor;

class Piece {

public:
    Piece() { m_type = CPT_EMPTY; m_color = CPC_NONE; }
    Piece(ChessPieceType type, ChessPieceColor color) { m_type = type, m_color = color; }
    ~Piece() {}

    ChessPieceType getType() const { return m_type; }
    void setType(ChessPieceType type) { m_type = type; }
    ChessPieceColor getColor() const { return m_color; }
    void setColor(ChessPieceColor color) { m_color = color; }

    ChessPieceColor convertirColor(const char& c) const;
    ChessPieceType convertirTipo(const char& c) const;

    void renderP(const int posX, const int posY);

    string converirAString() const;

private:
    ChessPieceType  m_type;
    ChessPieceColor m_color;
};


#endif