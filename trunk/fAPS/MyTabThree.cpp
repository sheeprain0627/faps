// MyTabThree.cpp : implementation file
//

#include "stdafx.h"
#include "MyTabThree.h"
#include "afxdialogex.h"
#include "Tdsloader.h"
#include "Ageprogression.h"
#include "detectFaceComponets.h"
#include <cxcore.h>
#include "cv.h"
#include <math.h>
#include<conio.h>
#include "highgui.h"
#include "cvaux.h"

using namespace cv;
#define HISTMATCH_EPSILON 0.000001

// MyTabThree dialog
Ageprogression age;
detectFaceComponets facedetect;
//CvPoint pointsArry[19];
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
	ON_BN_CLICKED(IDC_ApplyAge, &MyTabThree::OnBnClickedApplyage)
	ON_BN_CLICKED(IDC_saveface, &MyTabThree::OnBnClickedsaveface)
	ON_BN_CLICKED(IDC_BUTTON4, &MyTabThree::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &MyTabThree::OnBnClickedNew)
	ON_BN_CLICKED(IDC_BUTTON6, &MyTabThree::OnBnClickedButton6)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// MyTabThree message handlers



void MyTabThree::OnBnClickedButton1()
{
	CString s;
	GetDlgItemText(IDC_EDIT1, s);
	float x = atof( s );
	age.texureEnhancePrototype(x);
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
 
	dlg.m_ofn.lpstrTitle = _T("Open Image");
 
	if (dlg.DoModal() == IDOK) { 
		CString path = dlg.GetPathName();
		LoadImage2(path, 255, 0, 0);		
	}
}


