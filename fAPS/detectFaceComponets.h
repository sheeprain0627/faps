#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "highgui.h"
using namespace cv;

/*
* to detect facial components such as eye, nose and mouth
*/
class detectFaceComponets{

public:
	void loadFaceImages(IplImage *img);
	void detectFacialFeatures( IplImage *img,IplImage *temp_img,int img_no);
	void detectEyes( IplImage *img,CvRect *r);
	void detectNose( IplImage *img,CvRect *r);
	void detectMouth( IplImage *img,CvRect *r);
	int *getFeaturePoints_x();
	int *getFeaturePoints_y();
	CvPoint *getFeaturePoints(); /*!< float value sigma. */
};