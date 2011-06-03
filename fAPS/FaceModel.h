#pragma once
class FaceModel
{
public:
		  // Our vertex type
struct vertex_type {
    float x,y,z;
} ;

// The polygon (triangle), 3 numbers that aim 3 vertices
struct polygon_type {
    int a,b,c;
} Polygon;

// The object type
struct obj_type { 
    vertex_type vertex[1000]; 
    polygon_type polygon[1000];
} ;

	FaceModel(void);
	virtual ~FaceModel(void);
	void  display(obj_type cube);
	obj_type defineObject(void);

private:
	obj_type object ;


	  

};