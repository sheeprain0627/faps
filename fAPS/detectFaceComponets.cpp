#include "stdafx.h"
#include "MyTabThree.h"
#include "afxdialogex.h"
#include "Tdsloader.h"
#include "Ageprogression.h"
#include <cxcore.h>
#include "cv.h"
#include <math.h>
#include<conio.h>
#include "highgui.h"
#include "cvaux.h"
#include "detectFaceComponets.h"


CvPoint pointsArry[19];
CvHaarClassifierCascade *cascade,*cascade_e,*cascade_nose,*cascade_mouth;
CvMemStorage            *storage;
char *face_cascade="haarcascade_frontalface_alt2.xml";
char *eye_cascade="parojos.xml";
char *nose_cascade="Nariz.xml";
char *mouth_cascade="Mouth.xml";



int *detectFaceComponets::getFeaturePoints_x(){
	int detectedpoints_x[19];
	for(int i=0;i<19;i++){
		detectedpoints_x[i]=pointsArry[i].x;
	}
	return detectedpoints_x;
}

int *detectFaceComponets::getFeaturePoints_y(){
	int detectedpoints_y[19];
	for(int i=0;i<19;i++){
		detectedpoints_y[i]=pointsArry[i].y;
	}
	return detectedpoints_y;
}
 /*Mouth detect ion*/
void detectFaceComponets::detectMouth( IplImage *img,CvRect *r)
{
   CvSeq *mouth;
   //mouth detecetion - set ROI
   cvSetImageROI(img,/* the source image */
                 cvRect(r->x,            /* x = start from leftmost */
                        r->y+(r->height *2/3), /* y = a few pixels from the top */
                        r->width,        /* width = same width with the face */
                        r->height/3    /* height = 1/3 of face height */
                       )
                );
    mouth = cvHaarDetectObjects(img,/* the source image, with the estimated location defined */
                                cascade_mouth,      /* the eye classifier */
                                storage,        /* memory buffer */
                                1.15, 4, 0,     /* tune for your app */
                                cvSize(25, 15)  /* minimum detection scale */
                               );

        for( int i = 0; i < 1; i++ )
        {
     
          CvRect *mouth_cord = (CvRect*)cvGetSeqElem(mouth, i);

		  /* get the points*/
		 CvPoint mouthpoint1= cvPoint(mouth_cord->x, mouth_cord->y + mouth_cord->height/2);
		 CvPoint mouthpoint2= cvPoint(mouth_cord->x + mouth_cord->width/2, mouth_cord->y);
		 CvPoint mouthpoint3= cvPoint(mouth_cord->x + mouth_cord->width/2, mouth_cord->y + mouth_cord->height);
		 CvPoint mouthpoint4= cvPoint(mouth_cord->x + mouth_cord->width, mouth_cord->y + mouth_cord->height/2);
		  ///////////////////

		 
		 pointsArry[11].x=mouthpoint1.x;
		 pointsArry[11].y=mouthpoint1.y;
		  pointsArry[12].x=mouthpoint2.x;
		 pointsArry[12].y=mouthpoint2.y;
		  pointsArry[13].x=mouthpoint3.x;
		 pointsArry[13].y=mouthpoint3.y;
		  pointsArry[14].x=mouthpoint4.x;
		 pointsArry[14].y=mouthpoint4.y;
		 
		 /* draw points on mouth*/

		 cvCircle(img, mouthpoint1, 1, CV_RGB(255,255, 255), 1, 8, 0);
		 cvCircle(img, mouthpoint2, 1, CV_RGB(255,255, 255), 1, 8, 0);
		 cvCircle(img, mouthpoint3, 1, CV_RGB(255,255, 255), 1, 8, 0);
		 cvCircle(img, mouthpoint4, 1, CV_RGB(255,255, 255), 1, 8, 0);

          /* draw a red rectangle */
		 /*
          cvRectangle(img,
                      cvPoint(mouth_cord->x, mouth_cord->y),
                      cvPoint(mouth_cord->x + mouth_cord->width, mouth_cord->y + mouth_cord->height),
                      CV_RGB(255,255, 255),
                      1, 8, 0
                    );
					*/
        }
     //end mouth detection
         
}


