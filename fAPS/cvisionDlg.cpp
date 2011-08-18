
// cvisionDlg.cpp : implementation file


#include "stdafx.h"
#include "cvision.h"
#include "cvisionDlg.h"
#include "afxdialogex.h"
#include "resource.h"

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
	public:
		CAboutDlg();

	// Dialog Data
		enum { IDD = IDD_ABOUTBOX };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
	protected:
		DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CcvisionDlg dialog




CcvisionDlg::CcvisionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CcvisionDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CcvisionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
}


BEGIN_MESSAGE_MAP(CcvisionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CcvisionDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CcvisionDlg::OnBnClickedButton1)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CcvisionDlg message handlers

BOOL CcvisionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	CRect rect;

	// Get size and position of the picture control
	GetDlgItem(IDC_OPENGL)->GetWindowRect(rect);

	// Convert screen coordinates to client coordinates
	ScreenToClient(rect);

	// Create OpenGL Control window
	m_oglWindow.oglCreate(rect, this);

	// Setup the OpenGL Window's timer to render
	//m_oglWindow.OnTimer();
	//m_oglWindow.m_type=GL_POINTS;
	m_oglWindow.m_unpTimer = m_oglWindow.SetTimer(1, 1, 0);
	
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	// Included tab initialization

	
	CRect	rectPage, rectPage1;

	m_pDlgPage1	= new MyTabOne;
	m_pDlgPage1->Create(IDD_DIALOG1, &m_TabCtrl);

	m_pDlgPage2	= new MyTabTwo;
	m_pDlgPage2->Create(IDD_DIALOG2, &m_TabCtrl);

	m_pDlgPage3	= new MyTabThree;
	m_pDlgPage3->Create(IDD_DIALOG3, &m_TabCtrl);

	m_TabCtrl.GetWindowRect(rectPage);
	m_TabCtrl.ScreenToClient(rectPage);
	
	rectPage.left	+= 2;
	rectPage.top	+= 22;
	rectPage.right	-= 4;
	rectPage.bottom	-= 4;
	
	m_pDlgPage1->MoveWindow(rectPage);
	m_pDlgPage2->MoveWindow(rectPage);
	
	m_TabCtrl.AddPage(m_pDlgPage1, _T("Critical Points"));
	m_TabCtrl.AddPage(m_pDlgPage2, _T("Edit 3D"));
	
	rectPage.left	+= 2;
	rectPage.top	+= 22;
	rectPage.right	-= 4;
	rectPage.bottom -= 4;

	//tab 3 designs 
	m_pDlgPage3->MoveWindow(rectPage);
	m_TabCtrl.AddPage(m_pDlgPage3, _T("Age Progression"));	
	m_pDlgPage3->agebar.SetRange(20,50);
	m_pDlgPage3->agebar.SetTicFreq(5);


	m_pDlgPage1->SetDlgItemTextA(IDC_EDIT1, "Critical Points Selection Below:");

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CcvisionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();

	} else {
		CDialogEx::OnSysCommand(nID, lParam);
	}
}



BOOL CcvisionDlg::OnEraseBkgnd(CDC* pDC)
{
    CRect rect;
    GetClientRect(&rect);
    CBrush myBrush(RGB(192, 0, 68));    // dialog background color
    CBrush *pOld = pDC->SelectObject(&myBrush);
    BOOL bRes  = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
    pDC->SelectObject(pOld);    // restore old brush
	CBitmap cBit;
	/*cBit.setBiIDB_BITMAP8);
	CBitmap *pOld = pDC->SelectObject(IDB_BITMAP8);
    BOOL bRes  = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
    pDC->SelectObject(pOld);*/ 
    return bRes;                       // CDialog::OnEraseBkgnd(pDC);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework

void CcvisionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	} else {

		CDialogEx::OnPaint();

	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CcvisionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CcvisionDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CcvisionDlg::OnBnClickedButton1()
{
	
}
