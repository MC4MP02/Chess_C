#include <iostream>
#include "QueueMovements.h"


ChessPosition Movement::getInici()
{
	string i;
	i = m_movement[0];
	i += m_movement[1];
	ChessPosition pos(i);
	return pos;
}


ChessPosition Movement::getFinal()
{
	string f;
	f = m_movement[3];
	f += m_movement[4];
	ChessPosition pos(f);
	return pos;
}

void QueueMovements::afegeix(Movement& valor)
{
	if (m_primer != nullptr)
	{
		Node* aux = new Node;
		aux->setNext(nullptr);
		aux->setValor(valor);
		m_ultim->setNext(aux);
		m_ultim = aux;
	}
	else
	{
		m_primer = new Node;
		m_primer->setValor(valor);
		m_primer->setNext(nullptr);

		m_ultim = m_primer;
	}


}

void QueueMovements::treu()
{
	if (m_primer != nullptr)
	{
		Node* aux = m_primer;
		m_primer = aux->getNext();

		delete aux;
	}

}

bool QueueMovements::esBuida() const {

	if (m_primer == nullptr) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}