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
		void init_server();

	public:

		void* m_allow_invalid_ticket{};
		void* m_allow_wrong_game{};
		void* m_allow_all_invalid_tickets{};

		void* m_concommand_is_blocked{};

		void* m_check_for_duplicate_steamid{};

		IServer* m_sv{};
	};

	inline pointers* g_pointers{};
}
