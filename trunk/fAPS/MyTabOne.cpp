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
IplImage* img0[100];
ofstream myfile("res\\out.txt");//, ofstream::binary);
CString path;
const char* name = "img";
const char* savePath = "res\\pil.bmp";
int countImage;
bool load = false;
//count = 1;

int xCoordinate[100];
int yCoordinate[100];
int criticalPoints1[]={900,950,864,907,913,964,873,920,871,465,472,277,343,194,289};
int criticalPoints2[]={913,964,873,920,900,950,864,907,871,472,465,289,343,194,277};
int a=15;
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
	ON_BN_CLICKED(IDC_BUTTON5, &MyTabOne::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_SetFace, &MyTabOne::OnBnClickedSetface)
END_MESSAGE_MAP()


// MyTabOne message handlers

void MyTabOne::OnLButtonDown(UINT nFlags, CPoint point)
{
		
	int poiX, poiY;
	int X, Y;
	X = point.x;
	Y = point.y;

	pt = cvPoint(X-315,Y-66);
	
	
	//poiX = X-poiX1;
	//poiY = Y-poiY1;

	CString str1;
	str1.Format("%d", X);

	CString str2;
	str2.Format("%d", Y);
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON) {

		if(load == true ) {
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
 
		path= dlg.GetPathName();
		
		load = true;
		countImage = 0;
		img0[countImage] = cvLoadImage(path);             // load the image
		
		cvSaveImage(savePath,img0[countImage]);

		//OnBnClickedButton5();
		LoadImage(savePath,255,0,1); //sent the pathe of image to opengl window    //ajith
					
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
	myfile << "X\t\t";
	myfile << "\tY";
	myfile << "\n";

	for (int i=0; i < 15; i++) {

		myfile << xCoordinate[i];
		myfile << "\t\t\t";
		myfile << yCoordinate[i];
		myfile << "\n";

	}
	
	myfile.close();
	// TODO: Add your control notification handler code here
}


void MyTabOne::OnBnClickedButton4()
{
	
	
	// TODO: Add your control notification handler code here
}


void MyTabOne::OnBnClickedButton5()
{
	resizePicDB();
	//resizePic1();
	//cropPic1();
	//LoadImage(savePath,255,0,1);
	
	//IplImage *source = cvLoadImage( "res\\b.bmp");	float u1=((float)xCoordinate[a+4])/(source->width);	float v1=(1+(float)(source->height-yCoordinate[a+4]+2)/(source->height));	changeVU1(u1,v1);
	
}

int MyTabOne::getfwidth(){
	return (xCoordinate[a+1]-xCoordinate[a+0]);
}


int MyTabOne::getfHeight(){
	return (yCoordinate[a+3]-yCoordinate[a+2]);
}

void MyTabOne::resizePic(){
	// Create an IplImage object *image 
IplImage *source = cvLoadImage( path);
// Here we retrieve a percentage value to a integer
int fwidth=getfwidth();
int fheight=getfHeight();
double xpercent = 165.0/fwidth;
double ypercent=155.0/fheight;
int newwidth=(int)(((source->width)*xpercent));
int newheight=(int)(((source->height)*ypercent));

if(newwidth%2!=0){
	newwidth+=1;
}

if(newheight%2!=0){
	newheight+=1;
}

for(int i=0;i<20;i++){
	xCoordinate[i]=(int)xCoordinate[i]*xpercent;
	yCoordinate[i]=(int)yCoordinate[i]*ypercent;
		
}

// declare a destination IplImage object with correct size, depth and channels

//( cvSize((int)(((source->width)*1.013)) , (int)(((source->height)*1.06)) ),
      IplImage *destination = cvCreateImage( cvSize(newwidth,newheight),source->depth, source->nChannels );

//use cvResize to resize source to a destination image
cvResize(source, destination);

// save image with a name supplied with a second argument
      cvSaveImage( "res\\a.bmp", destination );

	  cvReleaseImage(&source);


}


void MyTabOne::resizePicDB(){
	
IplImage *source = cvLoadImage( path);

int fwidth=xCoordinate[1]-xCoordinate[0];
int fheight=yCoordinate[2]-yCoordinate[0];
double xpercent = 78.0/fwidth;
double ypercent=78.0/fheight;
int newwidth=(int)(((source->width)*xpercent));
int newheight=(int)(((source->height)*ypercent));

IplImage *destination = cvCreateImage( cvSize(newwidth,newheight),source->depth, source->nChannels );
cvResize(source, destination);

for(int i=0;i<3;i++){
	xCoordinate[i]=(int)xCoordinate[i]*xpercent;
	yCoordinate[i]=(int)yCoordinate[i]*ypercent;
		
}

int x0=xCoordinate[0]-45;
int y0=yCoordinate[0]-75;
	

cvSetImageROI(destination, cvRect(x0, y0, 165, 210));
 
IplImage *img2 = cvCreateImage(cvGetSize(destination), destination->depth,destination->nChannels);
 
/* copy subimage */
cvCopy(destination, img2, NULL);
 
/* always reset the Region of Interest */
cvResetImageROI(destination);
cvSaveImage( "db\\b.bmp", img2 );
cvReleaseImage(&source);
}

void MyTabOne::cropPic(){

	/* load image */
IplImage *img1 = cvLoadImage("res\\a.bmp", 1);
 
/* sets the Region of Interest
   Note that the rectangle area has to be __INSIDE__ the image */

int x0=xCoordinate[a+2]-115;
int y0=yCoordinate[a+2]-90;
	

cvSetImageROI(img1, cvRect(x0, y0, 240, 320));
 
/* create destination image
   Note that cvGetSize will return the width and the height of ROI */
IplImage *img2 = cvCreateImage(cvGetSize(img1), img1->depth,img1->nChannels);
 
/* copy subimage */
cvCopy(img1, img2, NULL);
 
/* always reset the Region of Interest */
cvResetImageROI(img1);

cvSaveImage( "res\\b.bmp", img2 );
//cvSaveImage( "Ageprogression\\2_murali.bmp", img2 );

for(int i=0;i<20;i++){
	xCoordinate[i]=(int)(xCoordinate[i]-x0);
	yCoordinate[i]=(int)(yCoordinate[i]-y0);
		
}
cvReleaseImage(&img1);

//adjust the texture
IplImage *source = cvLoadImage( "res\\b.bmp");
float u1=((float)(xCoordinate[0]+10))/(source->width);	float v1=(1+(float)((source->height-yCoordinate[0]+2))/(source->height));	changeVU1(u1,v1);
cvReleaseImage(&source);
changeXYZ(xCoordinate,yCoordinate,criticalPoints1);
}

void MyTabOne::OnBnClickedSetface()
{
	resizePic();
	cropPic();

	//float a=(source->width)*(0.821289-0.1818449)/(xCoordinate[1]-xCoordinate[0]);
	//float b=(source->width)*(0.1818449*xCoordinate[1]-0.821289*xCoordinate[0])/(xCoordinate[1]-xCoordinate[0]);

	//IplImage *source = cvLoadImage( "res\\b.bmp");	float u1=((float)xCoordinate[4])/(source->width);	float v1=(1+(float)(source->height-yCoordinate[4]+2)/(source->height));	changeVU1(u1,v1);
	
	LoadImage("res\\b.bmp",255,0,1);
	

	//changeVU(xCoordinate,yCoordinate,criticalPoints1);
	
}

void MyTabOne::resizePic1(){
	for (int i=0;i<3;i++){
		char file[50];
		sprintf(file, "db\\%d.png", (i+1));
		IplImage* ipl = cvLoadImage(file); 
		CvSize size = cvSize(240,320); 
		IplImage* tmpsize=cvCreateImage(size,ipl->depth, ipl->nChannels );	

		cvResize(ipl,tmpsize); 
		sprintf(file, "Ageprogression\\%d.bmp", (i+1));
		cvSaveImage( file, tmpsize );
		cvReleaseImage( &ipl); 

	}
}

void MyTabOne::cropPic1(){

	int x0=xCoordinate[0];
	int y0=yCoordinate[2];
	
	IplImage *img1 = cvLoadImage(savePath, 1);
cvSetImageROI(img1, cvRect(x0, y0,xCoordinate[1]-x0, yCoordinate[3]-y0));
 
/* create destination image
   Note that cvGetSize will return the width and the height of ROI */
IplImage *img2 = cvCreateImage(cvGetSize(img1), img1->depth,img1->nChannels);
 
/* copy subimage */
cvCopy(img1, img2, NULL);
 
/* always reset the Region of Interest */
cvResetImageROI(img1);

cvSaveImage( "db\\1.bmp", img2 );
cvReleaseImage(&img1);
}

