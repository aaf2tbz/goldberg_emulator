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

// ISteamGameStats (deprecated in the real SDK, kept for games built against
// SDK <= 1.17). The emulator accepts all stat-reporting calls.
class Steam_GameStats :
public ISteamGameStats
{
    class Settings *settings;
    class SteamCallResults *callback_results;

public:
    Steam_GameStats(class Settings *settings, class SteamCallResults *callback_results)
    {
        this->settings = settings;
        this->callback_results = callback_results;
    }

    SteamAPICall_t GetNewSession( int8 nAccountType, uint64 ulAccountID, int32 nAppID, RTime32 rtTimeStarted )
    {
        PRINT_DEBUG("Steam_GameStats::GetNewSession\n");
        return 0;
    }

    SteamAPICall_t EndSession( uint64 ulSessionID, RTime32 rtTimeEnded, int nReasonCode )
    {
        PRINT_DEBUG("Steam_GameStats::EndSession\n");
        return 0;
    }

    EResult AddSessionAttributeInt( uint64 ulSessionID, const char* pstrName, int32 nData )
    {
        PRINT_DEBUG("Steam_GameStats::AddSessionAttributeInt\n");
        return k_EResultOK;
    }

    EResult AddSessionAttributeString( uint64 ulSessionID, const char* pstrName, const char *pstrData )
    {
        PRINT_DEBUG("Steam_GameStats::AddSessionAttributeString\n");
        return k_EResultOK;
    }

    EResult AddSessionAttributeFloat( uint64 ulSessionID, const char* pstrName, float fData )
    {
        PRINT_DEBUG("Steam_GameStats::AddSessionAttributeFloat\n");
        return k_EResultOK;
    }

    EResult AddNewRow( uint64 *pulRowID, uint64 ulSessionID, const char *pstrTableName )
    {
        PRINT_DEBUG("Steam_GameStats::AddNewRow\n");
        if (pulRowID) *pulRowID = 0;
        return k_EResultOK;
    }

    EResult CommitRow( uint64 ulRowID )
    {
        PRINT_DEBUG("Steam_GameStats::CommitRow\n");
        return k_EResultOK;
    }

    EResult CommitOutstandingRows( uint64 ulSessionID )
    {
        PRINT_DEBUG("Steam_GameStats::CommitOutstandingRows\n");
        return k_EResultOK;
    }

    EResult AddRowAttributeInt( uint64 ulRowID, const char *pstrName, int32 nData )
    {
        PRINT_DEBUG("Steam_GameStats::AddRowAttributeInt\n");
        return k_EResultOK;
    }

    EResult AddRowAtributeString( uint64 ulRowID, const char *pstrName, const char *pstrData )
    {
        PRINT_DEBUG("Steam_GameStats::AddRowAtributeString\n");
        return k_EResultOK;
    }

    EResult AddRowAttributeFloat( uint64 ulRowID, const char *pstrName, float fData )
    {
        PRINT_DEBUG("Steam_GameStats::AddRowAttributeFloat\n");
        return k_EResultOK;
    }

    EResult AddSessionAttributeInt64( uint64 ulSessionID, const char *pstrName, int64 llData )
    {
        PRINT_DEBUG("Steam_GameStats::AddSessionAttributeInt64\n");
        return k_EResultOK;
    }

    EResult AddRowAttributeInt64( uint64 ulRowID, const char *pstrName, int64 llData )
    {
        PRINT_DEBUG("Steam_GameStats::AddRowAttributeInt64\n");
        return k_EResultOK;
    }
};
