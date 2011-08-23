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
#include "metrixCalculation.h"


using namespace std;
using namespace cv;

const int poiX1 = 25;
const int poiY1 = 25;
metrixCalculation aa;
int countfile=0;
CvPoint pt;
IplImage* img0[100];
ofstream myfile("res\\out.txt");//, ofstream::binary);
CString path;
const char* name = "img";
const char* savePath = "res\\pil.bmp";
int countImage;
int countDb;
bool load = false;

IplImage* dbImage;
//count = 1;
//int globalCoordinateX[100];
//int globalCoordinateY[100];
int criticalPoints1[] = {900,950,864,907,913,964,873,920,871,465,472,277,343,194,289};
int criticalPoints2[] = {913,964,873,920,900,950,864,907,871,472,465,289,343,194,277};
int a = 15;


IplImage *selectedImg,*temp;
void releaseImg(IplImage *a,int x,int y);
IplImage* findImg(int x,int y);
int globalCoordinateX[]={59, 78, 98, 79, 118, 142, 97, 135, 152, 172, 154, 85, 118, 147, 118, 35, 117, 187, 119 };
int globalCoordinateY[]={119,110, 124, 130, 112, 170, 169, 122, 108, 116, 129, 198, 193, 200, 212, 118, 85, 109, 248 };
int noOfControlPoints = 19;
int selPoint = -1;

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
	ON_BN_CLICKED(IDC_BUTTON5, &MyTabOne::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_SetFace, &MyTabOne::OnBnClickedSetface)
	ON_WM_MOUSEMOVE()
//	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



/*void MyTabOne::OnLButtonDown(UINT nFlags, CPoint point)
{
		
	int X, Y;
	X = point.x;
	Y = point.y;

	pt = cvPoint(X - 315, Y - 66);

	CString str1;
	str1.Format("%d", X);

	CString str2;
	str2.Format("%d", Y);
	//MessageBox("X:" + str1+  "Y:" + str2,"Right",MB_ICONSTOP|MB_OK);
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON) {
		MessageBox("X:" + str1+  "Y:" + str2,"aaaaaaaaaaaa",MB_ICONSTOP|MB_OK);
	if(selectedImg!=NULL){
				releaseImg(selectedImg,pt.x,pt.y);
					selectedImg=NULL;
			}
	}
	
	/*int poiX, poiY;
	int X, Y;
	X = point.x;
	Y = point.y;

	pt = cvPoint(X - 315, Y - 66);
	
	CString str1;
	str1.Format("%d", X);

	CString str2;
	str2.Format("%d", Y);
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON) {

		if(load == true ) {


			//MessageBox("X:" + str1+  "Y:" + str2,"aaaaaaaaaaaa",MB_ICONSTOP|MB_OK);
			countImage++;
			//MessageBox(NULL,"X:" + str1 +"  Y:"+ str2 , "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);
			
			img0[countImage] = cvCloneImage(img0[countImage - 1]);
		
			cvCircle(img0[countImage], pt, 1, CV_RGB(0, 255, 0), -1, 8,0);

			cvSaveImage(savePath, img0[countImage]);

			CImage img;
			img.Load(savePath);
			m_PicCtrl.SetBitmap((HBITMAP)img.Detach());
			xCoordinate[countImage - 1] = pt.x;
			yCoordinate[countImage - 1] = pt.y;

			globalCoordinateX[countImage - 1] = pt.x;
			globalCoordinateY[countImage - 1] = pt.y;

			if(countImage >= 4 && countImage < 8)
				SetDlgItemTextA(IDC_EDIT1, "Please Click RIGHT EYE critical points");
				//MessageBox("Please Click RIGHT EYE critical points!!!!!!", "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);

			if(countImage < 11 && countImage >= 8)
				SetDlgItemTextA(IDC_EDIT1, "Please Click NOSE critical points");
				//MessageBox("Please Click NOSE critical points!!!!!!", "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);

			if(countImage >= 11)
				SetDlgItemTextA(IDC_EDIT1, "Please Click MOUTH critical points");
				//MessageBox("Please Click MOUTH critical points!!!!!!", "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);

		
			if(countImage == 16) {
						
			}

		}
	}	

	
  	if (nFlags == WM_LBUTTONDOWN) {
		MessageBox("bbbbbb","Sorry, this is not a 24 Bit Bitmap.",MB_ICONSTOP|MB_OK);
	}
	
	CWnd::OnLButtonDown(nFlags, point);

}
*/

