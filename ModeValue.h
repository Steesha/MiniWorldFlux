#pragma once
#include <unordered_set>
#include "Value.h"

class ModeValue : public Value {

public:

	ModeValue(std::string name, std::string current);

	std::string getValue();
	std::unordered_set<std::string> getModes();

	bool setValue(std::string newVal);

	bool addMode(std::string mode);

	bool isCurrentMode(std::string mode);

	void setUnfold(bool unfold);
	bool isUnfold();
	void toggleUnfold();

private:

	bool unfold;
	std::string value;
	std::unordered_set<std::string> modes;
	
};

