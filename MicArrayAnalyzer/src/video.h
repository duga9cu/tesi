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
		bool frameMatrixInit(int channels);
		bool bframeMatrixAlloc;
	public:
		
		double** GetFrameMatrix() {return frameMatrix;}
		int GetFrameNum() {return frameNum;}
		double GetOverallMax() {return overallMax;}
		double GetOverallMin() {return overallMin;}
		double GetMaxintheBand(int band) {return maxInTheBand[band];}
		double GetMinintheBand(int band) {return minInTheBand[band];}
		
		void SetFrameMatrix(double** p,int channels) {frameMatrix = p;}	
		void SetFrameNumber (int frame) {frameNum=frame;}
		void SetOverallMax(double ovrllM) {overallMax=ovrllM;}
		void SetOverallMin(double ovrllm) {overallMin=ovrllm;}
		
		// 'ctors
		VideoFrame(double **fM, int channels, int fn, double ovrllMax, double ovrllmin);
	};

class Video
	{
	private:
		std::map<int,VideoFrame*> resultCube;
		int numOfFrames;
		double overallMax, overallMin;
		void SetOverallMax() ;
		void SetOverallMin() ;
		
		
	public:
		void AddFrame(VideoFrame* f) ;
		
		double** GetFrameMatrix(int frameNum) {return resultCube[frameNum]->GetFrameMatrix();}
		int GetNumOfFrames() {return numOfFrames;}
		
		void SetNumOfFrames(int n) {numOfFrames=n ;}
		
		// 'ctors
		Video(): numOfFrames(0), overallMax(0),overallMin(0) {}
//		~Video() {delete[] resultCube;}
	};
#endif __VIDEO_H__
