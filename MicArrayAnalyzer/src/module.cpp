/**********************************************************************
 
 Audacity: A Digital Audio Editor
 
 Microphone Array Analyzer
 
 module.cpp
 
 Luca Novarini
 
 **********************************************************************/


#include <effects/EffectManager.h>
#include <LoadModules.h>
#include <Prefs.h>

#include "gui.h"
#include "module.h"

#include <wx/timer.h>

//#ifndef __AUDEBUG__  //FORCING DEBUG MODE
//#define __AUDEBUG__
//#endif

// ----------------------------------------------------------------------------
// MyThread
// ----------------------------------------------------------------------------

MyThread::MyThread(MicArrayAnalyzer* maa, int frame)
: wxThread()
{
	mMAA = maa;
    m_count = frame;
}

MyThread::~MyThread()
{	
	//TODO

}

wxThread::ExitCode MyThread::Entry()
{
    printf("Thread started (priority = %u). id #=%d\n", GetPriority(), GetId());
	
	// check if the application is shutting down: in this case all threads
	// should stop a.s.a.p.
	{
		wxCriticalSectionLocker locker(mMAA->m_critSec); //approfondisci
		
        // check if just this thread was asked to exit
		if ( TestDestroy() ) return NULL;
						
		if(Calculate())
		{
			printf("\n************************** Process: calculate(%d) ***************************\n",m_count+1);
		}
		else
		{
			wxMessageBox(_("Something strange occourred.\nCannot calculate Acoustical Parameters."),_("Error"), wxOK | wxICON_ERROR);
			//		 delete mAp; mAp = 0;
			return false;
		}		
		
		printf("Thread id#=%d finished.\n", GetId());
		
		return NULL;
	}
}	

