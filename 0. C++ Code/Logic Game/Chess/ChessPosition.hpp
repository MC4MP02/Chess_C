#ifndef ChessPosition_hpp
#define ChessPosition_hpp

#include <stdio.h>
#include <string>
#include <ostream>
#include <vector>

using namespace std;


class ChessPosition {

public:
    ChessPosition() { m_posX = 0; m_posY = 0; }
    ChessPosition(string posicio);
    ChessPosition(int x, int y) { m_posX = x; m_posY = y; }
    ~ChessPosition() {}

    int getPosX()const { return m_posX; }
    void setPosX(int posX) { m_posX = posX; }
    int getPosY()const { return m_posY; }
    void setPosY(int posY) { m_posY = posY; }

    bool operator==(const ChessPosition& posicio) const;
    string convertirAString()const;

private:
    int m_posX; //Column
    int m_posY; //Row
};
ostream& operator<<(ostream& output, ChessPosition& posicio);
typedef vector<ChessPosition> VecOfPositions;

#endif