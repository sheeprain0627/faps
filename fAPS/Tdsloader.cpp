//!  3ds file readed class 
/*!
  Read the 3ds files and process it. It contains all the methods that are used to process the 3ds file and the face texture.
*/

#include "StdAfx.h"
#include "Tdsloader.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>
#include<math.h>
#include <fstream>

#include <cxcore.h>
#include "cv.h"
#include "highgui.h"
#include "cvaux.h"
#include <imgproc_c.h>
#include <windows.h>

#include "feature.h"

using namespace std;

ofstream textureFile("res\\texture.txt");
ifstream readFile25("res\\texture_new.txt");
ifstream readFile50("res\\texture_old.txt");
ofstream textureDif("res\\texture_dif.txt");


feature featureInstance;
/*!
	 constructor of Tdsloader
*/
Tdsloader::Tdsloader(void)
{
}

/*!
	 destructor of Tdsloader
*/
Tdsloader::~Tdsloader(void)
{
}

float leftEyeChangeVal; // eye val of (new texture val /Original texture val)
float rightEyeChangeVal; // eye val of (new texture val /Original texture val)
float noseChangeVal; // nose val of (new texture val /Original texture val)
float mouthChangeVal; // mouth val of (new texture val /Original texture val)


// The width and height of your window, change them as you like
int screen_width=640;
int screen_height=480;
GLenum m_type=GL_TRIANGLES;

// Absolute rotation values (0-359 degrees) and rotation increments for each frame
double rotation_x=0, rotation_x_increment=0.1;
double rotation_y=0, rotation_y_increment=0.05;
double rotation_z=0, rotation_z_increment=0.03;


int num_texture=-1; //Counter to keep track of the last loaded texture

// Flag for rendering as lines or filled polygons
int filling=1; //0=OFF 1=ON

//Now the object is generic, the cube has annoyed us a little bit, or not?
obj_type object;
obj_type ori_object;
CString opath,tpath;


/*!
Load the 3ds file and create the model for rendering the 3D scene
\param p_object object model of face
\param p_filename file path of 3ds file
*/

