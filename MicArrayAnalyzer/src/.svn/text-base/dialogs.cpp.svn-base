///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep 12 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "dialogs.h"

///////////////////////////////////////////////////////////////////////////

MyModuleDlg::MyModuleDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 1313,-1 ), wxSize( -1,-1 ) );
	
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer291;
	bSizer291 = new wxBoxSizer( wxVERTICAL );
	
	m_pMap = new MyMap(this, ID_MAP, wxDefaultPosition, wxDefaultSize);
	//m_pMap->SetMinSize( wxSize( 1110,505 ) );
	
	bSizer291->Add( m_pMap, 0, wxALL, 5 );
	
	bSizer32->Add( bSizer291, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer311;
	bSizer311 = new wxBoxSizer( wxVERTICAL );
	
	m_wxpButtonsPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	wxBoxSizer* vSizer1;
	vSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_wxbOk = new wxButton( m_wxpButtonsPanel, wxID_ANY, _("Ok, close."), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxbOk->SetDefault(); 
	vSizer1->Add( m_wxbOk, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_wxbCopyResultsToClipboard = new wxButton( m_wxpButtonsPanel, wxID_ANY, _("Copy results to clipboard!"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	vSizer1->Add( m_wxbCopyResultsToClipboard, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_wxbHelp = new wxButton( m_wxpButtonsPanel, wxID_ANY, _("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	vSizer1->Add( m_wxbHelp, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_wxpButtonsPanel->SetSizer( vSizer1 );
	m_wxpButtonsPanel->Layout();
	vSizer1->Fit( m_wxpButtonsPanel );
	bSizer311->Add( m_wxpButtonsPanel, 0, wxLEFT|wxRIGHT|wxTOP|wxALIGN_RIGHT, 5 );
	
	m_wxpBandSelection = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxVERTICAL );
	
	wxString m_wxrbBandSelectionChoices[] = { _("Lin"), _("A-weighted"), _("31.5 Hz"), _("63 Hz"), _("125 Hz"), _("250 Hz"), _("500 Hz"), _("1 KHz"), _("2 KHz"), _("4 KHz"), _("8 KHz"), _("16 KHz") };
	int m_wxrbBandSelectionNChoices = sizeof( m_wxrbBandSelectionChoices ) / sizeof( wxString );
	m_wxrbBandSelection = new wxRadioBox( m_wxpBandSelection, wxID_ANY, _("Octave Band Analysis"), wxDefaultPosition, wxSize( -1,-1 ), m_wxrbBandSelectionNChoices, m_wxrbBandSelectionChoices, 1, wxRA_SPECIFY_COLS );
	m_wxrbBandSelection->SetSelection( 0 );
	m_wxrbBandSelection->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer25->Add( m_wxrbBandSelection, 0, wxALL|wxEXPAND|wxALIGN_RIGHT, 5 );
	
	m_wxpBandSelection->SetSizer( bSizer25 );
	m_wxpBandSelection->Layout();
	bSizer25->Fit( m_wxpBandSelection );
	bSizer311->Add( m_wxpBandSelection, 0, wxLEFT|wxRIGHT|wxALIGN_RIGHT, 5 );
	
	bSizer32->Add( bSizer311, 1, wxALIGN_RIGHT|wxEXPAND, 0 );
	
	bSizer31->Add( bSizer32, 1, wxEXPAND|wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer33;
	bSizer33 = new wxBoxSizer( wxHORIZONTAL );
	
	m_wxpColorMapOptions = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( m_wxpColorMapOptions, wxID_ANY, _("ColorMap Options") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer9;
	fgSizer9 = new wxFlexGridSizer( 2, 5, 0, 0 );
	fgSizer9->SetFlexibleDirection( wxBOTH );
	fgSizer9->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText63 = new wxStaticText( m_wxpColorMapOptions, wxID_ANY, _("Scale Style:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText63->Wrap( -1 );
	fgSizer9->Add( m_staticText63, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxString m_wxcScaleStyleChoices[] = { _("Jet"), _("Hot"), _("Cold") };
	int m_wxcScaleStyleNChoices = sizeof( m_wxcScaleStyleChoices ) / sizeof( wxString );
	m_wxcScaleStyle = new wxChoice( m_wxpColorMapOptions, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_wxcScaleStyleNChoices, m_wxcScaleStyleChoices, 0 );
	m_wxcScaleStyle->SetSelection( 0 );
	fgSizer9->Add( m_wxcScaleStyle, 0, wxALL, 5 );
	
	
	fgSizer9->Add( 10, 0, 1, wxEXPAND, 5 );
	
	m_staticText64 = new wxStaticText( m_wxpColorMapOptions, wxID_ANY, _("Map Transparency:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText64->Wrap( -1 );
	fgSizer9->Add( m_staticText64, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxHORIZONTAL );
	
	m_wxscTransparency = new wxSpinCtrl( m_wxpColorMapOptions, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 110,-1 ), wxSP_ARROW_KEYS, 0, 100, 50 );
	bSizer29->Add( m_wxscTransparency, 0, wxALL, 5 );
	
	m_staticText68 = new wxStaticText( m_wxpColorMapOptions, wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText68->Wrap( -1 );
	bSizer29->Add( m_staticText68, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 5 );
	
	fgSizer9->Add( bSizer29, 0, 0, 5 );
	
	m_staticText65 = new wxStaticText( m_wxpColorMapOptions, wxID_ANY, _("Scale Unit:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText65->Wrap( -1 );
	fgSizer9->Add( m_staticText65, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxString m_wxcScaleUnitChoices[] = { _("Decibel [dB]"), _("Pressure [Pa]"), _("Square root [Pa^(1/2)]"), _("Cube root [Pa^(1/3)]") };
	int m_wxcScaleUnitNChoices = sizeof( m_wxcScaleUnitChoices ) / sizeof( wxString );
	m_wxcScaleUnit = new wxChoice( m_wxpColorMapOptions, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_wxcScaleUnitNChoices, m_wxcScaleUnitChoices, 0 );
	m_wxcScaleUnit->SetSelection( 0 );
	fgSizer9->Add( m_wxcScaleUnit, 0, wxALL, 5 );
	
	
	fgSizer9->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText67 = new wxStaticText( m_wxpColorMapOptions, wxID_ANY, _("Interpolation Method:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText67->Wrap( -1 );
	fgSizer9->Add( m_staticText67, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxString m_wxcInterpolationMethodChoices[] = { _("Bilinear"), _("Bicubic"), _("Sinc (Lanczos)") };
	int m_wxcInterpolationMethodNChoices = sizeof( m_wxcInterpolationMethodChoices ) / sizeof( wxString );
	m_wxcInterpolationMethod = new wxChoice( m_wxpColorMapOptions, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_wxcInterpolationMethodNChoices, m_wxcInterpolationMethodChoices, 0 );
	m_wxcInterpolationMethod->SetSelection( 0 );
	m_wxcInterpolationMethod->Enable( false );
	
	fgSizer9->Add( m_wxcInterpolationMethod, 0, wxALL, 5 );
	
	sbSizer5->Add( fgSizer9, 1, wxEXPAND, 5 );
	
	m_wxpColorMapOptions->SetSizer( sbSizer5 );
	m_wxpColorMapOptions->Layout();
	sbSizer5->Fit( m_wxpColorMapOptions );
	bSizer33->Add( m_wxpColorMapOptions, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_wxpSpecialOptions = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer51;
	sbSizer51 = new wxStaticBoxSizer( new wxStaticBox( m_wxpSpecialOptions, wxID_ANY, _("Other Options") ), wxVERTICAL );
	
	m_wxcbShowVirtMikes = new wxCheckBox( m_wxpSpecialOptions, wxID_ANY, _("Show virtual mikes positions"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer51->Add( m_wxcbShowVirtMikes, 0, wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	m_wxcbSeparateBandAutoscale = new wxCheckBox( m_wxpSpecialOptions, wxID_ANY, _("Optimize color scale for the selected audio band (autoscale)"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer51->Add( m_wxcbSeparateBandAutoscale, 0, wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	m_wxpSpecialOptions->SetSizer( sbSizer51 );
	m_wxpSpecialOptions->Layout();
	sbSizer51->Fit( m_wxpSpecialOptions );
	bSizer33->Add( m_wxpSpecialOptions, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer33->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_wxpMousePointerData = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( m_wxpMousePointerData, wxID_ANY, _("Mouse Pointer Data") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer8;
	fgSizer8 = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizer8->SetFlexibleDirection( wxBOTH );
	fgSizer8->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_wxtcXPosLabel = new wxTextCtrl( m_wxpMousePointerData, wxID_ANY, _("Azimuth:"), wxDefaultPosition, wxSize( -1,-1 ), wxTE_READONLY|wxNO_BORDER );
	m_wxtcXPosLabel->SetBackgroundColour( wxColour( 240, 235, 226 ) );
	m_wxtcXPosLabel->SetMaxSize( wxSize( 70,-1 ) );
	
	fgSizer8->Add( m_wxtcXPosLabel, 0, wxEXPAND|wxTOP|wxLEFT, 5 );
	
	m_wxtcXPos = new wxTextCtrl( m_wxpMousePointerData, wxID_ANY, _("0"), wxDefaultPosition, wxSize( 70,-1 ), wxTE_LEFT|wxTE_READONLY|wxNO_BORDER );
	m_wxtcXPos->SetBackgroundColour( wxColour( 240, 235, 226 ) );
	m_wxtcXPos->SetMinSize( wxSize( 70,-1 ) );
	m_wxtcXPos->SetMaxSize( wxSize( 70,-1 ) );
	
	fgSizer8->Add( m_wxtcXPos, 0, wxTOP|wxRIGHT, 5 );
	
	m_wxtcXPosUnit = new wxTextCtrl( m_wxpMousePointerData, wxID_ANY, _("[deg]"), wxDefaultPosition, wxSize( 50,-1 ), wxTE_CENTRE|wxTE_READONLY|wxNO_BORDER );
	m_wxtcXPosUnit->SetBackgroundColour( wxColour( 240, 235, 226 ) );
	m_wxtcXPosUnit->SetMinSize( wxSize( 50,-1 ) );
	m_wxtcXPosUnit->SetMaxSize( wxSize( 50,-1 ) );
	
	fgSizer8->Add( m_wxtcXPosUnit, 0, wxTOP|wxRIGHT|wxLEFT|wxALIGN_RIGHT, 5 );
	
	m_wxtcYPosLabel = new wxTextCtrl( m_wxpMousePointerData, wxID_ANY, _("Elevation:"), wxDefaultPosition, wxSize( -1,-1 ), wxTE_READONLY|wxNO_BORDER );
	m_wxtcYPosLabel->SetBackgroundColour( wxColour( 240, 235, 226 ) );
	m_wxtcYPosLabel->SetMinSize( wxSize( 70,-1 ) );
	
	fgSizer8->Add( m_wxtcYPosLabel, 0, wxEXPAND|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_wxtcYPos = new wxTextCtrl( m_wxpMousePointerData, wxID_ANY, _("0"), wxDefaultPosition, wxSize( 70,-1 ), wxTE_LEFT|wxTE_READONLY|wxNO_BORDER );
	m_wxtcYPos->SetBackgroundColour( wxColour( 240, 235, 226 ) );
	m_wxtcYPos->SetMinSize( wxSize( 70,-1 ) );
	m_wxtcYPos->SetMaxSize( wxSize( 70,-1 ) );
	
	fgSizer8->Add( m_wxtcYPos, 0, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_wxtcYPosUnit = new wxTextCtrl( m_wxpMousePointerData, wxID_ANY, _("[deg]"), wxDefaultPosition, wxSize( 50,-1 ), wxTE_CENTRE|wxTE_READONLY|wxNO_BORDER );
	m_wxtcYPosUnit->SetBackgroundColour( wxColour( 240, 235, 226 ) );
	m_wxtcYPosUnit->SetMinSize( wxSize( 50,-1 ) );
	m_wxtcYPosUnit->SetMaxSize( wxSize( 50,-1 ) );
	
	fgSizer8->Add( m_wxtcYPosUnit, 0, wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_wxtcLevelLabel = new wxTextCtrl( m_wxpMousePointerData, wxID_ANY, _("Level:"), wxDefaultPosition, wxSize( -1,-1 ), wxTE_READONLY|wxNO_BORDER );
	m_wxtcLevelLabel->SetBackgroundColour( wxColour( 240, 235, 226 ) );
	m_wxtcLevelLabel->SetMinSize( wxSize( 70,-1 ) );
	
	fgSizer8->Add( m_wxtcLevelLabel, 0, wxALIGN_BOTTOM|wxEXPAND|wxLEFT, 5 );
	
	m_wxtcLevel = new wxTextCtrl( m_wxpMousePointerData, wxID_ANY, _("0"), wxDefaultPosition, wxSize( 70,-1 ), wxTE_LEFT|wxTE_READONLY|wxNO_BORDER );
	m_wxtcLevel->SetBackgroundColour( wxColour( 240, 235, 226 ) );
	m_wxtcLevel->SetMinSize( wxSize( 70,-1 ) );
	m_wxtcLevel->SetMaxSize( wxSize( 70,-1 ) );
	
	fgSizer8->Add( m_wxtcLevel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_BOTTOM|wxRIGHT, 5 );
	
	m_wxtcLevelUnit = new wxTextCtrl( m_wxpMousePointerData, wxID_ANY, _("[CBRT]"), wxDefaultPosition, wxSize( 50,-1 ), wxTE_CENTRE|wxTE_READONLY|wxNO_BORDER );
	m_wxtcLevelUnit->SetBackgroundColour( wxColour( 240, 235, 226 ) );
	m_wxtcLevelUnit->SetMinSize( wxSize( 50,-1 ) );
	m_wxtcLevelUnit->SetMaxSize( wxSize( 50,-1 ) );
	
	fgSizer8->Add( m_wxtcLevelUnit, 0, wxALIGN_BOTTOM|wxALIGN_RIGHT|wxRIGHT|wxLEFT, 5 );
	
	sbSizer4->Add( fgSizer8, 1, wxEXPAND, 5 );
	
	m_wxpMousePointerData->SetSizer( sbSizer4 );
	m_wxpMousePointerData->Layout();
	sbSizer4->Fit( m_wxpMousePointerData );
	bSizer33->Add( m_wxpMousePointerData, 0, wxALIGN_RIGHT|wxBOTTOM|wxLEFT|wxRIGHT|wxTOP|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer31->Add( bSizer33, 0, wxEXPAND|wxALL, 5 );
	
	this->SetSizer( bSizer31 );
	this->Layout();
	bSizer31->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_wxbOk->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleDlg::OnOk ), NULL, this );
	m_wxbCopyResultsToClipboard->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleDlg::OnCopyResultsToClipboard ), NULL, this );
	m_wxbHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleDlg::OnHelp ), NULL, this );
	m_wxrbBandSelection->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( MyModuleDlg::OnBandAnalysis ), NULL, this );
	m_wxcScaleStyle->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyModuleDlg::OnScaleStyle ), NULL, this );
	m_wxscTransparency->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( MyModuleDlg::OnTransparency ), NULL, this );
	m_wxcScaleUnit->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyModuleDlg::OnScaleUnit ), NULL, this );
	m_wxcbShowVirtMikes->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyModuleDlg::OnShowVirtMikesPos ), NULL, this );
	m_wxcbSeparateBandAutoscale->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyModuleDlg::OnSeparateBandAutoscale ), NULL, this );
}

MyModuleDlg::~MyModuleDlg()
{
	// Disconnect Events
	m_wxbOk->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleDlg::OnOk ), NULL, this );
	m_wxbCopyResultsToClipboard->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleDlg::OnCopyResultsToClipboard ), NULL, this );
	m_wxbHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleDlg::OnHelp ), NULL, this );
	m_wxrbBandSelection->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( MyModuleDlg::OnBandAnalysis ), NULL, this );
	m_wxcScaleStyle->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyModuleDlg::OnScaleStyle ), NULL, this );
	m_wxscTransparency->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( MyModuleDlg::OnTransparency ), NULL, this );
	m_wxcScaleUnit->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyModuleDlg::OnScaleUnit ), NULL, this );
	m_wxcbShowVirtMikes->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyModuleDlg::OnShowVirtMikesPos ), NULL, this );
	m_wxcbSeparateBandAutoscale->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyModuleDlg::OnSeparateBandAutoscale ), NULL, this );
	
}

