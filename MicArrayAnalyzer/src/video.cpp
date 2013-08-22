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

double FromdB(const double value_dB, const MeasureUnit mu)
{
    switch (mu)
    {
        case MU_dB:   return value_dB;
        case MU_Pa:   return (undB20(value_dB));
        case MU_Sqrt: return sqrt(undB20(value_dB));
        case MU_Cbrt: return pow(10.0, ((1.0 / 3.0)*log10(undB20(value_dB)))); 
    }
    return value_dB;
}

bool DoubleToRGB(unsigned char* rgb, 
				 const double   value, 
				 const double   min, 
				 const double   max, 
				 const int      style)
{
    unsigned char c1=144;
    double max4=(max-min)/4;
    float max3=(max-min)/3;   
    double dbTmpValue = value;
    
    switch (style)
    {
        case CMS_JET: //Jet ColorMap
            dbTmpValue -= min;
            if (dbTmpValue == HUGE_VAL)
            {    
                rgb[0] = rgb[1] = rgb[2] = 255; 
            }
            else if (dbTmpValue < 0)
            {    
                rgb[0] = rgb[1] = rgb[2] = 0; 
            }
            else if (dbTmpValue < max4)
            {   
                rgb[0] = 0; 
                rgb[1] = 0; 
                rgb[2] = c1 + (unsigned char)((255-c1)*dbTmpValue/max4); 
            }
            else if (dbTmpValue < 2*max4)
            {   
                rgb[0] = 0; 
                rgb[1] = (unsigned char)(255*(dbTmpValue-max4)/max4); 
                rgb[2] = 255; 
            }
            else if (dbTmpValue < 3*max4)
            {   
                rgb[0] = (unsigned char)(255*(dbTmpValue-2*max4)/max4); 
                rgb[1] = 255; 
                rgb[2] = 255 - rgb[0]; 
            }
            else if (dbTmpValue < max)
            {   
                rgb[0] = 255; 
                rgb[1] = (unsigned char)(255-255*(dbTmpValue-3*max4)/max4); 
                rgb[2] = 0; 
            }
            else
            {   
                rgb[0] = 255; 
                rgb[1] = rgb[2] = 0; 
            }
            break;
            
        case CMS_HOT: //Hot ColorMap
            dbTmpValue -= min;
            if (dbTmpValue == HUGE_VAL)
            { 
                rgb[0] = rgb[1] = rgb[2] = 255; 
            }
            else if (dbTmpValue < 0)
            { 
                rgb[0] = rgb[1] = rgb[2] = 0; 
            }
            else if (dbTmpValue < max3)
            { 
                rgb[0] = (unsigned char)(255*dbTmpValue/max3); 
                rgb[1] = 0; 
                rgb[2] = 0; 
            }
            else if (dbTmpValue < 2*max3)
            { 
                rgb[0] = 255; 
                rgb[1] = (unsigned char)(255*(dbTmpValue-max3)/max3); 
                rgb[2] = 0; 
            }
            else if (dbTmpValue < max)
            { 
                rgb[0] = 255; 
                rgb[1] = 255; 
                rgb[2] = (unsigned char)(255*(dbTmpValue-2*max3)/max3); 
            }
            else
            { 
                rgb[0] = rgb[1] = rgb[2] = 255; 
            }
            break;
            
        case CMS_COLD: //Cold ColorMap
            dbTmpValue -= min;
            if (dbTmpValue == HUGE_VAL)
            { 
                rgb[0] = rgb[1] = rgb[2] = 255; 
            }
            else if (dbTmpValue < 0)
            { 
                rgb[0] = rgb[1] = rgb[2] = 0; 
            }
            else if (dbTmpValue < max3)
            { 
                rgb[0] = 0; 
                rgb[1] = 0; 
                rgb[2] = (unsigned char)(255*dbTmpValue/max3); 
            }
            else if (dbTmpValue < 2*max3)
            { 
                rgb[0] = 0; 
                rgb[1] = (unsigned char)(255*(dbTmpValue-max3)/max3); 
                rgb[2] = 255; 
            }
            else if (dbTmpValue < max)
            { 
                rgb[0] = (unsigned char)(255*(dbTmpValue-2*max3)/max3); 
                rgb[1] = 255; 
                rgb[2] = 255; 
            }
            else
            { 
                rgb[0] = rgb[1] = rgb[2] = 255; 
            }
            break;
            
        default:
            return false; //Not supported ColorMap requested
    }
    
    return true;
}


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
	m_aadLevelsMap= new double** [12]; //has one matrix for each audio band
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
	if (!videoIsComplete) return videoIsComplete;
	
	//init
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