void mouseHandler(int event, int x, int y, int flags, void *param) {

        switch(event) {
        
        case CV_EVENT_LBUTTONDOWN:
                pt = cvPoint(x, y);
                cvCircle(dbImage, pt, 1, CV_RGB(0,255,0), 1, 8,0);
                cvShowImage(name, dbImage);
                globalCoordinateX[countDb] = x;
                globalCoordinateY[countDb] = y;
                countDb++;
                break;
        }
}



void MyTabOne::OnBnClickedButton1()
{
	this -> DragAcceptFiles(true);

	CFileDialog dlg(TRUE, _T("*.bmp"), NULL,
	OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
	_T("image files (*.bmp; *.jpg) |*.bmp;*.jpg|All Files (*.*)|*.*||"),NULL);
 
	dlg.m_ofn.lpstrTitle = _T("Open Image");
 
	if (dlg.DoModal() == IDOK) {
 
		
		path = dlg.GetPathName();
		
		load = true;
        countImage = 0;
        countDb = 0;
        img0[countImage] = cvLoadImage(path);             // load the image

                
        cvNamedWindow(name, CV_WINDOW_AUTOSIZE);

        cvSetMouseCallback( name, mouseHandler, NULL );
        dbImage = cvLoadImage(path);
        cvShowImage(name, dbImage);

		cvNamedWindow("image", CV_WINDOW_AUTOSIZE);
	
		cvShowImage("image", img0[countImage]);
	
		showImage();	//defined inside the class
		
		LoadImage(savePath, 255, 0, 1); //sent the pathe of image to opengl window    //ajith
					
	}
		
}


void MyTabOne::OnBnClickedButton2()
{
	countImage -= 1;
	cvSaveImage(savePath, img0[countImage]);
	
	CImage img;
	img.Load(savePath);
	m_PicCtrl.SetBitmap((HBITMAP)img.Detach());
	
	if(countImage < 5)
		SetDlgItemTextA(IDC_EDIT1, "Please Click LEFT EYE critical points");
	
	if(countImage >= 5 && countImage < 9)
		SetDlgItemTextA(IDC_EDIT1, "Please Click RIGHT EYE critical points");
			//MessageBox("Please Click RIGHT EYE critical points!!!!!!", "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);

	if(countImage < 12 && countImage >= 9)
		SetDlgItemTextA(IDC_EDIT1, "Please Click NOSE critical points");
		//MessageBox("Please Click NOSE critical points!!!!!!", "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);

	if(countImage >= 12)
		SetDlgItemTextA(IDC_EDIT1, "Please Click MOUTH critical points");
		//MessageBox("Please Click MOUTH critical points!!!!!!", "Click Critical Points Selection",  MB_OK | MB_ICONEXCLAMATION);

	
	
}


void MyTabOne::OnBnClickedButton3()
{
	
	
}


void MyTabOne::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
}


void MyTabOne::OnBnClickedButton5()
{
	IplImage *dst=cvLoadImage("res//pil111.bmp", CV_LOAD_IMAGE_COLOR );
	IplImage *src=cvLoadImage("res//pil111.bmp", CV_LOAD_IMAGE_COLOR );
	//test1234();
	//HistogramEqualization();
	aa.CalFundermentalMatrix(src,dst);
	//resizePicDB();
	//resizePic1();

	//cropPic1();

	//LoadImage(savePath,255,0,1);
	
	//IplImage *source = cvLoadImage( "res\\b.bmp");	float u1=((float)xCoordinate[a+4])/(source->width);	float v1=(1+(float)(source->height-yCoordinate[a+4]+2)/(source->height));	changeVU1(u1,v1);
	
}

int MyTabOne::getfwidth(){
	return (xCoordinate[a + 1] - xCoordinate[a + 0]);
}


int MyTabOne::getfHeight(){
	return (yCoordinate[a + 3] - yCoordinate[a + 2]);
}

