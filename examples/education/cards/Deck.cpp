// Deck1.cpp: implementation of the CDeck class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cards.h"
#include "Deck.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int CDeck::defMaxSuit = 4;
int CDeck::defMaxCard = 52;

CDeck::CDeck()
: maxSuit(defMaxSuit), maxCard(defMaxCard)
{
  init();
}

CDeck::CDeck(int _maxSuit, int _maxCard)
: maxSuit(_maxSuit), maxCard(_maxCard)
{
  init();
}

CDeck::~CDeck()
{

}

void CDeck::init()
{
	for (int suit = 0; suit < maxSuit; suit++)
	{
		for (int card = 0; card < maxCard; card++)
		{
			cards.AddTail(CCard(suit, card));
		}
	}

}

void CDeck::operator +(CCard &card)
{
   cards.AddTail(card);
}
