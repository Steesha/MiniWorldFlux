#include "pch.h"
#include "FloatValue.h"
#undef min
#undef max
FloatValue::FloatValue(std::string name, float val, float valMin, float valMax) : value(val), Value(name, ValueType::Float, &this->value), min(valMin), max(valMax), integer(false) {

}

FloatValue::FloatValue(std::string name, int val, int valMin, int valMax) : value(val), Value(name, ValueType::Float, &this->value), min(valMin), max(valMax), integer(true) {
	
}

float FloatValue::getValue() {
	
	float val = Value::getValue<float>();
	if (val < this->min) return this->min;
	if (val > this->max) return this->max;
	return val;
}

long FloatValue::getValueLong() {
	return lroundf(this->getValue());
}

float FloatValue::getMin() {
	return this->min;
}

float FloatValue::getMax() {
	return this->max;
}

void FloatValue::setValue(float newVal) {
	Value::setValue<float>(newVal);
}

void FloatValue::setValueLong(float newVal) {
	Value::setValue<float>(lroundf(newVal));
}

void FloatValue::setValueLong(long newVal) {
	Value::setValue<float>(static_cast<float>(newVal));
}

bool FloatValue::isIntegerValue() {
	return this->integer;
}
