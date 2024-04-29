#include "Chessboard.hpp"
#include <iostream>
#include <fstream>

using namespace std;

void Chessboard::renderCB()
{
	int x = 1;
	int y = 0;
	int i = 0;

	for (int fil = NUM_ROWS - 1; fil >= 0; fil--) {

		y = i;
		i++;
		for (int col = 0; col < NUM_COLS; col++) {
			m_board[col][fil].renderP(x * col, y);
		}

	}

}

void Chessboard::LoadBoardFromFile(const string& path)
{
	ifstream fitxer;
	fitxer.open(path);

	if (fitxer.is_open())
	{
		string first;
		string second;

		fitxer >> first >> second;

		Piece pieza;
		ChessPieceColor color = pieza.convertirColor(first[0]);
		ChessPieceType tipo = pieza.convertirTipo(second[0]);
		pieza.setColor(color);
		pieza.setType(tipo);
		string posicion = "";
		posicion = second[1];
		posicion += second[2];
		ChessPosition pos(posicion);
		m_board[pos.getPosX()][pos.getPosY()] = pieza;



		while (!fitxer.eof())
		{
			fitxer >> first >> second;


			Piece pieza;
			ChessPieceColor color = pieza.convertirColor(first[0]);
			ChessPieceType tipo = pieza.convertirTipo(second[0]);
			pieza.setColor(color);
			pieza.setType(tipo);
			string posicion = "";
			posicion = second[1];
			posicion += second[2];
			ChessPosition pos(posicion);
			m_board[pos.getPosX()][pos.getPosY()] = pieza;

		}

		fitxer.close();
	}
}

ChessPieceColor Chessboard::GetPieceColorAtPos(const ChessPosition& pos) const
{
	return m_board[pos.getPosX()][pos.getPosY()].getColor();
}

ChessPieceType Chessboard::GetPieceTypeAtPos(const ChessPosition& pos) const
{
	return m_board[pos.getPosX()][pos.getPosY()].getType();

}


VecOfPositions Chessboard::GetValidMoves(const ChessPosition& pos) const
{
	VecOfPositions movimientos;

	switch (m_board[pos.getPosX()][pos.getPosY()].getType())
	{
	case CPT_Pawn: GetValidMovesPawn(pos, movimientos);
		break;
	case CPT_Knight: GetValidMovesKnight(pos, movimientos);
		break;
	case CPT_Bishop: GetValidMovesBishop(pos, movimientos);
		break;
	case CPT_Rook: GetValidMovesRook(pos, movimientos);
		break;
	case CPT_King: GetValidMovesKing(pos, movimientos);
		break;
	case CPT_Queen: GetValidMovesQueen(pos, movimientos);
		break;
	default:
		break;
	}

	return movimientos;

}

