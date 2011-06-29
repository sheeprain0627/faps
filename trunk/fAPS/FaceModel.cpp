#include "StdAfx.h"
#include "FaceModel.h"
#include <windows.h>
//#include <GL/glut.h>
#include <GL/GL.h>
#include <GL/GLU.H>
#include<iostream>
#include <string>
#include <fstream>

using namespace std; 


#define MAX_VERTICES 4000 // Max number of vertices (for each object)
#define MAX_POLYGONS 4000 // Max number of polygons (for each object)

//polygon_type kk;  

//FaceModel::obj_type cube;

FaceModel::FaceModel(void)
{

}


FaceModel::~FaceModel(void)
{
}


/*
 * ---------------- www.spacesimulator.net --------------
 *   ---- Space simulators and 3d engine tutorials ----
 *
 * Author: Damiano Vitulli
 *
 * This program is released under the BSD licence
 * By using this program you agree to licence terms on spacesimulator.net copyright page
 *
 * Tutorial 2: 3d engine - Start to draw using OpenGL!
 * 
 *
 * To compile this project you must include the following libraries:
 * opengl32.lib,glu32.lib,glut.lib
 * You need also the header file glut.h in your compiler directory.
 *  
 */





/**********************************************************
 *
 * TYPES DECLARATION
 *
 *********************************************************/

// Our vertex type




/**********************************************************
 *
 * VARIABLES DECLARATION
 *
 *********************************************************/



//vertex_type vertex[MAX_VERTICES]; 
  //  polygon_type polygon[MAX_POLYGONS];


