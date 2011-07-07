#include "StdAfx.h"
#include "feature.h"
//#include "tutorial4.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>


feature::feature(void)
{
}


feature::~feature(void)
{
}


//#include "main.h"
//#include "3ds.h"
//#include "feature.h"

obj_type ori_pObject;


void feature::set3Dobject(obj_type_ptr pObject){

	ori_pObject.vertices_qty=pObject->vertices_qty;

	//ori_pObject.vertex = new  [pObject->numOfVerts];

	for(int i=0;i<pObject->vertices_qty;i++){
		ori_pObject.vertex[i].x=pObject->vertex[i].x;
		ori_pObject.vertex[i].y=pObject->vertex[i].y;
		ori_pObject.vertex[i].z=pObject->vertex[i].z;
	}
	//ori_pObject=pObject;
}

// change nose cordinates


void feature::changeNose(obj_type_ptr pObject, float aggesmntVal){
	//printf("%f\n",pObject->vertex[469].x);
	//printf("%f\n",pObject->vertex[470].x);
	//printf("%f\n",pObject->vertex[471].x);
	//printf("%f\n",pObject->vertex[472].x);

	//float y1y2;
	//float x1x2;
	int highVal[12]={472,506,540,575,609,647,686,724,760,797,835,873};
	int lowVal[12]=	{464,497,530,565,600,637,676,716,752,790,829,869};
	int highMid[12]={469,503,536,570,605,643,682,721,757,794,833,872};
	int lowMid[12]=	{467,500,535,569,604,642,680,719,755,793,831,870};

	//float aggesmntVal;
	printf("%f\n",pObject->vertex[472].x);
	printf("%f\n",pObject->vertex[472].y);
	printf("%f\n",pObject->vertex[464].x);
	printf("%f\n",pObject->vertex[464].y);
	printf("%f\n",pObject->vertex[468].x);
	printf("%f\n",pObject->vertex[468].y);


	//printf("pls enter the nose changing value\t");
	//scanf("%f",&aggesmntVal);
	//printf("%f",aggesmntVal);

	//aggesmntVal=0.2;

	///////////////////////////////////////////////////////////////////////////////////////////////

	//int highval=472;
	//int highmid=469;
	//int lowval=464;
	//int lowmid=467;
	for(int i=0;i<12;i++){
	

	float gradiant1=calculateGradiant(pObject->vertex[highVal[i]].x, pObject->vertex[highMid[i]].x, (aggesmntVal/(i+1)));
	float gradiant2=calculateGradiant(pObject->vertex[lowVal[i]].x, pObject->vertex[lowMid[i]].x, -((aggesmntVal+0.05)/(i+1)));
	//y1y2=(pObject->vertex[472].x + 0.06 - pObject->vertex[469].x);
	//x1x2=(pObject->vertex[472].x - pObject->vertex[469].x);
	//c=pObject->vertex[469].x;

	for(int j=(highMid[i]+1); j<=highVal[i];j++){

		pObject->vertex[j].x=gradiant1*(ori_pObject.vertex[j].x);
		//pObject->vertex[471].x=gradiant1*(pObject->vertex[highval-1].x);
		//pObject->vertex[470].x=gradiant1*(pObject->vertex[highval-2].x);
	}

	for(int k=(lowVal[i]);k<lowMid[i];k++){
		//pObject->vertex[467].x=gradiant2*(pObject->vertex[467].x);
		pObject->vertex[k].x=gradiant2*(ori_pObject.vertex[k].x);
		//pObject->vertex[465].x=gradiant2*(pObject->vertex[465].x);
		//pObject->vertex[464].x=gradiant2*(pObject->vertex[464].x);
}

	}

////////////////////////////////////////////////////////////////////////////////////////////////////////
		//pObject->vertex[835].x=pObject->vertex[835].x + 0.9;
		//pObject->vertex[872].x=pObject->vertex[873].x + 0.45;
		//pObject->vertex[870].x=pObject->vertex[870].x - 0.45;
		//pObject->vertex[829].x=pObject->vertex[829].x - 0.9;
	//pObject->vertex[469].x=pObject->vertex[469].x + 0.9;

//printf("new values \n");
	//printf("%f\n",pObject->vertex[435].x);
	//printf("%f\n",pObject->vertex[469].x);
	//printf("%f\n",pObject->vertex[470].x);
	//printf("%f\n",pObject->vertex[471].x);
	//printf("%f\n",pObject->vertex[472].x);
}


