#pragma once


class Ageprogression
{
public:
	Ageprogression(void);
	~Ageprogression(void);
void texureEnhancePrototype(float p);
void applyIbsdt(float q);

void setSigma(float q);
//float getIbsdt()const;
//void setIbsdt(float r);
private:
	float sigma;
	//float ibsdt;

};