bool MyThread::Calculate()
{
	int frame = m_count;
	sampleCount frameLengthSmpl = mMAA->GetFrameLengthSmpl();
	float frameOverlapRatio = mMAA->GetFrameOverlapRatio();
	sampleCount	iAudioTrackLength = mMAA->GetAudioTrackLength();
	int iProjectNumTracks = mMAA->GetProjNumTracks();
	float ** ppfAudioData = mMAA->GetAudioData();
	float ***pppfDeconvIRsData = mMAA->GetDeconvIRsData();
	wxBitmap wxbBgndImage = mMAA->GetBGNDBmp();
	int iArrayType = mMAA->GetArrayType();
	VirtualMikesSet* vmsMirroredMikes = mMAA->GetVirtualMikeSet();
	bool bMirroredMikesAlloc = mMAA->GetMirroredMikesAlloc();
	int iVirtualMikes = mMAA->GetVirtualMikes();
	double * MikesCoordinates = mMAA->GetMikesCoordinates();
	int iNTriangles = mMAA->GetNumOfMeshes();
	TriangularMesh** tmMeshes = mMAA->GetTriangles();
	AFMatrixvolver* afmvConvolver = mMAA->GetConvolver();
	AudioPool* apOutputData = mMAA->GetapOutputData();
	
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer::Calculate(): copying ppfAudioData into ActualFrameAudioData\n");
	fflush(stdout);
#endif
	sampleCount startFrameSmpl = (frame-1)*(frameLengthSmpl - frameLengthSmpl*frameOverlapRatio); // frame is bound between 1 and numofFrames but we want the first frame to start from the first sample (0)
	sampleCount endFrameSmpl = startFrameSmpl + frameLengthSmpl;
	bool lastframe = false;
	int zeropadding=0;
	if (endFrameSmpl >= iAudioTrackLength) { //on the last frame, cut!
		zeropadding=endFrameSmpl-iAudioTrackLength;
		endFrameSmpl = iAudioTrackLength;
		lastframe=true;
	}
	
	for (int i=0; i<iProjectNumTracks; i++) {  //copy data into actual frame
		for (int j=startFrameSmpl; j<endFrameSmpl; j++) {    
			ActualFrameAudioData[i][j-startFrameSmpl] = ppfAudioData[i][j];
		}
	}
	
	if (lastframe) { //on the last frame, zero padding!
		for (int i=0; i<iProjectNumTracks; i++) { 
			for (int j=endFrameSmpl; j<endFrameSmpl+zeropadding; j++) {    
				ActualFrameAudioData[i][j-startFrameSmpl] = 0;
			}
		}	
	}
	
	
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer::Calculate(): Background image check and resize\n");
	fflush(stdout);
#endif
	
	//	InitProgressMeter(_("Checking background image size..."));
	
	//Background Image Size Check (and scaling if necessary)
	if ((wxbBgndImage.GetWidth() != X_RES)||(wxbBgndImage.GetHeight() != Y_RES))
	{
		//We need to scale choosen image to fit image panel dimensions
		wxImage tmp = wxbBgndImage.ConvertToImage();
		tmp = tmp.Scale(X_RES,Y_RES,wxIMAGE_QUALITY_HIGH);
		wxbBgndImage = wxBitmap(tmp);
	}
	
	//	UpdateProgressMeter(1,1);
	
	//	DestroyProgressMeter();	
	
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer::Calculate(): Adding virtual mikes to Delaunay triangulation.\n");
	fflush(stdout);
#endif
	
	//	InitProgressMeter(_("Adding virtual mikes to the Delaunay triangulation..."));
	
	//Adding mikes to the Delaunay triangulation
	Delaunay::Point tempP;
	vector<Delaunay::Point> v;
	
	if (iArrayType == 0)
	{
#ifdef __AUDEBUG__
		printf("MicArrayAnalyzer::Calculate(): Virtual mikes mirroring ENABLED (spherical array detected).\n");
		fflush(stdout);
#endif
		vmsMirroredMikes = new VirtualMikesSet;   //For spherical arrays we need to "clone" each virtual mike properly
		//to guarantee ColorMap boundary continuity.
		//See "GetMirroredMikes" if you want to explore cloning rules!
		bMirroredMikesAlloc = true;
	}
	int i, j;
	for (i=0;i<iVirtualMikes;i++)
	{
		//		UpdateProgressMeter(i,iVirtualMikes);
		
		tempP[0] = MikesCoordinates[2*i]; tempP[1] = MikesCoordinates[2*i + 1];
#ifdef __AUDEBUG__
		printf("MicArrayAnalyzer::Calculate(): adding virtual mike [%d]\n",i);
		fflush(stdout);
		//         VirtualMike* pvmDebug;
#endif
		v.push_back(tempP);  //Adding mike to the triangulation
		
		if (iArrayType == 0)
		{
			for (j=0;j<3;j++)   //For each virt. mike, three mirrored mikes exists.
            {
				double dMirroredMike[2];
			mMAA->GetMirroredMike(MikesCoordinates[2*i],MikesCoordinates[2*i+1],dMirroredMike,j); //Retrieving mirror #j mike coords.
				tempP[0] = dMirroredMike[0]; tempP[1] = dMirroredMike[1];
#ifdef __AUDEBUG__
				printf("MicArrayAnalyzer::Calculate(): adding mirror [%d] of virtual mike [%d]\n",j,i);
				fflush(stdout);
#endif
				v.push_back(tempP);                                     //Adding mirrored mike to the triangulation
				vmsMirroredMikes->AddVirtualMike(tempP[0],tempP[1],i);    //By passing "i" to AddMike we specify that this is a clone of Mic #i.
            }
		}
	}
	
	//	DestroyProgressMeter();
	
	//	InitProgressMeter(_("Generating mesh surface..."));
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer::Calculate(): Triangulating...");
	fflush(stdout);
#endif
	Delaunay dt(v);   //"dt" stands for (d)elaunay (t)riangulation
	dt.Triangulate(); //The triangulation will be computed here....
	iNTriangles = dt.ntriangles(); //Storing the number of computed triangular meshes
	
	//	UpdateProgressMeter(1,iNTriangles+1);
	
	tmMeshes = new TriangularMesh* [iNTriangles];      //The computed triangulation will be stored inside a TriangularMesh array.
	int x[3],y[3],mic[3];                              //(x,y) = position, mic = mic #.
	Delaunay::fIterator fit = dt.fbegin();
	
	int k;
	for(j=0;j<iNTriangles;j++)
	{
		//		UpdateProgressMeter(j+1,iNTriangles+1);
		x[0] = dt.point_at_vertex_id(dt.Org(fit))[0];
		x[1] = dt.point_at_vertex_id(dt.Dest(fit))[0];
		x[2] = dt.point_at_vertex_id(dt.Apex(fit))[0];
		y[0] = dt.point_at_vertex_id(dt.Org(fit))[1];
		y[1] = dt.point_at_vertex_id(dt.Dest(fit))[1];
		y[2] = dt.point_at_vertex_id(dt.Apex(fit))[1];
		
		for (i = 0; i < iVirtualMikes; i++)
			for (k = 0; k < 3; k++)
				if ((x[k] == MikesCoordinates[2*i])&&(y[k] == MikesCoordinates[2*i + 1]))
				{
					mic[k] = i; //Find and save mic # for each vertex.
				}
		
		VirtualMike* pvmCurrent;
		
		for (i = 0; i < vmsMirroredMikes->GetNumberOfMikes(); i++)
			for (k = 0; k < 3; k++)
            {
				pvmCurrent = vmsMirroredMikes->GetVirtualMike(i);
				if ((x[k] == pvmCurrent->GetX())&&(y[k] == pvmCurrent->GetY()))
				{
					mic[k] = pvmCurrent->GetMicID(); //Find and save original mic # for each mirrored mike too.
				}
            }
		tmMeshes[j] = new TriangularMesh(x,y,mic);
		++fit;
	}
	//	DestroyProgressMeter();
	
	
	//Setting up convolution class
#ifdef __AUDEBUG__
	printf("Triangulating...DONE\nMicArrayAnalyzer::Calculate(): Setting up convolution class.\n");
	fflush(stdout);
#endif
    //afmvConvolver = new AFMatrixvolver(sfinfo.channels, iCapsules, iAudioTrackLength, iDeconvIRsLength); //The class constructor wanna know, in order: # of rows, # of columns, Audacity audio data Length, IRs length.
	afmvConvolver = new AFMatrixvolver(iVirtualMikes, mMAA->GetCapsulesNumber(), mMAA->GetFrameLengthSmpl(), mMAA->GetDeconvIRsLength()); //The class constructor wanna know, in order: # of rows, # of columns, Audacity audio data Length, IRs length.
	afmvConvolver->SetMatrixAutorange(false); //I disabled autorange because it works on each output channel separately.
	afmvConvolver->SetRemoveDC(true);         //Remove DC is good instead.
	afmvConvolver->SetPreserveLength(true);   //Length preservation (truncation) enabled.
	
	//Copying data pointers inside the convolution class
	for(i = 0; i < iVirtualMikes; i++)  //for each row of the IRs matrix (REMEMBER that sfinfo.channels and iVirtualMikes are the same thing...)
	{
#ifdef __HARDDEBUG__
		printf("MicArrayAnalyzer::Calculate(): Copying audio track [%d] pointer.\n",i);
		fflush(stdout);
#endif
		afmvConvolver->SetInputVectorItem(ActualFrameAudioData[i],i); //inside this "for" loop I load Audacity tracks too instead of using another separate "for"
		for(j = 0; j < mMAA->GetCapsulesNumber(); j++)
		{
#ifdef __HARDDEBUG__
            printf("MicArrayAnalyzer::Calculate(): Copying IR (%d,%d) pointer.\n",i,j);
            fflush(stdout);
#endif
			afmvConvolver->SetFilterMatrixItem(pppfDeconvIRsData[i][j],i,j);
		}
	}
	
	/* Convolution calculation!
	 The convolution is computed in this fashion:
	 
	 |ir(1,1) ir(1,2) .... ir(1,j)|   |x1|
	 |ir(2,1) ir(2,2) .... ir(2,j)|   |x2|
	 |ir(3,1) ir(3,2) .... ir(3,j)|   |x3| 
	 | .....   .....  ....  ..... | * |..|  = |y1 y2 y3 ... yi|
	 | .....   .....  ....  ..... |   |..|
	 |ir(i,1)  .....  .... ir(i,j)|   |xj|
	 
	 where i = (# of rows) = (# of virtual microphones) and j = (# of audacity project tracks) = (# of array capsules).
	 "Obviously" yk = ir(k,1) * x1 + ir(k,2) * x2 + ... + ir(k,j) * xj , where * stands for convolution, not a simple product :)
	 AFMatrixvolver class does the summation too!
	 */
	//	 #ifdef __AUDEBUG__
	//	 printf("MicArrayAnalyzer::Calculate(): Convolving...");
	//	 fflush(stdout);
	//	 #endif
	//	 afmvConvolver->Process();
	//	 #ifdef __AUDEBUG__
	//	 printf("DONE\n");
	//	 fflush(stdout);
	//	 #endif
	
	
	//Retrieving Convolution Output Data
	//	InitProgressMeter(_("Retrieving convolution results from convolver object..."));
	mMAA->CalculateFSScalingFactor();   //Finding the project track with the max absolute level, and computing the ratio between this level and the local peak level of the same track. This will be used as a trick to associate dFSLevel with the absolute max without the need of convolving the entire recording!
	apOutputData = new AudioPool(iVirtualMikes,mMAA->GetdFSLevel() - double(mMAA->GetfdBScalingFactor()), mMAA->GetProjSampleRate()); //AudioPool alloc
	for(int i=0; i<iVirtualMikes; i++)
	{
#ifdef __AUDEBUG__
		printf("MicArrayAnalyzer::Calculate(): Retrieving convolution result [%d] from convolver object.\n",i);
		fflush(stdout);
#endif
		//		UpdateProgressMeter(i,iVirtualMikes);
		//Arguments: 1st -> track #, 2nd -> data pointer, 3rd -> data vector length, 4th -> true if data output array need to be alloc before copying.
		//apOutputData->SetTrack(i,(float*)afmvConvolver->GetOutputVectorItem(i),afmvConvolver->GetOutputVectorItemLength(),true);
		apOutputData->SetTrack(i,ActualFrameAudioData[i], mMAA->GetFrameLengthSmpl(), true); //***DEBUG*** BYPASSING CONVOLUTION!
	}
	//	DestroyProgressMeter();
	
	//NORMALIZING Output Tracks! -->> new peak level will be 1.
	//	InitProgressMeter(_("Autoranging output signals to match FS..."));
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer::Calculate(): AutoRanging output signals.\n");
	fflush(stdout);
#endif
	double dMax;
	dMax = apOutputData->FindOverallMax();
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer::Calculate(): Found Max Level = %f [pressure]\n",dMax);
	fflush(stdout);
#endif
	//	UpdateProgressMeter(1,2);
	apOutputData->ApplyOverallGain(1/dMax);
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer::Calculate(): applied overall gain = %f ; new overall max = %f [pressure]\n",1/dMax,apOutputData->FindOverallMax());
	fflush(stdout);      
#endif
	//	UpdateProgressMeter(2,2);
	//	DestroyProgressMeter();
	
	//Calculating Results
	if (apOutputData->FillResultsMatrix()) {
		//		resultCube[frame]=apOutputData->GetResultsMatrix(); 
		//construct video frame
		VideoFrame* videoframe= new VideoFrame(apOutputData->GetResultsMatrix(),
											   apOutputData->GetChannelsNumber(),
											   frame,
											   apOutputData->GetMaxResultInTheMatrix(),
											   apOutputData->GetMinResultInTheMatrix());
		for (int band=0; band<12; band++) {
			videoframe->SetMaxInTheBand(apOutputData->GetMaxResultInTheBand(band), band);
			videoframe->SetMinInTheBand(apOutputData->GetMinResultInTheBand(band), band);
		}//and add it to the video!
	mMAA->outputFrames->AddFrame(videoframe);
		mMAA->SetResultAvail(true);
	}
	else {		mMAA->SetResultAvail(false); }
	
	//	PrintResult(frame);
	
	//THE END!
	return true;
}

