#pragma once
#include <GL/glut.h>

class Tdsloader
{
public:
	Tdsloader(void);
	~Tdsloader(void);
};

/*
 * ---------------- www.spacesimulator.net --------------
 *   ---- Space simulators and 3d engine tutorials ----
 *
 * Author: Damiano Vitulli
 *
 * This program is released under the BSD licence
 * By using this program you agree to licence terms on spacesimulator.net copyright page
 *
 *
 * Tutorial 4: 3d engine - 3ds models loader
 * 
 * File header: tutorial4.h
 *  
 */



/**********************************************************
 *
 * TYPES DECLARATION
 *
 *********************************************************/

#define MAX_VERTICES 8000 // Max number of vertices (for each object)
#define MAX_POLYGONS 8000 // Max number of polygons (for each object)



//GLenum m_type=GL_POINTS;
// Our vertex type
typedef struct{
    float x,y,z;
}vertex_type;

// The polygon (triangle), 3 numbers that aim 3 vertices
typedef struct{
    unsigned short a,b,c;
}polygon_type;

// The mapcoord type, 2 texture coordinates for each vertex
typedef struct{
    float u,v;
}mapcoord_type;

// The object type
typedef struct {
	char name[20];
    
	int vertices_qty;
    int polygons_qty;

    vertex_type vertex[MAX_VERTICES]; 
    polygon_type polygon[MAX_POLYGONS];
    mapcoord_type mapcoord[MAX_VERTICES];
    int id_texture,id_texture2;
} obj_type, *obj_type_ptr;






 char Load3DS (obj_type_ptr ogg, char *filename);
void  display();
void  sdisplay();
void modify(float x, CString selectedString);
int LoadBitmap(CString path,int tlevel,int blevel,float clevel);
void setTexture(CString path);
void init();
void changeMode(GLenum mode);
void LoadImage(CString path,int tlevel,int blevel,float clevel);
void LoadImage2(CString path,int tlevel,int blevel,float clevel);
void changeContrast(float clevel);
void reset();
void move(char dir);	//move the texture 
void scaleTex();
void markVertex(int vertex);
void makeLine();
void changeVU(int x[],int y[],int cpoints[]);	// change the uv values from critical points selction
void changeXYZ(int x[],int y[],int cpoints[]);
void changeVU1(float u1,float  v1);	//change uv by considering 1st point movement
void changeVU2(float u1,float  v1);	//change uv by a linear equation
void drawBox();

void test();

extern int num_texture;