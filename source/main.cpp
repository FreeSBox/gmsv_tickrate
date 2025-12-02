#include "GarrysMod/Lua/Interface.h"

#include "pointers.hpp"
#include "byte_patch_manager.hpp"

#include <memory>


std::unique_ptr<pointers> pointers_instance;
std::unique_ptr<byte_patch_manager> byte_patch_manager_instance;

GMOD_MODULE_OPEN()
{
	pointers_instance = std::make_unique<pointers>();
	Msg("Pointers initialized.\n");

	byte_patch_manager_instance = std::make_unique<byte_patch_manager>();
	Msg("Byte Patch Manager initialized.\n");

	return 0;
}

GMOD_MODULE_CLOSE()
{
	byte_patch_manager_instance.reset();
	Msg("Byte Patch Manager uninitialized.\n");

	pointers_instance.reset();
	Msg("Pointers uninitialized.\n");

	return 0;
}
