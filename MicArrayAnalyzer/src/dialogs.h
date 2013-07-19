///////////////////////////////////////////////////////////////////////////// C++ code generated with wxFormBuilder (version Apr 16 2008)// http://www.wxformbuilder.org///// PLEASE DO "NOT" EDIT THIS FILE!///////////////////////////////////////////////////////////////////////////#ifndef __dialogs__#define __dialogs__#include "map.h"#include <wx/gdicmn.h>#include <wx/font.h>#include <wx/colour.h>#include <wx/settings.h>#include <wx/string.h>#include <wx/sizer.h>#include <wx/scrolwin.h>#include <wx/button.h>#include <wx/panel.h>#include <wx/radiobox.h>#include <wx/choice.h>#include <wx/stattext.h>#include <wx/statline.h>#include <wx/textctrl.h>#include <wx/slider.h>#include <wx/spinctrl.h>#include <wx/statbox.h>#include <wx/checkbox.h>#include <wx/dialog.h>#include <wx/bitmap.h>#include <wx/image.h>#include <wx/icon.h>#include <wx/statbmp.h>#include <wx/listctrl.h>///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Class MyModuleDlg///////////////////////////////////////////////////////////////////////////////class MyModuleDlg : public wxDialog {	private:		protected:		enum		{			ID_MAP = 1000,		};				wxScrolledWindow* m_wxswPanelMap;		MyMap* m_pMap;		wxPanel* m_wxButtonsPanel;		wxButton* m_wxbOk;		wxButton* m_wxbCopyResultsToClipboard;		wxButton* m_wxbHelp;		wxPanel* m_wxpBandSelection;		wxRadioBox* m_wxrbBandSelection;		wxChoice* m_choice1;		wxStaticText* m_staticText1;		wxStaticLine* m_staticline6;				wxButton* m_buttonStop;		wxButton* m_buttonPause;		wxButton* m_buttonPlay;		wxTextCtrl* m_textCtrlCurTime;		wxSlider* m_sliderVideoFrame;		wxSpinCtrl* m_spinCtrlCurFrame;		wxPanel* m_wxpColorMapOptions;		wxStaticText* m_staticText2;		wxChoice* m_wxcScaleStyle;				wxStaticText* m_staticText3;		wxSpinCtrl* m_wxscTransparency;		wxStaticText* m_staticText4;		wxStaticText* m_staticText5;		wxChoice* m_wxcScaleUnit;				wxStaticText* m_staticText6;		wxChoice* m_wxcInterpolationMethod;		wxPanel* m_wxpSpecialOptions;		wxCheckBox* m_wxcbShowVirtMikes;		wxCheckBox* m_wxcbSeparateBandAutoscale;				wxPanel* m_wxpMousePointerData;		wxTextCtrl* m_wxtcXPosLabel;		wxTextCtrl* m_wxtcXPos;		wxTextCtrl* m_wxtcXPosUnit;		wxTextCtrl* m_wxtcYPosLabel;		wxTextCtrl* m_wxtcYPos;		wxTextCtrl* m_wxtcYPosUnit;		wxTextCtrl* m_wxtcLevelLabel;		wxTextCtrl* m_wxtcLevel;		wxTextCtrl* m_wxtcLevelUnit;				// Virtual event handlers, overide them in your derived class		virtual void OnOk( wxCommandEvent& event ){ event.Skip(); }		virtual void OnCopyResultsToClipboard( wxCommandEvent& event ){ event.Skip(); }		virtual void OnHelp( wxCommandEvent& event ){ event.Skip(); }		virtual void OnBandAnalysis( wxCommandEvent& event ){ event.Skip(); }		virtual void OnChoiceFrameRate( wxCommandEvent& event ){ event.Skip(); }		virtual void OnSTOPBtn( wxCommandEvent& event ){ event.Skip(); }		virtual void OnPAUSEBtn( wxCommandEvent& event ){ event.Skip(); }		virtual void OnPLAYBtn( wxCommandEvent& event ){ event.Skip(); }		virtual void OnSliderScroll( wxScrollEvent& event ){ event.Skip(); }		virtual void OnSpinCurFrame( wxSpinEvent& event ){ event.Skip(); }		virtual void OnSpinCtrlTxt( wxCommandEvent& event ){ event.Skip(); }		virtual void OnScaleStyle( wxCommandEvent& event ){ event.Skip(); }		virtual void OnTransparency( wxSpinEvent& event ){ event.Skip(); }		virtual void OnScaleUnit( wxCommandEvent& event ){ event.Skip(); }		virtual void OnInterpolationMethod( wxCommandEvent& event ){ event.Skip(); }		virtual void OnShowVirtMikesPos( wxCommandEvent& event ){ event.Skip(); }		virtual void OnSeparateBandAutoscale( wxCommandEvent& event ){ event.Skip(); }				public:		MyModuleDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Microphone Array Analyzer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1313,672 ), long style = wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxHSCROLL|wxVSCROLL );		~MyModuleDlg();	};////////////////////////////////////////////////////////////////////////////////// Class MyModuleConfDlg///////////////////////////////////////////////////////////////////////////////class MyModuleConfDlg : public wxDialog {	private:		protected:		wxPanel* m_panel7;		wxStaticText* m_staticText7;		wxTextCtrl* m_wxtcBgndImagePath;		wxButton* m_wxbBrowseBgndImage;		wxPanel* m_panel8;		wxStaticText* m_staticText8;		wxTextCtrl* m_wxtcXMLConfigFilePath;		wxButton* m_wxbBrowseXMLConfigFile;		wxPanel* m_wxpTable;				wxStaticText* m_wxstHeadersCheckLabel;		wxStaticText* m_wxstHeadersCheck;		wxStaticText* m_wxstMicNameLabel;		wxStaticText* m_wxstMicName;		wxStaticText* m_wxstManufacturerLabel;		wxStaticText* m_wxstManufacturer;		wxStaticText* m_wxstArrayTypeLabel;		wxStaticText* m_wxstArrayType;				wxStaticText* m_wxstDeconvIRsLengthLabel;		wxStaticText* m_wxstNumOfCapsulesLabel;		wxStaticText* m_wxstNumOfVirtMikesLabel;				wxStaticText* m_wxstNumOfCapsulesLabel2;				wxStaticText* m_wxstSamplingRateLabel;		wxStaticText* m_wxstBitDepthLabel;		wxStaticLine* m_staticline2;		wxStaticText* m_wxstXMLLabel;		wxStaticText* m_wxstXMLLength;		wxStaticText* m_wxstXMLCapsules;		wxStaticText* m_wxstXMLVirtual;		wxStaticText* m_wxstXMLLabel2;		wxStaticText* m_wxstXMLCapsules2;		wxStaticText* m_wxstWAVLabel2;		wxStaticText* m_wxstWAVfsample;		wxStaticText* m_wxstWAVFormat;		wxStaticLine* m_staticline21;						wxStaticBitmap* m_wxsbLengthCheck;		wxStaticBitmap* m_wxsbWAVChannelsCheck;						wxStaticBitmap* m_wxsbProjChannelsCheck;				wxStaticBitmap* m_wxsbSampleFormatCheck;		wxStaticBitmap* m_wxsbRateCheck;		wxStaticLine* m_staticline22;		wxStaticText* m_wxstWAVLabel;				wxStaticText* m_wxstWAVLength;		wxStaticText* m_wxstWAVChannels;				wxStaticText* m_wxstProjectLabel;		wxStaticText* m_wxstProjChannels;		wxStaticText* m_wxstProjectLabel2;		wxStaticText* m_wxstProjRate;		wxStaticText* m_wxstProjSampleFormat;		wxStaticLine* m_staticline23;				wxStaticText* m_wxstTotalLengthLabel;		wxStaticText* m_wxstWAVChannelsLabel;				wxStaticText* m_wxstProjChannelsLabel;				wxStaticText* m_wxstProjRateLabel;		wxStaticText* m_wxstProjSampleFormatLabel;		wxPanel* m_panel10;		wxStaticText* m_staticText104;				wxTextCtrl* m_wxtcFS;		wxStaticText* m_staticText105;		wxStaticText* m_staticText1041;				wxTextCtrl* m_wxtcMinSPL;		wxStaticText* m_staticText1051;		wxPanel* m_panel101;		wxStaticText* m_staticText1042;				wxTextCtrl* m_wxtcFLength;		wxStaticText* m_staticText1052;		wxStaticText* m_staticText10411;				wxTextCtrl* m_wxtcFOvlp;		wxStaticText* m_staticText10511;		wxStaticLine* m_staticline1;		wxPanel* m_pButtonsPanel;		wxButton* m_wxbHelp;				wxButton* m_wxbCancel;		wxButton* m_wxbOk;				// Virtual event handlers, overide them in your derived class		virtual void OnBrowseBGND( wxCommandEvent& event ){ event.Skip(); }		virtual void OnBrowseXML( wxCommandEvent& event ){ event.Skip(); }		virtual void FSOnChar( wxKeyEvent& event ){ event.Skip(); }		virtual void FSKillFocus( wxFocusEvent& event ){ event.Skip(); }		virtual void FSOnFocus( wxFocusEvent& event ){ event.Skip(); }		virtual void MinSPLOnChar( wxKeyEvent& event ){ event.Skip(); }		virtual void MinSPLKillFocus( wxFocusEvent& event ){ event.Skip(); }		virtual void MinSPLOnFocus( wxFocusEvent& event ){ event.Skip(); }		virtual void FLengthOnChar( wxKeyEvent& event ){ event.Skip(); }		virtual void FLengthKillFocus( wxFocusEvent& event ){ event.Skip(); }		virtual void FLengthOnFocus( wxFocusEvent& event ){ event.Skip(); }		virtual void FOvlpOnChar( wxKeyEvent& event ){ event.Skip(); }		virtual void FOvlpKillFocus( wxFocusEvent& event ){ event.Skip(); }		virtual void FOvlpOnFocus( wxFocusEvent& event ){ event.Skip(); }		virtual void OnHelp( wxCommandEvent& event ){ event.Skip(); }		virtual void OnCancel( wxCommandEvent& event ){ event.Skip(); }		virtual void OnOk( wxCommandEvent& event ){ event.Skip(); }				public:		MyModuleConfDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Microphone Array Analyzer - Configure"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );		~MyModuleConfDlg();	};////////////////////////////////////////////////////////////////////////////////// Class MyEditWatchPointsDlg///////////////////////////////////////////////////////////////////////////////class MyEditWatchPointsDlg : public wxDialog {	private:		protected:		wxListCtrl* m_wxlcWatchpoints;		wxButton* m_wxbOk;		wxButton* m_wxbCancel;				wxButton* m_wxbRemove;		wxButton* m_wxbEditLabel;		public:		MyEditWatchPointsDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Edit Watchpoints"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );		~MyEditWatchPointsDlg();	};#endif //__dialogs__