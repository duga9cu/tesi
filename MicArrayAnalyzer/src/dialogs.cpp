///////////////////////////////////////////////////////////////////////////// C++ code generated with wxFormBuilder (version Apr 16 2008)// http://www.wxformbuilder.org///// PLEASE DO "NOT" EDIT THIS FILE!///////////////////////////////////////////////////////////////////////////#include "dialogs.h"///////////////////////////////////////////////////////////////////////////MyModuleDlg::MyModuleDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style ){	this->SetSizeHints( wxSize( 1313,-1 ), wxDefaultSize );		wxBoxSizer* bSizer1;	bSizer1 = new wxBoxSizer( wxVERTICAL );		wxBoxSizer* mappa;	mappa = new wxBoxSizer( wxHORIZONTAL );		m_wxswPanelMap = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );	m_wxswPanelMap->SetScrollRate( 5, 5 );	wxBoxSizer* bSizer3;	bSizer3 = new wxBoxSizer( wxVERTICAL );		m_pMap = new MyMap(m_wxswPanelMap,ID_MAP,wxDefaultPosition, wxDefaultSize);	m_pMap->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );	m_pMap->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );		bSizer3->Add( m_pMap, 0, wxALL, 5 );		m_wxswPanelMap->SetSizer( bSizer3 );	m_wxswPanelMap->Layout();	bSizer3->Fit( m_wxswPanelMap );	mappa->Add( m_wxswPanelMap, 1, wxEXPAND | wxALL, 5 );		wxBoxSizer* bSizer8;	bSizer8 = new wxBoxSizer( wxVERTICAL );		m_wxButtonsPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );	wxBoxSizer* vSizer1;	vSizer1 = new wxBoxSizer( wxVERTICAL );		m_wxbOk = new wxButton( m_wxButtonsPanel, wxID_ANY, wxT("Ok, Close."), wxDefaultPosition, wxDefaultSize, 0 );	vSizer1->Add( m_wxbOk, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );		m_wxbCopyResultsToClipboard = new wxButton( m_wxButtonsPanel, wxID_ANY, wxT("Copy results to clipboard!"), wxDefaultPosition, wxDefaultSize, 0 );	vSizer1->Add( m_wxbCopyResultsToClipboard, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5 );		m_wxbHelp = new wxButton( m_wxButtonsPanel, wxID_ANY, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );	vSizer1->Add( m_wxbHelp, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );		m_wxButtonsPanel->SetSizer( vSizer1 );	m_wxButtonsPanel->Layout();	vSizer1->Fit( m_wxButtonsPanel );	bSizer8->Add( m_wxButtonsPanel, 0, wxALIGN_RIGHT|wxLEFT|wxRIGHT|wxTOP, 5 );		m_wxpBandSelection = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );	wxBoxSizer* bSizer10;	bSizer10 = new wxBoxSizer( wxVERTICAL );		wxString m_wxrbBandSelectionChoices[] = { wxT("Lin"), wxT("A-weighted"), wxT("31.5 Hz"), wxT("63 Hz"), wxT("125 Hz"), wxT("250 Hz"), wxT("500 Hz"), wxT("1 KHz"), wxT("2 KHz"), wxT("4 KHz"), wxT("8 KHz"), wxT("16 KHz") };	int m_wxrbBandSelectionNChoices = sizeof( m_wxrbBandSelectionChoices ) / sizeof( wxString );	m_wxrbBandSelection = new wxRadioBox( m_wxpBandSelection, wxID_ANY, wxT("Octave Band Analysis"), wxDefaultPosition, wxDefaultSize, m_wxrbBandSelectionNChoices, m_wxrbBandSelectionChoices, 1, wxRA_SPECIFY_COLS );	m_wxrbBandSelection->SetSelection( 0 );	bSizer10->Add( m_wxrbBandSelection, 0, wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );		m_wxpBandSelection->SetSizer( bSizer10 );	m_wxpBandSelection->Layout();	bSizer10->Fit( m_wxpBandSelection );	bSizer8->Add( m_wxpBandSelection, 0, wxALIGN_RIGHT|wxLEFT|wxRIGHT, 5 );		mappa->Add( bSizer8, 0, 0, 5 );		bSizer1->Add( mappa, 1, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5 );		wxStaticBoxSizer* player;	player = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Video Player") ), wxHORIZONTAL );		wxString m_choice1Choices[] = { wxT("0.1x"), wxT("0.2x"), wxT("0.5x"), wxT("1x") };	int m_choice1NChoices = sizeof( m_choice1Choices ) / sizeof( wxString );	m_choice1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1NChoices, m_choice1Choices, 0 );	m_choice1->SetSelection( 0 );	player->Add( m_choice1, 0, wxALIGN_CENTER_VERTICAL, 5 );		m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Playback Speed"), wxDefaultPosition, wxDefaultSize, 0 );	m_staticText1->Wrap( -1 );	player->Add( m_staticText1, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 10 );		m_staticline6 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );	player->Add( m_staticline6, 0, wxEXPAND | wxALL, 5 );			player->Add( 0, 0, 0, 0, 5 );		m_buttonStop = new wxButton( this, wxID_ANY, wxT("Stop"), wxDefaultPosition, wxDefaultSize, 0 );	player->Add( m_buttonStop, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );		m_buttonPause = new wxButton( this, wxID_ANY, wxT("Pause"), wxDefaultPosition, wxDefaultSize, 0 );	player->Add( m_buttonPause, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );		m_buttonPlay = new wxButton( this, wxID_ANY, wxT("Play"), wxDefaultPosition, wxDefaultSize, 0 );	player->Add( m_buttonPlay, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );		m_textCtrlCurTime = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );	player->Add( m_textCtrlCurTime, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );		m_sliderVideoFrame = new wxSlider( this, wxID_ANY, 0, 1, 100, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS|wxSL_BOTTOM|wxSL_HORIZONTAL );	player->Add( m_sliderVideoFrame, 1, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP, 13 );		m_spinCtrlCurFrame = new wxSpinCtrl( this, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 100, 1 );	player->Add( m_spinCtrlCurFrame, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );		bSizer1->Add( player, 0, wxALIGN_BOTTOM|wxALL|wxEXPAND, 5 );		wxBoxSizer* opzioni;	opzioni = new wxBoxSizer( wxHORIZONTAL );			opzioni->Add( 0, 0, 1, wxEXPAND, 5 );		m_wxpColorMapOptions = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );	wxStaticBoxSizer* sbSizer2;	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_wxpColorMapOptions, wxID_ANY, wxT("ColorMap Options") ), wxVERTICAL );		wxFlexGridSizer* fgSizer1;	fgSizer1 = new wxFlexGridSizer( 2, 3, 0, 0 );	fgSizer1->SetFlexibleDirection( wxBOTH );	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );		m_staticText2 = new wxStaticText( m_wxpColorMapOptions, wxID_ANY, wxT("Scale Style"), wxDefaultPosition, wxDefaultSize, 0 );	m_staticText2->Wrap( -1 );	fgSizer1->Add( m_staticText2, 0, wxALL, 5 );		wxString m_wxcScaleStyleChoices[] = { wxT("Jet"), wxT("Hot"), wxT("Cold") };	int m_wxcScaleStyleNChoices = sizeof( m_wxcScaleStyleChoices ) / sizeof( wxString );	m_wxcScaleStyle = new wxChoice( m_wxpColorMapOptions, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_wxcScaleStyleNChoices, m_wxcScaleStyleChoices, 0 );	m_wxcScaleStyle->SetSelection( 0 );	fgSizer1->Add( m_wxcScaleStyle, 0, wxALL, 5 );			fgSizer1->Add( 10, 0, 1, wxEXPAND, 5 );		m_staticText5 = new wxStaticText( m_wxpColorMapOptions, wxID_ANY, wxT("Scale Unit:"), wxDefaultPosition, wxDefaultSize, 0 );	m_staticText5->Wrap( -1 );	fgSizer1->Add( m_staticText5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );		wxString m_wxcScaleUnitChoices[] = { wxT("Decibel [dB]"), wxT("Pressure [Pa]"), wxT("Square root [Pa^(1/2)]"), wxT("Cube root [Pa^(1/3)]") };	int m_wxcScaleUnitNChoices = sizeof( m_wxcScaleUnitChoices ) / sizeof( wxString );	m_wxcScaleUnit = new wxChoice( m_wxpColorMapOptions, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_wxcScaleUnitNChoices, m_wxcScaleUnitChoices, 0 );	m_wxcScaleUnit->SetSelection( 0 );	fgSizer1->Add( m_wxcScaleUnit, 0, wxALL, 5 );			fgSizer1->Add( 0, 0, 1, wxEXPAND, 5 );		sbSizer2->Add( fgSizer1, 1, 0, 5 );		m_wxpColorMapOptions->SetSizer( sbSizer2 );	m_wxpColorMapOptions->Layout();	sbSizer2->Fit( m_wxpColorMapOptions );	opzioni->Add( m_wxpColorMapOptions, 0, wxALIGN_LEFT|wxALL, 5 );			opzioni->Add( 0, 0, 1, wxEXPAND, 5 );		m_wxpSpecialOptions = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );	wxStaticBoxSizer* sbSizer3;	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( m_wxpSpecialOptions, wxID_ANY, wxT("Other Options") ), wxVERTICAL );		m_wxcbShowVirtMikes = new wxCheckBox( m_wxpSpecialOptions, wxID_ANY, wxT("Show virtual mikes positions"), wxDefaultPosition, wxDefaultSize, 0 );		sbSizer3->Add( m_wxcbShowVirtMikes, 0, wxEXPAND|wxLEFT|wxRIGHT, 5 );		m_wxcbSeparateBandAutoscale = new wxCheckBox( m_wxpSpecialOptions, wxID_ANY, wxT("Optimize color scale for the selected audio band (autoscale)"), wxDefaultPosition, wxDefaultSize, 0 );		sbSizer3->Add( m_wxcbSeparateBandAutoscale, 0, wxEXPAND|wxLEFT|wxRIGHT, 5 );		m_wxpSpecialOptions->SetSizer( sbSizer3 );	m_wxpSpecialOptions->Layout();	sbSizer3->Fit( m_wxpSpecialOptions );	opzioni->Add( m_wxpSpecialOptions, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );			opzioni->Add( 0, 0, 1, wxEXPAND, 5 );		m_wxpMousePointerData = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );	wxStaticBoxSizer* sbSizer4;	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( m_wxpMousePointerData, wxID_ANY, wxT("Mouse Pointer Data") ), wxVERTICAL );		wxFlexGridSizer* fgSizer2;	fgSizer2 = new wxFlexGridSizer( 3, 3, 0, 0 );	fgSizer2->SetFlexibleDirection( wxBOTH );	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );		m_wxtcXPosLabel = new wxTextCtrl( m_wxpMousePointerData, wxID_ANY, wxT("Azimuth:"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxNO_BORDER );	m_wxtcXPosLabel->SetMaxSize( wxSize( 70,-1 ) );		fgSizer2->Add( m_wxtcXPosLabel, 0, wxEXPAND|wxLEFT|wxTOP, 5 );		m_wxtcXPos = new wxTextCtrl( m_wxpMousePointerData, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 70,-1 ), wxTE_LEFT|wxTE_READONLY|wxNO_BORDER );	m_wxtcXPos->SetMinSize( wxSize( 70,-1 ) );	m_wxtcXPos->SetMaxSize( wxSize( 70,-1 ) );		fgSizer2->Add( m_wxtcXPos, 0, wxRIGHT|wxTOP, 5 );		m_wxtcXPosUnit = new wxTextCtrl( m_wxpMousePointerData, wxID_ANY, wxT("[Deg]"), wxDefaultPosition, wxSize( 50,-1 ), wxTE_CENTRE|wxTE_READONLY|wxNO_BORDER );	m_wxtcXPosUnit->SetMinSize( wxSize( 50,-1 ) );	m_wxtcXPosUnit->SetMaxSize( wxSize( 50,-1 ) );		fgSizer2->Add( m_wxtcXPosUnit, 0, wxALIGN_RIGHT|wxLEFT|wxRIGHT|wxTOP, 5 );		m_wxtcYPosLabel = new wxTextCtrl( m_wxpMousePointerData, wxID_ANY, wxT("Elevation:"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxNO_BORDER );	m_wxtcYPosLabel->SetMaxSize( wxSize( 70,-1 ) );		fgSizer2->Add( m_wxtcYPosLabel, 0, wxALL, 5 );		m_wxtcYPos = new wxTextCtrl( m_wxpMousePointerData, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 70,-1 ), wxTE_LEFT|wxTE_READONLY|wxNO_BORDER );	m_wxtcYPos->SetMinSize( wxSize( 70,-1 ) );	m_wxtcYPos->SetMaxSize( wxSize( 70,-1 ) );		fgSizer2->Add( m_wxtcYPos, 0, wxALL, 5 );		m_wxtcYPosUnit = new wxTextCtrl( m_wxpMousePointerData, wxID_ANY, wxT("[Deg]"), wxDefaultPosition, wxSize( 50,-1 ), wxTE_CENTRE|wxTE_READONLY|wxNO_BORDER );	m_wxtcYPosUnit->SetMinSize( wxSize( 50,-1 ) );	m_wxtcYPosUnit->SetMaxSize( wxSize( 50,-1 ) );		fgSizer2->Add( m_wxtcYPosUnit, 0, wxALL, 5 );		m_wxtcLevelLabel = new wxTextCtrl( m_wxpMousePointerData, wxID_ANY, wxT("Level:"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxNO_BORDER );	m_wxtcLevelLabel->SetMaxSize( wxSize( 70,-1 ) );		fgSizer2->Add( m_wxtcLevelLabel, 0, wxALL, 5 );		m_wxtcLevel = new wxTextCtrl( m_wxpMousePointerData, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 70,-1 ), wxTE_LEFT|wxTE_READONLY|wxNO_BORDER );	m_wxtcLevel->SetMinSize( wxSize( 70,-1 ) );	m_wxtcLevel->SetMaxSize( wxSize( 70,-1 ) );		fgSizer2->Add( m_wxtcLevel, 0, wxALL, 5 );		m_wxtcLevelUnit = new wxTextCtrl( m_wxpMousePointerData, wxID_ANY, wxT("[CBRT]"), wxDefaultPosition, wxSize( 50,-1 ), wxTE_CENTRE|wxTE_READONLY|wxNO_BORDER );	m_wxtcLevelUnit->SetMinSize( wxSize( 50,-1 ) );	m_wxtcLevelUnit->SetMaxSize( wxSize( 50,-1 ) );		fgSizer2->Add( m_wxtcLevelUnit, 0, wxALL, 5 );		sbSizer4->Add( fgSizer2, 1, wxEXPAND, 5 );		m_wxpMousePointerData->SetSizer( sbSizer4 );	m_wxpMousePointerData->Layout();	sbSizer4->Fit( m_wxpMousePointerData );	opzioni->Add( m_wxpMousePointerData, 0, wxALIGN_RIGHT|wxALL, 5 );			opzioni->Add( 0, 0, 1, wxEXPAND, 5 );		bSizer1->Add( opzioni, 0, wxALL|wxEXPAND, 5 );		this->SetSizer( bSizer1 );	this->Layout();		this->Centre( wxBOTH );		// Connect Events	m_wxbOk->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleDlg::OnOk ), NULL, this );	m_wxbCopyResultsToClipboard->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleDlg::OnCopyResultsToClipboard ), NULL, this );	m_wxbHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleDlg::OnHelp ), NULL, this );	m_wxrbBandSelection->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( MyModuleDlg::OnBandAnalysis ), NULL, this );	m_choice1->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyModuleDlg::OnChoiceFrameRate ), NULL, this );	m_buttonStop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleDlg::OnSTOPBtn ), NULL, this );	m_buttonPause->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleDlg::OnPAUSEBtn ), NULL, this );	m_buttonPlay->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleDlg::OnPLAYBtn ), NULL, this );	m_sliderVideoFrame->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyModuleDlg::OnSliderScroll ), NULL, this );	m_sliderVideoFrame->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyModuleDlg::OnSliderScroll ), NULL, this );	m_sliderVideoFrame->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyModuleDlg::OnSliderScroll ), NULL, this );	m_sliderVideoFrame->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyModuleDlg::OnSliderScroll ), NULL, this );	m_sliderVideoFrame->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyModuleDlg::OnSliderScroll ), NULL, this );	m_sliderVideoFrame->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyModuleDlg::OnSliderScroll ), NULL, this );	m_sliderVideoFrame->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyModuleDlg::OnSliderScroll ), NULL, this );	m_sliderVideoFrame->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyModuleDlg::OnSliderScroll ), NULL, this );	m_sliderVideoFrame->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyModuleDlg::OnSliderScroll ), NULL, this );	m_spinCtrlCurFrame->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( MyModuleDlg::OnSpinCurFrame ), NULL, this );	m_spinCtrlCurFrame->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MyModuleDlg::OnSpinCtrlTxt ), NULL, this );	m_wxcScaleStyle->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyModuleDlg::OnScaleStyle ), NULL, this );	m_wxcScaleUnit->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyModuleDlg::OnScaleUnit ), NULL, this );	m_wxcbShowVirtMikes->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyModuleDlg::OnShowVirtMikesPos ), NULL, this );	m_wxcbSeparateBandAutoscale->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyModuleDlg::OnSeparateBandAutoscale ), NULL, this );}MyModuleDlg::~MyModuleDlg(){	// Disconnect Events	m_wxbOk->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleDlg::OnOk ), NULL, this );	m_wxbCopyResultsToClipboard->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleDlg::OnCopyResultsToClipboard ), NULL, this );	m_wxbHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleDlg::OnHelp ), NULL, this );	m_wxrbBandSelection->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( MyModuleDlg::OnBandAnalysis ), NULL, this );	m_choice1->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyModuleDlg::OnChoiceFrameRate ), NULL, this );	m_buttonStop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleDlg::OnSTOPBtn ), NULL, this );	m_buttonPause->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleDlg::OnPAUSEBtn ), NULL, this );	m_buttonPlay->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleDlg::OnPLAYBtn ), NULL, this );	m_sliderVideoFrame->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyModuleDlg::OnSliderScroll ), NULL, this );	m_sliderVideoFrame->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyModuleDlg::OnSliderScroll ), NULL, this );	m_sliderVideoFrame->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyModuleDlg::OnSliderScroll ), NULL, this );	m_sliderVideoFrame->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyModuleDlg::OnSliderScroll ), NULL, this );	m_sliderVideoFrame->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyModuleDlg::OnSliderScroll ), NULL, this );	m_sliderVideoFrame->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyModuleDlg::OnSliderScroll ), NULL, this );	m_sliderVideoFrame->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyModuleDlg::OnSliderScroll ), NULL, this );	m_sliderVideoFrame->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyModuleDlg::OnSliderScroll ), NULL, this );	m_sliderVideoFrame->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyModuleDlg::OnSliderScroll ), NULL, this );	m_spinCtrlCurFrame->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( MyModuleDlg::OnSpinCurFrame ), NULL, this );	m_spinCtrlCurFrame->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MyModuleDlg::OnSpinCtrlTxt ), NULL, this );	m_wxcScaleStyle->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyModuleDlg::OnScaleStyle ), NULL, this );	m_wxcScaleUnit->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyModuleDlg::OnScaleUnit ), NULL, this );	m_wxcbShowVirtMikes->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyModuleDlg::OnShowVirtMikesPos ), NULL, this );	m_wxcbSeparateBandAutoscale->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyModuleDlg::OnSeparateBandAutoscale ), NULL, this );}MyModuleConfDlg::MyModuleConfDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style ){	this->SetSizeHints( wxDefaultSize, wxDefaultSize );		wxBoxSizer* bSizer16;	bSizer16 = new wxBoxSizer( wxVERTICAL );		m_panel7 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );	wxBoxSizer* bSizer17;	bSizer17 = new wxBoxSizer( wxVERTICAL );		m_staticText7 = new wxStaticText( m_panel7, wxID_ANY, wxT("Background image file:"), wxDefaultPosition, wxDefaultSize, 0 );	m_staticText7->Wrap( -1 );	bSizer17->Add( m_staticText7, 0, wxALIGN_LEFT|wxALIGN_TOP, 5 );		wxBoxSizer* bSizer18;	bSizer18 = new wxBoxSizer( wxHORIZONTAL );		m_wxtcBgndImagePath = new wxTextCtrl( m_panel7, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );	m_wxtcBgndImagePath->SetMinSize( wxSize( 410,-1 ) );		bSizer18->Add( m_wxtcBgndImagePath, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );		m_wxbBrowseBgndImage = new wxButton( m_panel7, wxID_ANY, wxT("Browse..."), wxDefaultPosition, wxDefaultSize, 0 );	bSizer18->Add( m_wxbBrowseBgndImage, 0, wxALL, 5 );		bSizer17->Add( bSizer18, 0, wxEXPAND, 5 );		m_panel7->SetSizer( bSizer17 );	m_panel7->Layout();	bSizer17->Fit( m_panel7 );	bSizer16->Add( m_panel7, 0, wxALIGN_CENTER|wxALL, 5 );		m_panel8 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );	wxStaticBoxSizer* sbSizer5;	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( m_panel8, wxID_ANY, wxT("Probe settings") ), wxVERTICAL );		wxBoxSizer* bSizer19;	bSizer19 = new wxBoxSizer( wxVERTICAL );		m_staticText8 = new wxStaticText( m_panel8, wxID_ANY, wxT("XML configuration file:"), wxDefaultPosition, wxDefaultSize, 0 );	m_staticText8->Wrap( -1 );	bSizer19->Add( m_staticText8, 0, wxLEFT|wxTOP, 5 );		wxBoxSizer* bSizer20;	bSizer20 = new wxBoxSizer( wxHORIZONTAL );		m_wxtcXMLConfigFilePath = new wxTextCtrl( m_panel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );	m_wxtcXMLConfigFilePath->SetMinSize( wxSize( 410,-1 ) );		bSizer20->Add( m_wxtcXMLConfigFilePath, 0, wxALL, 5 );		m_wxbBrowseXMLConfigFile = new wxButton( m_panel8, wxID_ANY, wxT("Browse..."), wxDefaultPosition, wxDefaultSize, 0 );	bSizer20->Add( m_wxbBrowseXMLConfigFile, 0, wxALL, 5 );		bSizer19->Add( bSizer20, 0, wxEXPAND, 5 );		sbSizer5->Add( bSizer19, 0, wxEXPAND, 5 );		m_wxpTable = new wxPanel( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );	wxBoxSizer* bSizer22;	bSizer22 = new wxBoxSizer( wxVERTICAL );		wxBoxSizer* m_wxbsHeadersCheck;	m_wxbsHeadersCheck = new wxBoxSizer( wxHORIZONTAL );		m_wxstHeadersCheckLabel = new wxStaticText( m_wxpTable, wxID_ANY, wxT("Headers check:"), wxDefaultPosition, wxDefaultSize, 0 );	m_wxstHeadersCheckLabel->Wrap( -1 );	m_wxbsHeadersCheck->Add( m_wxstHeadersCheckLabel, 0, wxBOTTOM|wxRIGHT|wxTOP, 5 );		m_wxstHeadersCheck = new wxStaticText( m_wxpTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );	m_wxstHeadersCheck->Wrap( -1 );	m_wxbsHeadersCheck->Add( m_wxstHeadersCheck, 0, wxBOTTOM|wxTOP, 5 );		bSizer22->Add( m_wxbsHeadersCheck, 0, wxEXPAND, 5 );		wxBoxSizer* bSizer25;	bSizer25 = new wxBoxSizer( wxHORIZONTAL );		m_wxstMicNameLabel = new wxStaticText( m_wxpTable, wxID_ANY, wxT("Mic name:"), wxDefaultPosition, wxDefaultSize, 0 );	m_wxstMicNameLabel->Wrap( -1 );	bSizer25->Add( m_wxstMicNameLabel, 0, wxALL, 5 );		m_wxstMicName = new wxStaticText( m_wxpTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );	m_wxstMicName->Wrap( -1 );	bSizer25->Add( m_wxstMicName, 0, wxALL, 5 );		bSizer22->Add( bSizer25, 0, wxEXPAND, 5 );		wxBoxSizer* bSizer251;	bSizer251 = new wxBoxSizer( wxHORIZONTAL );		m_wxstManufacturerLabel = new wxStaticText( m_wxpTable, wxID_ANY, wxT("Manufacturer:"), wxDefaultPosition, wxDefaultSize, 0 );	m_wxstManufacturerLabel->Wrap( -1 );	bSizer251->Add( m_wxstManufacturerLabel, 0, wxALL, 5 );		m_wxstManufacturer = new wxStaticText( m_wxpTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );	m_wxstManufacturer->Wrap( -1 );	bSizer251->Add( m_wxstManufacturer, 0, wxALL, 5 );		bSizer22->Add( bSizer251, 1, wxEXPAND, 5 );		wxBoxSizer* bSizer252;	bSizer252 = new wxBoxSizer( wxHORIZONTAL );		m_wxstArrayTypeLabel = new wxStaticText( m_wxpTable, wxID_ANY, wxT("Array type:"), wxDefaultPosition, wxDefaultSize, 0 );	m_wxstArrayTypeLabel->Wrap( -1 );	bSizer252->Add( m_wxstArrayTypeLabel, 0, wxALL, 5 );		m_wxstArrayType = new wxStaticText( m_wxpTable, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );	m_wxstArrayType->Wrap( -1 );	bSizer252->Add( m_wxstArrayType, 0, wxALL, 5 );		bSizer22->Add( bSizer252, 1, wxEXPAND, 5 );		m_wxpTable->SetSizer( bSizer22 );	m_wxpTable->Layout();	bSizer22->Fit( m_wxpTable );	sbSizer5->Add( m_wxpTable, 1, wxALIGN_LEFT|wxALL|wxEXPAND, 0 );		m_panel8->SetSizer( sbSizer5 );	m_panel8->Layout();	sbSizer5->Fit( m_panel8 );	bSizer16->Add( m_panel8, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );		m_panel12 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );	wxStaticBoxSizer* sbSizer6;	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( m_panel12, wxID_ANY, wxT("Transparency") ), wxHORIZONTAL );		m_wxsldTransparency = new wxSlider( m_panel12, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );	sbSizer6->Add( m_wxsldTransparency, 1, wxALIGN_CENTER|wxALL, 5 );		m_wxscTransparency = new wxSpinCtrl( m_panel12, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 50 );	sbSizer6->Add( m_wxscTransparency, 0, wxALIGN_CENTER|wxALL, 5 );		m_staticText50 = new wxStaticText( m_panel12, wxID_ANY, wxT("%"), wxDefaultPosition, wxDefaultSize, 0 );	m_staticText50->Wrap( -1 );	sbSizer6->Add( m_staticText50, 0, wxALIGN_CENTER|wxALL, 5 );		m_panel12->SetSizer( sbSizer6 );	m_panel12->Layout();	sbSizer6->Fit( m_panel12 );	bSizer16->Add( m_panel12, 0, wxALL|wxEXPAND, 10 );		wxGridSizer* gSizer1;	gSizer1 = new wxGridSizer( 2, 2, 0, 0 );		m_panel10 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );	wxFlexGridSizer* fgSizer4;	fgSizer4 = new wxFlexGridSizer( 2, 4, 0, 0 );	fgSizer4->SetFlexibleDirection( wxBOTH );	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );		m_staticText104 = new wxStaticText( m_panel10, wxID_ANY, wxT("   Peak SPL value corresponding to FS:"), wxDefaultPosition, wxDefaultSize, 0 );	m_staticText104->Wrap( -1 );	fgSizer4->Add( m_staticText104, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );			fgSizer4->Add( 20, 0, 1, wxEXPAND, 5 );		m_wxtcFS = new wxTextCtrl( m_panel10, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 45,25 ), wxTE_CENTRE );	fgSizer4->Add( m_wxtcFS, 0, wxALL, 5 );		m_staticText105 = new wxStaticText( m_panel10, wxID_ANY, wxT("dB"), wxDefaultPosition, wxDefaultSize, 0 );	m_staticText105->Wrap( -1 );	fgSizer4->Add( m_staticText105, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );		m_staticText1041 = new wxStaticText( m_panel10, wxID_ANY, wxT("   Minimum SPL treshold:"), wxDefaultPosition, wxDefaultSize, 0 );	m_staticText1041->Wrap( -1 );	fgSizer4->Add( m_staticText1041, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );			fgSizer4->Add( 20, 0, 1, wxEXPAND, 5 );		m_wxtcMinSPL = new wxTextCtrl( m_panel10, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 45,25 ), wxTE_CENTRE );	fgSizer4->Add( m_wxtcMinSPL, 0, wxALL, 5 );		m_staticText1051 = new wxStaticText( m_panel10, wxID_ANY, wxT("dB"), wxDefaultPosition, wxDefaultSize, 0 );	m_staticText1051->Wrap( -1 );	fgSizer4->Add( m_staticText1051, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );		m_panel10->SetSizer( fgSizer4 );	m_panel10->Layout();	fgSizer4->Fit( m_panel10 );	gSizer1->Add( m_panel10, 0, wxALL, 5 );		m_panel101 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );	wxFlexGridSizer* fgSizer41;	fgSizer41 = new wxFlexGridSizer( 3, 4, 0, 0 );	fgSizer41->SetFlexibleDirection( wxBOTH );	fgSizer41->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );		m_staticText1042 = new wxStaticText( m_panel101, wxID_ANY, wxT("Frame length:"), wxDefaultPosition, wxDefaultSize, 0 );	m_staticText1042->Wrap( -1 );	fgSizer41->Add( m_staticText1042, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );			fgSizer41->Add( 20, 0, 1, wxEXPAND, 5 );		m_wxtcFLength = new wxTextCtrl( m_panel101, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 45,25 ), wxTE_CENTRE );	fgSizer41->Add( m_wxtcFLength, 0, wxALL, 5 );		m_staticText1052 = new wxStaticText( m_panel101, wxID_ANY, wxT("sec.   "), wxDefaultPosition, wxDefaultSize, 0 );	m_staticText1052->Wrap( -1 );	fgSizer41->Add( m_staticText1052, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );		m_staticText10411 = new wxStaticText( m_panel101, wxID_ANY, wxT("Frame overlap:"), wxDefaultPosition, wxDefaultSize, 0 );	m_staticText10411->Wrap( -1 );	fgSizer41->Add( m_staticText10411, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );			fgSizer41->Add( 20, 0, 1, wxEXPAND, 5 );		m_wxtcFOvlp = new wxTextCtrl( m_panel101, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 45,25 ), wxTE_CENTRE );	fgSizer41->Add( m_wxtcFOvlp, 0, wxALL, 5 );		m_staticText10511 = new wxStaticText( m_panel101, wxID_ANY, wxT("%"), wxDefaultPosition, wxDefaultSize, 0 );	m_staticText10511->Wrap( -1 );	fgSizer41->Add( m_staticText10511, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );		m_staticText23 = new wxStaticText( m_panel101, wxID_ANY, wxT("Total number of frames: "), wxDefaultPosition, wxDefaultSize, 0 );	m_staticText23->Wrap( -1 );	fgSizer41->Add( m_staticText23, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );			fgSizer41->Add( 0, 0, 1, wxEXPAND, 5 );		m_wxstTotFrames = new wxStaticText( m_panel101, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );	m_wxstTotFrames->Wrap( -1 );	fgSizer41->Add( m_wxstTotFrames, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );		m_panel101->SetSizer( fgSizer41 );	m_panel101->Layout();	fgSizer41->Fit( m_panel101 );	gSizer1->Add( m_panel101, 0, wxALIGN_RIGHT|wxALL, 5 );		bSizer16->Add( gSizer1, 0, 0, 5 );		m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );	bSizer16->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );		m_pButtonsPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );	wxBoxSizer* bSizer44;	bSizer44 = new wxBoxSizer( wxHORIZONTAL );		m_wxbHelp = new wxButton( m_pButtonsPanel, wxID_ANY, wxT("Help"), wxDefaultPosition, wxDefaultSize, 0 );	bSizer44->Add( m_wxbHelp, 0, wxALIGN_CENTER_VERTICAL|wxALL, 10 );			bSizer44->Add( 0, 0, 1, 0, 5 );		m_wxbCancel = new wxButton( m_pButtonsPanel, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );	bSizer44->Add( m_wxbCancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 10 );		m_wxbOk = new wxButton( m_pButtonsPanel, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );	bSizer44->Add( m_wxbOk, 0, wxALIGN_CENTER_VERTICAL|wxALL, 10 );		m_pButtonsPanel->SetSizer( bSizer44 );	m_pButtonsPanel->Layout();	bSizer44->Fit( m_pButtonsPanel );	bSizer16->Add( m_pButtonsPanel, 0, wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );		this->SetSizer( bSizer16 );	this->Layout();	bSizer16->Fit( this );		this->Centre( wxBOTH );		// Connect Events	m_wxbBrowseBgndImage->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleConfDlg::OnBrowseBGND ), NULL, this );	m_wxbBrowseXMLConfigFile->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleConfDlg::OnBrowseXML ), NULL, this );	m_wxsldTransparency->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyModuleConfDlg::OnSlideTransparency ), NULL, this );	m_wxsldTransparency->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyModuleConfDlg::OnSlideTransparency ), NULL, this );	m_wxsldTransparency->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyModuleConfDlg::OnSlideTransparency ), NULL, this );	m_wxsldTransparency->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyModuleConfDlg::OnSlideTransparency ), NULL, this );	m_wxsldTransparency->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyModuleConfDlg::OnSlideTransparency ), NULL, this );	m_wxsldTransparency->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyModuleConfDlg::OnSlideTransparency ), NULL, this );	m_wxsldTransparency->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyModuleConfDlg::OnSlideTransparency ), NULL, this );	m_wxsldTransparency->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyModuleConfDlg::OnSlideTransparency ), NULL, this );	m_wxsldTransparency->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyModuleConfDlg::OnSlideTransparency ), NULL, this );	m_wxscTransparency->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( MyModuleConfDlg::OnSpinTransArrow ), NULL, this );	m_wxscTransparency->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MyModuleConfDlg::OnSpinTransText ), NULL, this );	m_wxtcFS->Connect( wxEVT_CHAR, wxKeyEventHandler( MyModuleConfDlg::FSOnChar ), NULL, this );	m_wxtcFS->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( MyModuleConfDlg::FSKillFocus ), NULL, this );	m_wxtcFS->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( MyModuleConfDlg::FSOnFocus ), NULL, this );	m_wxtcMinSPL->Connect( wxEVT_CHAR, wxKeyEventHandler( MyModuleConfDlg::MinSPLOnChar ), NULL, this );	m_wxtcMinSPL->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( MyModuleConfDlg::MinSPLKillFocus ), NULL, this );	m_wxtcMinSPL->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( MyModuleConfDlg::MinSPLOnFocus ), NULL, this );	m_wxtcFLength->Connect( wxEVT_CHAR, wxKeyEventHandler( MyModuleConfDlg::FLengthOnChar ), NULL, this );	m_wxtcFLength->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( MyModuleConfDlg::FLengthKillFocus ), NULL, this );	m_wxtcFLength->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( MyModuleConfDlg::FLengthOnFocus ), NULL, this );	m_wxtcFOvlp->Connect( wxEVT_CHAR, wxKeyEventHandler( MyModuleConfDlg::FOvlpOnChar ), NULL, this );	m_wxtcFOvlp->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( MyModuleConfDlg::FOvlpKillFocus ), NULL, this );	m_wxtcFOvlp->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( MyModuleConfDlg::FOvlpOnFocus ), NULL, this );	m_wxbHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleConfDlg::OnHelp ), NULL, this );	m_wxbCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleConfDlg::OnCancel ), NULL, this );	m_wxbOk->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleConfDlg::OnOk ), NULL, this );}MyModuleConfDlg::~MyModuleConfDlg(){	// Disconnect Events	m_wxbBrowseBgndImage->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleConfDlg::OnBrowseBGND ), NULL, this );	m_wxbBrowseXMLConfigFile->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleConfDlg::OnBrowseXML ), NULL, this );	m_wxsldTransparency->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyModuleConfDlg::OnSlideTransparency ), NULL, this );	m_wxsldTransparency->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyModuleConfDlg::OnSlideTransparency ), NULL, this );	m_wxsldTransparency->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyModuleConfDlg::OnSlideTransparency ), NULL, this );	m_wxsldTransparency->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyModuleConfDlg::OnSlideTransparency ), NULL, this );	m_wxsldTransparency->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyModuleConfDlg::OnSlideTransparency ), NULL, this );	m_wxsldTransparency->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyModuleConfDlg::OnSlideTransparency ), NULL, this );	m_wxsldTransparency->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyModuleConfDlg::OnSlideTransparency ), NULL, this );	m_wxsldTransparency->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyModuleConfDlg::OnSlideTransparency ), NULL, this );	m_wxsldTransparency->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyModuleConfDlg::OnSlideTransparency ), NULL, this );	m_wxscTransparency->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( MyModuleConfDlg::OnSpinTransArrow ), NULL, this );	m_wxscTransparency->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MyModuleConfDlg::OnSpinTransText ), NULL, this );	m_wxtcFS->Disconnect( wxEVT_CHAR, wxKeyEventHandler( MyModuleConfDlg::FSOnChar ), NULL, this );	m_wxtcFS->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( MyModuleConfDlg::FSKillFocus ), NULL, this );	m_wxtcFS->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( MyModuleConfDlg::FSOnFocus ), NULL, this );	m_wxtcMinSPL->Disconnect( wxEVT_CHAR, wxKeyEventHandler( MyModuleConfDlg::MinSPLOnChar ), NULL, this );	m_wxtcMinSPL->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( MyModuleConfDlg::MinSPLKillFocus ), NULL, this );	m_wxtcMinSPL->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( MyModuleConfDlg::MinSPLOnFocus ), NULL, this );	m_wxtcFLength->Disconnect( wxEVT_CHAR, wxKeyEventHandler( MyModuleConfDlg::FLengthOnChar ), NULL, this );	m_wxtcFLength->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( MyModuleConfDlg::FLengthKillFocus ), NULL, this );	m_wxtcFLength->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( MyModuleConfDlg::FLengthOnFocus ), NULL, this );	m_wxtcFOvlp->Disconnect( wxEVT_CHAR, wxKeyEventHandler( MyModuleConfDlg::FOvlpOnChar ), NULL, this );	m_wxtcFOvlp->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( MyModuleConfDlg::FOvlpKillFocus ), NULL, this );	m_wxtcFOvlp->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( MyModuleConfDlg::FOvlpOnFocus ), NULL, this );	m_wxbHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleConfDlg::OnHelp ), NULL, this );	m_wxbCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleConfDlg::OnCancel ), NULL, this );	m_wxbOk->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyModuleConfDlg::OnOk ), NULL, this );}MyEditWatchPointsDlg::MyEditWatchPointsDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style ){	this->SetSizeHints( wxDefaultSize, wxDefaultSize );		wxBoxSizer* bSizer45;	bSizer45 = new wxBoxSizer( wxHORIZONTAL );		m_wxlcWatchpoints = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_SINGLE_SEL );	m_wxlcWatchpoints->SetMinSize( wxSize( 170,300 ) );		bSizer45->Add( m_wxlcWatchpoints, 0, wxALL, 5 );		wxBoxSizer* bSizer46;	bSizer46 = new wxBoxSizer( wxVERTICAL );		m_wxbOk = new wxButton( this, wxID_ANY, wxT("Ok, close."), wxDefaultPosition, wxDefaultSize, 0 );	bSizer46->Add( m_wxbOk, 0, wxALL|wxEXPAND, 5 );		m_wxbCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );	bSizer46->Add( m_wxbCancel, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );			bSizer46->Add( 0, 0, 1, wxEXPAND, 5 );		m_wxbRemove = new wxButton( this, wxID_ANY, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );	bSizer46->Add( m_wxbRemove, 0, wxALL|wxEXPAND, 5 );		m_wxbEditLabel = new wxButton( this, wxID_ANY, wxT("Edit Label..."), wxDefaultPosition, wxDefaultSize, 0 );	bSizer46->Add( m_wxbEditLabel, 0, wxBOTTOM|wxLEFT|wxRIGHT, 5 );		bSizer45->Add( bSizer46, 1, wxEXPAND, 5 );		this->SetSizer( bSizer45 );	this->Layout();	bSizer45->Fit( this );		this->Centre( wxBOTH );}MyEditWatchPointsDlg::~MyEditWatchPointsDlg(){}