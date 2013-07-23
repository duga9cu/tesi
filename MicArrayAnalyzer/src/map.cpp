/*
 *  map.cpp
 *  MicArrayAnalyzer
 *
 *  Created by Simone Campanini on 2/27/12.
 *  Copyright 2012. All rights reserved.
 *
 */

#include <wx/clipbrd.h>
#include <wx/dcbuffer.h>

#include "myartprovider.h"
#include "micarrayanalyzer.h"
#include "map.h"

////////////////////////////////////////////////////////////////////////////////
// Functions implementation
////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////
// MyGrob implementation
////////////////////////////////////////////////////////////////////////////////

// 'ctors
MyGrob::MyGrob()
 : m_wxrctBoundingBox(),
   m_wxFont(MM_FONT_SIZE, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL)
{}

MyGrob::MyGrob(const wxPoint pos, const wxSize size, const int fontSize)
 : m_wxrctBoundingBox(pos, size),
   m_wxFont(fontSize, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL)
{}

MyGrob::~MyGrob()
{}

////////////////////////////////////////////////////////////////////////////////
// MyRuler implementation
////////////////////////////////////////////////////////////////////////////////
void MyRuler::Init()
{
    if(m_pwxbmpBackground)
        delete m_pwxbmpBackground;
    
    switch(m_iOrientation)
    {
        case RO_HORIZONTAL:
            //m_pwxbmpBackground = new wxBitmap(wxArtProvider::GetBitmap(wxT("xruler_bgnd")));
            switch(m_iFormat)
            {
                case RF_DEGREES:
                    m_iMainSubdiv = RS_MAIN_DEG_XSUBDIV;
                    m_iSecSubdiv  = RS_SEC_DEG_XSUBDIV;
                    m_iScaleWidth = X_RES_DEG;        
                    break;

                case RF_PIXELS:
                    m_iMainSubdiv = RS_MAIN_PX_XSUBDIV;
                    m_iSecSubdiv  = RS_SEC_PX_XSUBDIV;
                    m_iScaleWidth = m_wxrctBoundingBox.width;  //+5;  //JUST 4 GUI DESIGN REASONS we should add 5 
                                                               //       pixels to this (5 px is the total size of panel borders)
                    break;
            }
            break;
            
        case RO_VERTICAL:
            //m_pwxbmpBackground = new wxBitmap(wxArtProvider::GetBitmap(wxT("yruler_bgnd")));
            switch(m_iFormat)
            {
                case RF_DEGREES:
                    m_iMainSubdiv = RS_MAIN_DEG_YSUBDIV;
                    m_iSecSubdiv  = RS_SEC_DEG_YSUBDIV;
                    m_iScaleWidth = Y_RES_DEG;                    
                    break;
                    
                case RF_PIXELS:
                    m_iMainSubdiv = RS_MAIN_PX_YSUBDIV;
                    m_iSecSubdiv  = RS_SEC_PX_YSUBDIV;
                    m_iScaleWidth = m_wxrctBoundingBox.height;
                    break;
            }
            break;            
    }    
    //m_wxrctBoundingBox.width  = m_pwxbmpBackground->GetWidth();
    //m_wxrctBoundingBox.height = m_pwxbmpBackground->GetHeight();
}

