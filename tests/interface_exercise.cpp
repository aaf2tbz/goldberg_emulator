// Interface exercise test for the emulator.
// Requests every ISteam* interface at every known version string, verifies a
// non-NULL pointer is returned, and calls a representative sample of the
// newest methods to catch ABI/vtable mistakes.
#include "sdk_includes/steam_api.h"
#include "sdk_includes/steam_gameserver.h"
#include "sdk_includes/isteammasterserverupdater.h"
#include "sdk_includes/isteamtv.h"
#include "sdk_includes/isteamunifiedmessages.h"
#include "sdk_includes/isteammusicremote.h"
#include "sdk_includes/isteamapplist.h"
#include "sdk_includes/steamnetworkingfakeip.h"
#include <cstdio>
#include <cstring>

static int failures = 0;
static int checks = 0;

#define CHECK(cond, msg) do { ++checks; if (!(cond)) { ++failures; std::printf("FAIL: %s\n", msg); } } while (0)

static HSteamPipe pipe_ = 0;
static HSteamUser user_ = 0;

static void *request(const char *ver)
{
    return SteamClient()->GetISteamGenericInterface(user_, pipe_, ver);
}

// ISteamClient versions
static void test_client_versions()
{
    const char *vers[] = { "SteamClient007", "SteamClient008", "SteamClient009", "SteamClient010",
                           "SteamClient011", "SteamClient012", "SteamClient013", "SteamClient014",
                           "SteamClient015", "SteamClient016", "SteamClient017", "SteamClient018",
                           "SteamClient019", "SteamClient020", "SteamClient021", "SteamClient023" };
    for (auto v : vers) {
        ISteamClient *c = (ISteamClient *)SteamInternal_CreateInterface(v);
        CHECK(c != NULL, v);
    }
    // v023 accessors
    ISteamClient *c = SteamClient();
    CHECK(c->GetISteamUser(user_, pipe_, "SteamUser023") != NULL, "GetISteamUser 023");
    CHECK(c->GetISteamFriends(user_, pipe_, "SteamFriends018") != NULL, "GetISteamFriends 018");
    CHECK(c->GetISteamApps(user_, pipe_, "STEAMAPPS_INTERFACE_VERSION009") != NULL, "GetISteamApps 009");
    CHECK(c->GetISteamUGC(user_, pipe_, "STEAMUGC_INTERFACE_VERSION021") != NULL, "GetISteamUGC 021");
    CHECK(c->GetISteamUtils(pipe_, "SteamUtils011") != NULL, "GetISteamUtils 011");
    CHECK(c->GetISteamInput(user_, pipe_, "SteamInput007") != NULL, "GetISteamInput 007");
    CHECK(c->GetISteamRemotePlay(user_, pipe_, "STEAMREMOTEPLAY_INTERFACE_VERSION004") != NULL, "GetISteamRemotePlay 004");
    CHECK(c->GetISteamUserStats(user_, pipe_, "STEAMUSERSTATS_INTERFACE_VERSION013") != NULL, "GetISteamUserStats 013");
    CHECK(c->GetISteamVideo(user_, pipe_, "STEAMVIDEO_INTERFACE_V007") != NULL, "GetISteamVideo 007");
    CHECK(c->GetISteamMatchmakingServers(user_, pipe_, "SteamMatchMakingServers003") != NULL, "MatchmakingServers 003");
    CHECK((void *)SteamNetworkingSockets_SteamAPI() != NULL, "SteamNetworkingSockets 013");
}

// intermediate interface versions
static void test_intermediate_versions()
{
    CHECK((ISteamUGC *)request("STEAMUGC_INTERFACE_VERSION018") != NULL, "UGC 018");
    CHECK((ISteamUGC *)request("STEAMUGC_INTERFACE_VERSION020") != NULL, "UGC 020");
    CHECK((ISteamUGC *)request("STEAMUGC_INTERFACE_VERSION017") != NULL, "UGC 017");
    CHECK((ISteamFriends *)request("SteamFriends017") != NULL, "Friends 017");
    CHECK((ISteamRemotePlay *)request("STEAMREMOTEPLAY_INTERFACE_VERSION001") != NULL, "RemotePlay 001");
    CHECK((ISteamRemotePlay *)request("STEAMREMOTEPLAY_INTERFACE_VERSION002") != NULL, "RemotePlay 002");
    CHECK((ISteamRemotePlay *)request("STEAMREMOTEPLAY_INTERFACE_VERSION003") != NULL, "RemotePlay 003");
    CHECK((ISteamUserStats *)request("STEAMUSERSTATS_INTERFACE_VERSION012") != NULL, "UserStats 012");
    CHECK((ISteamNetworkingSockets *)request("SteamNetworkingSockets012") != NULL, "NetSockets 012");
}

