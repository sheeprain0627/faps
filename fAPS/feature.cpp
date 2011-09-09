#include "StdAfx.h"
#include "feature.h"
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


//**************spring model deformation of ****************//
void feature::changeNose(obj_type_ptr pObject, float aggesmntVal){
	
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


	for(int i=0;i<12;i++){
	

	float gradiant1=calculateGradiant(pObject->vertex[highVal[i]].x, pObject->vertex[highMid[i]].x, (aggesmntVal/(i+1)));
	float gradiant2=calculateGradiant(pObject->vertex[lowVal[i]].x, pObject->vertex[lowMid[i]].x, -((aggesmntVal)/(i+1)));
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
}


//****************change mouth coordinates*********************//
void feature::changeMouth(obj_type_ptr pObject,float aggesmntVal){
	int highVal[12]={197,228,259,289,318,350}; // first lover lip points then upper lip points
	int lowVal[12]=	{190,218,247,276,307,337};
	int highMid[12]={194,283,254,223,313,344};
	int lowMid[12]=	{193,283,253,223,313,343};

	for(int i=0;i<6;i++){
	

	float gradiant1=calculateGradiant(pObject->vertex[highVal[i]].x, pObject->vertex[highMid[i]].x, (aggesmntVal/(i+1)));
	float gradiant2=calculateGradiant(pObject->vertex[lowVal[i]].x, pObject->vertex[lowMid[i]].x, -(aggesmntVal/(i+1)));
	
	for(int j=(highMid[i]+1); j<=highVal[i];j++){

		pObject->vertex[j].x=gradiant1*(ori_pObject.vertex[j].x);
		
	}

	for(int k=(lowVal[i]);k<lowMid[i];k++){
		
		pObject->vertex[k].x=gradiant2*(ori_pObject.vertex[k].x);
		
}

	}
	
}

// ****************change left eye coordinates ***********************//
void feature::changeLeftEye(obj_type_ptr pObject, float aggesmntVal){
	int highVal[5]={860,900,946,987,1030}; // 
	int lowVal[5]=	{863,902,950,997,1041};

	
	for(int i=0;i<5;i++){
	

	float gradiant1=calculateGradiant(pObject->vertex[highVal[i]].x, pObject->vertex[lowVal[i]].x, (-aggesmntVal/(i+1)));
	

	for(int j=(lowVal[i]-1); j>=highVal[i];j--){

		pObject->vertex[j].x=gradiant1*(ori_pObject.vertex[j].x);
	}
	}
}


//****************change right eye coordinates***********************//
void feature::changeRightEye(obj_type_ptr pObject, float aggesmntVal){
	int highVal[5]={881,920,967,1012,1056}; // 
	int lowVal[5]=	{879,918,965,1003,1046};

	for(int i=0;i<5;i++){
	

	float gradiant1=calculateGradiant(pObject->vertex[highVal[i]].x, pObject->vertex[lowVal[i]].x, (aggesmntVal/(i+1)));
	
	for(int j=(lowVal[i]+1); j<=highVal[i];j++){

		pObject->vertex[j].x=gradiant1*(ori_pObject.vertex[j].x);
		
	}
	}
}

//************************deformation of cheek in 3D model************//

void feature::changeCheek(obj_type_ptr pObject,  float aggesmntVal ){

	
	int values_11[3]={107,108,109};
	int values_10[3]={129,130,131};
	int values_9[3]={152,153,154};
	int values_8[2]={175,176};
	int values_7[2]={203,204};
	int values_6[1]={233};
	int values_5[1]={263};
	int values_4[2]={291,292};
	int values_3[2]={321,322};
	int values_2[3]={351,352,353};
	int values_1[4]={382,383,384,385};
	int values0[5]={413,414,415,416,417};
	int values1[6]={443,444,445,446,447,448};
	int values2[7]={474,475,476,477,478,479,480};
	int values3[7]={507,508,509,510,511,512,513};
	int values4[6]={541,542,543,544,545,546};
	int values5[5]={576,577,578,579,580};
	int values6[4]={610,611,612,613};
	int values7[3]={650,651,652};
	int values8[2]={690,691};



	int c1values_11[3]={117,118,119};
	int c1values_10[3]={139,140,141};
	int c1values_9[3]={162,163,164};
	int c1values_8[2]={187,188};
	int c1values_7[2]={215,261};
	int c1values_6[1]={244};
	int c1values_5[1]={274};
	int c1values_4[2]={304,302};
	int c1values_3[2]={334,335};
	int c1values_2[3]={366,367,368};
	int c1values_1[4]={396,397,398,399};
	int c1values0[5]={427,428,429,430,431};
	int c1values1[6]={456,457,458,459,460,461};
	int c1values2[7]={489,490,491,492,493,494,495};
	int c1values3[7]={522,523,524,525,526,527,528};
	int c1values4[6]={559,560,561,562,563,564};
	int c1values5[5]={594,595,596,597,598};
	int c1values6[4]={632,633,634,635};
	int c1values7[3]={673,674,675};
	int c1values8[2]={713,714};



	//float aggesmntVal=0.2;
	printf("pls enter the cheek changing value\t");
	///scanf("%f",&aggesmntVal);
	

	for(int j=0; j<7;j++){

		
		pObject->vertex[values2[j]].z=ori_pObject.vertex[values2[j]].z - aggesmntVal *4/8 ;
		pObject->vertex[values3[j]].z=ori_pObject.vertex[values3[j]].z - aggesmntVal *4/8 ;
		
		
	}


	for(int j=0; j<7;j++){

		
		pObject->vertex[c1values2[j]].z=ori_pObject.vertex[c1values2[j]].z - aggesmntVal *4/8 ;
		pObject->vertex[c1values3[j]].z=ori_pObject.vertex[c1values3[j]].z - aggesmntVal *4/8 ;
		
	}

	for(int j=0; j<6;j++){
		pObject->vertex[values1[j]].z=ori_pObject.vertex[values1[j]].z - aggesmntVal*4/8 ;

		pObject->vertex[values4[j]].z=ori_pObject.vertex[values4[j]].z - aggesmntVal *4/8 ;
		
	}

	
	for(int j=0; j<6;j++){
		pObject->vertex[c1values1[j]].z=ori_pObject.vertex[c1values1[j]].z - aggesmntVal*4/8 ;

		pObject->vertex[c1values4[j]].z=ori_pObject.vertex[c1values4[j]].z - aggesmntVal *4/8 ;
		
	}
	for(int j=0; j<5;j++){
	
		pObject->vertex[values0[j]].z=ori_pObject.vertex[values0[j]].z - aggesmntVal *4/8 ;
		pObject->vertex[values5[j]].z=ori_pObject.vertex[values5[j]].z - aggesmntVal *4/8 ;
		
	}

	for(int j=0; j<5;j++){
	
		pObject->vertex[c1values0[j]].z=ori_pObject.vertex[c1values0[j]].z - aggesmntVal *4/8 ;
		pObject->vertex[c1values5[j]].z=ori_pObject.vertex[c1values5[j]].z - aggesmntVal *4/8 ;
		
	}


	for(int j=0; j<4;j++){

	
		pObject->vertex[values_1[j]].z=ori_pObject.vertex[values_1[j]].z - aggesmntVal *4/8 ;
		
		pObject->vertex[values6[j]].z=ori_pObject.vertex[values6[j]].z - aggesmntVal *4/8 ;
		
	}

	
	for(int j=0; j<4;j++){

	
		pObject->vertex[c1values_1[j]].z=ori_pObject.vertex[c1values_1[j]].z - aggesmntVal*4/8 ;
		
		pObject->vertex[c1values6[j]].z=ori_pObject.vertex[c1values6[j]].z - aggesmntVal*4/8 ;
		
	}

	for(int j=0; j<3;j++){

		
		pObject->vertex[values7[j]].z=ori_pObject.vertex[values7[j]].z - aggesmntVal*4/8 ;
		pObject->vertex[values_2[j]].z=ori_pObject.vertex[values_2[j]].z - aggesmntVal*4/8 ;
		pObject->vertex[values_9[j]].z=ori_pObject.vertex[values_9[j]].z - aggesmntVal*4/8 ;
		pObject->vertex[values_10[j]].z=ori_pObject.vertex[values_10[j]].z - aggesmntVal*4/8 ;
		pObject->vertex[values_11[j]].z=ori_pObject.vertex[values_11[j]].z - aggesmntVal*4/8 ;
	}

	for(int j=0; j<3;j++){

		pObject->vertex[c1values7[j]].z=ori_pObject.vertex[c1values7[j]].z - aggesmntVal*4/8 ;
		pObject->vertex[c1values_2[j]].z=ori_pObject.vertex[c1values_2[j]].z - aggesmntVal*4/8 ;
		pObject->vertex[c1values_9[j]].z=ori_pObject.vertex[c1values_9[j]].z - aggesmntVal*4/8 ;
		pObject->vertex[c1values_10[j]].z=ori_pObject.vertex[c1values_10[j]].z - aggesmntVal*4/8 ;
		pObject->vertex[c1values_11[j]].z=ori_pObject.vertex[c1values_11[j]].z - aggesmntVal*4/8 ;
		
	}
	
	for(int j=0; j<2;j++){

		pObject->vertex[values_8[j]].z=ori_pObject.vertex[values_8[j]].z - aggesmntVal*4/8 ;
		pObject->vertex[values_7[j]].z=ori_pObject.vertex[values_7[j]].z - aggesmntVal*4/8 ;
		pObject->vertex[values_4[j]].z=ori_pObject.vertex[values_4[j]].z - aggesmntVal*4/8 ;
		pObject->vertex[values_3[j]].z=ori_pObject.vertex[values_3[j]].z - aggesmntVal*4/8 ;
		pObject->vertex[values8[j]].z=ori_pObject.vertex[values8[j]].z - aggesmntVal*4/8 ;
		
	}

	for(int j=0; j<2;j++){

		
		pObject->vertex[c1values_8[j]].z=ori_pObject.vertex[c1values_8[j]].z - aggesmntVal*4/8 ;
		pObject->vertex[c1values_7[j]].z=ori_pObject.vertex[c1values_7[j]].z - aggesmntVal*4/8 ;
		pObject->vertex[c1values_4[j]].z=ori_pObject.vertex[c1values_4[j]].z - aggesmntVal*4/8 ;
		pObject->vertex[c1values_3[j]].z=ori_pObject.vertex[c1values_3[j]].z - aggesmntVal*4/8 ;
		pObject->vertex[c1values8[j]].z=ori_pObject.vertex[c1values8[j]].z - aggesmntVal*4/8 ;
		
	}

	for(int j=45; j<=100;j++){

		pObject->vertex[j].z=ori_pObject.vertex[j].z - aggesmntVal/2;
		
	}
	
	pObject->vertex[c1values_5[0]].z=ori_pObject.vertex[c1values_5[0]].z - aggesmntVal*4/8 ;
	pObject->vertex[c1values_6[0]].z=ori_pObject.vertex[c1values_6[0]].z - aggesmntVal*4/8 ;
	pObject->vertex[values_5[0]].z=ori_pObject.vertex[values_5[0]].z - aggesmntVal*4/8 ;
	pObject->vertex[values_6[0]].z=ori_pObject.vertex[values_6[0]].z - aggesmntVal*4/8 ;
}

//********************use to appply linear interpolation****************//

float feature::calculateGradiant(float changingVertex, float nonChangingVertex, float changeVal){
//float gradiant;

	float y1y2;
	float x1x2;
	//float gradiant;
	y1y2=(changingVertex + changeVal - nonChangingVertex);
	x1x2=(changingVertex - nonChangingVertex);

return y1y2/x1x2;
}