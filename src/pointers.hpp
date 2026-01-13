#pragma once

class IServer;

namespace gm
{
	class pointers
	{
	public:
		explicit pointers();
		~pointers();

	private:
		void init_engine();

	public:

		void* m_run_frame{};
	};

	inline pointers* g_pointers{};
}
