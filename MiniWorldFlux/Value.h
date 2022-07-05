#pragma once
#include <string>

#define ToBaseValue(_ValuePtr) reinterpret_cast<Value*>(_ValuePtr)
#define ToDirectValue(_ValuePtr, _ValueType) reinterpret_cast<_ValueType*>(_ValuePtr)

enum class ValueType : unsigned int {

    Float = 0,
    Boolean,
    Mode

};

class Value {

public:
    std::string getName();
    ValueType getType();

protected:

    Value(std::string valName, ValueType valType, void* val);

    template <class GetType>
    GetType getValue();

    template <class SetType>
    void setValue(SetType newVal);

private:

    std::string name;
    ValueType type;
    void* value;

};

template <class GetType>
GetType Value::getValue() {
    GetType* val = reinterpret_cast<GetType*>(value);
    return *val;
}

template <class SetType>
void Value::setValue(SetType newVal) {
    SetType* val = reinterpret_cast<SetType*>(value);
    *val = newVal;
}
