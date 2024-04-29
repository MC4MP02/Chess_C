#include "Piece.hpp"
#include <string>
#include <iostream>
using namespace std;

//1 --> blanques
//0 --> negres
//R=rei, D=Dama, T=torre, A=alfil, C=cavall, P=peó 

string Piece::converirAString() const
{
	string pieza = " ";

	if (m_color == CPC_White)
		pieza += "1";
	else {
		if (m_color == CPC_Black)
			pieza += "0";
	}

	if ((m_color == CPC_White) || (m_color == CPC_Black))
	{
		switch (m_type)
		{
		case CPT_King: pieza += "R";
			break;
		case CPT_Queen: pieza += "D";
			break;
		case CPT_Rook: pieza += "T";
			break;
		case CPT_Bishop: pieza += "A";
			break;
		case CPT_Knight: pieza += "C";
			break;
		case CPT_Pawn: pieza += "P";
			break;
		default:
			break;
		}
	}
	return pieza;
}

ChessPieceColor Piece::convertirColor(const char& c) const
{
	ChessPieceColor color = CPC_NONE;

	if (c == '0')
		color = CPC_White;
	else
		if (c == '1')
			color = CPC_Black;

	return color;
}

ChessPieceType Piece::convertirTipo(const char& c) const
{
	ChessPieceType tipo = CPT_EMPTY;


	switch (c)
	{
	case 'R': tipo = CPT_King;
		break;
	case 'D': tipo = CPT_Queen;
		break;
	case 'T': tipo = CPT_Rook;
		break;
	case 'A': tipo = CPT_Bishop;
		break;
	case 'C': tipo = CPT_Knight;
		break;
	case 'P': tipo = CPT_Pawn;
		break;
	default:
		break;
	}
	return tipo;
}

void Piece::renderP(const int posX, const int posY)
{
	if (m_color == CPC_White) {
		if (m_type == CPT_Pawn)
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
		if (m_type == CPT_Knight)
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KNIGHT_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
		if (m_type == CPT_King)
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KING_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
		if (m_type == CPT_Queen)
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_QUEEN_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
		if (m_type == CPT_Rook)
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ROOK_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
		if (m_type == CPT_Bishop)
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BISHOP_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
	}
	else if (m_color == CPC_Black)
	{
		if (m_type == CPT_Pawn)
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
		if (m_type == CPT_Knight)
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KNIGHT_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
		if (m_type == CPT_King)
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KING_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
		if (m_type == CPT_Queen)
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_QUEEN_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
		if (m_type == CPT_Rook)
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ROOK_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
		if (m_type == CPT_Bishop)
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BISHOP_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
	}
}