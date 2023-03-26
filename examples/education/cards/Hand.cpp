// Hand.cpp: implementation of the CHand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cards.h"
#include "Hand.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHand::CHand()
{

}

CHand::~CHand()
{

}

void CHand::operator +(CCard &card)
{
   cards.AddTail(card);
}