MyModuleConfDlg::MyModuleConfDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxVERTICAL );
	
	m_panel5 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText1 = new wxStaticText( m_panel5, wxID_ANY, _("Background image file:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer12->Add( m_staticText1, 0, wxLEFT|wxTOP, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_wxtcBgndImagePath = new wxTextCtrl( m_panel5, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	m_wxtcBgndImagePath->SetMinSize( wxSize( 410,-1 ) );
	
	bSizer4->Add( m_wxtcBgndImagePath, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_wxbBrowseBgndImage = new wxButton( m_panel5, wxID_ANY, _("Browse..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_wxbBrowseBgndImage, 0, wxALL, 5 );
	
	bSizer12->Add( bSizer4, 0, wxEXPAND, 5 );
	
	m_panel5->SetSizer( bSizer12 );
	m_panel5->Layout();
	bSizer12->Fit( m_panel5 );
	bSizer29->Add( m_panel5, 1, wxALIGN_CENTER|wxALL, 5 );
	
	m_panel8 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( m_panel8, wxID_ANY, _("Probe settings") ), wxVERTICAL );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText63 = new wxStaticText( m_panel8, wxID_ANY, _("XML configuration file:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText63->Wrap( -1 );
	m_staticText63->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer25->Add( m_staticText63, 0, wxLEFT|wxTOP, 5 );
	
	wxBoxSizer* bSizer81;
	bSizer81 = new wxBoxSizer( wxHORIZONTAL );
	
	m_wxtcXMLConfigFilePath = new wxTextCtrl( m_panel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	m_wxtcXMLConfigFilePath->SetMinSize( wxSize( 410,-1 ) );
	
	bSizer81->Add( m_wxtcXMLConfigFilePath, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	m_wxbBrowseXmlConfigFile = new wxButton( m_panel8, wxID_ANY, _("Browse..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer81->Add( m_wxbBrowseXmlConfigFile, 0, wxALL, 5 );
	
	bSizer25->Add( bSizer81, 0, wxEXPAND, 5 );
	
	sbSizer4->Add( bSizer25, 0, wxEXPAND, 5 );
	
	m_wxpTable = new wxPanel( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer251;
	bSizer251 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer251->Add( 0, 0, 0, wxEXPAND, 0 );
	
	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxVERTICAL );
	
	m_wxbsHeadersCheck = new wxBoxSizer( wxHORIZONTAL );
	
	m_wxstHeadersCheckLabel = new wxStaticText( m_wxpTable, wxID_ANY, _("Headers check:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstHeadersCheckLabel->Wrap( -1 );
	m_wxstHeadersCheckLabel->Enable( false );
	
	m_wxbsHeadersCheck->Add( m_wxstHeadersCheckLabel, 0, wxBOTTOM|wxRIGHT|wxTOP, 5 );
	
	m_wxstHeadersCheck = new wxStaticText( m_wxpTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstHeadersCheck->Wrap( -1 );
	m_wxstHeadersCheck->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 91, false, wxEmptyString ) );
	
	m_wxbsHeadersCheck->Add( m_wxstHeadersCheck, 0, wxBOTTOM|wxTOP, 5 );
	
	bSizer26->Add( m_wxbsHeadersCheck, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxHORIZONTAL );
	
	m_wxstMicNameLabel = new wxStaticText( m_wxpTable, wxID_ANY, _("Mic Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstMicNameLabel->Wrap( -1 );
	m_wxstMicNameLabel->Enable( false );
	
	bSizer27->Add( m_wxstMicNameLabel, 0, wxRIGHT, 5 );
	
	m_wxstMicName = new wxStaticText( m_wxpTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstMicName->Wrap( -1 );
	m_wxstMicName->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 91, false, wxEmptyString ) );
	
	bSizer27->Add( m_wxstMicName, 0, 0, 5 );
	
	bSizer26->Add( bSizer27, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxHORIZONTAL );
	
	m_wxstManufacturerLabel = new wxStaticText( m_wxpTable, wxID_ANY, _("Manufacturer:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstManufacturerLabel->Wrap( -1 );
	m_wxstManufacturerLabel->Enable( false );
	
	bSizer34->Add( m_wxstManufacturerLabel, 0, wxRIGHT, 5 );
	
	m_wxstManufacturer = new wxStaticText( m_wxpTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstManufacturer->Wrap( -1 );
	m_wxstManufacturer->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 91, false, wxEmptyString ) );
	
	bSizer34->Add( m_wxstManufacturer, 0, 0, 5 );
	
	bSizer26->Add( bSizer34, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer341;
	bSizer341 = new wxBoxSizer( wxHORIZONTAL );
	
	m_wxstArrayTypeLabel = new wxStaticText( m_wxpTable, wxID_ANY, _("Array Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstArrayTypeLabel->Wrap( -1 );
	m_wxstArrayTypeLabel->Enable( false );
	
	bSizer341->Add( m_wxstArrayTypeLabel, 0, wxRIGHT, 5 );
	
	m_wxstArrayType = new wxStaticText( m_wxpTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstArrayType->Wrap( -1 );
	m_wxstArrayType->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 91, false, wxEmptyString ) );
	
	bSizer341->Add( m_wxstArrayType, 0, 0, 5 );
	
	bSizer26->Add( bSizer341, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer8;
	fgSizer8 = new wxFlexGridSizer( 3, 5, 0, 0 );
	fgSizer8->SetFlexibleDirection( wxBOTH );
	fgSizer8->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_wxbsXML = new wxBoxSizer( wxHORIZONTAL );
	
	
	m_wxbsXML->Add( 25, 0, 0, 0, 5 );
	
	m_wxstXMLLabel = new wxStaticText( m_wxpTable, wxID_ANY, _("XML"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstXMLLabel->Wrap( -1 );
	m_wxstXMLLabel->Enable( false );
	
	m_wxbsXML->Add( m_wxstXMLLabel, 0, wxALL, 5 );
	
	
	m_wxbsXML->Add( 25, 0, 0, 0, 5 );
	
	fgSizer8->Add( m_wxbsXML, 1, wxEXPAND, 5 );
	
	m_wxbsSpacer = new wxBoxSizer( wxVERTICAL );
	
	
	m_wxbsSpacer->Add( 0, 0, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	fgSizer8->Add( m_wxbsSpacer, 1, wxEXPAND, 5 );
	
	m_wxbsWAV = new wxBoxSizer( wxHORIZONTAL );
	
	
	m_wxbsWAV->Add( 25, 0, 0, 0, 5 );
	
	m_wxstWAVLabel = new wxStaticText( m_wxpTable, wxID_ANY, _("WAV"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstWAVLabel->Wrap( -1 );
	m_wxstWAVLabel->Enable( false );
	
	m_wxbsWAV->Add( m_wxstWAVLabel, 1, wxALL|wxEXPAND, 5 );
	
	
	m_wxbsWAV->Add( 25, 0, 0, 0, 5 );
	
	fgSizer8->Add( m_wxbsWAV, 1, wxEXPAND, 5 );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer( wxVERTICAL );
	
	m_wxstDeconvIRsLengthLabel = new wxStaticText( m_wxpTable, wxID_ANY, _("Deconv. IRs Length [SMP]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstDeconvIRsLengthLabel->Wrap( -1 );
	m_wxstDeconvIRsLengthLabel->Enable( false );
	
	bSizer36->Add( m_wxstDeconvIRsLengthLabel, 0, 0, 5 );
	
	m_wxstNumOfCapsulesLabel = new wxStaticText( m_wxpTable, wxID_ANY, _("# of capsules"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstNumOfCapsulesLabel->Wrap( -1 );
	m_wxstNumOfCapsulesLabel->Enable( false );
	
	bSizer36->Add( m_wxstNumOfCapsulesLabel, 0, wxRIGHT, 5 );
	
	fgSizer8->Add( bSizer36, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer37;
	bSizer37 = new wxBoxSizer( wxVERTICAL );
	
	m_wxstXMLLength = new wxStaticText( m_wxpTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT|wxST_NO_AUTORESIZE );
	m_wxstXMLLength->Wrap( -1 );
	m_wxstXMLLength->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 91, false, wxEmptyString ) );
	m_wxstXMLLength->SetMinSize( wxSize( 75,-1 ) );
	
	bSizer37->Add( m_wxstXMLLength, 0, wxALIGN_CENTER_HORIZONTAL, 19 );
	
	m_wxstXMLCapsules = new wxStaticText( m_wxpTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT|wxST_NO_AUTORESIZE );
	m_wxstXMLCapsules->Wrap( -1 );
	m_wxstXMLCapsules->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 91, false, wxEmptyString ) );
	m_wxstXMLCapsules->SetMinSize( wxSize( 75,-1 ) );
	
	bSizer37->Add( m_wxstXMLCapsules, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	fgSizer8->Add( bSizer37, 0, wxEXPAND, 5 );
	
	m_wxsbLengthCheck = new wxStaticBitmap( m_wxpTable, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	m_wxsbLengthCheck->SetMaxSize( wxSize( 15,15 ) );
	
	fgSizer8->Add( m_wxsbLengthCheck, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_wxstWAVLength = new wxStaticText( m_wxpTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT|wxST_NO_AUTORESIZE );
	m_wxstWAVLength->Wrap( -1 );
	m_wxstWAVLength->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 91, false, wxEmptyString ) );
	m_wxstWAVLength->SetMinSize( wxSize( 75,-1 ) );
	
	fgSizer8->Add( m_wxstWAVLength, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 19 );
	
	m_wxstTotalLengthLabel = new wxStaticText( m_wxpTable, wxID_ANY, _("Total length [SMP]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstTotalLengthLabel->Wrap( -1 );
	m_wxstTotalLengthLabel->Enable( false );
	
	fgSizer8->Add( m_wxstTotalLengthLabel, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	m_wxstNumOfVirtMikesLabel = new wxStaticText( m_wxpTable, wxID_ANY, _("# of virtual mikes"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstNumOfVirtMikesLabel->Wrap( -1 );
	m_wxstNumOfVirtMikesLabel->Enable( false );
	
	fgSizer8->Add( m_wxstNumOfVirtMikesLabel, 0, wxALIGN_CENTER_VERTICAL|wxTOP, 5 );
	
	m_wxstXMLVirtual = new wxStaticText( m_wxpTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT|wxST_NO_AUTORESIZE );
	m_wxstXMLVirtual->Wrap( -1 );
	m_wxstXMLVirtual->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 91, false, wxEmptyString ) );
	m_wxstXMLVirtual->SetMinSize( wxSize( 75,-1 ) );
	
	fgSizer8->Add( m_wxstXMLVirtual, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxTOP, 5 );
	
	m_wxsbWAVChannelsCheck = new wxStaticBitmap( m_wxpTable, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	m_wxsbWAVChannelsCheck->SetMaxSize( wxSize( 15,15 ) );
	
	fgSizer8->Add( m_wxsbWAVChannelsCheck, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP, 5 );
	
	m_wxstWAVChannels = new wxStaticText( m_wxpTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT|wxST_NO_AUTORESIZE );
	m_wxstWAVChannels->Wrap( -1 );
	m_wxstWAVChannels->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 91, false, wxEmptyString ) );
	m_wxstWAVChannels->SetMinSize( wxSize( 75,-1 ) );
	
	fgSizer8->Add( m_wxstWAVChannels, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxTOP, 5 );
	
	m_wxstWAVChannelsLabel = new wxStaticText( m_wxpTable, wxID_ANY, _("# of channels"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstWAVChannelsLabel->Wrap( -1 );
	m_wxstWAVChannelsLabel->Enable( false );
	
	fgSizer8->Add( m_wxstWAVChannelsLabel, 0, wxALIGN_CENTER_VERTICAL|wxTOP, 5 );
	
	
	fgSizer8->Add( 0, 0, 0, wxEXPAND, 0 );
	
	m_wxstXMLLabel2 = new wxStaticText( m_wxpTable, wxID_ANY, _("XML"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstXMLLabel2->Wrap( -1 );
	m_wxstXMLLabel2->Enable( false );
	
	fgSizer8->Add( m_wxstXMLLabel2, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	fgSizer8->Add( 0, 0, 0, wxEXPAND, 0 );
	
	m_wxstProjectLabel = new wxStaticText( m_wxpTable, wxID_ANY, _("PROJECT"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstProjectLabel->Wrap( -1 );
	m_wxstProjectLabel->Enable( false );
	
	fgSizer8->Add( m_wxstProjectLabel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	fgSizer8->Add( 0, 0, 0, wxEXPAND, 0 );
	
	m_wxstNumOfCapsulesLabel2 = new wxStaticText( m_wxpTable, wxID_ANY, _("# of capsules"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstNumOfCapsulesLabel2->Wrap( -1 );
	m_wxstNumOfCapsulesLabel2->Enable( false );
	
	fgSizer8->Add( m_wxstNumOfCapsulesLabel2, 0, 0, 5 );
	
	m_wxstXMLCapsules2 = new wxStaticText( m_wxpTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT|wxST_NO_AUTORESIZE );
	m_wxstXMLCapsules2->Wrap( -1 );
	m_wxstXMLCapsules2->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 91, false, wxEmptyString ) );
	m_wxstXMLCapsules2->SetMinSize( wxSize( 75,-1 ) );
	
	fgSizer8->Add( m_wxstXMLCapsules2, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 19 );
	
	m_wxsbProjChannelsCheck = new wxStaticBitmap( m_wxpTable, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	m_wxsbProjChannelsCheck->SetMaxSize( wxSize( 15,15 ) );
	
	fgSizer8->Add( m_wxsbProjChannelsCheck, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_wxstProjChannels = new wxStaticText( m_wxpTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT|wxST_NO_AUTORESIZE );
	m_wxstProjChannels->Wrap( -1 );
	m_wxstProjChannels->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 91, false, wxEmptyString ) );
	m_wxstProjChannels->Enable( false );
	m_wxstProjChannels->SetMinSize( wxSize( 75,-1 ) );
	
	fgSizer8->Add( m_wxstProjChannels, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 19 );
	
	m_wxstProjChannelsLabel = new wxStaticText( m_wxpTable, wxID_ANY, _("# of channels"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstProjChannelsLabel->Wrap( -1 );
	m_wxstProjChannelsLabel->Enable( false );
	
	fgSizer8->Add( m_wxstProjChannelsLabel, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_wxstWAVLabel2 = new wxStaticText( m_wxpTable, wxID_ANY, _("WAV"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstWAVLabel2->Wrap( -1 );
	m_wxstWAVLabel2->Enable( false );
	
	fgSizer8->Add( m_wxstWAVLabel2, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_wxstProjectLabel2 = new wxStaticText( m_wxpTable, wxID_ANY, _("PROJECT"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstProjectLabel2->Wrap( -1 );
	m_wxstProjectLabel2->Enable( false );
	
	fgSizer8->Add( m_wxstProjectLabel2, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_wxstSamplingRateLabel = new wxStaticText( m_wxpTable, wxID_ANY, _("Sampling Rate [Hz]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstSamplingRateLabel->Wrap( -1 );
	m_wxstSamplingRateLabel->Enable( false );
	
	fgSizer8->Add( m_wxstSamplingRateLabel, 0, 0, 5 );
	
	m_wxstWAVfsample = new wxStaticText( m_wxpTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxALIGN_LEFT|wxST_NO_AUTORESIZE );
	m_wxstWAVfsample->Wrap( -1 );
	m_wxstWAVfsample->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 91, false, wxEmptyString ) );
	m_wxstWAVfsample->SetMinSize( wxSize( 75,-1 ) );
	
	fgSizer8->Add( m_wxstWAVfsample, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 19 );
	
	m_wxsbRateCheck = new wxStaticBitmap( m_wxpTable, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	m_wxsbRateCheck->SetMaxSize( wxSize( 15,15 ) );
	
	fgSizer8->Add( m_wxsbRateCheck, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_wxstProjRate = new wxStaticText( m_wxpTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT|wxST_NO_AUTORESIZE );
	m_wxstProjRate->Wrap( -1 );
	m_wxstProjRate->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 91, false, wxEmptyString ) );
	m_wxstProjRate->Enable( false );
	m_wxstProjRate->SetMinSize( wxSize( 75,-1 ) );
	
	fgSizer8->Add( m_wxstProjRate, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 19 );
	
	m_wxstProjRateLabel = new wxStaticText( m_wxpTable, wxID_ANY, _("Proj. Rate [Hz]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstProjRateLabel->Wrap( -1 );
	m_wxstProjRateLabel->Enable( false );
	
	fgSizer8->Add( m_wxstProjRateLabel, 0, 0, 5 );
	
	m_wxstBitDepthLabel = new wxStaticText( m_wxpTable, wxID_ANY, _("Bit Depth [bit]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstBitDepthLabel->Wrap( -1 );
	m_wxstBitDepthLabel->Enable( false );
	
	fgSizer8->Add( m_wxstBitDepthLabel, 0, wxALIGN_CENTER_VERTICAL|wxTOP, 5 );
	
	m_wxstWAVFormat = new wxStaticText( m_wxpTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT|wxST_NO_AUTORESIZE );
	m_wxstWAVFormat->Wrap( -1 );
	m_wxstWAVFormat->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 91, false, wxEmptyString ) );
	m_wxstWAVFormat->SetMinSize( wxSize( 75,-1 ) );
	
	fgSizer8->Add( m_wxstWAVFormat, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxTOP, 5 );
	
	m_wxsbSampleFormatCheck = new wxStaticBitmap( m_wxpTable, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	m_wxsbSampleFormatCheck->SetMaxSize( wxSize( 15,15 ) );
	
	fgSizer8->Add( m_wxsbSampleFormatCheck, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxTOP, 5 );
	
	m_wxstProjSampleFormat = new wxStaticText( m_wxpTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT|wxST_NO_AUTORESIZE );
	m_wxstProjSampleFormat->Wrap( -1 );
	m_wxstProjSampleFormat->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 91, false, wxEmptyString ) );
	m_wxstProjSampleFormat->Enable( false );
	m_wxstProjSampleFormat->SetMinSize( wxSize( 75,-1 ) );
	
	fgSizer8->Add( m_wxstProjSampleFormat, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxTOP, 5 );
	
	m_wxstProjSampleFormatLabel = new wxStaticText( m_wxpTable, wxID_ANY, _("Sample Format [bit]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxstProjSampleFormatLabel->Wrap( -1 );
	m_wxstProjSampleFormatLabel->Enable( false );
	
	fgSizer8->Add( m_wxstProjSampleFormatLabel, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxTOP, 5 );
	
	bSizer26->Add( fgSizer8, 0, 0, 5 );
	
	bSizer251->Add( bSizer26, 1, wxLEFT|wxRIGHT, 5 );
	
	m_wxpTable->SetSizer( bSizer251 );
	m_wxpTable->Layout();
	bSizer251->Fit( m_wxpTable );
	sbSizer4->Add( m_wxpTable, 0, wxALIGN_CENTER_HORIZONTAL, 0 );
	
	m_panel8->SetSizer( sbSizer4 );
	m_panel8->Layout();
	sbSizer4->Fit( m_panel8 );
	bSizer29->Add( m_panel8, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_panel18 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer10;
	fgSizer10 = new wxFlexGridSizer( 2, 3, 0, 0 );
	fgSizer10->SetFlexibleDirection( wxBOTH );
	fgSizer10->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText42 = new wxStaticText( m_panel18, wxID_ANY, _("Peak SPL value corresponding to FS:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	fgSizer10->Add( m_staticText42, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_wxtcFS = new wxTextCtrl( m_panel18, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 45,25 ), wxTE_CENTRE );
	fgSizer10->Add( m_wxtcFS, 0, wxALL, 5 );
	
	m_staticText43 = new wxStaticText( m_panel18, wxID_ANY, _("dB"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	fgSizer10->Add( m_staticText43, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText421 = new wxStaticText( m_panel18, wxID_ANY, _("Minimum SPL treshold:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText421->Wrap( -1 );
	m_staticText421->SetMinSize( wxSize( 237,-1 ) );
	
	fgSizer10->Add( m_staticText421, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_wxtcMinSPL = new wxTextCtrl( m_panel18, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 45,25 ), wxTE_CENTRE );
	fgSizer10->Add( m_wxtcMinSPL, 0, wxALL, 5 );
	
	m_staticText431 = new wxStaticText( m_panel18, wxID_ANY, _("dB"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText431->Wrap( -1 );
	fgSizer10->Add( m_staticText431, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_panel18->SetSizer( fgSizer10 );
	m_panel18->Layout();
	fgSizer10->Fit( m_panel18 );
	bSizer29->Add( m_panel18, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer29->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	m_pButtonsPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer371;
	bSizer371 = new wxBoxSizer( wxHORIZONTAL );
	
	m_wxbHelp = new wxButton( m_pButtonsPanel, wxID_ANY, _("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer371->Add( m_wxbHelp, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer371->Add( 0, 0, 1, 0, 5 );
	
	m_wxbCancel = new wxButton( m_pButtonsPanel, wxID_ANY, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer371->Add( m_wxbCancel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_wxbOk = new wxButton( m_pButtonsPanel, wxID_ANY, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	m_wxbOk->Enable( false );
	
	bSizer371->Add( m_wxbOk, 0, wxALL|wxALIGN_CENTER_VERTICAL, 10 );
	
	m_pButtonsPanel->SetSizer( bSizer371 );
	m_pButtonsPanel->Layout();
	bSizer371->Fit( m_pButtonsPanel );
	bSizer29->Add( m_pButtonsPanel, 0, wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer29 );
	this->Layout();
	bSizer29->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_wxbBrowseBgndImage->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleConfDlg::OnBrowseBGND ), NULL, this );
	m_wxbBrowseXmlConfigFile->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleConfDlg::OnBrowseXML ), NULL, this );
	m_wxtcFS->Connect( wxEVT_CHAR, wxKeyEventHandler( MyModuleConfDlg::FSOnChar ), NULL, this );
	m_wxtcFS->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( MyModuleConfDlg::FSKillFocus ), NULL, this );
	m_wxtcFS->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( MyModuleConfDlg::FSOnFocus ), NULL, this );
	m_wxtcMinSPL->Connect( wxEVT_CHAR, wxKeyEventHandler( MyModuleConfDlg::MinSPLOnChar ), NULL, this );
	m_wxtcMinSPL->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( MyModuleConfDlg::MinSPLKillFocus ), NULL, this );
	m_wxtcMinSPL->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( MyModuleConfDlg::MinSPLOnFocus ), NULL, this );
	m_wxbHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleConfDlg::OnHelp ), NULL, this );
	m_wxbCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleConfDlg::OnCancel ), NULL, this );
	m_wxbOk->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleConfDlg::OnOk ), NULL, this );
}

MyModuleConfDlg::~MyModuleConfDlg()
{
	// Disconnect Events
	m_wxbBrowseBgndImage->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleConfDlg::OnBrowseBGND ), NULL, this );
	m_wxbBrowseXmlConfigFile->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleConfDlg::OnBrowseXML ), NULL, this );
	m_wxtcFS->Disconnect( wxEVT_CHAR, wxKeyEventHandler( MyModuleConfDlg::FSOnChar ), NULL, this );
	m_wxtcFS->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( MyModuleConfDlg::FSKillFocus ), NULL, this );
	m_wxtcFS->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( MyModuleConfDlg::FSOnFocus ), NULL, this );
	m_wxtcMinSPL->Disconnect( wxEVT_CHAR, wxKeyEventHandler( MyModuleConfDlg::MinSPLOnChar ), NULL, this );
	m_wxtcMinSPL->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( MyModuleConfDlg::MinSPLKillFocus ), NULL, this );
	m_wxtcMinSPL->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( MyModuleConfDlg::MinSPLOnFocus ), NULL, this );
	m_wxbHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleConfDlg::OnHelp ), NULL, this );
	m_wxbCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleConfDlg::OnCancel ), NULL, this );
	m_wxbOk->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleConfDlg::OnOk ), NULL, this );
	
}

MyEditWatchpointsDlg::MyEditWatchpointsDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer39;
	bSizer39 = new wxBoxSizer( wxHORIZONTAL );
	
	m_wxlcWatchpoints = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_SINGLE_SEL|wxSUNKEN_BORDER );
	m_wxlcWatchpoints->SetMinSize( wxSize( 170,300 ) );
	
	bSizer39->Add( m_wxlcWatchpoints, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxVERTICAL );
	
	m_wxbOk = new wxButton( this, wxID_ANY, _("Ok, close."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer40->Add( m_wxbOk, 0, wxALL, 5 );
	
	m_wxbCancel = new wxButton( this, wxID_ANY, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer40->Add( m_wxbCancel, 0, wxBOTTOM|wxLEFT|wxRIGHT, 5 );
	
	
	bSizer40->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_wxbRemove = new wxButton( this, wxID_ANY, _("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer40->Add( m_wxbRemove, 0, wxALL, 5 );
	
	m_wxbEditLabel = new wxButton( this, wxID_ANY, _("Edit Label..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer40->Add( m_wxbEditLabel, 0, wxBOTTOM|wxLEFT|wxRIGHT, 5 );
	
	bSizer39->Add( bSizer40, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer39 );
	this->Layout();
	bSizer39->Fit( this );
	
	this->Centre( wxBOTH );
}

MyEditWatchpointsDlg::~MyEditWatchpointsDlg()
{
}
