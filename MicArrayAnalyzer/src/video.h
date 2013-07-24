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

#include <wx/hashmap.h>


#define FRAMELENGTH 0.05					// seconds of audio to chunck for one video frame //IMPORTANT! non deve scendere sotto lunghezzaFiltro/SampleRate per fare la convoluzione! (0,046 nel test teatro)
#define FRAMEOVERLAP 0.1					// percentage of frame overlapping

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
		WX_DECLARE_HASH_MAP( int, VideoFrame*, wxIntegerHash, wxIntegerEqual, WxHash_Map );
//		std::map<int,VideoFrame*> resultCube;
		WxHash_Map resultCube;
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
