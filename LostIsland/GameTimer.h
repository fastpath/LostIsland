#pragma once
typedef std::hash_map<INT,LONGLONG> StopWatchMap;

class GameTimer
{
private:
    DOUBLE m_dFrequency;
    LONGLONG m_lLastStop;
    LONG m_lDeltaMillis;
    LONG m_lAccumulator;
    StopWatchMap m_StopWatches;
    
public:
    GameTimer(VOID);
    ~GameTimer(VOID);

    BOOL init(VOID);
    LONG next(VOID);
    INT tick(VOID);
    LONG tock(INT CONST& p_iID, BOOL CONST& p_bReset);
    
    LONG getDeltaMillis(VOID) CONST { return m_lDeltaMillis; }
};

