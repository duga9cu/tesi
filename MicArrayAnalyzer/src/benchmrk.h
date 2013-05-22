/*
 *  benchmrk.h
 *  MicArrayAnalyzer
 *
 *  Created by Simone Campanini on 2/29/12.
 *  Copyright 2012 Casa della Musica. All rights reserved.
 *
 */

#ifdef _MSC_VER
#include <time.h>
#include <windows.h>

#define DELTA_EPOCH_IN_MICROSECONDS 11644473600000000Ui64

struct timezone
{
    int tz_minuteswest; // minutes W of Greenwich
    int tz_dsttime;     // type of dst correction
};

// according to timeval::tv_usec data type
typedef long suseconds_t;

int gettimeofday(struct timeval* tv, struct timezone* tz);

#else
//unix systems
#include <sys/time.h>
#endif

class TimeBenchmark
{
private:
    struct timeval m_tvTime;
    double m_dbElapsedTime;
    
public:
    void Start();
    void Stop();
    
    double GetElapsedTime();
    
    TimeBenchmark();
};

