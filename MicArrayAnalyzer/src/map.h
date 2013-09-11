/*
 *  map.h
 *  MicArrayAnalyzer
 *
 *  Created by Simone Campanini on 2/27/12.
 *  Copyright 2012. All rights reserved.
 *
 */

#define __WXDEBUG__

#ifndef __MAP_H__
#define __MAP_H__

#include <wx/wx.h>

#include "micarrayanalyzer.h"

#ifdef __WXDEBUG__
#include "benchmrk.h"
#endif

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////
//enum MeasureUnit { MU_dB   = 0, MU_Pa,   MU_Sqrt,   MU_Cbrt }; 
//double FromdB(const double value_dB, const MeasureUnit mu);

////////////////////////////////////////////////////////////////////////////////
// MyGrob -> GRaphicOBject
////////////////////////////////////////////////////////////////////////////////
#if defined __WXOSX__
    #define MM_FONT_SIZE 10
#elif defined __WXMSW__
    #define MM_FONT_SIZE  8
#else // GTK
    #define MM_FONT_SIZE  6
#endif

class MyGrob
{
  protected:
    wxRect m_wxrctBoundingBox;
    wxFont m_wxFont;

  public:
    virtual void Draw(wxDC& dc) = 0;
  
    // interface
    wxRect& GetBoundingBox()            { return m_wxrctBoundingBox; }
    void SetPosition(const wxPoint pos) { m_wxrctBoundingBox.x = pos.x;
                                          m_wxrctBoundingBox.y = pos.y; }
    void SetSize(const wxSize size)     { m_wxrctBoundingBox.width  = size.GetWidth(); 
                                          m_wxrctBoundingBox.height = size.GetHeight(); } 
    
    // 'ctors
    MyGrob();
    MyGrob(const wxPoint pos, const wxSize size, const int fontSize = MM_FONT_SIZE);
    ~MyGrob();
};

////////////////////////////////////////////////////////////////////////////////
// MyRuler
////////////////////////////////////////////////////////////////////////////////
class MyRuler : public MyGrob
{
  public:
    enum Orientation { RO_HORIZONTAL = 0, RO_VERTICAL };
    enum Format      { RF_DEGREES = 0,    RF_PIXELS };
    enum SymmScale   { RSS_ASYMM = 0,     RSS_SYMM };
    
  private:
    enum Sizes       { RS_FONT             = 7,              
                       RS_MAIN_NOTCHES     = 10,  //Length of main notches
                       RS_SEC_NOTCHES      = 5,   //Length of secondary notches
                       RS_MAIN_DEG_XSUBDIV = 8,   //One subdivision every 45 degrees 
                                                  // (considering X_RES_DEG = 360)
                       RS_SEC_DEG_XSUBDIV  = 4,   //Four secondary notches inside 
                                                  // each 45 degrees interval.
                       RS_MAIN_PX_XSUBDIV  = 8,   //One subdivision every 120 pixels.
                       RS_SEC_PX_XSUBDIV   = 4,   //Four secondary notches inside each 
                                                  // 120 px interval.
                       RS_MAIN_DEG_YSUBDIV = 4,   //Same here, but for Y-Axis Ruler!
                       RS_SEC_DEG_YSUBDIV  = 4,         
                       RS_MAIN_PX_YSUBDIV  = 4,
                       RS_SEC_PX_YSUBDIV   = 4 }; 
    
    int m_iOrientation,
        m_iFormat,
        m_iSymmScale,
        m_iMainSubdiv, 
        m_iSecSubdiv, 
        m_iScaleWidth;
    
    wxBitmap* m_pwxbmpBackground;
    
    void Init();
    
  public:
    virtual void Draw(wxDC& dc);

    // interface
    int GetOrientation() const { return m_iOrientation; }
    int GetFormat     () const { return m_iFormat; }  
    int GetSymmScale  () const { return m_iSymmScale; }
    
    void SetOrientation(const int orientation);
    void SetFormat     (const int format);
    void SetSymmScale  (const int scale);
    
    // 'ctors
    MyRuler();
    MyRuler(const wxPoint pos, const wxSize size, const int orientation = RO_HORIZONTAL);
    ~MyRuler();
};

////////////////////////////////////////////////////////////////////////////////
// MyColorMap
////////////////////////////////////////////////////////////////////////////////
class MyColorMap : public MyGrob
{
  public:
    enum Styles      { CMS_JET = 0, CMS_HOT, CMS_COLD };
    
  private:  
    enum ColorBarSizes { CBS_WIDTH  =  27, 
                         CBS_HEIGHT = 440, 
                         CBS_SMALL_RECT_HEIGHT = 5 }; 
    // Total ColorBar height (440 px) is subdivided into small 27x5 (w x h) px 
    // rectangles (NOTE that small rectangles height should verify 
    //  ColorBarHeight % SmallRectHeight = 0)

    int m_iMeasureUnit;
    int m_iStyle;
    double m_dbMax,
           m_dbMin;
    
  public:
    virtual void Draw(wxDC& dc);
    
    // static
    static bool DoubleToRGB(unsigned char* rgb, 
                            const double   value, 
                            const double   min, 
                            const double   max, 
                            const int      style = CMS_JET);

    //interface 
    int GetMeasureUnit() const { return m_iMeasureUnit; }
    int GetStyle      () const { return m_iStyle; }
    double GetMax     () const { return m_dbMax; }
    double GetMin     () const { return m_dbMin; }
    
    void SetMeasureUnit(const int mu)     { m_iMeasureUnit = mu; }
    void SetStyle      (const int style)  { m_iStyle = style; }
    void SetMax        (const double max) { m_dbMax = max; }
    void SetMin        (const double min) { m_dbMin = min; }
    void SetMaxMin     (const double max, 
                        const double min) { m_dbMax = max; 
                                            m_dbMin = min; }
    // 'ctors
    MyColorMap();    
    MyColorMap(const wxPoint pos, const wxSize size);
    ~MyColorMap();
};