void Chessboard::GetValidMovesPawn(const ChessPosition& pos, VecOfPositions& vector) const
{

	ChessPosition auxChess;
	if (GetPieceColorAtPos(pos) == CPC_Black)
	{
		//COMPROVACION PRIMERA POS NEGRAS
		if (pos.getPosY() == 6)
		{
			if (m_board[pos.getPosX()][pos.getPosY() - 1].getType() == CPT_EMPTY)
			{
				auxChess.setPosX(pos.getPosX());
				auxChess.setPosY(pos.getPosY() - 1);
				vector.push_back(auxChess);
			}

			if (m_board[pos.getPosX()][pos.getPosY() - 2].getType() == CPT_EMPTY
				&& m_board[pos.getPosX()][pos.getPosY() - 1].getType() == CPT_EMPTY)
			{
				auxChess.setPosX(pos.getPosX());
				auxChess.setPosY(pos.getPosY() - 2);
				vector.push_back(auxChess);
			}
		}
		else
		{
			if (m_board[pos.getPosX()][pos.getPosY() - 1].getType() == CPT_EMPTY && pos.getPosY() > 0)
			{
				auxChess.setPosX(pos.getPosX());
				auxChess.setPosY(pos.getPosY() - 1);
				vector.push_back(auxChess);
			}
		}
		//COMPROVACION DIAGONAL NEGRAS
		if (m_board[pos.getPosX() + 1][pos.getPosY() - 1].getColor() == CPC_White && (pos.getPosX() + 1 <= 7) && (pos.getPosY() - 1 >= 0))
		{
			auxChess.setPosX(pos.getPosX() + 1);
			auxChess.setPosY(pos.getPosY() - 1);
			vector.push_back(auxChess);
		}
		if (m_board[pos.getPosX() - 1][pos.getPosY() - 1].getColor() == CPC_White && (pos.getPosX() - 1 >= 0) && (pos.getPosY() - 1 >= 0))
		{
			auxChess.setPosX(pos.getPosX() - 1);
			auxChess.setPosY(pos.getPosY() - 1);
			vector.push_back(auxChess);
		}
	}
	else if (GetPieceColorAtPos(pos) == CPC_White)
	{
		//COMPROVACION PRIMERA POS BLANCAS
		if (pos.getPosY() == 1)
		{
			if (m_board[pos.getPosX()][pos.getPosY() + 1].getType() == CPT_EMPTY)
			{
				auxChess.setPosX(pos.getPosX());
				auxChess.setPosY(pos.getPosY() + 1);
				vector.push_back(auxChess);
			}
			if (m_board[pos.getPosX()][pos.getPosY() + 2].getType() == CPT_EMPTY
				&& m_board[pos.getPosX()][pos.getPosY() + 1].getType() == CPT_EMPTY)
			{
				auxChess.setPosX(pos.getPosX());
				auxChess.setPosY(pos.getPosY() + 2);
				vector.push_back(auxChess);
			}
		}
		else {
			if (m_board[pos.getPosX()][pos.getPosY() + 1].getType() == CPT_EMPTY && pos.getPosY() < 7)
			{
				auxChess.setPosX(pos.getPosX());
				auxChess.setPosY(pos.getPosY() + 1);
				vector.push_back(auxChess);
			}
		}
		//COMPROVACION DIAGONAL BLANCAS
		if (m_board[pos.getPosX() + 1][pos.getPosY() + 1].getColor() == CPC_Black && (pos.getPosX() + 1 <= 7) && (pos.getPosY() + 1 <= 7))
		{
			auxChess.setPosX(pos.getPosX() + 1);
			auxChess.setPosY(pos.getPosY() + 1);
			vector.push_back(auxChess);
		}
		if (m_board[pos.getPosX() - 1][pos.getPosY() + 1].getColor() == CPC_Black && (pos.getPosX() - 1 >= 0) && (pos.getPosY() + 1 <= 7))
		{
			auxChess.setPosX(pos.getPosX() - 1);
			auxChess.setPosY(pos.getPosY() + 1);
			vector.push_back(auxChess);
		}
	}
}

