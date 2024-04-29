#ifndef CurrentGame_hpp
#define CurrentGame_hpp

#include <stdio.h>  
#include <string>
#include "GameInfo.h"
#include "Chessboard.hpp"
#include "QueueMovements.h"
#include "../GraphicManager.h"
using namespace std;



class CurrentGame {

public:
    CurrentGame() {}

    void init(GameMode mode, const string& intitialBoardFile, const string& movementsFile); //inicialitza segons el mode de joc
    void end(); //en el mode normal guarda els moviments de la cua al fitxer movementsFile que es passa per paràmetre

    //funcions per imprimir els diferents missatges per pantalla
    void msgInici();
    void msgWinner();
    void msgMoviments();

    void winner(); //determina si hi ha un guanyador o no amb l'atribut m_winner
    void auxUpdateandRender(int mousePosX, int mousePosY, bool mouseStatus); //funcio que determina quan cal pintar els moviments possibles, que mou les peces quan toca i que actualitza el torn de la partida
    bool updateAndRender(int mousePosX, int mousePosY, bool mouseStatus, bool click); //funcio que actualitza el tauler constantment amb l'ajuda de les altres funcions

private:

    Chessboard m_board; //tauler

    QueueMovements m_movements; //cua de moviments
    string m_movList; //nom del fitxer que guardem els moviments
    VecOfPositions m_validPos; //vector amb les posicions on es pot more

    GameMode m_mode; //mode de joc
    ChessPieceColor m_player; //torn

    ChessPosition m_mouse; //posicio a la que fem click
    ChessPosition m_selected; //posicio de la peça a moure

    bool m_winner; //true si hi ha guanyador
    bool m_move; //true si fem click per moure
    bool m_paint; //true si hem de pintar els possibles moviments


};

#endif /* CurrentGame_hpp */