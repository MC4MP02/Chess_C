#include "CurrentGame.hpp"
#include "GameInfo.h"
#include <iostream>
#include <fstream>


void CurrentGame::init(GameMode mode, const string& intitialBoardFile, const string& movementsFile)
{
    m_board.LoadBoardFromFile(intitialBoardFile); //inicialitza el tauler
    m_player = CPC_White; //el jugador que comença la partida es el blanc
    m_winner = false; //encara no hi ha guanyador
    m_mode = mode; //guardem el mode

    if (m_mode == GM_NORMAL) //en el mode normal guardarem els moviments que fem
    {
        m_movList = movementsFile;
    }
    else if (m_mode == GM_REPLAY) //mode replay inicialitzem la cua amb els moviments de la partida anterior
    {
        ifstream fitxer;
        fitxer.open(movementsFile);
        if (fitxer.is_open())
        {
            string i, f;
            fitxer >> i >> f;
            while (!fitxer.eof())
            {
                Movement mov;
                mov.inicialitza(i, f);
                m_movements.afegeix(mov);
                fitxer >> i >> f;
            }
            fitxer.close();
        }
    }
}


void CurrentGame::end()
{
    if (m_mode == GM_NORMAL)
    {
        ofstream f;
        f.open(m_movList);
        if (f.is_open())
        {
            Movement m;
            string mov;

            while (!m_movements.esBuida())
            {
                m = m_movements.getPrimer();
                mov = m.getMovement();
                m_movements.treu();
                f << mov;

            }
            f.close();
        }
    }
}


void CurrentGame::msgInici()
{
    string msg;
    if (m_mode == GM_NORMAL)
    {
        msg = "Game Mode: NORMAL";
        GraphicManager::getInstance()->drawFont(FONT_RED_30, CELL_INIT_X, CELL_INIT_Y + (CELL_H * NUM_ROWS) + 60, 0.8, msg); //missatge del mode en que estem
        string jug;
        if (m_player == CPC_Black) jug = "Black";
        else if (m_player == CPC_White) jug = "White";
        msg = "Turn : " + jug;
        GraphicManager::getInstance()->drawFont(FONT_RED_30, CELL_INIT_X, CELL_INIT_Y + (CELL_H * NUM_ROWS) + 110, 0.8, msg); //missatge per saber de qui es el torn
    }
    else if (m_mode == GM_REPLAY)
    {
        msg = "Game Mode: REPLAY";
        GraphicManager::getInstance()->drawFont(FONT_RED_30, CELL_INIT_X, CELL_INIT_Y + (CELL_H * NUM_ROWS) + 60, 0.8, msg); //missatge del mode en que estem
        string jug;
        if (m_player == CPC_Black) jug = "Black";
        else if (m_player == CPC_White) jug = "White";
        msg = "Turn : " + jug;
        GraphicManager::getInstance()->drawFont(FONT_RED_30, CELL_INIT_X, CELL_INIT_Y + (CELL_H * NUM_ROWS) + 110, 0.8, msg); //missatge per saber de qui es el torn

    }
}

void CurrentGame::msgWinner()
{
    string msg, winner;
    if (m_player == CPC_Black) winner = "BLACK";
    else if (m_player == CPC_White) winner = "WHITE";

    msg = "WINNER: " + winner;
    GraphicManager::getInstance()->drawFont(FONT_RED_30, CELL_INIT_X, CELL_INIT_Y + (CELL_H * NUM_ROWS) + 160, 2, msg);
}

void CurrentGame::msgMoviments()
{
    string msg, winner;
    msg = "No hi ha mes moviments";
    GraphicManager::getInstance()->drawFont(FONT_RED_30, CELL_INIT_X, CELL_INIT_Y + (CELL_H * NUM_ROWS) + 160, 2, msg);
}

