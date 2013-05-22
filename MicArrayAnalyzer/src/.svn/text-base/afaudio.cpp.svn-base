/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Common libraries

  afaudio.h

  Angelo Farina - Simone Campanini

*******************************************************************//**

\class AFAudioTrack
\brief A base class for audio track manipulation in the Angelo Farina's way

  This class can store an audio data vector and its methods can do
  some basic operations on it, plus it has some filtering tools.
  When filtering a backup of the waveform is taken.

*//*******************************************************************/
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "afaudio.h"

bool AFAudioTrack::InitTrack(const int nCh)
{
    if(m_smpcLen == 0) return false;
    DeleteTrack(nCh);

    m_apsmpTrack[nCh]         = new AFSample[m_smpcLen];
    m_apsmpFilteredTrack[nCh] = new AFSample[m_smpcLen];
   
    return true;
}

bool AFAudioTrack::DeleteTrack(const int nCh)
{
   if(m_apsmpTrack[nCh]) 
       delete [] m_apsmpTrack[nCh];
   if(m_apsmpFilteredTrack[nCh]) 
       delete [] m_apsmpFilteredTrack[nCh];
   
   return true;
}

void AFAudioTrack::Copy(AFSample *src, AFSample *dest, AFSampleCount len, double gain)
{ for(AFSampleCount i=0; i < len; i++) dest[i] = AFSample(gain * src[i]); }

//---------------------------- Utils------------------------------
void AFAudioTrack::ResetFilteredTrack(const int nCh, const double gain)
{ Copy(m_apsmpTrack[nCh], m_apsmpFilteredTrack[nCh], m_smpcLen, gain); }

void AFAudioTrack::ReplaceTrackWithFiltered(const int nCh, const double gain)
{ Copy(m_apsmpFilteredTrack[nCh], m_apsmpTrack[nCh], m_smpcLen, gain); } 

void AFAudioTrack::FindMin(const int nCh)
{
    double max = 0.0;
    for(AFSampleCount i = 0; i < m_smpcLen; i++) 
        max = (m_apsmpTrack[nCh][i] > max) ? m_apsmpTrack[nCh][i] : max;
}

void AFAudioTrack::FindMax(const int nCh)
{
    double min = 0.0;
    for(AFSampleCount i = 0; i < m_smpcLen; i++) 
        min = (m_apsmpTrack[nCh][i] < min) ? m_apsmpTrack[nCh][i] : min;
}

//---------------------------- Filtering methods------------------------------

void AFAudioTrack::IIR(const int nCh, 
                       const double alpha, const double beta, const double gamma, 
                       const double mu, const double sigma)
{
   // code by Angelo Farina
   AFSampleCount n = 0;
   double x_n;
   double x_nm1 = 0.0;
   double x_nm2 = 0.0;
   double y_nm1 = 0.0;
   double y_nm2 = 0.0;
   
//   printf("IIR Filter INIT: alpha=%f beta=%f gamma=%f mu=%f sigma=%f\n",alpha,beta,gamma,mu,sigma);
//   fflush(stdout);
   
   x_n = m_apsmpFilteredTrack[nCh][n];
   // x_(n) = 2 * (Alfa * (x_n + Mu * x_nm1 + sigma * x_nm2) + gamma * y_nm1 - beta * y_nm2) - Basic
   m_apsmpFilteredTrack[nCh][n] = AFSample( 2.0 * (alpha * (x_n + mu*x_nm1 + sigma*x_nm2) + gamma*y_nm1 - beta*y_nm2) );
//   printf("IIR Filter: PROCESSING CHANNEL [%d], x[%d]=%f x[%d]=%f x[%d]=%f y[%d]=%f y[%d]=%f y[%d]=%f\n",nCh,n-2,x_nm2,n-1,x_nm1,n,x_n,n-2,y_nm2,n-1,y_nm1,n,m_apsmpFilteredTrack[nCh][n]);
//   fflush(stdout);
   x_nm2 = x_nm1;
   x_nm1 = x_n;
   
   n = 1;
   x_n = m_apsmpFilteredTrack[nCh][n];
   y_nm1=m_apsmpFilteredTrack[nCh][n-1];
   m_apsmpFilteredTrack[nCh][n] = AFSample( 2.0 * (alpha * (x_n + mu*x_nm1 + sigma*x_nm2) + gamma*y_nm1 - beta*y_nm2) );
//   printf("IIR Filter: PROCESSING CHANNEL [%d], x[%d]=%f x[%d]=%f x[%d]=%f y[%d]=%f y[%d]=%f y[%d]=%f\n",nCh,n-2,x_nm2,n-1,x_nm1,n,x_n,n-2,y_nm2,n-1,y_nm1,n,m_apsmpFilteredTrack[nCh][n]);
//   fflush(stdout);
   x_nm2 = x_nm1;
   x_nm1 = x_n;
   
   for(n=2; n<m_smpcLen; n++) {
      x_n   = m_apsmpFilteredTrack[nCh][n];
      y_nm1 = m_apsmpFilteredTrack[nCh][n-1];
      y_nm2 = m_apsmpFilteredTrack[nCh][n-2];
      m_apsmpFilteredTrack[nCh][n] = AFSample( 2.0 * (alpha * (x_n + mu*x_nm1 + sigma*x_nm2) + gamma*y_nm1 - beta*y_nm2) );
//      printf("IIR Filter: PROCESSING CHANNEL [%d], x[%d]=%f x[%d]=%f x[%d]=%f y[%d]=%f y[%d]=%f y[%d]=%f\n",nCh,n-2,x_nm2,n-1,x_nm1,n,x_n,n-2,y_nm2,n-1,y_nm1,n,m_apsmpFilteredTrack[nCh][n]);
//      fflush(stdout);
      x_nm2 = x_nm1;
      x_nm1 = x_n;
   }
}

