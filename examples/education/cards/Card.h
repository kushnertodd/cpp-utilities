// Card.h: interface for the CCard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CARD_H__E1100446_25AF_11DC_A328_009027972DB2__INCLUDED_)
#define AFX_CARD_H__E1100446_25AF_11DC_A328_009027972DB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCard  
{
public:
	CCard(int _suit, int _rank);
	CCard();
	virtual ~CCard();
    int suit;
	int rank;
};

#endif // !defined(AFX_CARD_H__E1100446_25AF_11DC_A328_009027972DB2__INCLUDED_)
