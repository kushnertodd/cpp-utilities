// Deck1.h: interface for the CDeck class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DECK1_H__E1100447_25AF_11DC_A328_009027972DB2__INCLUDED_)
#define AFX_DECK1_H__E1100447_25AF_11DC_A328_009027972DB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "hand.h"

class CDeck  
{
public:
	void operator+(CCard& card);
	void init();
	CDeck();
	CDeck(int _maxSuit, int _maxCard);
	virtual ~CDeck();
	int maxSuit;
	int maxCard;
    CList<CCard, CCard&> cards;
	static  int defMaxSuit;
	static  int defMaxCard;
};

#endif // !defined(AFX_DECK1_H__E1100447_25AF_11DC_A328_009027972DB2__INCLUDED_)
