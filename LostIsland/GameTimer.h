#pragma once
typedef std::hash_map<INT,LONG> StopWatchMap;

enum TockOption {
    ERASE, RESET, KEEPRUNNING,
};

enum TickOption {
    REALTIME, GAMETIME,
};

class GameTimer
{
private:
    DOUBLE       m_sysFrequency;
    LONG         m_sysAccumulator;
    LONG         m_sysDeltaMillis;
    StopWatchMap m_realtime;
    DOUBLE       m_gameFrequency;
    LONG         m_gameAccumulator;
    LONG         m_gameDeltaMillis;
    StopWatchMap m_gametime;
    LONGLONG     m_lastStop;
    BOOL         m_paused;

    StopWatchMap* GetTarget(INT p_id);
    
public:
    GameTimer(VOID);
    ~GameTimer(VOID);

    BOOL Init(VOID);
    VOID Next(VOID);
    INT Tick(TickOption p_option);
    LONG Tock(INT p_id, TockOption p_option);

    VOID Pause(VOID) { m_paused = TRUE; }
    VOID Resume(VOID) { m_paused = FALSE; }
    VOID SetFactor(DOUBLE p_factor) { m_gameFrequency = m_sysFrequency / p_factor; }
    LONG GetGameDeltaMillis(VOID) CONST { return m_gameDeltaMillis; }
    LONG GetSysDeltaMillis(VOID) CONST { return m_sysDeltaMillis; }
};