char Load3DS (obj_type_ptr p_object, char *p_filename)
{
	int i; //Index variable

	FILE *l_file; //File pointer

	unsigned short l_chunk_id; //Chunk identifier
	unsigned int l_chunk_lenght; //Chunk lenght

	unsigned char l_char; //Char variable
	unsigned short l_qty; //Number of elements in each chunk

	unsigned short l_face_flags; //Flag that stores some face information

	if ((l_file=fopen (p_filename, "rb"))== NULL) return 0; //Open the file

	while (ftell (l_file) < filelength (fileno (l_file))) //Loop to scan the whole file 
	{
		//getche(); //Insert this command for debug (to wait for keypress for each chuck reading)

		fread (&l_chunk_id, 2, 1, l_file); //Read the chunk header
		printf("ChunkID: %x\n",l_chunk_id); 
		fread (&l_chunk_lenght, 4, 1, l_file); //Read the lenght of the chunk
		printf("ChunkLenght: %x\n",l_chunk_lenght);

		switch (l_chunk_id)
		{
			//----------------- MAIN3DS -----------------
			// Description: Main chunk, contains all the other chunks
			// Chunk ID: 4d4d 
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
		case 0x4d4d: 
			break;    

			//----------------- EDIT3DS -----------------
			// Description: 3D Editor chunk, objects layout info 
			// Chunk ID: 3d3d (hex)
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
		case 0x3d3d:
			break;

			//--------------- EDIT_OBJECT ---------------
			// Description: Object block, info for each object
			// Chunk ID: 4000 (hex)
			// Chunk Lenght: len(object name) + sub chunks
			//-------------------------------------------
		case 0x4000: 
			i=0;
			do
			{
				fread (&l_char, 1, 1, l_file);
				p_object->name[i]=l_char;
				i++;
			}while(l_char != '\0' && i<20);
			break;

			//--------------- OBJ_TRIMESH ---------------
			// Description: Triangular mesh, contains chunks for 3d mesh info
			// Chunk ID: 4100 (hex)
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
		case 0x4100:
			break;

			//--------------- TRI_VERTEXL ---------------
			// Description: Vertices list
			// Chunk ID: 4110 (hex)
			// Chunk Lenght: 1 x unsigned short (number of vertices) 
			//             + 3 x float (vertex coordinates) x (number of vertices)
			//             + sub chunks
			//-------------------------------------------
		case 0x4110: 
			fread (&l_qty, sizeof (unsigned short), 1, l_file);
			p_object->vertices_qty = l_qty;
			printf("Number of vertices: %d\n",l_qty);
			for (i=0; i<l_qty; i++)
			{
				fread (&p_object->vertex[i].x, sizeof(float), 1, l_file);
				//printf("Vertices list x: %f\n",p_object->vertex[i].x);
				fread (&p_object->vertex[i].y, sizeof(float), 1, l_file);
				//printf("Vertices list y: %f\n",p_object->vertex[i].y);
				fread (&p_object->vertex[i].z, sizeof(float), 1, l_file);
				//printf("Vertices list z: %f\n",p_object->vertex[i].z);
			}
			break;

			//--------------- TRI_FACEL1 ----------------
			// Description: Polygons (faces) list
			// Chunk ID: 4120 (hex)
			// Chunk Lenght: 1 x unsigned short (number of polygons) 
			//             + 3 x unsigned short (polygon points) x (number of polygons)
			//             + sub chunks
			//-------------------------------------------
		case 0x4120:
			fread (&l_qty, sizeof (unsigned short), 1, l_file);
			p_object->polygons_qty = l_qty;
			printf("Number of polygons: %d\n",l_qty); 
			for (i=0; i<l_qty; i++)
			{
				fread (&p_object->polygon[i].a, sizeof (unsigned short), 1, l_file);
				fread (&p_object->polygon[i].b, sizeof (unsigned short), 1, l_file);
				fread (&p_object->polygon[i].c, sizeof (unsigned short), 1, l_file);
				fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
			}
			break;

			//------------- TRI_MAPPINGCOORS ------------
			// Description: Vertices list
			// Chunk ID: 4140 (hex)
			// Chunk Lenght: 1 x unsigned short (number of mapping points) 
			//             + 2 x float (mapping coordinates) x (number of mapping points)
			//             + sub chunks
			//-------------------------------------------
		case 0x4140:
			fread (&l_qty, sizeof (unsigned short), 1, l_file);
			for (i=0; i<l_qty; i++)
			{
				fread (&p_object->mapcoord[i].u, sizeof (float), 1, l_file);
				printf("Mapping list u: %f\n",p_object->mapcoord[i].u);
				fread (&p_object->mapcoord[i].v, sizeof (float), 1, l_file);
				printf("Mapping list v: %f\n",p_object->mapcoord[i].v);
			}
			break;

			//----------- Skip unknow chunks ------------
			//We need to skip all the chunks that currently we don't use
			//We use the chunk lenght information to set the file pointer
			//to the same level next chunk
			//-------------------------------------------
		default:
			fseek(l_file, l_chunk_lenght-6, SEEK_CUR);
		} 
	}
	fclose (l_file); // Closes the file stream
	return (1); // Returns ok
}


void init(){
	glEnable(GL_TEXTURE_2D); // This Enable the Texture mapping
	
	//read and load 3ds data to memeory
	Load3DS (&object,"res//facemodel.3ds");

	opath="res//facetemplete.bmp";
	tpath="res//black.bmp";
	object.id_texture=LoadBitmap(opath,255,0,1);		//adjust the conrst level for age progress : 0-1
	object.id_texture2=LoadBitmap(tpath,255,0,0);

	ori_object=object;
}


/*!
Change the view mode of 3d model
\param mode mode of 3d model : point/line
*/

void changeMode(GLenum mode){
	m_type=mode;

}

/*!
reset the 3d model with default values
*/

void reset()
{
	object=ori_object;
	glDisable (GL_TEXTURE_2D);
}


/*!
set the texture on 3d model 
*/

