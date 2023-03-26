// numbersDlg.h : header file
//

#if !defined(AFX_NUMBERSDLG_H__2B4026A7_FB0E_11DB_A328_009027972DB2__INCLUDED_)
#define AFX_NUMBERSDLG_H__2B4026A7_FB0E_11DB_A328_009027972DB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CNumbersDlg dialog

class CNumbersDlg : public CDialog
{
// Construction
public:
	CNumbersDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNumbersDlg)
	enum { IDD = IDD_NUMBERS_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumbersDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNumbersDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHigh();
	afx_msg void OnLow();
	afx_msg void OnRight();
	afx_msg void OnAgain();
	afx_msg void OnRightbutton();
	void int2Field(int i, int id);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	int guess;
	int incr;
	int tries;
    CFont m_font;
#define maxguess 1000
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NUMBERSDLG_H__2B4026A7_FB0E_11DB_A328_009027972DB2__INCLUDED_)