//change mouth coordinates
void feature::changeMouth(obj_type_ptr pObject,float aggesmntVal){
	int highVal[12]={197,228,259,289,318,350}; // first lover lip points then upper lip points
	int lowVal[12]=	{190,218,247,276,307,337};
	int highMid[12]={194,283,254,223,313,344};
	int lowMid[12]=	{193,283,253,223,313,343};



	//float aggesmntVal;
	//printf("pls enter the mouth changing value\t");
	//scanf("%f",&aggesmntVal);

	//aggesmntVal=0.05;

	///////////////////////////////////////////////////////////////////////////////////////////////

	//int highval=472;
	//int highmid=469;
	//int lowval=464;
	//int lowmid=467;
	for(int i=0;i<6;i++){
	

	float gradiant1=calculateGradiant(pObject->vertex[highVal[i]].x, pObject->vertex[highMid[i]].x, (aggesmntVal/(i+1)));
	float gradiant2=calculateGradiant(pObject->vertex[lowVal[i]].x, pObject->vertex[lowMid[i]].x, -(aggesmntVal/(i+1)));
	//y1y2=(pObject->vertex[472].x + 0.06 - pObject->vertex[469].x);
	//x1x2=(pObject->vertex[472].x - pObject->vertex[469].x);
	//c=pObject->vertex[469].x;

	for(int j=(highMid[i]+1); j<=highVal[i];j++){

		pObject->vertex[j].x=gradiant1*(ori_pObject.vertex[j].x);
		//pObject->vertex[471].x=gradiant1*(pObject->vertex[highval-1].x);
		//pObject->vertex[470].x=gradiant1*(pObject->vertex[highval-2].x);
	}

	for(int k=(lowVal[i]);k<lowMid[i];k++){
		//pObject->vertex[467].x=gradiant2*(pObject->vertex[467].x);
		pObject->vertex[k].x=gradiant2*(ori_pObject.vertex[k].x);
		//pObject->vertex[465].x=gradiant2*(pObject->vertex[465].x);
		//pObject->vertex[464].x=gradiant2*(pObject->vertex[464].x);
}

	}
	//pObject->vertex[350].y=pObject->vertex[350].y+0.5;
	//pObject->vertex[337].y=pObject->vertex[337].y+0.5;
}

// change left eye coordinates
void feature::changeLeftEye(obj_type_ptr pObject, float aggesmntVal){
	int highVal[5]={860,900,946,987,1030}; // 
	int lowVal[5]=	{863,902,950,997,1041};

	//pObject->vertex[1041].y=pObject->vertex[860].y+0.5;
	//pObject->vertex[1030].y=pObject->vertex[867].y+0.5;

	//float aggesmntVal;
	//printf("pls enter the left eye changing value\t");
	//scanf("%f",&aggesmntVal);
	for(int i=0;i<5;i++){
	

	float gradiant1=calculateGradiant(pObject->vertex[highVal[i]].x, pObject->vertex[lowVal[i]].x, (-aggesmntVal/(i+1)));
	//float gradiant2=calculateGradiant(pObject->vertex[lowVal[i]].x, pObject->vertex[lowMid[i]].x, -(aggesmntVal/(i+1)));
	//y1y2=(pObject->vertex[472].x + 0.06 - pObject->vertex[469].x);
	//x1x2=(pObject->vertex[472].x - pObject->vertex[469].x);
	//c=pObject->vertex[469].x;

	for(int j=(lowVal[i]-1); j>=highVal[i];j--){

		pObject->vertex[j].x=gradiant1*(ori_pObject.vertex[j].x);
		//pObject->vertex[471].x=gradiant1*(pObject->vertex[highval-1].x);
		//pObject->vertex[470].x=gradiant1*(pObject->vertex[highval-2].x);
	}
	}
}


//change right eye coordinates
void feature::changeRightEye(obj_type_ptr pObject, float aggesmntVal){
	int highVal[5]={881,920,967,1012,1056}; // 
	int lowVal[5]=	{879,918,965,1003,1046};

	//pObject->vertex[1046].y=pObject->vertex[860].y+0.5;
	//pObject->vertex[1056].y=pObject->vertex[867].y+0.5;

	//float aggesmntVal;
	//printf("pls enter the right eye changing value\t");
	//scanf("%f",&aggesmntVal);
	for(int i=0;i<5;i++){
	

	float gradiant1=calculateGradiant(pObject->vertex[highVal[i]].x, pObject->vertex[lowVal[i]].x, (aggesmntVal/(i+1)));
	//float gradiant2=calculateGradiant(pObject->vertex[lowVal[i]].x, pObject->vertex[lowMid[i]].x, -(aggesmntVal/(i+1)));
	//y1y2=(pObject->vertex[472].x + 0.06 - pObject->vertex[469].x);
	//x1x2=(pObject->vertex[472].x - pObject->vertex[469].x);
	//c=pObject->vertex[469].x;

	for(int j=(lowVal[i]+1); j<=highVal[i];j++){

		pObject->vertex[j].x=gradiant1*(ori_pObject.vertex[j].x);
		//pObject->vertex[471].x=gradiant1*(pObject->vertex[highval-1].x);
		//pObject->vertex[470].x=gradiant1*(pObject->vertex[highval-2].x);
	}
	}
}


float feature::calculateGradiant(float changingVertex, float nonChangingVertex, float changeVal){
//float gradiant;

	float y1y2;
	float x1x2;
	//float gradiant;
	y1y2=(changingVertex + changeVal - nonChangingVertex);
	x1x2=(changingVertex - nonChangingVertex);

return y1y2/x1x2;
}