void AFAudioTrack::Gain(const int nCh, const double G)
{
   // G [dB] -> g
   double g = pow(10.0, G/20.0);
   for(AFSampleCount k=1; k<m_smpcLen; k++) m_apsmpFilteredTrack[nCh][k] *= g;
}

void AFAudioTrack::Filter(const int type, const int nCh, const double f0, const double fQ)
{
   // code by Angelo Farina

   // Two poles IIR filter
   double alpha = 0.0;
   double mu    = 0.0;
   double sigma = 0.0;
   
//   printf("Filter: f0=%f fQ=%f M_PI=%f m_dbRate=%f\n",f0,fQ,M_PI,m_dbRate);
//   fflush(stdout);
   
   double theta0 = 2.0 * M_PI * f0 / m_dbRate;
   double d      = 2.0 * tan(theta0 / 2.0 / fQ) / sin(theta0);
   double beta   = 0.5 * (1.0 - 0.5*d*sin(theta0)) / (1.0 + 0.5*d*sin(theta0));
   double gamma  = (0.5 + beta) * cos(theta0);

//   printf("Filter: theta0=%f d=%f beta=%f gamma=%f\n",theta0,d,beta,gamma);
//   fflush(stdout);

   switch(type) {
   case BPF:
      mu    = 0.0;
      alpha = (0.5 - beta) / 2.0;
      sigma = -1.0;
      break;
   case LPF:
      mu    = 2.0;
      alpha = (0.5 + beta - gamma) / 4.0;
      sigma = 1.0;
      break;
   case HPF:
      mu    = -2.0;
      alpha = (0.5 + beta + gamma) / 4.0;
      sigma = 1.0;
      break;
   case NotchF: 
      mu    = -2 * cos(theta0);
      alpha = (0.5 + beta) / 2.0;
      sigma = 1.0;
      break;
   default:
      break;
   } 
   
//   printf("Filter: alpha=%f mu=%f sigma=%f\n",alpha,mu,sigma);
//   fflush(stdout);

   IIR(nCh, alpha, beta, gamma, mu, sigma);
}