void MyRuler::Draw(wxDC& dc)
{
    dc.SetFont(m_wxFont);
    
    //Draw Background image
    //dc.DrawBitmap(*m_pwxbmpBackground, m_wxrctBoundingBox.x, m_wxrctBoundingBox.y);
    dc.SetBrush(wxColour(241, 243, 227));
    dc.SetPen(*wxBLACK_PEN);
    dc.DrawRectangle(m_wxrctBoundingBox);
    
    dc.SetPen(wxColour(223, 215, 198));
            
    wxString wxsLabel;
    int iSubdivCount = m_iMainSubdiv * m_iSecSubdiv;
    
    wxPoint wxptLabelPos(m_wxrctBoundingBox.x, m_wxrctBoundingBox.y);
    
    if(m_iOrientation == RO_HORIZONTAL)
    {
        // Small shadows
        dc.DrawLine(m_wxrctBoundingBox.x, 
                    m_wxrctBoundingBox.y + m_wxrctBoundingBox.height - 1,
                    m_wxrctBoundingBox.x + m_wxrctBoundingBox.width,
                    m_wxrctBoundingBox.y + m_wxrctBoundingBox.height - 1);
        dc.DrawPoint(m_wxrctBoundingBox.x, 
                     m_wxrctBoundingBox.y);
        dc.DrawPoint(m_wxrctBoundingBox.x + m_wxrctBoundingBox.width - 1, 
                     m_wxrctBoundingBox.y);
        
        dc.SetPen(*wxBLACK_PEN);

        wxptLabelPos.x = (m_wxrctBoundingBox.width + 5)/iSubdivCount;
        wxptLabelPos.y = m_wxrctBoundingBox.height;
        
        //Drawing X-Axis Notches and Graduation Labels
        for (int i = 0; i <= iSubdivCount; i++)
        {
            if(i % m_iSecSubdiv)
            {
                //Handling "secondary notch" case
                dc.DrawLine(m_wxrctBoundingBox.x + i * wxptLabelPos.x,
                            m_wxrctBoundingBox.y + wxptLabelPos.y - 1,
                            m_wxrctBoundingBox.x + i * wxptLabelPos.x,
                            m_wxrctBoundingBox.y + wxptLabelPos.y - int(RS_SEC_NOTCHES));
            }
            else 
            {
                //Handling "main notch" case
                if((i != 0) && (i < iSubdivCount))
                {
                    //We should paint every notch EXCEPT first and last notches (included in the background paint!)
                    dc.DrawLine(m_wxrctBoundingBox.x + i * wxptLabelPos.x,
                                m_wxrctBoundingBox.y + wxptLabelPos.y - 1,
                                m_wxrctBoundingBox.x + i * wxptLabelPos.x,
                                m_wxrctBoundingBox.y + wxptLabelPos.y - int(RS_MAIN_NOTCHES));
                }
                
                //Printing Label
                wxsLabel.Printf(wxT("%d"), 
                                i*m_iScaleWidth/iSubdivCount - m_iSymmScale*m_iScaleWidth/2);
                
                if (i == iSubdivCount)
                {
                    //Last label should be printed on the left of the main notch!
                    wxSize labelsize;
                    labelsize = dc.GetTextExtent(wxsLabel);
                    dc.DrawText(wxsLabel, 
                                m_wxrctBoundingBox.x + i * wxptLabelPos.x - labelsize.GetWidth() - 2, 
                                m_wxrctBoundingBox.y + 2);
                }
                else
                {
                    dc.DrawText(wxsLabel,
                                m_wxrctBoundingBox.x + i * wxptLabelPos.x + 2, 
                                m_wxrctBoundingBox.y + 2);
                }
            }
        }        
    } 
    else // RO_VERTICAL
    {
        // Small shadows
        dc.DrawLine(m_wxrctBoundingBox.x + m_wxrctBoundingBox.width - 1, 
                    m_wxrctBoundingBox.y,
                    m_wxrctBoundingBox.x + m_wxrctBoundingBox.width - 1 ,
                    m_wxrctBoundingBox.y + m_wxrctBoundingBox.height - 1);
        dc.DrawPoint(m_wxrctBoundingBox.x, 
                     m_wxrctBoundingBox.y);
        dc.DrawPoint(m_wxrctBoundingBox.x, 
                     m_wxrctBoundingBox.y + m_wxrctBoundingBox.height - 1);        
        
        dc.SetPen(*wxBLACK_PEN);

        wxptLabelPos.x = m_wxrctBoundingBox.width - 2;
        wxptLabelPos.y = (m_wxrctBoundingBox.height + 5)/iSubdivCount;
        
        for (int i = 0; i <= iSubdivCount; i++)
        {
            if (i % m_iSecSubdiv)
            { //Handling "secondary notch" case
                dc.DrawLine( m_wxrctBoundingBox.x + wxptLabelPos.x - int(RS_SEC_NOTCHES),
                             m_wxrctBoundingBox.y + i * wxptLabelPos.y,
                             m_wxrctBoundingBox.x + wxptLabelPos.x,
                             m_wxrctBoundingBox.y + i * wxptLabelPos.y );
            }
            else 
            { //Handling "main notch" case
                if((i != 0) && (i < iSubdivCount))
                { //We should paint every notch EXCEPT first and last notches (included in the background paint!)
                    dc.DrawLine( m_wxrctBoundingBox.x + wxptLabelPos.x - int(RS_MAIN_NOTCHES),
                                 m_wxrctBoundingBox.y + i * wxptLabelPos.y,
                                 m_wxrctBoundingBox.x + wxptLabelPos.x,
                                 m_wxrctBoundingBox.y + i * wxptLabelPos.y );
                }
                
                //Printing Label
                wxsLabel.Printf(wxT("%d"),
                                (iSubdivCount - i)*m_iScaleWidth/iSubdivCount - m_iSymmScale*m_iScaleWidth/2);
                
                if (i == iSubdivCount)
                {
                    //Last label should be printed on top of the main notch!
                    wxSize labelsize;
                    labelsize = dc.GetTextExtent(wxsLabel);
                    dc.DrawText(wxsLabel, 
                                m_wxrctBoundingBox.x + 3, 
                                m_wxrctBoundingBox.y + i * wxptLabelPos.y - labelsize.GetHeight() - 1);
                }
                else
                {
                    dc.DrawText(wxsLabel, 
                                m_wxrctBoundingBox.x + 3, 
                                m_wxrctBoundingBox.y + i * wxptLabelPos.y + 2 );
                }
            }
        }
    }
}