void MyTabOne::resizePic(){
		// Create an IplImage object *image 
	IplImage *source = cvLoadImage( path);
	// Here we retrieve a percentage value to a integer
	int fwidth = getfwidth();
	int fheight = getfHeight();
	double xpercent = 165.0 / fwidth;
	double ypercent = 155.0 / fheight;
	int newwidth = (int)(((source->width)*xpercent));
	int newheight = (int)(((source->height)*ypercent));

	if(newwidth%2 != 0) {
		newwidth += 1;
	}

	if(newheight%2 != 0) {
		newheight += 1;
	}

	for(int i = 0;i < 20;i++) {
		xCoordinate[i] = (int)xCoordinate[i] * xpercent;
		yCoordinate[i] = (int)yCoordinate[i] * ypercent;
		
	}

	// declare a destination IplImage object with correct size, depth and channels

	//( cvSize((int)(((source->width)*1.013)) , (int)(((source->height)*1.06)) ),
	IplImage *destination = cvCreateImage( cvSize(newwidth, newheight), source->depth, source->nChannels);

	//use cvResize to resize source to a destination image
	cvResize(source, destination);

	// save image with a name supplied with a second argument
	cvSaveImage("res\\a.bmp", destination );

	cvReleaseImage(&source);

}


void MyTabOne::resizePicDB(){
	
	IplImage *source = cvLoadImage(path);

	int fwidth = xCoordinate[1] - xCoordinate[0];
	int fheight = yCoordinate[2] - yCoordinate[0];
	double xpercent = 78.0 / fwidth;
	double ypercent = 78.0 / fheight;
	int newwidth = (int)(((source->width) * xpercent));
	int newheight = (int)(((source->height) * ypercent));

	IplImage *destination = cvCreateImage( cvSize(newwidth,newheight),source->depth, source->nChannels );
	cvResize(source, destination);

	for(int i = 0;i < 3; i++) {
		xCoordinate[i] = (int)xCoordinate[i] * xpercent;
		yCoordinate[i] = (int)yCoordinate[i] * ypercent;
		
	}

	//165*210
	int x0=xCoordinate[0]-45;int y0=yCoordinate[0]-75;cvSetImageROI(destination, cvRect(x0, y0, 165, 210));


	//240*320
	//int x0=xCoordinate[0]-78;int y0=yCoordinate[0]-120;cvSetImageROI(destination, cvRect(x0, y0, 240, 320));

	IplImage *img2 = cvCreateImage(cvGetSize(destination), destination->depth, destination->nChannels);
 
	/* copy subimage */
	cvCopy(destination, img2, NULL);
 
	/* always reset the Region of Interest */
	cvResetImageROI(destination);
	countfile++;
	stringstream  fname;
	fname << "Ageprogression\\" << countfile << ".bmp";
	cvSaveImage( fname.str().c_str(), img2 );
	cvReleaseImage(&source);
}

void MyTabOne::cropPic(){

	/* load image */
	IplImage *img1 = cvLoadImage("res\\a.bmp", 1);
 
	/* sets the Region of Interest
	   Note that the rectangle area has to be __INSIDE__ the image */

	int x0 = xCoordinate[a+2] - 115;
	int y0 = yCoordinate[a+2] - 90;
	

	cvSetImageROI(img1, cvRect(x0, y0, 240, 320));
 
	/* create destination image
	   Note that cvGetSize will return the width and the height of ROI */
	IplImage *img2 = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);
 
	/* copy subimage */
	cvCopy(img1, img2, NULL);
 
	/* always reset the Region of Interest */
	cvResetImageROI(img1);

	cvSaveImage("res\\b.bmp", img2);
	//cvSaveImage( "Ageprogression\\2_murali.bmp", img2 );

	for(int i = 0;i < 20;i++) {
		xCoordinate[i] = (int)(xCoordinate[i] - x0);
		yCoordinate[i] = (int)(yCoordinate[i] - y0);
		
	}
	cvReleaseImage(&img1);

	//adjust the texture
	IplImage *source = cvLoadImage("res\\b.bmp");
	float u1 = ((float)(xCoordinate[0] + 10)) / (source->width);	
	float v1  =(1 + (float)((source->height - yCoordinate[0] + 2)) / (source->height));

	changeVU1(u1, v1);
	cvReleaseImage(&source);
	changeXYZ(xCoordinate, yCoordinate, criticalPoints1);
}