// new methods
static void test_new_methods()
{
    std::printf("marker A apps\n"); std::fflush(stdout);
    ISteamApps *apps = SteamApps();
    int avail = 0, priv = 0;
    CHECK(apps->GetNumBetas(&avail, &priv) == 1, "GetNumBetas");
    char name[64] = {0}, desc[64] = {0};
    uint32 flags = 0, build = 0, updated = 0;
    CHECK(apps->GetBetaInfo(0, &flags, &build, name, sizeof(name), desc, sizeof(desc), &updated), "GetBetaInfo");
    apps->SetGamePerformanceSetting(k_EGamePerformanceSetting_High);
    apps->SetGameRenderResolution(1280, 720);

    std::printf("marker B utils\n"); std::fflush(stdout);
    ISteamUtils *utils = SteamUtils();
    CHECK(utils->IsRunningOnSteamHardware() == k_ESteamHardwareTypeNone, "IsRunningOnSteamHardware");
    CHECK(utils->GetSteamHardwareDefaultConfig() == k_ESteamHardwareDefaultConfigNone, "GetSteamHardwareDefaultConfig");
    CHECK(utils->IsRunningUnderProton() == false, "IsRunningUnderProton");
    utils->DismissGamepadTextInput();

    std::printf("marker C timeline\n"); std::fflush(stdout);
    ISteamTimeline *timeline = SteamTimeline();
    CHECK(timeline != NULL, "SteamTimeline accessor");
    std::printf("t1 tooltip\n"); std::fflush(stdout);
    timeline->SetTimelineTooltip("test", 0.f);
    std::printf("t2 gamemode\n"); std::fflush(stdout);
    timeline->SetTimelineGameMode(k_ETimelineGameMode_Playing);
    std::printf("t3 addinst\n"); std::fflush(stdout);
    TimelineEventHandle_t ev = timeline->AddInstantaneousTimelineEvent("t", "d", "icon", 5);
    std::printf("t4 remove\n"); std::fflush(stdout);
    timeline->RemoveTimelineEvent(ev);
    std::printf("t5 startphase\n"); std::fflush(stdout);
    timeline->StartGamePhase();
    std::printf("t6 setphaseid\n"); std::fflush(stdout);
    timeline->SetGamePhaseID("phase1");
    std::printf("t7 endphase\n"); std::fflush(stdout);
    timeline->EndGamePhase();

    std::printf("marker D ugc\n"); std::fflush(stdout);
    ISteamUGC *ugc = SteamUGC();
    uint32 subs = ugc->GetNumSubscribedItems();
    (void)subs;
    PublishedFileId_t ids[8];
    ugc->GetSubscribedItems(ids, 8, false);
    ugc->GetNumDownloadedItems();
    ugc->GetDownloadedItems(ids, 8);
    EUGCContentDescriptorID descs[4];
    ugc->GetUserContentDescriptorPreferences(descs, 4);
    ugc->MarkDownloadedItemAsUnused(1);

    std::printf("marker E remoteplay\n"); std::fflush(stdout);
    ISteamRemotePlay *rp = SteamRemotePlay();
    rp->ShowRemotePlayTogetherUI();
    rp->BEnableRemotePlayTogetherDirectInput();
    rp->DisableRemotePlayTogetherDirectInput();
    RemotePlayInput_t input;
    rp->GetInput(&input, 1);
    RemotePlayCursorID_t cursor = rp->CreateMouseCursor(32, 32, 1, 1, NULL);
    rp->SetMouseCursor(1, cursor);

    std::printf("marker F matchmaking\n"); std::fflush(stdout);
    ISteamMatchmakingServers *ms = SteamMatchmakingServers();
    CHECK(ms != NULL, "MatchmakingServers");
    // ServerFriends with NULL response must not crash
    ms->ServerFriends(0x0100007f, 27015, NULL);

    std::printf("marker G netsockets\n"); std::fflush(stdout);
    ISteamNetworkingSockets *ns = SteamNetworkingSockets();
    CHECK(ns != NULL, "NetworkingSockets");
    HSteamNetConnection c1 = 0, c2 = 0;
    ns->CreateSocketPair(&c1, &c2, true, NULL, NULL);
    CHECK(c1 != 0 && c2 != 0, "CreateSocketPair");
    ISteamNetworkingFakeUDPPort *fake = ns->CreateFakeUDPPort(-1);
    CHECK(fake != NULL, "CreateFakeUDPPort");
    if (fake) {
        SteamNetworkingIPAddr addr;
        addr.Clear();
        addr.SetIPv4(0x0100007f, 1234);
        fake->SendMessageToFakeIP(addr, "hello", 5, k_nSteamNetworkingSend_Unreliable);
        SteamNetworkingMessage_t *msgs[4];
        fake->ReceiveMessages(msgs, 4);
        fake->DestroyFakeUDPPort();
    }
    ns->BeginAsyncRequestFakeIP(1);
    SteamNetworkingFakeIPResult_t info;
    ns->GetFakeIP(0, &info);
    CHECK(info.m_eResult == k_EResultOK, "GetFakeIP");

    std::printf("marker H user\n"); std::fflush(stdout);
    ISteamUser *user = SteamUser();
    CHECK(user->GetSteamID().IsValid(), "GetSteamID");
    int blob = 0;
    user->InitiateGameConnection_DEPRECATED(&blob, sizeof(blob), user->GetSteamID(), 0x0100007f, 27015, true);
    user->TerminateGameConnection_DEPRECATED(0x0100007f, 27015);
}


