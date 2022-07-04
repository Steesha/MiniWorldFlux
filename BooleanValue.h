#pragma once
#include "Value.h"

class BooleanValue : public Value {

public:
	
	BooleanValue(std::string name);
	BooleanValue(std::string name, bool current);

	bool getValue();
	void setValue(bool newVal);
	void toggle();

private:
	bool value;

};