////////////////////////////////////////////////////////////////////////////////
// MyMap events
////////////////////////////////////////////////////////////////////////////////
extern const wxEventType wxEVT_POINTER_POSITION;
#define EVT_POINTER_POSITION(id, fn) \
           DECLARE_EVENT_TABLE_ENTRY( wxEVT_POINTER_POSITION, id, -1 \
                                      (wxObjectEventFunction) (wxEventFunction) \
                                      (wxCommandEventFunction) &fn, (wxObject*) NULL )

////////////////////////////////////////////////////////////////////////////////
// MyMap additional public structures
////////////////////////////////////////////////////////////////////////////////
struct MyMouseCoord
{
    double x, y, z;
    int    format, unit;
    MyMouseCoord()
    : x(0.0), y(0.0), z(0.0), format(MyRuler::RF_PIXELS), unit(MU_dB)
    {}
};

////////////////////////////////////////////////////////////////////////////////
// MyMap
////////////////////////////////////////////////////////////////////////////////
#if defined __WXOSX__
    #define MM_BORDER             5
    #define MM_H_RULER_HEIGHT    30
    #define MM_V_RULER_WIDTH     30
    #define MM_COLOR_MAP_WIDTH   90
    #define MM_COLOR_MAP_HEIGHT 460

#elif defined __WXMSW__
    #define MM_BORDER             5
    #define MM_H_RULER_HEIGHT    25
    #define MM_V_RULER_WIDTH     25
    #define MM_COLOR_MAP_WIDTH   80
    #define MM_COLOR_MAP_HEIGHT 460

#else // GTK
    #define MM_BORDER             5
    #define MM_H_RULER_HEIGHT    20
    #define MM_V_RULER_WIDTH     20
    #define MM_COLOR_MAP_WIDTH   86
    #define MM_COLOR_MAP_HEIGHT 460
#endif

class MyMap : public wxControl
{
  public:
    enum { HORIZONTAL = 0, VERTICAL = 1 };
    
  private:
    enum { ID_MM_TIMER = 2050 };

    double** m_aadLevelsMap;
    wxImage* m_pwximgColorMap;
    wxImage* m_pwximgVirtMikesMap;

#ifdef __WXDEBUG__        
    wxImage*      m_pwximgDebugMap;
    bool          m_bShowDebugMap;      
    TimeBenchmark m_benchTime;
#endif
    
    wxRect   m_wxrctImageBox;
    
    // duplicated data
    int m_iCurrentUnit;
    double m_dbMin,
           m_dbMax;
    // end of duplicated data
    
    int  m_iCurrentBand;
    bool m_bShowVirtMikesPos;
    wxPoint m_awxptVirtMikesPos [32]; // virtual mikes positions as array of points...
    
    int m_iTransparency;
    
    MyRuler    *m_pHorzRuler,
               *m_pVertRuler;       
    MyColorMap* m_pColorMap;
    
    MyMouseCoord m_MouseCoord;
    
    MicArrayAnalyzer* m_pMaa;

    wxTimer m_Timer;
    
    // private methods
    void DrawCrossOnImage(wxImage* img, const int x, const int y, const wxColour* color);
    
    void InitColorMap();
    void InitVirtMikesMap();
#ifdef __WXDEBUG__    
    void InitDebugMap();
    
    void MarkDebugMap(wxPoint& p);
#endif
    
  protected:
    void UpdateMap(wxDC& dc, wxSize size);
    
    // Event handlers
    void OnPaint(wxPaintEvent& evt);
    void OnMouseOverDisplay(wxMouseEvent& evt);
#ifdef __WXDEBUG__
    void OnLeftDClick(wxMouseEvent& evt);
#endif
    void OnTimer(wxTimerEvent& evt);

    virtual wxSize DoGetBestSize() const;
    
    void Init();
    void DestroyMaps();
    
  public:
    // Operations
    bool CopyToClipboard();
	void InitLevelsMap();

    // Interface
    bool AreVirtMikesPosShown() const { return m_bShowVirtMikesPos; }    
    
    MyRuler* GetRuler(const int wich)  { return ((wich == HORIZONTAL) ? m_pHorzRuler
                                                                      : m_pVertRuler); }
    int      GetBand()         const   { return m_iCurrentBand; }
    int      GetMeasureUnit()  const   { return m_iCurrentUnit; }
    int      GetStyle()        const   { return m_pColorMap->GetStyle(); }
    int      GetTransparency() const   { return m_iTransparency; }

    void     GetPointerCoords(double& x, double& y, double& z) const;
    
    void ShowVirtMikesPos(const bool bShow = true) { m_bShowVirtMikesPos = bShow; }
    void SetBand         (const int band);
    void SetMeasureUnit  (const int mu);                                        
    void SetStyle        (const int style);
    void SetMaxMin       (const double max, 
                          const double min);
    void SetTransparency (const int transparency);
	
	void SetImageAlpha(int image,	//case 1:Colormap image , case 2:VirtMikes image, case 3:Debug image
					   const int alpha_perc, 
					   const bool is_colormap = false); 

    
    void SetMicArrayAnalyzerPtr(MicArrayAnalyzer* pMaa) { m_pMaa = pMaa; }
    
    // 'ctors
    MyMap(wxWindow* parent,
          wxWindowID id      = wxID_ANY,
          const wxPoint& pos = wxDefaultPosition,
          const wxSize& size = wxDefaultSize,
          const long style   = wxFULL_REPAINT_ON_RESIZE | wxBORDER_NONE);
    ~MyMap();

};

#endif // __MAP_H__
