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

// ISteamTimeline (SDK 1.53+). The Steam Timeline is a purely cosmetic Steam
// client feature; the emulator accepts all event/game-phase calls and reports
// that no recordings exist.
class Steam_Timeline :
public ISteamTimeline001,
public ISteamTimeline
{
    class Settings *settings;
    class SteamCallResults *callback_results;

public:
    Steam_Timeline(class Settings *settings, class SteamCallResults *callback_results)
    {
        this->settings = settings;
        this->callback_results = callback_results;
    }

    // ISteamTimeline001 (SDK 1.60) methods
    void SetTimelineStateDescription( const char *pchDescription, float flTimeDelta )
    {
        PRINT_DEBUG("Steam_Timeline::SetTimelineStateDescription\n");
    }

    void ClearTimelineStateDescription( float flTimeDelta )
    {
        PRINT_DEBUG("Steam_Timeline::ClearTimelineStateDescription\n");
    }

    void AddTimelineEvent( const char *pchIcon, const char *pchTitle, const char *pchDescription, uint32 unPriority, float flStartOffsetSeconds, float flDuration, ETimelineEventClipPriority ePossibleClip )
    {
        PRINT_DEBUG("Steam_Timeline::AddTimelineEvent\n");
    }

    void SetTimelineTooltip( const char *pchDescription, float flTimeDelta )
    {
        PRINT_DEBUG("Steam_Timeline::SetTimelineTooltip\n");
    }

    void ClearTimelineTooltip( float flTimeDelta )
    {
        PRINT_DEBUG("Steam_Timeline::ClearTimelineTooltip\n");
    }

    void SetTimelineGameMode( ETimelineGameMode eMode )
    {
        PRINT_DEBUG("Steam_Timeline::SetTimelineGameMode %i\n", eMode);
    }

    TimelineEventHandle_t AddInstantaneousTimelineEvent( const char *pchTitle, const char *pchDescription, const char *pchIcon, uint32 unIconPriority, float flStartOffsetSeconds, ETimelineEventClipPriority ePossibleClip )
    {
        PRINT_DEBUG("Steam_Timeline::AddInstantaneousTimelineEvent\n");
        return 0;
    }

    TimelineEventHandle_t AddRangeTimelineEvent( const char *pchTitle, const char *pchDescription, const char *pchIcon, uint32 unIconPriority, float flStartOffsetSeconds, float flDuration, ETimelineEventClipPriority ePossibleClip )
    {
        PRINT_DEBUG("Steam_Timeline::AddRangeTimelineEvent\n");
        return 0;
    }

    TimelineEventHandle_t StartRangeTimelineEvent( const char *pchTitle, const char *pchDescription, const char *pchIcon, uint32 unPriority, float flStartOffsetSeconds, ETimelineEventClipPriority ePossibleClip )
    {
        PRINT_DEBUG("Steam_Timeline::StartRangeTimelineEvent\n");
        return 0;
    }

    void UpdateRangeTimelineEvent( TimelineEventHandle_t ulEvent, const char *pchTitle, const char *pchDescription, const char *pchIcon, uint32 unPriority, ETimelineEventClipPriority ePossibleClip )
    {
        PRINT_DEBUG("Steam_Timeline::UpdateRangeTimelineEvent\n");
    }

    void EndRangeTimelineEvent( TimelineEventHandle_t ulEvent, float flEndOffsetSeconds )
    {
        PRINT_DEBUG("Steam_Timeline::EndRangeTimelineEvent\n");
    }

    void RemoveTimelineEvent( TimelineEventHandle_t ulEvent )
    {
        PRINT_DEBUG("Steam_Timeline::RemoveTimelineEvent\n");
    }

    SteamAPICall_t DoesEventRecordingExist( TimelineEventHandle_t ulEvent )
    {
        PRINT_DEBUG("Steam_Timeline::DoesEventRecordingExist\n");
        return 0;
    }

    void StartGamePhase()
    {
        PRINT_DEBUG("Steam_Timeline::StartGamePhase\n");
    }

    void EndGamePhase()
    {
        PRINT_DEBUG("Steam_Timeline::EndGamePhase\n");
    }

    void SetGamePhaseID( const char *pchPhaseID )
    {
        PRINT_DEBUG("Steam_Timeline::SetGamePhaseID\n");
    }

    SteamAPICall_t DoesGamePhaseRecordingExist( const char *pchPhaseID )
    {
        PRINT_DEBUG("Steam_Timeline::DoesGamePhaseRecordingExist\n");
        return 0;
    }

    void AddGamePhaseTag( const char *pchTagName, const char *pchTagIcon, const char *pchTagGroup, uint32 unPriority )
    {
        PRINT_DEBUG("Steam_Timeline::AddGamePhaseTag\n");
    }

    void SetGamePhaseAttribute( const char *pchAttributeGroup, const char *pchAttributeValue, uint32 unPriority )
    {
        PRINT_DEBUG("Steam_Timeline::SetGamePhaseAttribute\n");
    }

    void OpenOverlayToGamePhase( const char *pchPhaseID )
    {
        PRINT_DEBUG("Steam_Timeline::OpenOverlayToGamePhase\n");
    }

    void OpenOverlayToTimelineEvent( const TimelineEventHandle_t ulEvent )
    {
        PRINT_DEBUG("Steam_Timeline::OpenOverlayToTimelineEvent\n");
    }
};
