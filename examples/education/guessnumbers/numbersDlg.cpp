// numbersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "numbers.h"
#include "numbersDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNumbersDlg dialog

CNumbersDlg::CNumbersDlg(CWnd* pParent /*=NULL*/)
: CDialog(CNumbersDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNumbersDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNumbersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNumbersDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNumbersDlg, CDialog)
//{{AFX_MSG_MAP(CNumbersDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_HIGHBUTTON, OnHigh)
ON_BN_CLICKED(IDC_LOWBUTTON, OnLow)
ON_BN_CLICKED(IDC_AGAINBUTTON, OnAgain)
	ON_BN_CLICKED(IDC_RIGHTBUTTON, OnRightbutton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNumbersDlg message handlers

BOOL CNumbersDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	LOGFONT lf;                        // Used to create the CFont.
	memset(&lf, 0, sizeof(LOGFONT));   // Clear out structure.
	lf.lfHeight = 20;                  // Request a 20-pixel-high font
	lf.lfWeight = FW_BOLD;
	strcpy(lf.lfFaceName, "Arial");    //    with face name "Arial".
	m_font.CreateFontIndirect(&lf);    // Create the font.
	SetFont(&m_font);
	for (int i = IDC_FIRST; i <= IDC_LAST; i++) {
		CWnd* pWnd2  = static_cast<CWnd*>(GetDlgItem(i));
		pWnd2->SetFont(&m_font);
	}
	CWnd* pWnd2  = static_cast<CWnd*>(GetDlgItem(IDOK));
	pWnd2->SetFont(&m_font);
	OnAgain();
	
	//return TRUE;  // return TRUE  unless you set the focus to a control
	return FALSE;
}

void CNumbersDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNumbersDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNumbersDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CNumbersDlg::OnHigh() 
{
	// TODO: Add your control notification handler code here
	if (incr > 1) {
		incr = (incr + 1) / 2;
		guess -= incr;
		tries++;
		int2Field(guess, IDC_STATIC1);
		int2Field(tries, IDC_STATIC5);
	} else {
		this->MessageBox("Oh! You Win!");
		OnAgain();
	}
}

void CNumbersDlg::OnLow() 
{
	// TODO: Add your control notification handler code here
	if (incr > 1) {
		incr = (incr + 1) / 2;
		guess += incr;
		tries++;
		int2Field(guess, IDC_STATIC1);
		int2Field(tries, IDC_STATIC5);
	} else {
		this->MessageBox("Oh! You Win!");
		OnAgain();
	}
}

void CNumbersDlg::OnAgain() 
{
	// TODO: Add your control notification handler code here
    incr = 500;
	guess = 500;
    tries = 1;
	int2Field(guess, IDC_STATIC1);
	int2Field(tries, IDC_STATIC5);
}

void CNumbersDlg::OnRight() 
{
	// TODO: Add your control notification handler code here
	this->MessageBox("Great! I Win!");
    OnAgain();
}

void CNumbersDlg::OnRightbutton() 
{
	// TODO: Add your control notification handler code here
	this->MessageBox("Great! I Win!");
    OnAgain();
}

void CNumbersDlg::int2Field(int i, int id)
{
	char buf[50];
	sprintf(buf, "%d", i);
	CWnd* pWnd  = static_cast<CWnd*>(this->GetDlgItem(id));
	pWnd->SetWindowText(buf);
}