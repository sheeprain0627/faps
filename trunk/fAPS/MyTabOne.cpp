/*
* MyTabOne.cpp : implementation file
*/

#include "stdafx.h"
#include "MyTabOne.h"
#include "afxdialogex.h"

#include <cxcore.h>
#include "cv.h"
#include "cvisionDlg.h"
#include "highgui.h"
#include "cvaux.h"
#include <imgproc_c.h>
#include <fstream>
#include "Tdsloader.h"
#include "metrixCalculation.h"
#include "MyTabThree.h"
#include "detectFaceComponets.h"
#include "windows.h"
#include "Ageprogression.h"

//to avoid the VS2020 +matlab bug
#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif

#include "facewarp.h" /* MATLAB-generated header file */




using namespace std;
using namespace cv;

const int poiX1 = 25;
const int poiY1 = 25;
metrixCalculation aa;
detectFaceComponets facecomp;
//MyTabThree bb;
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
bool matlabCon=false;

IplImage* dbImage;


int criticalPoints1[] = {900,950,864,907,913,964,873,920,871,465,472,277,343,194,289};
int criticalPoints2[] = {913,964,873,920,900,950,864,907,871,472,465,289,343,194,277};
int a = 15;
CWinThread *pMatThread;


IplImage *selectedImg,*temp;
void releaseImg(IplImage *a,int x,int y);
IplImage* findImg(int x,int y);
int globalCoordinateX[100] ;
int globalCoordinateY[100] ;

int xCoordinate[23];
int yCoordinate[23];


int noOfControlPoints = 23;
int selPoint = -1;



IMPLEMENT_DYNAMIC(MyTabOne, CDialog)


/*!
	 constructor of tab1
*/
	MyTabOne::MyTabOne(CWnd* pParent /*=NULL*/)
	: CDialog(MyTabOne::IDD, pParent)
{
	//initialte the matlab library connection
	if( !matlabCon)
	{
		matlabCon=mclInitializeApplication(NULL,0);
		facewarpInitialize();
	}
}

/*!
	 destructor of tab 1
*/
MyTabOne::~MyTabOne()
{
}

/*!	 control handlers
	 \param pDX CDataExchange argument.
*/

void MyTabOne::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, m_picture, m_PicCtrl);
	DDX_Control(pDX, IDC_PROGRESSWarpWait, warpWait);
}


BEGIN_MESSAGE_MAP(MyTabOne, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &MyTabOne::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &MyTabOne::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_SetFace, &MyTabOne::OnBnClickedSetface)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()



/*!
	 mouse event handler for openCV
*/
void mouseHandler(int event, int x, int y, int flags, void *param) {

	switch(event) {

	case CV_EVENT_LBUTTONDOWN:
		pt = cvPoint(x, y);
		cvCircle(dbImage, pt, 1, CV_RGB(0,255,0), 1, 8,0);
		///cvShowImage(name, dbImage);
		globalCoordinateX[countDb] = x;
		globalCoordinateY[countDb] = y;
		countDb++;
		break;

	case CV_EVENT_RBUTTONDOWN:
		ofstream crifile;
		string savePath=path;
		savePath.replace(savePath.length()-4,4,".txt");

		//strtok(path,".");
		crifile.open (savePath);

		for (int i=0;i<23;i++){

			crifile << globalCoordinateX[i] << " " << globalCoordinateY[i] << "\n" ;			

		}

		crifile.close();

		break;


	}
}



void MyTabOne::OnBnClickedButton1()
{
	resetModel();		// reset the 3d model vith default alues
	warpWait.SetPos(0);
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




		//fasc points detection
		facecomp.loadFaceImages(img0[countImage]);
		CvPoint *featurePoints=facecomp.getFeaturePoints();
		for(int i=0;i<23;i++){
			xCoordinate[i]=featurePoints[i].x;
			yCoordinate[i]=featurePoints[i].y;
		}



		cvSetMouseCallback( name, mouseHandler, NULL );
		dbImage = cvLoadImage(path);
		showImage();	//defined inside the class

		
	}

}

/*!
	 thread to face wraping process
*/


UINT MyTabOne::MyThreadProc(LPVOID pParam)
{

	mlfFaceWarp();




	return 0;
}