void MyTabOne::OnBnClickedSetface()
{
	resizePic();
	cropPic();

	//float a=(source->width)*(0.821289-0.1818449)/(xCoordinate[1]-xCoordinate[0]);
	//float b=(source->width)*(0.1818449*xCoordinate[1]-0.821289*xCoordinate[0])/(xCoordinate[1]-xCoordinate[0]);

	//IplImage *source = cvLoadImage( "res\\b.bmp");	float u1=((float)xCoordinate[4])/(source->width);	float v1=(1+(float)(source->height-yCoordinate[4]+2)/(source->height));	changeVU1(u1,v1);
	
	LoadImage("res\\b.bmp", 255, 0, 1);
	float x = 8.6;
	CString selectedString = "selctVal";
	modify(x, selectedString);
	//changeVU(xCoordinate,yCoordinate,criticalPoints1);
	//aa.WritePixelsToFile(cvLoadImage("res\\a.bmp", 1),"pixelVal.txt");
//	aa.CalFundermentalMatrix();
}

void MyTabOne::resizePic1(){

	for (int i = 0;i < 3;i++) {

		char file[50];
		sprintf(file, "db\\%d.png", (i+1));
		IplImage* ipl = cvLoadImage(file); 
		CvSize size = cvSize(240,320); 
		IplImage* tmpsize = cvCreateImage(size, ipl->depth, ipl->nChannels);	

		cvResize(ipl, tmpsize); 
		sprintf(file, "Ageprogression\\%d.bmp", (i + 1));
		cvSaveImage( file, tmpsize );
		cvReleaseImage(&ipl); 

	}
}

void MyTabOne::cropPic1(){

	int x0 = xCoordinate[0];
	int y0 = yCoordinate[2];
	
	IplImage *img1 = cvLoadImage(savePath, 1);
	cvSetImageROI(img1, cvRect(x0, y0,xCoordinate[1] - x0, yCoordinate[3] - y0));
 
	/* create destination image
	   Note that cvGetSize will return the width and the height of ROI */
	IplImage *img2 = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels);
 
	/* copy subimage */
	cvCopy(img1, img2, NULL);
 
	/* always reset the Region of Interest */
	cvResetImageROI(img1);

	cvSaveImage( "db\\1.bmp", img2);
	cvReleaseImage(&img1);
}


IplImage* MyTabOne::findImg(int x,int y){
	IplImage *img = img0[countImage];
	
	for(int i = 0; i < noOfControlPoints; i++){
		if((x>=(globalCoordinateX[i]-2)) && (x<=(globalCoordinateX[i]+2 ))&& (y<=(globalCoordinateY[i]+2 ))&& (y<=(globalCoordinateY[i]+2 ))){
			selPoint=i;
			break;
		}

	}

	for(int j=0;j < noOfControlPoints;j++){
		if(j != selPoint){
			img = cvCloneImage(img);
			cvRectangle(img, 
						cvPoint(globalCoordinateX[j] -1, globalCoordinateY[j] - 1), 
						cvPoint(globalCoordinateX[j] , globalCoordinateY[j] ), 
						cvScalar(0, 0,  255, 0), 2, 8, 0);
		}
	}
	return img;
}

void MyTabOne::releaseImg(IplImage *a,int x,int y){
	IplImage *img1 = cvCloneImage(a);
			cvRectangle(img1, 
						cvPoint(x-1, y-1 ), 
						cvPoint(x + 1, y + 1), 
						cvScalar(0, 0, 255, 0), 2, 8, 0);

		cvSaveImage(savePath, img1);
		CImage img;
		img.Load(savePath);
		m_PicCtrl.SetBitmap((HBITMAP)img.Detach());

		globalCoordinateX[selPoint]=x;
		globalCoordinateY[selPoint]=y;
		cvReleaseImage(&img1);
		selPoint=-1;
}


void MyTabOne::showImage(){
	IplImage *img2 = img0[countImage];

	for(int j=0;j<noOfControlPoints;j++){		
		img2 = cvCloneImage(img2);
			cvRectangle(img2, 
						cvPoint(globalCoordinateX[j] - 1, globalCoordinateY[j] - 1), 
						cvPoint(globalCoordinateX[j] , globalCoordinateY[j] ), 
						cvScalar(0, 0, 255, 0), 2, 8, 0);
		}

		cvSaveImage(savePath, img2);

		CImage img;
		img.Load(savePath);
		m_PicCtrl.SetBitmap((HBITMAP)img.Detach());

		//SetDlgItemTextA(IDC_EDIT1, "Please Click LEFT EYE critical points");
	cvShowImage("image", img2);
	cvReleaseImage(&img2);
}



