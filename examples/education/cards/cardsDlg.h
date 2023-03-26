// cardsDlg.h : header file
//

#if !defined(AFX_CARDSDLG_H__E110043B_25AF_11DC_A328_009027972DB2__INCLUDED_)
#define AFX_CARDSDLG_H__E110043B_25AF_11DC_A328_009027972DB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "deck.h"

/////////////////////////////////////////////////////////////////////////////
// CCardsDlg dialog

class CCardsDlg : public CDialog
{
// Construction
public:
	CCardsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCardsDlg)
	enum { IDD = IDD_CARDS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCardsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCardsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARDSDLG_H__E110043B_25AF_11DC_A328_009027972DB2__INCLUDED_)