// ----------------------------------------------------------------------------
// EffectMicArrayAnalyzer
// ----------------------------------------------------------------------------
MyThread *EffectMicArrayAnalyzer::CreateThread(int frame) 
{ 
	MyThread *thread = new MyThread(mMAA,frame); 
	if ( thread->Create() != wxTHREAD_NO_ERROR ) 
	{ 
		wxLogError(wxT("Can't create thread!")); 
	} 
	wxCriticalSectionLocker enter(m_critsect); 
	m_threads.Add(thread); 
	return thread; 
} 

void EffectMicArrayAnalyzer::UpdateThreadStatus()
{
	wxCriticalSectionLocker enter(m_critsect);
	
	// update the counts of running/total threads
	size_t nRunning = 0,
	nCount = m_threads.Count();
	for ( size_t n = 0; n < nCount; n++ )
	{
		if ( m_threads[n]->IsRunning() )
			nRunning++;
	}
	
	if ( nCount != m_nCount || nRunning != m_nRunning )
	{
		m_nRunning = nRunning;
		m_nCount = nCount;
		
		printf("%u threads total, %u running.", unsigned(nCount), unsigned(nRunning));
	}
	//else: avoid flicker - don't print anything
}


bool EffectMicArrayAnalyzer::Init()
{
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer: INIT\n");
	fflush(stdout);
#endif
	
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer: Allocating new MicArrayAnalyzer object.\n");
	fflush(stdout);
#endif
	
	mMAA = new MicArrayAnalyzer();
	
	sampleFormat trackFormat;
	int ntracks;
	
	// ------------- Checking proj tracks rate & format ----------------
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer: Proj rate & format check.\n");
	fflush(stdout);
#endif
	this->CopyInputTracks(); // Set up mOutputTracks (mOutputTracks is a TrackList object where input tracks will be copied)
	TrackListIterator iter(mOutputTracks);
	WaveTrack *waveTrack = (WaveTrack*)(iter.First());
	
	ntracks = GetNumWaveTracks();
	trackFormat = waveTrack->GetSampleFormat();  //Assuming first track as a reference for track format!
	
#ifdef __AUDEBUG__
	int debug = 0;
#endif
	while (waveTrack != NULL)
	{
#ifdef __AUDEBUG__
		printf("MicArrayAnalyzer: track [%d] check...\n",debug);
		fflush(stdout);
		debug++;
#endif
		if ((mProjectRate != waveTrack->GetRate()) || (trackFormat != waveTrack->GetSampleFormat()))
		{
			wxMessageBox(_("One or more tracks with mismatched sample rate and/or format."),_("Error"),wxOK|wxICON_ERROR);
			delete mMAA;
			mMAA = 0;
			return false;
		}
		waveTrack = (WaveTrack*)(iter.Next());
	}
	
	//All seems to be ok....
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer: Rate & format check COMPLETED.\n");
	fflush(stdout);
#endif
	mMAA->SetProjectNumTracks(ntracks);
	mMAA->SetProjSampleFormat(trackFormat);
	mMAA->SetProjSampleRate(mProjectRate);
	sampleCount framelengthsmpl = mMAA->GetFrameLength() * mProjectRate ;
	mMAA->SetFrameLengthSmpl(framelengthsmpl);
	return true;
}