void MyTabOne::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if((selPoint!=-1)&&(selectedImg!=NULL)){			
	int poiX, poiY;
	int X, Y;
	X = point.x;
	Y = point.y;

	pt = cvPoint(X - 315, Y - 66);

	
	if(load && (selectedImg != NULL)) {

	temp = cvCloneImage(selectedImg);
			cvRectangle(temp, 
						cvPoint(pt.x - 1,pt.y - 1), 
						cvPoint(pt.x + 1, pt.y + 1), 
						cvScalar(0, 0,  255,0), 2, 8, 0);
			cvShowImage("image", temp); 
			cvSaveImage(savePath, temp);

							
		CImage img;
		img.Load(savePath);
		m_PicCtrl.SetBitmap((HBITMAP)img.Detach());
	}
	CDialog::OnMouseMove(nFlags, point);
	}
}


void MyTabOne::OnLButtonDown(UINT nFlags, CPoint point)
{
	int poiX, poiY;
	int X, Y;
	X = point.x;
	Y = point.y;

	pt = cvPoint(X - 315, Y - 66);

	CString str1;
	str1.Format("%d", X);

	CString str2;
	str2.Format("%d", Y);
	
	//MessageBox("X:" + str1+  "Y:" + str2,"Right",MB_ICONSTOP|MB_OK);


	if(((nFlags & MK_LBUTTON) == MK_LBUTTON) && load) {
		//MessageBox("X:" + str1+  "Y:" + str2,"Right",MB_ICONSTOP|MB_OK);
	
	selectedImg=findImg( pt.x, pt.y);
	}


	CDialog::OnLButtonDown(nFlags, point);
}


void MyTabOne::OnLButtonUp(UINT nFlags, CPoint point)
{
	if((selectedImg!=NULL)&&selPoint!=-1){
	int X, Y;
	X = point.x;
	Y = point.y;

	pt = cvPoint(X - 315, Y - 66);

	CString str1;
	str1.Format("%d", X);

	CString str2;
	str2.Format("%d", Y);

	if( load) {
	
	if(selectedImg != NULL){
				releaseImg(selectedImg, pt.x, pt.y);
					selectedImg = NULL;
			}
	}
	

	CDialog::OnLButtonUp(nFlags, point);
}
}

int* getXCriticalPoints(){
	return globalCoordinateX;
}

int* getYCriticalPoints(){
	return globalCoordinateY;
}

void MyTabOne::HistogramEqualization(){
const char* name = "Histogram Equalization";
	IplImage *img = cvLoadImage("res//Untitled.bmp", 3);
	IplImage* out = cvCreateImage( cvGetSize(img), 8, 3 );

	
	IplImage *imgRed = cvCreateImage(cvGetSize(img), 8, 1);
    IplImage *imgGreen = cvCreateImage(cvGetSize(img), 8, 1);
    IplImage *imgBlue = cvCreateImage(cvGetSize(img), 8, 1);
    cvSplit(img, imgRed, imgGreen, imgBlue, NULL);
	


	IplImage *imgRed1 = cvCreateImage(cvGetSize(img), 8, 1);
    IplImage *imgGreen1 = cvCreateImage(cvGetSize(img), 8, 1);
    IplImage *imgBlue1 = cvCreateImage(cvGetSize(img), 8, 1);

	cvEqualizeHist( imgRed, imgRed1 );
	cvEqualizeHist( imgGreen, imgGreen1 );
	cvEqualizeHist( imgBlue, imgBlue1 );

	cvMerge(imgRed1, imgGreen1, imgBlue1, NULL, out);

	// Show original
	cvNamedWindow( "Original", 1) ;
	cvShowImage( "Original", img );

	// Perform histogram equalization
	//cvEqualizeHist( img, out );

	// Show histogram equalized
	cvNamedWindow( name, 1) ;
	cvShowImage( name, out );

	cvWaitKey();

	cvReleaseImage( &img );
	cvReleaseImage( &out );
}

