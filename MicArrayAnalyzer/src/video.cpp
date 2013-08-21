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


bool Video::SetMinsAndMaxs()		
{
	if (!videoIsComplete) return videoIsComplete;
	
	//init
#ifdef __AUDEBUG__
	VideoFrame *ciccio=resultCube[1];
#endif
	double max=0; 
	double min=resultCube[1]->GetOverallMin(); 
	for (int band=0; band<12; band++) {
		overallBandMax[band]=0;
		overallBandMin[band]=resultCube[1]->GetMinInTheBand(band);
	}
	//calc
	for(int i=1;i<=numOfFrames;i++) {
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
		//overallmax
		double valmax = resultCube[i]->GetOverallMax() ; //can be optimized
		if(valmax > max)	max=valmax;
		
		//overallmin
		double valmin = resultCube[i]->GetOverallMin() ; //can be optimized
		if(valmin< min)	min=valmin;
			
	}
	overallMax = max;
	overallMin = min;
		
	return videoIsComplete;
}


void Video::AddFrame(VideoFrame* f) 	{
	assert(f->GetFrameNum() <= numOfFrames);
		resultCube[f->GetFrameNum()] = f;
//	VideoFrame* ciccio=resultCube[f->GetFrameNum()];
//	if (ciccio) ;
}

//void Video::DeleteAllData() {
//	for (int i=1; i<=numOfFrames; i++) {
//		resultCube[i]->DeleteAllData();
//	}
//}