bool EffectMicArrayAnalyzer::LoadTrackData(WaveTrack *wt, int id)
{
	sampleCount start;
	sampleCount end;
	
	//Get start and end times from track
	double trackStart = wt->GetStartTime();
	double trackEnd   = wt->GetEndTime();
	
	//Set the current bounds to whichever left marker is
	//greater and whichever right marker is less:
	double curT0 = mT0 < trackStart? trackStart: mT0;
	double curT1 = mT1 > trackEnd? trackEnd: mT1;
	
	// Process only if the right marker is to the right of the left marker
	if (curT1 > curT0)
	{
		float local_min, local_max, absolute_min, absolute_max;
		wt->GetMinMax(&local_min, &local_max, curT0, curT1);
		wt->GetMinMax(&absolute_min, &absolute_max, trackStart, trackEnd);
		
		//Transform the marker timepoints to samples
		start = wt->TimeToLongSamples(curT0);
		end   = wt->TimeToLongSamples(curT1);
		
		mMAA->SetLocalMinMax(id,local_min,local_max);
		mMAA->SetAbsoluteMinMax(id,absolute_min,absolute_max);
		
		if(mMAA->SetAudioTrackLength(end-start)) 
			mMAA->AudioTrackInit(id,end-start); //Memory allocation
		wt->Get((samplePtr)mMAA->GetAudioDataTrack(id),floatSample,start,end-start);
	}
	return true;
}

