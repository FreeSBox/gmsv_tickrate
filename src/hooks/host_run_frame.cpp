#include "hooking/hooking.hpp"
#include <chrono>
#include <tier0/dbg.h>

std::chrono::duration<double> frame_delta{};
namespace gm
{
	void hooks::_Host_RunFrame(float time)
	{
		const std::chrono::time_point start_time = std::chrono::high_resolution_clock::now();
		g_hooking->get_original<hooks::_Host_RunFrame>()(time);
		const std::chrono::time_point end_time = std::chrono::high_resolution_clock::now();

		frame_delta = end_time-start_time;
		return;
	}
}
