// numbers.h : main header file for the NUMBERS application
//

#if !defined(AFX_NUMBERS_H__2B4026A5_FB0E_11DB_A328_009027972DB2__INCLUDED_)
#define AFX_NUMBERS_H__2B4026A5_FB0E_11DB_A328_009027972DB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNumbersApp:
// See numbers.cpp for the implementation of this class
//

class CNumbersApp : public CWinApp
{
public:
	CNumbersApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumbersApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNumbersApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NUMBERS_H__2B4026A5_FB0E_11DB_A328_009027972DB2__INCLUDED_)
