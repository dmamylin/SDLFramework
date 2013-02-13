#ifndef CTimer_H
#define CTimer_H

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class CTimer
{
private:
    LARGE_INTEGER frequency;
    LARGE_INTEGER timeStart;
    LARGE_INTEGER timeEnd;

    bool run;

public:
    CTimer(bool start = false);
    ~CTimer() { }

    void Start(void);
    void Stop(void);

    double GetTime(void); //In milliseconds
    inline bool Run(void) { return run; }
};

CTimer::CTimer(bool start)
{
    run = start;

    QueryPerformanceFrequency(&frequency);
    timeStart.QuadPart = 0;
    timeEnd.QuadPart = 0;

    if ( run )
        QueryPerformanceCounter(&timeStart);
}

inline void CTimer::Start(void)
{
    if ( !run )
    {
        run = true;
        QueryPerformanceCounter(&timeStart);
    }
}

inline void CTimer::Stop(void)
{
    if ( run )
    {
        run = false;
        QueryPerformanceCounter(&timeEnd);
    }
}

inline double CTimer::GetTime(void)
{
    if ( run )
    {
        QueryPerformanceCounter(&timeEnd);
        return double( timeEnd.QuadPart - timeStart.QuadPart ) / frequency.QuadPart * 1000.0;
    }

    return double( timeEnd.QuadPart - timeStart.QuadPart ) / frequency.QuadPart * 1000.0;
}

#endif