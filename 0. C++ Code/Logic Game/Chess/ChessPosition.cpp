#include "ChessPosition.hpp"
#include "GameInfo.h"

bool ChessPosition::operator==(const ChessPosition& posicio) const
{
	return ((m_posX == posicio.m_posX) && (m_posY == posicio.m_posY));
}

ostream& operator<<(ostream& output, ChessPosition& posicio)
{
	output << posicio.convertirAString();
	return output;
}

ChessPosition::ChessPosition(string posicion)
{
	switch (posicion[0])
	{
	case 'a': m_posX = 0;
		break;
	case 'b': m_posX = 1;
		break;
	case 'c': m_posX = 2;
		break;
	case 'd': m_posX = 3;
		break;
	case 'e': m_posX = 4;
		break;
	case 'f': m_posX = 5;
		break;
	case 'g': m_posX = 6;
		break;
	case 'h': m_posX = 7;
		break;
	default:
		break;
	}

	switch (posicion[1])
	{
	case '1': m_posY = 0;
		break;
	case '2': m_posY = 1;
		break;
	case '3': m_posY = 2;
		break;
	case '4': m_posY = 3;
		break;
	case '5': m_posY = 4;
		break;
	case '6': m_posY = 5;
		break;
	case '7': m_posY = 6;
		break;
	case '8': m_posY = 7;
		break;
	default:
		break;
	}
}

string ChessPosition::convertirAString() const
{
	string posicion = " ";

	switch (m_posX)
	{
	case 0: posicion += "a";
		break;
	case 1: posicion += "b";
		break;
	case 2: posicion += "c";
		break;
	case 3: posicion += "d";
		break;
	case 4: posicion += "e";
		break;
	case 5: posicion += "f";
		break;
	case 6: posicion += "g";
		break;
	case 7: posicion += "h";
		break;
	default:
		break;
	}

	switch (m_posY)
	{
	case 0: posicion += "1";
		break;
	case 1: posicion += "2";
		break;
	case 2: posicion += "3";
		break;
	case 3: posicion += "4";
		break;
	case 4: posicion += "5";
		break;
	case 5: posicion += "6";
		break;
	case 6: posicion += "7";
		break;
	case 7: posicion += "8";
		break;
	default:
		break;
	}

	return posicion;
}

/* Coordinate system:
	Y (rows)
  . ^
  . |  **Black**
  4 |
  3 |
  2 |
  1 |  **White**
 (0,0)----------> X (cols)
	  a b c ...
*/