#include "StdAfx.h"
#include "GameTimer.h"


GameTimer::GameTimer(void)
{
}


GameTimer::~GameTimer(void)
{
}


BOOL GameTimer::init(VOID)
{
    LARGE_INTEGER frequency;
    BOOL success = QueryPerformanceFrequency(&frequency);
    m_dFrequency = (DOUBLE)frequency.QuadPart;
    return success;
}


LONG CONST& GameTimer::next(VOID)
{
    static LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    LONGLONG delta = m_lAccumulator + now.QuadPart - m_lLastStop;
    m_lDeltaMillis = (LONG)(1e3 * (DOUBLE)delta / m_dFrequency);
    m_lAccumulator += (LONG)(delta - (LONGLONG)((DOUBLE)m_lDeltaMillis * m_dFrequency * 1e-3));
    m_lLastStop = now.QuadPart;
    return this->getDeltaMillis();
}


INT GameTimer::tick(VOID) 
{
    INT id;
    do {
        id = rand();
    } while(m_StopWatches.find(id) != m_StopWatches.end());
    static LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    m_StopWatches[id] = now.QuadPart;
    return id;
}


LONG GameTimer::tock(INT CONST& p_iID, BOOL CONST& p_bReset) 
{
    if(m_StopWatches.find(p_iID) != m_StopWatches.end()) {
        static LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        LONG delta = (LONGLONG)(now.QuadPart - m_StopWatches[p_iID]);
        if(p_bReset) {
            m_StopWatches.erase(p_iID);
        }
        return (LONG)(1e3 * delta / m_dFrequency);
    } else {
        return 0;
    }
}



