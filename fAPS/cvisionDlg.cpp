
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

const int poiX1 = 25;
const int poiY1 = 25;
CvPoint pt;
IplImage* img0[16];
ofstream myfile("J:\\Lecure-Notes\\Lecture_notes\\out.txt");
const char* name = "img";
const char* savePath = "res\\pil.bmp";
int countImage;
//count = 1;

int xCoordinate[16];
int yCoordinate[16];

int xHolder[16];
int yHolder[16];

int high_switch_value = 0;
int highInt = 0;
int low_switch_value = 0;
int lowInt = 0;

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
	DDX_Control(pDX, m_picture, m_PicCtrl);
	DDX_Control(pDX, IDC_BUTTON1, m_Button1);
	DDX_Control(pDX, IDC_EDIT1, m_textbox);
	
}

BEGIN_MESSAGE_MAP(CcvisionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CcvisionDlg::OnOpen)
	ON_BN_CLICKED(IDC_BUTTON2, &CcvisionDlg::OnBnClickedButton2)
	ON_WM_LBUTTONDOWN(&CcvisionDlg::OnLButtonDown)
	ON_BN_CLICKED(IDOK, &CcvisionDlg::OnBnClickedOk)
	ON_STN_CLICKED(m_picture, &CcvisionDlg::OnStnClickedpicture)
	ON_EN_CHANGE(IDC_EDIT1, &CcvisionDlg::OnEnChangeEdit1)
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


void switch_callback_h( int position ){
	highInt = position;
}
void switch_callback_l( int position ){
	lowInt = position;
}


void mouseHandler(int event, int x, int y, int flags, void* param)
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
	
}


void CcvisionDlg::OnOpen()
{
	countImage -=1;
	cvSaveImage(savePath,img0[countImage]);
	
	CImage img;
	img.Load(savePath);
	m_PicCtrl.SetBitmap((HBITMAP)img.Detach());
	
	if(countImage<4)
			SetDlgItemTextA(IDC_EDIT1, "Please Click LEFT EYE critical points");
			

	if(countImage>=4&& countImage<8)
			SetDlgItemTextA(IDC_EDIT1, "Please Click RIGHT EYE critical points");
			//MessageBox("Please Click RIGHT EYE critical points!!!!!!", "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);

		if(countImage<11 && countImage >=8)
			SetDlgItemTextA(IDC_EDIT1, "Please Click NOSE critical points");
			//MessageBox("Please Click NOSE critical points!!!!!!", "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);

		if(countImage>=11)
			SetDlgItemTextA(IDC_EDIT1, "Please Click MOUTH critical points");
			//MessageBox("Please Click MOUTH critical points!!!!!!", "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);

	//cvShowImage(name, img0[countImage-1]);
	
		  
 }

void CcvisionDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	
		
	int poiX, poiY;
	int X, Y;
	X = point.x;
	Y = point.y;

	pt = cvPoint(X-21,Y-45);
	
	
	//poiX = X-poiX1;
	//poiY = Y-poiY1;

	CString str1;
	str1.Format("%d", X);

	CString str2;
	str2.Format("%d", Y);
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON) {

		//MessageBox("X:" + str1+  "Y:" + str2,"aaaaaaaaaaaa",MB_ICONSTOP|MB_OK);
		countImage++;
		//MessageBox(NULL,"X:" + str1 +"  Y:"+ str2 , "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);
	
		
		
		
		img0[countImage] = cvCloneImage(img0[countImage-1]);
		
		cvCircle(img0[countImage], pt, 1, CV_RGB(0,255,0), -1, 8,0);
		cvShowImage(name, img0[countImage]);
		cvSaveImage(savePath,img0[countImage]);

		CImage img;
		img.Load(savePath);
		m_PicCtrl.SetBitmap((HBITMAP)img.Detach());
		xCoordinate[countImage-1] = pt.x;
		yCoordinate[countImage-1] = pt.y;

		if(countImage>=4&& countImage<8)
			SetDlgItemTextA(IDC_EDIT1, "Please Click RIGHT EYE critical points");
			//MessageBox("Please Click RIGHT EYE critical points!!!!!!", "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);

		if(countImage<11 && countImage >=8)
			SetDlgItemTextA(IDC_EDIT1, "Please Click NOSE critical points");
			//MessageBox("Please Click NOSE critical points!!!!!!", "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);

		if(countImage>=11)
			SetDlgItemTextA(IDC_EDIT1, "Please Click MOUTH critical points");
			//MessageBox("Please Click MOUTH critical points!!!!!!", "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);

		
		if(countImage == 16) {

			//insertionSort(xCoordinate, 15);
			//insertionSort(yCoordinate, 15);
		
			}


	}	

	
	//m_PicCtrl.
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON){

		//MessageBox("X:" + str1+  "Y:" + str2,"Sorry, this is not a 24 Bit Bitmap.",MB_ICONSTOP|MB_OK);
		
		
  }

	if (nFlags == WM_LBUTTONDOWN) {
		MessageBox("bbbbbb","Sorry, this is not a 24 Bit Bitmap.",MB_ICONSTOP|MB_OK);
	}
	
	CWnd::OnLButtonDown(nFlags, point);

}




void CcvisionDlg::swap(int a, int b) {

	int temp;

	temp = a;
	a = b;
	b = temp;

}

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



void CcvisionDlg::OnBnClickedButton2()
{
	this->DragAcceptFiles(true);
	CFileDialog dlg(TRUE, _T("*.bmp"), NULL,
	OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
	_T("image files (*.bmp; *.jpg) |*.bmp;*.jpg|All Files (*.*)|*.*||"),NULL);
 
	dlg.m_ofn.lpstrTitle= _T("Open Image");
 
	if (dlg.DoModal() == IDOK) {
 
		CString path= dlg.GetPathName();

		
		countImage = 0;
		img0[countImage] = cvLoadImage(path);             // load the image
		
		cvSaveImage(savePath,img0[countImage]);

		/*CRect rc;
		m_PicCtrl. GetWindowRect(&rc);

		rc.bottom = rc.top + img0[countImage]->height;
		rc.right = rc.left + img0[countImage]->width;*/

		//m_PicCtrl.MoveWindow(&rc, TRUE);
				
		CImage img;
		img.Load(path);
		m_PicCtrl.SetBitmap((HBITMAP)img.Detach());

		SetDlgItemTextA(IDC_EDIT1, "Please Click LEFT EYE critical points");
		//MessageBox("Please Click LEFT EYE critical points!!!!!!", "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);

	//cvSaveImage("K:\\Reka-Photo\\pil.jpg",img0[0]);
	  
		//cvNamedWindow(name, 1);
		
		//cvShowImage(name, img0[countImage]);
		
		//cvSetMouseCallback(name, mouseHandler);
		


		//MessageBox("Please Click EYES critical points!!!!!!","Click Critical Points",MB_OK);

		}

	

}


void CcvisionDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CcvisionDlg::OnStnClickedpicture()
{
	// TODO: Add your control notification handler code here
}


void CcvisionDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
