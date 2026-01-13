// garrysmod_common has pattern scanning, but it's so fucking unreadable and not documented that I'm just gonna take the YimMenu classes instead.
#include "memory/batch.hpp"
#include "memory/pattern.hpp"
#include "memory/module.hpp"

#include "pointers.hpp"

namespace gm
{
	void pointers::init_engine()
	{
		memory::batch batch;
		memory::module module("engine");

#if ARCHITECTURE_IS_X86_64
		batch.add("_Host_RunFrame", "F3 0F 11 45 D0 48", [this](memory::handle ptr) {
			m_run_frame = ptr.sub(15).as<void*>();
		});
#elif ARCHITECTURE_IS_X86
		batch.add("_Host_RunFrame", "85 F6 0F 95 45 D7", [this](memory::handle ptr) {
			m_run_frame = ptr.sub(15).as<void*>();
		});
#endif

		batch.run(module);
	}
	pointers::pointers()
	{
		init_engine();

		g_pointers = this;
	}

	pointers::~pointers()
	{
		g_pointers = nullptr;
	}
}