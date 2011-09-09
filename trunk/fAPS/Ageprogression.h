#pragma once


class Ageprogression
{
public:
	Ageprogression(void);
	~Ageprogression(void);
void texureEnhancePrototype(float p,int age);
void applyIbsdt(float q);

void setSigma(float q);
void mergeImage(IplImage* target, IplImage* source, int x, int y) ;
void cvOverlayImage(IplImage* src, IplImage* overlay, CvPoint location, CvScalar S, CvScalar D);
private:
	float sigma;
	

};