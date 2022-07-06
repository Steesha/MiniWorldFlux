#include "pch.h"
#include "ModeValue.h"

ModeValue::ModeValue(std::string name, std::string current) : value(current), Value(name, ValueType::Mode, &this->value), unfold(false) {
	this->modes.insert(current);
}

std::string ModeValue::getValue() {
	return Value::getValue<std::string>();
}

std::unordered_set<std::string> ModeValue::getModes() {
	return this->modes;
}

bool ModeValue::setValue(std::string newVal) {
	bool res = this->modes.find(newVal) != std::end(this->modes);
	if (res) {
		Value::setValue<std::string>(newVal);
	}
	return res;
}

bool ModeValue::addMode(std::string mode) {
	auto res = this->modes.insert(mode);
	return res.second;
}

bool ModeValue::isCurrentMode(std::string mode) {
	return this->value.compare(mode) == 0;
}

void ModeValue::setUnfold(bool unfold) {
	this->unfold = unfold;
}

bool ModeValue::isUnfold() {
	return this->unfold;
}

void ModeValue::toggleUnfold() {
	this->unfold = !this->unfold;
}
