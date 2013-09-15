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

//#ifndef __AUDEBUG__  //FORCING DEBUG MODE
//#define __AUDEBUG__
//#endif

// ----------------------------------------------------------------------------
// MyThread
// ----------------------------------------------------------------------------

MyThread::MyThread(MicArrayAnalyzer* maa,unsigned int frame,wxMutex *mutex, wxCondition *condition, wxCriticalSection* cs, size_t* tc)
: wxThread()
{
	mMAA = maa;
    m_count = frame;
	m_mutexCondFinish = mutex;
	m_condFinish = condition;
	effectCritsect= cs;
	pnThreadCount = tc;
	bOutOfMemoryExit = false;
}

MyThread::~MyThread()
{			
	printf("Thread id# = %d finished.\n", m_count);
}

void MyThread::InitThreadMAA() 
{
	threadMAA = new MicArrayAnalyzer(*mMAA);
}

wxThread::ExitCode MyThread::Entry()
{
//#ifdef __AUDEBUG__
//		effectCritsect->Enter(); //thread atomicity
//#endif
	mMAA->m_errorBuffer.Printf(_("Frame %d Run Out Of Memory ! ... go get some more memory ;)"),m_count); //just in case ...

    printf("Thread started (priority = %u). id #=%d\n", GetPriority(), m_count);

	if (mMAA->GetErrorOutOfMemory()) return NULL;

	InitThreadMAA();
	if(mMAA->GetErrorOutOfMemory()) {
		mMAA->outputFrames->SetNumOfFrames(mMAA->outputFrames->GetSize() - (*pnThreadCount+1));
		mMAA->mAAcritSec->Leave(); //connected to the entry() in gotbadalloc
		return NULL;
	}
	wxThreadIdType threadId = this->GetId();
	printf("\n************************** Process: calculate(%d) ***************************\n",m_count);
	if(threadMAA->Calculate(m_count))
	{
		printf("Process: calculate(%d) successfully executed by thread # %lu\n",m_count, threadId);
	}
	else
	{
		printf("Process: calculate(%d)  executed by thread # %lu FAILED DUE TO LACK OF MEMORY\n",m_count, threadId);
		//		wxMessageBox(_("Something strange occourred.\nCannot calculate Acoustical Parameters."),_("Error"), wxOK | wxICON_ERROR);
		if(!mMAA->outputFrames->IsVideoResized()){
//		mMAA->m_wxsSecurityBuffer.Empty();
			wxMessageBox(mMAA->m_errorBuffer,_("Error"),wxOK|wxICON_ERROR);
		//mMAA->m_errorBuffer.Printf(_("Frame %d Run Out Of Memory ! ... go get some more memory ;)"),m_count);
//		wxMessageBox(mMAA->m_errorBuffer,_("Error"),wxOK|wxICON_ERROR);
		}
		//		delete mAp; mAp = 0;				
	}
	
	wxMutexLocker lock(*m_mutexCondFinish); 
	m_condFinish->Signal();
	wxCriticalSectionLocker locker(*effectCritsect); 
	*pnThreadCount= *pnThreadCount - 1 ;
	if(mMAA->GetErrorOutOfMemory()) {
		if (!mMAA->outputFrames->IsVideoResized()) {
			//resize video with valid frames only!
			mMAA->outputFrames->SetVideoResized();
		mMAA->outputFrames->CutVideo(mMAA->outputFrames->GetSize() - (*pnThreadCount+1));
			
		}
		mMAA->mAAcritSec->Leave(); //connected to the entry() in gotbadalloc
	}
	
//#ifdef __AUDEBUG__
//		effectCritsect->Leave();  //thread atomicity
//#endif
	return NULL;
}	

// ----------------------------------------------------------------------------
// EffectMicArrayAnalyzer
// ----------------------------------------------------------------------------
MyThread *EffectMicArrayAnalyzer::CreateThread(unsigned int frame) 
{
	if (m_nThreadCount >= mMAA->GetNumOfFrames()) return NULL;
	MyThread *thread = new MyThread(mMAA,frame, m_mutexCondFinish, m_condFinish, &effectCritsect, &m_nThreadCount); 
	if ( thread->Create() != wxTHREAD_NO_ERROR ) 
	{ 
		wxLogError(wxT("Can't create thread!")); 
	} 
	m_threads.Add(thread);
	m_nThreadCount++;
	return thread; 
} 

//void EffectMicArrayAnalyzer::UpdateThreadStatus()
//{
//	wxCriticalSectionLocker enter(effectCritsect);
//	
//	// update the counts of running/total threads
//	size_t nRunning = 0,
//	nCount = m_threads.Count();
//	for ( size_t n = 0; n < nCount; n++ )
//	{
//		if ( m_threads[n]->IsRunning() )
//			nRunning++;
//	}
//	
//	if ( nCount != m_nCount || nRunning != m_nRunning )
//	{
//		m_nRunning = nRunning;
//		m_nCount = nCount;
//		
//		printf("%u threads total, %u running.", unsigned(nCount), unsigned(nRunning));
//	}
//	//else: avoid flicker - don't print anything
//}


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
		{
			mMAA->AudioTrackInit(id,end-start); //Memory allocation
			mMAA->SetAudioTrackStart(start);
			mMAA->SetAudioTrackEnd(end);
		}
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
	
	
	//----------------  Showing conf dialog ----------------
	if (!DoShowConfDialog()) 
		return false;
	
	//---------------- Loading deconvolution IRs from file ----------------
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer: Copying deconv IRs from file to MicArrayAnalyzer object.\n");
	fflush(stdout);