void AFAudioTrack::AFilter(const int nCh)
{
   // code by Angelo Farina
 
   // IIR two-poles filter
 
   //  filter 1 - high pass 20.6 Hz
   double c_1 =  1.0 - exp(-2.0 * M_PI * (20.6) / m_dbRate);
   double c_1m = 1.0 - c_1;
   //  filter 2 - high pass 20.6 Hz
   double c_2 =  1.0 - exp(-2.0 * M_PI * (20.6) / m_dbRate);
   double c_2m = 1.0 - c_2;
   //  filter 3 - high pass 107.7 Hz
   double c_3 =  1.0 - exp(-2.0 * M_PI * (107.7) / m_dbRate);
   double c_3m = 1.0 - c_3;
   //  filter 4 - high pass 737.9 Hz
   double c_4 =  1.0 - exp(-2.0 * M_PI * (737.9) / m_dbRate);
   double c_4m = 1.0 - c_4;
   //  filter 5 - low pass 12200 Hz
   double c_5 =  1.0 - exp(-2.0 * M_PI * (12200.0) / m_dbRate);
   double c_5m = 1.0 - c_5;
   //  filter 6 - low pass 12200 Hz
   double c_6 =  1.0 - exp(-2.0 * M_PI * (12200.0) / m_dbRate);
   double c_6m = 1.0 - c_6;

   // the following are delays
   double delta_1 = 0.0;
   double delta_2 = 0.0;
   double delta_3 = 0.0;
   double delta_4 = 0.0;

   double A,B,C,D,E,F;

   AFSampleCount k = 0;
   // The first sample is elaborated separately.
   //   first 4 high pass filters 
   A = m_apsmpFilteredTrack[nCh][k] - delta_1;
   delta_1 = m_apsmpFilteredTrack[nCh][k] * c_1 + delta_1 * c_1m;
   B = A - delta_2;
   delta_2 = A * c_2 + delta_2 * c_2m;
   C = B - delta_3;
   delta_3 = B * c_3 + delta_3 * c_3m;
   D = C - delta_4;
   delta_4 = C * c_4 + delta_4 * c_4m;
   
   E=D;
   F=D;
   //   2 last low pass filters
   E = D * c_5 + E * c_5m;
   F = E * c_6 + F * c_6m;
   m_apsmpFilteredTrack[nCh][k] = AFSample(F/0.858);
   
   for (k=1;  k<m_smpcLen; k++) {
      //    first 4 high pass filters
      A = m_apsmpFilteredTrack[nCh][k] - delta_1;
      delta_1 = m_apsmpFilteredTrack[nCh][k] * c_1 + delta_1 * c_1m;
      B = A - delta_2;
      delta_2 = A * c_2 + delta_2 * c_2m;
      C = B - delta_3;
      delta_3 = B * c_3 + delta_3 * c_3m;
      D = C - delta_4;
      delta_4 = C * c_4 + delta_4 * c_4m;
      
      //    2 last low pass filters
      E = D * c_5 + E * c_5m;
      F = E * c_6 + F * c_6m;
      m_apsmpFilteredTrack[nCh][k] = AFSample(F/0.858); // correction to make 1kHz gain  0 dB
   }
}

void AFAudioTrack::LFilter(const int nCh)
{
   // code by Angelo Farina
 
   double f0,fQ;

   //  filter 1 - high pass 10 Hz
   f0 = 10.0f; // Hz
   fQ = 0.707f;
   Filter(HPF, nCh, f0, fQ); 
   //  filter 2 - high pass 14 Hz
   f0 = 14.0f; // Hz
   fQ = 0.707f;
   Filter(HPF, nCh, f0, fQ); 
   //  filter 3 - high pass  20 Hz
   f0 = 20.0f; // Hz
   fQ = 0.707f;
   Filter(HPF, nCh, f0, fQ);
   /*
   //  filter 4 - low pass 20 kHz
   f0 = 20000.0f; // Hz
   fQ = 0.707f;
   Filter(LPF, nCh, f0, fQ); 
   //  filter 5 - low pass 20.4 kHz
   f0 = 20400.0f; // Hz
   fQ = 0.707f;
   Filter(LPF, nCh, f0, fQ); 
   //  filter 6 - low pass 20.9 kHz
   f0 = 20900.0f; // Hz
   fQ = 0.707f;
   Filter(LPF, nCh, f0, fQ); 
   */
}

