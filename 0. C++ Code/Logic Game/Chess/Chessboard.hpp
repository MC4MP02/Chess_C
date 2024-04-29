#ifndef Chessboard_hpp
#define Chessboard_hpp

#include <stdio.h>
#include "Piece.hpp"
#include "ChessPosition.hpp"
#include "GameInfo.h"
//#include <vector>
#include "../GraphicManager.h"
//#include <iostream>
using namespace std;




class Chessboard {

public:
    Chessboard() {}
    ~Chessboard() {}

    void LoadBoardFromFile(const string& path);
    ChessPieceColor GetPieceColorAtPos(const ChessPosition& pos) const;
    ChessPieceType GetPieceTypeAtPos(const ChessPosition& pos) const;

    VecOfPositions  GetValidMoves(const ChessPosition& pos) const;

    void GetValidMovesPawn(const ChessPosition& pos, VecOfPositions& vector) const;
    void GetValidMovesKnight(const ChessPosition& pos, VecOfPositions& vector) const;
    void GetValidMovesBishop(const ChessPosition& pos, VecOfPositions& vector) const;
    void GetValidMovesRook(const ChessPosition& pos, VecOfPositions& vector) const;
    void GetValidMovesQueen(const ChessPosition& pos, VecOfPositions& vector) const;
    void GetValidMovesKing(const ChessPosition& pos, VecOfPositions& vector) const;

    bool MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo);
    string ToString() const;
    void renderCB();


private:
    Piece m_board[NUM_COLS][NUM_ROWS];

};


#endif /* Chessboard_hpp */