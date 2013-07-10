/*
 *  video.h
 *  MicArrayAnalyzer
 *
 *  Created by Lorenzo Rotteglia 
 *  Copyright 2013. All rights reserved.
 *
 */

#include "video.h"

bool VideoFrame::frameMatrixInit(int channels)
{
	
	if (bframeMatrixAlloc) delete [] frameMatrix;
	frameMatrix = new double* [channels];
	
	for (int i = 0; i < channels; i++)
	{
		frameMatrix[i] = new double [2+10];                       //2 = Lin + A-Weighted, 10 = 10 bands octave filters, for each audio track!
		for (int j = 0; j < 12; j++) { frameMatrix[i][j] = 0; }   //Clearing.
	}
	
	bframeMatrixAlloc = true;
	return true;
}

VideoFrame::VideoFrame(double **fM, int channels, int fn, double ovrllMax, double ovrllmin) :
frameNum(fn),
overallMax(ovrllMax),
overallMin(ovrllmin),
bframeMatrixAlloc(false)
{
	frameMatrixInit(channels);
}

		 
void Video::SetOverallMax()		{
	double max=0; 
	for(int i=0;i<numOfFrames;i++) 
		if(resultCube[i]->GetOverallMax() > max)
			max=resultCube[i]->GetOverallMax();
	overallMax = max;
}

void Video::SetOverallMin() {
	double min=resultCube[0]->GetOverallMin(); 
	for(int i=1;i<numOfFrames;i++) 
		if(resultCube[i]->GetOverallMin()<min) 
			min=resultCube[i]->GetOverallMin();
			overallMin = min;
}

void Video::AddFrame(VideoFrame* f) 	{
	assert(f->GetFrameNum() <= numOfFrames);
	//			assert(frame.GetFrameNum()==resultCube.size()+1);
	resultCube[f->GetFrameNum()]=f;
	if (f->GetFrameNum() == numOfFrames-1) {
	//TODO calculate overall max min
	} 
}
