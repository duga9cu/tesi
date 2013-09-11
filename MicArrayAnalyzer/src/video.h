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

#define FRAMELENGTH_MIN 1					 //in ms -> 1s / 0.01s = 1000 fps which is the max frame rate value imposed
#define FRAMELENGTH_MAX 50					//in ms -> 1s / 0.05s = 20 fps which is the min frame rate value imposed


//defaults
#define FRAMELENGTH 50					// milliseconds of audio to chunck for one video frame 
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
		wxBitmap m_wxbBgndImage;

	public:
		
		double** GetMatrix() {return frameMatrix;}
		double** GetLevels(int band) {return m_aadLevelsMap[band];}
		int GetFrameNum() {return frameNum;}
		double GetOverallMax() {return overallMax;}
		double GetOverallMin() {return overallMin;}
		double GetMaxInTheBand(int band) {return maxInTheBand[band];}
		double GetMinInTheBand(int band) {return minInTheBand[band];}
		wxBitmap GetBgndImage() {return m_wxbBgndImage;}
		
		void SetMaxInTheBand(double max , int band) {maxInTheBand[band]=max;}
		void SetMinInTheBand(double min , int band) {minInTheBand[band]=min;}
		void SetLevelsMap(double** levelsmap, int band) {m_aadLevelsMap[band]=levelsmap;}
		void SetBgndImage(wxBitmap wxb) {m_wxbBgndImage=wxb;}
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
		double overallBandMax[12]; //max of the video for each band
		double overallBandMin[12]; //min of the video for each band
		bool isVideoComplete;
		int m_width, m_height; 		//pixel ratio for each frame
		
	public:
		int m_iCurrentUnit;

		void AddFrame(VideoFrame* f) ;
		bool IsVideoComplete() {isVideoComplete = (resultCube.size()==numOfFrames) ? true: false; return isVideoComplete;}
//		void CreateColorMaps();
		//		void DeleteAllData();
		void DeleteFrame(int frame) {resultCube.erase(frame);}

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
		wxBitmap GetBgndImage( int frame ) {return resultCube[frame]->GetBgndImage();}
		
		//setters
		void SetTransparency(int valTransp) {transparency = valTransp;}
		void SetNumOfFrames(int val) {numOfFrames = val;}
//		void SetVideoIsComplete(bool value) {isVideoComplete=value;}
		void SetFrameLevelsMap(int frame, double** levelsmap, int band) {resultCube[frame]->SetLevelsMap(levelsmap, band);}
		void SetBgndImage(wxBitmap wxb, int frame) {resultCube[frame]->SetBgndImage(wxb);}
		bool SetMinsAndMaxs();

		// 'ctors
		Video(int width, int height):m_width(width), m_height(height), numOfFrames(0), transparency(50), overallMax(0),overallMin(0),isVideoComplete(false) {}
		~Video() {
			for (int i=1; i<numOfFrames; i++) {
				delete resultCube[i];
			}
		}
	};
#endif __VIDEO_H__