void setTexture(CString path)
{
	object.id_texture2=LoadBitmap(path,255,0,1);
}



void test(){
	const double PI = 4.0*atan(1.0);
	for(int i=0;i<object.vertices_qty;i++){

		if(object.mapcoord[i].v>1){
			object.mapcoord[i].v-=1;

		}
	}
}

void scaleTex(){
	glScalef(2,2,2);

}

/*!
Move the texture
\param dir direction of the movement
*/

void move(char dir){
	switch(dir){
	case 'l' :
		for(int i=0;i<1683;i++)	
			object.mapcoord[i].u+=.01;
		break;

	case 'r' :
		for(int i=0;i<1683;i++)	
			object.mapcoord[i].u-=.01;
		break;

	case 'u' :
		for(int i=0;i<1683;i++)	
			object.mapcoord[i].v-=.01;
		break;

	case 'd' :
		for(int i=0;i<1683;i++)	
			object.mapcoord[i].v+=.01;
		break;

	default : break;

	}



}

void sdisplay(){

	int l_index;
	glBegin(m_type); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
	for (l_index=0;l_index<object.polygons_qty;l_index++)
	{
		//----------------- FIRST VERTEX -----------------
		// Texture coordinates of the first vertex
		glTexCoord2f( object.mapcoord[ object.polygon[l_index].a ].u, object.mapcoord[ object.polygon[l_index].a ].v);
		// Coordinates of the first vertex
		glVertex3f( object.vertex[ object.polygon[l_index].a ].x,
			object.vertex[ object.polygon[l_index].a ].y,
			object.vertex[ object.polygon[l_index].a ].z); //Vertex definition

		//----------------- SECOND VERTEX -----------------
		// Texture coordinates of the second vertex
		glTexCoord2f( object.mapcoord[ object.polygon[l_index].b ].u,object.mapcoord[ object.polygon[l_index].b ].v);
		// Coordinates of the second vertex
		glVertex3f( object.vertex[ object.polygon[l_index].b ].x,
			object.vertex[ object.polygon[l_index].b ].y,
			object.vertex[ object.polygon[l_index].b ].z);

		//----------------- THIRD VERTEX -----------------
		// Texture coordinates of the third vertex
		glTexCoord2f( object.mapcoord[ object.polygon[l_index].c ].u,                      object.mapcoord[ object.polygon[l_index].c ].v);
		// Coordinates of the Third vertex
		glVertex3f( object.vertex[ object.polygon[l_index].c ].x,
			object.vertex[ object.polygon[l_index].c ].y,
			object.vertex[ object.polygon[l_index].c ].z);
	}
	glEnd();

}

/*!
Display the 3ds file
*/


void display(){	

	glBindTexture(GL_TEXTURE_2D, object.id_texture);

	sdisplay();		//call the normal frawing function in opengl

	glDepthFunc(GL_LEQUAL);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// set the blending mode
	
	glBlendFunc(GL_ONE,GL_ONE);
	glBindTexture(GL_TEXTURE_2D, object.id_texture2);

	sdisplay();

	glDepthFunc(GL_LESS);   // return to normal depth mode
	glDisable(GL_BLEND);    // don't need blending any more
	glFlush(); // This force the execution of OpenGL commands
}

/*!
	 changing cheek value
	 \param val as float deciding how much to deform
	 \param age as int of which age group
*/

void Tdsloader::changecheek(float val,int age){
	if(val>0){

		switch (age)
		{
		case 30: val=0;
			break;
		case 40: val=val*.1;
			break;
		case 50: val=val*.3;
			break;
		case 60: val=val*.5;
			break;
		case 70: val=val*.7;
			break;
		case 80: val=val*.8;
			break;
		default: val=0;
			break;
		}

		featureInstance.changeCheek(&object, val);
	}


}

/*!
	 to mdify the 3D model
	 \param x as float deciding how much to deform
	 \param selctVal as CString.
*/
void modify(float x, CString selctVal){
	featureInstance.set3Dobject(&object);

	featureInstance.changeNose(&object,noseChangeVal);
	featureInstance.changeMouth(&object,mouthChangeVal);
}


