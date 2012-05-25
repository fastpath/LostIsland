#pragma once
class GameTimer
{
private:
    LARGE_INTEGER m_Frequency;
    LARGE_INTEGER m_Delta;
    LARGE_INTEGER m_LastStop;

public:
    GameTimer(void);
    ~GameTimer(void);

    BOOL init(VOID);
    VOID next(VOID);
};