bool EffectMicArrayAnalyzer::PromptUser()
{
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer: PROMPTUSER\n");
	fflush(stdout);
#endif
	
	
	
	//---------------- Loading tracks data from Audacity current project ----------------
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer: Copying tracks data into MicArrayAnalyzer object.\n");
	fflush(stdout);
#endif
	mMAA->AudioDataInit();  //Alloc the main audio data pool (the array of tracks!)
	TrackListIterator iter(mOutputTracks);
	WaveTrack *waveTrack = (WaveTrack*)(iter.First());
	
	for (int i = 0; i < mMAA->GetProjNumTracks(); i++)
	{
#ifdef __AUDEBUG__  // **** DEBUG   
		printf("MicArrayAnalyzer: Copying track [%d] data...\n", i);
		fflush(stdout);
#endif
		
		if ((!LoadTrackData(waveTrack,i)) || (waveTrack == NULL))
		{
			wxMessageBox(_("Error copying data from Audacity project!"),_("Error"),wxOK|wxICON_ERROR);
			delete mMAA;
			mMAA = 0;
			return false;
		}
		
		//Iterate to the next track
		waveTrack = (WaveTrack*)(iter.Next());
	}
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer: Project tracks copy SUCCEDEED.\n");
	fflush(stdout);
#endif
	
	
	
	
	//---------------- Even more set up ----------------
	sampleCount atl= mMAA->GetAudioTrackLength();
	sampleCount fls =  mMAA->GetFrameLengthSmpl();
	sampleCount ovlp = mMAA->GetFrameOverlapSmpl();
	int numOfFrames = atl / (fls-ovlp);  
	mMAA->SetNumOfFrames(numOfFrames);
	
	//----------------  Showing conf dialog ----------------
	if (!DoShowConfDialog()) 
		return false;
	
	//---------------- Loading deconvolution IRs from file ----------------
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer: Copying deconv IRs from file to MicArrayAnalyzer object.\n");
	fflush(stdout);
#endif
	if(!mMAA->LoadDeconvIRs())
	{
		wxMessageBox(_("Error copying deconv IRs from WAV file!"),_("Error"),wxOK|wxICON_ERROR);
		delete mMAA;
		mMAA = 0;
		return false;
	}
	
	return true;
}

