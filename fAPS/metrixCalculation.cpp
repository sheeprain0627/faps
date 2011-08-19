#include "StdAfx.h"
#include "metrixCalculation.h"
#include <stdio.h>
//#include <cvcam.h>   
#include <cv.h>   
#include "highgui.h"   
//#include <stdio.h>   
#include <vector>   
#include <math.h> 
#include <iostream>
//#include <cv.h>

float **metrixCalculation::MatrixMultiplication(float **a, float **b){
	

 // int a[3][3] , b[3][3] , c[3][3];
	//float **c;
	float **c= new float*[3];

	for(int i=0; i<3;i++)
	{
c[i]= new float[3];
	}

  int i , j , k;
 // cout<<"Enter Matrix A";
  //for( i = 0 ; i < 3 ; i++)
    // for( j = 0 ; j < 3 ; j++)
      //  cin>>a[i][j];
 // cout<<"Enter Matrix B";
 // for( i = 0 ; i < 3 ; i++)
    // for( j = 0 ; j < 3 ; j++)
      //  cin>>b[i][j];
  for( i = 0 ; i < 3 ; i++)
     for( j = 0 ; j < 3 ; j++)
     {
        c[i][j] = 0;
        for( k = 0 ;k < 3 ; k++)
           c[i][j] += a[i][k]*b[k][j];
     }
 // cout<<"The resultant matrix is ";
 // for( i = 0 ; i < 3 ; i++)
  //{
    // for( j = 0 ; j < 3 ; j++)
       // cout<<a[i][j]<<" ";
     //cout<<endl;
 // }

	  return c;
}



float **metrixCalculation::MatrixInversion(float **A, int order)
{
    
	//float **Y;
	float **Y= new float*[3];

	for(int i=0; i<3;i++)
	{
Y[i]= new float[3];
	}

	// get the determinant of a
    double det = 1.0/CalcDeterminant(A,order);

    // memory allocation
    float *temp = new float[(order-1)*(order-1)];
    float **minor = new float*[order-1];
    for(int i=0;i<order-1;i++)
        minor[i] = temp+(i*(order-1));

    for(int j=0;j<order;j++)
    {
        for(int i=0;i<order;i++)
        {
            // get the co-factor (matrix) of A(j,i)
            GetMinor(A,minor,j,i,order);
            Y[i][j] = det*CalcDeterminant(minor,order-1);
            if( (i+j)%2 == 1)
                Y[i][j] = -Y[i][j];
        }
    }

    // release memory
    //delete [] minor[0];
    delete [] temp;
    delete [] minor;
return Y;
}

// calculate the cofactor of element (row,col)
int metrixCalculation::GetMinor(float **src, float **dest, int row, int col, int order)
{
    // indicate which col and row is being copied to dest
    int colCount=0,rowCount=0;

    for(int i = 0; i < order; i++ )
    {
        if( i != row )
        {
            colCount = 0;
            for(int j = 0; j < order; j++ )
            {
                // when j is not the element
                if( j != col )
                {
                    dest[rowCount][colCount] = src[i][j];
                    colCount++;
                }
            }
            rowCount++;
        }
    }

    return 1;
}

// Calculate the determinant recursively.
double metrixCalculation::CalcDeterminant( float **mat, int order)
{
    // order must be >= 0
	// stop the recursion when matrix is a single element
    if( order == 1 )
        return mat[0][0];

    // the determinant value
    float det = 0;

    // allocate the cofactor matrix
    float **minor;
    minor = new float*[order-1];
    for(int i=0;i<order-1;i++)
        minor[i] = new float[order-1];

    for(int i = 0; i < order; i++ )
    {
        // get minor of element (0,i)
        GetMinor( mat, minor, 0, i , order);
        // the recusion is here!

        det += (i%2==1?-1.0:1.0) * mat[0][i] * CalcDeterminant(minor,order-1);
        //det += pow( -1.0, i ) * mat[0][i] * CalcDeterminant( minor,order-1 );
    }

    // release memory
    for(int i=0;i<order-1;i++)
        delete [] minor[i];
    delete [] minor;

    return det;
}