void MyTabThree::OnNMCustomdrawAgebar(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	int curret = agebar.GetPos();
	
	float x = (float)(curret - 20) / 30;
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
		cvNamedWindow("Lap", 1);
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

  if (src->nChannels == 3 && channel == 3) {
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
  for (i = 0; i < img->height; i++) {
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
  for (i = 0; i < bins-1; i++) {
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

	for (int i = 0;i < 256; i++) {
		hist[i] = 0;
		density[i] = 0;
	}

	  if (src->nChannels == 3) {

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
		//cvThreshHist

		int grayLevel = 0, n = 0, grayLevel1 = 0, n1 = 0;
		n = src->height * src->width;
		double fvalue = 0.0, fvalue1 = 0.0;
		int total = 0, total1 = 0;
		double mean = 0.0, newhist1 = 0, newhist = 0, aggreHIst = 0.0, varToal = 0.0, variance = 0.0, stDeviation;

		double mean1 = 0.0, varToal1 = 0.0, variance1 = 0.0, stDeviation1;

		//double min1 = 0.0, min = 0.0, max = 0.0, max1 = 0, min2 = 0.0, max2 = 0.0;
		int min = 0, max = 0;
		for (int j = 0; j < src->height; j++) {
		
			for(int x = 0; x < src->width; x++) {
			
				grayLevel = cvGetReal2D(v, j, x);
				grayLevel1 = cvGetReal2D(v1, j, x);
				//hist[grayLevel] += 1;
				total += grayLevel;
				total1 += grayLevel1;
		
			}
		}

		mean = total / n;
		mean1 = total1 / n;

		for (int j = 0; j < src->height; j++){
		
			for(int x = 0; x < src->width; x++){
			
				grayLevel = cvGetReal2D(v, j, x);
				grayLevel1 = cvGetReal2D(v1, j, x);

				varToal += (grayLevel - mean) * (grayLevel - mean);
				varToal1 += (grayLevel1 - mean1) * (grayLevel1 - mean1);
		
			}
		}

		variance = varToal / n;

		stDeviation = sqrt(variance);

		variance1 = varToal1 / n;

		stDeviation1 = sqrt(variance1);

		//int min = 0, max = 0;

		//fitted dynamic range into two segma
		
		/*for (int j = 0; j < src->height; j++){
		
			for(int x = 0; x<src->width; x++){
			
				grayLevel = cvGetReal2D(v, j, x);
				grayLevel1 = cvGetReal2D(v1, j, x);

				min = (int)mean - (int)(stDeviation*0.3);
				max = (int)mean + (int)(stDeviation*0.3);

				if(grayLevel > min || grayLevel < max ) {

					
					if(grayLevel == min){
						grayLevel = (int)mean1 - (int)stDeviation1;
					}

					else {
						grayLevel = ((grayLevel - min) * (int)stDeviation1) / (int)stDeviation + (((int)mean1) + (int)stDeviation1);
					}


				}

				cvSetReal2D(v, j, x, grayLevel);
				
				/*newhist = (grayLevel - mean) / (stDeviation);
				newhist1 = (grayLevel1 - mean1) / (stDeviation1);
				//aggreHIst = (newhist + newhist1)/2.0;
			
				//aggreHIst = (aggreHIst*(stDeviation+stDeviation1)/2.0) + ((mean +mean1)/2.0);

				//newhist = fvalue;
				if(min > newhist) 
					min = newhist;

				 if(min1 > newhist1)
					min1 = newhist1;
			
				if(max < newhist) 
					max = newhist;

				if(max1 < newhist1) 
					max1 = newhist1;

				if(min2 > aggreHIst)
					min2 = aggreHIst;
			
				if(max2 < aggreHIst) 
					max2 = aggreHIst;
			

				if((newhist1 < 0) || (newhist < 0)) {

					//newhist = abs(newhist);
					//cvSetReal2D(v, j, x, newhist);
					//cvSetReal2D(v1, j, x, newhist1);

				} else {
					//newhist += 100;
					//cvSetReal2D(v, j, x, newhist);
					//cvSetReal2D(v1, j, x, newhist1);
				}
				*/
			//}
		//}

		/*for (int j = 0;j < src->height; j++) {
		
			for(int x = 0; x < src->width; x++) {

				grayLevel = cvGetReal2D(v, j, x);
				grayLevel1 = cvGetReal2D(v1, j, x);

				newhist = (grayLevel - mean) / (stDeviation);
				newhist1 = (grayLevel1 - mean1) / (stDeviation1);
				aggreHIst = (newhist + newhist1);
			
				aggreHIst = ((aggreHIst * sqrt((stDeviation * stDeviation) + (stDeviation1 * stDeviation1))) + ((mean + mean1)));

				if(min1 > aggreHIst)
					min1 = aggreHIst;
			
				if(max1 < aggreHIst) 
					max1 = aggreHIst;

				//cvSetReal2D(v1, j, x, aggreHIst);
			}
		}
	
		for (int j = 0; j < src->height; j++) {
		
			for(int x = 0; x < src->width; x++) {

				grayLevel = cvGetReal2D(v, j, x);
				//grayLevel -= 80; 
				grayLevel1 = cvGetReal2D(v1, j, x);
				//grayLevel1 +=30;
				//aggreHIst = (grayLevel + grayLevel1)/2;

				newhist = (grayLevel - mean) / (stDeviation);
				newhist1 = (grayLevel1 - mean1) / (stDeviation1);
				aggreHIst = (newhist + newhist1);
			
				aggreHIst = ((aggreHIst * sqrt((stDeviation * stDeviation) + (stDeviation1 * stDeviation1))) + 
						((mean + mean1))) * 255 / (abs(min1) + max1);
				
				if(aggreHIst < 0) {
					aggreHIst = abs(aggreHIst);
					cvSetReal2D(v1, j, x, aggreHIst);
					cvSetReal2D(v, j, x, grayLevel);
				
				} else {

					cvSetReal2D(v, j, x, grayLevel);			
					cvSetReal2D(v1, j, x, aggreHIst);
				}


			}
		}
		*/

		double retinex = 0.0;
		double funct = 0.0, coef = 0.0;
		for (int j = 0;j < src->height; j++) {
		
			for(int x = 0; x < src->width; x++) {

				grayLevel = cvGetReal2D(v, j, x);

				coef = (x*x + j*j)/(25);
				funct =exp(coef);
				retinex = log10f(grayLevel) - log10f(grayLevel * funct);

				retinex = pow(10, retinex);
				cvSetReal2D(v, j, x, retinex);


			}

		}
		//cvEqualizeHist(v, v);

		cvMerge(h, s, v, NULL, hsv);
		cvCvtColor(hsv, src1, CV_HSV2BGR);
		show_histogram("NewHist", src1, "gray");
		cvShowImage("one",src1);
		//cvSaveImage("res//texture11.bmp", dst1);


		cvMerge(h1, s1, v1, NULL, hsv1);
		cvCvtColor(hsv1, dst1, CV_HSV2BGR);
		show_histogram("AggreHist1", dst1, "gray");
		cvShowImage("two",dst1);
		//cvSaveImage("res//texture.bmp", dst1);
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
	
	IplImage* src = cvLoadImage("res\\FACEJ.jpg");
	IplImage* dst = cvLoadImage("res\\FACEY.jpg"); //cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	IplImage* src1 = cvLoadImage("res\\FACEJ.jpg");
	IplImage* dst1 = cvLoadImage("res\\FACEJ.jpg");

	IplImage* xx= histeq(src, dst, src1, dst1);

	//cvShowImage("src", src);
	//cvShowImage("dst", xx);
	cvWaitKey(0);

}


void MyTabThree::OnBnClickedApplyage()
{
	CString s;
	GetDlgItemText(IDC_EDIT1, s);
	float x = atof( s );
		age.applyIbsdt(x);


	// TODO: Add your control notification handler code here
}


void MyTabThree::OnBnClickedsaveface()
{
	captureImage();
	// TODO: Add your control notification handler code here
}


void MyTabThree::OnBnClickedButton4()
{
	

int i,j,k;
int heightc,widthc,stepc,channelsc;

int temp=0;
int units=0;
uchar *data,*datac;
i=j=k=0;

IplImage *frame=cvLoadImage("res\\FACEN.jpg",1);
IplImage *convert=cvCreateImage( cvGetSize(frame), 8, 3 );
IplImage *result=cvCreateImage( cvGetSize(frame), 8, 3 );
//printf("By what value Do you want to increase the strenght of the color..? ");
//scanf("%d", &units);
units = 30;
if(frame==NULL ) {
//puts("unable to load the frame");exit(0);}
}


cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
 cvNamedWindow("Result",CV_WINDOW_AUTOSIZE);

heightc = convert->height;
widthc = convert->width;

stepc=convert->widthStep;
channelsc=convert->nChannels;
datac = (uchar *)convert->imageData;

IplImage*  h, * s, * v;
	
	
		h   = cvCreateImage(cvGetSize(frame), 8, 1);
		s   = cvCreateImage(cvGetSize(frame), 8, 1);
		v   = cvCreateImage(cvGetSize(frame), 8, 1);

cvCvtColor(frame,convert,CV_BGR2HSV);
cvSplit(convert, h, s, v, NULL);
int gray = 0;
for(i=0;i< (heightc);i++) for(j=0;j<(widthc);j++)
{/*Here datac means data of the HSV Image*/
/*Here i want to Increase the saturation or the strength of the Colors in the Image and
then I would be able to perform a good color detection*/

temp=datac[i*stepc+j*channelsc+1]+units;/*increas the saturaion component is the second arrray.*/

gray = cvGetReal2D(v, i, j);
gray = gray - 23;
cvSetReal2D(v, i, j, gray);

/*Here there is a small problem...when you add a value to the data and if it exceeds 255
it starts all over again from zero and hence some of the pixels might go to zero.
So to stop this we need to include this loop i would not try to explain the loop but
please try and follow it is easy to do so..*/
if(temp>255) datac[i*stepc+j*channelsc+1]=255;
else datac[i*stepc+j*channelsc+1]=temp;/*you may
please remove and see what is happening if the if else loop is not there*/}


//cvEqualizeHist(v, v);

cvMerge(h, s, v, NULL, convert);
		

cvCvtColor(convert, result, CV_HSV2BGR);
cvShowImage("Result", result);
cvShowImage("original", frame);

 cvSaveImage("Enhresult.jpg",result);
 cvWaitKey(0);
 cvDestroyWindow("original");
 cvDestroyWindow("Result");
 

 }


// Compute histogram and CDF for an image with mask
void MyTabThree::do1ChnHist(const Mat& _i, const Mat& mask, double* h, double* cdf) {
	Mat _t = _i.reshape(1,1);

	/*Mat _tm;
	mask.copyTo(_tm);
	CvPoint pt;
	_tm = _tm.reshape(1,1);
	for(int p=0; p < _t.cols; p++) {
	uchar tm = _tm.at<uchar>(0,p);
	int itm = tm;
	if(itm > 0) {
	uchar c = _t.at<uchar>(0,p);
	h[c] += 1.0;
	}
	}*/
 
	// Get the histogram with or without the mask
	if (true) {
		cv::Mat _tm;
		mask.copyTo(_tm);
		_tm = _tm.reshape(1,1);

		for(int p=0; p<_t.cols; p++) {
			uchar m = _tm.at<uchar>(0,p);
			if(m > 0) { // Mask value
				uchar c = _t.at<uchar>(0,p); // Image value
				h[c] += 1.0;
	        }
        }
    }
    else {
        for(int p=0; p<_t.cols; p++) {
            uchar c = _t.at<uchar>(0,p);   // Image value
            h[c] += 1.0;
		}
	}
	//normalize hist
	Mat _tmp(1,256,CV_64FC1,h);
	double minVal,maxVal;
	minMaxLoc(_tmp,&minVal,&maxVal);
	_tmp = _tmp / maxVal;
 
	cdf[0] = h[0];
	for(int j=1; j < 256; j++) {
	cdf[j] = cdf[j-1]+h[j];
	}
 
	//normalize CDF
	_tmp.data = (uchar*)cdf;
	minMaxLoc(_tmp,&minVal,&maxVal);
	_tmp = _tmp / maxVal;
}

void MyTabThree::histMatchRGB(Mat& src, const Mat& src_mask, const Mat& dst, const Mat& dst_mask) {
#ifdef BTM_DEBUG
    namedWindow("original source",CV_WINDOW_AUTOSIZE);
    imshow("original source",src);
    namedWindow("original query",CV_WINDOW_AUTOSIZE);
    imshow("original query",dst);
#endif
 
	namedWindow("original source",CV_WINDOW_AUTOSIZE);
    imshow("original source",src);
    namedWindow("original query",CV_WINDOW_AUTOSIZE);
    imshow("original query",dst);

    vector<Mat> chns;
    split(src,chns);
    vector<Mat> chns1;
    split(dst,chns1);
    Mat src_hist = Mat::zeros(1,256,CV_64FC1);
    Mat dst_hist = Mat::zeros(1,256,CV_64FC1);
    Mat src_cdf = Mat::zeros(1,256,CV_64FC1);
    Mat dst_cdf = Mat::zeros(1,256,CV_64FC1);
    Mat Mv(1,256,CV_8UC1);
    uchar* M = Mv.ptr<uchar>();
 
    for (int i=0;i<3;i++) {
        src_hist.setTo(cvScalar(0));
        dst_hist.setTo(cvScalar(0));
        src_cdf.setTo(cvScalar(0));
        src_cdf.setTo(cvScalar(0));

		
 
        
 
        uchar last = 0;
        double* _src_cdf = src_cdf.ptr<double>();
        double* _dst_cdf = dst_cdf.ptr<double>();
		double* _src_hist = src_hist.ptr<double>();
        double* _dst_hist = dst_hist.ptr<double>();

		do1ChnHist(chns[i],src_mask,_src_hist,_src_cdf);
        do1ChnHist(chns1[i],dst_mask,_dst_hist,_dst_cdf);
 
        for(int j=0;j<src_cdf.cols;j++) {
            double F1j = _src_cdf[j];
 
            for(uchar k = last; k<dst_cdf.cols; k++) {
                double F2k = _dst_cdf[k];
                if(abs(F2k - F1j) < HISTMATCH_EPSILON || F2k > F1j) {
                    M[j] = k;
                    last = k;
                    break;
                }
            }
        }
 
        Mat lut(1,256,CV_8UC1,M);
        LUT(chns[i],lut,chns[i]);
    }
 
    Mat res;
    merge(chns,res);
 
	namedWindow("matched",CV_WINDOW_AUTOSIZE);
    imshow("matched",res);
	imwrite("Ageprogression\\hist.jpg", res);
	//show_histogram("matched", res, "gray");
 
    //waitKey(BTM_WAIT_TIME);
#ifdef BTM_DEBUG
    namedWindow("matched",CV_WINDOW_AUTOSIZE);
    imshow("matched",res);
 
    waitKey(BTM_WAIT_TIME);
#endif
 
    res.copyTo(src);
}



void MyTabThree::OnBnClickedNew()
{
		
		// TODO: Add your control notification handler code here
	Mat src=cvLoadImage("Ageprogression\\img4E.bmp");
	Mat dst=cvLoadImage("Ageprogression\\retinex2.jpg");
	Mat src_mask = cvLoadImage("Ageprogression\\white.bmp",0);
	Mat dst_mask = cvLoadImage("Ageprogression\\white.bmp",0);
	
 
	histMatchRGB(dst,dst_mask,src,src_mask);


}




void MyTabThree::OnBnClickedButton6()
{

	
	facedetect.loadFaceImages();

   
}


BOOL MyTabThree::OnEraseBkgnd(CDC* pDC)
{
	SBitdraw(pDC, IDB_TABBACKGRND, 1);

	return true;//CDialog::OnEraseBkgnd(pDC);
}


bool MyTabThree::SBitdraw(CDC *pDC, UINT nIDResource, int i) 
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
