///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep 12 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __dialogs__
#define __dialogs__

#include <wx/intl.h>

#include "map.h"
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/radiobox.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/spinctrl.h>
#include <wx/statbox.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/dialog.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/statline.h>
#include <wx/listctrl.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MyModuleDlg
///////////////////////////////////////////////////////////////////////////////
class MyModuleDlg : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			ID_MAP = 1000,
		};
		
		MyMap* m_pMap;
		wxPanel* m_wxpButtonsPanel;
		wxButton* m_wxbOk;
		wxButton* m_wxbCopyResultsToClipboard;
		wxButton* m_wxbHelp;
		wxPanel* m_wxpBandSelection;
		wxRadioBox* m_wxrbBandSelection;
		wxPanel* m_wxpColorMapOptions;
		wxStaticText* m_staticText63;
		wxChoice* m_wxcScaleStyle;
		
		wxStaticText* m_staticText64;
		wxSpinCtrl* m_wxscTransparency;
		wxStaticText* m_staticText68;
		wxStaticText* m_staticText65;
		wxChoice* m_wxcScaleUnit;
		
		wxStaticText* m_staticText67;
		wxChoice* m_wxcInterpolationMethod;
		wxPanel* m_wxpSpecialOptions;
		wxCheckBox* m_wxcbShowVirtMikes;
		wxCheckBox* m_wxcbSeparateBandAutoscale;
		
		wxPanel* m_wxpMousePointerData;
		wxTextCtrl* m_wxtcXPosLabel;
		wxTextCtrl* m_wxtcXPos;
		wxTextCtrl* m_wxtcXPosUnit;
		wxTextCtrl* m_wxtcYPosLabel;
		wxTextCtrl* m_wxtcYPos;
		wxTextCtrl* m_wxtcYPosUnit;
		wxTextCtrl* m_wxtcLevelLabel;
		wxTextCtrl* m_wxtcLevel;
		wxTextCtrl* m_wxtcLevelUnit;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCopyResultsToClipboard( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnHelp( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBandAnalysis( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnScaleStyle( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTransparency( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnScaleUnit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnShowVirtMikesPos( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSeparateBandAutoscale( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MyModuleDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Microphone Array Analyzer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~MyModuleDlg();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class MyModuleConfDlg
///////////////////////////////////////////////////////////////////////////////
class MyModuleConfDlg : public wxDialog 
{
	private:
	
	protected:
		wxPanel* m_panel5;
		wxStaticText* m_staticText1;
		wxTextCtrl* m_wxtcBgndImagePath;
		wxButton* m_wxbBrowseBgndImage;
		wxPanel* m_panel8;
		wxStaticText* m_staticText63;
		wxTextCtrl* m_wxtcXMLConfigFilePath;
		wxButton* m_wxbBrowseXmlConfigFile;
		wxPanel* m_wxpTable;
		
		wxBoxSizer* m_wxbsHeadersCheck;
		wxStaticText* m_wxstHeadersCheckLabel;
		wxStaticText* m_wxstHeadersCheck;
		wxStaticText* m_wxstMicNameLabel;
		wxStaticText* m_wxstMicName;
		wxStaticText* m_wxstManufacturerLabel;
		wxStaticText* m_wxstManufacturer;
		wxStaticText* m_wxstArrayTypeLabel;
		wxStaticText* m_wxstArrayType;
		
		wxBoxSizer* m_wxbsXML;
		
		wxStaticText* m_wxstXMLLabel;
		
		wxBoxSizer* m_wxbsSpacer;
		
		wxBoxSizer* m_wxbsWAV;
		
		wxStaticText* m_wxstWAVLabel;
		
		
		wxStaticText* m_wxstDeconvIRsLengthLabel;
		wxStaticText* m_wxstNumOfCapsulesLabel;
		wxStaticText* m_wxstXMLLength;
		wxStaticText* m_wxstXMLCapsules;
		wxStaticBitmap* m_wxsbLengthCheck;
		wxStaticText* m_wxstWAVLength;
		wxStaticText* m_wxstTotalLengthLabel;
		wxStaticText* m_wxstNumOfVirtMikesLabel;
		wxStaticText* m_wxstXMLVirtual;
		wxStaticBitmap* m_wxsbWAVChannelsCheck;
		wxStaticText* m_wxstWAVChannels;
		wxStaticText* m_wxstWAVChannelsLabel;
		
		wxStaticText* m_wxstXMLLabel2;
		
		wxStaticText* m_wxstProjectLabel;
		
		wxStaticText* m_wxstNumOfCapsulesLabel2;
		wxStaticText* m_wxstXMLCapsules2;
		wxStaticBitmap* m_wxsbProjChannelsCheck;
		wxStaticText* m_wxstProjChannels;
		wxStaticText* m_wxstProjChannelsLabel;
		
		wxStaticText* m_wxstWAVLabel2;
		
		wxStaticText* m_wxstProjectLabel2;
		
		wxStaticText* m_wxstSamplingRateLabel;
		wxStaticText* m_wxstWAVfsample;
		wxStaticBitmap* m_wxsbRateCheck;
		wxStaticText* m_wxstProjRate;
		wxStaticText* m_wxstProjRateLabel;
		wxStaticText* m_wxstBitDepthLabel;
		wxStaticText* m_wxstWAVFormat;
		wxStaticBitmap* m_wxsbSampleFormatCheck;
		wxStaticText* m_wxstProjSampleFormat;
		wxStaticText* m_wxstProjSampleFormatLabel;
		wxPanel* m_panel18;
		wxStaticText* m_staticText42;
		wxTextCtrl* m_wxtcFS;
		wxStaticText* m_staticText43;
		wxStaticText* m_staticText421;
		wxTextCtrl* m_wxtcMinSPL;
		wxStaticText* m_staticText431;
		wxStaticLine* m_staticline1;
		wxPanel* m_pButtonsPanel;
		wxButton* m_wxbHelp;
		
		wxButton* m_wxbCancel;
		wxButton* m_wxbOk;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnBrowseBGND( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBrowseXML( wxCommandEvent& event ) { event.Skip(); }
		virtual void FSOnChar( wxKeyEvent& event ) { event.Skip(); }
		virtual void FSKillFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void FSOnFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void MinSPLOnChar( wxKeyEvent& event ) { event.Skip(); }
		virtual void MinSPLKillFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void MinSPLOnFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnHelp( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MyModuleConfDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Plug-in name - Configure"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~MyModuleConfDlg();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class MyEditWatchpointsDlg
///////////////////////////////////////////////////////////////////////////////
class MyEditWatchpointsDlg : public wxDialog 
{
	private:
	
	protected:
		wxListCtrl* m_wxlcWatchpoints;
		wxButton* m_wxbOk;
		wxButton* m_wxbCancel;
		
		wxButton* m_wxbRemove;
		wxButton* m_wxbEditLabel;
	
	public:
		
		MyEditWatchpointsDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Edit Watchpoints..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~MyEditWatchpointsDlg();
	
};

#endif //__dialogs__
