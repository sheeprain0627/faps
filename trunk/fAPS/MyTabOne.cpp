// MyTabOne.cpp : implementation file
//

#include "stdafx.h"
#include "MyTabOne.h"
#include "afxdialogex.h"

#include <cxcore.h>
#include "cv.h"
#include "highgui.h"
#include "cvaux.h"
#include <imgproc_c.h>
#include <fstream>
#include "Tdsloader.h"


//#include "ximage.h"

using namespace std;
using namespace cv;

const int poiX1 = 25;
const int poiY1 = 25;
CvPoint pt;
IplImage* img0[16];
ofstream myfile("res\\out.txt");
const char* name = "img";
const char* savePath = "res\\pil.bmp";
int countImage;
//count = 1;

int xCoordinate[16];
int yCoordinate[16];

// MyTabOne dialog

IMPLEMENT_DYNAMIC(MyTabOne, CDialog)

MyTabOne::MyTabOne(CWnd* pParent /*=NULL*/)
	: CDialog(MyTabOne::IDD, pParent)
{

}

MyTabOne::~MyTabOne()
{
}

void MyTabOne::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, m_picture, m_PicCtrl);
}


BEGIN_MESSAGE_MAP(MyTabOne, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &MyTabOne::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &MyTabOne::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &MyTabOne::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &MyTabOne::OnBnClickedButton4)
	ON_WM_LBUTTONDOWN(&TabOne::OnLButtonDown)
END_MESSAGE_MAP()


// MyTabOne message handlers

void MyTabOne::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	
		
	int poiX, poiY;
	int X, Y;
	X = point.x;
	Y = point.y;

	pt = cvPoint(X-256,Y-57);
	
	
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
		//cvShowImage(name, img0[countImage]);
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



void MyTabOne::OnBnClickedButton1()
{
	this->DragAcceptFiles(true);
	CFileDialog dlg(TRUE, _T("*.bmp"), NULL,
	OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
	_T("image files (*.bmp; *.jpg) |*.bmp;*.jpg|All Files (*.*)|*.*||"),NULL);
 
	dlg.m_ofn.lpstrTitle= _T("Open Image");
 
	if (dlg.DoModal() == IDOK) {
 
		CString path= dlg.GetPathName();
		LoadImage(path); //sent the pathe of image to opengl window
		
		countImage = 0;
		img0[countImage] = cvLoadImage(path);             // load the image
		
		cvSaveImage(savePath,img0[countImage]);

					
		CImage img;
		img.Load(path);
		m_PicCtrl.SetBitmap((HBITMAP)img.Detach());

		SetDlgItemTextA(IDC_EDIT1, "Please Click LEFT EYE critical points");

	}
		//MessageBox("Please Click LEFT EYE critical points!!!!!!", "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);

	//cvSaveImage("K:\\Reka-Photo\\pil.jpg",img0[0]);
	  
		//cvNamedWindow(name, 1);
		
		//cvShowImage(name, img0[countImage]);
		
		//cvSetMouseCallback(name, mouseHandler);
		


		//MessageBox("Please Click EYES critical points!!!!!!","Click Critical Points",MB_OK);
}


void MyTabOne::OnBnClickedButton2()
{
	countImage -=1;
	cvSaveImage(savePath,img0[countImage]);
	
	CImage img;
	img.Load(savePath);
	m_PicCtrl.SetBitmap((HBITMAP)img.Detach());
	
	if(countImage<5)
			SetDlgItemTextA(IDC_EDIT1, "Please Click LEFT EYE critical points");
			

	if(countImage>=5&& countImage<9)
			SetDlgItemTextA(IDC_EDIT1, "Please Click RIGHT EYE critical points");
			//MessageBox("Please Click RIGHT EYE critical points!!!!!!", "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);

		if(countImage<12 && countImage >=9)
			SetDlgItemTextA(IDC_EDIT1, "Please Click NOSE critical points");
			//MessageBox("Please Click NOSE critical points!!!!!!", "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);

		if(countImage>=12)
			SetDlgItemTextA(IDC_EDIT1, "Please Click MOUTH critical points");
			//MessageBox("Please Click MOUTH critical points!!!!!!", "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);

	//cvShowImage(name, img0[countImage-1]);
	
}


void MyTabOne::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
}


void MyTabOne::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
}
