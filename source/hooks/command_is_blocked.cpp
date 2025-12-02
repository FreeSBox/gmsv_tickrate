#include "hooking/hooking.hpp"
#include <dbg.h>

namespace gm
{
	char* hooks::ConCommand_IsBlocked(char* command)
	{
		return nullptr;
	}
}
