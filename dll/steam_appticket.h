/* Copyright (C) 2019 Mr Goldberg
   This file is part of the Goldberg Emulator

   The Goldberg Emulator is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 3 of the License, or (at your option) any later version.

   The Goldberg Emulator is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the Goldberg Emulator; if not, see
   <http://www.gnu.org/licenses/>.  */

#include "base.h"

// ISteamAppTicket (SDK 1.53+). Provides a ticket proving app ownership.
class Steam_AppTicket :
public ISteamAppTicket
{
    class Settings *settings;

public:
    Steam_AppTicket(class Settings *settings)
    {
        this->settings = settings;
    }

    uint32 GetAppOwnershipTicketData( uint32 nAppID, void *pvBuffer, uint32 cbBufferLength, uint32 *piAppId, uint32 *piSteamId, uint32 *piSignature, uint32 *pcbSignature )
    {
        PRINT_DEBUG("Steam_AppTicket::GetAppOwnershipTicketData %u %u\n", nAppID, cbBufferLength);

        AppTicketV1 ticket;
        ticket.Reset();
        ticket.TicketVersion = 1;

        auto serialized = ticket.Serialize();

        uint32 needed = serialized.size();
        if (piAppId) *piAppId = nAppID;
        if (piSteamId) *piSteamId = settings->get_local_steam_id().GetAccountID();
        if (piSignature) *piSignature = 0;
        if (pcbSignature) *pcbSignature = 0;

        if (!pvBuffer) return needed;
        if (cbBufferLength < needed) return needed;
        memcpy(pvBuffer, serialized.data(), needed);
        return needed;
    }
};
