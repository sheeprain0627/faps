#include "stdafx.h"
#include <cv.h>
#include <cv.h>
#include <highgui.h>
#include "Ageprogression.h"


Ageprogression::Ageprogression(void)
{
}

Ageprogression::~Ageprogression(void)
{
}

void Ageprogression ::texureEnhancePrototype(float p){
	
	IplImage* imgRed[3];
    IplImage* imgGreen[3];
    IplImage* imgBlue[3];
    float q=p;
	for(int i=0;i<3;i++)
    {
        IplImage* img;
        char filename[30];
        sprintf(filename, "Ageprogression\\%d.bmp", (i+1));
        img = cvLoadImage(filename);
        imgRed[i] = cvCreateImage(cvGetSize(img), 8, 1);
        imgGreen[i] = cvCreateImage(cvGetSize(img), 8, 1);
        imgBlue[i] = cvCreateImage(cvGetSize(img), 8, 1);
        cvSplit(img, imgRed[i], imgGreen[i], imgBlue[i], NULL);
        cvReleaseImage(&img);
    }
	
	CvSize imgSize = cvGetSize(imgRed[0]);
	IplImage* imgResultRed = cvCreateImage(imgSize, 8, 1);
    IplImage* imgResultGreen = cvCreateImage(imgSize, 8, 1);
    IplImage* imgResultBlue = cvCreateImage(imgSize, 8, 1);
    IplImage* imgResult = cvCreateImage(imgSize, 8, 3);

	for(int y=0;y<imgSize.height;y++)
    {
        for(int x=0;x<imgSize.width;x++)
        {
            int theSumRed=0;
            int theSumGreen=0;
            int theSumBlue=0;
            for(int i=0;i<3;i++)
            {
                theSumRed+=cvGetReal2D(imgRed[i], y, x);
                theSumGreen+=cvGetReal2D(imgGreen[i], y, x);
                theSumBlue+=cvGetReal2D(imgBlue[i], y, x);
            }
            theSumRed = (float)theSumRed/3.0f;
            theSumGreen = (float)theSumGreen/3.0f;
            theSumBlue = (float)theSumBlue/3.0f;
            cvSetReal2D(imgResultRed, y, x, theSumRed);
            cvSetReal2D(imgResultGreen, y, x, theSumGreen);
            cvSetReal2D(imgResultBlue, y, x, theSumBlue);
        }
    }
	cvMerge(imgResultRed, imgResultGreen, imgResultBlue, NULL, imgResult);
    cvSaveImage("Ageprogression\\result.bmp",imgResult );

	for(int i=0;i<3;i++)
	{ 
	    char infilename[30];
	    char outfilename[30];
        sprintf(infilename, "Ageprogression\\%d.bmp", (i+1));   
	    IplImage* img1 = cvLoadImage(infilename);
	    IplImage* out = cvCreateImage( cvGetSize(img1), IPL_DEPTH_8U, 3 ); 
        cvSmooth(img1, out, CV_GAUSSIAN, 7, 7,q, 0);
	    sprintf(outfilename, "Ageprogression\\%d_smooth.bmp", (i+1));
		cvSaveImage(outfilename, out);
	}

	/* apply Image based surface detils transfer */
	IplImage* imgRedSmooth[3];
    IplImage* imgGreenSmooth[3];
    IplImage* imgBlueSmooth[3];
	
	for(int i=0;i<3;i++)
	{
	    char otfilename[30];
        sprintf(otfilename, "Ageprogression\\%d_smooth.bmp", (i+1));
	    IplImage* imgSmooth = cvLoadImage(otfilename);
        imgRedSmooth[i] = cvCreateImage(cvGetSize(imgSmooth), 8, 1);
        imgGreenSmooth[i] = cvCreateImage(cvGetSize(imgSmooth), 8, 1);
        imgBlueSmooth[i] = cvCreateImage(cvGetSize(imgSmooth), 8, 1);
        cvSplit(imgSmooth, imgRedSmooth[i], imgGreenSmooth[i], imgBlueSmooth[i], NULL);
        cvReleaseImage(&imgSmooth);
	}

	IplImage* imgResultRedTem= cvCreateImage(imgSize, 8, 1);
    IplImage* imgResultGreenTem = cvCreateImage(imgSize, 8, 1);
    IplImage* imgResultBlueTem = cvCreateImage(imgSize, 8, 1);
    IplImage* imgResultD = cvCreateImage(imgSize, 8, 3);
	for(int y=0;y<imgSize.height;y++)
    {
        for(int x=0;x<imgSize.width;x++)
        {
                double theFinalRed=cvGetReal2D(imgResultRed, y, x);
                double theFinalGreen=cvGetReal2D(imgResultGreen, y, x);
                double theFinalBlue=cvGetReal2D(imgResultBlue, y, x);

            for(int i=0;i<3;i++)
            {
                double  theRealRed=cvGetReal2D(imgRed[i], y, x);
                double  theRealGreen=cvGetReal2D(imgGreen[i], y, x);
                double theRealBlue=cvGetReal2D(imgBlue[i], y, x);

			    double	theSmoothRed=cvGetReal2D(imgRedSmooth[i], y, x);
			    double	theSmoothGreen=cvGetReal2D(imgGreenSmooth[i], y, x);
			    double	theSmoothBlue=cvGetReal2D(imgBlueSmooth[i], y, x);

			    double	theTemFinalRed=theRealRed/theSmoothRed;
			    double	theTemFinalGreen=theRealGreen/theSmoothGreen;
			    double	theTemFinalBlue=theRealBlue/theSmoothBlue;

				theFinalRed *=theTemFinalRed;
				theFinalGreen *=theTemFinalGreen;
				theFinalBlue *=theTemFinalBlue;
            }
		  cvSetReal2D(imgResultRedTem, y, x, theFinalRed);
          cvSetReal2D(imgResultGreenTem, y, x, theFinalGreen);
          cvSetReal2D(imgResultBlueTem, y, x, theFinalBlue);
        }
    }
	cvMerge(imgResultRedTem, imgResultGreenTem, imgResultBlueTem, NULL, imgResultD);
    cvSaveImage("Ageprogression\\Texure-Enhanced-prototype.bmp",imgResultD);
	cvShowImage("Texure-Enhanced-prototype", imgResultD);
	cvWaitKey(0);

}

