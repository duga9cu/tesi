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

#include <wx/wx.h>

#include "micarrayanalyzer.h"

class VideoFrame
	{
	private:
		double** frameMap; 
		int frameNum;
		
			
	public:
		void SetFrameMap(double** p) {frameMap = p;}
		void setFrameNum(int n) {frameNum = n;}
		
		double** GetFrameMap() {return frameMap;}
		int GetFrameNum() {return frameNum;}
		
		// 'ctors
		VideoFrame();

		~VideoFrame();
	};

class Video
	{
	private:
		vector<VideoFrame> resultCube;
		int numOfFrames;
		
		// 'ctors
		Video();
		
		~Video();
		
};