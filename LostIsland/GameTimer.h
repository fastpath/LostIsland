#pragma once

enum TockOption {
    ERASE, RESET, KEEPRUNNING,
};

enum TickOption {
    REALTIME, GAMETIME, IMMEDIATE
};

typedef std::hash_map<INT,LONG> StopWatchMap;
typedef std::hash_map<INT,LONGLONG> ImmediateMap;
typedef std::hash_map<INT,TickOption> StopWatchTypeMap;

class GameTimer
{
private:
    DOUBLE           m_sysFrequency;
    LONG             m_sysAccumulator;
    LONG             m_sysDeltaMillis;
    StopWatchMap     m_realtime;
    DOUBLE           m_gameFrequency;
    LONG             m_gameAccumulator;
    LONG             m_gameDeltaMillis;
    StopWatchMap     m_gametime;
    LONGLONG         m_lastStop;
    BOOL             m_paused;
    ImmediateMap     m_immediateStops;
    StopWatchTypeMap m_types;

    INT GetTickTockID(VOID) CONST;
    INT Tick(INT p_id, TickOption p_option);
    
public:
    GameTimer(VOID);
    ~GameTimer(VOID);

    BOOL Init(VOID);
    VOID Next(VOID);
    LONG Tock(INT p_id, TockOption p_option);

    INT Tick(TickOption p_option) { return this->Tick(this->GetTickTockID(), p_option); }
    VOID Pause(VOID) { m_paused = TRUE; }
    VOID Resume(VOID) { m_paused = FALSE; }
    VOID SetFactor(DOUBLE p_factor) { m_gameFrequency = m_sysFrequency / p_factor; }
    LONG GetGameDeltaMillis(VOID) CONST { return m_gameDeltaMillis; }
    LONG GetSysDeltaMillis(VOID) CONST { return m_sysDeltaMillis; }
};