void CurrentGame::winner()
{
    bool black = true;
    bool white = true;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            ChessPosition pos;
            pos.setPosX(i);
            pos.setPosY(j);
            if (m_board.GetPieceTypeAtPos(pos) == CPT_King && m_board.GetPieceColorAtPos(pos) == CPC_Black) white = false; //si existeix un rei negre el blanc no ha guanyat
            if (m_board.GetPieceTypeAtPos(pos) == CPT_King && m_board.GetPieceColorAtPos(pos) == CPC_White) black = false; //si existeix un rei blanc el negre no ha guanyat
        }
    }

    if (white || black) m_winner = true; //un dels dos ha guanyat
    else m_winner = false; //cap ha guanyat

}


bool CurrentGame::updateAndRender(int mousePosX, int mousePosY, bool mouseStatus, bool click)
{
    //inicialitzem el tauler
    GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);
    msgInici();
    bool fi = false;

    if (m_mode == GM_NORMAL) //mode NORMAL
    {
        if (m_paint) //si el boolea que indica que s'ha de pintar es true
        {
            m_validPos = m_board.GetValidMoves(m_selected); //moviments de la peça seleccionada
            for (int i = 0; i < m_validPos.size(); i++)
            {
                int x = m_validPos[i].getPosX();
                int y = (NUM_ROWS - 1) - m_validPos[i].getPosY();
                GraphicManager::getInstance()->drawSprite(IMAGE_VALID_POS, CELL_INIT_X + (x * CELL_W), (CELL_INIT_Y + (y * CELL_H))); //pintem els possibles moviments
            }
            m_board.renderCB(); //render
        }
        else m_board.renderCB(); //si no s'ha de pintar fem el render directament

        if (!m_winner)
        {
            auxUpdateandRender(mousePosX, mousePosY, mouseStatus); //si encara no hi ha guanyador anem a la funcio select per fer el seguent moviment
        }
        else
        {
            msgWinner();
            fi = true;
        }
    }


    else if (m_mode == GM_REPLAY) //mode REPLAY
    {
        m_board.renderCB();

        if (click && !m_movements.esBuida()) //si cliquem i la pila no es buida
        {
            Movement mov;
            ChessPosition i, f;
            mov = m_movements.getPrimer();
            i = mov.getInici();
            f = mov.getFinal();
            bool mogut = m_board.MovePiece(i, f); //fem el moviment del top de la pila
            m_movements.treu(); //treiem el moviment de la cua
            winner();
            if (!m_winner && m_player == CPC_White) m_player = CPC_Black;
            else if (!m_winner && m_player == CPC_Black) m_player = CPC_White;

        }
        else if (m_movements.esBuida())
        {
            if (m_winner) msgWinner();
            else msgMoviments();

            fi = true;
        }
    }
    return fi;

}

void CurrentGame::auxUpdateandRender(int mousePosX, int mousePosY, bool mouseStatus)
{
    if (mouseStatus) // si cliquem
    {
        if (mousePosX >= CELL_INIT_X && mousePosX <= (CELL_INIT_X + CELL_W * NUM_COLS) && mousePosY >= CELL_INIT_Y && mousePosY <= (CELL_INIT_Y + CELL_H * NUM_ROWS)) //mirem si esta dins del tauler
        {
            ChessPosition pos((mousePosX - CELL_INIT_X) / CELL_W, (NUM_ROWS - 1) - (mousePosY - CELL_INIT_Y) / (CELL_H));
            m_mouse = pos;

            if (m_board.GetPieceColorAtPos(m_mouse) == m_player) //si la fitxa seleccionada es del color del jugador guardem la peça seleccionada i indiquem que podem pintar
            {
                m_paint = true;
                m_move = false;
                m_selected = m_mouse;
            }
            else
            {
                m_paint = false;
                m_move = m_board.MovePiece(m_selected, m_mouse);
            }

        }
        else
        {
            m_move = false;
            m_paint = false;
        }
    }

    if (m_move)
    {
        //guardar a la cua de moviments
        Movement m;
        string inicial;
        string final;
        inicial = m_selected.convertirAString();
        final = m_mouse.convertirAString();
        m.inicialitza(inicial, final);
        m_movements.afegeix(m);

        winner();

        //canvi de torn si no hi ha guanyador
        if (!m_winner && m_player == CPC_White) m_player = CPC_Black;
        else if (!m_winner && m_player == CPC_Black) m_player = CPC_White;
    }

}