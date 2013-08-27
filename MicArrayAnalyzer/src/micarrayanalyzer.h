/**********************************************************************
 
 Audacity: A Digital Audio Editor
 
 Microphone Array Analyzer
 
 micarrayanalyzer.h
 
 Luca Novarini
 
 **********************************************************************/


#ifndef __MICARRAYANALYZER_MICARRAYANALYZER_H__
#define __MICARRAYANALYZER_MICARRAYANALYZER_H__

#include <wx/wx.h>
#include <wx/filename.h>   //Needed to use wxFileName class
#include <sndfile.h>       //Needed to read WAV files
#include <string>
#include <wx/string.h>
#include <map>
#include <stdlib.h>
#include <Audacity.h>
#include <SampleFormat.h>
#include <Sequence.h>
#include <widgets/ProgressDialog.h>
#include "virtualmikes.h"
#include "meshandinterpol.h"
#include "multivolver.h"   //Used to compute matrix convolution!
#include "afaudio.h"       //Here's the definition of AFAudioTrack class.
#include "video.h"


#include "commdefs.h"

using namespace std;

#define   MAP_WIDTH  960
#define   MAP_HEIGHT 480

const int WAV_FORMAT_ANDMASK = 0x0000000F; //A useful mask to read libsndfile format field
const int X_RES              = MAP_WIDTH;  //Image panel X resolution, in pixels.
const int Y_RES              = MAP_HEIGHT; //Image panel Y resolution, in pixels.
const int X_RES_DEG          = 360;
const int Y_RES_DEG          = 180;
const double MIN_SPL_DEFAULT = 0.0;       //dB
const double FS_DEFAULT      = 120.0;     //dB

/// Conversion from C-string to wxString
#define         cs2ws(s)   (wxString(s,wxConvUTF8))


// -------------------------
// AudioPool Class Header
// -------------------------
// AFAudioTrack is a powerful class that helds audio data and does filtering and some other useful operations!
// AudioPool is a simple derivation that adds specific functionalities to this base class.
class AudioPool : public AFAudioTrack
	{
		ProgressDialog  *mProgress;
		
		double** ppdResultsMatrix; //ROWS = various channels, COLUMN 1 = Linear Leq for each channel, COLUMN 2 = A-Filtered Leq, COLUMN 3 = ecc.ecc.
		bool bResultsMatrixAlloc;
		double dFcOctaveBandFilters[10];
		
		//Private methods
		double LeqFilteredTrack(int ch);        //Returns Leq_dB of Filtered Channel #ch.
		bool ResultsMatrixInit();
		
	protected:
		void InitProgressMeter(const wxString& operation);
		bool UpdateProgressMeter(int step,int total);
		void DestroyProgressMeter();
		
	public:
		double FindOverallMax();            //Find max abs value for the whole audio pool.
		bool ApplyOverallGain(double gain); //Applying gain to each sample of each track of the pool.
		double GetResultsMatrixCell(int row, int col) { return ppdResultsMatrix[row][col]; }
		double** GetResultsMatrix() {return ppdResultsMatrix;}
		double GetMaxResultInTheMatrix();
		double GetMinResultInTheMatrix();
		double GetMaxResultInTheBand(int col); //Returns MAX level inside the choosen ppdResultsMatrix column.
		double GetMinResultInTheBand(int col); //Returns MIN level inside the choosen ppdResultsMatrix column.
		bool FillResultsMatrix();  //Hard working function!
		
		void SetResultsMatrix(double** ppd) {ppdResultsMatrix = ppd;} //errelle 
		
		//Constructor/Destructor
		AudioPool(const int nTracks, double dBFullScale, double Fs);
		~AudioPool();
	};

//-------------------------------
// MicArrayAnalyzer Class Header
//-------------------------------

