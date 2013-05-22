/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Common libraries

  afaudio.h

  Angelo Farina - Simone Campanini

**********************************************************************/
#ifndef __AURORA_AFAUDIO_H__
#define __AURORA_AFAUDIO_H__

#include "audtypes.h"
#include "commdefs.h"


class AFAudioTrack {

   public:
       enum Mode { AFM_MONO = 1, AFM_STEREO = 2, AFM_TETRA = 4 };
       enum FilterType { BPF, LPF, HPF, NotchF };

   protected:     
      int     m_nMode;     // is stereo|tetra
      double  m_dbRate;    //samplerate
      int     m_nChannels; 
      double  m_dbFullScale;
      
      AFSample** m_apsmpTrack;          // audio track
      AFSample** m_apsmpFilteredTrack;

      AFSampleCount m_smpcLen;  // lenghts of the tracks.
      
   private: 
      double* m_pdbMin;  // minimum of the tracks.
      double* m_pdbMax;  // maximum of the tracks.

   protected:   
      // If a track length is set, initialize channel 'ch' track
      bool InitTrack(const int nCh);
      bool DeleteTrack(const int nCh);
   
      void Copy(AFSample *src, AFSample *dest, const AFSampleCount len, const double gain);        
   
      // Find min/max for nChannel 'nCh' track
      void FindMin(const int nCh);
      void FindMax(const int nCh);
   
   public:
      // --- Utils
    
      /// Reset backup track to original 'nCh' track
      void ResetFilteredTrack(const int nCh, const double gain = 1.0);
      
      /// Set track to filtered version for 'nCh' track (loosing backup)
      void ReplaceTrackWithFiltered(const int nCh, const double gain = 1.0);
    
    
    // --- Filtering
   private:
       void IIR(const int nCh, 
                const double alpha, const double beta, const double gamma, 
                const double mu, const double sigma);

   public:
      void Gain(const int nCh, const double G); // G [dB]
      
      void Filter(const int type, const int nCh, const double f0, const double fQ);
      void AFilter(const int nCh); //... bool preserve = true);
      void LFilter(const int nCh);
      void ISO_8041_Filter(const int nCh);
      void ITU_P56_Filter(const int nCh);
      void UNI_9916_Filter(const int nCh);
      void OctaveFilter(const int nCh, const double dbFc);
      void RemoveMean(const int nCh);
      double NoiseCorrection(const int nCh);
      
   // --- Checkers
      bool IsStereo() const { return (m_nMode == AFM_STEREO); }
      bool IsTetra()  const { return (m_nMode == AFM_TETRA); }
      
   // --- Get/Setters
      double  GetSamplerate()     const { return m_dbRate; }
      int     GetChannelsNumber() const { return m_nChannels; }
      double  GetFullScale()      const { return m_dbFullScale; } // dB
      
      AFSample* GetTrack (const int nCh) const         { return m_apsmpTrack[nCh]; }
      AFSample* GetFilteredTrack (const int nCh) const { return m_apsmpFilteredTrack[nCh]; }  
      
      AFSample  GetTrackSample (const int nCh, const AFSampleCount smpl)         const { return m_apsmpTrack[nCh][smpl]; }
      AFSample  GetTrackSquaredSample (const int nCh, const AFSampleCount smpl)  const { return m_apsmpTrack[nCh][smpl] * m_apsmpTrack[nCh][smpl]; }
      AFSample  GetFilteredTrackSample (const int nCh, const AFSampleCount smpl) const { return m_apsmpFilteredTrack[nCh][smpl]; }
      AFSample  GetFilteredTrackSquaredSample (const int nCh, const AFSampleCount smpl) const { return m_apsmpFilteredTrack[nCh][smpl] * m_apsmpFilteredTrack[nCh][smpl]; }
      
      AFSampleCount GetTrackLength() const { return m_smpcLen; }
      
      double  GetTrackMin(const int nCh) const { return m_pdbMin[nCh]; }
      double  GetTrackMax(const int nCh) const { return m_pdbMax[nCh]; }
   
      // TODO: This is here just for compatibility, but must be removed as soon as possible!!!
      void SetStereo(const bool bValue) { m_nChannels = (m_nMode = (bValue) ? AFM_STEREO : AFM_MONO); }
      
      void SetMode(const int nChnls)    { m_nChannels = (m_nMode = nChnls); }
      void SetSamplerate(const double dbValue) { m_dbRate = dbValue; }
      void SetFullScale(const double dbValue)  { m_dbFullScale = dbValue; }
      
      void SetTrack(const int nCh, AFSample *src, const bool bInitTrack = false);
      void SetTrack(const int nCh, double *pdbSrc, const bool bInitTrack = false);
      void SetTrack(const int nCh, AFSample *psmpSrc, const AFSampleCount smpcLen, const bool bInitTrack = false);
      void SetTrack(const int nCh, double *pdbSrc, const AFSampleCount smpcLen, const bool bInitTrack = false);
      
      void SetTrackLength(const AFSampleCount smpcLen, const bool bInitTrack = false, int nCh = 0);
      
      void SetTrackMin(const int nCh, const double dbMin) { m_pdbMin[nCh] = dbMin; }
      void SetTrackMax(const int nCh, const double dbMax) { m_pdbMax[nCh] = dbMax; }
      
      void SetTrackSample(const int nCh, const AFSampleCount smpcPos, const AFSample smpValue)  { m_apsmpTrack[nCh][smpcPos] = smpValue; }
      void SetFilteredTrackSample(const int nCh, const AFSampleCount smpcPos, const AFSample smpValue) { m_apsmpFilteredTrack[nCh][smpcPos] = smpValue; }
   
    // --- Ctors
      AFAudioTrack(const int nChannels = 1);
      ~AFAudioTrack();
};

#endif // __AURORA_IR_H__
