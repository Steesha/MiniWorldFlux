#include "pch.h"
#include "BooleanValue.h"

BooleanValue::BooleanValue(std::string name) : value(false), Value(name, ValueType::Boolean, &this->value) {
	
}

BooleanValue::BooleanValue(std::string name, bool current) : value(current), Value(name, ValueType::Boolean, &this->value) {
	
}

bool BooleanValue::getValue() {
	return Value::getValue<bool>();
}

void BooleanValue::setValue(bool newVal) {
	Value::setValue<bool>(newVal);
}

void BooleanValue::toggle() {
	this->setValue(!this->getValue());
}
