// Hand.h: interface for the CHand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HAND_H__EBD4B901_25B4_11DC_A328_009027972DB2__INCLUDED_)
#define AFX_HAND_H__EBD4B901_25B4_11DC_A328_009027972DB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "card.h"
#include <afxtempl.h>

class CHand  
{
public:
	void operator +(CCard &card);
	CHand();
	virtual ~CHand();
    CList<CCard, CCard&> cards;

};

#endif // !defined(AFX_HAND_H__EBD4B901_25B4_11DC_A328_009027972DB2__INCLUDED_)
