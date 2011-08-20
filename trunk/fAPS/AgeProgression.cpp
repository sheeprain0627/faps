#include "stdafx.h"
#include <cv.h>
#include <highgui.h>
#include "Ageprogression.h"
#include "Tdsloader.h"
#include "MyTabOne.h"



Ageprogression::Ageprogression(void)
{
}

Ageprogression::~Ageprogression(void)
{
}

//define number of images takein as database
const int NO_IMAGES=4;


//create the age prototype
void Ageprogression ::texureEnhancePrototype(float p){		
	IplImage* imgRed[NO_IMAGES];
    IplImage* imgGreen[NO_IMAGES];
    IplImage* imgBlue[NO_IMAGES];
    float q=p;

	//split the database images in to RGB segment
	for(int i=0;i<NO_IMAGES;i++)
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
            for(int i=0;i<NO_IMAGES;i++)
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
	for(int i=0;i<NO_IMAGES;i++)
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
	IplImage* imgRedSmooth[NO_IMAGES];
    IplImage* imgGreenSmooth[NO_IMAGES];
    IplImage* imgBlueSmooth[NO_IMAGES];
	

	//split the smoothed database images in to RGB segment
	for(int i=0;i<NO_IMAGES;i++)
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

            for(int i=0;i<NO_IMAGES;i++)
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


   IplImage* input = cvLoadImage("Ageprogression\\2_murali.bmp");
   IplImage* imgRed_input = cvCreateImage(cvGetSize(input), 8, 1);
   IplImage* imgGreen_input = cvCreateImage(cvGetSize(input), 8, 1);
   IplImage* imgBlue_input = cvCreateImage(cvGetSize(input), 8, 1);
  cvSplit(input, imgRed_input, imgGreen_input, imgBlue_input, NULL);
  cvReleaseImage(&input);


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
		
			//not applying IBSDT
				int *xc=getXCriticalPoints();
				int *yc=getYCriticalPoints();

                double	theTemFinalRed;
			    double	theTemFinalGreen;
			    double	theTemFinalBlue;
//left eye
		  int cx1=26;//xc[0];
		  int cy2=66;//yc[1];
		  int cy3=80;//yc[2]; 
		  int cx4=66;//xc[3];
//right eye	
		  int cx5=104;//xc[4];
		  int cy6=65;//yc[5];
		  int cy7=81;//yc[6]; 
		  int cx8=144;//xc[7];
//mouth	
		  int cx12=57;//xc[11];  
		  int cy13=143;//yc[12];
		  int cy14=165;//yc[13];
		  int cx15=117;//xc[14]; 
		  
//calculate eclipse
		  float a1=(float)((cx4-cx1)/2);
		  float b1=(float)((cy3-cy2)/2);
		  float ck1=((float)((a1+cx1-x)*(a1+cx1-x)))/(a1*a1)+((float)((cy2+b1-y)*(cy2+b1-y)))/(b1*b1);
		  float a2=(float)((cx8-cx5)/2);
		  float b2=(float)((cy7-cy6)/2);
		  float ck2=((float)((a2+cx5-x)*(a2+cx5-x)))/(a2*a2)+((float)((cy6+b2-y)*(cy6+b2-y)))/(b2*b2);
		  float a3=(float)((cx15-cx12)/2);
		  float b3=(float)((cy14-cy13)/2);
		  float ck3=((float)((a3+cx12-x)*(a3+cx12-x)))/(a3*a3)+((float)((cy13+b3-y)*(cy13+b3-y)))/(b3*b3);
			
          if (((x>=cx1)&&(x<=cx4)&&(y>=cy2)&&(ck1<=1.0)&&(y<=cy3))||((x>=cx5)&&(x<=cx8)&&(y>=cy6)&&(ck2<=1.0)&&(y<=cy7))||((x>=cx12)&&(x<=cx15)&&(y>=cy13)&&(ck3<=1.0)&&(y<=cy14))){
					theTemFinalRed=cvGetReal2D(imgRed_input, y, x);
			    	theTemFinalGreen=cvGetReal2D(imgGreen_input, y, x);
			    	theTemFinalBlue=cvGetReal2D(imgBlue_input, y, x);
				}
		  /*
				double	theTemFinalRed;
			    double	theTemFinalGreen;
			    double	theTemFinalBlue;
		  float a1=20; float b1=7;
		  float ck1=((float)((20+26-x)*(20+26-x)))/(a1*a1)+((float)((66+7-y)*(66+7-y)))/(b1*b1);
		  float a2=20; float b2=8;
		  float ck2=((float)((20+104-x)*(20+104-x)))/(a2*a2)+((float)((65+8-y)*(65+8-y)))/(b2*b2);
		  float a3=30; float b3=11;
		  float ck3=((float)((30+57-x)*(30+57-x)))/(a3*a3)+((float)((143+11-y)*(143+11-y)))/(b3*b3);
				if (((x>=26)&&(x<=66)&&(y>=66)&&(ck1<=1.0)&&(y<=80))||((x>=104)&&(x<=144)&&(y>=65)&&(ck2<=1.0)&&(y<=81))||((x>=57)&&(x<=117)&&(y>=143)&&(ck3<=1.0)&&(y<=165))){
					theTemFinalRed=cvGetReal2D(imgRed_input, y, x);
			    	theTemFinalGreen=cvGetReal2D(imgGreen_input, y, x);
			    	theTemFinalBlue=cvGetReal2D(imgBlue_input, y, x);}*/
				else {
			   	theTemFinalRed=theSoomthlRed_Input*theRealRed_Prototype/theSmoothRed_Prototype;
			   	theTemFinalGreen=theSoomthFinalGreen_Input*theRealGreen_Prototype/theSmoothGreen_Prototype;
			   	theTemFinalBlue=theSoomthFinalBlue_Input*theRealBlue_Prototype/theSmoothBlue_Prototype;
				}
			
		  cvSetReal2D(imgResultRedTem, y, x, theTemFinalRed);
          cvSetReal2D(imgResultGreenTem, y, x, theTemFinalGreen);
          cvSetReal2D(imgResultBlueTem, y, x, theTemFinalBlue);
          
        }
    }

	cvMerge(imgResultRedTem, imgResultGreenTem, imgResultBlueTem, NULL, imgResultD);
    cvNamedWindow("IBSDT");
    cvShowImage("IBSDT", imgResultD);
    cvSaveImage("Ageprogression\\IBSDT.bmp",imgResultD);

	IplImage* black = cvLoadImage("Ageprogression\\black.bmp");
	cvOverlayImage(black, imgResultD, cvPoint(35, 55), cvScalar(0.5,0.5,0.5,0.5), cvScalar(0.5,0.5,0.5,0.5));
	//mergeImage(black,imgResultD,30,30);
	cvSaveImage("Ageprogression\\newimage.bmp",black);
	
	LoadImage("Ageprogression\\newimage.bmp", 255, 0, 1);
	//cvWaitKey(0);
	//;



}

void Ageprogression ::setSigma(float q){
	sigma=q;
}

void Ageprogression ::mergeImage(IplImage* target, IplImage* source, int x, int y) {
    for (int ix=0; x<source->width; x++) {
        for (int iy=0; y<source->height; y++) {
            int r = cvGet2D(source, iy, ix).val[2];
            int g = cvGet2D(source, iy, ix).val[1];
            int b = cvGet2D(source, iy, ix).val[0];
            CvScalar bgr = cvScalar(b, g, r);
            cvSet2D(target, iy+y, ix+x, bgr);
        }
    }
}


void Ageprogression ::cvOverlayImage(IplImage* src, IplImage* overlay, CvPoint location, CvScalar S, CvScalar D)
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
}