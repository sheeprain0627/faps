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
Tdsloader::Tdsloader(void)
{
}


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
					//printf("Polygon point a: %d\n",p_object->polygon[i].a);
					fread (&p_object->polygon[i].b, sizeof (unsigned short), 1, l_file);
					//printf("Polygon point b: %d\n",p_object->polygon[i].b);
					fread (&p_object->polygon[i].c, sizeof (unsigned short), 1, l_file);
					//printf("Polygon point c: %d\n",p_object->polygon[i].c);
					fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
					//printf("Face flags: %x\n",l_face_flags);
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


//this enable the trasparence on texture
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//read and load 3ds data to memeory
	Load3DS (&object,"spaceship.3ds");

	//object.id_texture=LoadBitmap("D:\\Works\\MFC works\\FAPS\\fAPS\\fAPS\\face1.bmp"); // The Function LoadBitmap() return the current texture ID

	opath="res//pil111.bmp";
	tpath="res//black.bmp";
object.id_texture=LoadBitmap(opath,255,0,1);		//adjust the conrst level for age progress : 0-1
	object.id_texture2=LoadBitmap(tpath,255,0,0);

    ori_object=object;
	//glBindTexture(GL_TEXTURE_2D, object.id_texture);

}


void changeMode(GLenum mode){

	m_type=mode;

	}

void reset()
{
object=ori_object;
}



void setTexture(CString path)
{
	object.id_texture2=LoadBitmap(path,255,0,1);
}


void makeLine(){

	for(int i=1280;i<1303;i++){
	
		object.vertex[i].y+=0.5;
		//object.mapcoord[i].v*=1.15;

	}

}

void markVertex(int vertex){
	//glBegin(GL_POINTS);
	//glPointSize(2);
	//glColor3f (1.0, 1.0, 0.0); 	
		//glColor4f(particles[z].colr, particles[z].colg, particles[z].colb, particles[z].life);
		
			//glVertex3f(object.vertex[vertex].x,object.vertex[vertex].y, object.vertex[vertex].z);
		//	glEnd();
	
	object.mapcoord[vertex].u=0;object.mapcoord[vertex].v=0;
}

void test(){
	const double PI = 4.0*atan(1.0);
	for(int i=0;i<object.vertices_qty;i++){
	
		if(object.mapcoord[i].v>1){
			object.mapcoord[i].v-=1;

		}

		//object.mapcoord[i].u=atan((object.vertex[i].x/object.vertex[i].y)/PI+0.5);
		//object.mapcoord[i].v=asin((object.vertex[i].x/PI)+0.5);

	}
}

void scaleTex(){


	glScalef(2,2,2);

}


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

void display(){	
	
	glBindTexture(GL_TEXTURE_2D, object.id_texture);
	
	sdisplay();		//call the normal frawing function in opengl

	 glDepthFunc(GL_LEQUAL);

	 glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



// set the blending mode
//glEnable(GL_BLEND);
glBlendFunc(GL_ONE,GL_ONE);

// set second texture
//(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//CString path2="res//pil.bmp";



glBindTexture(GL_TEXTURE_2D, object.id_texture2);

sdisplay();

glDepthFunc(GL_LESS);   // return to normal depth mode
glDisable(GL_BLEND);    // don't need blending any more


	
	/*
	glBegin(GL_POINTS);
	glPointSize(20);
	glTexCoord2f( object.mapcoord[ object.polygon[50].a ].u, object.mapcoord[ object.polygon[50].a ].v);
        // Coordinates of the first vertex
        glVertex3f( object.vertex[ object.polygon[50].a ].x,
                    object.vertex[ object.polygon[50].a ].y,
                    object.vertex[ object.polygon[50].a ].z); //Vertex definition
	glEnd();

	*/


    glFlush(); // This force the execution of OpenGL commands
}