// game server side
static void test_gameserver()
{
    bool ok = SteamGameServer_Init(0, 27015, 27016, eServerModeNoAuthentication, "1.0.0.0");
    CHECK(ok, "SteamGameServer_Init");
    ISteamGameServer *gs = SteamGameServer();
    CHECK(gs != NULL, "SteamGameServer accessor");
    ISteamGameServerStats *gsstats = SteamGameServerStats();
    CHECK(gsstats != NULL, "SteamGameServerStats accessor");
    ISteamUtils *gsutils = SteamGameServerUtils();
    CHECK(gsutils != NULL, "SteamGameServerUtils 011");
    ISteamUGC *gsugc = SteamGameServerUGC();
    CHECK(gsugc != NULL, "SteamGameServerUGC 021");
    ISteamNetworkingSockets *gsns = SteamGameServerNetworkingSockets();
    CHECK(gsns != NULL, "SteamGameServerNetworkingSockets 013");
    if (gs) {
        gs->LogOnAnonymous(); // standard gameserver pattern
        CHECK(gs->BLoggedOn(), "GS BLoggedOn");
        CSteamID sid = gs->GetSteamID();
        (void)sid;
    }
}

// callback delivery
struct SteamServersConnected_test { enum { k_iCallback = k_iSteamUserCallbacks + 1 }; };
static bool got_callback = false;
struct CallbackSink
{
    STEAM_CALLBACK(CallbackSink, on_servers_connected, SteamServersConnected_test)
    {
        got_callback = true;
    }
};

static void test_callbacks()
{
    CallbackSink sink;
    // the emulator does not post SteamServersConnected by default; just verify
    // registration machinery does not crash.
    SteamAPI_RunCallbacks();
}

int main()
{
    SteamErrMsg err;
    if (SteamAPI_InitEx(&err) != k_ESteamAPIInitResult_OK) {
        std::printf("SteamAPI_InitEx failed\n");
        return 2;
    }
    pipe_ = SteamAPI_GetHSteamPipe();
    user_ = SteamAPI_GetHSteamUser();

    test_client_versions();
    test_intermediate_versions();
    test_new_methods();
    test_gameserver();
    test_callbacks();

    SteamAPI_Shutdown();
    std::printf("%d checks, %d failures\n", checks, failures);
    return failures ? 1 : 0;
}
