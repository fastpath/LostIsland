#include "StdAfx.h"
#include "GameTimer.h"


GameTimer::GameTimer(VOID):
m_paused(FALSE), m_sysAccumulator(0), m_gameDeltaMillis(0)
{
}


GameTimer::~GameTimer(VOID)
{
}


BOOL GameTimer::Init(VOID)
{
    LARGE_INTEGER frequency, now;
    BOOL success = QueryPerformanceFrequency(&frequency);
    m_sysFrequency = (DOUBLE)frequency.QuadPart;
    QueryPerformanceCounter(&now);
    m_lastStop = now.QuadPart;
    this->SetFactor(1.0f);
    return success;
}


VOID GameTimer::Next(VOID)
{
    static LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    LONGLONG deltaTicks = now.QuadPart - m_lastStop;

    if(!m_paused)
    {
        LONGLONG sysDeltaTicks = deltaTicks + m_sysAccumulator;
        m_sysDeltaMillis = (LONG)((DOUBLE)sysDeltaTicks / (1e-3 * m_sysFrequency));
        m_sysAccumulator = (LONG)(sysDeltaTicks - (LONGLONG)((DOUBLE)m_sysDeltaMillis * (1e-3 * m_sysFrequency)));
        StopWatchMap::iterator rtend = m_realtime.end();
        for(StopWatchMap::iterator iter = m_realtime.begin(); iter != rtend; ++iter) 
        {
            iter->second += m_sysDeltaMillis;
        }

        LONGLONG gameDeltaTicks = deltaTicks + m_gameAccumulator;
        m_gameDeltaMillis = (LONG)((DOUBLE)gameDeltaTicks / (1e-3 * m_gameFrequency));
        m_gameAccumulator = (LONG)(gameDeltaTicks - (LONGLONG)((DOUBLE)m_gameDeltaMillis * (1e-3 * m_gameFrequency)));
        StopWatchMap::iterator gtend = m_gametime.end();
        for(StopWatchMap::iterator iter = m_gametime.begin(); iter != gtend; ++iter) 
        {
            iter->second += m_gameDeltaMillis;
        }
    }

    m_lastStop = now.QuadPart;
}


INT GameTimer::Tick(INT id, TickOption p_option) 
{
    switch(m_types[id] = p_option)
    {
    case REALTIME: m_realtime[id] = 0; break;
    case GAMETIME: m_gametime[id] = 0; break;
    case IMMEDIATE:
        static LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        m_immediateStops[id] = now.QuadPart;
        break;
    }
    return id;
}


LONG GameTimer::Tock(INT p_id, TockOption p_option) 
{
    LONG time = 0;
    if(m_types.find(p_id) != m_types.end())
    {
        TickOption tick = m_types[p_id];
        StopWatchMap* pTarget = NULL;
        switch(tick)
        {
        case GAMETIME: pTarget = &m_gametime; break;
        case REALTIME: pTarget = &m_realtime; break;
        }
        if(pTarget == NULL)
        {
            static LARGE_INTEGER now;
            QueryPerformanceCounter(&now);
            time = (LONG)((DOUBLE)(now.QuadPart - m_immediateStops[p_id]) / (1e-3 * m_sysFrequency));
        }
        else
        {
            time = (*pTarget)[p_id];
        }

        switch(p_option)
        {
        case ERASE:
            if(pTarget == NULL)
            {
                m_immediateStops.erase(p_id);
            }
            else
            {
                pTarget->erase(p_id);
            }
            break;
        case RESET: this->Tick(p_id, tick); break;
        case KEEPRUNNING: break;
        }
    }
    return time;
}


INT GameTimer::GetTickTockID(VOID) CONST
{
    INT id = rand();
    while(m_types.find(id) != m_types.end())
    {
        id = rand();
    }
    return id;
}