// read the vertices and polycons from the file


	/*

void loadData(){
ifstream myfile("testfile.txt");
    int a = 0;
    int b = 0;
    if(!myfile) //Always test the file open.
    {
                cout<<"Error opening output file"<<endl;
                system("pause");
                
    }
	string str[30][3];
    while(!myfile.eof())
    {
      getline(myfile,str[a][b],' ');
      if(a ==29)
      {
           a=0;
           ++b;
           getline(myfile,str[a][b],' ');
      }
      a++;
    }
      
}

*/
	
 FaceModel::obj_type FaceModel::defineObject(void){

	obj_type object = 
{
    {
        1.3,1.7,1.0,1.4,1.3,0.46100003,1.5,1.4,1.1,2.1,1.1,0.947,-0.0327,2.5,-0.81600004,-0.0327,1.9,-1.3,0.38199997,1.9,-1.4,0.491,2.5,-0.72400004,0.774,1.5999999,-1.1,0.81799996,2.3,-0.607,1.1,1.4,-0.458,1.1,1.1,-0.72400004,1.4,0.575,-0.28100002,1.1999999,1.9,0.456,1.5999999,2.1,0.916,1.4,2.3999999,0.51600003,1.0,2.7,-0.338,0.578,2.8,-0.467,-0.0327,3.0,-0.572,2.0,3.3000002,-0.0959,2.6,2.5,0.79,3.0,3.1999998,0.345,3.7,2.3999999,1.1,3.8999999,2.8,0.973,4.5,2.1,1.8000001,4.7,2.3,1.8000001,4.7999997,1.8000001,2.3,5.0,2.0,2.5,5.2999997,1.5,3.3000002,4.7,1.1999999,2.3999999,4.7999997,0.57,2.2,5.2999997,0.817,3.1999998,3.8,0.91899997,1.5,2.1,0.148,0.285,3.1999998,0.144,0.726,3.1999998,0.927,1.1,4.0,0.297,1.1999999,5.6,-1.0,3.1999998,5.2,-1.0,2.0,4.2,-1.0,0.758,3.3000002,-1.1,0.218,1.5999999,-1.1,-0.414,1.1999999,-0.126,-1.0,0.709,0.79499996,-1.9,0.927,0.41700003,-1.4,0.927,0.0207,-1.9,1.4,-0.652,-1.8000001,1.1,-0.539,-2.3999999,1.4,-1.1,-1.5999999,1.0,-1.8000001,-1.4,1.3,-2.0,-1.1,1.9,-2.5,-1.0,2.8999999,-2.7,-0.0201,3.7,-4.0,0.665,4.0,-2.3,0.733,1.1,-2.3999999,-1.5999999,0.556,-1.9,-1.9,0.86099994,-1.5,-1.8000001,0.338,1.1,-2.2,-0.0327,1.1,-2.3,-0.0327,0.172,-3.3000002,0.31599998,0.43,-2.8999999,0.68700004,0.453,-2.2,0.73,0.072,-2.8,0.752,-0.387,-3.1,0.338,-0.0747,-3.3000002,1.1999999,-1.1999999,-1.9,1.1999999,-1.1,-2.1,0.948,-0.97999996,-2.3999999,0.839,-1.1,-2.6,0.665,-1.1999999,-2.5,0.425,-0.76600003,-3.1999998,0.338,-1.7,-2.3,0.491,-1.5,-2.3,0.31599998,-2.0,-2.0,0.621,-1.7,-2.0,-0.0327,-0.32999998,-3.6000001,0.35999998,-0.377,-3.4,-0.0327,-0.972,-3.3000002,-0.0109,-2.0,-2.1,-0.0109,-2.5,-1.9,0.273,-2.5,-1.9,0.578,-2.3999999,-1.8000001,-0.0109,-3.1,-2.1,0.31599998,-3.1,-2.1,0.796,-3.0,-2.0,1.3,-3.1,-1.7,2.0,-3.3000002,-1.1999999,2.7,-3.6000001,-0.374,3.0,-4.0,-0.171,2.5,-4.4,-0.456,2.3999999,-4.0,-0.30400002,2.0,-4.3,-1.1,0.0109,-5.2,-1.5,0.38199997,-4.4,-2.1,-0.0109,-4.4,-2.1,0.709,-5.1,-1.5,0.752,-4.4,-2.0,1.4,-4.3,-1.5999999,1.4,-5.0,-1.4,1.9,-4.7999997,-1.1,2.5,-5.4,-0.40600002,1.7,-5.5,-0.973,1.3,-5.5,-1.1999999,0.68700004,-5.4,-1.4,0.0109,-6.2,-1.7,0.81799996,-6.2,-1.5999999,1.3,-6.2,-1.3,1.7,-6.2,-1.1,2.3999999,-6.2,-0.361,3.3000002,-6.2,0.647,3.4,-5.2999997,0.65800005,5.1,-2.1,2.0,5.7,-2.0,3.3000002,5.6,-3.1999998,3.3000002,4.9,-3.6000001,2.1,5.2,-4.5,3.3000002,4.5,-5.1,2.3,5.0,-5.1,3.1999998,4.2,-6.0,2.3,4.7,-6.1000004,3.1,4.0,-6.8,2.3999999,3.5,-7.5,2.6,3.7,-7.5,3.1,2.7,-8.3,3.0,2.8,-7.7,0.88100004,2.1,-8.2,0.929,4.3,-6.9,3.0,4.0,-5.2,1.5999999,3.1999998,-6.9,0.686,2.5,-7.0,-0.42800003,0.0109,-7.2000003,-1.8000001,0.73,-7.2000003,-1.7,0.73,-7.9,-1.1999999,0.0109,-7.9,-1.3,0.0327,-8.4,-0.206,0.752,-8.4,-0.25800002,1.4,-8.2,-0.307,1.3,-7.6,-1.1999999,1.3,-7.2000003,-1.4,1.7,-7.1,-1.1999999,2.1,-7.7,-0.371,0.0327,-8.6,0.90400004,0.796,-8.5,0.93500006,0.0327,-9.0,2.8999999,0.905,-8.9,2.7,1.7,-8.7,2.8999999,1.5,-8.4,0.938,5.1,2.2,2.6,4.9,2.7,1.9,5.2999997,2.8999999,3.1999998,4.9,3.4,2.3999999,4.1,3.3000002,0.906,4.0,3.8999999,1.1999999,5.1,3.8999999,3.1999998,4.7999997,4.0,2.7,4.9,4.6,3.1,3.8999999,5.0,1.9,3.8999999,4.4,1.5999999,3.1,3.6000001,0.303,3.1,4.2,0.483,3.0,4.7,0.752,3.0,5.2999997,1.1,3.0,5.8999996,1.4,3.8999999,5.7,2.1,4.5,5.5,2.8999999,3.8,6.6000004,2.7,2.8999999,6.8,1.9,2.2,6.1000004,0.86300004,3.1999998,7.2000003,2.6,2.7,7.7999997,2.6,2.3,8.3,2.8999999,1.9,8.4,2.8,2.0,7.9,2.1,2.1,8.6,3.6000001,1.5999999,8.8,3.5,1.0,8.9,3.5,1.1,8.7,2.6,0.447,9.0,3.4,0.578,8.8,2.5,-0.0545,9.0,3.4,-0.076299995,8.8,2.5,-0.076299995,8.3,1.7,0.68700004,8.3,1.7,1.3,8.2,1.8000001,2.2,7.0,1.3,2.1,5.4,0.584,2.2,4.7999997,0.24399999,2.1,4.5,0.0516,2.2,3.8999999,-0.0607,1.3,3.4,-0.352,1.3,4.0,-0.35,0.68700004,3.5,-0.425,-0.0327,3.6000001,-0.462,0.752,4.1,-0.40199998,-0.0545,4.1,-0.44599998,1.3,4.6,-0.18200001,0.774,4.5,-0.22299999,-0.0545,4.6,-0.22600001,0.752,5.0,0.00648,-0.0545,5.0,-0.0181,0.796,5.5,0.22,-0.0545,5.5,0.193,0.81799996,6.2,0.429,-0.0545,6.2,0.40100002,0.752,7.7999997,1.1999999,-0.0545,7.3,0.801,0.752,7.2000003,0.792,1.4,7.1,0.955,1.3,6.1000004,0.527,1.3,5.5,0.33100003,1.3,4.9,0.0311,4.3,1.8000001,1.7,4.2,1.3,1.5,3.6000001,1.9,1.0,3.3000002,1.3,0.985,2.5,2.0,0.78000003,2.3999999,1.5,0.80300003,2.0,1.5999999,0.85600007,-1.5999999,1.3,1.1,-1.5,1.1999999,0.464,-1.4,1.5999999,1.0,-2.1,1.1,0.972,-0.578,2.5,-0.72400004,-0.469,1.9,-1.4,-0.905,2.2,-0.60400003,-0.86099994,1.5999999,-1.1,-1.1,1.3,-0.45499998,-1.1,1.0,-0.72099996,-1.5,0.554,-0.278,-1.1999999,1.9,0.459,-1.5999999,2.1,0.91899997,-1.5,2.3999999,0.519,-1.1,2.7,-0.335,-0.665,2.8,-0.467,-2.1,3.3000002,-0.0713,-2.7,2.5,0.81799996,-3.1,3.1,0.372,-4.0,2.7,1.0,-3.8,2.3999999,1.1,-4.7999997,2.3,1.9,-4.5,2.0,1.8000001,-5.0,1.9,2.5,-4.7999997,1.7,2.3999999,-5.2999997,1.5,3.3000002,-4.7,1.1999999,2.5,-5.4,0.755,3.1999998,-4.9,0.508,2.2,-3.8999999,0.858,1.5999999,-2.2,0.13,0.31,-3.3000002,0.104,0.754,-3.1999998,0.88600004,1.1999999,-4.0,0.236,1.1999999,-5.6,-1.1,3.3000002,-5.2,-1.1,2.1,-4.2,-1.1,0.788,-3.3000002,-1.1,0.24499999,-1.7,-1.1999999,-0.41099998,-1.1999999,-0.148,-1.0,-0.99200004,0.396,-1.4,-0.774,0.79499996,-1.9,-0.99200004,-9.35E-4,-1.9,-1.4,-0.673,-1.8000001,-1.1999999,-0.561,-2.3999999,-1.5,-1.1999999,-1.5999999,-1.1,-1.8000001,-1.4,-1.4,-2.1,-1.1,-1.9,-2.5,-1.0,-2.8999999,-2.7,0.0075299996,-4.0,-2.3,0.76399994,-3.7,-4.0,0.69200003,-1.1,-2.5,-1.5999999,-0.59999996,-1.9,-1.9,-0.905,-1.5999999,-1.8000001,-0.425,1.1,-2.2,-0.38199997,0.43,-2.8999999,-0.752,0.453,-2.2,-0.796,0.050400004,-2.8,-0.81799996,-0.40800002,-3.0,-0.403,-0.0747,-3.3000002,-1.1999999,-1.3,-1.9,-1.1999999,-1.1,-2.1,-0.99200004,-1.0,-2.3999999,-0.88299996,-1.1,-2.6,-0.491,-0.76600003,-3.1999998,-0.709,-1.1999999,-2.5,-0.534,-1.5,-2.3,-0.38199997,-1.7,-2.3,-0.35999998,-2.0,-2.0,-0.665,-1.7,-2.0,-0.425,-0.377,-3.4,-0.294,-2.5,-1.9,-0.59999996,-2.3999999,-1.8000001,-0.338,-3.1,-2.1,-0.81799996,-3.1,-2.0,-1.3,-3.1,-1.7,-2.0,-3.3000002,-1.1999999,-2.7,-3.7,-0.34600002,-3.0,-4.0,-0.143,-2.5,-4.5,-0.42800003,-2.3999999,-4.0,-0.276,-2.0,-4.3,-1.1,-0.38199997,-4.4,-2.1,-0.709,-5.1,-1.5,-0.752,-4.4,-2.0,-1.4,-4.4,-1.5999999,-1.4,-5.0,-1.4,-1.9,-4.7999997,-1.1,-2.5,-5.5,-0.378,-1.5999999,-5.5,-0.97,-1.3,-5.5,-1.1999999,-0.665,-5.4,-1.4,-0.796,-6.2,-1.5999999,-1.3,-6.2,-1.3,-1.7,-6.2,-1.1,-2.3999999,-6.3,-0.333,-3.1999998,-6.2,0.675,-3.3000002,-5.4,0.686,-5.1,-2.2,2.1,-5.7,-2.1,3.3000002,-5.6,-3.3000002,3.4,-4.9,-3.6000001,2.2,-5.2,-4.6,3.3000002,-5.0,-5.1,3.3000002,-4.4,-5.1,2.3,-4.6,-6.2,3.1999998,-4.2,-6.1000004,2.3999999,-3.7,-7.6,3.1,-3.4,-7.6,2.6,-3.8999999,-6.9,2.5,-2.6,-8.3,3.0,-2.8,-7.7,0.909,-2.0,-8.2,0.954,-4.2,-7.0,3.1,-4.0,-5.2999997,1.5999999,-3.1,-7.0,0.713,-2.3999999,-7.0,-0.39999998,-0.68700004,-7.2000003,-1.7,-0.68700004,-7.9,-1.1999999,-0.68700004,-8.4,-0.25800002,-1.4,-8.2,-0.30400002,-1.3,-7.7,-1.1,-1.3,-7.2000003,-1.4,-1.7,-7.1,-1.1999999,-2.0,-7.7,-0.34600002,-0.73,-8.5,0.93500006,-0.81799996,-8.9,2.7,-1.4,-8.4,0.941,-1.5999999,-8.7,2.8999999,-5.0,2.6,1.9,-5.2,2.1,2.7,-5.2999997,2.8,3.1999998,-4.9,3.3000002,2.3999999,-4.1,3.8,1.1999999,-4.2,3.1999998,0.937,-4.9,4.0,2.8,-5.1,3.8,3.1999998,-5.0,4.6,3.1,-4.0,4.4,1.5999999,-4.0,5.0,1.9,-3.1999998,3.6000001,0.32999998,-3.1999998,4.2,0.51,-3.1,4.6,0.78000003,-3.1,5.2,1.1,-4.0,5.6,2.2,-3.1,5.8999996,1.4,-4.6,5.4,3.0,-3.8999999,6.5,2.7,-3.1,6.8,1.9,-2.3,6.0,0.888,-3.4,7.1,2.6,-2.8,7.7,2.6,-2.1,7.9,2.1,-2.0,8.4,2.8,-2.3999999,8.2,2.8999999,-1.7,8.7,3.5,-2.2,8.6,3.6000001,-1.3,8.6,2.6,-1.1999999,8.9,3.5,-0.73,8.8,2.5,-0.578,9.0,3.4,-0.839,8.3,1.7,-1.4,8.2,1.8000001,-2.3,7.0,1.3,-2.2,5.4,0.60899997,-2.3,4.7999997,0.268,-2.2,4.5,0.076299995,-2.3,3.8,-0.0361,-1.4,3.4,-0.34899998,-1.4,4.0,-0.347,-0.774,3.5,-0.425,-0.86099994,4.1,-0.39900002,-1.4,4.6,-0.17899999,-0.88299996,4.5,-0.22,-0.86099994,4.9,0.00951,-0.905,5.4,0.22299999,-0.948,6.2,0.432,-0.88299996,7.7,1.1999999,-0.88299996,7.2000003,0.79499996,-1.5,7.1,0.95799994,-1.5,6.1000004,0.53,-1.4,5.4,0.334,-1.4,4.9,0.0341,-4.2,1.3,1.5999999,-4.4,1.7,1.7,-3.7,1.8000001,1.0,-3.4,1.1999999,1.0,-2.6,1.9,0.80700004,-2.5,1.4,0.831,-2.0,1.5999999,0.88100004,
	}, 
    {
       3,2,1,4,2,3,7,6,5,5,8,7,9,7,8,8,10,9,9,10,11,12,9,11,13,12,11,2,13,11,14,2,11,10,14,11,1,2,14,15,1,14,16,15,14,10,17,16,16,14,10,18,17,10,10,8,18,19,18,8,8,5,19,20,15,16,21,15,20,20,22,21,23,21,22,22,24,23,25,23,24,24,26,25,27,25,26,26,28,27,29,27,28,29,30,27,32,31,30,33,30,31,34,2,4,13,2,34,35,34,4,4,36,35,37,35,36,36,33,37,31,37,33,32,38,31,38,39,31,39,37,31,40,37,39,35,37,40,41,34,35,41,42,34,35,40,41,42,13,34,43,13,42,45,44,9,9,12,45,43,45,12,12,13,43,43,46,45,47,46,43,48,46,47,43,42,47,49,47,42,42,50,49,51,50,42,42,52,51,53,52,42,55,54,53,53,41,55,42,41,53,51,56,50,52,56,51,57,50,56,58,50,57,9,44,59,59,7,9,59,60,6,6,7,59,62,61,60,60,59,62,63,62,59,59,44,63,45,63,44,46,63,45,64,63,46,48,65,64,64,46,48,62,63,64,64,66,62,49,50,58,58,67,49,68,49,67,47,49,68,48,68,69,47,68,48,70,65,48,48,69,70,65,70,71,71,72,65,74,73,72,72,71,74,75,73,74,76,57,75,76,58,57,75,74,76,77,61,62,62,66,77,65,78,66,66,64,65,78,77,66,79,77,78,78,72,79,78,65,72,80,79,72,72,73,80,75,80,73,81,80,75,75,82,81,57,83,82,82,75,57,56,83,57,85,84,81,81,82,85,86,85,82,82,83,86,56,86,83,87,86,56,56,88,87,52,88,56,89,88,52,52,53,89,53,90,89,54,90,53,91,90,54,90,91,92,89,90,92,91,93,92,96,95,94,97,94,95,95,98,97,99,97,98,100,97,99,99,101,100,93,101,99,91,101,93,102,101,91,103,101,102,100,101,103,103,104,100,97,100,104,104,105,97,94,97,105,107,106,94,94,105,107,108,107,105,105,104,108,109,108,104,104,103,109,102,110,103,110,109,103,102,111,110,112,111,102,102,54,112,91,54,102,40,55,41,113,55,40,40,39,113,114,113,39,39,38,114,115,113,114,116,113,115,115,117,116,119,118,116,116,117,119,121,120,118,118,119,121,124,123,122,125,123,124,126,123,125,125,127,126,128,122,120,120,121,128,129,118,120,116,118,129,129,54,116,112,54,129,129,111,112,120,111,129,122,111,120,130,111,122,110,111,130,130,131,110,116,54,55,55,113,116,128,124,122,133,132,106,106,107,133,133,134,132,134,135,132,136,135,134,134,137,136,138,137,134,139,138,134,134,133,139,140,139,133,141,139,140,142,139,141,141,131,142,110,131,141,141,109,110,140,109,141,108,109,140,143,136,137,137,144,143,145,143,144,144,146,145,148,147,146,146,144,148,125,147,148,148,127,125,122,123,126,126,130,122,142,131,130,130,126,142,127,148,138,142,126,127,127,138,142,139,142,138,148,144,137,137,138,148,133,107,108,108,140,133,29,32,30,149,28,26,26,150,149,29,28,149,149,151,29,152,151,149,149,150,152,154,150,153,152,150,154,155,151,152,152,156,155,157,155,156,159,158,157,157,156,159,152,159,156,154,159,152,150,26,153,26,24,153,153,24,22,22,160,153,154,153,160,160,161,154,159,154,161,161,162,159,163,159,162,158,159,163,158,163,164,164,165,158,157,158,165,165,166,157,165,167,166,168,167,165,165,164,168,169,168,164,167,168,170,171,170,168,173,172,171,171,174,173,175,172,173,173,176,175,173,178,177,177,176,173,180,179,177,177,178,180,182,181,179,179,180,182,184,183,182,182,180,184,185,184,180,180,178,185,174,185,178,178,173,174,168,186,174,174,171,168,168,169,186,164,163,169,187,169,163,162,188,187,189,188,162,162,161,189,190,189,161,161,160,190,160,20,190,22,20,160,191,190,20,192,190,191,20,17,191,16,17,20,193,191,17,17,18,193,194,193,18,18,19,194,195,193,194,194,196,195,191,193,195,195,192,191,189,190,192,192,197,189,195,198,197,197,192,195,199,198,195,195,196,199,200,198,199,199,201,200,202,200,201,201,203,202,204,202,203,203,205,204,184,206,183,206,207,183,208,207,206,206,209,208,174,186,185,186,209,185,169,209,186,210,209,169,169,211,210,187,211,169,212,211,187,187,188,212,197,212,188,188,189,197,200,212,197,197,198,200,211,212,200,200,202,211,210,211,202,202,204,210,208,210,204,209,210,208,205,207,208,208,204,205,163,162,187,184,185,206,206,185,209,1,15,3,27,30,33,214,213,27,27,213,25,213,215,23,23,25,213,215,213,214,214,216,215,23,215,217,217,21,23,215,216,218,218,217,215,219,217,218,217,219,15,15,21,217,222,221,220,220,221,223,6,225,224,224,5,6,225,227,226,226,224,225,228,226,227,228,227,229,228,229,230,228,230,221,228,221,231,228,231,226,231,221,222,231,222,232,231,232,233,234,226,231,231,233,234,234,235,224,224,226,234,235,19,5,5,224,235,233,232,236,236,232,237,237,238,236,237,240,239,239,238,237,240,242,241,241,239,240,242,244,243,243,241,242,243,244,245,244,246,245,246,248,247,248,246,249,223,221,250,250,221,230,223,250,251,251,252,223,252,251,253,253,249,252,249,253,248,248,254,247,248,255,254,248,253,255,255,253,256,256,253,251,251,250,257,250,258,257,257,256,251,250,230,258,258,230,259,261,260,229,229,227,261,260,259,230,230,229,260,260,262,259,259,262,263,263,262,264,263,258,259,258,263,265,265,266,258,258,266,267,267,268,258,258,268,269,269,271,270,270,257,269,269,257,258,266,272,267,267,272,268,272,266,273,273,266,274,261,227,225,225,275,261,60,275,225,225,6,60,61,276,275,275,60,61,276,277,261,261,275,276,261,277,260,260,277,262,262,277,278,279,264,262,262,278,279,277,276,280,280,278,277,266,265,281,281,274,266,281,265,282,282,265,263,283,282,264,264,282,263,279,284,283,283,264,279,284,279,285,285,286,284,288,287,286,286,285,288,287,288,289,289,273,290,273,274,290,290,287,289,61,77,280,280,276,61,291,279,278,278,280,291,280,77,291,77,79,285,285,291,77,285,279,291,285,79,80,80,288,285,288,80,289,80,81,292,292,289,80,293,273,289,289,292,293,273,293,272,84,294,292,292,81,84,294,295,293,293,292,294,293,295,272,272,295,296,296,297,272,272,297,268,268,297,298,298,269,268,298,299,269,269,299,271,271,299,300,301,300,299,301,299,298,301,302,300,94,303,96,303,94,304,304,305,303,305,304,306,306,304,307,307,308,306,306,308,302,302,308,300,300,308,309,309,308,310,308,307,311,311,310,308,307,304,312,312,311,307,312,304,94,106,313,312,312,94,106,313,314,311,311,312,313,314,315,310,310,311,314,310,316,309,310,315,316,316,317,309,309,317,318,318,271,309,309,271,300,257,270,256,256,270,319,319,255,256,255,319,320,320,254,255,320,319,321,321,319,322,322,323,321,325,324,323,323,322,325,327,326,324,324,325,327,330,329,328,328,329,331,331,329,332,332,333,331,327,330,334,334,326,327,327,325,335,335,325,322,322,271,335,335,271,318,318,317,335,335,317,327,327,317,330,330,317,336,317,316,337,337,336,317,270,271,322,322,319,270,330,328,334,132,338,313,313,106,132,132,339,338,132,135,339,135,136,340,340,339,135,339,340,341,339,341,342,342,338,339,338,342,343,343,342,344,344,342,345,345,337,344,344,337,316,316,315,344,344,315,343,343,315,314,136,143,346,346,340,136,143,145,347,347,346,143,349,348,346,346,347,349,349,331,333,333,348,349,329,330,336,336,332,329,337,345,332,332,336,337,341,348,333,332,345,341,341,333,332,341,345,342,346,348,341,341,340,346,313,338,343,343,314,313,246,247,245,243,351,350,350,241,243,351,243,245,245,352,351,351,352,353,353,350,351,355,350,354,354,350,353,352,357,356,356,353,352,356,357,358,360,359,356,356,358,360,356,359,353,353,359,354,355,241,350,355,239,241,239,355,361,361,238,239,355,354,362,362,361,355,354,359,363,363,362,354,363,359,364,364,359,360,364,360,365,365,366,364,360,358,367,367,365,360,367,368,365,368,369,366,366,365,368,366,369,370,371,369,368,369,371,372,375,374,373,373,372,375,375,377,376,376,374,375,378,374,376,376,379,378,381,380,378,378,379,381,181,182,380,380,381,181,183,382,380,380,182,183,382,383,378,378,380,382,383,373,374,374,378,383,384,369,372,372,373,384,384,370,369,370,364,366,364,370,385,385,386,363,386,387,362,362,363,386,387,388,361,361,362,387,388,236,361,361,236,238,236,388,389,389,388,390,389,234,236,236,234,233,234,389,391,391,235,234,235,391,194,194,19,235,391,392,196,196,194,391,391,389,390,390,392,391,388,387,393,393,390,388,394,392,390,390,393,394,394,199,196,196,392,394,394,395,201,201,199,394,395,396,203,203,201,395,396,397,205,205,203,396,183,398,382,183,207,398,398,207,399,399,400,398,383,384,373,383,400,384,384,400,370,370,400,401,401,402,370,370,402,385,402,403,386,386,385,402,403,393,387,387,386,403,403,395,394,394,393,403,395,403,402,402,396,395,402,401,397,397,396,402,397,401,399,399,401,400,207,205,397,397,399,207,385,363,364,398,383,382,400,383,398,220,232,222,249,246,244,244,405,404,242,405,244,406,405,242,242,240,406,405,406,407,407,404,405,406,240,237,237,408,406,407,406,408,408,409,407,409,408,410,232,410,408,408,237,232,
		 }

};

	return object;
}




