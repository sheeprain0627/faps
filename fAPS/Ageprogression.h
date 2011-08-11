#pragma once


class Ageprogression
{
public:
	Ageprogression(void);
	~Ageprogression(void);
void texureEnhancePrototype(float p);
void applyIbsdt(float q);

void setSigma(float q);
void mergeImage(IplImage* target, IplImage* source, int x, int y) ;
void cvOverlayImage(IplImage* src, IplImage* overlay, CvPoint location, CvScalar S, CvScalar D);
//float getIbsdt()const;
//void setIbsdt(float r);
private:
	float sigma;
	//float ibsdt;

};