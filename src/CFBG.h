/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan
 * Copyright (С) since 2019+ AzerothCore <www.azerothcore.org>
 * Licence MIT https://opensource.org/MIT
 */

#ifndef _CFBG_H_
#define _CFBG_H_

#include "Common.h"
#include "Player.h"
#include "Battleground.h"
#include "BattlegroundQueue.h"
#include <unordered_map>

enum FakeMorphs
{
    // FAKE_M_GOBLIN = 20582,
    // FAKE_F_GOBLIN = 20583,

    // FAKE_M_UNDEAD missing
    // FAKE_F_UNDEAD missing
    
    FAKE_M_FEL_ORC        = 21267,
    FAKE_F_ORC            = 20316,

    FAKE_M_DWARF          = 20317,
    // FAKE_F_DWARF missing

    FAKE_M_NIGHT_ELF      = 20318,
    // FAKE_F_NIGHT_ELF missing

    FAKE_F_DRAENEI        = 20323,
    FAKE_M_BROKEN_DRAENEI = 21105,

    FAKE_M_TROLL          = 20321,
    // FAKE_F_TROLL missing

    FAKE_M_HUMAN          = 19723,
    FAKE_F_HUMAN          = 19724,
    FAKE_M_BLOOD_ELF      = 20578,
    FAKE_F_BLOOD_ELF      = 20579,
    FAKE_F_GNOME          = 20320,
    FAKE_M_GNOME          = 20580,
    FAKE_F_TAUREN         = 20584,
    FAKE_M_TAUREN         = 20585

};

struct FakePlayer
{
    // Fake
    uint8   FakeRace;
    uint32  FakeMorph;
    TeamId  FakeTeamID;

    // Real
    uint8   RealRace;
    uint32  RealMorph;
    TeamId  RealTeamID;
};

enum CFBGBattlegroundQueueGroupTypes
{
    BG_QUEUE_CFBG = 4
};

class CFBG
{
public:
    static CFBG* instance();

    void LoadConfig();

    bool IsEnableSystem();
    bool IsEnableAvgIlvl();
    bool IsEnableBalancedTeams();
    bool IsEnableEvenTeams();
    uint32 EvenTeamsMaxPlayersThreshold();
    uint32 GetMaxPlayersCountInGroup();
    uint32 averagePlayersLevelQueue;
    uint32 averagePlayersItemLevelQueue;
    uint32 joiningPlayers;

    uint32 GetBGTeamAverageItemLevel(Battleground* bg, TeamId team);
    uint32 GetBGTeamSumPlayerLevel(Battleground* bg, TeamId team);
    uint32 GetAllPlayersCountInBG(Battleground* bg);

    TeamId GetLowerTeamIdInBG(Battleground* bg, Player* player);
    TeamId GetLowerAvgIlvlTeamInBg(Battleground* bg);
    TeamId SelectBgTeam(Battleground* bg, Player* player);

    bool IsAvgIlvlTeamsInBgEqual(Battleground* bg);
    bool SendRealNameQuery(Player* player);
    bool IsPlayerFake(Player* player);
    bool ShouldForgetInListPlayers(Player* player);
    bool IsPlayingNative(Player* player);

    void ValidatePlayerForBG(Battleground* bg, Player* player, TeamId teamId);
    void SetFakeRaceAndMorph(Player* player);
    void SetFactionForRace(Player* player, uint8 Race);
    void ClearFakePlayer(Player* player);
    void DoForgetPlayersInList(Player* player);
    void FitPlayerInTeam(Player* player, bool action, Battleground* bg);
    void DoForgetPlayersInBG(Player* player, Battleground* bg);
    void SetForgetBGPlayers(Player* player, bool value);
    bool ShouldForgetBGPlayers(Player* player);
    void SetForgetInListPlayers(Player* player, bool value);
    void UpdateForget(Player* player);
    bool SendMessageQueue(BattlegroundQueue* bgqueue, Battleground* bg, PvPDifficultyEntry const* bracketEntry, Player* leader);

    bool FillPlayersToCFBGWithSpecific(BattlegroundQueue* bgqueue, Battleground* bg, const int32 aliFree, const int32 hordeFree, BattlegroundBracketId thisBracketId, BattlegroundQueue* specificQueue, BattlegroundBracketId specificBracketId);
    bool FillPlayersToCFBG(BattlegroundQueue* bgqueue, Battleground* bg, const int32 aliFree, const int32 hordeFree, BattlegroundBracketId bracket_id);

private:
    typedef std::unordered_map<Player*, FakePlayer> FakePlayersContainer;
    typedef std::unordered_map<Player*, uint64> FakeNamePlayersContainer;
    typedef std::unordered_map<Player*, bool> ForgetBGPlayersContainer;
    typedef std::unordered_map<Player*, bool> ForgetInListPlayersContainer;

    FakePlayersContainer _fakePlayerStore;
    FakeNamePlayersContainer _fakeNamePlayersStore;
    ForgetBGPlayersContainer _forgetBGPlayersStore;
    ForgetInListPlayersContainer _forgetInListPlayersStore;

    // For config
    bool _IsEnableSystem;
    bool _IsEnableAvgIlvl;
    bool _IsEnableBalancedTeams;
    bool _IsEnableEvenTeams;
    uint32 _EvenTeamsMaxPlayersThreshold;
    uint32 _MaxPlayersCountInGroup;

    void randomRaceMorph(uint8* race, uint32* morph, TeamId team, uint8 _class, uint8 gender);

    template <std::size_t N>
    uint8 getRandomRace(const uint8 (&races)[N]);
    uint32 getMorphFromRace(uint8 race, uint8 gender);
};

#define sCFBG CFBG::instance()

#endif // _KARGATUM_CFBG_H_
