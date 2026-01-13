#include "GarrysMod/Lua/Interface.h"

#include "pointers.hpp"
#include "hooking/hooking.hpp"

#include <chrono>
#include <memory>

std::unique_ptr<gm_tickrate::pointers> pointers_instance;
std::unique_ptr<gm_tickrate::hooking> hooking_instance;

using namespace GarrysMod::Lua;

extern std::chrono::duration<double> frame_delta;

LUA_FUNCTION(GetFrameDelta)
{
	LUA->PushNumber(std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(frame_delta).count());

	return 1;
}

GMOD_MODULE_OPEN()
{
	using namespace gm_tickrate;

	pointers_instance = std::make_unique<pointers>();
	Msg("Pointers initialized.\n");

	hooking_instance = std::make_unique<hooking>();
	Msg("Hooking initialized.\n");

	g_hooking->enable();
	Msg("Hooking enabled.\n");

	LUA->PushSpecial( GarrysMod::Lua::SPECIAL_GLOB );
	LUA->PushString( "GetFrameDelta" );
	LUA->PushCFunction( GetFrameDelta );
	LUA->SetTable( -3 ); // `_G.GetFrameDelta = GetFrameDelta`

	return 0;
}

GMOD_MODULE_CLOSE()
{
	using namespace gm_tickrate;

	g_hooking->disable();
	Msg("Hooking disabled.\n");

	hooking_instance.reset();
	Msg("Hooking uninitialized.\n");

	pointers_instance.reset();
	Msg("Pointers uninitialized.\n");

	return 0;
}