void MyTabOne::test123(){
int point_count = 100;
CvMat* points1;
CvMat* points2;
CvMat* status;
CvMat* fundamental_matrix;
//points1=(byte *) malloc(200);
points1 = cvCreateMat(1,point_count,CV_64FC1);
points2 = cvCreateMat(1,point_count,CV_64FC1);
status = cvCreateMat(1,point_count,CV_64FC1);

/* Fill the points here … */
for(int i = 0; i < point_count; i++ )
{
	cvmSet(points1,0,i,i+1);
	cvmSet(points1,0,i,i+2);
//points1->data.db[i*2] = 1;
//points1->data.db[i*2+1] = 2;
//points2->data.db[i*2] = 3;
//points2->data.db[i*2+1] =4 ;
}

fundamental_matrix = cvCreateMat(1,point_count,CV_64FC1);
int q=4;
int fm_count = cvFindFundamentalMat( points1,points2,fundamental_matrix,CV_FM_RANSAC,1.0,0.99,status );

}

void MyTabOne::test1234(){


CvMat* mmat = cvCreateMat(3,3,CV_32FC1);
    //CvPoint2D32f* c1 = (&cvPoint2D32f(43,18), &cvPoint2D32f(280,40), &cvPoint2D32f(19,223), &cvPoint2D32f(300,200));
    //CvPoint2D32f* c2 = (&cvPoint2D32f(0,0), &cvPoint2D32f(300,0), &cvPoint2D32f(0,225), &cvPoint2D32f(300,225));

CvPoint2D32f *c1 = new CvPoint2D32f[4];
CvPoint2D32f *c2 = new CvPoint2D32f[4];
/*
int trg_img_cordinate_x[19]={65.0,80.0,80.0,102.0,132.0,147.0,149.0,165.0,116.0,101.0,132,88,119,117,144,33,199,117,117};
int trg_img_cordinate_y[19]={127.0,117.0,131.0,127.0,127.0,113.0,130.0,124.0,121.0,171.0,169,201,193,210,201,142,142,102,253};
//int db_img_cordinate_x[19]={62.0,79.0,80.0,104.0,136.0,156.0,157.0,173.0,120.0,99.0,144.0,87,120,120,148,35,196,119,117};
//int db_img_cordinate_y[19]={121.0,111.0,130.0,127.0,124.0,110.0,129.0,120.0,112.0,171.0,172.0,202,191,215,198,136,140,88,256};
int db_img_cordinate_x[19]={65.0,80.0,80.0,102.0,132.0,147.0,149.0,165.0,116.0,101.0,132,88,119,117,144,33,199,117,117};
int db_img_cordinate_y[19]={127.0,117.0,131.0,127.0,127.0,113.0,130.0,124.0,121.0,171.0,169,201,193,210,201,142,142,102,253};
*/
int trg_img_cordinate_x[4]={0,0,240,240};
int trg_img_cordinate_y[4]={0,320,0,320};
//int db_img_cordinate_x[19]={62.0,79.0,80.0,104.0,136.0,156.0,157.0,173.0,120.0,99.0,144.0,87,120,120,148,35,196,119,117};
//int db_img_cordinate_y[19]={121.0,111.0,130.0,127.0,124.0,110.0,129.0,120.0,112.0,171.0,172.0,202,191,215,198,136,140,88,256};
int db_img_cordinate_x[4]={0,0,240,240};
int db_img_cordinate_y[4]={0,320,100,200};




/* Fill the points here ... */

for( int i = 0; i < 4; i++ )
{

	c1[i].x = trg_img_cordinate_x[i];   c1[i].y = trg_img_cordinate_y[i];
	c2[i].x = db_img_cordinate_x[i];   c2[i].y = db_img_cordinate_y[i];


}



    mmat = cvGetPerspectiveTransform(c1, c2, mmat);
	IplImage *src=cvLoadImage("res//pil111.bmp", 1);
	int a=-1;
	for (int i = 0; i < 3; i ++)
{
for (int j = 0; j < 3; j ++)
{
	//a=cvmGet(points1, i, j);
 a=cvmGet(mmat, i, j);
}
}

	IplImage *img_out= cvCloneImage(src);
    cvWarpPerspective(src, img_out, mmat);

	cvNamedWindow("ori",1);
cvShowImage("ori",src);

	cvNamedWindow("wrppedImg",1);
cvShowImage("wrppedImg",img_out);


}