void MyRuler::SetOrientation(const int orientation)
{ 
    m_iOrientation = orientation; 
    Init();
}

void MyRuler::SetFormat(const int format)
{ 
    m_iFormat = format; 
    Init(); 
}
                            
void MyRuler::SetSymmScale(const int scale)
{ 
    m_iSymmScale = scale; 
}
           
// 'ctors
MyRuler::MyRuler()
: MyGrob(),
  m_iOrientation(RO_HORIZONTAL),
  m_iFormat(RF_DEGREES),
  m_iSymmScale(RSS_ASYMM),
  m_iMainSubdiv(0), 
  m_iSecSubdiv(0), 
  m_iScaleWidth(0),                             
  m_pwxbmpBackground(0)
{
    Init();
}

MyRuler::MyRuler(const wxPoint pos, const wxSize size, const int orientation)
: MyGrob(pos, size),
  m_iOrientation(orientation),
  m_iFormat(RF_DEGREES),
  m_iSymmScale(RSS_ASYMM),
  m_iMainSubdiv(0), 
  m_iSecSubdiv(0), 
  m_iScaleWidth(0), 
  m_pwxbmpBackground(0)
{
    Init();
}

MyRuler::~MyRuler()
{
    if(m_pwxbmpBackground)
        delete m_pwxbmpBackground;
}

