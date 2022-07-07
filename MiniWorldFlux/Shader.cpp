#include "pch.h"
#include "Shader.h"

Shader::Shader() : AbstractModule("Shader", Category::Visual) {
	this->addValue(this->disableZBuffer);
	this->addValue(this->color);
	this->addValue(this->colR);
	this->addValue(this->colG);
	this->addValue(this->colB);
	this->addValue(this->colA);
}

Shader* Shader::getInstance() {
	static Shader* inst = new Shader();
	return inst;
}

void Shader::onEnabled() {

}

void Shader::onDisabled() {

}

bool Shader::isDisaledZBuffer() {
	return this->disableZBuffer->getValue();
}

bool Shader::isColor() {
	return this->color->getValue();
}

uint32_t Shader::getColor() {
	return D3DCOLOR_RGBA(this->colR->getValueLong(), this->colG->getValueLong(), this->colB->getValueLong(), this->colA->getValueLong());
}