void MyTabOne::OnBnClickedButton5()
{
	//histogram matching for Database

	MyTabThree three;
	int ageGrp = 80;
	int noOfImages = 4;	// no of Images in the each age group
	char filename[30];
	char filenamehist[30];
	Mat histEqu;
	ifstream images("db\\NoOfImage.txt", ios::in);
	int img[7];

	if(images == NULL) {
	}

	else {

		int width, height;
		width = xCoordinate[16] - xCoordinate[15];
		height =  yCoordinate[18] - yCoordinate[19];
		unsigned char* l_text;				



		for(int i = 3; i < 9; i++) {		// Age intervels

			images >> noOfImages; 
			ageGrp = 10 * i;
			for(int j =0; j < noOfImages; j++) {

				sprintf(filename, "Ageprogression\\%d\\%d.jpg", ageGrp,(j+1));


				Mat src;	//=cvLoadImage("Ageprogression\\2_output.bmp");			// template Image
				Mat dst;	//=cvLoadImage(filename);
				Mat src_mask;		//= cvLoadImage("Ageprogression\\whiteDB.bmp",0);	// threshold area
				Mat dst_mask;		// = cvLoadImage("Ageprogression\\whiteDB.bmp",0);

				IplImage* imgSrc = cvLoadImage("Ageprogression\\2_output.bmp",1);
				IplImage* imgDst = cvLoadImage(filename,1);

				l_text = (byte *) malloc(3*width*height);

				for(int z = 0; z<3*width*height;z++) {
					l_text[z] = 255;
				}
				//memset(l_text, 255, 3*width*height);


				IplImage* isrc_mask = cvCreateImage(cvSize(width, height), 8, 3);
				cvSetData(isrc_mask, l_text, width*3);


				IplImage* idst_mask = cvCreateImage(cvSize(width, height), 8, 3);
				cvSetData(idst_mask, l_text, width*3);


				cvSetImageROI(imgSrc, cvRect(xCoordinate[15], yCoordinate[19],width, height));
				cvSetImageROI(imgDst, cvRect(xCoordinate[15], yCoordinate[19],width, height));

				src = imgSrc;
				dst = imgDst;
				src_mask = isrc_mask;
				dst_mask = idst_mask;

				histEqu = three.histMatchRGB(dst,dst_mask,src,src_mask);		//histogram fitting function

				Ageprogression age;
				IplImage* srcImg = cvLoadImage(filename);

				IplImage* histMat = &(IplImage)histEqu;

				IplImage* dbImg = cvOverlayImage(srcImg, histMat, cvPoint(xCoordinate[15], yCoordinate[19]), cvScalar(0.5,0.5,0.5,0.5), cvScalar(0.5,0.5,0.5,0.5));

				sprintf(filenamehist, "Ageprogression\\%d\\hist%d.jpg", ageGrp,(j+1));
				cvSaveImage(filenamehist, dbImg);
				free(l_text);
				//imwrite(filenamehist, histEqu);									//storing the results
			}

		}
	}


}


/*!
method use in merge two images
\param src an IplImage as source image
\param overlay IplImage as the image which gets overlayed on source image 
\param location a CvPoint as giving location to overlay
\param S a CvScalar
\param D a CvScalar.
*/

IplImage* MyTabOne ::cvOverlayImage(IplImage* src, IplImage* overlay, CvPoint location, CvScalar S, CvScalar D)
{
	int x,y,i;

	for(x=0;x < overlay->width -10;x++)
	{
		if(x+location.x>=src->width) continue;
		for(y=0;y < overlay->height -10;y++)
		{
			if(y+location.y>=src->height) continue;
			CvScalar source = cvGet2D(src, y+location.y, x+location.x);
			CvScalar over = cvGet2D(overlay, y, x);
			CvScalar merged;
			for(i=0;i<4;i++)
				merged.val[i] = (S.val[i]*source.val[i]+D.val[i]*over.val[i]);
			cvSet2D(src, y+location.y, x+location.x, merged);
		}
	}

	return src;
}

int MyTabOne::getfwidth(){
	return (xCoordinate[a + 1] - xCoordinate[a + 0]);
}


int MyTabOne::getfHeight(){
	return (yCoordinate[a + 3] - yCoordinate[a + 2]);
}