/*Nose detection*/
void detectFaceComponets::detectNose( IplImage *img,CvRect *r)
{
  CvSeq *nose;
 
  //nose detection- set ROI
  cvSetImageROI(img,                    /* the source image */
                cvRect(r->x,            /* x = start from leftmost */
                       r->y , /* y = a few pixels from the top */
                       r->width,        /* width = same width with the face */
                       r->height  /* height = 1/3 of face height */
                      )
               );
         

  nose = cvHaarDetectObjects(img, /* the source image, with the estimated location defined */
                             cascade_nose,      /* the eye classifier */
                             storage,        /* memory buffer */
                             1.15, 3, 0,     /* tune for your app */
                             cvSize(25, 15)  /* minimum detection scale */
                            );

  for( int i = 0; i < 1; i++ )
      {
          CvRect *nose_cord = (CvRect*)cvGetSeqElem(nose, i);

		  /*darw nose points*/

		 CvPoint nosepoint2= cvPoint(nose_cord->x, nose_cord->y + nose_cord->height/2);
		 CvPoint nosepoint3= cvPoint(nose_cord->x + nose_cord->width, nose_cord->y + nose_cord->height/2);

		  pointsArry[9].x=nosepoint2.x;
		  pointsArry[9].y=nosepoint2.y;
		  pointsArry[10].x=nosepoint3.x;
		  pointsArry[10].y=nosepoint3.y;

		 cvCircle(img, nosepoint2, 1, CV_RGB(255,255, 255), 1, 8, 0);
		 cvCircle(img, nosepoint3, 1, CV_RGB(255,255, 255), 1, 8, 0);
          /* draw a red rectangle */
		  /*

          cvRectangle(img,
                      cvPoint(nose_cord->x, nose_cord->y),
                      cvPoint(nose_cord->x + nose_cord->width, nose_cord->y + nose_cord->height),
                      CV_RGB(0,255, 0),
                      1, 8, 0
                  );

      */  
	  }
}


