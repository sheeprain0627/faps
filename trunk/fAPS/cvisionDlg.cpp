
// cvisionDlg.cpp : implementation file


#include "stdafx.h"
#include "cvision.h"
#include "cvisionDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "OpenGLControl.h"

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
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON3);
}

void CcvisionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
	DDX_Control(pDX, IDC_SLIDER1, m_zoomSlider);
}


BEGIN_MESSAGE_MAP(CcvisionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CcvisionDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CcvisionDlg::OnBnClickedButton1)
	//	ON_WM_ERASEBKGND()
	ON_WM_DRAWITEM()
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
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


	//********* Included tab initialization********//


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

	m_TabCtrl.AddPage(m_pDlgPage1, _T("      Critical Points      "));
	m_TabCtrl.AddPage(m_pDlgPage2, _T("Edit 3D"));

	//tab 3 designs 
	m_pDlgPage3->MoveWindow(rectPage);
	m_TabCtrl.AddPage(m_pDlgPage3, _T("Age Progression"));	
	m_pDlgPage3->agebar.SetRange(20,50);
	m_pDlgPage3->agebar.SetTicFreq(5);

	//Setting Slider Properties
	m_zoomSlider.SetRangeMin(20);
	m_zoomSlider.SetRangeMax(80);
	m_zoomSlider.SetTicFreq(5);


	///////////////************tab finished***************//////////////


	///////*************Font size of Text in edit ctrl***********///////////

	/*CFont fnt;
	fnt.CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
	ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	DEFAULT_PITCH, "Cambria");
	m_pDlgPage1->GetDlgItem(IDC_EDIT1)->SetFont(&fnt);
	m_pDlgPage1->SetDlgItemTextA(IDC_EDIT1, "Critical Points Selection Below:");

	fnt.Detach();*/

	///////**************Font finished*************************/////////

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


//////////********Background Image Of main dialog*********////////////

//BOOL CcvisionDlg::OnEraseBkgnd(CDC* pDC)
//{
//	CRect rect;
//		GetClientRect(&rect);
//		CDC dc;
//		dc.CreateCompatibleDC(pDC);
//		m_background.LoadBitmapA(IDB_BACKGROUND);
//		CBitmap* pOldBitmap = dc.SelectObject(&m_background);
//
//
//		BITMAP bmap;
//		
//		m_background.GetBitmap(&bmap);
//		pDC->StretchBlt(0, 0, rect.Width(),rect.Height(), &dc,0, 0,bmap.bmWidth,bmap.bmHeight, SRCCOPY);
//
//		
//		dc.SelectObject(pOldBitmap);
//
//	return true;	//CDialogEx::OnEraseBkgnd(pDC);
//}


/////////**************Backgrnd Finished******************/////////////////////


//////////*************Button Colour*******************///////////////////////

void CcvisionDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if((nIDCtl==IDOK) || (nIDCtl==IDCANCEL))         //checking for the button 

	{
		CDC dc;
		RECT rect;
		dc.Attach(lpDrawItemStruct ->hDC);   // Get the Button DC to CDC


		rect = lpDrawItemStruct->rcItem;     //Store the Button rect to our local rect.


		dc.Draw3dRect(&rect,RGB(255,255,255),RGB(0,0,0)); 

		dc.FillSolidRect(&rect,RGB(0,0,0));//Here you can define the required color to appear on the Button.


		UINT state=lpDrawItemStruct->itemState;  //This defines the state of the Push button either pressed or not. 


		if((state & ODS_SELECTED))
		{
			dc.DrawEdge(&rect,EDGE_SUNKEN,BF_RECT);

		}
		else
		{
			dc.DrawEdge(&rect,EDGE_RAISED,BF_RECT);
		}

		dc.SetBkColor(RGB(0,00,0));   //Setting the Text Background color

		dc.SetTextColor(RGB(255,255,255));     //Setting the Text Color
		//dc.SetText



		TCHAR buffer[MAX_PATH];           //To store the Caption of the button.

		ZeroMemory(buffer,MAX_PATH );     //Intializing the buffer to zero

		::GetWindowText(lpDrawItemStruct->hwndItem,buffer,MAX_PATH); //Get the Caption of Button Window 


		dc.DrawText(buffer,&rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);//Redraw the  Caption of Button Window 


		dc.Detach();  // Detach the Button DC

	}

	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


///////////////////***********Button Finished**************////////////////////////

BOOL CcvisionDlg::OnEraseBkgnd(CDC* pDC)
{

	SBitdraw(pDC, IDB_BACKGROUND, 1);
	return true;//CDialog::OnEraseBkgnd(pDC);
}

bool CcvisionDlg::SBitdraw(CDC *pDC, UINT nIDResource, int i) 
{
	CBitmap* m_bitmap;
	m_bitmap=new CBitmap();
	m_bitmap->LoadBitmap(nIDResource);
	if(!m_bitmap->m_hObject)
		return true;
	CRect rect;
	GetClientRect(&rect);
	CDC dc;
	dc.CreateCompatibleDC(pDC);    
	dc.SelectObject(m_bitmap);
	int bmw, bmh ;
	BITMAP bmap;
	m_bitmap->GetBitmap(&bmap);
	bmw = bmap.bmWidth;
	bmh = bmap.bmHeight;
	int xo=0, yo=0;
	switch(i){
	case 1:
		pDC->StretchBlt(xo, yo, rect.Width(),
			rect.Height(), &dc,
			0, 0,bmw,bmh, SRCCOPY);
		break;
	case 2:
		if(bmw < rect.Width())
			xo = (rect.Width() - bmw)/2;
		else 
			xo=0;
		if(bmh < rect.Height())
			yo = (rect.Height()-bmh)/2;
		else
			yo=0;
		pDC->BitBlt (xo, yo, rect.Width(),
			rect.Height(), &dc,
			0, 0, SRCCOPY);
		break;
	case 3:
		for (yo = 0; yo < rect.Height(); yo += bmh)
		{
			for (xo = 0; xo < rect.Width(); xo += bmw)
			{
				pDC->BitBlt (xo, yo, rect.Width(),
					rect.Height(), &dc,
					0, 0, SRCCOPY);
			}
		}
	}
	return true;

}



void CcvisionDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
