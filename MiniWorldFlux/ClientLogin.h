#pragma once
#include "pch.h"
#include "AES.h"
#include "Offsets.h"
class ClientLogin
{
public:
	DWORD getXORKEY();

	bool Login();
private:
	DWORD xorkey = 0;
};