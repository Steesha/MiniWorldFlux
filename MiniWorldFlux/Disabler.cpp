#include "pch.h"
#include "Disabler.h"

Disabler::Disabler() : AbstractModule("Disabler", Category::World) {

	Address* enumWndAddr = reinterpret_cast<Address*>(GetProcAddress(GetModuleHandleA("user32.dll"), "EnumWindows"));
	this->enumWndProtect.init(enumWndAddr, 5);
	Address* enumProcAddr = reinterpret_cast<Address*>(GetProcAddress(GetModuleHandleA("kernelbase.dll"), "K32EnumProcesses"));
	this->enumProcProtect.init(enumProcAddr, 5);
}

Disabler* Disabler::getInstance() {
	static Disabler* inst = new Disabler();
	return inst;
}

void Disabler::onEnabled() {
	
	if (this->bypassed) return;

	this->enumWndProtect.destroy();
	this->enumProcProtect.destroy();
	memcpy(this->enumWndProtect.getAddress(), this->bypassAsm, 5);
	memcpy(this->enumProcProtect.getAddress(), this->bypassAsm, 5);
	this->enumWndProtect.restore();
	this->enumProcProtect.restore();

	this->bypassed = true;

}

void Disabler::onDisabled() {

	if (!this->bypassed) return;

	this->enumWndProtect.destroy();
	this->enumProcProtect.destroy();
	memcpy(this->enumWndProtect.getAddress(), this->enumWndAsm, 5);
	memcpy(this->enumProcProtect.getAddress(), this->enumProcAsm, 5);
	this->enumWndProtect.restore();
	this->enumProcProtect.restore();

	this->bypassed = false;

}

