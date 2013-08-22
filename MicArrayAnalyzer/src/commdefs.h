/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Common libraries

  commdefs.h

  Angelo Farina - Simone Campanini

**********************************************************************/
#ifndef __AURORA_COMMDEFS_H__
#define __AURORA_COMMDEFS_H__

#include <wx/wx.h>

#include "audtypes.h"
#include "version.h"

#define   AURORA_NAME   "Aurora"
#define wxAURORA_NAME _("Aurora")

#include <assert.h>
#include <math.h>

// ----- from unixsh math.h
#ifndef M_PI
    #define M_PI        3.1415926535897932384626433
#endif
#ifndef M_SQRT2
    #define M_SQRT2     1.41421356237309504880  /* sqrt(2) */
#endif
#ifndef M_SQRT1_2
    #define M_SQRT1_2   0.70710678118654752440  /* 1/sqrt(2) */
#endif
#ifndef M_E
    #define M_E         2.7182818284590452354   /* e */
#endif

// #ifndef TWO_PI
//     #define TWO_PI      6.2831853   /* 2*pi */
// #endif

// ----- custom
#define dB(x)     ((x > 0) ? 10.0*log10(x) : -200.0)
#define dB20(x)   ((x > 0) ? 20.0*log10(x) : -200.0)
#define undB(x)   (pow(10.0, x/10.0))
#define undB20(x) (pow(10.0, x/20.0))
//inline double undB(double x, double b = 10.0) {
//	return std::pow(10.0,x/b);
//}
//inline double undB20(double x) {
//	return undB(x,20.0);
//}

// these are for fftw_complex vectors
#ifndef __FFTW_REIM__
#define __FFTW_REIM__
    #define Re(c) c[0]         // real part of c fftw[f]_complex
    #define Im(c) c[1]         // imag part of c fftw[f]_complex
    #define Mod(c)    sqrt(c[0]*c[0] + c[1]*c[1]) // Module, where 'c' is a fftw[f]_complex
    #define SqrMod(c)     (c[0]*c[0] + c[1]*c[1])  // Square module, where 'c' is a fftw[f]_complex
    #define Magnitude(c)    sqrt(c[0]*c[0] + c[1]*c[1])  // Magnitude and Mod should be alias.
    #define SqrMagnitude(c)      (c[0]*c[0] + c[1]*c[1])
    #define Phase(c)        (-atan2(c[1], c[0])) 
    #define DegPhase(c)     (-(atan2(c[1], c[0]) * 180) / M_PI)
    #define Mag(c) c[0]
    #define Ph(c)  c[1]
#endif

// useful for rounding to nearest integer
#define iround(d)  ( int((d >= 0) ? floor(d + 0.5) : ceil(d - 0.5)) )
#define afround(d) (AFSampleCount(d + 0.5))

#ifdef __WXWIN__
    // Windows use the backslash in path expressions...
    #define TRAILING_SLASH wxT("\\")
    #define TRAILING_SLASH_CH '\\'
#else
    // ...while Unixes system use the slash.
    #define TRAILING_SLASH wxT("/")
    #define TRAILING_SLASH_CH '/'
#endif

#ifdef __WXMSW__
   #define LINE_BREAK  _("\r\n")
#else
   #define LINE_BREAK  _("\n")
#endif

#endif // __AURORA_COMMDEFS_H__