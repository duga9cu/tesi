/*
 *  FFMPEGencodeVideoToFramesPPM.h
 *  MicArrayAnalyzer
 *
 *  Created by Lorenzo Rotteglia on Thu 248 September.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#define UINT64_C(v)  (v ## ULL) //is it allright to evade include <stdint.h> like this??

//#include <wx/stdpaths.h>


#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include "swscale.h"

#include <stdio.h>
typedef uint32_t millisec;


void SaveFrame(AVFrame *pFrame, int width, int height, int iFrame) ;

int EncodeFrames( char *argv, millisec start_ms, millisec end_ms) ;