/*!
Method that changes the texture mapping coordiante
\param x as int array of x coordinates
\param y as int array of y coordiantes
\param cpoints as int array to chnage
*/


void changeVU(int x[],int y[],int cpoints[]){


	//select the fisrt point of left eye only thatn the remaining points will automatically moved by the new distance
	float nc=(x[4])/240.0;			
	float du=nc-object.mapcoord[cpoints[0]].u;
	for(int i=0;i<1683;i++)	
		object.mapcoord[i].u+=du;

	float dv=(1+(320.0-y[0]+2)/320.0)-object.mapcoord[cpoints[0]].v;	//2 reduced for adjustment
	for(int i=0;i<1683;i++)	
		object.mapcoord[i].v+=dv;

}

/*!
Method that changes the texture mapping coordiante
\param u1 as float of  u coordinates
\param v1 as float v coordinates
*/

void changeVU1(float u1,float  v1){

	float du=u1-object.mapcoord[900].u;
	for(int i=0;i<1683;i++)	
		object.mapcoord[i].u+=du;

	float dv=v1-object.mapcoord[900].v;	//2 reduced for adjustment
	for(int i=0;i<1683;i++)	
		object.mapcoord[i].v+=dv;


}


//values for the 3d model
void changeXYZ(int x[],int y[],int cpoints[]){

	//automacitc nose modification
	float noseRatio= (x[10]/240.0)/ori_object.mapcoord[cpoints[10]].u;  //ration between new u val/ old u val
	float newNoseVertexVal=(ori_object.vertex[cpoints[10]].x)*noseRatio;
	noseChangeVal=newNoseVertexVal-ori_object.vertex[cpoints[10]].x;

	//automatic mouth modification

	float mouthRatio= (x[14]/240.0)/ori_object.mapcoord[cpoints[14]].u;  //ration between new u val/ old u val
	float newMouthVertexVal=(ori_object.vertex[cpoints[14]].x)*mouthRatio;
	mouthChangeVal=newMouthVertexVal-ori_object.vertex[cpoints[14]].x;

	//automatic lefteye modification
	// problem ajith is putting the new value of poit 0 for texture mapping
	float leftEyeRatio= (x[0]/240.0)/ori_object.mapcoord[cpoints[0]].u;  //ration between new u val/ old u val
	//test
	//float leftEyeRatio1= (x[3]/240.0)/object.mapcoord[cpoints[3]].u;
	float newLEyeVertexVal=(ori_object.vertex[cpoints[0]].x)*leftEyeRatio;
	leftEyeChangeVal=newLEyeVertexVal-ori_object.vertex[cpoints[0]].x;

	//automatic righteye modification
	float rightEyeRatio= (x[7]/240.0)/ori_object.mapcoord[cpoints[7]].u;  //ration between new u val/ old u val
	float newREyeVertexVal=(ori_object.vertex[cpoints[7]].x)*rightEyeRatio;
	rightEyeChangeVal=newREyeVertexVal-ori_object.vertex[cpoints[7]].x;
}


/*!
Method that read the image and store the data into model
\param path file path of image
\param tlevel tranparent level of the face testure
\param blevel brightness level of the face testure
\param clevel contrast level of the face testure
*/