void Chessboard::GetValidMovesKnight(const ChessPosition& pos, VecOfPositions& vector) const
{
	ChessPosition auxChess;

	if ((m_board[pos.getPosX() + 2][pos.getPosY() + 1].getType() == CPT_EMPTY)
		|| (m_board[pos.getPosX() + 2][pos.getPosY() + 1].getColor() != m_board[pos.getPosX()][pos.getPosY()].getColor()))
	{
		if (pos.getPosX() + 2 <= 7 && pos.getPosY() + 1 <= 7)
		{
			auxChess.setPosX(pos.getPosX() + 2);
			auxChess.setPosY(pos.getPosY() + 1);
			vector.push_back(auxChess);
		}
	}

	if ((m_board[pos.getPosX() + 1][pos.getPosY() + 2].getType() == CPT_EMPTY)
		|| (m_board[pos.getPosX() + 1][pos.getPosY() + 2].getColor() != m_board[pos.getPosX()][pos.getPosY()].getColor()))
	{
		if (pos.getPosX() + 1 <= 7 && pos.getPosY() + 2 <= 7)
		{
			auxChess.setPosX(pos.getPosX() + 1);
			auxChess.setPosY(pos.getPosY() + 2);
			vector.push_back(auxChess);
		}
	}

	if ((m_board[pos.getPosX() - 1][pos.getPosY() + 2].getType() == CPT_EMPTY)
		|| (m_board[pos.getPosX() - 1][pos.getPosY() + 2].getColor() != m_board[pos.getPosX()][pos.getPosY()].getColor()))
	{
		if (pos.getPosX() - 1 >= 0 && pos.getPosY() + 2 <= 7)
		{
			auxChess.setPosX(pos.getPosX() - 1);
			auxChess.setPosY(pos.getPosY() + 2);
			vector.push_back(auxChess);
		}
	}

	if ((m_board[pos.getPosX() - 2][pos.getPosY() + 1].getType() == CPT_EMPTY)
		|| (m_board[pos.getPosX() - 2][pos.getPosY() + 1].getColor() != m_board[pos.getPosX()][pos.getPosY()].getColor()))
	{
		if (pos.getPosX() - 2 >= 0 && pos.getPosY() + 1 <= 7)
		{
			auxChess.setPosX(pos.getPosX() - 2);
			auxChess.setPosY(pos.getPosY() + 1);
			vector.push_back(auxChess);
		}
	}

	if ((m_board[pos.getPosX() - 2][pos.getPosY() - 1].getType() == CPT_EMPTY)
		|| (m_board[pos.getPosX() - 2][pos.getPosY() - 1].getColor() != m_board[pos.getPosX()][pos.getPosY()].getColor()))
	{
		if (pos.getPosX() - 2 >= 0 && pos.getPosY() - 1 >= 0)
		{
			auxChess.setPosX(pos.getPosX() - 2);
			auxChess.setPosY(pos.getPosY() - 1);
			vector.push_back(auxChess);
		}
	}

	if ((m_board[pos.getPosX() - 1][pos.getPosY() - 2].getType() == CPT_EMPTY)
		|| (m_board[pos.getPosX() - 1][pos.getPosY() - 2].getColor() != m_board[pos.getPosX()][pos.getPosY()].getColor()))
	{
		if (pos.getPosX() - 1 >= 0 && pos.getPosY() - 2 >= 0)
		{
			auxChess.setPosX(pos.getPosX() - 1);
			auxChess.setPosY(pos.getPosY() - 2);
			vector.push_back(auxChess);
		}
	}

	if ((m_board[pos.getPosX() + 1][pos.getPosY() - 2].getType() == CPT_EMPTY)
		|| (m_board[pos.getPosX() + 1][pos.getPosY() - 2].getColor() != m_board[pos.getPosX()][pos.getPosY()].getColor()))
	{
		if (pos.getPosX() + 1 <= 7 && pos.getPosY() - 2 >= 0)
		{
			auxChess.setPosX(pos.getPosX() + 1);
			auxChess.setPosY(pos.getPosY() - 2);
			vector.push_back(auxChess);
		}
	}

	if ((m_board[pos.getPosX() + 2][pos.getPosY() - 1].getType() == CPT_EMPTY)
		|| (m_board[pos.getPosX() + 2][pos.getPosY() - 1].getColor() != m_board[pos.getPosX()][pos.getPosY()].getColor()))
	{
		if (pos.getPosX() + 2 <= 7 && pos.getPosY() - 1 >= 0)
		{
			auxChess.setPosX(pos.getPosX() + 2);
			auxChess.setPosY(pos.getPosY() - 1);
			vector.push_back(auxChess);
		}
	}


}

