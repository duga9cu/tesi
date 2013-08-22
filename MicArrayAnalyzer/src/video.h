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
#include "meshandinterpol.h"
#include "commdefs.h"

#define FRAMELENGTH 0.05					// seconds of audio to chunck for one video frame //IMPORTANT! non deve scendere sotto lunghezzaFiltro/SampleRate per fare la convoluzione! (0,046 nel test teatro)
#define FRAMEOVERLAP 0.1					// percentage of frame overlapping
#define TRANSPARENCY 50					// alpha value for the colormap superposition



//double FromdB(const double value_dB, const MeasureUnit mu);
//bool DoubleToRGB(unsigned char* rgb, const double value, const double min, const double max, const int style);

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
		double*** m_aadLevelsMap;

	public:
		
		double** GetMatrix() {return frameMatrix;}
		double** GetLevels(int band) {return m_aadLevelsMap[band];}
		int GetFrameNum() {return frameNum;}
		double GetOverallMax() {return overallMax;}
		double GetOverallMin() {return overallMin;}
		double GetMaxInTheBand(int band) {return maxInTheBand[band];}
		double GetMinInTheBand(int band) {return minInTheBand[band];}
		
		void SetMaxInTheBand(double max , int band) {maxInTheBand[band]=max;}
		void SetMinInTheBand(double min , int band) {minInTheBand[band]=min;}
		void SetLevelsMap(double** levelsmap, int band) {m_aadLevelsMap[band]=levelsmap;}
//		void DeleteAllData() {delete frameMatrix;}
		
		// 'ctors
		VideoFrame(double **fM, int channels, int fn, double ovrllMax, double ovrllmin);
		~VideoFrame() {delete frameMatrix;}
	};

class Video
	{
	private:
		WX_DECLARE_HASH_MAP( int, VideoFrame*, wxIntegerHash, wxIntegerEqual, WxHash_Map );
		WxHash_Map resultCube;
		int numOfFrames;
		int transparency;
		double overallMax, overallMin;
		double overallBandMax[12];
		double overallBandMin[12];
		bool videoIsComplete;
		int m_width, m_height; 		//pixel ratio for each frame
		
	public:
		int m_iCurrentUnit;

		void AddFrame(VideoFrame* f) ;
		bool IsVideoComplete() {videoIsComplete = (resultCube.size()==numOfFrames) ? true: false; return videoIsComplete;}
//		void CreateColorMaps();

		//getters
		double** GetFrameMatrix(int frameNum) {return resultCube[frameNum]->GetMatrix();}
		double** GetFrameLevels(int frameNum,int band) {return resultCube[frameNum]->GetLevels(band);}
		int GetNumOfFrames() {return numOfFrames;}
		int GetSize() {return resultCube.size();}
		double GetOverallMax() {return overallMax;}
		double GetOverallMin() {return overallMin;}
		double GetOverallBandMax(int band) {return overallBandMax[band];}
		double GetOverallBandMin(int band) {return overallBandMin[band];}
		int GetTransparency() {return transparency;}
		VideoFrame* GetVideoFrame(unsigned int frameNum) {return resultCube[frameNum];}
		
		//setters
		void SetTransparency(int valTransp) {transparency = valTransp;}
		void SetNumOfFrames(int n) {numOfFrames=n ;}
//		void SetVideoIsComplete(bool value) {videoIsComplete=value;}
		void SetFrameLevelsMap(int frame, double** levelsmap, int band) {resultCube[frame]->SetLevelsMap(levelsmap, band);}
		bool SetMinsAndMaxs();
//		void DeleteAllData();

		// 'ctors
		Video(int width, int height):m_width(width), m_height(height), numOfFrames(0), transparency(50), overallMax(0),overallMin(0),videoIsComplete(false) {}
		~Video() { /* has to be empty */}
	};
#endif __VIDEO_H__