/*Eyes detection*/
void detectFaceComponets::detectEyes( IplImage *img,CvRect *r)
{
    char *eyecascade;
    CvSeq *eyes;
    int eye_detect=0;
   

   //eye detection starts
  /* Set the Region of Interest: estimate the eyes' position */
   
    cvSetImageROI(img,                    /* the source image */
          cvRect
          (
              r->x,            /* x = start from leftmost */
              r->y + (r->height/5.5), /* y = a few pixels from the top */
              r->width,        /* width = same width with the face */
              r->height/3.0    /* height = 1/3 of face height */
          )
      );

      /* detect the eyes */
      eyes = cvHaarDetectObjects( img,            /* the source image, with the estimated location defined */
                                  cascade_e,      /* the eye classifier */
                                  storage,        /* memory buffer */
                                  1.15, 3, 0,     /* tune for your app */
                                  cvSize(25, 15)  /* minimum detection scale */
                                );
   
      //printf("\no of eyes detected are %d",eyes->total);
   
     
        /* draw a rectangle for each detected eye */
        for( int i = 0; i < 1; i++ )
          {
              eye_detect++;
              /* get one eye */
              CvRect *eye = (CvRect*)cvGetSeqElem(eyes, i);


			  CvPoint eyepoint[8];


		 eyepoint[0]= cvPoint(eye->x , eye->y + eye->height/2);
		 eyepoint[1]= cvPoint(eye->x + eye->width/6, eye->y + eye->height*1/4);
		 eyepoint[2]= cvPoint(eye->x + eye->width/6, eye->y + eye->height*3/4);
		 eyepoint[3]= cvPoint(eye->x + eye->width*2/6, eye->y + eye->height*2/4);
		 eyepoint[4]= cvPoint(eye->x + eye->width*4/6, eye->y + eye->height/2);
		 eyepoint[5]= cvPoint(eye->x +  + eye->width*5/6, eye->y + eye->height*1/4);
		 eyepoint[6]= cvPoint(eye->x + eye->width*5/6, eye->y + eye->height*3/4);
		 eyepoint[7]= cvPoint(eye->x + eye->width, eye->y + eye->height*2/4);
		 CvPoint nosepoint1= cvPoint(eye->x + eye->width/2, eye->y + eye->height/2);
		  ///////////////////

		 for(int i=0;i<8;i++){ 
		 pointsArry[i].x=eyepoint[i].x;
		 pointsArry[i].y=eyepoint[i].y;
		 }

		 pointsArry[8].x=nosepoint1.x;
		 pointsArry[8].y=nosepoint1.y;
		 /* draw points on mouth*/

		 cvCircle(img, eyepoint[0], 1, CV_RGB(255,255, 255), 1, 8, 0);
		 cvCircle(img, eyepoint[1], 1, CV_RGB(255,255, 255), 1, 8, 0);
		 cvCircle(img, eyepoint[2], 1, CV_RGB(255,255, 255), 1, 8, 0);
		 cvCircle(img, eyepoint[3], 1, CV_RGB(255,255, 255), 1, 8, 0);
		 cvCircle(img, eyepoint[4], 1, CV_RGB(255,255, 255), 1, 8, 0);
		 cvCircle(img, eyepoint[5], 1, CV_RGB(255,255, 255), 1, 8, 0);
		 cvCircle(img, eyepoint[6], 1, CV_RGB(255,255, 255), 1, 8, 0);
		 cvCircle(img, eyepoint[7], 1, CV_RGB(255,255, 255), 1, 8, 0);

		 cvCircle(img, nosepoint1, 1, CV_RGB(255,255, 255), 1, 8, 0);

              /* draw a red rectangle */
			  /*
                        cvRectangle(img,
                                    cvPoint(eye->x, eye->y),
                                    cvPoint(eye->x + eye->width, eye->y + eye->height),
                                    CV_RGB(0, 0, 255),
                                    1, 8, 0
                                   );
								   */
			int tot = 0;

			IplImage* hsv, * h, * s, * v;
	

			

			hsv = cvCreateImage(cvGetSize(img), 8, 3);
			h   = cvCreateImage(cvGetSize(img), 8, 1);
			s   = cvCreateImage(cvGetSize(img), 8, 1);
			v   = cvCreateImage(cvGetSize(img), 8, 1);

			cvCvtColor(img, hsv, CV_BGR2HSV);
			cvSplit(hsv, h, s, v, NULL);

			int gray = 0;
			int max = 0, mx =0 ,mGray =0, my=0, mxj = 0, myi = 0;
			int maxGray = 0;
			int maxX = 0;
			int dif = 0;
			
			for(int i = eye->y; i < eye->height + eye->y; i++) {

				for(int j = eye->x; j < eye->width + eye->x; j++) {
						
					gray = cvGetReal2D(v, i, j);
					//dif = cvGetReal2D(v, i, j) - cvGetReal2D(v, i, j-1);
					if(gray < 20){
						//maxGray = gray;
						myi = j;
						mxj =  i;

						if(mx < mxj) {
						mx = j;
						my = i;
						}

					}
					//tot = (eye->x + eye->width - j)*gray;
					//max = tot;
					/*if(max < tot) {
						max = tot;
						mx = i;
						mj = j;

					}*/
					
						
				}

				
			}

			cvMerge(h, s, v, NULL, img);
				cvCvtColor(img, img, CV_HSV2BGR);
				//cvCircle(img, cvPoint(eye->x, eye->y), 1, CV_RGB(0, 255, 0), -1, 8,0);
				cvCircle(img, cvPoint(mx, my), 1, CV_RGB(0, 255, 0), -1, 8,0);


           
}

}