void AFAudioTrack::ISO_8041_Filter(const int nCh)
{
   // Ponderazione Accelerazione Asse Generico secondo norma ISO-8041
   //void AccFilter(float  *X,float fSamp,long IRL)
    
// filtro 1 - passa alto 0.7943 Hz
   const double c_1 =  1.0 - exp(-2.0 * M_PI * (0.7943) / m_dbRate);
   const double c_1m = 1.0 - c_1;
// filtro 2 - passa alto 0.7943 Hz
   const double c_2 =  1.0 - exp(-2.0 * M_PI * (0.7943) / m_dbRate);
   const double c_2m = 1.0 - c_2;
// filtro 3 - passa basso 5.684 Hz
   const double c_3 =  1.0 - exp(-2.0 * M_PI * (5.684) / m_dbRate);
   const double c_3m = 1.0 - c_3;
// filtro 4 - passa basso 100 Hz
   const double c_4 =  1.0 - exp(-2.0 * M_PI * (100.0) / m_dbRate);
   const double c_4m = 1.0 - c_4;
// filtro 5 - passa basso 100 Hz
   const double c_5 =  1.0 - exp(-2.0 * M_PI * (100.0) / m_dbRate);
   const double c_5m = 1.0 - c_5;

   AFSampleCount k;
   double delta_1 = 0.0;
   double delta_2 = 0.0;
   double A,B,C=0.0, D=0.0, E=0.0;

   for(k = 0; k < m_smpcLen; k++) {
        
//      primi 2 filtri passa alto in cascata
      A = m_apsmpFilteredTrack[nCh][k] - delta_1;
      delta_1 = m_apsmpFilteredTrack[nCh][k] * c_1 + delta_1 * c_1m;
      B = A - delta_2;
      delta_2 = A * c_2 + delta_2 * c_2m;

//      3 filtri passa basso conclusivi
      C = B * c_3 + C * c_3m;
      D = C * c_4 + D * c_4m;
      E = D * c_5 + E * c_5m;
      m_apsmpFilteredTrack[nCh][k] = AFSample(E*1.19); // correzione per rendere il guadagno ad 1 Hz = 0 dB
   }
}

void AFAudioTrack::ITU_P56_Filter(const int nCh)
{
   // code by Angelo Farina
   // Filtro passa-banda secondo ITU-P56 (160-5500 Hz)
   double f0,fQ;
   
//  filtro 1 - passa alto 110 Hz
   f0=110.0; // Hz
   fQ=0.7;   // Butterworth
   Filter(HPF, nCh, f0, fQ);    
//  filtro 2 - passa alto 90 Hz
   f0=90.0;  // Hz
   fQ=1.5;
   Filter(HPF, nCh, f0, fQ);    
//  filtro 3 - passa basso 6500 Hz
   f0=6500.0; // Hz
   fQ=0.8;
   Filter(LPF, nCh, f0, fQ);    
//  filtro 4 - passa basso 7500 Hz
   f0=7500.0; // Hz
   fQ=1.8;     //era 1.9
   Filter(LPF, nCh, f0, fQ);
//  filtro 5 - passa banda 1100 Hz
   f0=1100.0; // Hz
   fQ=0.11;
   Filter(BPF, nCh, f0, fQ);

// Correzione guadagno -0.11 dB
   Gain(nCh, -0.15);

}

void AFAudioTrack::UNI_9916_Filter(const int nCh)
{
   // Filtro passa basso a 250 Hz - UNI 9916
   double f0,fQ;
   
//  filtro 1 - passa basso 250 Hz
   f0=320.0; // Hz
   fQ=1.0;   // Butterworth
   Filter(LPF, nCh, f0, fQ);    
//  filtro 2 - passa basso 260 Hz
   f0=360.0;  // Hz
   fQ=0.6;
   Filter(LPF, nCh, f0, fQ);    
//  filtro 3 - passa basso 270 Hz
   f0=400.0; // Hz
   fQ=1.1;
   Filter(LPF, nCh, f0, fQ);    
//  filtro 4 - passa basso 280 Hz
   f0=500.0; // Hz
   fQ=0.5;     //era 1.9
   Filter(LPF, nCh, f0, fQ);

// Correzione guadagno 0.0 dB
   Gain(nCh, 0.0);

}

void AFAudioTrack::OctaveFilter(const int nCh, const double dbFc)
{   
   // code by Angelo Farina

   double f0, fQ;
   // Band filtering with six-poles IIR filter
   // first filter (2 poles)
   f0 = 0.755f * dbFc;
   fQ = 6.0f;
   Filter(BPF, nCh, f0, fQ); 
   // second filter (2 poles)
   f0 = dbFc;
   fQ = 3.0f;
   Filter(BPF, nCh, f0, fQ); 
   // third filter (2 poles)
   f0 = 1.33f * dbFc;
   fQ = 6.0f;
   Filter(BPF, nCh, f0, fQ); 
}


