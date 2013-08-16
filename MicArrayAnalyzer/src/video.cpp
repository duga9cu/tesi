/*
 *  video.h
 *  MicArrayAnalyzer
 *
 *  Created by Lorenzo Rotteglia 
 *  Copyright 2013. All rights reserved.
 *
 */

#include "video.h"

bool VideoFrame::frameMatrixInit(int channels, double** fM)
{
	
	if (bframeMatrixAlloc) delete [] frameMatrix;
	frameMatrix = new double* [channels];
	
	for (int i = 0; i < channels; i++)
	{
		frameMatrix[i] = new double [2+10];                       //2 = Lin + A-Weighted, 10 = 10 bands octave filters, for each audio track!
		for (int j = 0; j < 12; j++) { frameMatrix[i][j] = fM[i][j]; }   //copying frame matrix.
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
	frameMatrixInit(channels,fM);
	
}


void Video::SetMinsAndMaxs()		
{
	//init
	double max=0; 
	double min=resultCube[1]->GetOverallMin(); 
	for (int band=0; band<12; band++) {
		overallBandMax[band]=0;
		overallBandMin[band]=resultCube[1]->GetMinInTheBand(band);
	}
	//calc
	for(int i=1;i<=numOfFrames;i++) {
		//overallmax
		double valmax = resultCube[i]->GetOverallMax() ;
		if(valmax > max)	max=valmax;
		
		//overallmin
		double valmin = resultCube[i]->GetOverallMin() ;
		if(valmin< min)	min=valmin;
		
		//maxintheband
		for (int band=0; band<12; band++) {
			if(resultCube[i]->GetMaxInTheBand(band) > overallBandMax[band])
				overallBandMax[band] = resultCube[i]->GetMaxInTheBand(band);
		}
		
		//minintheband
		for (int band=0; band<12; band++) {
			if(resultCube[i]->GetMinInTheBand(band) < overallBandMin[band])
				overallBandMin[band] = resultCube[i]->GetMinInTheBand(band);
		}
	}
	overallMax = max;
	overallMin = min;
}


void Video::AddFrame(VideoFrame* f) 	{
	assert(f->GetFrameNum() <= numOfFrames);
	//			assert(frame.GetFrameNum()==resultCube.size()+1);
	resultCube[f->GetFrameNum()]=f;
//	resultCube.insert(f);
//	if (f->GetFrameNum() == numOfFrames) {//last frame added
	if (resultCube.size() == numOfFrames) { //last frame added
		// calculate overall max min
		this->SetMinsAndMaxs();
		
	} 
}
