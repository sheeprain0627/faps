#include <cv.h>
#include <cvaux.h>
class metrixCalculation{

public:
	float **MatrixMultiplication(float **a, float **b);
	float **MatrixInversion(float **A, int order);
	int GetMinor(float **src, float **dest, int row, int col, int order);
	double CalcDeterminant( float **mat, int order);
	//float **WrapFuction(int img_cordinate_x[],int img_cordinate_y[],int db_img_cordinate_x[],int db_img_cordinate_y[] );
    float **WrapFuction();
    
	int WritePixelsToFile(IplImage *img,const char *filename,CvMat* mat);
	void CalFundermentalMatrix(IplImage *src,IplImage *dst);
};

//void CalFundermentalMatrix(IplImage *src,IplImage *dst);