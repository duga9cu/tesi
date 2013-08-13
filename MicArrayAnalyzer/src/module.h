/**********************************************************************

  Audacity: A Digital Audio Editor
              
  Microphone Array Analyzer
  
  module.h

  Luca Novarini

**********************************************************************/

#ifndef __MICARRAYANALYZER_MODULE_H__
#define __MICARRAYANALYZER_MODULE_H__


#include <Audacity.h>
#include <effects/Effect.h>
#include <WaveTrack.h>
#include <SampleFormat.h>
#include <Sequence.h>

#include "micarrayanalyzer.h"



// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/thread.h"
#include "wx/dynarray.h"
#include "wx/numdlg.h"
#include "wx/progdlg.h"
#include "del_interface.h"

class WaveTrack;

WX_DEFINE_ARRAY_PTR(wxThread *, wxArrayThread); 

// --------------------------------------------------------------------------- 
// a simple thread 
// --------------------------------------------------------------------------- 
class MyThread : public wxThread 
	{ 
	public: 
		MyThread(MicArrayAnalyzer* maa, int frame); 
		virtual ~MyThread(); 
		// thread execution starts here 
		virtual void *Entry(); 
	public: 
		unsigned m_count;  //?????
		MicArrayAnalyzer* mMAA;
	private:
		bool Calculate();
		float** ActualFrameAudioData;
	}; 


// --------------------------------------------------------------------------- 
// main effect class
// --------------------------------------------------------------------------- 
class EffectMicArrayAnalyzer: public Effect
   {
   private:
      MicArrayAnalyzer *mMAA;
      bool LoadTrackData(WaveTrack *wt, int id);
      void SelectTracks(bool status);
      void SelectAllTracks();
      void DeselectAllTracks();
	  bool DoShowConfDialog();
      void End();
	  MyThread *CreateThread(int frame);
	   void UpdateThreadStatus();
	   
	   // remember the number of running threads and total number of threads
	   size_t m_nRunning,
	   m_nCount;
   
   public:
      // ---------------- Standard Audacity Effects' methods ----------------
      virtual wxString GetEffectName() { return wxString(_("Microphone Array Analyzer...")); }
      virtual wxString GetEffectIdentifier() { return wxString(_("MicArrayAnalyzer")); }
      virtual wxString GetEffectAction() { return wxString(_("MicArrayAnalyzer")); }

      virtual std::set<wxString> GetEffectCategories() 
         {
         std::set<wxString> result;
         result.insert(wxT("http://lv2plug.in/ns/lv2core/#AnalyserPlugin"));
         return result;
         }

      virtual int GetEffectFlags() { return BUILTIN_EFFECT | PROCESS_EFFECT; }   

      virtual bool Init();
      virtual bool PromptUser();

   protected:
      virtual bool Process();
	   
	   void InitVideoProgressMeter(const wxString& operation);
	   bool UpdateVideoProgressMeter(int step,int total);
	   void DestroyVideoProgressMeter();

 
   public:     
      EffectMicArrayAnalyzer();
      ~EffectMicArrayAnalyzer();
	   
	   // critical section protects access to all of the fields below 
	   wxCriticalSection m_critsect; 
	   // all the threads currently alive - as soon as the thread terminates, it's removed from the array 
	   wxArrayThread m_threads; 
	   // semaphore used to wait for the threads to exit, see MyFrame::OnQuit() 
	   wxSemaphore m_semAllDone; 
	   // indicates that we're shutting down and all threads should exit 
	   bool m_shuttingDown;

	   
//	   DECLARE_EVENT_TABLE()
   };


#endif // __MICARRAYANALYZER_MODULE_H__

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

