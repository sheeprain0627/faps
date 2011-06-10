
// cvisionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cvision.h"
#include "cvisionDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#include <cxcore.h>
#include "cv.h"
#include "highgui.h"
#include "cvaux.h"
#include <imgproc_c.h>
#include <fstream>


//#include "ximage.h"

using namespace std;
using namespace cv;



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
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcvisionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, m_picture, m_PicCtrl);
	//DDX_Control(pDX, IDC_BUTTON1, m_Button1);
	//  DDX_Control(pDX, IDC_EDIT1, m_textbox);

	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
}

BEGIN_MESSAGE_MAP(CcvisionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON1, &CcvisionDlg::OnOpen)
	//ON_BN_CLICKED(IDC_BUTTON2, &CcvisionDlg::OnBnClickedButton2)
	//ON_WM_LBUTTONDOWN(&CcvisionDlg::OnLButtonDown)
	ON_BN_CLICKED(IDOK, &CcvisionDlg::OnBnClickedOk)
//	ON_STN_CLICKED(m_picture, &CcvisionDlg::OnStnClickedpicture)
	//ON_EN_CHANGE(IDC_EDIT1, &CcvisionDlg::OnEnChangeEdit1)
	//ON_BN_CLICKED(IDC_BUTTON3, &CcvisionDlg::OnBnClickedButton3)
	//ON_BN_CLICKED(IDC_BUTTON1, &CcvisionDlg::OnBnClickedButton1)
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

	// TODO: Add extra initialization here

	SetDlgItemTextA(IDC_EDIT1, "Critical points Selection");


	CRect	rectPage;

	//创建页面
	m_pDlgPage1	= new MyTabOne;
	m_pDlgPage1->Create(IDD_DIALOG1, &m_TabCtrl);

	m_pDlgPage2	= new MyTabTwo;
	m_pDlgPage2->Create(IDD_DIALOG2, &m_TabCtrl);

	m_pDlgPage3	= new MyTabThree;
	m_pDlgPage3->Create(IDD_DIALOG3, &m_TabCtrl);

	//布置页面
	m_TabCtrl.GetWindowRect(rectPage);
	m_TabCtrl.ScreenToClient(rectPage);

	rectPage.left	+= 2;
	rectPage.top	+= 22;
	rectPage.right	-= 4;
	rectPage.bottom	-= 4;

	m_pDlgPage1->MoveWindow(rectPage);
	m_pDlgPage2->MoveWindow(rectPage);
	m_pDlgPage3->MoveWindow(rectPage);

	//添加页面
	m_TabCtrl.AddPage(m_pDlgPage1, _T("Tab1"));
	m_TabCtrl.AddPage(m_pDlgPage2, _T("Tab2"));
	m_TabCtrl.AddPage(m_pDlgPage3, _T("Tab3"));


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CcvisionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.





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
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CcvisionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




/*void mouseHandler(int event, int x, int y, int flags, void* param)
{
	
	int xP, yP;
	xP = x;
	yP = y;
	CString str1;
	str1.Format("%d", xP);

	CString str2;
	str2.Format("%d", yP);
	
//MessageBoxA("Please Click EYES critical points!!!!!!","Click Critical Points",MB_OK);
	switch(event){
	case CV_EVENT_LBUTTONDOWN:

		countImage++;
		//MessageBox(NULL,"X:" + str1 +"  Y:"+ str2 , "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);
	
		if(countImage==1)
			MessageBox(NULL,"Please Click LEFT EYE critical points!!!!!!", "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);

		if(countImage==5)
			MessageBox(NULL,"Please Click RIGHT EYE critical points!!!!!!", "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);

		if(countImage==9)
			MessageBox(NULL,"Please Click NOSE critical points!!!!!!", "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);

		if(countImage==12)
			MessageBox(NULL,"Please Click MOUTH critical points!!!!!!", "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);
		
		pt = cvPoint(x, y);
		img0[countImage] = cvCloneImage(img0[countImage-1]);
		cvCircle( img0[countImage], pt, 2, CV_RGB(0,255,0), -1, 8,0);
		cvShowImage(name, img0[countImage]);
	
	if(flags & CV_EVENT_FLAG_CTRLKEY)
	printf("Left button down with CTRL pressed\n");
	break;

	case CV_EVENT_MOUSEMOVE:
		
	case CV_EVENT_LBUTTONUP:
	printf("Left button up\n");
	break;
	}
	
}*/


//void CcvisionDlg::OnOpen()
//{
//	
//	
//		  
// }

//void CcvisionDlg::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	
//	
//		
//	
//
//}




//void CcvisionDlg::swap(int a, int b) {
//
//	int temp;
//
//	temp = a;
//	a = b;
//	b = temp;
//
//}

/*IplImage* Concat(IplImage * src,IplImage *dest){
	IplImage * temp;

	if (!src && dest)
	temp=cvCloneImage(dest);

	else if (!dest && src)
	temp=cvCloneImage(src);

	else if (!dest && !src)
	temp=NULL;

	else{
		cvSetImageROI(src,cvRect(0,0,src->width,src->height));
		temp=cvCreateImage(cvSize(src->width+dest->width+1,
		(dest->height<=src->height ? src->height : dest->height)),
		IPL_DEPTH_8U,1);
		
		cvCopyImage(dest,src);
		
		cvSetImageROI(dest,cvRect(src->width,0,
		dest->width,dest->height));
		cvCopy(dest,temp);
		temp->roi=NULL;
	}

	cvShowImage(name, temp);
	return temp;
}*/



//void CcvisionDlg::OnBnClickedButton2()
//{
//	
//
//}


void CcvisionDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


//void CcvisionDlg::OnStnClickedpicture()
//{
//	// TODO: Add your control notification handler code here
//}


//void CcvisionDlg::OnEnChangeEdit1()
//{
//	// TODO:  If this is a RICHEDIT control, the control will not
//	// send this notification unless you override the CDialogEx::OnInitDialog()
//	// function and call CRichEditCtrl().SetEventMask()
//	// with the ENM_CHANGE flag ORed into the mask.
//
//	// TODO:  Add your control notification handler code here
//}


//void CcvisionDlg::OnBnClickedButton3()
//{
//	// TODO: Add your control notification handler code here
//}


//void CcvisionDlg::OnBnClickedButton1()
//{
//	// TODO: Add your control notification handler code here
//}
