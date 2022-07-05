#pragma once
#include "Value.h"

class FloatValue : public Value {

public:
	FloatValue(std::string name, float val, float min, float max);
	FloatValue(std::string name, int val, int min, int max);

	float getValue();
	long getValueLong();
	float getMin();
	float getMax();

	void setValue(float newVal);
	void setValueLong(float newVal);
	void setValueLong(long newVal);

	bool isIntegerValue();

private:
	float value;
	float min;
	float max;
	bool integer;

};