#endif
	if(!mMAA->LoadDeconvIRs()) //DEBUG : CONTROLLA QUANTO VALE numofframes
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
	
	MicArrayAnalyzerDlg dlog_1(mParent, mMAA); //init dialog
	
	int numofcores= wxThread::GetCPUCount(); 	
	InitVideoProgressMeter(_("Calculating video frame for each band..."));
	UpdateVideoProgressMeter(1 , mMAA->GetNumOfFrames());
	
#ifdef __AUDEBUG__
	printf("process:: start timer for threads calculate()..\n");
	fflush(stdout);
	m_benchTime.Start();
#endif
	
	//the first frame is on the main thread (in order to complete init of some variables of mMAA)
	printf("\n************************** Process: calculate(%d) ***************************\n",1);
	if(mMAA->Calculate(1))
	{
		//				printf("\n************************** Process: calculate(%d) ***************************\n",mMAA->GetNumOfFrames());
	}
	else
	{
		wxMessageBox(_("Something strange occourred.\nCannot calculate Acoustical Parameters."),_("Error"), wxOK | wxICON_ERROR);
		//		wxMessageBox(_("Out Of Memory ! ... go get some memory ;)"),_("Error"),wxOK|wxICON_ERROR);
		
		//		 delete mAp; mAp = 0;
		return false;
	}	
	
	// the mutex should be initially locked
    m_mutexCondFinish->Lock();
	effectCritsect.Enter();
	unsigned int frame;
	//from second frame we start one thread per core
	for (frame = 2; frame < 2+numofcores; frame++) 
	{
		MyThread* thread = CreateThread(frame);	
		if (thread != NULL) {
			thread->Run(); 
		}
		UpdateVideoProgressMeter(frame , mMAA->GetNumOfFrames());
	}
	
	
	
	//wait for every thread to finish
	//	while (!m_threads.IsEmpty()) {
	while (m_nThreadCount) {
		effectCritsect.Leave();
		m_condFinish->Wait();
		effectCritsect.Enter();
		if (frame <= mMAA->GetNumOfFrames()) 
		{
			MyThread* thread = CreateThread(frame);	
			if (thread != NULL) {
				thread->Run();
			}
		}
		if(!mMAA->GetErrorOutOfMemory()) {
		UpdateVideoProgressMeter(frame , mMAA->GetNumOfFrames());
		frame++;
		} 
	}

	
	effectCritsect.Leave();
	
#ifdef __AUDEBUG__
	//	mMAA->PrintResults();
	printf("\n\n******************* ALL THREADS DONE!! ***************\n");
	printf("process:: stop timer for threads calculate(). ");
	fflush(stdout);
	m_benchTime.Stop();
	printf("timer: elapsed time = %.1f ms", m_benchTime.GetElapsedTime());
#endif
	
	DestroyVideoProgressMeter();
	
	if (mMAA->outputFrames->IsVideoComplete(mMAA->GetErrorOutOfMemory())) {
		printf("\n\n******************* VIDEO COMPLETED!! ***************\n\n");
	}
	//calculate video overall max/min SPL, and for each band too
	if(!mMAA->outputFrames->SetMinsAndMaxs()) {
		mMAA->m_wxsSecurityBuffer.Printf(wxT("Video is not complete! it contains %d frames over %d. There was an irreversible problem."), mMAA->outputFrames->GetSize(), mMAA->GetNumOfFrames());
		wxMessageBox(mMAA->m_wxsSecurityBuffer,_("Error"),wxOK|wxICON_ERROR);
		return false;
	}
	
	//set first frame background image
	mMAA->SetCurFrame(1);
	mMAA->SetBgndImage( mMAA->GetBGNDVideoBmp() );
	//	mMAA->outputFrames->CreateColorMaps();
	
	
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
	mMAA->DeleteAllData();
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
	if (step>total) step=total;
	mMAA->m_wxsSecurityBuffer.Printf(_("Calculating video frame %d for each band..."),step);
	return bool(mProgress->Update(step, total, mMAA->m_wxsSecurityBuffer) == eProgressSuccess); // [esseci] 
}

void EffectMicArrayAnalyzer::DestroyVideoProgressMeter()
{
	if(mProgress) delete mProgress;
	mProgress = 0;
}



EffectMicArrayAnalyzer::EffectMicArrayAnalyzer()
: mMAA(0), m_nThreadCount(0)
{
	m_mutexCondFinish= new wxMutex();
	m_condFinish = new wxCondition(*m_mutexCondFinish);
	assert (m_condFinish->IsOk());
}


EffectMicArrayAnalyzer::~EffectMicArrayAnalyzer()
{
	if(mMAA != 0) {
		mMAA->DeleteAllData();
		delete mMAA;
	}
	delete m_condFinish;
	delete m_mutexCondFinish;
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

