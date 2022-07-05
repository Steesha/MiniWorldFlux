#include "Value.h"

Value::Value(std::string valName, ValueType valType, void* val) : name(valName), type(valType), value(val) {

}

std::string Value::getName() {
	return this->name;
}

ValueType Value::getType() {
	return this->type;
}