int LoadBitmap(CString path,int tlevel,int blevel,float clevel) 
{
	int i, j=0; //Index variables
	FILE *l_file; //File pointer
	unsigned char *l_texture; //The pointer to the memory zone in which we will load the texture

	// windows.h gives us these types to work with the Bitmap files
	BITMAPFILEHEADER fileheader; 
	BITMAPINFOHEADER infoheader;
	RGBTRIPLE rgb;

	num_texture++; // The counter of the current texture is increased

	if( (l_file = fopen(path, "rb"))==NULL) return (-1); // Open the file for reading

	fread(&fileheader, sizeof(fileheader), 1, l_file); // Read the fileheader

	fseek(l_file, sizeof(fileheader), SEEK_SET); // Jump the fileheader
	fread(&infoheader, sizeof(infoheader), 1, l_file); // and read the infoheader

	// Now we need to allocate the memory for our image (width * height * color deep)
	l_texture = (byte *) malloc(infoheader.biWidth * infoheader.biHeight * 4);
	// And fill it with zeros
	memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);



	int w,x,u;
	w=0;
	x=0;
	u=0;


	int l_text_25[9696];
	int l_text_50[9696];
	int text_dif[9696];
	int new_text[9696];

	unsigned char* l_text;				

	l_text = (byte *) malloc(9696);
	memset(l_text, 0, 9696);

	while(x<9696) {
		readFile25 >> l_text_25[x+0];
		readFile50 >> l_text_50[x+0];
		text_dif[x+0] = l_text_50[x+0] - l_text_25[x+0];
		l_text[x+2] = (unsigned char)text_dif[x+0];

		readFile25 >> l_text_25[x+1];
		readFile50 >> l_text_50[x+1];
		text_dif[x+1] = l_text_50[x+1] - l_text_25[x+1];
		l_text[x+2] = (unsigned char)text_dif[x+1];

		readFile25 >> l_text_25[x+2];
		readFile50 >> l_text_50[x+2];			
		text_dif[x+2] = l_text_50[x+2] - l_text_25[x+2];
		l_text[x+0] = (unsigned char)text_dif[x+2];

		x +=3;
	}


	//cvReleaseImage(&img11);
	// At this point we can read every pixel of the image
	for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++)
	{            
		// We load an RGB value from the file
		fread(&rgb, sizeof(rgb), 1, l_file); 				

		// And store it
		l_texture[j+0] = clevel*(rgb.rgbtRed-blevel); // Red component
		l_texture[j+1] = clevel*(rgb.rgbtGreen-blevel); // Green component
		l_texture[j+2] = clevel*(rgb.rgbtBlue-blevel); // Blue component
		l_texture[j+3] = tlevel; // Alpha value
		j += 4; // Go to the next position
		
	}




	fclose(l_file); // Closes the file stream

	glBindTexture(GL_TEXTURE_2D, num_texture); // Bind the ID texture specified by the 2nd parameter

	// The next commands sets the texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // The magnification function ("linear" produces better results)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //The minifying function

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // We don't combine the color with the original surface color, use only the texture map.

	// Finally we define the 2d texture
	glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

	// And create 2d mipmaps for the minifying function
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

	free(l_texture); // Free the memory we used to load the texture

	return (num_texture); // Returns the current texture OpenGL ID
}

//for origianl face
void LoadImage(CString path,int tlevel,int blevel,float clevel){
	//CString path2="res//ww.bmp";
	opath=path;
	ori_object.id_texture=object.id_texture=LoadBitmap(path,tlevel,blevel,clevel); // The Function LoadBitmap() return the current texture ID

	glBindTexture(GL_TEXTURE_2D, object.id_texture);
}


//for binding face
void LoadImage2(CString path,int tlevel,int blevel,float clevel){
	//CString path2="res//ww.bmp";
	tpath=path;
	ori_object.id_texture2=LoadBitmap(path,tlevel,blevel,clevel); // The Function LoadBitmap() return the current texture ID

	glBindTexture(GL_TEXTURE_2D, object.id_texture2);
}

/*!
method that changes the contrast level of the face testure
\param clevel contrast level of the face testure
*/

void changeContrast(float clevel){
	object.id_texture=LoadBitmap(opath,255,0,1.0-clevel); // The Function LoadBitmap() return the current texture ID

	glBindTexture(GL_TEXTURE_2D, object.id_texture);

	object.id_texture2=LoadBitmap(tpath,255,0,clevel); // The Function LoadBitmap() return the current texture ID

	glBindTexture(GL_TEXTURE_2D, object.id_texture2);

}


/*!
method that draw a box on selected vertex point

*/