////////////////////////////////////////////////////////////////////////////////
// MyColorMap implementation
////////////////////////////////////////////////////////////////////////////////
bool MyColorMap::DoubleToRGB(unsigned char* rgb, 
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
                            
void MyColorMap::Draw(wxDC& dc)
{
    unsigned char rgb_value[3];
    wxColour brush_color;
    wxBrush brush;
    
    //Updating units label
    dc.SetFont(m_wxFont);
    //wxCoord w,h;   //wxCoord is typedef as an alias of "int".
    wxString units;
    switch(m_iMeasureUnit)
    {
        case MU_dB:   units.Printf(wxT("[dB]"));   break;
        case MU_Pa:   units.Printf(wxT("[Pa]"));   break;
        case MU_Sqrt: units.Printf(wxT("[SQRT]")); break;
        case MU_Cbrt: units.Printf(wxT("[CBRT]")); break;
        default:      units.Printf(wxT("[dB]"));
    }
    //dc_units.GetSize(&w,&h); // ???????
    wxSize labelsize;
    labelsize = dc.GetTextExtent(units);
    dc.DrawText(units, 
                m_wxrctBoundingBox.x + (m_wxrctBoundingBox.width - labelsize.GetWidth())/2 + 5,
                m_wxrctBoundingBox.y + 3);
        
    //Drawing colors!
    int y, 
        iSmallRectHeight = CBS_SMALL_RECT_HEIGHT; 

    wxRect wxrctColorBar(m_wxrctBoundingBox.x + 5, 
                         m_wxrctBoundingBox.y + labelsize.GetHeight() + 10 + 3, 
                         CBS_WIDTH, 
                         CBS_HEIGHT);
    
    dc.SetPen(*wxTRANSPARENT_PEN); //Doing this small rectangles borders will NOT be shown!
    for(int i = 0; i < (wxrctColorBar.height/iSmallRectHeight); i++)
    {
        DoubleToRGB(rgb_value,
                    double((wxrctColorBar.height/iSmallRectHeight - 1) - i),
                    0,
                    (wxrctColorBar.height/iSmallRectHeight - 1),
                    m_iStyle);
        
        brush_color.Set(rgb_value[0], rgb_value[1], rgb_value[2]);
        brush.SetColour(brush_color);
        dc.SetBrush(brush); //Setting current small rectangle bgnd color.
        y = i * iSmallRectHeight; // +10
        dc.DrawRectangle(wxrctColorBar.x, 
                         wxrctColorBar.y + y, 
                         wxrctColorBar.width, 
                         iSmallRectHeight);
    }
    
    //Drawing ColorBar total border
    dc.SetBrush(*wxTRANSPARENT_BRUSH); //No bgnd color
    dc.SetPen(*wxBLACK_PEN);
    dc.DrawRectangle(wxrctColorBar);
    
    //Drawing black notches
    int length          = 5;    //notches length, in px
    int iColorBarSubdiv = 8;    //number of notches (NOTE that number of notches should 
                                // verify ColorBarHeight % ColorBarSubdiv = 0)
    for(int i = 1; i < iColorBarSubdiv; i++)
    {
        y = i * (wxrctColorBar.height/iColorBarSubdiv); // + 10
        dc.DrawLine(wxrctColorBar.x, 
                    wxrctColorBar.y + y, 
                    wxrctColorBar.x + length, 
                    wxrctColorBar.y + y);
        dc.DrawLine(wxrctColorBar.x + wxrctColorBar.width - length,
                    wxrctColorBar.y + y,
                    wxrctColorBar.x + wxrctColorBar.width,
                    wxrctColorBar.y + y);
    }
    
    //Plotting labels
    wxString scale_label;
    double value, min, max;
    dc.SetFont(m_wxFont);
    
    //Getting correct min and max levels, according to the selected Scale Unit and Octave Band.
    max = FromdB(m_dbMax, MeasureUnit(m_iMeasureUnit));
    min = FromdB(m_dbMin, MeasureUnit(m_iMeasureUnit));
    
    int w, h;
    for(int i = 0; i < (iColorBarSubdiv + 1); i++)
    {
        value = max - ((max - min)/iColorBarSubdiv)*i;
        if (m_iMeasureUnit == MU_dB)
            scale_label.Printf(wxT("%.1f"), value);  //For dB scale we DON'T use scientific notation.
        else
            scale_label.Printf(wxT("%.1E"), value);
        
        dc.GetTextExtent(scale_label, &w, &h);
        dc.DrawText(scale_label, 
                    wxrctColorBar.GetRight() + 3, 
                    wxrctColorBar.y - h/2 + i*(wxrctColorBar.height/iColorBarSubdiv)); // + 10
    }
    
}

// 'ctors
MyColorMap::MyColorMap()
: MyGrob(),
  m_iMeasureUnit(MU_dB),
  m_iStyle(CMS_JET),
  m_dbMax(120.0),
  m_dbMin(0.0)
{}

MyColorMap::MyColorMap(const wxPoint pos, const wxSize size)
: MyGrob(pos, size),
  m_iMeasureUnit(MU_dB),
  m_iStyle(CMS_JET),
  m_dbMax(120.0),
  m_dbMin(0.0)
{}

MyColorMap::~MyColorMap()
{}

////////////////////////////////////////////////////////////////////////////////
// MyMap events
////////////////////////////////////////////////////////////////////////////////
const wxEventType wxEVT_POINTER_POSITION = wxNewEventType();

////////////////////////////////////////////////////////////////////////////////
// MyMap
////////////////////////////////////////////////////////////////////////////////
void MyMap::SetImageAlpha(wxImage* img, const int alpha_perc, const bool is_colormap)
{
    double min = 0.0;
    if (is_colormap)
    {
        //Retrieving min SPL threshold, converted in the current scale unit. 
        // Pixels with associated levels < threshold will be FULLY TRANSPARENT!
        min = ::FromdB( m_pMaa->GetMinSPLThreshold(), MeasureUnit(m_iCurrentUnit) );
    }
    
    if (!(img->HasAlpha())) 
        img->SetAlpha();  //Alpha channel Init, if necessary.
    
    for (int y = 0; y < img->GetHeight(); y++)
    {
        for (int x = 0; x < img->GetWidth(); x++)
        {
            if( (is_colormap) && (m_aadLevelsMap[x][y] < min)) 
            { 
                // If Level < min SPL threshold -->> full   transparency!
                img->SetAlpha(x, y, 0);   
            }
            else 
            { 
                //Scaling [0;100] % alpha level to fit [0;255] range.
                img->SetAlpha(x, y, (unsigned char)((255/100)*alpha_perc));   
            }
        }
    }
}

void MyMap::DrawCrossOnImage(wxImage* img, const int x, const int y, const wxColour* color)
{
    int size = 2;
    for (int k = -size; k <= size; k++)
    {
         if(m_wxrctImageBox.Contains(x+k, y+k)) 
         {
              img->SetRGB(x+k, y+k, color->Red(), color->Green(), color->Blue());
              img->SetAlpha(x+k, y+k,(unsigned char)255);   // FULLY OPAQUE
         }
         if(m_wxrctImageBox.Contains(x+k, y-k))
         {
             img->SetRGB(x+k, y-k, color->Red(), color->Green(), color->Blue());
             img->SetAlpha(x+k, y-k, (unsigned char)255);   // FULLY OPAQUE
         }
    }    
}

void MyMap::InitLevelsMap()
{
#ifdef __WXDEBUG__
    m_benchTime.Start();    
#endif
    
    int i,k,l;
    
    //Levels Map matrix init.
    if(!m_aadLevelsMap)
    {
        m_aadLevelsMap = new double* [m_wxrctImageBox.width];
        for (int l = 0; l < m_wxrctImageBox.width; l++) 
            m_aadLevelsMap[l] = new double [m_wxrctImageBox.height];
    }
    
    int j = 0; //Used to remember the previous triangle where a point was located, used to speed-up point location!
    TriangularMesh* tmCurrentTri;
    
    m_pMaa->ClearInterpolCoeffs();  //Clearing A,B,C,det for each triangle.
    
    for (i = 0; i < m_wxrctImageBox.width; i++)
    {
        for (k = 0; k < m_wxrctImageBox.height; k++)
        {
            //Locating the position of pixel (i,k) inside the triangulation
            for (l = 0; l < m_pMaa->GetNumOfMeshes(); l++)
            {
                tmCurrentTri = NULL;
                if (m_pMaa->InOrOutTriangle(i,k,j) >= 0) //InOrOutTriangle returns -1 if point (i,k) is outside, 0 in it's onside and +1 if it's inside triangle number j.
                {
                    tmCurrentTri = m_pMaa->GetTriangle(j);
                    break; //Location completed!
                }
                else
                {
                    j++;
                    if (j >= m_pMaa->GetNumOfMeshes()) 
                        j = 0; //Re-init.
                }
            }
            
            if (tmCurrentTri != NULL)
            {
                if (!tmCurrentTri->AreCoeffsSet())  //If coeffs aren't set,
                {                                //we should set levels at triangle vertexes before calling GetInterpolatedValue().
                    double levels[3];
                    
                    for (int vert = 0; vert < 3; vert++)
                    {
                        //Retrieving level @ each vertex inside the choosen 
                        //ch = mic# at the choosen vertex, band = wxRadioButton choice!
                        levels[vert] = m_pMaa->GetResult(tmCurrentTri->GetMicAtVertex(vert),
                                                         m_iCurrentBand);
                        //Scaling to the correct unit
                        levels[vert] = ::FromdB(levels[vert], MeasureUnit(m_iCurrentUnit)); 
                    }
                    //Setting levels will automatically compute interpolation coeffs.
                    tmCurrentTri->SetLevelsAtVertexes(levels); 
                }
                m_aadLevelsMap[i][k] = tmCurrentTri->GetInterpolatedValue(i,k);
            }
        }
    }
#ifdef __WXDEBUG__
    m_benchTime.Stop();
    printf("MyMap::InitLevelsMap timing: %.1f ms\n", m_benchTime.GetElapsedTime());
#endif    
}

void MyMap::InitColorMap()
{
#ifdef __WXDEBUG__
    m_benchTime.Start();
#endif    
    
    if(!m_pwximgColorMap)    
        m_pwximgColorMap = new wxImage(m_wxrctImageBox.width, m_wxrctImageBox.height); //New image, all pixels are inited to black.
    
    //Retrieving min and max levels for the current band, scaled to the correct unit.
    double min = ::FromdB(m_dbMin, MeasureUnit(m_iCurrentUnit));  
    double max = ::FromdB(m_dbMax, MeasureUnit(m_iCurrentUnit));  
    
#ifdef __AUDEBUG__
    printf("Gui::InitColorMap(): min = %f ; max = %f ; scale_unit = %d \n", min, max, m_iCurrentUnit);
#endif
    
    unsigned char rgb[3];
    
    for (int i = 0; i < m_wxrctImageBox.width; i++)
    {
        for (int k = 0; k < m_wxrctImageBox.height; k++)
        {
            MyColorMap::DoubleToRGB(rgb, m_aadLevelsMap[i][k], min, max, m_pColorMap->GetStyle());
            m_pwximgColorMap->SetRGB(i, k, rgb[0], rgb[1], rgb[2]);
        }
    } 
#ifdef __WXDEBUG__
    m_benchTime.Stop();
    printf("MyMap::InitColorMap timing: %.1f ms\n", m_benchTime.GetElapsedTime());
#endif    
}

void MyMap::InitVirtMikesMap()
{
    m_pwximgVirtMikesMap = new wxImage(m_wxrctImageBox.width, m_wxrctImageBox.height);
    
    //Initializing it as a FULLY transparent image.
    SetImageAlpha(m_pwximgVirtMikesMap, 0);
    int x,y;
    for (int j = 0; j < m_pMaa->GetNumOfMeshes(); j++)
    {
        for (int k = 0; k < 3; k++)
        {
#ifdef __AUDEBUG__
            printf("MicArrayAnalyzerDlg::Init: Drawing vertex [%d] of triangle [%d]\n",k,j);
            fflush(stdout);
#endif
            x = (m_pMaa->GetTriangle(j))->GetVertexX(k);
            y = (m_pMaa->GetTriangle(j))->GetVertexY(k);
            DrawCrossOnImage(m_pwximgVirtMikesMap, x, y, wxWHITE); //Choosen color = WHITE
        }
    }
}

#ifdef __WXDEBUG__    
void MyMap::InitDebugMap()
{   
    m_pwximgDebugMap = new wxImage(m_wxrctImageBox.width, m_wxrctImageBox.height);

    //Initalizing as a FULLY transparent image.
    SetImageAlpha(m_pwximgDebugMap, 0);
    
}

void MyMap::MarkDebugMap(wxPoint& p)
{
    if(!m_pwximgDebugMap)
        InitDebugMap();
    
    // ULTRA DEBUGGING FOR TRIANGLE LOCATION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    TriangularMesh* tmCurrentTri;
    for (int l = 0; l < m_pMaa->GetNumOfMeshes(); l++)
    {
        tmCurrentTri = NULL;
        printf("LeftDClick: Checking triangle [%d]...\n",l);
        fflush(stdout);
        //InOrOutTriangle returns -1 if point (i,k) is outside, 0 in it's onside 
        // and +1 if it's inside triangle number j.
        if(m_pMaa->InOrOutTriangle(int(p.x),int(p.y),l) >= 0) 
        {
            printf("LeftDClick: point (%d,%d) found inside triangle [%d]\n",int(p.x),int(p.y),l);
            fflush(stdout);
            tmCurrentTri = m_pMaa->GetTriangle(l);
            break; //Location completed!
        }
    }
    if ((tmCurrentTri != NULL) && (tmCurrentTri->AreCoeffsSet()))
    {
        int x, y;
        for (int k = 0; k < 3; k++)
        {
            printf("LeftDClick: Drawing cross on vertes [%d].\n",k);
            fflush(stdout);
            x = tmCurrentTri->GetVertexX(k);
            y = tmCurrentTri->GetVertexY(k);
            if(m_wxrctImageBox.Contains(x,y)) 
                DrawCrossOnImage(m_pwximgDebugMap, x, y,wxRED);
        }
    }
    else
    {
        printf("LeftDClick: triangle NOT FOUND or interpolation coeffs not set.\n");
        fflush(stdout);
    }
    
    if(m_wxrctImageBox.Contains(p.x, p.y))
        DrawCrossOnImage(m_pwximgDebugMap, int(p.x), int(p.y), wxWHITE);
}
#endif

void MyMap::UpdateMap(wxDC& dc, wxSize size)
{
#ifdef __WXMSW__
    dc.SetBrush(wxBrush(GetBackgroundColour()));
    dc.SetPen(*wxTRANSPARENT_PEN);
    wxRect canvas(0, 0, size.GetWidth(), size.GetHeight());
    dc.DrawRectangle(canvas);
#endif

    m_pHorzRuler->Draw(dc);
    m_pVertRuler->Draw(dc);

    m_pColorMap->Draw(dc);
    
    //Draw Background Image (bottom layer)
    dc.DrawBitmap(m_pMaa->GetBGNDBmp(), 0, 0, false); //false = ignore transparency -->> fully opaque.
    
    //Draw ColorMap (mid layer)
//    if(!m_aadLevelsMap)
        InitLevelsMap();
    
//    if(!m_pwximgColorMap) 
        InitColorMap();
   
    //Applying transparency, respecting minimum SPL threshold.
    SetImageAlpha(m_pwximgColorMap, 100 - m_iTransparency, true);
    //CAN'T ignore transparency here! -->> true
    dc.DrawBitmap(*m_pwximgColorMap, 0, 0, true);                                 
    
    //Draw Mic Positions and/or Delaunay Triangles (if requested as a special option)
    if(m_bShowVirtMikesPos) 
    {
        if(!m_pwximgVirtMikesMap)
            InitVirtMikesMap();
            
        dc.DrawBitmap(*m_pwximgVirtMikesMap, 0, 0, true);
    }
    
    //Draw WatchPoints and Labels (top layer) NOW USED AS A DEBUG LAYER!
#ifdef __WXDEBUG__
    if(m_bShowDebugMap && m_pwximgDebugMap)         
        dc.DrawBitmap(*m_pwximgDebugMap, 0, 0, true); 
#endif
    
}

void MyMap::OnPaint(wxPaintEvent& evt)
{
    const wxSize sz = GetClientSize();
    wxAutoBufferedPaintDC adc(this);
    UpdateMap(adc, sz);
}

void MyMap::OnMouseOverDisplay(wxMouseEvent& evt)
{
    // process mouse position
    int x = evt.GetX(), y = evt.GetY();
    
    if(!m_wxrctImageBox.Contains(x, y))
    {
        m_MouseCoord.x = -1.0;
        m_MouseCoord.y = -1.0;
        SetCursor(wxCursor(*wxSTANDARD_CURSOR));
        return;
    }

    SetCursor(wxCursor(*wxCROSS_CURSOR));

    switch(m_pHorzRuler->GetFormat())
    {
        case MyRuler::RF_PIXELS:
            m_MouseCoord.x = double(x);
            m_MouseCoord.y = double(m_wxrctImageBox.height - y);
            break;
            
        case MyRuler::RF_DEGREES:
            m_MouseCoord.x = double(X_RES_DEG)*(x / double(m_wxrctImageBox.width));
            m_MouseCoord.y = double(Y_RES_DEG)*((m_wxrctImageBox.height - y) / double(m_wxrctImageBox.height));
            break;
    }
    m_MouseCoord.z      = m_aadLevelsMap[x][y];
    m_MouseCoord.format = m_pHorzRuler->GetFormat();
    m_MouseCoord.unit   = GetMeasureUnit();
    
    // send a 'position updated' message
    wxCommandEvent event(wxEVT_POINTER_POSITION, GetId());
    event.SetClientData((void *)&m_MouseCoord);
    event.SetEventObject(this);
    ProcessEvent(event);
}

#ifdef __WXDEBUG__
void MyMap::OnLeftDClick(wxMouseEvent& evt)
{
    m_bShowDebugMap = !m_bShowDebugMap;
    if(m_bShowDebugMap)
    {
        wxPoint p(evt.GetX(), evt.GetY());
        MarkDebugMap(p);
        Refresh();
    }
    else 
    {
        delete m_pwximgDebugMap;
    }
}
#endif

void MyMap::OnTimer(wxTimerEvent& evt)
{
    if(m_MouseCoord.x < 0.0 && m_MouseCoord.y < 0.0)
    {
        wxCommandEvent event(wxEVT_POINTER_POSITION, GetId());
        event.SetClientData((void *)&m_MouseCoord);
        event.SetEventObject(this);
        ProcessEvent(event);
    }
}

wxSize MyMap::DoGetBestSize() const
{
    // quite ugly, but...
    wxSize sz(MAP_WIDTH  + MM_BORDER + MM_V_RULER_WIDTH  + MM_BORDER + MM_COLOR_MAP_WIDTH + MM_BORDER, 
              MAP_HEIGHT + MM_BORDER + MM_H_RULER_HEIGHT + MM_BORDER);
    return sz;
}


void MyMap::Init()
{
    // It can be useful sometime...
}

void MyMap::DestroyMaps()
{
//   if(m_aadLevelsMap)
//    {
//        for (int i = 0; i < X_RES; i++) 
//            delete m_aadLevelsMap[i];
//    
//        delete [] m_aadLevelsMap;
//        m_aadLevelsMap = 0;
//    }
//    
//    if(m_pwximgColorMap)
//    {
//        delete m_pwximgColorMap;
//        m_pwximgColorMap = 0;
//    }
    
}

bool MyMap::CopyToClipboard()
{
    wxSize sz = GetClientSize();
    
    wxBitmap bmp(sz.GetWidth(), sz.GetHeight());
    wxMemoryDC dc(bmp);
    
    if(!dc.IsOk())
    {
        ::wxMessageBox(wxT("Invalid DC"),
                       wxT("Error"),
                       wxOK | wxICON_ERROR);
        return false;
    }
    
    UpdateMap(dc, sz);
    wxClipboardLocker locker;
    if(!locker)
    {
        ::wxMessageBox(wxT("Can't lock clipboard"),
                       wxT("Error"),
                       wxOK | wxICON_ERROR);
        return false;
    }
    
    if(!wxTheClipboard->AddData(new wxBitmapDataObject(bmp)))
        return false;
    
    return true;
}

void MyMap::SetBand(const int band)
{
    DestroyMaps();
    m_iCurrentBand = band; 
}

void MyMap::SetMeasureUnit(const int mu)            
{
    DestroyMaps();
    m_iCurrentUnit = int(mu);
    m_pColorMap->SetMeasureUnit(m_iCurrentUnit); 
}

void MyMap::SetStyle(const int style)         
{ 
    DestroyMaps();
    m_pColorMap->SetStyle(style); 
}

void MyMap::SetMaxMin(const double max, const double min)
{
    DestroyMaps();
    m_dbMin = min; 
    m_dbMax = max;
    m_pColorMap->SetMaxMin(max, min); 
}

void MyMap::SetTransparency(const int transparency)  
{ 
    DestroyMaps();
    m_iTransparency = transparency; 
}

void MyMap::GetPointerCoords(double& x, double& y, double& z) const
{
    x = m_MouseCoord.x;
    y = m_MouseCoord.y;
    z = m_MouseCoord.z;
}

// 'ctors
MyMap::MyMap(wxWindow* parent,
             wxWindowID id,
             const wxPoint& pos,
             const wxSize& size,
             const long style)
: wxControl(parent, id, pos, size, style),
  m_aadLevelsMap(0),
  m_pwximgColorMap(0),
  m_pwximgVirtMikesMap(0),
#ifdef __WXDEBUG__    
  m_pwximgDebugMap(0),
  m_bShowDebugMap(false),
  m_benchTime(),
#endif
  m_wxrctImageBox(0, 0, MAP_WIDTH, MAP_HEIGHT), // X_RES, Y_RES
  m_iCurrentUnit(MU_dB),
  m_dbMin(0.0),
  m_dbMax(120.0),
  m_iCurrentBand(0), // ???
  m_bShowVirtMikesPos(false),
  m_iTransparency(50),
  m_pHorzRuler(0),
  m_pVertRuler(0),
  m_pColorMap(0),
  m_MouseCoord(),
  m_pMaa(0),
  m_Timer(this, ID_MM_TIMER)
{
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);

    m_pHorzRuler = new MyRuler(wxPoint(0, MAP_HEIGHT + MM_BORDER), 
                               wxSize(MAP_WIDTH + MM_BORDER,  MM_H_RULER_HEIGHT), 
                               MyRuler::RO_HORIZONTAL);

    m_pVertRuler = new MyRuler(wxPoint(MAP_WIDTH + MM_BORDER, 0), 
                               wxSize(MM_V_RULER_WIDTH, MAP_HEIGHT + MM_BORDER), 
                               MyRuler::RO_VERTICAL);

    m_pColorMap  = new MyColorMap(wxPoint(MAP_WIDTH + MM_BORDER + MM_V_RULER_WIDTH + MM_BORDER, 0), 
                                  wxSize(MM_COLOR_MAP_WIDTH, MM_COLOR_MAP_HEIGHT));    
    Init();
    
    m_Timer.Start(2000);

    // Events connections
    Connect(wxEVT_PAINT,       wxPaintEventHandler(MyMap::OnPaint),            NULL, this);
    Connect(wxEVT_MOTION,      wxMouseEventHandler(MyMap::OnMouseOverDisplay), NULL, this);
#ifdef __WXDEBUG__
    Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(MyMap::OnLeftDClick),       NULL, this);
#endif
    Connect(wxEVT_TIMER,       wxTimerEventHandler(MyMap::OnTimer),            NULL, this);
}

MyMap::~MyMap()
{
    DestroyMaps();
    
    if(m_pwximgVirtMikesMap)
        delete m_pwximgVirtMikesMap;
    
    if(m_pHorzRuler)
        delete m_pHorzRuler;
    if(m_pVertRuler)
        delete m_pVertRuler;
    if(m_pColorMap)
        delete m_pColorMap;
    
    Disconnect(wxEVT_PAINT,       wxPaintEventHandler(MyMap::OnPaint),            NULL, this);
    Disconnect(wxEVT_MOTION,      wxMouseEventHandler(MyMap::OnMouseOverDisplay), NULL, this);
#ifdef __WXDEBUG__
    Disconnect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(MyMap::OnLeftDClick),       NULL, this);
#endif
    Disconnect(wxEVT_TIMER,       wxTimerEventHandler(MyMap::OnTimer),            NULL, this);
    
}

