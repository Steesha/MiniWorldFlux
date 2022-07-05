#pragma once
#include <string>
#include <vector>
#include "Value.h"
#include "KeyboardSimulator.h"

#define ToggleCheck if (!this->getToggle()) return
#define DefaultConstructor(_Class) _Class() = default
#define DefaultDeconstructor(_Class) ~_Class() = default
#define NoMoveConstructor(_Class) _Class(_Class&&) = delete
#define NoCopyConstructor(_Class) _Class(const _Class&) = delete
#define NoAssignOperator(_Class) _Class& operator=(const _Class&) = delete

enum class Category : unsigned int {
	
	Combat = 0,
	Movement,
	Visual,
	Player,
	World

};

class AbstractModule {

public:

	void toggle();
	void onToggled();
	std::string getName();
	bool getToggle();
	void setToggle(bool _New);
	void enable();
	void disable();
	Category getCategory();
	Value* getValue(std::string name);
	std::vector<Value*> getValues();
	void addValue(Value* v);
	unsigned char getKey();
	void setKey(unsigned char newKey);

	virtual void onEnabled() = 0;
	virtual void onDisabled() = 0;

	AbstractModule(std::string modName, Category modCategory);
	AbstractModule(std::string modName, Category modCategory, unsigned char keyCode);
	AbstractModule(AbstractModule&& mod) = delete;
	AbstractModule(AbstractModule& other) = delete;
	virtual ~AbstractModule() = default;
	AbstractModule& operator=(const AbstractModule& _New) = delete;

protected:
	std::string name;
	Category category;
	unsigned char key;
	bool i_toggle;
	std::vector<Value*> values;

};