class MicArrayAnalyzer
	{
	private:
//		ProgressDialog  *mProgress;
		
		double dMinSPLThreshold;
		double dFSLevel;
		double dProjectRate; //  samples/sec
		sampleFormat sfProjectFormat;
		int iProjectNumTracks;
		sampleCount iAudioTrackLength; //num of samples
		
		bool bMirroredMikesAlloc; // [esseci]
		
		wxFileName* wxfnXMLFile;
		bool bXMLFileAlloc;
		
		wxFileName* wxfnWAVFile;
		bool bWAVFileAlloc;
		
		SNDFILE *infile;
		bool bSndFileAlloc;
		SF_INFO sfinfo;
		wxString wxsMicName;
		wxString wxsManufacturer;
		int iArrayType;
		int iMikesCoordsUnits;
		int iCapsules;
		int iVirtualMikes;
		int iDeconvIRsLength;
		
		double *MikesCoordinates;
		bool bMikesCoordsAlloc;
		
		wxBitmap wxbBgndImage;
		bool bBgndImageAlloc;
		wxFileName* wxfnBgndImageFile;
		
		VirtualMikesSet *vmsMirroredMikes;  //It MAY contains mirrored virtual mikes, ONLY IF the array is spherical.
		TriangularMesh **tmMeshes;
		int iNTriangles;                    //# of stored triangular meshes
		
		float **ppfAudioData, **ActualFrameAudioData;
		/*********************************************/
//		map<int, double**> resultCube;
		/*********************************************/
		bool bAudioDataAlloc;
		float *pfLocalMin;      //Four arrays of local/absolute min/max for each audio track. Used to apply correctly FS scaling!
		float *pfLocalMax;
		float *pfAbsoluteMin;
		float *pfAbsoluteMax;
		float fdBScalingFactor;
		
		float ***pppfDeconvIRsData;
		bool bDeconvIRsDataAlloc;
		
		AudioPool *apOutputData;
		bool bResultsAvail;  //This is a flag that will be set when filtering and averaging is done.
		
		AFMatrixvolver* afmvConvolver;   //Used to compute matrix convolution
		
		int *piWatchpoints;              //Watchpoints (x,y) will be stored in this array in a linear fashion.
		int iWatchpoints;                //Number of stored watchpoints.
		wxArrayString wxasWatchpointsLabels;
		bool bWatchpointsAlloc;          //false = watchpoints not yet defined.
		
		bool GetMirroredMike(double original_x, double original_y, double* mirror_xy, int mirror_num);
		void InitLevelsMap(int frame);
		
		int curFrame;
		double frameLength; // seconds
		sampleCount frameLengthSmpl; //samples
		float frameOverlapRatio; // ratio [0,1]
		bool playing;
		bool bandAutoscale;
		
		
		
	protected:
	//	void InitProgressMeter(const wxString& operation);
//		bool UpdateProgressMeter(int step,int total);
//		void DestroyProgressMeter();
		
	public:     
		Video *outputFrames;

		wxCriticalSection *mAAcritSec;  //protects common data among  threads

		bool ReadXMLData();
		bool BadXML();
		bool BadWAV();
		void AudioDataInit();                     //Init of the whole audio data space.
		bool AudioTrackInit(int i, int length);   //Init of a single audio track, inside the audio data space.
		bool LoadDeconvIRs();                     //That guy does everything, from memory allocation to read from wav file.
		void NextFrame() {
			SetCurFrame(++curFrame); 
//							apOutputData->SetResultsMatrix(resultCube[curFrame]);
		}
		void DeleteAllData();
		void PrintResults();
		void PrintResult(unsigned int frame);
		void PrintActualFrame(int frame);
		void PrintLevels();
		
		// Getters
		double GetFSLevel() { return dFSLevel; }
		double GetMinSPLThreshold() { return dMinSPLThreshold; }
		double GetMaxSPL(bool autoscale_each_band = false, int band = 0);  //max in the whole video if louder than minSPLthreshold
		double GetMinSPL(bool autoscale_each_band = false, int band = 0);  //min in the whole video if louder than minSPLthreshold
		int GetArrayType() { return iArrayType; }
		wxString GetMicName() { return wxsMicName; }
		wxString GetManufacturer() { return wxsManufacturer; }
		int GetCapsulesNumber() { return iCapsules; }
		int GetVirtualMikes() { return iVirtualMikes; }
		int GetDeconvIRsLength() { return iDeconvIRsLength; }
		sf_count_t GetWAVLength() { return sfinfo.frames; }
		int GetWAVChannels() { return sfinfo.channels; }
		int GetWAVSampleRate() { return sfinfo.samplerate; }
		wxString GetWAVFormatName();
		sampleFormat GetWAVSampleFormat();
		double GetProjSampleRate() { return dProjectRate; }
		sampleFormat GetProjSampleFormat() { return sfProjectFormat; }
		int GetProjNumTracks() { return iProjectNumTracks; }
		float* GetAudioDataTrack(int id) { return ppfAudioData[id]; }
		wxBitmap GetBGNDBmp() { if (bBgndImageAlloc) {return wxbBgndImage;} else {return NULL;} }
		double GetResult(int ch, int band) { if(bResultsAvail) { return apOutputData->GetResultsMatrixCell(ch,band); } else return 0; }
		int GetNumOfMeshes() { return iNTriangles; }
		int InOrOutTriangle(int a, int b, int c) { return tmMeshes[c]->PointTest(a,b); }
		TriangularMesh* GetTriangle(int value) { return tmMeshes[value]; }
		sampleCount GetAudioTrackLength() {return iAudioTrackLength;} //errelle
		int GetNumOfFrames() {return outputFrames->GetNumOfFrames();}
		int GetCurFrame() {return curFrame;}
		wxString GetCurTime();
		double GetFrameLength() {return frameLength;}
		sampleCount GetFrameLengthSmpl() {return frameLengthSmpl;}
		sampleCount GetFrameOverlapSmpl() {return frameOverlapRatio*frameLengthSmpl;}
		double GetFrameOverlapRatio() {return frameOverlapRatio;}
		bool Playing() {return playing;}
		int GetTransparency() {return outputFrames->GetTransparency();}
		bool IsBandAutoscale() {return bandAutoscale;}
		
		// Setters
		void SetLocalMinMax(int id,float min,float max) { if(bAudioDataAlloc) { pfLocalMin[id] = min; pfLocalMax[id] = max; } }
		void SetAbsoluteMinMax(int id,float min,float max) { if(bAudioDataAlloc) { pfAbsoluteMin[id] = min; pfAbsoluteMax[id] = max; } }
		bool SetAudioTrackLength(int value);
		void SetProjSampleRate(double value) { dProjectRate = value; }
		void SetProjSampleFormat(sampleFormat value) { sfProjectFormat = value; }
		void SetProjectNumTracks(int value) { iProjectNumTracks = value; }
		void SetXMLFile(const wxString& str);
		void SetWAVFile(const wxString& str);
		bool SetBgndImage(const wxString& str);
		void SetFSLevel(double value) { dFSLevel = value; }
		void SetMinSPLThreshold(double value) { dMinSPLThreshold = value; }
		void SetNumOfFrames(int value) {outputFrames->SetNumOfFrames(value); }
		void SetCurFrame(int value) {
			curFrame = value; 
			apOutputData->SetResultsMatrix( outputFrames->GetFrameMatrix(curFrame));
#ifdef __AUDEBUG__
//			PrintResult(curFrame);
#endif
		}
		void SetFrameLength(double value) {frameLength = value; frameLengthSmpl = frameLength * dProjectRate;}
		void SetFrameLengthSmpl(sampleCount valueSmpl){ frameLengthSmpl = valueSmpl; }
		void SetFrameOverlapRatio(double ratio) {frameOverlapRatio = ratio;}
		void SetPlaying(bool value) {playing = value;}
		void SetBandAutoscale(bool value) {bandAutoscale = value;}
		void SetTransparency(int valTrans) {outputFrames->SetTransparency(valTrans);}
				
		void ClearInterpolCoeffs() { for (int i=0;i<iNTriangles;i++) { tmMeshes[i]->DeleteCoeffs(); } }
		void CalculateFSScalingFactor();
		bool Calculate(unsigned int f); // This function does the hard work!

		MicArrayAnalyzer();
		MicArrayAnalyzer(const MicArrayAnalyzer& mMAA); //ellerre
		~MicArrayAnalyzer();
	};



#endif // __MICARRAYANALYZER_MICARRAYANALYZER_H__