void Chessboard::GetValidMovesBishop(const ChessPosition& pos, VecOfPositions& vector) const
{
	bool fi = false;
	int auxX, auxY;

	int MaxArriba = 7 - pos.getPosY();
	int MaxAbajo = pos.getPosY();
	int MaxDerecha = 7 - pos.getPosX();
	int MaxIzquierda = pos.getPosX();

	int cont = 7;

	ChessPosition auxChess;

	int posX = pos.getPosX();
	int posY = pos.getPosY();

	//DIAGONAL DERECHA ARRIBA
	auxX = pos.getPosX() + 1;
	auxY = pos.getPosY() + 1;
	cont = 7;
	while (auxX <= 7 && auxY <= 7 && cont > 0 && !fi)
	{
		if (MaxArriba <= MaxDerecha)
		{
			cont = MaxArriba;
		}
		else
		{
			cont = MaxDerecha;
		}

		if (m_board[auxX][auxY].getType() == CPT_EMPTY && cont > 0) {
			auxChess.setPosX(auxX);
			auxChess.setPosY(auxY);
			vector.push_back(auxChess);
		}
		else
		{
			if (m_board[auxX][auxY].getColor() != m_board[posX][posY].getColor() && cont > 0)
			{
				auxChess.setPosX(auxX);
				auxChess.setPosY(auxY);
				vector.push_back(auxChess);
			}
			fi = true;
		}

		cont--;
		auxX++;
		auxY++;
	}

	//DIAGONAL DERECHA ABAJO
	auxX = pos.getPosX() + 1;
	auxY = pos.getPosY() - 1;
	cont = 7;
	fi = false;

	while (auxX <= 7 && auxY >= 0 && cont > 0 && !fi)
	{
		if (MaxAbajo <= MaxDerecha)
		{
			cont = MaxAbajo;
		}
		else {
			cont = MaxDerecha;
		}

		if (m_board[auxX][auxY].getType() == CPT_EMPTY && cont > 0)
		{
			auxChess.setPosX(auxX);
			auxChess.setPosY(auxY);
			vector.push_back(auxChess);
		}
		else
		{
			if (m_board[auxX][auxY].getColor() != m_board[pos.getPosX()][pos.getPosY()].getColor() && cont > 0)
			{
				auxChess.setPosX(auxX);
				auxChess.setPosY(auxY);
				vector.push_back(auxChess);
			}
			fi = true;
		}


		cont--;
		auxX++;
		auxY--;
	}

	//DIAGONAL IZQUIERDA ARRIBA
	auxX = pos.getPosX() - 1;
	auxY = pos.getPosY() + 1;
	cont = 7;
	fi = false;

	while (auxX >= 0 && auxY <= 7 && cont > 0 && !fi)
	{
		if (MaxArriba <= MaxIzquierda)
		{
			cont = MaxArriba;
		}
		else {
			cont = MaxIzquierda;
		}

		if (m_board[auxX][auxY].getType() == CPT_EMPTY && cont > 0) {
			auxChess.setPosX(auxX);
			auxChess.setPosY(auxY);
			vector.push_back(auxChess);
		}
		else
		{
			if (m_board[auxX][auxY].getColor() != m_board[pos.getPosX()][pos.getPosY()].getColor() && cont > 0)
			{
				auxChess.setPosX(auxX);
				auxChess.setPosY(auxY);
				vector.push_back(auxChess);
			}
			fi = true;
		}

		cont--;
		auxX--;
		auxY++;
	}

	//DIAGONAL IZQUIERDA ABAJO
	auxX = pos.getPosX() - 1;
	auxY = pos.getPosY() - 1;
	cont = 7;
	fi = false;

	while (auxX >= 0 && auxY >= 0 && cont > 0 && !fi)
	{
		if (MaxAbajo <= MaxIzquierda)
		{
			cont = MaxAbajo;
		}
		else {
			cont = MaxIzquierda;
		}

		if (m_board[auxX][auxY].getType() == CPT_EMPTY && cont > 0) {
			auxChess.setPosX(auxX);
			auxChess.setPosY(auxY);
			vector.push_back(auxChess);
		}
		else
		{
			if (m_board[auxX][auxY].getColor() != m_board[pos.getPosX()][pos.getPosY()].getColor() && cont > 0)
			{
				auxChess.setPosX(auxX);
				auxChess.setPosY(auxY);
				vector.push_back(auxChess);
			}
			fi = true;
		}

		cont--;
		auxX--;
		auxY--;
	}
}

