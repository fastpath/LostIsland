#include "StdAfx.h"
#include "GameTimer.h"


GameTimer::GameTimer(void)
{
}


GameTimer::~GameTimer(void)
{
}


BOOL GameTimer::init(VOID) {
    return QueryPerformanceFrequency(&m_Frequency);
}


VOID GameTimer::next(VOID) {
    static LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

}
