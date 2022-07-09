#ifndef _FORWARDS_HPP
#define _FORWARDS_HPP
#include <Windows.h>

#define ToUPointer(_Address) reinterpret_cast<uintptr_t*>(_Address)
#define FORWARDS_FN_START(_FunctionName) __declspec(naked) void _FunctionName()
#define FORWARDS_FN_END(_BackflowAddress) \
__asm push [_BackflowAddress] \
__asm ret

class Forwards {
	
public:
	Forwards() : target(0x00000000), destnation(0x00000000) {
		
	}

	Forwards(uintptr_t target, uintptr_t destnation) : target(target), destnation(destnation) {
		
		// Backup the origin code
		RtlCopyMemory(&this->originCode, ToUPointer(target), 6);

		// Build the detour code
		RtlCopyMemory(&(this->detourCode[1]), &destnation, 4);
		
	}

	void init(uintptr_t target, uintptr_t destnation) {
		this->target = target;
		this->destnation = destnation;

		// Backup the origin code
		RtlCopyMemory(&this->originCode, ToUPointer(target), 6);

		// Build the detour code
		RtlCopyMemory(&(this->detourCode[1]), &destnation, 4);
	}

	void forward() {
		RtlCopyMemory(ToUPointer(this->target), this->detourCode, 6);
	}

	void reset() {
		RtlCopyMemory(ToUPointer(this->target), this->originCode, 6);
	}

private:
	uintptr_t target;		// Hook Address
	uintptr_t destnation;	// Forwards function
	unsigned char originCode[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	unsigned char detourCode[6] = { 0x68, 0x00, 0x00, 0x00, 0x00, 0xC3 };

};

#endif // _FORWARDS_HPP
