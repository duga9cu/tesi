/*
 *  video.h
 *  MicArrayAnalyzer
 *
 *  Created by Lorenzo Rotteglia 
 *  Copyright 2013. All rights reserved.
 *
 */
#ifndef __VIDEO_H__
#define __VIDEO_H__

#include <map>
class AudioPool;

class VideoFrame
	{
	private:
		double** frameMatrix; 
		int frameNum;
		double overallMax, overallMin;
		double maxInTheBand[12];		
		double minInTheBand[12];
		bool frameMatrixInit(int channels, double** fM);
		bool bframeMatrixAlloc;
	public:
		
		double** GetFrameMatrix() {return frameMatrix;}
		int GetFrameNum() {return frameNum;}
		double GetOverallMax() {return overallMax;}
		double GetOverallMin() {return overallMin;}
		double GetMaxInTheBand(int band) {return maxInTheBand[band];}
		double GetMinInTheBand(int band) {return minInTheBand[band];}
		
		void SetMaxInTheBand(double max , int band) {maxInTheBand[band]=max;}
		void SetMinInTheBand(double min , int band) {minInTheBand[band]=min;}
		
		// 'ctors
		VideoFrame(double **fM, int channels, int fn, double ovrllMax, double ovrllmin);
	};

class Video
	{
	private:
		std::map<int,VideoFrame*> resultCube;
		int numOfFrames;
		double overallMax, overallMin;
		double overallBandMax[12];
		double overallBandMin[12];
		void SetMinsAndMaxs();
		
		
	public:
		void AddFrame(VideoFrame* f) ;
		
		double** GetFrameMatrix(int frameNum) {return resultCube[frameNum]->GetFrameMatrix();}
		int GetNumOfFrames() {return numOfFrames;}
		double GetOverallMax() {return overallMax;}
		double GetOverallMin() {return overallMin;}
		double GetOverallBandMax(int band) {return overallBandMax[band];}
		double GetOverallBandMin(int band) {return overallBandMin[band];}
		
		void SetNumOfFrames(int n) {numOfFrames=n ;}
		
		// 'ctors
		Video(): numOfFrames(0), overallMax(0),overallMin(0) {}
//		~Video() {delete[] resultCube;}
	};
#endif __VIDEO_H__
