// MyTabThree.cpp : implementation file
//

#include "stdafx.h"
#include "MyTabThree.h"
#include "afxdialogex.h"
#include "Tdsloader.h"
#include "Ageprogression.h"
#include <cxcore.h>
#include "cv.h"
#include <math.h>



// MyTabThree dialog
Ageprogression age;
IMPLEMENT_DYNAMIC(MyTabThree, CDialog)

MyTabThree::MyTabThree(CWnd* pParent /*=NULL*/)
	: CDialog(MyTabThree::IDD, pParent)
{

}

MyTabThree::~MyTabThree()
{
}

void MyTabThree::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AgeBar, agebar);
}


BEGIN_MESSAGE_MAP(MyTabThree, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &MyTabThree::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_Pick, &MyTabThree::OnBnClickedPick)
	ON_BN_CLICKED(IDC_LoadTexture, &MyTabThree::OnBnClickedLoadtexture)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_AgeBar, &MyTabThree::OnNMCustomdrawAgebar)
	ON_EN_CHANGE(IDC_EDIT1, &MyTabThree::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &MyTabThree::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &MyTabThree::OnBnClickedButton3)
END_MESSAGE_MAP()


// MyTabThree message handlers


void MyTabThree::OnBnClickedButton1()
{
float p=age.getSigma();
age.texureEnhancePrototype(p);
}


void MyTabThree::OnBnClickedPick()
{
	drawBox();
	// TODO: Add your control notification handler code here
}


void MyTabThree::OnBnClickedLoadtexture()
{
	this->DragAcceptFiles(true);
	CFileDialog dlg(TRUE, _T("*.bmp"), NULL,
	OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
	_T("image files (*.bmp; *.jpg) |*.bmp;*.jpg|All Files (*.*)|*.*||"),NULL);
 
	dlg.m_ofn.lpstrTitle= _T("Open Image");
 
	if (dlg.DoModal() == IDOK) { 
		CString path= dlg.GetPathName();
		LoadImage2(path,255,0,0);		
	}
}