//float **metrixCalculation::WrapFuction(int trg_img_cordinate_x[13],int trg_img_cordinate_y[13],int db_img_cordinate_x[13],int db_img_cordinate_y[13] ){
	float **metrixCalculation::WrapFuction(){
		int trg_img_cordinate_x[19]={65,80,80,102,132,147,149,165,116,101,132,88,119,117,144,33,199,117,117};
		int trg_img_cordinate_y[19]={127,117,131,127,127,113,130,124,121,171,169,201,193,210,201,142,142,102,253};
		int db_img_cordinate_x[19]={62,79,80,104,136,156,157,173,120,99,144,87,120,120,148,35,196,119,117};
		int db_img_cordinate_y[19]={121,111,130,127,124,110,129,120,112,171,172,202,191,215,198,136,140,88,256};
	
	//float **wrapMetrix;

	float **wrapMetrix= new float*[3]; //assgin 1st dimention
	for(int i=0; i<3;i++)
	{
wrapMetrix[i]= new float[3];
	}
	//float **QPt;
	//float **PPt;
	float **QPt= new float*[3]; //assgin 1st dimention
	for(int i=0; i<3;i++)
	{
QPt[i]= new float[3];
	}



	float **PPt= new float*[3];

	for(int i=0; i<3;i++)
	{
PPt[i]= new float[3];
	}

	float **PPt_inv=new float*[3];
	for(int i=0; i<3;i++)
	{
PPt_inv[i]= new float[3];
	}
	
	
	QPt[0][0]=0.0;
		QPt[0][1]=0.0;
		QPt[0][2]=0.0;
		QPt[1][0]=0.0;
		QPt[1][1]=0.0;
		QPt[1][2]=0.0;
		QPt[2][0]=0.0;
		QPt[2][1]=0.0;
		QPt[2][2]=19.0;

		PPt[0][0]=0.0;
		PPt[0][1]=0.0;
		PPt[0][2]=0.0;
		PPt[1][0]=0.0;
		PPt[1][1]=0.0;
		PPt[1][2]=0.0;
		PPt[2][0]=0.0;
		PPt[2][1]=0.0;
		PPt[2][2]=19.0;

		
	
	for(int i=0; i<19;i++){

		QPt[0][0]=QPt[0][0] + trg_img_cordinate_x[i]*db_img_cordinate_x[i];
		QPt[0][1]=QPt[0][1] + trg_img_cordinate_x[i]*db_img_cordinate_y[i];
		QPt[0][2]=QPt[0][2] + trg_img_cordinate_x[i];
		QPt[1][0]=QPt[1][0] + trg_img_cordinate_y[i]*db_img_cordinate_x[i];
		QPt[1][1]=QPt[1][1] + trg_img_cordinate_y[i]*db_img_cordinate_y[i];
		QPt[1][2]=QPt[1][2] + trg_img_cordinate_y[i];
		QPt[2][0]=QPt[2][0] + db_img_cordinate_x[i];
		QPt[2][1]=QPt[2][1] + db_img_cordinate_y[i];
		//QPt[2][2]=19;


		PPt[0][0]=QPt[0][0] + db_img_cordinate_x[i]*db_img_cordinate_x[i];
		PPt[0][1]=QPt[0][1] + db_img_cordinate_x[i]*db_img_cordinate_y[i];
		PPt[0][2]=QPt[0][2] + db_img_cordinate_x[i];
		PPt[1][0]=QPt[1][0] + db_img_cordinate_x[i]*db_img_cordinate_y[i];
		PPt[1][1]=QPt[1][1] + db_img_cordinate_y[i]*db_img_cordinate_y[i];
		PPt[1][2]=QPt[1][2] + db_img_cordinate_y[i];
		PPt[2][0]=QPt[2][0] + db_img_cordinate_x[i];
		PPt[2][1]=QPt[2][1] + db_img_cordinate_y[i];
		//PPt[2][2]=19;

		
	}

	PPt_inv=MatrixInversion(PPt, 3);
		wrapMetrix=MatrixMultiplication(QPt, PPt_inv);
return wrapMetrix;
}


/*
Function takes OpenCV image as input and dumps its pixels to a file specified by filename in function arguments.
*/
int metrixCalculation::WritePixelsToFile(IplImage *img,const char *filename)
{
  /*open a file in text mode with write permissions.*/
 FILE *file = fopen(filename, "wt");
 if(file==NULL)
 {
  /*If unable to open the specified file display error and return.*/
  perror("Unable to open specified file");
  return -1;
  }
  int i,j;
  CvScalar **s;
  CvSize size=cvGetSize(img);
  s= new CvScalar*[size.height];
  for(int i=0; i<size.height;i++)
	{
		s[i]= new CvScalar[size.width];
	}

  float **W=new float*[3];
	for(int i=0; i<3;i++)
	{
W[i]= new float[3];
	}

	 float **W_inv=new float*[3];
	for(int i=0; i<3;i++)
	{
W_inv[i]= new float[3];
	}

  W=WrapFuction(); //get the wrappin metrix
  W_inv=MatrixInversion(W, 3); // inverse the metrix
  for(i=0;i< size.height;i++)
     {
      for(j=0;j< size.width;j++)
        {

			int X_pixel=j*W_inv[0][0]+i*W_inv[0][1]+ W_inv[0][2]; // reverce mapping value for x coordinate
			int Y_pixel=j*W_inv[1][0]+i*W_inv[1][1]+ W_inv[1][2];  // reverce mapping value for x coordinate
         s[i][j]=cvGet2D(img,X_pixel,Y_pixel); // get the (i,j) pixel value

         fprintf (file,"%f\t",s[i][j].val[0]); // dump the (i,j) pixel value in file 
        }                         
      fprintf(file,"\n");//write new line in file to seperate rows.         
     }
     /*release the file pointer.*/
 fclose(file);
 return 1;
} 

