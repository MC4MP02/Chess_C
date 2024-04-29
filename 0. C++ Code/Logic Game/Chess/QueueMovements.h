#ifndef QueueMovements_h
#define QueueMovements_h

#include <stdio.h>
#include <string>
#include "GameInfo.h"
#include "ChessPosition.hpp"
using namespace std;

class Movement
{
public:
	void inicialitza(string posInici, string posFinal) { m_movement = posInici, m_movement+=" ", m_movement += posFinal, m_movement += "\n"; }
	void setMovement(string moviments) { m_movement = moviments; }
	string getMovement() const { return m_movement; }
	ChessPosition getInici();
	ChessPosition getFinal();
private:
	string m_movement;

};

class Node
{
public:
	Movement& getValor() { return m_valor; }
	Node* getNext() { return m_next; }
	void setValor(const Movement& valor) { m_valor = valor; }
	void setNext(Node* next) { m_next = next; }
private:
	Movement m_valor;
	Node* m_next;
};


class QueueMovements
{
public:
	void afegeix(Movement& valor);
	void treu();
	Movement& getPrimer() const { return m_primer->getValor(); }
	Movement& getUltim() const { return m_ultim->getValor(); }
	bool esBuida() const;
private:
	Node* m_primer;
	Node* m_ultim;
};



#endif /* CurrentGame_hpp */