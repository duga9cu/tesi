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


#define FRAMELENGTH_DFLT 1					// default choice
#define FRAMEOVERLAP 0.1					// percentage of frame overlapping
#define TRANSPARENCY 50						// alpha value for the colormap superposition
#define   MAP_WIDTH  960					//pixel of background image
#define   MAP_HEIGHT 480					//pixel of background image
#define WINDOWFUNC	3						//hanning window
	
const int possibleLenghts[]={512,1024,2048,4096,8192,16384};
const std::vector<int>FrameLengths(possibleLenghts, possibleLenghts + sizeof(possibleLenghts) / sizeof(int) ); // samples of audio to chunck for one video frame


class AudioPool;

class VideoFrame
	{
	private:
		double** frameMatrix; 
		int frameNum, m_matrixChannels;
		double overallMax, overallMin;
		double maxInTheBand[12];		
		double minInTheBand[12];
		bool frameMatrixInit(int channels, double** fM);
		bool bframeMatrixAlloc;
		double*** m_aadLevelsMap;
		bool m_bLevelsMapAlloc;
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
		void SetLevelsMap(double** levelsmap, int band) {m_aadLevelsMap[band]=levelsmap; m_bLevelsMapAlloc=true;}
		void SetBgndImage(wxBitmap wxb) {m_wxbBgndImage=wxb;}
//		void DeleteAllData() {delete frameMatrix;}
		
		// 'ctors
		VideoFrame(double **fM, int channels, int fn, double ovrllMax, double ovrllmin);
		~VideoFrame();
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
		bool isVideoResized;
		int m_width, m_height; 		//pixel ratio for each frame
		
	public:
		int m_iCurrentUnit;

		void AddFrame(VideoFrame* f) ;
		bool IsVideoComplete(bool oomerror) { isVideoComplete = (resultCube.size()==numOfFrames || oomerror) ? true: false; return isVideoComplete;}
		bool IsVideoResized() {return isVideoResized;}
//		void CreateColorMaps();
		//		void DeleteAllData();
		void DeleteFrame(int frame) {delete resultCube[frame]; resultCube.erase(frame);}
		void CutVideo(int lastframe); //called in case of lack of memory

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
		void SetVideoResized() {isVideoResized = true;} //it is supposed to resize only in case of Out-Of-Memory

		// 'ctors
		Video(int width, int height):	m_width(width), 
										m_height(height), 
										numOfFrames(0), 
										transparency(50), 
										overallMax(0),
										overallMin(0),
										isVideoComplete(false), 
										isVideoResized(false) 
		{
		}
		~Video() { /* has to be empty */}
	};
#endif __VIDEO_H__
