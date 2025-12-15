#include "hooking/hooking.hpp"
#include "../engine/baseclient.h"
#include "../engine/sv_steamauth.h"
#include "../engine/server.h"
#include "pointers.hpp"
#include <tier0/dbg.h>

namespace gm
{
	//-----------------------------------------------------------------------------
	// Purpose: returns true if the userid's are the same
	//-----------------------------------------------------------------------------
	bool CompareUserID( const USERID_t & id1, const USERID_t & id2 )
	{
		if ( id1.idtype != id2.idtype )
			return false;

		switch ( id1.idtype )
		{
		case IDTYPE_STEAM:
		case IDTYPE_VALVE:
			{
				return (id1.steamid == id2.steamid );
			}
		default:
			break;
		}

		return false;
	}

	bool hooks::CheckForDuplicateSteamID(CSteam3Server* _this, CBaseClient* client)
	{
		if (_this->BLanOnly())
		{
			return false;
		}

		for (int i = 0; i < g_pointers->m_sv->GetClientCount(); i++)
		{
			IClient *cl = g_pointers->m_sv->GetClient( i );

			// Not connected, no SteamID yet
			if (!cl->IsConnected() || cl->IsFakeClient())
				continue;

			// This will never happen, GetNetworkID always sets idtype to IDTYPE_STEAM
			// This also crashes when cl is not const.
			//if (cl->GetNetworkID().idtype != IDTYPE_STEAM)
			//	continue;

			// don't compare this client against himself in the list
			if (client == cl)
				continue;

			if (!CompareUserID(client->GetNetworkID(), cl->GetNetworkID()))
				continue;

			INetChannel *netchan = cl->GetNetChannel();
			if (netchan && netchan->IsTimingOut())
			{
				cl->Disconnect("Was timing out when another client joined with this steamid");
				return false;
			}

			// SteamID is reused
			return true;
		}

		return false;
	}
}
