// cards.h : main header file for the CARDS application
//

#if !defined(AFX_CARDS_H__E1100439_25AF_11DC_A328_009027972DB2__INCLUDED_)
#define AFX_CARDS_H__E1100439_25AF_11DC_A328_009027972DB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCardsApp:
// See cards.cpp for the implementation of this class
//

class CCardsApp : public CWinApp
{
public:
	CCardsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCardsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCardsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARDS_H__E1100439_25AF_11DC_A328_009027972DB2__INCLUDED_)