void Ageprogression ::applyIbsdt(float q){


   IplImage* img_murali = cvLoadImage("Ageprogression\\1_murali.bmp");
   IplImage* imgRed_murali = cvCreateImage(cvGetSize(img_murali), 8, 1);
   IplImage* imgGreen_murali = cvCreateImage(cvGetSize(img_murali), 8, 1);
   IplImage* imgBlue_murali = cvCreateImage(cvGetSize(img_murali), 8, 1);
  cvSplit(img_murali, imgRed_murali, imgGreen_murali, imgBlue_murali, NULL);
  CvSize imgSize_murali = cvGetSize(img_murali);
  cvReleaseImage(&img_murali);



for(int i=0;i<2;i++)
	{ 
	char infilename_murali[30];
	char outfilename_murali[50];
    sprintf(infilename_murali, "Ageprogression\\%d_murali.bmp", (i+1));   
	IplImage* img_murali = cvLoadImage(infilename_murali);
	IplImage* out_murali = cvCreateImage( cvGetSize(img_murali), IPL_DEPTH_8U, 3 ); 
    cvSmooth(img_murali, out_murali, CV_GAUSSIAN, 7, 7,q, 0);
	sprintf(outfilename_murali, "Ageprogression\\%d_smooth_murali.bmp", (i+1));
	cvSaveImage(outfilename_murali, out_murali);
	//cvNamedWindow("Gaussian Smooth", 1 );
	//cvShowImage("Gaussian Smooth", out_murali);
	//cvWaitKey(0);
	} 

    IplImage* imgRedSmooth_murali[2];
    IplImage* imgGreenSmooth_murali[2];
    IplImage* imgBlueSmooth_murali[2];
	
	for(int i=0;i<2;i++)
	{
	char otfilename_murali[50];
    sprintf(otfilename_murali, "Ageprogression\\%d_smooth_murali.bmp", (i+1));
	IplImage* imgSmooth_murali = cvLoadImage(otfilename_murali);
    imgRedSmooth_murali[i] = cvCreateImage(cvGetSize(imgSmooth_murali), 8, 1);
    imgGreenSmooth_murali[i] = cvCreateImage(cvGetSize(imgSmooth_murali), 8, 1);
    imgBlueSmooth_murali[i] = cvCreateImage(cvGetSize(imgSmooth_murali), 8, 1);
    cvSplit(imgSmooth_murali, imgRedSmooth_murali[i], imgGreenSmooth_murali[i], imgBlueSmooth_murali[i], NULL);
    cvReleaseImage(&imgSmooth_murali);
	}


	IplImage* imgResultRedTem_murali= cvCreateImage(imgSize_murali, 8, 1);
    IplImage* imgResultGreenTem_murali = cvCreateImage(imgSize_murali, 8, 1);
    IplImage* imgResultBlueTem_murali = cvCreateImage(imgSize_murali, 8, 1);
    IplImage* imgResultD_murali = cvCreateImage(imgSize_murali, 8, 3);

for(int y=0;y<imgSize_murali.height;y++)
    {
        for(int x=0;x<imgSize_murali.width;x++)
        {
                double theFinalRed_murali=cvGetReal2D(imgRedSmooth_murali[1], y, x);
                double theFinalGreen_murali=cvGetReal2D(imgGreenSmooth_murali[1], y, x);
                double theFinalBlue_murali=cvGetReal2D(imgBlueSmooth_murali[1], y, x);

                double  theRealRed_murali=cvGetReal2D(imgRed_murali, y, x);
                double  theRealGreen_murali=cvGetReal2D(imgGreen_murali, y, x);
                double theRealBlue_murali=cvGetReal2D(imgBlue_murali, y, x);

			    double	theSmoothRed_murali=cvGetReal2D(imgRedSmooth_murali[0], y, x);
			    double	theSmoothGreen_murali=cvGetReal2D(imgGreenSmooth_murali[0], y, x);
			    double	theSmoothBlue_murali=cvGetReal2D(imgBlueSmooth_murali[0], y, x);

			    double	theTemFinalRed_murali=theFinalRed_murali*theRealRed_murali/theSmoothRed_murali;
			    double	theTemFinalGreen_murali=theFinalGreen_murali*theRealGreen_murali/theSmoothGreen_murali;
			    double	theTemFinalBlue_murali=theFinalBlue_murali*theRealBlue_murali/theSmoothBlue_murali;

		  cvSetReal2D(imgResultRedTem_murali, y, x, theTemFinalRed_murali);
          cvSetReal2D(imgResultGreenTem_murali, y, x, theTemFinalGreen_murali);
          cvSetReal2D(imgResultBlueTem_murali, y, x, theTemFinalBlue_murali);
          
        }
    }

	cvMerge(imgResultRedTem_murali, imgResultGreenTem_murali, imgResultBlueTem_murali, NULL, imgResultD_murali);
    cvNamedWindow("IBSDT");
    cvShowImage("IBSDT", imgResultD_murali);
    cvSaveImage("Ageprogression\\IBSDT.bmp",imgResultD_murali);
	//cvWaitKey(0);
	//;



}
float Ageprogression ::getSigma()const{
	return sigma;
}
void Ageprogression ::setSigma(float q){
	sigma=q;
}


