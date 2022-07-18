#include "pch.h"
#include "FastSkill.h"

FastSkill::FastSkill() : AbstractModule("FastSkill", Category::Player) {
	fastSkillChecker.init(ToPointer(Client::hWorld + (Offsets::getOffset(Of_FastSkill) ^ Client::_XorKey), unsigned char), 8);
}

FastSkill* FastSkill::getInstance() {
	static FastSkill* inst = new FastSkill();
	return inst;
}

void FastSkill::onEnabled() {
	IngameCheck;

	VM_TIGER_WHITE_START
	fastSkillChecker.destroy();
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_FastSkill) ^ Client::_XorKey) + 0, 0x0F);
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_FastSkill) ^ Client::_XorKey) + 1, 0x57);
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_FastSkill) ^ Client::_XorKey) + 2, 0xC0);
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_FastSkill) ^ Client::_XorKey) + 3, 0x90);
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_FastSkill) ^ Client::_XorKey) + 4, 0x90);
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_FastSkill) ^ Client::_XorKey) + 5, 0x90);
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_FastSkill) ^ Client::_XorKey) + 6, 0x90);
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_FastSkill) ^ Client::_XorKey) + 7, 0x90);
	fastSkillChecker.restore();
	VM_TIGER_WHITE_END

}

void FastSkill::onDisabled()
{
	IngameCheck;
	
	VM_TIGER_WHITE_START
	fastSkillChecker.destroy();
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_FastSkill) ^ Client::_XorKey) + 0, 0xF3);
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_FastSkill) ^ Client::_XorKey) + 1, 0x0F);
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_FastSkill) ^ Client::_XorKey) + 2, 0x59);
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_FastSkill) ^ Client::_XorKey) + 3, 0x05);
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_FastSkill) ^ Client::_XorKey) + 4, 0x38);
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_FastSkill) ^ Client::_XorKey) + 5, 0x16);
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_FastSkill) ^ Client::_XorKey) + 6, 0xBC);
	Memory::write<unsigned char>(Client::hWorld + (Offsets::getOffset(Of_FastSkill) ^ Client::_XorKey) + 7, 0x79);
	fastSkillChecker.restore();
	VM_TIGER_WHITE_END

}