bool EffectMicArrayAnalyzer::Process()  
{
#ifdef __AUDEBUG__
	printf("This is PROCESS\n");
	fflush(stdout);
#endif
	
	// ---- is it necessary anymore? ----
//	//check if frameLength is sufficiently short
//	if(mMAA->GetFrameLengthSmpl() > mMAA->GetAudioTrackLength() ) {
//		printf("Process: redefining frame Length because audio track to analyze is shorter!");
//		mMAA->SetFrameLength(mMAA->GetAudioTrackLength() / 10);
//		mMAA->SetFrameLengthSmpl( mMAA->GetFrameLength() * mProjectRate );		
//	}
	
	InitVideoProgressMeter(_("Calculating video frame for each band..."));
	
	
	for (sampleCount frame = 1; frame <= mMAA->GetNumOfFrames(); frame++) 
	{
		CreateThread(frame)->Run();
		UpdateVideoProgressMeter(frame,mMAA->GetNumOfFrames());
	}
#ifdef __AUDEBUG__
	mMAA->PrintResults();
#endif
	while (!m_threads.empty()) 
	{
	//TODO wait on the all done condition!
		wxSleep(10000);
	}
	DestroyVideoProgressMeter();
	
	MicArrayAnalyzerDlg dlog_1(mParent, mMAA);
	
	dlog_1.CenterOnParent();
	if(dlog_1.ShowModal())
	{
		//m_bProcess = true;
	}
	
	return true;
}