void MyTabThree::OnNMCustomdrawAgebar(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	int curret =agebar.GetPos();
	
	float x=(float)(curret-20)/30;
	changeContrast(x);
	
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void MyTabThree::OnEnChangeEdit1()
{

	CString s;
	GetDlgItemText(IDC_EDIT3, s);
	float p = atof( s );
	age.setSigma(p);
	
}


void MyTabThree::OnBnClickedButton2()
{
		IplImage* img11;
		IplImage* img_new;
		
		img_new = cvLoadImage("Ageprogression\\1.bmp");
		cvNamedWindow("Lap",1);
		//img11 = cvCreateImage(cvSize(101,32),8 , 3);
		
		show_histogram("Lap", img_new, "red");
		//cvSetData(img11,l_text ,303);
		//cvShowImage("Lap", img11);	
		
		cvWaitKey();

	
	// TODO: Add your control notification handler code here
}





void MyTabThree::show_histogram(char* window_title, IplImage* src, char* channel_name)
{
  IplImage* img, * canvas;
  int       bins = 256;
  int       hist[256];
  double    scale;
  int       i, j, channel, max = 0;

  CvScalar   colors[] = { CV_RGB(0,0,255), CV_RGB(0,255,0),
                          CV_RGB(255,0,0), CV_RGB(0,0,0) };

  channel = strcmp(channel_name, "blue")  == 0 ? 0
          : strcmp(channel_name, "green") == 0 ? 1
          : strcmp(channel_name, "red")   == 0 ? 2
          : strcmp(channel_name, "gray")  == 0 ? 3 : 0;

  if (src->nChannels == 3 && channel == 3)
  {
    img = cvCreateImage(cvGetSize(src), 8, 1);
    cvCvtColor(src, img, CV_BGR2GRAY);
  }
  else if (channel > src->nChannels)
    return;
  else
    img = cvCloneImage(src);

  canvas = cvCreateImage(cvSize(256, 125), IPL_DEPTH_8U, 3);
  cvSet(canvas, CV_RGB(255,255,255), NULL);

  /* Reset histogram */
  for (j = 0; j < bins-1; hist[j]=0, j++);

  /* Calc histogram of the image */
  for (i = 0; i < img->height; i++)
  {
    uchar* ptr = (uchar*)(img->imageData + i * img->widthStep);
    for (j = 0; j < img->width; j+=img->nChannels)
      hist[ptr[j+(channel == 3 ? 0 : channel)]]++;
  }

  /* Get histogram peak */
  for (i = 0; i < bins-1; i++)
    max = hist[i] > max ? hist[i] : max;

  /* Get scale so the histogram fit the canvas height */
  scale = max > canvas->height ? (double)canvas->height/max : 1.;

  /* Draw histogram */
  for (i = 0; i < bins-1; i++)
  {
    CvPoint pt1 = cvPoint(i, canvas->height - (hist[i] * scale));
    CvPoint pt2 = cvPoint(i, canvas->height);
    cvLine(canvas, pt1, pt2, colors[channel], 1, 8, 0);
  }

  cvShowImage(window_title, canvas);
  cvReleaseImage(&img);
}


IplImage* MyTabThree::histeq(IplImage* src, IplImage* dst, IplImage* src1, IplImage* dst1)
{
  
	int hist[256];
	int density[256];
	IplImage* hsv, * h, * s, * v;
	IplImage* hsv1, * h1, * s1, * v1;

	for (int i=0;i<256;i++){
		hist[i] = 0;
		density[i] = 0;
	}

  if (src->nChannels == 3)
  {
    hsv = cvCreateImage(cvGetSize(src), 8, 3);
    h   = cvCreateImage(cvGetSize(src), 8, 1);
    s   = cvCreateImage(cvGetSize(src), 8, 1);
    v   = cvCreateImage(cvGetSize(src), 8, 1);

    cvCvtColor(src, hsv, CV_BGR2HSV);
    cvSplit(hsv, h, s, v, NULL);


	 hsv1 = cvCreateImage(cvGetSize(dst), 8, 3);
    h1   = cvCreateImage(cvGetSize(dst), 8, 1);
    s1   = cvCreateImage(cvGetSize(dst), 8, 1);
    v1   = cvCreateImage(cvGetSize(dst), 8, 1);

    cvCvtColor(dst, hsv1, CV_BGR2HSV);
    cvSplit(hsv1, h1, s1, v1, NULL);
	show_histogram("oldHistSRC", src, "gray");
	show_histogram("oldHistDST", dst, "gray");
	cvShowImage("src", src);
	cvShowImage("dst", dst);

	int grayLevel =0,n=0, grayLevel1 =0,n1=0;
	n = src->height*src->width;
	double fvalue = 0.0, fvalue1 = 0.0;
	int total=0, total1=0;
	double mean = 0.0, newhist1=0,newhist=0, aggreHIst=0.0,varToal=0.0, variance = 0.0, stDeviation;

	
	double mean1 = 0.0, varToal1=0.0, variance1 = 0.0, stDeviation1;

	double min1=0.0, min=0.0, max=0.0, max1=0,min2=0.0,max2=0.0;

	

	for (int j=0;j<src->height;j++){
		
		for(int x=0;x<src->width;x++){
			

			grayLevel = cvGetReal2D(v,j,x);
			grayLevel1 = cvGetReal2D(v1,j,x);
			//hist[grayLevel] += 1;
			total+=grayLevel;
			total1+=grayLevel1;
		
		}
	}

	mean = total/n;
	mean1 = total1/n;

	for (int j=0;j<src->height;j++){
		
		for(int x=0;x<src->width;x++){
			
			grayLevel = cvGetReal2D(v,j,x);
			grayLevel1 = cvGetReal2D(v1,j,x);

			varToal += (grayLevel - mean)*(grayLevel - mean);
			varToal1 += (grayLevel1 - mean1)*(grayLevel1 - mean1);

			
		
		}
	}

	variance = varToal/n;

	stDeviation = sqrt(variance);

	variance1 = varToal1/n;

	stDeviation1 = sqrt(variance1);

	for (int j=0;j<src->height;j++){
		
		for(int x=0;x<src->width;x++){
			
			grayLevel = cvGetReal2D(v,j,x);
			grayLevel1 = cvGetReal2D(v1,j,x);

			newhist = (grayLevel-mean)/(stDeviation);
			newhist1 = (grayLevel1-mean1)/(stDeviation1);
			//aggreHIst = (newhist + newhist1)/2.0;
			
			//aggreHIst = (aggreHIst*(stDeviation+stDeviation1)/2.0) + ((mean +mean1)/2.0);

			//newhist = fvalue;
			if(min>newhist) 
				min = newhist;

			 if(min1>newhist1)
				min1 = newhist1;
			
			if(max<newhist) 
				max = newhist;

			if(max1<newhist1) 
				max1 = newhist1;

			if(min2>aggreHIst)
				min2 = aggreHIst;
			
			if(max2<aggreHIst) 
				max2 = aggreHIst;
			

			if((newhist1 <0) || (newhist<0)) {

				//newhist = abs(newhist);
				//cvSetReal2D(v, j, x, newhist);
				//cvSetReal2D(v1, j, x, newhist1);

			}

			else {
				//newhist += 100;
				//cvSetReal2D(v, j, x, newhist);
				//cvSetReal2D(v1, j, x, newhist1);
			}

			
			

			
		
		}
	}

	for (int j=0;j<src->height;j++){
		
		for(int x=0;x<src->width;x++){
			grayLevel = cvGetReal2D(v,j,x);
			grayLevel1 = cvGetReal2D(v1,j,x);

			newhist = (grayLevel-mean)/(stDeviation);
			newhist1 = (grayLevel1-mean1)/(stDeviation1);
			aggreHIst = (newhist + newhist1);
			
			aggreHIst = ((aggreHIst*sqrt((stDeviation*stDeviation)+(stDeviation1*stDeviation1))) + ((mean +mean1)));

			if(min1>aggreHIst)
				min1 = aggreHIst;
			
			if(max1<aggreHIst) 
				max1 = aggreHIst;

			//cvSetReal2D(v1, j, x, aggreHIst);
			


		}
	}
	
	for (int j=0;j<src->height;j++){
		
		for(int x=0;x<src->width;x++){
			grayLevel = cvGetReal2D(v,j,x);
			//grayLevel -= 80; 
			grayLevel1 = cvGetReal2D(v1,j,x);
			//grayLevel1 +=30;
			//aggreHIst = (grayLevel + grayLevel1)/2;

			newhist = (grayLevel-mean)/(stDeviation);
			newhist1 = (grayLevel1-mean1)/(stDeviation1);
			aggreHIst = (newhist + newhist1);
			
			aggreHIst = ((aggreHIst*sqrt((stDeviation*stDeviation)+(stDeviation1*stDeviation1))) + ((mean +mean1)))*255/(abs(min1)+max1);
			//aggreHIst += 30;

			if(aggreHIst <0) {
				aggreHIst = abs(aggreHIst);
				cvSetReal2D(v1, j, x, aggreHIst);
				cvSetReal2D(v, j, x, grayLevel);
				
			}

			else {

				//aggreHIst += (abs(min1)*255/(min1 + max1));
				cvSetReal2D(v, j, x, grayLevel);
			cvSetReal2D(v1, j, x, aggreHIst);
			}


		}
	}

    //cvEqualizeHist(v, v);

    cvMerge(h, s, v, NULL, hsv);
    cvCvtColor(hsv, src1, CV_HSV2BGR);
	show_histogram("NewHist", src1, "gray");
	cvShowImage("one",src1);



	cvMerge(h1, s1, v1, NULL, hsv1);
    cvCvtColor(hsv1, dst1, CV_HSV2BGR);
	show_histogram("AggreHist1", dst1, "gray");
	cvShowImage("two",dst1);
	cvSaveImage("res//texture.bmp", dst1);
	//cvSmooth();
  }
  else if (src->nChannels == 1)
    //cvEqualizeHist(src, dst);

  if (hsv) cvReleaseImage(&hsv);
  if (h) cvReleaseImage(&h);
  if (s) cvReleaseImage(&s);
  if (v) cvReleaseImage(&v);

/*IplImage* image_32F = cvCreateImage(cvGetSize(src),IPL_DEPTH_32F,1);

//now convert the 8bit Image into 32bit floating points
cvCvtScale(src,image_32F);


//to store given mean and varian		src	CXX0017: Error: symbol "src" not found	

CvScalar mean,std_deviation;


//calculate mean and standard deviation
cvAvgSdv(image_32F, &mean, &std_deviation);


//cvNormalize(image_32F,dst,0,1,CV_MINMAX,0);
cvConvertScale(image_32F, image_32F, (1/mean.val[0]), 0);

//cvDiv(NULL,image_32F,image_32F,s);

cvSaveImage("energy_normalized.jpg",image_32F);

//cvAddS(src, value, CvArr* dst, const CvArr* mask=NULL);
*/
return dst;



}






void MyTabThree::OnBnClickedButton3()
{
	
	 IplImage* src = cvLoadImage("K:\\FAPS-Images\\wringle.bmp");
  IplImage* dst = cvLoadImage("K:\\FAPS-Images\\FACEJ.jpg"); //cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
  IplImage* src1 = cvLoadImage("K:\\FAPS-Images\\FACEY.jpg");
  IplImage* dst1 = cvLoadImage("K:\\FAPS-Images\\FACEY.jpg");

  IplImage* xx= histeq(src, dst, src1, dst1);

  //cvShowImage("src", src);
  //cvShowImage("dst", xx);
  cvWaitKey(0);


}
