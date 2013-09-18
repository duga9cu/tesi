/*
 *  video.h
 *  MicArrayAnalyzer
 *
 *  Created by Lorenzo Rotteglia 
 *  Copyright 2013. All rights reserved.
 *
 */

#include "video.h"
#include "commdefs.h"


bool VideoFrame::frameMatrixInit(int channels, double** fM)
{
	m_matrixChannels=channels;
	
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
	m_aadLevelsMap= new double** [12]; //has one matrix for each audio band
}

VideoFrame::~VideoFrame() {
	for (int i=0; i<m_matrixChannels; ++i) {
		delete [] frameMatrix[i];
	}
	delete[] frameMatrix; 
	
	for (int i=0; i<10+2; ++i) {
		for (int j=0; j<MAP_WIDTH; ++j) {
			delete [] m_aadLevelsMap[i][j];
		}
		delete [] m_aadLevelsMap[i];
	}
	delete[] m_aadLevelsMap;
}

//void Video::CreateColorMaps()
//{   
//    
//	wxImage *pwximgColorMap = new wxImage(m_width, m_height); //New image, all pixels are inited to black.
//	
//	//Retrieving min and max levels for the current band, scaled to the correct unit.
//	double min = FromdB(m_dbMin, MeasureUnit(m_iCurrentUnit));  
//	double max = FromdB(m_dbMax, MeasureUnit(m_iCurrentUnit));  
//	
//#ifdef __AUDEBUG__
//	printf("Gui::InitColorMap(): min = %f ; max = %f ; scale_unit = %d \n", min, max, m_iCurrentUnit);
//#endif
//	
//	unsigned char rgb[3];
//    
//    for (int i = 0; i < m_width; i++)
//    {
//        for (int k = 0; k < m_height; k++)
//        {
//            DoubleToRGB(rgb, m_aadLevelsMap[i][k], min, max, style);
//            pwximgColorMap->SetRGB(i, k, rgb[0], rgb[1], rgb[2]);
//        }
//    }   
//}


bool Video::SetMinsAndMaxs()		
{
	if (!isVideoComplete) return isVideoComplete;
	
	//init
	overallMax=0; 
	overallMin=resultCube[1]->GetOverallMin(); 
	for (int band=0; band<12; band++) {
		overallBandMax[band]=0;
		overallBandMin[band]=resultCube[1]->GetMinInTheBand(band);
	}
	//calc
	for(int i=1;i<=numOfFrames;i++) {
		//overallBandMax
		for (int band=0; band<12; band++) {
			if(resultCube[i]->GetMaxInTheBand(band) > overallBandMax[band])
				overallBandMax[band] = resultCube[i]->GetMaxInTheBand(band);
		}
		
		//overallBandMin
		for (int band=0; band<12; band++) {
			if(resultCube[i]->GetMinInTheBand(band) < overallBandMin[band])
				overallBandMin[band] = resultCube[i]->GetMinInTheBand(band);
		}
		//overallmax
		double valmax = resultCube[i]->GetOverallMax() ; //can be optimized
		if(valmax > overallMax)	overallMax=valmax;
		
		//overallmin
		double valmin = resultCube[i]->GetOverallMin() ; //can be optimized
		if(valmin< overallMin)	overallMin=valmin;
			
	}
		
	return isVideoComplete;
}


void Video::AddFrame(VideoFrame* f) 	{
	if(f->GetFrameNum() <= numOfFrames)
		resultCube[f->GetFrameNum()] = f;
//	VideoFrame* ciccio=resultCube[f->GetFrameNum()];
//	if (ciccio) ;
}

//void Video::DeleteAllData() {
//	for (int i=1; i<=numOfFrames; i++) {
//		resultCube[i]->DeleteAllData();
//	}
//}

void Video::CutVideo(int lastframe) 
{
	lastframe=lastframe-10; //get some buffer
	SetNumOfFrames(lastframe);
	for (int i=lastframe+1; i<=resultCube.size(); i++) {
		DeleteFrame(i);
		
	}

}