void EffectMicArrayAnalyzer::End()
{
	// Deleting mMAA object
	delete mMAA;
	mMAA = 0;
}

bool EffectMicArrayAnalyzer::DoShowConfDialog() {
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer: Showing conf dialog.\n");
	fflush(stdout);
#endif
	MicArrayAnalyzerConfDlg dlog(mParent, mMAA);
	dlog.CenterOnParent();
	
	if(!dlog.ShowModal())
	{
		wxMessageBox(_("An error occurred while showing configuration dialog."),_("Microphone Array Analyzer plug-in"),wxOK|wxICON_ERROR);
		delete mMAA;
		mMAA = 0;
		return false;
	}
	return true;
}

void EffectMicArrayAnalyzer::InitVideoProgressMeter(const wxString& operation)
{
	mProgress = new ProgressDialog(_("Mic Array Analyzer"),operation);
}

bool EffectMicArrayAnalyzer::UpdateVideoProgressMeter(int step,int total)
{
	return bool(mProgress->Update(step, total) == eProgressSuccess); // [esseci] 
}

void EffectMicArrayAnalyzer::DestroyVideoProgressMeter()
{
	if(mProgress) delete mProgress;
	mProgress = 0;
}



EffectMicArrayAnalyzer::EffectMicArrayAnalyzer()
: mMAA(0), m_shuttingDown(false)
{}


EffectMicArrayAnalyzer::~EffectMicArrayAnalyzer()
{
	if(mMAA != 0) delete mMAA;
}


//----------------------------------------------------------------------------
// Module callback
//----------------------------------------------------------------------------
extern "C"
{
#ifdef _MSC_VER
#define DLL_API _declspec(dllexport)
#else
#define DLL_API __attribute__ ((visibility("default")))
#endif
	
	// [esseci] da qui in giu` riscritta per compatibilita` con Audacity 1.3.14 e successivi.
	//          Attenzione: se hai una versione precedente, quasi certamente non funzionera`
	
	wxString g_wxszVersion;
	
	extern DLL_API const wxChar* GetVersionString();	
	extern DLL_API int ModuleDispatch(ModuleDispatchTypes type);
	
	const wxChar* GetVersionString()
	{
		if(gPrefs != 0)
			gPrefs->Read(wxT("/Version"), &g_wxszVersion);
		
		return g_wxszVersion.c_str();
	}
	
	int ModuleDispatch(ModuleDispatchTypes type)
	{
		switch(type)
		{
			case ModuleInitialize: 
			{
#ifdef __AUDEBUG__
				fprintf(stderr, "[MicArrayAnalyzer]: dispatch %d received.\n", int(type));
#endif
				EffectManager & em = EffectManager::Get();
				em.RegisterEffect(new EffectMicArrayAnalyzer(), BUILTIN_EFFECT | ANALYZE_EFFECT );
				break;
			}
				
			case ModuleTerminate:
			case AppInitialized:
			case AppQuiting:
			case ProjectInitialized:
			case ProjectClosing:
			case MenusRebuilt:
#ifdef __AUDEBUG__
				fprintf(stderr, "[MicArrayAnalyzer]: dispatch %d received.\n", int(type));
#endif
				break;
				
			default:
#ifdef __AUDEBUG__
				fprintf(stderr, "[MicArrayAnalyzer]: unknown dispatch received.\n");
#endif
				break;
		} 
		
		return 1;
	}
};



// Indentation settings for Vim and Emacs and unique identifier for Arch, a
// version control system. Please do not modify past this point.
//
// Local Variables:
// c-basic-offset: 3
// indent-tabs-mode: nil
// End:
//
// vim: et sts=3 sw=3
// arch-tag: c05d7383-e7cd-410e-b7b8-f45f47c9e283

