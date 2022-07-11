#pragma once
#include "pch.h"

using Address = unsigned long;
using Offset = unsigned long;

#define ToAddress(_Pointer) reinterpret_cast<Address>(_Pointer)
#define ToPointer(_Address, _Type) reinterpret_cast<_Type*>(_Address)

namespace Memory {
	
	template <class Type>
	Type* read(Address base, Offset offset) {
		
		Type* addr = reinterpret_cast<Type*>(base + offset);
		if (IsBadReadPtr(addr, sizeof(addr)) == 0) {
			return addr;
		}
		else {
			return nullptr;
		}
	}

	template <class Data>
	bool write(Address addr, Data data) {

		Data* dataPtr = reinterpret_cast<Data*>(addr);
		if (IsBadWritePtr(dataPtr, sizeof(dataPtr)) == 0) {
			*dataPtr = data;
			if (*dataPtr == data) return true;
		}

		return false;
	}

}


