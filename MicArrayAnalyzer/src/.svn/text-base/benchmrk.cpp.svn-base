/*
 *  benchmrk.cpp
 *  MicArrayAnalyzer
 *
 *  Created by Simone Campanini on 2/29/12.
 *  Copyright 2012 Casa della Musica. All rights reserved.
 *
 */

#include "benchmrk.h"

#ifdef _MSC_VER
int gettimeofday(struct timeval* tv, struct timezone* tz)
{
    FILETIME ft;
    unsigned __int64 tmpres = 0;
    static int tzflag;

    if(tv != NULL)
    {
        GetSystemTimeAsFileTime(&ft);

        tmpres  |= ft.dwHighDateTime;
        tmpres <<= 32;
        tmpres  |= ft.dwHighDateTime;

        // converting file time to unix epoch
        tmpres -= DELTA_EPOCH_IN_MICROSECONDS;
        tmpres /= 10; // convert into us
        tv->tv_sec  = (long)(tmpres / 1000000UL);
        tv->tv_usec = (long)(tmpres % 1000000UL);
    }

    if(tz != NULL)
    {
        if(!tzflag)
        {
            _tzset();
            tzflag++;
        }
        tz->tz_minuteswest = _timezone / 60;
        tz->tz_dsttime = _daylight;
    }

    return 0;
}
#endif

void TimeBenchmark::Start()
{
    m_dbElapsedTime = 0.0;
    gettimeofday(&m_tvTime, 0);
}

void TimeBenchmark::Stop()
{
    struct timeval m_tvStopTime;
    gettimeofday(&m_tvStopTime, 0);
    
    time_t diffSec = m_tvStopTime.tv_sec - m_tvTime.tv_sec;
    suseconds_t diffUsecs = m_tvStopTime.tv_usec - m_tvTime.tv_usec; 
    
    m_dbElapsedTime = double(diffSec) * 1e+3 + double(diffUsecs) * 1e-3; //ms
}

double TimeBenchmark::GetElapsedTime()
{
    return m_dbElapsedTime;
}

TimeBenchmark::TimeBenchmark()
: m_tvTime(),
  m_dbElapsedTime(0.0)
{}