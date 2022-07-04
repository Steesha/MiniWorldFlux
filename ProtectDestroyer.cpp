#include "ProtectDestroyer.h"

namespace Memory {
	
	void ProtectDestroyer::init(void* address, size_t size) {
		this->address = address;
		this->size = size;
	}

	bool ProtectDestroyer::destroy() {
		
		int res = VirtualProtect(this->address, size, PAGE_EXECUTE_READWRITE, &(this->originalProtect));
		return res != 0;
	}

	void ProtectDestroyer::restore() {
		
		VirtualProtect(this->address, size, this->originalProtect, nullptr);
	}

	void* ProtectDestroyer::getAddress() {
		return this->address;
	}

}