void modify(float x, CString selctVal){
	featureInstance.set3Dobject(&object);
	
	featureInstance.changeNose(&object,noseChangeVal);
	featureInstance.changeMouth(&object,mouthChangeVal);
	featureInstance.changeLeftEye(&object,leftEyeChangeVal);
	featureInstance.changeRightEye(&object,rightEyeChangeVal);
/*
	if(selctVal == "Nose")
	{
		 featureInstance.changeNose(&object,noseChangeVal);
	}
	else if(selctVal == "Mouth")
	{
		featureInstance.changeMouth(&object,mouthChangeVal);
	}
	if(selctVal == "LeftEye")
	{
		featureInstance.changeLeftEye(&object,leftEyeChangeVal);
	}
	if(selctVal == "RightEye")
	{
		featureInstance.changeRightEye(&object,rightEyeChangeVal);
	}
	
	else
	{
		//do nothing
	}
		//
*/

	//for(int i=498;i<630;i++){


//object.vertex[i].x=x;object.vertex[i].y=x;object.vertex[i].z=x;
	//}
	//object.vertex[500].x=x;object.vertex[500].y=x;object.vertex[500].z=x;
	//display(GL_TRIANGLES);

}


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


			if(((i>(230*240)+58+u && i<(230*240)+160+u)) && (i<(230*240)+58+32*240)) {
				
			//if(text_dif[w+0]>8 || text_dif[w+0] <-8 ) 	
			l_text[w+2] = 0.5*(rgb.rgbtRed + text_dif[w+0]); // Red component

			//else if( text_dif[w+1]>8 || text_dif[w+1]<-8)
            l_text[w+1] = 0.5*(rgb.rgbtGreen + text_dif[w+1]); // Green component

			//else if( text_dif[w+2]>8 || text_dif[w+2]<-8)
            l_text[w+0] = 0.5*(rgb.rgbtBlue + text_dif[w+2]); // Blue component

			/*else {

				l_text[w+2] = rgb.rgbtRed;
				l_text[w+1] = rgb.rgbtGreen;
				l_text[w+0] = rgb.rgbtBlue;
			}*/
		
			l_texture[j+0] = 0.88*(rgb.rgbtRed + text_dif[w+0]); // Red component
			l_texture[j+1] = 0.88*(rgb.rgbtGreen + text_dif[w+1]); // Green component
			l_texture[j+2] =  0.88*(rgb.rgbtBlue + text_dif[w+2]); // Blue component
			
			/*l_texture[j+0] = clevel*(rgb.rgbtRed-blevel); // Red component
			l_texture[j+1] = clevel*(rgb.rgbtGreen-blevel); // Green component
			l_texture[j+2] = clevel*(rgb.rgbtBlue-blevel); // Blue component*/
			l_texture[j+3] = tlevel; // Alpha value
			j += 4; // Go to the next position

			w +=3;
			if(i==(230*240)+159+u)
				u += 240;
			
			}


			else {

				// And store it
				l_texture[j+0] = clevel*(rgb.rgbtRed-blevel); // Red component
				l_texture[j+1] = clevel*(rgb.rgbtGreen-blevel); // Green component
				l_texture[j+2] = clevel*(rgb.rgbtBlue-blevel); // Blue component
				l_texture[j+3] = tlevel; // Alpha value
				j += 4; // Go to the next position
			}
		}


		
		/*IplImage* img11;
		IplImage* img_new;
		
		img_new = cvLoadImage("K:\\FAPS-Images\\3Dsloader-640-480\\FACEM.bmp");
		cvNamedWindow("Lap",1);
		img11 = cvCreateImage(cvSize(101,32),8 , 3);
		
		cvSetData(img11,l_text ,303);
		cvShowImage("Lap", img11);	
		
		cvWaitKey();*/

		  
		//img_new = cvCreateImage(cvSize(101,32), IPL_DEPTH_8U, 3);
		//cvSmooth( img11, img_new, CV_GAUSSIAN, 7, 7 );
		//cvSmooth( img11, img_new, CV_MEDIAN, 7, 7 );
		
		//cvResize(img11,img_new,1);
		//cvLaplace(img11, img_new, 3);
		//cvShowImage("smooth", img_new);


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


void LoadImage(CString path,int tlevel,int blevel,float clevel){
	//CString path2="res//ww.bmp";
	opath=path;
	ori_object.id_texture=object.id_texture=LoadBitmap(path,tlevel,blevel,clevel); // The Function LoadBitmap() return the current texture ID

    glBindTexture(GL_TEXTURE_2D, object.id_texture);
	
	//glBindTexture(GL_TEXTURE_2D, LoadBitmap(path));
}//

void LoadImage2(CString path,int tlevel,int blevel,float clevel){
	//CString path2="res//ww.bmp";
	tpath=path;
	ori_object.id_texture2=LoadBitmap(path,tlevel,blevel,clevel); // The Function LoadBitmap() return the current texture ID

    glBindTexture(GL_TEXTURE_2D, object.id_texture2);
	
	//glBindTexture(GL_TEXTURE_2D, LoadBitmap(path));
}//


void changeContrast(float clevel){
	object.id_texture=LoadBitmap(opath,255,0,1.0-clevel); // The Function LoadBitmap() return the current texture ID

    glBindTexture(GL_TEXTURE_2D, object.id_texture);

	object.id_texture2=LoadBitmap(tpath,255,0,clevel); // The Function LoadBitmap() return the current texture ID

    glBindTexture(GL_TEXTURE_2D, object.id_texture2);

}

//deform the image according to the given face size




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


//captures the current image and fill it in current data
void captureImage() 
{
	int width=300;
	int height=400;
glReadBuffer(GL_FRONT);
BYTE* currentData=(BYTE *)malloc(width*height*4);
glPixelStorei(GL_PACK_ALIGNMENT, 4); 
glReadPixels(0,0,width,height,GL_BGRA_EXT,GL_UNSIGNED_BYTE,currentData);
WriteBmp("output//output.bmp",width,height,32,(int *)currentData);
}

//writes the data into a .bmp image and saves it
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


FILE* image = fopen (name,"wb");
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