void drawBox(){

	//MessageBox(0, "Join us at Inferno Dev!", "DLL Message", MB_OK | MB_ICONINFORMATION);
	glBegin(GL_TRIANGLES);
	for (int l_index=100;l_index<300;l_index++)
	{
		//----------------- FIRST VERTEX -----------------
		// Texture coordinates of the first vertex
		glColor3f(1.0,0.0,0.0);
		glVertex3f( object.vertex[ object.polygon[l_index].a ].x,
			object.vertex[ object.polygon[l_index].a ].y,
			object.vertex[ object.polygon[l_index].a ].z); //Vertex definition
		glColor3f(0.0,1.0,0.0);
		//----------------- SECOND VERTEX -----------------
		// Texture coordinates of the second vertex

		glVertex3f( object.vertex[ object.polygon[l_index].b ].x,
			object.vertex[ object.polygon[l_index].b ].y,
			object.vertex[ object.polygon[l_index].b ].z);

		glColor3f(0.0,0.0,1.0);
		glVertex3f( object.vertex[ object.polygon[l_index].c ].x,
			object.vertex[ object.polygon[l_index].c ].y,
			object.vertex[ object.polygon[l_index].c ].z);
	}
	glEnd();  
	glFlush();

}

/*!
method that captures the current image and fill it in current data
\param spath save file path name

*/

//captures the current image and fill it in current data
void captureImage(char *spath) 
{
	int width=240;
	int height=400;
	glReadBuffer(GL_BACK);
	BYTE* currentData=(BYTE *)malloc(width*height*4);
	glPixelStorei(GL_PACK_ALIGNMENT, 4); 
	glReadPixels(55,0,width,height,GL_BGRA_EXT,GL_UNSIGNED_BYTE,currentData);
	WriteBmp(spath,width,height,32,(int *)currentData);
	addLogo(spath);
}

/*!
writes the data into a .bmp image and saves it
\param name file name
\param W width of the image
\param H heght of the image
\param Bpp 
\param data image data
*/


void WriteBmp(char* name,int W,int H,int Bpp,int* data)	 
{
	BITMAPINFO Bmi={0};
	Bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	Bmi.bmiHeader.biWidth = W;
	Bmi.bmiHeader.biHeight = H;
	Bmi.bmiHeader.biPlanes = 1;
	Bmi.bmiHeader.biBitCount = Bpp; 
	Bmi.bmiHeader.biCompression = BI_RGB;
	Bmi.bmiHeader.biSizeImage = W*H*Bpp/8; 


	FILE* image = fopen ("res//temp.bmp","wb");
	if(image==0)
		return;
	int h = abs(Bmi.bmiHeader.biHeight);
	int w = abs(Bmi.bmiHeader.biWidth);
	Bmi.bmiHeader.biHeight=h;
	Bmi.bmiHeader.biWidth=w;
	int sz = Bmi.bmiHeader.biSizeImage;

	BITMAPFILEHEADER bfh;
	bfh.bfType=('M'<<8)+'B'; 
	bfh.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER); 
	bfh.bfSize=sz+bfh.bfOffBits; 
	bfh.bfReserved1=0; 
	bfh.bfReserved2=0; 

	fwrite(&bfh,sizeof(bfh),1,image);
	fwrite(&Bmi.bmiHeader,sizeof(BITMAPINFOHEADER),1,image);
	fwrite(data,sz,1,image);	
	fclose(image);	
}


void addLogo(char* name){
	IplImage* img1=cvLoadImage("res//temp.bmp");
	IplImage* img2=cvLoadImage("res//logo.jpg");



	IplImage *dest = cvCreateImage( cvSize((int)240 ,(int)70),img2->depth, img2->nChannels );

//use cvResize to resize source to a destination image
cvResize(img2, dest);


	/* define rectangle for ROI */
CvRect rect = cvRect(0, 330, img1->width, img1->height);
 
/* sets Region of Interest */
cvSetImageROI(img1, rect);
 
/* Add both images
   Note that now both images have 'same' width & height */
cvAdd(img1, dest, img1, NULL);
 
/* always reset the region of interest */
cvResetImageROI(img1);
cvSaveImage(name,img1);

}


/*
* Reset the model parameters
*/

void resetModel(){
	object=ori_object;
	changeContrast(0);

}