void Chessboard::GetValidMovesRook(const ChessPosition& pos, VecOfPositions& vector) const
{

	bool fi = false;
	ChessPosition auxChess;

	int posX = pos.getPosX();
	int posY = pos.getPosY();

	//HORIZONTAL DERECHA

	int aux = pos.getPosX() + 1;
	while (aux <= 7 && !fi)
	{
		if (m_board[aux][posY].getType() == CPT_EMPTY)
		{
			auxChess.setPosX(aux);
			auxChess.setPosY(posY);
			vector.push_back(auxChess);
			aux++;
		}
		else
		{
			if (m_board[aux][posY].getColor() != m_board[posX][posY].getColor())
			{
				auxChess.setPosX(aux);
				auxChess.setPosY(posY);
				vector.push_back(auxChess);

			}
			fi = true;
		}

	}


	//HORIZONTAL IZQUIERDA

	fi = false;
	aux = pos.getPosX() - 1;

	while (aux >= 0 && !fi)
	{
		if (m_board[aux][posY].getType() == CPT_EMPTY)
		{
			auxChess.setPosX(aux);
			auxChess.setPosY(posY);
			vector.push_back(auxChess);
			aux--;
		}
		else
		{
			if (m_board[aux][posY].getColor() != m_board[posX][posY].getColor())
			{
				auxChess.setPosX(aux);
				auxChess.setPosY(posY);
				vector.push_back(auxChess);

			}
			fi = true;
		}


	}

	//VERTICAL ARRIBA

	fi = false;
	aux = pos.getPosY() + 1;

	while (aux <= 7 && !fi)
	{
		if (m_board[posX][aux].getType() == CPT_EMPTY)
		{
			auxChess.setPosX(posX);
			auxChess.setPosY(aux);
			vector.push_back(auxChess);
			aux++;
		}
		else
		{
			if (m_board[posX][aux].getColor() != m_board[posX][posY].getColor())
			{
				auxChess.setPosX(posX);
				auxChess.setPosY(aux);
				vector.push_back(auxChess);

			}
			fi = true;
		}

	}


	fi = false;
	//VERTICAL ABAJO
	aux = pos.getPosY() - 1;

	while (aux >= 0 && !fi)
	{

		if (m_board[posX][aux].getType() == CPT_EMPTY)
		{
			auxChess.setPosX(posX);
			auxChess.setPosY(aux);
			vector.push_back(auxChess);
			aux--;
		}
		else
		{
			if (m_board[posX][aux].getColor() != m_board[posX][posY].getColor())
			{
				auxChess.setPosX(posX);
				auxChess.setPosY(aux);
				vector.push_back(auxChess);

			}
			fi = true;
		}
	}
}

void Chessboard::GetValidMovesQueen(const ChessPosition& pos, VecOfPositions& vector) const
{
	GetValidMovesRook(pos, vector);
	GetValidMovesBishop(pos, vector);
}