void AFAudioTrack::RemoveMean(const int nCh)
{
   // code by Angelo Farina

   double dbMean = 0.0;
   AFSampleCount i;

   for(i = 0; i < m_smpcLen; i++)
      dbMean += m_apsmpFilteredTrack[nCh][i];

   dbMean /= double(m_smpcLen);

   for(i = 0; i < m_smpcLen; i++)  
      m_apsmpFilteredTrack[nCh][i] -= AFSample(dbMean);

}

double  AFAudioTrack::NoiseCorrection(const int nCh)
{
   double dbFactor = 0.0;
   double dbSample = 0.0;
   
   // Now will calculate the mean of the IR's last 16th energy
   for(AFSampleCount i = (m_smpcLen - (AFSampleCount)(m_smpcLen/16)); 
       i < m_smpcLen; i++) {

         dbSample  = m_apsmpFilteredTrack[nCh][i];
         dbSample *= dbSample;
         dbFactor += dbSample; 
   }

   dbFactor /= double(m_smpcLen/16); // Square of the noise RMS value

   return dbFactor;
}


void AFAudioTrack::SetTrack(int nCh, AFSample *psmpSrc, bool bInitTrack)
{  
    if(m_smpcLen > 0) 
    {
        if(bInitTrack) InitTrack(nCh);

        memcpy(m_apsmpTrack[nCh], psmpSrc, m_smpcLen * sizeof(AFSample)); 
        ResetFilteredTrack(nCh);
//        FindMin(nCh);    FindMax(nCh);
    }
}


void AFAudioTrack::SetTrack(const int nCh, AFSample *psmpSrc, const AFSampleCount smpcLen, const bool bInitTrack)
{  
    SetTrackLength(smpcLen, bInitTrack, nCh);

    memcpy(m_apsmpTrack[nCh], psmpSrc, m_smpcLen * sizeof(AFSample)); 
    ResetFilteredTrack(nCh);
//    FindMin(nCh); FindMax(nCh);
}

void AFAudioTrack::SetTrack(const int nCh, double *pdbSrc, bool const bInitTrack)
{  
    if(m_smpcLen > 0) 
    {
        if(bInitTrack) InitTrack(nCh);

        for(AFSampleCount i = 0; i < m_smpcLen; i++) 
            m_apsmpTrack[nCh][i] = pdbSrc[i];
        
        ResetFilteredTrack(nCh);
//        FindMin(nCh);  FindMax(nCh);
    }
}


void AFAudioTrack::SetTrack(const int nCh, double* pdbSrc, const AFSampleCount smpcLen, const bool bInitTrack)
{  
    SetTrackLength(smpcLen, bInitTrack, nCh);

    for(AFSampleCount i = 0; i < m_smpcLen; i++) 
        m_apsmpTrack[nCh][i] = pdbSrc[i];
    
    ResetFilteredTrack(nCh);
//    FindMin(nCh);  FindMax(nCh);
}

void AFAudioTrack::SetTrackLength(const AFSampleCount smpcLen, const bool bInitTrack, int nCh)
{
    m_smpcLen = smpcLen; 
    if(bInitTrack) InitTrack(nCh);
}



AFAudioTrack::AFAudioTrack(const int nChannels) 
  : m_nMode(AFM_MONO),
    m_dbRate(0),
    m_nChannels(nChannels),
    m_dbFullScale(120.0),  // dB
    m_smpcLen(0)
{
#ifdef __AUDEBUG__
   printf("afaudio: istantiated for %d tracks\n", m_nChannels); fflush(stdout);
#endif
   m_apsmpTrack = new AFSample* [m_nChannels];
   m_apsmpFilteredTrack = new AFSample* [m_nChannels];
   m_pdbMin = new double [m_nChannels];
   m_pdbMax = new double [m_nChannels];
   
   for(int nCh = 0; nCh < m_nChannels; nCh++) {
       
       m_apsmpTrack[nCh]  = 0; 
       m_apsmpFilteredTrack[nCh] = 0;
       m_pdbMin[nCh]= 0;
       m_pdbMax[nCh]= 0;
   }
   
   switch(m_nChannels) {
       case 2: m_nMode = AFM_STEREO; break;
       case 4: m_nMode = AFM_TETRA;  break;
   }
}


AFAudioTrack::~AFAudioTrack()
{
    for(int nCh = 0; nCh < m_nChannels; nCh++)
        DeleteTrack(nCh);
   
    delete [] m_apsmpTrack;
    delete [] m_apsmpFilteredTrack;
    delete [] m_pdbMin;
    delete [] m_pdbMax;
}
