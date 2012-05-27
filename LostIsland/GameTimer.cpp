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
    LARGE_INTEGER frequency;
    BOOL success = QueryPerformanceFrequency(&frequency);
    m_sysFrequency = (DOUBLE)frequency.QuadPart;
    this->SetFactor(1.0f);
    //std::cout << frequency.QuadPart << std::endl;
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


INT GameTimer::Tick(TickOption p_option) 
{
    StopWatchMap* pTarget = NULL;
    switch(p_option) {
    case REALTIME: pTarget = &m_realtime; break;
    case GAMETIME: pTarget = &m_gametime; break;
    }
    INT id;
    do {
        id = rand();
    } while(this->GetTarget(id) != NULL);
    (*pTarget)[id] = 0;
    return id;
}


LONG GameTimer::Tock(INT p_id, TockOption p_option) 
{
    StopWatchMap* pTarget = this->GetTarget(p_id);
    if(pTarget != NULL) {
        LONG val = (*pTarget)[p_id];
        switch(p_option)
        {
        case ERASE: pTarget->erase(p_id); break;
        case RESET: (*pTarget)[p_id] = 0; break;
        case KEEPRUNNING: break;
        }
        return val;
    } else {
        return 0;
    }
}


StopWatchMap* GameTimer::GetTarget(INT p_id)
{
    if(m_realtime.find(p_id) != m_realtime.end())
    {
        return &m_realtime;
    }
    else if(m_gametime.find(p_id) != m_gametime.end())
    {
        return &m_gametime;
    }
    else 
    {
        return NULL;
    }
}