void Chessboard::GetValidMovesKing(const ChessPosition& pos, VecOfPositions& vector) const
{
	ChessPosition auxChess;

	//Moviments vericals
	if ((m_board[pos.getPosX()][pos.getPosY() - 1].getType() == CPT_EMPTY)
		|| (m_board[pos.getPosX()][pos.getPosY() - 1].getColor() != m_board[pos.getPosX()][pos.getPosY()].getColor()))
	{
		if (pos.getPosY() - 1 >= 0)
		{
			auxChess.setPosX(pos.getPosX());
			auxChess.setPosY(pos.getPosY() - 1);
			vector.push_back(auxChess);
		}
	}

	if ((m_board[pos.getPosX()][pos.getPosY() + 1].getType() == CPT_EMPTY)
		|| (m_board[pos.getPosX()][pos.getPosY() + 1].getColor() != m_board[pos.getPosX()][pos.getPosY()].getColor()))
	{
		if (pos.getPosY() + 1 <= 7)
		{
			auxChess.setPosX(pos.getPosX());
			auxChess.setPosY(pos.getPosY() + 1);
			vector.push_back(auxChess);
		}
	}

	//moviments horitzontals

	if ((m_board[pos.getPosX() - 1][pos.getPosY()].getType() == CPT_EMPTY)
		|| (m_board[pos.getPosX() - 1][pos.getPosY()].getColor() != m_board[pos.getPosX()][pos.getPosY()].getColor()))
	{
		if (pos.getPosX() - 1 >= 0)
		{
			auxChess.setPosX(pos.getPosX() - 1);
			auxChess.setPosY(pos.getPosY());
			vector.push_back(auxChess);
		}
	}

	if ((m_board[pos.getPosX() + 1][pos.getPosY()].getType() == CPT_EMPTY)
		|| (m_board[pos.getPosX() + 1][pos.getPosY()].getColor() != m_board[pos.getPosX()][pos.getPosY()].getColor()))
	{
		if (pos.getPosX() + 1 <= 7)
		{
			auxChess.setPosX(pos.getPosX() + 1);
			auxChess.setPosY(pos.getPosY());
			vector.push_back(auxChess);
		}
	}

	//moviments diagonals
	if ((m_board[pos.getPosX() - 1][pos.getPosY() - 1].getType() == CPT_EMPTY)
		|| (m_board[pos.getPosX() - 1][pos.getPosY() - 1].getColor() != m_board[pos.getPosX()][pos.getPosY()].getColor()))
	{
		if (pos.getPosY() - 1 >= 0 && pos.getPosX() - 1 >= 0)
		{
			auxChess.setPosX(pos.getPosX() - 1);
			auxChess.setPosY(pos.getPosY() - 1);
			vector.push_back(auxChess);
		}
	}

	if ((m_board[pos.getPosX() + 1][pos.getPosY() - 1].getType() == CPT_EMPTY)
		|| (m_board[pos.getPosX() + 1][pos.getPosY() - 1].getColor() != m_board[pos.getPosX()][pos.getPosY()].getColor()))
	{
		if (pos.getPosY() - 1 >= 0 && pos.getPosX() + 1 <= 7)
		{
			auxChess.setPosX(pos.getPosX() + 1);
			auxChess.setPosY(pos.getPosY() - 1);
			vector.push_back(auxChess);
		}
	}

	if ((m_board[pos.getPosX() - 1][pos.getPosY() + 1].getType() == CPT_EMPTY)
		|| (m_board[pos.getPosX() - 1][pos.getPosY() + 1].getColor() != m_board[pos.getPosX()][pos.getPosY()].getColor()))
	{
		if (pos.getPosY() + 1 <= 7 && pos.getPosX() - 1 >= 0)
		{
			auxChess.setPosX(pos.getPosX() - 1);
			auxChess.setPosY(pos.getPosY() + 1);
			vector.push_back(auxChess);
		}
	}

	if ((m_board[pos.getPosX() + 1][pos.getPosY() + 1].getType() == CPT_EMPTY)
		|| (m_board[pos.getPosX() + 1][pos.getPosY() + 1].getColor() != m_board[pos.getPosX()][pos.getPosY()].getColor()))
	{
		if (pos.getPosY() + 1 <= 7 && pos.getPosX() + 1 >= 0)
		{
			auxChess.setPosX(pos.getPosX() + 1);
			auxChess.setPosY(pos.getPosY() + 1);
			vector.push_back(auxChess);
		}
	}

}


bool Chessboard::MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo)
{
	bool mogut = false;
	int i = 0;
	Piece pieza;
	VecOfPositions movimientos = GetValidMoves(posFrom);

	while (!mogut && i < movimientos.size())
	{
		if (movimientos[i] == posTo)
		{
			pieza.setColor(m_board[posFrom.getPosX()][posFrom.getPosY()].getColor());
			pieza.setType(m_board[posFrom.getPosX()][posFrom.getPosY()].getType());
			m_board[posTo.getPosX()][posTo.getPosY()] = pieza; //movem la peça a la nova posició

			m_board[posFrom.getPosX()][posFrom.getPosY()].setColor(CPC_NONE);
			m_board[posFrom.getPosX()][posFrom.getPosY()].setType(CPT_EMPTY); //alliberem la posició a la que estava la peça moguda

			mogut = true;

		}
		else
			i++;

	}

	return mogut;
}

string Chessboard::ToString() const
{
	string tauler = "";
	int i;
	int j;

	for (i = 7; i >= 0; i--)
	{
		for (j = -1; j < 8; j++)
		{
			if (j == -1)
			{
				tauler += i;
				tauler += " ";
			}
			else
			{
				if (m_board[i][j].getType() == CPT_EMPTY)
				{
					if (j != 7)
						tauler += " __ ";
					else
						tauler += " __\n";
				}
				else
				{
					if (j != 7)
					{
						tauler += " ";
						tauler += m_board[i][j].converirAString();
						tauler += " ";
					}
					else
					{
						tauler += " ";
						tauler += m_board[i][j].converirAString();
						tauler += "\n";
					}
				}
			}
		}
	}

	tauler += "  a  b  c  d  e  f  g  h "; //afegeixo la última fila que és la que té les lletres de la columna


	return tauler;
}