void FaceModel ::  display(obj_type cube)
{


	
	
	 int l_index;

	glBegin(GL_LINES); // GlBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
    for (l_index=0;l_index<718;l_index++)
    {
		//glutWireCube(2.0f);
        glColor3f(1.0,0.0,0.0); // Color for the vertex
        glVertex3f( cube.vertex[ cube.polygon[l_index].a ].x,    cube.vertex[ cube.polygon[l_index].a ].y,    cube.vertex[ cube.polygon[l_index].a ].z);//Vertex definition
        glColor3f(1.0,0.0,0.0); 
        glVertex3f( cube.vertex[ cube.polygon[l_index].b ].x,    cube.vertex[ cube.polygon[l_index].b ].y,    cube.vertex[ cube.polygon[l_index].b ].z);
       glColor3f(1.0,0.0,0.0); 
       glVertex3f( cube.vertex[ cube.polygon[l_index].c ].x,    cube.vertex[ cube.polygon[l_index].c ].y,    cube.vertex[ cube.polygon[l_index].c ].z);
    }
    glEnd();

    glFlush(); 

	/*
   // Wireframe Mode
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   glBegin(GL_QUADS);
      // Top Side
      glVertex3f( 1.0f, 1.0f,  1.0f);
      glVertex3f( 1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f,  1.0f);

      // Bottom Side
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);

      // Front Side
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);

      // Back Side
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);

      // Left Side
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);

      // Right Side
      glVertex3f( 1.0f,  1.0f,  1.0f);
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);
   glEnd();


   */

}



/**********************************************************
 *
 * The main routine
 * 
 *********************************************************/

