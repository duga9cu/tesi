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


class WaveTrack;

class EffectMicArrayAnalyzer: public Effect
   {
   private:
      MicArrayAnalyzer *mMAA;
	   ProgressDialog  *m_frameProgress;

      bool LoadTrackData(WaveTrack *wt, int id);
      void SelectTracks(bool status);
      void SelectAllTracks();
      void DeselectAllTracks();
      void End();
   
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

