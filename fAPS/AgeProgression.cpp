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

//define number of images takein as database
const int no_db=4;


//create the age prototype
void Ageprogression ::texureEnhancePrototype(float p){
	
	IplImage* imgRed[no_db];
    IplImage* imgGreen[no_db];
    IplImage* imgBlue[no_db];
    float q=p;

	//split the database images in to RGB segment
	for(int i=0;i<no_db;i++)
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


	//calculate the sum of RGD and find the average
	for(int y=0;y<imgSize.height;y++)
    {
        for(int x=0;x<imgSize.width;x++)
        {
            int theSumRed=0;
            int theSumGreen=0;
            int theSumBlue=0;
            for(int i=0;i<no_db;i++)
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


	//smoothening the each database image
	for(int i=0;i<no_db;i++)
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
	IplImage* imgRedSmooth[no_db];
    IplImage* imgGreenSmooth[no_db];
    IplImage* imgBlueSmooth[no_db];
	

	//split the smoothed database images in to RGB segment
	for(int i=0;i<no_db;i++)
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

	//age prototype algo
	for(int y=0;y<imgSize.height;y++)
    {
        for(int x=0;x<imgSize.width;x++)
        {
                double theFinalRed=cvGetReal2D(imgResultRed, y, x);
                double theFinalGreen=cvGetReal2D(imgResultGreen, y, x);
                double theFinalBlue=cvGetReal2D(imgResultBlue, y, x);

            for(int i=0;i<no_db;i++)
            {
				//avaraged database image
                double  theRealRed=cvGetReal2D(imgRed[i], y, x);
                double  theRealGreen=cvGetReal2D(imgGreen[i], y, x);
                double theRealBlue=cvGetReal2D(imgBlue[i], y, x);

				//smoothened avaraged database image
			    double	theSmoothRed=cvGetReal2D(imgRedSmooth[i], y, x);
			    double	theSmoothGreen=cvGetReal2D(imgGreenSmooth[i], y, x);
			    double	theSmoothBlue=cvGetReal2D(imgBlueSmooth[i], y, x);

				//algo
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
    cvSaveImage("Ageprogression\\1_murali.bmp",imgResultD); //Texure-Enhanced-prototype.bmp
	cvShowImage("Texure-Enhanced-prototype", imgResultD);
	cvWaitKey(0);

}

//apply the age prototype with input image
void Ageprogression ::applyIbsdt(float q){


   IplImage* AgePrototype = cvLoadImage("Ageprogression\\1_murali.bmp");
   IplImage* imgRed_Prototype = cvCreateImage(cvGetSize(AgePrototype), 8, 1);
   IplImage* imgGreen_Prototype = cvCreateImage(cvGetSize(AgePrototype), 8, 1);
   IplImage* imgBlue_Prototype = cvCreateImage(cvGetSize(AgePrototype), 8, 1);
  cvSplit(AgePrototype, imgRed_Prototype, imgGreen_Prototype, imgBlue_Prototype, NULL);
  CvSize imgSize_Standard = cvGetSize(AgePrototype);
  cvReleaseImage(&AgePrototype);


  //smoothening the age prototype and input image
for(int i=0;i<2;i++)
	{ 
	char infilename_face[30];
	char outfilename_face[50];
    sprintf(infilename_face, "Ageprogression\\%d_murali.bmp", (i+1));   
	IplImage* in_face = cvLoadImage(infilename_face);
	IplImage* out_face = cvCreateImage( cvGetSize(in_face), IPL_DEPTH_8U, 3 ); 
    cvSmooth(in_face, out_face, CV_GAUSSIAN, 7, 7,q, 0);
	sprintf(outfilename_face, "Ageprogression\\%d_smooth_murali.bmp", (i+1));
	cvSaveImage(outfilename_face, out_face);
	//cvNamedWindow("Gaussian Smooth", 1 );
	//cvShowImage("Gaussian Smooth", out_murali);
	//cvWaitKey(0);
	} 

    IplImage* imgRedSmoothed[2];
    IplImage* imgGreenSmoothed[2];
    IplImage* imgBlueSmoothed[2];
	

	//split of smoothened images into RGB segment
	for(int i=0;i<2;i++)
	{
	char otfilename_murali[50];
    sprintf(otfilename_murali, "Ageprogression\\%d_smooth_murali.bmp", (i+1));
	IplImage* imgSmoothed = cvLoadImage(otfilename_murali);
    imgRedSmoothed[i] = cvCreateImage(cvGetSize(imgSmoothed), 8, 1);
    imgGreenSmoothed[i] = cvCreateImage(cvGetSize(imgSmoothed), 8, 1);
    imgBlueSmoothed[i] = cvCreateImage(cvGetSize(imgSmoothed), 8, 1);
    cvSplit(imgSmoothed, imgRedSmoothed[i], imgGreenSmoothed[i], imgBlueSmoothed[i], NULL);
    cvReleaseImage(&imgSmoothed);
	}

	//the output age progressed image dae stored here
	IplImage* imgResultRedTem= cvCreateImage(imgSize_Standard, 8, 1);
    IplImage* imgResultGreenTem = cvCreateImage(imgSize_Standard, 8, 1);
    IplImage* imgResultBlueTem= cvCreateImage(imgSize_Standard, 8, 1);
    IplImage* imgResultD = cvCreateImage(imgSize_Standard, 8, 3);

for(int y=0;y<imgSize_Standard.height;y++)
    {
        for(int x=0;x<imgSize_Standard.width;x++)
        {      
		//Smoothed Input image
                double theSoomthlRed_Input=cvGetReal2D(imgRedSmoothed[1], y, x);
                double theSoomthFinalGreen_Input=cvGetReal2D(imgGreenSmoothed[1], y, x);
                double theSoomthFinalBlue_Input=cvGetReal2D(imgBlueSmoothed[1], y, x);

		//AgePrototype image 
                double  theRealRed_Prototype=cvGetReal2D(imgRed_Prototype, y, x);
                double  theRealGreen_Prototype=cvGetReal2D(imgGreen_Prototype, y, x);
                double theRealBlue_Prototype=cvGetReal2D(imgBlue_Prototype, y, x);
		//Smoothed AgePrototype image 
			    double	theSmoothRed_Prototype=cvGetReal2D(imgRedSmoothed[0], y, x);
			    double	theSmoothGreen_Prototype=cvGetReal2D(imgGreenSmoothed[0], y, x);
			    double	theSmoothBlue_Prototype=cvGetReal2D(imgBlueSmoothed[0], y, x);

	//the algo function
			    double	theTemFinalRed=theSoomthlRed_Input*theRealRed_Prototype/theSmoothRed_Prototype;
			    double	theTemFinalGreen=theSoomthFinalGreen_Input*theRealGreen_Prototype/theSmoothGreen_Prototype;
			    double	theTemFinalBlue=theSoomthFinalBlue_Input*theRealBlue_Prototype/theSmoothBlue_Prototype;

		  cvSetReal2D(imgResultRedTem, y, x, theTemFinalRed);
          cvSetReal2D(imgResultGreenTem, y, x, theTemFinalGreen);
          cvSetReal2D(imgResultBlueTem, y, x, theTemFinalBlue);
          
        }
    }

	cvMerge(imgResultRedTem, imgResultGreenTem, imgResultBlueTem, NULL, imgResultD);
    cvNamedWindow("IBSDT");
    cvShowImage("IBSDT", imgResultD);
    cvSaveImage("Ageprogression\\IBSDT.bmp",imgResultD);
	//cvWaitKey(0);
	//;



}

void Ageprogression ::setSigma(float q){
	sigma=q;
}