void detectFaceComponets::detectFacialFeatures( IplImage *img,IplImage *temp_img,int img_no)
{
   
    char image[100],msg[100],temp_image[100];
    float m[6];
    double factor = 1;
    CvMat M = cvMat( 2, 3, CV_32F, m );
    int w = (img)->width;
    int h = (img)->height;
    CvSeq* faces;
    CvRect *r;

    m[0] = (float)(factor*cos(0.0));
    m[1] = (float)(factor*sin(0.0));
    m[2] = w*0.5f;
    m[3] = -m[1];
    m[4] = m[0];
    m[5] = h*0.5f;
   
    cvGetQuadrangleSubPix(img, temp_img, &M);
    CvMemStorage* storage=cvCreateMemStorage(0);
    cvClearMemStorage( storage );
   
    if( cascade )
        faces = cvHaarDetectObjects(img,cascade, storage, 1.2, 2, CV_HAAR_DO_CANNY_PRUNING, cvSize(20, 20));
    else
        printf("\nFrontal face cascade not loaded\n");

    //printf("\n no of faces detected are %d",faces->total);
   

    /* for each face found, draw a red box */
    for(int i = 0 ; i < 1 ; i++ )
    {       
        r = ( CvRect* )cvGetSeqElem( faces, i );

		/* draw points on overall face*/
		 CvPoint facepoint1= cvPoint(r->x , r->y + r->height/2);
		 CvPoint facepoint2= cvPoint(r->x + r->width, r->y + r->height/2);
		 CvPoint facepoint3= cvPoint(r->x + r->width/2, r->y + r->height/5);
		 CvPoint facepoint4= cvPoint(r->x + r->width/2, r->y + r->height*9/8);
		  ///////////////////

		 pointsArry[15].x=facepoint1.x;
		 pointsArry[15].y=facepoint1.y;
		 pointsArry[16].x=facepoint1.x;
		 pointsArry[16].y=facepoint1.y;
		 pointsArry[17].x=facepoint1.x;
		 pointsArry[17].y=facepoint1.y;
		 pointsArry[18].x=facepoint1.x;
		 pointsArry[18].y=facepoint1.y;
		 /* draw points on overall face*/

		 cvCircle(img, facepoint1, 1, CV_RGB(255,255, 255), 1, 8, 0);
		 cvCircle(img, facepoint2, 1, CV_RGB(255,255, 255), 1, 8, 0);
		 cvCircle(img, facepoint3, 1, CV_RGB(255,255, 255), 1, 8, 0);
		 cvCircle(img, facepoint4, 1, CV_RGB(255,255, 255), 1, 8, 0);


		/*draw rectangle for face*/
		/*
        cvRectangle( img,cvPoint( r->x, r->y ),cvPoint( r->x + r->width, r->y + r->height ),
                     CV_RGB( 255, 0, 0 ), 1, 8, 0 );   
   


        printf("\n face_x=%d face_y=%d wd=%d ht=%d",r->x,r->y,r->width,r->height);

		*/
       
        detectEyes(img,r);
        /* reset region of interest */
        cvResetImageROI(img);
        detectNose(img,r);
        cvResetImageROI(img);
        detectMouth(img,r);
        cvResetImageROI(img);
    }
    /* reset region of interest */
      cvResetImageROI(img);

      if(faces->total>0)
        {
            //sprintf(image,"D:\\face_output\\%d.jpg",img_no);
            cvSaveImage( "Ageprogression\\pil.bmp", img );
        }
}


void detectFaceComponets::loadFaceImages()
{

	
   CvCapture *capture;
	IplImage  *img,*temp_img;
	int       key;

	char image[100],temp_image[100];


    /* load the classifier
       note that I put the file in the same directory with
       this code */
    storage = cvCreateMemStorage( 0 );
        cascade = ( CvHaarClassifierCascade* )cvLoad( face_cascade, 0, 0, 0 );
    cascade_e = ( CvHaarClassifierCascade* )cvLoad( eye_cascade, 0, 0, 0 );
    cascade_nose = ( CvHaarClassifierCascade* )cvLoad( nose_cascade, 0, 0, 0 );
    cascade_mouth = ( CvHaarClassifierCascade* )cvLoad( mouth_cascade, 0, 0, 0 );


   
    if( !(cascade || cascade_e ||cascade_nose||cascade_mouth) )
        {
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
        //return -1;
        }
   
    //for(int j=1;j<4;j++)
    //{

         //sprintf(image,"res\\%d.bmp",2);
       
        img=cvLoadImage("res\\c20.bmp");
        temp_img=cvLoadImage("res\\c20.bmp");
       
        if(!img)
        {
        printf("Could not load image file and trying once again: %s\n",image);
        }
        printf("\n curr_image = %s",image);
     
        detectFacialFeatures(img,temp_img,1);
    //}
 

    cvReleaseHaarClassifierCascade( &cascade );
    cvReleaseHaarClassifierCascade( &cascade_e );
   
    cvReleaseHaarClassifierCascade( &cascade_nose );
    cvReleaseHaarClassifierCascade( &cascade_mouth );
    cvReleaseMemStorage( &storage );
   
	cvShowImage("sdfs", img);
    
   

   
}