void metrixCalculation::CalFundermentalMatrix(IplImage *src,IplImage *dst)
{
	int point_count = 9;
CvMat* points1;
CvMat* points2;
CvMat* status;
CvMat* fundamental_matrix;
//IplImage *src, *dst;
int trg_img_cordinate_x[19]={65,80,80,102,132,147,149,165,116,101,132,88,119,117,144,33,199,117,117};
int trg_img_cordinate_y[19]={127,117,131,127,127,113,130,124,121,171,169,201,193,210,201,142,142,102,253};
int db_img_cordinate_x[19]={62,79,80,104,136,156,157,173,120,99,144,87,120,120,148,35,196,119,117};
int db_img_cordinate_y[19]={121,111,130,127,124,110,129,120,112,171,172,202,191,215,198,136,140,88,256};

points1 = cvCreateMat(1,point_count,CV_32FC2);
points2 = cvCreateMat(1,point_count,CV_32FC2);
status = cvCreateMat(1,point_count,CV_8UC1);

/* Fill the points here ... */

for( int i = 0; i < point_count; i++ )
{
    points1->data.db[i*2] = trg_img_cordinate_x[i];
    points1->data.db[i*2+1] = trg_img_cordinate_y[i];
    points2->data.db[i*2] = db_img_cordinate_x[i];
    points2->data.db[i*2+1] = db_img_cordinate_y[i];
}


/*
 cvmSet(points1,0,0,31); cvmSet(points1,1,0,34);
cvmSet(points1,0,1,165); cvmSet(points1,1,1,85);
 cvmSet(points1,0,2,51); cvmSet(points1,1,2,171);
 cvmSet(points1,0,3,174); cvmSet(points1,1,3,221);
 cvmSet(points1,0,4,210); cvmSet(points1,1,4,17);
 cvmSet(points1,0,5,290); cvmSet(points1,1,5,66);
 cvmSet(points1,0,6,283); cvmSet(points1,1,6,106);
 cvmSet(points1,0,7,89); cvmSet(points1,1,7,128);
 cvmSet(points1,0,8,129); cvmSet(points1,1,8,86);

 cvmSet(points2,0,0,88); cvmSet(points2,1,0,23);
 cvmSet(points2,0,1,203); cvmSet(points2,1,1,85);
 cvmSet(points2,0,2,101); cvmSet(points2,1,2,158);
 cvmSet(points2,0,3,205); cvmSet(points2,1,3,223);
 cvmSet(points2,0,4,154); cvmSet(points2,1,4,11);
 cvmSet(points2,0,5,350); cvmSet(points2,1,5,98);
 cvmSet(points2,0,6,289); cvmSet(points2,1,6,123);
 cvmSet(points2,0,7,136); cvmSet(points2,1,7,122);
 cvmSet(points2,0,8,170); cvmSet(points2,1,8,85);

 cvmSet(status,0,0,0);
 cvmSet(status,0,1,0);
 cvmSet(status,0,2,0);
 cvmSet(status,0,3,0);
 cvmSet(status,0,4,0);
 cvmSet(status,0,5,0);
 cvmSet(status,0,6,0);
 cvmSet(status,0,7,0);
 cvmSet(status,0,8,0);

 */
 
 //float *PPt_inv=new float[9];

	//for(int i=0; i<3;i++)
	//{
//PPt_inv[i]= new float[3];
//	}

fundamental_matrix = cvCreateMat(3,3,CV_32SC1);
//cvFindFundamentalMatrix( trg_img_cordinate_x,trg_img_cordinate_x,9,CV_FM_RANSAC,PPt_inv);
int fm_count = cvFindFundamentalMat( points1,points2,fundamental_matrix,CV_FM_RANSAC,1.0,0.99,status );
//std::cout<<"ff";


cvWarpPerspective( src, dst, fundamental_matrix);
cvNamedWindow("wrppedImg",1);
cvShowImage("wrppedImg",dst);


}