/*!
	resize the picture for the setFace to database
*/

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

	for(int i = 0;i < 23;i++) {
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

/*!
	resize the picture for the database collection
*/

void MyTabOne::resizePicDB(){

	IplImage *source = cvLoadImage(path);

	int fwidth = globalCoordinateX[1] - globalCoordinateX[0];
	int fheight = globalCoordinateY[2] - globalCoordinateY[0];
	double xpercent = 78.0 / fwidth;
	double ypercent = 78.0 / fheight;
	int newwidth = (int)(((source->width) * xpercent));
	int newheight = (int)(((source->height) * ypercent));

	IplImage *destination = cvCreateImage( cvSize(newwidth,newheight),source->depth, source->nChannels );
	cvResize(source, destination);

	for(int i = 0;i < 3; i++) {
		globalCoordinateX[i] = (int)globalCoordinateX[i] * xpercent;
		globalCoordinateY[i] = (int)globalCoordinateY[i] * ypercent;

	}

	//165*210
	int x0=globalCoordinateX[0]-45;int y0=globalCoordinateY[0]-75;cvSetImageROI(destination, cvRect(x0, y0, 165, 210));


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

/*!
	crop the picture for the setFace
*/

void MyTabOne::cropPic(){

	/* load image */
	IplImage *img1 = cvLoadImage("res\\a.bmp", 1);

	/* sets the Region of Interest
	Note that the rectangle area has to be __INSIDE__ the image */


	//reduce the 18th point from all other points
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

	cvSaveImage("Ageprogression\\2_output.bmp", img2);
	//cvSaveImage( "Ageprogression\\2_output.bmp", img2 );


	ofstream crifile;

	//strtok(path,".");
	crifile.open ("Ageprogression\\base.txt");


	for(int i = 0;i < 23;i++) {
		xCoordinate[i] = (int)(xCoordinate[i] - x0);
		yCoordinate[i] = (int)(yCoordinate[i] - y0);
		crifile << xCoordinate[i] << " " << yCoordinate[i] << "\n" ;			
	}
	crifile.close();
	cvReleaseImage(&img1);

	//adjust the texture
	IplImage *source = cvLoadImage("Ageprogression\\2_output.bmp");
	float u1 = ((float)(xCoordinate[0] + 10)) / (source->width);	
	float v1  =(1 + (float)((source->height - yCoordinate[0] + 2)) / (source->height));

	changeVU1(u1, v1);
	cvReleaseImage(&source);
	changeXYZ(xCoordinate, yCoordinate, criticalPoints1);
}

/*!
crop the picture for the setFace
*/

void MyTabOne::OnBnClickedSetface()
{
	resizePic();
	cropPic();

	LoadImage("Ageprogression\\2_output.bmp", 255, 0, 1);


	float x = 8.6;
	CString selectedString = "selctVal";
	modify(x, selectedString);


	warpWait.SetRange(0, 200);


	// Make some progress...


	pMatThread=AfxBeginThread(MyThreadProc,this);


	for(int i=0;i<200;i++ ){	Sleep(100);	 warpWait.SetPos(i);}
	//ForSingleObject( pMatThread->m_hThread, INFINITE );
	//warpWait.SetPos(100);

}

/*!
	resize the picture for the setFace to database
*/
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

/*!
crop the picture 
*/
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

/*!
find the appropriate image to select
*/
IplImage* MyTabOne::findImg(int x,int y){
	IplImage *img = img0[countImage];

	for(int i = 0; i < noOfControlPoints; i++){
		if((x>=(xCoordinate[i]-2)) && (x<=(xCoordinate[i]+2 ))&& (y>=(yCoordinate[i]-2 ))&& (y<=(yCoordinate[i]+2 ))){
			selPoint=i;
			break;
		}

	}

	for(int j=0;j < noOfControlPoints;j++){
		if(j != selPoint){
			img = cvCloneImage(img);
			cvRectangle(img, 
				cvPoint(xCoordinate[j] -1, yCoordinate[j] - 1), 
				cvPoint(xCoordinate[j] , yCoordinate[j] ), 
				cvScalar(0, 0,  255, 0), 2, 8, 0);
		}
	}
	return img;
}

/*!
release the selected point from image
\param a as IplIamge as selected image
\param x as int of location
\param y as int of location
*/
void MyTabOne::releaseImg(IplImage *a,int x,int y){
	IplImage *img1 = cvCloneImage(a);
	cvRectangle(img1, 
		cvPoint(x-1, y-1 ), 
		cvPoint(x , y ), 
		cvScalar(0, 0, 255, 0), 2, 8, 0);

	cvSaveImage(savePath, img1);
	CImage img;
	img.Load(savePath);
	m_PicCtrl.SetBitmap((HBITMAP)img.Detach());

	xCoordinate[selPoint]=x;
	yCoordinate[selPoint]=y;
	cvReleaseImage(&img1);
	selPoint=-1;
}

/*!
show image in the picture control after move each point
*/

void MyTabOne::showImage(){
	IplImage *img2 = img0[countImage];

	for(int j=0;j<noOfControlPoints;j++){		
		img2 = cvCloneImage(img2);
		cvRectangle(img2, 
			cvPoint(xCoordinate[j] - 1, yCoordinate[j] - 1), 
			cvPoint(xCoordinate[j] , yCoordinate[j] ), 
			cvScalar(0, 0, 255, 0), 2, 8, 0);
	}

	cvSaveImage(savePath, img2);

	CImage img;
	img.Load(savePath);
	m_PicCtrl.SetBitmap((HBITMAP)img.Detach());

	cvReleaseImage(&img2);
}

/*!
to handle OnMouseMove event in dialogs
\param nFlags as UINT
\param point as CPoint represetns the x,y points of pane
*/


void MyTabOne::OnMouseMove(UINT nFlags, CPoint point)
{
	
	if((selPoint!=-1)&&(selectedImg!=NULL)){			
		int poiX, poiY;
		int X, Y;
		X = point.x;
		Y = point.y;

		pt = cvPoint(X - 310, Y - 188);


		if(load && (selectedImg != NULL)) {

			temp = cvCloneImage(selectedImg);
			cvRectangle(temp, 
				cvPoint(pt.x - 1,pt.y - 1), 
				cvPoint(pt.x + 1, pt.y + 1), 
				cvScalar(0, 0,  0,255), 2, 8, 0);
			/* initialize font and add text */
			char buffer[3];
			itoa(selPoint+1, buffer, 10);		
			CvFont font;
			cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1.0, 1.0, 0, 1, CV_AA);
			cvPutText(temp,buffer ,cvPoint(pt.x+2,pt.y+2), &font, cvScalar(255, 255, 255, 0)); 

			//cvShowImage("image", temp);
			//cvCircle(temp, pt, 1, CV_RGB(0, 255, 0), -1, 8,0);
			cvSaveImage(savePath, temp);


			CImage img;
			img.Load(savePath);
			m_PicCtrl.SetBitmap((HBITMAP)img.Detach());
		}
		CDialog::OnMouseMove(nFlags, point);
	}
}

/*!
to handle OnLButtonDown event in dialogs
\param nFlags as UINT
\param point as CPoint represetns the x,y points of pane
*/
void MyTabOne::OnLButtonDown(UINT nFlags, CPoint point)
{
	int poiX, poiY;
	int X, Y;
	X = point.x;
	Y = point.y;

	pt = cvPoint(X - 310, Y - 188);

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

/*!
to handle OnLButtonUp event in dialogs
\param nFlags as UINT
\param point as CPoint represetns the x,y points of pane
*/

void MyTabOne::OnLButtonUp(UINT nFlags, CPoint point)
{
	if((selectedImg!=NULL)&&selPoint!=-1){
		int X, Y;
		X = point.x;
		Y = point.y;

		pt = cvPoint(X - 310, Y - 188);

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

/*!
getting X critical points
\return int as x coordiante
*/
int* getXCriticalPoints(){
	return xCoordinate;
}

/*!
getting Y critical points
\return int as y coordinate
*/

int* getYCriticalPoints(){
	return yCoordinate;
}

/*!
histogram equalization
*/
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

	cvWaitKey();

	cvReleaseImage( &img );
	cvReleaseImage( &out );
}


/*!
to change background color
*/

BOOL MyTabOne::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	SBitdraw(pDC, IDB_TABBACKGRND, 1);
	return true;	//CDialog::OnEraseBkgnd(pDC);
}

/*!
to change background color of each controls
\param pDC as CDC
\param nIDResource contrl ID of the item
\param i as position of the backgrnd
*/

bool MyTabOne::SBitdraw(CDC *pDC, UINT nIDResource, int i) 
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


/*!
OndrawItem handler to change the color of buttons
\param nIDCtl as contrl ID
\param lpDrawItemStruct
*/

void MyTabOne::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if((nIDCtl==IDC_BUTTON5) || (nIDCtl==IDC_SetFace) || (nIDCtl==IDC_BUTTON1) || (nIDCtl==IDC_BUTTON2) || (nIDCtl==IDC_BUTTON4) )         //checking for the button 

	{
		CDC dc;
		RECT rect;
		dc.Attach(lpDrawItemStruct ->hDC);   // Get the Button DC to CDC


		rect = lpDrawItemStruct->rcItem;     //Store the Button rect to our local rect.


		dc.Draw3dRect(&rect,RGB(255,255,255),RGB(0,0,0)); 

		dc.FillSolidRect(&rect,RGB(134,27,9));//Here you can define the required color to appear on the Button.


		UINT state=lpDrawItemStruct->itemState;  //This defines the state of the Push button either pressed or not. 


		if((state & ODS_SELECTED))
		{
			dc.DrawEdge(&rect,EDGE_SUNKEN,BF_RECT);

		}
		else
		{
			dc.DrawEdge(&rect,EDGE_RAISED,BF_RECT);
		}

		dc.SetBkColor(RGB(134,27,9));   //Setting the Text Background color

		dc.SetTextColor(RGB(255,255,255));     //Setting the Text Color
		//dc.Set



		TCHAR buffer[MAX_PATH];           //To store the Caption of the button.

		ZeroMemory(buffer,MAX_PATH );     //Intializing the buffer to zero

		::GetWindowText(lpDrawItemStruct->hwndItem,buffer,MAX_PATH); //Get the Caption of Button Window 


		dc.DrawText(buffer,&rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);//Redraw the  Caption of Button Window 


		dc.Detach();  // Detach the Button DC

	}

	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


