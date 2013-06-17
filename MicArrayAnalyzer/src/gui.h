/**********************************************************************
 
 Audacity: A Digital Audio Editor
 
 Microphone Array Analyzer
 
 gui.h
 
 Luca Novarini
 
 **********************************************************************/


#ifndef __MICARRAYANALYZER_GUI_H__
#define __MICARRAYANALYZER_GUI_H__

#include <wx/wx.h>

#include "micarrayanalyzer.h"
#include "dialogs.h"
#include "trprop.h"
#include "module.h"

// Some consts to define Main Dialog aspect
const int DEFAULT_RULER_FORMAT = 0;          //0 = deg, 1 = pixel
/*const int RULERS_FONT_SIZE = 7;              
 const wxCoord RULERS_MAIN_NOTCHES = 10;      //Length of main notches
 const wxCoord RULERS_SEC_NOTCHES = 5;        //Length of secondary notches
 const int RULERS_MAIN_DEG_XSUBDIV = 8;        //One subdivision every 45 degrees (considering X_RES_DEG = 360)
 const int RULERS_SEC_DEG_XSUBDIV = 4;         //Four secondary notches inside each 45 degrees interval.
 const int RULERS_MAIN_PX_XSUBDIV = 8;         //One subdivision every 120 pixels.
 const int RULERS_SEC_PX_XSUBDIV = 4;          //Four secondary notches inside each 120 px interval.
 const int RULERS_MAIN_DEG_YSUBDIV = 4;        //Same here, but for Y-Axis Ruler!
 const int RULERS_SEC_DEG_YSUBDIV = 4;         
 const int RULERS_MAIN_PX_YSUBDIV = 4;         
 const int RULERS_SEC_PX_YSUBDIV = 4;    
 */
//----------------------------------------------------
// Module Configuration Dialog
//----------------------------------------------------
class MicArrayAnalyzerConfDlg : public MyModuleConfDlg
	{
		MicArrayAnalyzer* mMAA;
		wxStaticBitmap* wxsbHeadersCheck;
		bool bHeaders, bBgndImage, bLength, bVirtMikes, bProjChannels, bProjRate, bProjBits;
	protected:
		void OnHelp( wxCommandEvent& event );
		void OnOk( wxCommandEvent& event );
		void OnCancel( wxCommandEvent& event );
		void OnPaint(wxPaintEvent & event);
		void Render(wxDC& dc);
		void SetHeadersCheckIcon(const wxChar* icon);
		void RePaint();
		void EnableTable();
		void OnBrowseXML(wxCommandEvent& event);
		void OnBrowseBGND(wxCommandEvent& event);
		void IsAllOKCheck();
		void MinSPLOnFocus(wxFocusEvent& event);
		void MinSPLKillFocus(wxFocusEvent& event);
		void MinSPLOnChar(wxKeyEvent& event);
		void FSOnFocus(wxFocusEvent& event);
		void FSKillFocus(wxFocusEvent& event);
		void FSOnChar(wxKeyEvent& event);
		double ReadAndForceDoubleTextCtrl(wxTextCtrl *txt, const double def_val);
	public:
		// Constructor / Destructor
		MicArrayAnalyzerConfDlg(wxWindow* parent, MicArrayAnalyzer* maa);
		~MicArrayAnalyzerConfDlg();
	};


//----------------------------------------------------------------------------
// Showing Result Dialog
//----------------------------------------------------------------------------
class MicArrayAnalyzerDlg : public MyModuleDlg
	{
		MicArrayAnalyzer* mMAA;
		
		int m_iCurrRulersFormat; // used for toggling...
		
		bool  updating;
		float frameRateCoeff;
		wxTimer	m_timer;
		enum { ID_MM_TIMER = 2013 };

		
	protected:
		void OnOk(wxCommandEvent& event);
		void OnCopyResultsToClipboard(wxCommandEvent& event);
		//      void OnChangeRulersFormat(wxCommandEvent& event);
		void OnSeparateBandAutoscale(wxCommandEvent& event);
		//      void OnEditWatchpoints(wxCommandEvent& event);
		void OnShowVirtMikesPos(wxCommandEvent& event);
		void OnScaleStyle(wxCommandEvent& event);
		void OnScaleUnit(wxCommandEvent& event);
		void OnTransparency(wxSpinEvent& event);
		void OnBandAnalysis(wxCommandEvent& event);
		void OnMouseOverMap(wxCommandEvent& event);
		//ellerre
		void OnSpinCurFrame(wxCommandEvent& event) ;
		void OnSpinCtrlTxt(wxCommandEvent& event) ;
		void OnSliderScroll( wxScrollEvent& event ) ;
		void OnSTOPBtn(wxCommandEvent& event) ;
		void OnPAUSEBtn(wxCommandEvent& event) ;
		void OnPLAYBtn(wxCommandEvent& event) ;
		void OnChoiceFrameRate(wxCommandEvent& event) ;
		void UpdateFrameControls();
		void OnTimer(wxTimerEvent& event); 

	public:
		MicArrayAnalyzerDlg(wxWindow* parent, MicArrayAnalyzer* maa);
		~MicArrayAnalyzerDlg();
	};



#endif // __MICARRAYANALYZER_GUI_H__

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
