#pragma once

#include "Tdsloader.h"
class feature
{
public:
	feature(void);
	~feature(void);
	void set3Dobject(obj_type_ptr pObject);

	void changeNose(obj_type_ptr pObject, float aggesmntVal);

	void changeMouth(obj_type_ptr pObject,float aggesmntVal);

	void changeLeftEye(obj_type_ptr pObject,float aggesmntVal);
	void changeRightEye(obj_type_ptr pObject,float aggesmntVal);

	void changeCheek(obj_type_ptr pObject, float val);


	float calculateGradiant(float y, float x, float change);
};
