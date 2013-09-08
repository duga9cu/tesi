/**********************************************************************
 
 Audacity: A Digital Audio Editor
 
 Microphone Array Analyzer
 
 gui.cpp
 
 Luca Novarini
 
 **********************************************************************/


#include <wx/wx.h>
#include <Audacity.h>
#include <SampleFormat.h>
#include <Sequence.h>
#include <wx/filename.h>
#include "gui.h"
#include "myartprovider.h"
#include <wx/dcclient.h>
#include <math.h>          //Required by ColorMap functions
#include <stdlib.h>        //Required by ColorMap functions
#include <wx/dcbuffer.h>
#include <wx/clipbrd.h>    //Used to copy bitmap to the clipboard
#include <wx/msgdlg.h>
#include <wx/string.h>



// -----------------------------------------------------------
// MicArrayAnalyzer Configuration Dialog
// -----------------------------------------------------------
MicArrayAnalyzerConfDlg::MicArrayAnalyzerConfDlg( wxWindow* parent, MicArrayAnalyzer *maa ) : MyModuleConfDlg(parent), mMAA(maa), bBgndImage(false), bHeaders(false), bLength(false), bVirtMikes(false), bProjRate(false), bProjBits(false), bProjChannels(false)
{
	updating=0;
	IsAllOKCheck();
	wxString buffer;
	//buffer.Printf(_("%d"),(int)mMAA->GetProjSampleRate());   //Retrieving Project Sample Rate
//	m_wxstProjRate->SetLabel(	buffer);
//	buffer.Printf(_("%d"),(int)mMAA->GetProjNumTracks());   //Retrieving Project Number of Traks
//	m_wxstProjChannels->SetLabel(buffer);
//	
//	switch (mMAA->GetProjSampleFormat()) //see SampleFormat.h to understand cases.
//	{
//		case int16Sample:
//			m_wxstProjSampleFormat->SetLabel(_("16-bit PCM"));
//			break;
//		case int24Sample:
//			m_wxstProjSampleFormat->SetLabel(_("24-bit PCM"));
//			break;
//		case floatSample:
//			m_wxstProjSampleFormat->SetLabel(_("32-bit float"));
//			break;
//		default:
//			m_wxstProjSampleFormat->SetLabel(_("32-bit float"));
//	}
	
	InitArtProvider(); //Init of the MyArtProvider, used to get icons!
	
	this->Connect(wxEVT_PAINT, wxPaintEventHandler(MicArrayAnalyzerConfDlg::OnPaint));
	
	//	buffer.Printf(_("%3.1f"),MIN_SPL_DEFAULT);
	//	m_wxtcMinSPL->SetValue(buffer);
	//	buffer.Printf(_("%3.1f"),FS_DEFAULT);
	//	m_wxtcFS->SetValue(buffer);
	//	buffer.Printf(_("%1.3f"),mMAA->GetFrameLength());
	//	m_wxtcFLength->SetValue(buffer);
	//	buffer.Printf(_("%3.2f"),mMAA->GetFrameOverlapRatio()*100);
	//	m_wxtcFOvlp->SetValue(buffer);
	
	//______________________________________________________
	//_________ remember values from last time _____________
	wxString str;
	const wxString emptystring = _("");
	
	buffer.Printf(_("/MicArrayAnalyzer/Conf/BackgroundImage"));
	m_Conf.Read(buffer, &str, emptystring);
	m_wxtcBgndImagePath->SetValue(str);
//	mMAA->SetBgndImage(str);
	mMAA->SetBgndVideo(str);
	bBgndImage = true;
	
	buffer.Printf(_("/MicArrayAnalyzer/Conf/XMLfile"));
	if(m_Conf.Read(buffer, &str, emptystring)) {
		mMAA->SetXMLFile(str);	
		m_wxtcXMLConfigFilePath->SetValue(str);
		ParseXML();
	}
	m_wxtcXMLConfigFilePath->SetValue(str);
	
	
	double d;
	
	buffer.Printf(_("/MicArrayAnalyzer/Conf/Transparency"));
	m_Conf.Read(buffer, &d, TRANSPARENCY);
	//	buffer.Printf(_("%d"),d);
	updating=2;
	m_wxscTransparency->SetValue(d);
	m_wxsldTransparency->SetValue(d);
	mMAA->SetTransparency(d);
	
	buffer.Printf(_("/MicArrayAnalyzer/Conf/SPLthreshold"));
	m_Conf.Read(buffer, &d, MIN_SPL_DEFAULT);
	buffer.Printf(_("%.1f"),d);
	m_wxtcMinSPL->SetValue(buffer);
	mMAA->SetMinSPLThreshold(d);
	
	buffer.Printf(_("/MicArrayAnalyzer/Conf/FSLevel"));
	m_Conf.Read(buffer, &d, FS_DEFAULT);
	buffer.Printf(_("%.1f"),d);
	m_wxtcFS->SetValue(buffer);
	mMAA->SetFSLevel(d);
	
	buffer.Printf(_("/MicArrayAnalyzer/Conf/FrameLength"));
	m_Conf.Read(buffer, &d, FRAMELENGTH);
	buffer.Printf(_("%.3f"),d);
	m_wxtcFLength->SetValue(buffer);
	mMAA->SetFrameLength(d);
	
	buffer.Printf(_("/MicArrayAnalyzer/Conf/FrameOverlapRatio"));
	m_Conf.Read(buffer, &d, FRAMEOVERLAP*100);
	buffer.Printf(_("%.1f"),d);
	m_wxtcFOvlp->SetValue(buffer);
	mMAA->SetFrameOverlapRatio(d/100);
	
	IsAllOKCheck();
	
	str.Printf(_("%d"),mMAA->GetAudioTrackLength()/(mMAA->GetFrameLengthSmpl()-mMAA->GetFrameOverlapSmpl()));
	m_wxstTotFrames->SetLabel(str);
}

MicArrayAnalyzerConfDlg::~MicArrayAnalyzerConfDlg()
{
	if (bHeaders) { delete wxsbHeadersCheck; }
}

void MicArrayAnalyzerConfDlg::OnBrowseBGND(wxCommandEvent& event) //Video version
{
	wxFileDialog* wxfdOpenFileDialog = 
					new wxFileDialog(this,
									 _("Open background file..."),
									 _(""),_(""),
									 _("All compatible types (*.mpg;*.mpeg;*.bmp;*.dib;*.gif;*.jpg;*.jpeg;*.jpe;*.jif;*.jfif;*.jfi;*.pcx;*.png;*.pnm;*.tif;*.tiff;*.xpm;*.xbm)|*.mpg;*.mpeg;*.bmp;*.dib;*.gif;*.jpg;*.jpeg;*.jpe;*.jif;*.jfif;*.jfi;*.pcx;*.png;*.pnm;*.tif;*.tiff;*.xpm;*.xbm|MPEG (P6) video (*.mpg;*.mpeg)|*.mpg;*.mpeg|Bitmap image (*.bmp;*.dib)|*.bmp;*.dib|GIF image (*.gif)|*.gif|JPEG image (*.jpg;*.jpeg;*.jpe;*.jif;*.jfif;*.jfi)|*.jpg;*.jpeg;*.jpe;*.jif;*.jfif;*.jfi|PCX image (*.pcx)|*.pcx|PNG image (*.png)|*.png|PNM image (*.pnm)|*.pnm|TIFF image (*.tif;*.tiff)|*.tif;*.tiff|XPM image (*.xpm)|*.xpm|XBM image (*.xbm)|*.xbm"),wxFD_OPEN);
	if (wxfdOpenFileDialog->ShowModal() == wxID_OK)
	{
		m_wxtcBgndImagePath->SetValue(_("Opening in progress, please wait..."));
//		if (mMAA->SetBgndImage(wxfdOpenFileDialog->GetPath()))
		if (mMAA->SetBgndVideo(wxfdOpenFileDialog->GetPath()))
		{
			m_wxtcBgndImagePath->SetValue(wxfdOpenFileDialog->GetPath());
			bBgndImage = true;
		}
		else
		{
			m_wxtcBgndImagePath->SetValue(_("An ERROR has occurred while opening image file..."));
			bBgndImage = false;
		}
	}
	
	IsAllOKCheck(); //Check if OK button could be enabled.
}

//void MicArrayAnalyzerConfDlg::OnBrowseBGND(wxCommandEvent& event)  //IMAGE VERSION
//{
//	wxFileDialog* wxfdOpenFileDialog = 
//	new wxFileDialog(this,
//					 _("Open background file..."),
//					 _(""),_(""),
//					 _("All compatible types (*.bmp;*.dib;*.gif;*.jpg;*.jpeg;*.jpe;*.jif;*.jfif;*.jfi;*.pcx;*.png;*.pnm;*.tif;*.tiff;*.xpm;*.xbm)|*.bmp;*.dib;*.gif;*.jpg;*.jpeg;*.jpe;*.jif;*.jfif;*.jfi;*.pcx;*.png;*.pnm;*.tif;*.tiff;*.xpm;*.xbm|Bitmap image (*.bmp;*.dib)|*.bmp;*.dib|GIF image (*.gif)|*.gif|JPEG image (*.jpg;*.jpeg;*.jpe;*.jif;*.jfif;*.jfi)|*.jpg;*.jpeg;*.jpe;*.jif;*.jfif;*.jfi|PCX image (*.pcx)|*.pcx|PNG image (*.png)|*.png|PNM image (*.pnm)|*.pnm|TIFF image (*.tif;*.tiff)|*.tif;*.tiff|XPM image (*.xpm)|*.xpm|XBM image (*.xbm)|*.xbm"),wxFD_OPEN);
//	if (wxfdOpenFileDialog->ShowModal() == wxID_OK)
//	{
//		m_wxtcBgndImagePath->SetValue(_("Opening in progress, please wait..."));
//			if (mMAA->SetBgndImage(wxfdOpenFileDialog->GetPath()))
//		{
//			m_wxtcBgndImagePath->SetValue(wxfdOpenFileDialog->GetPath());
//			bBgndImage = true;
//		}
//		else
//		{
//			m_wxtcBgndImagePath->SetValue(_("An ERROR has occurred while opening image file..."));
//			bBgndImage = false;
//		}
//	}
//	
//	IsAllOKCheck(); //Check if OK button could be enabled.
//}

void MicArrayAnalyzerConfDlg::ParseXML() 
{
	if (mMAA->BadXML())
	{
		// Handling two cases: (1) bad XML header, (2) good XML header but the XML doesn't hold mic array data.
		//m_wxsbHeadersCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("cross_icon")));
		m_wxstHeadersCheck->SetLabel(_("Bad XML header or not a Mic Array Configuration file"));
		SetHeadersCheckIcon(_("cross_icon"));
		bHeaders = true;
	}		
	else
	{
		mMAA->ReadXMLData(); //So, at least the XML seems ok. Reading data!
		EnableTable(); //Enabling the xml/wav/project data table
		
		//Filling **ONLY** XML fields of the data table
		wxString buffer;
		m_wxstMicName->SetLabel(mMAA->GetMicName());
		m_wxstManufacturer->SetLabel(mMAA->GetManufacturer());
		if (mMAA->GetArrayType() == 0) m_wxstArrayType->SetLabel(_("Spherical"));
		else { m_wxstArrayType->SetLabel(_("Planar")); }
		
		//buffer.Printf(_("%d"),mMAA->GetDeconvIRsLength());
		//			m_wxstXMLLength->SetLabel(buffer);
		//			buffer.Printf(_("%d"),mMAA->GetCapsulesNumber());
		//			m_wxstXMLCapsules->SetLabel(buffer);
		//			m_wxstXMLCapsules2->SetLabel(buffer);
		//			buffer.Printf(_("%d"),mMAA->GetVirtualMikes());         
		//			m_wxstXMLVirtual->SetLabel(buffer);
		//			
		
		//Here we can check if XML <-> PROJECT values are matched and set icons
		/* To do.... */
		
		if (mMAA->BadWAV())
		{
			// Handling bad wav file header error
			m_wxstHeadersCheck->SetLabel(_("Bad deconv. IRs WAV file header or file not found"));
			SetHeadersCheckIcon(_("cross_icon"));
			bHeaders = true;
			wxMessageBox(_("Bad deconv. IRs WAV file header or file not found"),_("Error"),wxOK|wxICON_ERROR);
			
		}
		else
		{
			// Everything SEEMS allright...
			m_wxstHeadersCheck->SetLabel(_("XML Header OK, WAV Header OK"));
			SetHeadersCheckIcon(_("check_icon"));
			bHeaders = true;
			
			//Filling data table with WAV data.
			//buffer.Printf(_("%d"),mMAA->GetWAVLength());
			//				m_wxstWAVLength->SetLabel(buffer);
			//				m_wxstWAVFormat->SetLabel(mMAA->GetWAVFormatName());
			//				buffer.Printf(_("%d"),mMAA->GetWAVSampleRate());
			//				m_wxstWAVfsample->SetLabel(buffer);
			//				buffer.Printf(_("%d"),mMAA->GetWAVChannels());
			//				m_wxstWAVChannels->SetLabel(buffer);
			//		
			
			
			//Now we can set XML <-> WAV and WAV <-> PROJECT icons too!
			bool errorFound = false;
			if ((mMAA->GetDeconvIRsLength() * mMAA->GetCapsulesNumber()) == mMAA->GetWAVLength())
			{
				//					m_wxsbLengthCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("check_icon")));
				bLength = true;
				//					m_wxsbLengthCheck->SetToolTip(wxEmptyString);
			}
			else
			{
				//					m_wxsbLengthCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("cross_icon")));
				bLength = false;
				//					m_wxsbLengthCheck->SetToolTip(_("XML and WAV files not matched!\nNote that No. of capsules multiplied by deconvolution IRs length should be equal to WAV file total length."));
				wxMessageBox(_("XML and WAV files not matched!\nNote that No. of capsules multiplied by deconvolution IRs length should be equal to WAV file total length."),_("Error"),wxOK|wxICON_ERROR);
				errorFound=true;
			}
			
			if (mMAA->GetVirtualMikes() == mMAA->GetWAVChannels())
			{
				//					m_wxsbWAVChannelsCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("check_icon")));
				bVirtMikes = true;
				//					m_wxsbWAVChannelsCheck->SetToolTip(wxEmptyString);
			}
			else
			{
				//					m_wxsbWAVChannelsCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("cross_icon")));
				bVirtMikes = false;
				//					m_wxsbWAVChannelsCheck->SetToolTip(_("XML and WAV files not matched!\nNote that No. of virtual mikes should be equal to No. of WAV file channels."));
				wxMessageBox(_("XML and WAV files not matched!\nNote that No. of virtual mikes should be equal to No. of WAV file channels."),_("Error"),wxOK|wxICON_ERROR);
				errorFound=true;
			}
			
			if (mMAA->GetCapsulesNumber() == mMAA->GetProjNumTracks())
			{
				//					m_wxsbProjChannelsCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("check_icon")));
				bProjChannels = true;
				//					m_wxsbProjChannelsCheck->SetToolTip(wxEmptyString);
			}
			else
			{
				//					m_wxsbProjChannelsCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("cross_icon")));
				bProjChannels = false;
				//					m_wxsbProjChannelsCheck->SetToolTip(_("XML doesn't match Audacity project!\nNote that No. of array capsules should be equal to No. of project tracks."));
				wxMessageBox(_("XML doesn't match Audacity project!\nNote that No. of array capsules should be equal to No. of project tracks."),_("Error"),wxOK|wxICON_ERROR);
				errorFound=true;
			}
			
			if (mMAA->GetWAVSampleRate() == (int)mMAA->GetProjSampleRate())
			{
				//					m_wxsbRateCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("check_icon")));
				bProjRate = true;
				//					m_wxsbRateCheck->SetToolTip(wxEmptyString);
			}
			else
			{
				//					m_wxsbRateCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("cross_icon")));
				bProjRate = false;
				//					m_wxsbRateCheck->SetToolTip(_("WAV doesn't match Audacity project!\nSample rates should be the same."));
				wxMessageBox(_("WAV doesn't match Audacity project!\nSample rates should be the same."),_("Error"),wxOK|wxICON_ERROR);
				errorFound=true;
			}
			
			if (mMAA->GetWAVSampleFormat() == mMAA->GetProjSampleFormat())
			{
				//					m_wxsbSampleFormatCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("check_icon")));
				bProjBits = true;
				//					m_wxsbSampleFormatCheck->SetToolTip(wxEmptyString);
			}
			else
			{
				//					m_wxsbSampleFormatCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("warning_icon")));
				bProjBits = false;
				//					m_wxsbSampleFormatCheck->SetToolTip(_("WAV doesn't match Audacity project!\nSample formats are different. However that's just a warning, you can continue anyway."));
				wxMessageBox(_("WAV doesn't match Audacity project!\nSample formats are different. However that's just a warning, you can continue anyway."),_("Error"),wxOK|wxICON_ERROR);
				errorFound=true;
			}
			
			if(errorFound) {
				m_wxstHeadersCheck->SetLabel(_("Change XML file!"));
			SetHeadersCheckIcon(_("cross_icon"));
			}
		}
	}
	IsAllOKCheck();
}

void MicArrayAnalyzerConfDlg::OnBrowseXML(wxCommandEvent& event)
{
	wxFileDialog* wxfdOpenFileDialog = new wxFileDialog(this,_("Open configuration file..."),_(""),_(""),_("XML file (*.xml;*.XML)|*.xml;*.XML"),wxFD_OPEN|wxFILE_MUST_EXIST);
	if (wxfdOpenFileDialog->ShowModal() == wxID_OK)
	{
		mMAA->SetXMLFile(wxfdOpenFileDialog->GetPath());
		m_wxtcXMLConfigFilePath->SetValue(wxfdOpenFileDialog->GetPath()); //Showing filename + path in the plugin window.
		
		if (mMAA->BadXML())
		{
			// Handling two cases: (1) bad XML header, (2) good XML header but the XML doesn't hold mic array data.
			//m_wxsbHeadersCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("cross_icon")));
			m_wxstHeadersCheck->SetLabel(_("Bad XML header or not a Mic Array Configuration file"));
			SetHeadersCheckIcon(_("cross_icon"));
			bHeaders = true;
		}		
		else
		{
			mMAA->ReadXMLData(); //So, at least the XML seems ok. Reading data!
			EnableTable(); //Enabling the xml/wav/project data table
			
			//Filling **ONLY** XML fields of the data table
			wxString buffer;
			m_wxstMicName->SetLabel(mMAA->GetMicName());
			m_wxstManufacturer->SetLabel(mMAA->GetManufacturer());
			if (mMAA->GetArrayType() == 0) m_wxstArrayType->SetLabel(_("Spherical"));
			else { m_wxstArrayType->SetLabel(_("Planar")); }
			
			//buffer.Printf(_("%d"),mMAA->GetDeconvIRsLength());
			//			m_wxstXMLLength->SetLabel(buffer);
			//			buffer.Printf(_("%d"),mMAA->GetCapsulesNumber());
			//			m_wxstXMLCapsules->SetLabel(buffer);
			//			m_wxstXMLCapsules2->SetLabel(buffer);
			//			buffer.Printf(_("%d"),mMAA->GetVirtualMikes());         
			//			m_wxstXMLVirtual->SetLabel(buffer);
			//			
			
			//Here we can check if XML <-> PROJECT values are matched and set icons
			/* To do.... */
			
			if (mMAA->BadWAV())
			{
				// Handling bad wav file header error
				m_wxstHeadersCheck->SetLabel(_("Bad deconv. IRs WAV file header or file not found"));
				SetHeadersCheckIcon(_("cross_icon"));
				bHeaders = true;
				wxMessageBox(_("Bad deconv. IRs WAV file header or file not found"),_("Error"),wxOK|wxICON_ERROR);
				
			}
			else
			{
				// Everything SEEMS allright...
				m_wxstHeadersCheck->SetLabel(_("XML Header OK, WAV Header OK"));
				SetHeadersCheckIcon(_("check_icon"));
				bHeaders = true;
				
				//Filling data table with WAV data.
				//buffer.Printf(_("%d"),mMAA->GetWAVLength());
				//				m_wxstWAVLength->SetLabel(buffer);
				//				m_wxstWAVFormat->SetLabel(mMAA->GetWAVFormatName());
				//				buffer.Printf(_("%d"),mMAA->GetWAVSampleRate());
				//				m_wxstWAVfsample->SetLabel(buffer);
				//				buffer.Printf(_("%d"),mMAA->GetWAVChannels());
				//				m_wxstWAVChannels->SetLabel(buffer);
				//		
				
				
				//Now we can set XML <-> WAV and WAV <-> PROJECT icons too!
				bool errorFound = false;
				if ((mMAA->GetDeconvIRsLength() * mMAA->GetCapsulesNumber()) == mMAA->GetWAVLength())
				{
					//					m_wxsbLengthCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("check_icon")));
					bLength = true;
					//					m_wxsbLengthCheck->SetToolTip(wxEmptyString);
				}
				else
				{
					//					m_wxsbLengthCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("cross_icon")));
					bLength = false;
					//					m_wxsbLengthCheck->SetToolTip(_("XML and WAV files not matched!\nNote that No. of capsules multiplied by deconvolution IRs length should be equal to WAV file total length."));
					wxMessageBox(_("XML and WAV files not matched!\nNote that No. of capsules multiplied by deconvolution IRs length should be equal to WAV file total length."),_("Error"),wxOK|wxICON_ERROR);
					errorFound=true;
				}
				
				if (mMAA->GetVirtualMikes() == mMAA->GetWAVChannels())
				{
					//					m_wxsbWAVChannelsCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("check_icon")));
					bVirtMikes = true;
					//					m_wxsbWAVChannelsCheck->SetToolTip(wxEmptyString);
				}
				else
				{
					//					m_wxsbWAVChannelsCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("cross_icon")));
					bVirtMikes = false;
					//					m_wxsbWAVChannelsCheck->SetToolTip(_("XML and WAV files not matched!\nNote that No. of virtual mikes should be equal to No. of WAV file channels."));
					wxMessageBox(_("XML and WAV files not matched!\nNote that No. of virtual mikes should be equal to No. of WAV file channels."),_("Error"),wxOK|wxICON_ERROR);
					errorFound=true;
				}
				
				if (mMAA->GetCapsulesNumber() == mMAA->GetProjNumTracks())
				{
					//					m_wxsbProjChannelsCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("check_icon")));
					bProjChannels = true;
					//					m_wxsbProjChannelsCheck->SetToolTip(wxEmptyString);
				}
				else
				{
					//					m_wxsbProjChannelsCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("cross_icon")));
					bProjChannels = false;
					//					m_wxsbProjChannelsCheck->SetToolTip(_("XML doesn't match Audacity project!\nNote that No. of array capsules should be equal to No. of project tracks."));
					wxMessageBox(_("XML doesn't match Audacity project!\nNote that No. of array capsules should be equal to No. of project tracks."),_("Error"),wxOK|wxICON_ERROR);
					errorFound=true;
				}
				
				if (mMAA->GetWAVSampleRate() == (int)mMAA->GetProjSampleRate())
				{
					//					m_wxsbRateCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("check_icon")));
					bProjRate = true;
					//					m_wxsbRateCheck->SetToolTip(wxEmptyString);
				}
				else
				{
					//					m_wxsbRateCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("cross_icon")));
					bProjRate = false;
					//					m_wxsbRateCheck->SetToolTip(_("WAV doesn't match Audacity project!\nSample rates should be the same."));
					wxMessageBox(_("WAV doesn't match Audacity project!\nSample rates should be the same."),_("Error"),wxOK|wxICON_ERROR);
					errorFound=true;
				}
				
				if (mMAA->GetWAVSampleFormat() == mMAA->GetProjSampleFormat())
				{
					//					m_wxsbSampleFormatCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("check_icon")));
					bProjBits = true;
					//					m_wxsbSampleFormatCheck->SetToolTip(wxEmptyString);
				}
				else
				{
					//					m_wxsbSampleFormatCheck->SetBitmap(wxArtProvider::GetBitmap(wxT("warning_icon")));
					bProjBits = false;
					//					m_wxsbSampleFormatCheck->SetToolTip(_("WAV doesn't match Audacity project!\nSample formats are different. However that's just a warning, you can continue anyway."));
					wxMessageBox(_("WAV doesn't match Audacity project!\nSample formats are different. However that's just a warning, you can continue anyway."),_("Error"),wxOK|wxICON_ERROR);
					errorFound=true;
				}
				
				if(errorFound) {
					m_wxstHeadersCheck->SetLabel(_("Change XML file!"));
					SetHeadersCheckIcon(_("cross_icon"));
				}
			}
		}
		IsAllOKCheck();
	}	
}

void MicArrayAnalyzerConfDlg::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(m_wxpTable);
	Render(dc);
}

void MicArrayAnalyzerConfDlg::OnOk( wxCommandEvent& event )
{
	mMAA->SetTransparency(m_wxscTransparency->GetValue());
	
	m_Conf.Write(_("/MicArrayAnalyzer/Conf/XMLfile"), m_wxtcXMLConfigFilePath->GetValue());
	m_Conf.Write(_("/MicArrayAnalyzer/Conf/BackgroundImage"),  m_wxtcBgndImagePath->GetValue());
	m_Conf.Write(_("/MicArrayAnalyzer/Conf/Transparency"), m_wxscTransparency->GetValue());
	m_Conf.Write(_("/MicArrayAnalyzer/Conf/SPLthreshold"), m_wxtcMinSPL->GetValue());
	m_Conf.Write(_("/MicArrayAnalyzer/Conf/FSLevel"),m_wxtcFS->GetValue());
	m_Conf.Write(_("/MicArrayAnalyzer/Conf/FrameLength"),m_wxtcFLength->GetValue());
	m_Conf.Write(_("/MicArrayAnalyzer/Conf/FrameOverlapRatio"),m_wxtcFOvlp->GetValue());
	m_Conf.Flush();
	EndModal(true);
}


void MicArrayAnalyzerConfDlg::OnCancel( wxCommandEvent& event )
{
	EndModal(false); 

}


void MicArrayAnalyzerConfDlg::IsAllOKCheck()
{
	if (bBgndImage && bHeaders && bLength && bVirtMikes && bProjChannels && bProjRate && bProjBits)
	{
		m_wxbOk->Enable();
		m_wxbOk->SetDefault();
		//		m_wxbOk->SetFocus();
	}
	else m_wxbOk->Enable(false);
}


void MicArrayAnalyzerConfDlg::Render(wxDC& dc)
{
	// **** HERE IS THE CODE THAT PLOT MY CUSTOM CONTROL GRID ****
	//	dc.SetPen(*wxGREY_PEN);
	//	
	//	int x1,y1,x2,y2,w,h,max_w = 0;
	//	
	//	//Finding the longer label of the right column
	//	m_wxstTotalLengthLabel->GetSize(&w,&h);
	//	if (w >= max_w) max_w = w;
	//	m_wxstWAVChannelsLabel->GetSize(&w,&h);
	//	if (w >= max_w) max_w = w;
	//	m_wxstProjChannelsLabel->GetSize(&w,&h);
	//	if (w >= max_w) max_w = w;
	//	m_wxstProjRateLabel->GetSize(&w,&h);
	//	if (w >= max_w) max_w = w;
	//	m_wxstProjSampleFormatLabel->GetSize(&w,&h);
	//	if (w >= max_w) max_w = w;
	//	
	//	//Drawing horizontal lines
	//	m_wxstDeconvIRsLengthLabel->GetPosition(&x1,&y1);
	//	m_wxstTotalLengthLabel->GetPosition(&x2,&y2);
	//	dc.DrawLine(x1,y1-4,x2+max_w,y1-4);
	//	
	//	m_wxstNumOfCapsulesLabel->GetPosition(&x1,&y1);
	//	m_wxstNumOfCapsulesLabel->GetSize(&w,&h);
	//	dc.DrawLine(x1,y1+h+1,x2+max_w,y1+h+1);
	//	
	//	m_wxstNumOfVirtMikesLabel->GetPosition(&x1,&y1);
	//	m_wxstNumOfVirtMikesLabel->GetSize(&w,&h);
	//	dc.DrawLine(x1,y1+h+2,x2+max_w,y1+h+2); 
	//	
	//	m_wxstNumOfCapsulesLabel2->GetPosition(&x1,&y1);
	//	m_wxstNumOfCapsulesLabel2->GetSize(&w,&h);
	//	dc.DrawLine(x1,y1-4,x2+max_w,y1-4);
	//	dc.DrawLine(x1,y1+h+2,x2+max_w,y1+h+2);
	//	
	//	m_wxstSamplingRateLabel->GetPosition(&x1,&y1);
	//	m_wxstSamplingRateLabel->GetSize(&w,&h);
	//	dc.DrawLine(x1,y1-4,x2+max_w,y1-4);
	//	dc.DrawLine(x1,y1+h+2,x2+max_w,y1+h+2);
	//	
	//	//Drawing vertical lines
	//	wxPoint wxpSizerPos;
	//	
	//	//First vert line (left line of XML column)
	//	m_wxstXMLLabel->GetPosition(&x1,&y1);
	//	wxpSizerPos = m_wxstXMLLength->GetPosition();
	//	m_wxstWAVFormat->GetPosition(&x2,&y2);
	//	m_wxstWAVFormat->GetSize(&w,&h);
	//	dc.DrawLine(wxpSizerPos.x+4,y1,wxpSizerPos.x+4,y2+h);
	//	
	//	//Next vert line (right line of XML column)
	//	wxSize wxsSizerSize;
	//	wxsSizerSize = m_wxstXMLLabel->GetSize();
	//	dc.DrawLine((wxpSizerPos.x + wxsSizerSize.GetWidth() + 5),y1,(wxpSizerPos.x + wxsSizerSize.GetWidth() + 5),y2+h); 
	//	
	//	//Next vert line (left line of WAV column)
	//	m_wxstWAVLabel->GetPosition(&x1,&y1);
	//	wxpSizerPos = m_wxstWAVLabel->GetPosition();
	//	dc.DrawLine(wxpSizerPos.x+4,y1,wxpSizerPos.x+4,y2+h);
	//	
	//	//Next (and last) vert line.
	//	wxsSizerSize = m_wxstWAVLabel->GetSize();
	//	dc.DrawLine((wxpSizerPos.x + wxsSizerSize.GetWidth() + 5),y1,(wxpSizerPos.x + wxsSizerSize.GetWidth() + 5),y2+h);
}


void MicArrayAnalyzerConfDlg::EnableTable()
{
	//We need to enable each label, one by one...
	m_wxstHeadersCheckLabel->Enable();
	m_wxstMicNameLabel->Enable();
	m_wxstManufacturerLabel->Enable();
	m_wxstArrayTypeLabel->Enable();
	//m_wxstXMLLabel->Enable();
	//	m_wxstXMLLabel2->Enable();
	//	m_wxstWAVLabel->Enable();
	//	m_wxstWAVLabel2->Enable();
	//	m_wxstProjectLabel->Enable();
	//	m_wxstProjectLabel2->Enable();
	//	m_wxstDeconvIRsLengthLabel->Enable();
	//	m_wxstNumOfCapsulesLabel->Enable();
	//	m_wxstNumOfVirtMikesLabel->Enable();
	//	m_wxstTotalLengthLabel->Enable();
	//	m_wxstWAVChannelsLabel->Enable();
	//	m_wxstNumOfCapsulesLabel2->Enable();
	//	m_wxstProjChannelsLabel->Enable();
	//	m_wxstSamplingRateLabel->Enable();
	//	m_wxstProjRateLabel->Enable();
	//	m_wxstBitDepthLabel->Enable();
	//	m_wxstProjSampleFormatLabel->Enable();
	//	
	//and make visible hidden fields
	/*m_wxstXMLLength->Show();
	 m_wxstXMLCapsules->Show();
	 m_wxstWAVLength->Show();
	 m_wxstXMLVirtual->Show();
	 m_wxstWAVChannels->Show();
	 m_wxstXMLCapsules2->Show();
	 m_wxstProjChannels->Show();
	 m_wxstWAVfsample->Show();
	 m_wxstProjRate->Show();
	 m_wxstWAVFormat->Show();
	 m_wxstProjBitDepth->Show();*/
}


void MicArrayAnalyzerConfDlg::SetHeadersCheckIcon(const wxChar* icon)
{
	int x,y,w,h;
	m_wxstHeadersCheck->GetPosition(&x,&y);
	m_wxstHeadersCheck->GetSize(&w,&h);
	if (bHeaders) delete wxsbHeadersCheck;
	wxsbHeadersCheck = new wxStaticBitmap(m_wxpTable,wxID_ANY,wxNullBitmap,wxPoint(x+w+4,y),wxSize(15,15));
	//	m_wxbsHeadersCheck->Add(wxsbHeadersCheck);
	wxsbHeadersCheck->SetBitmap(wxArtProvider::GetBitmap(icon));
}

void MicArrayAnalyzerConfDlg:: OnSlideTransparency(wxScrollEvent& event)
{
	int transp = m_wxsldTransparency->GetValue();
	if (transp < 0) mMAA->SetTransparency(0);
	else if (transp>100) mMAA->SetTransparency(100);
	else mMAA->SetTransparency(transp);
	updating=2;
	m_wxscTransparency->SetValue(mMAA->GetTransparency());
	UpdateTranspOverview();
}



void MicArrayAnalyzerConfDlg:: OnSpinTransText( wxCommandEvent& event )
{
	if (!updating) {
		updating++; //to prevent the next call (2nd of TWO!)
		int trans = event.GetInt();
		if (trans < 0) mMAA->SetTransparency(0);
		else if (trans> 100) mMAA->SetTransparency(100);
		else mMAA->SetTransparency(trans);		
		m_wxsldTransparency->SetValue(mMAA->GetTransparency());
		m_wxscTransparency->SetValue(mMAA->GetTransparency());
		UpdateTranspOverview();
	} else updating--;
}

void MicArrayAnalyzerConfDlg:: OnSpinTransArrow( wxSpinEvent& event) 
{
	//???
}


void MicArrayAnalyzerConfDlg:: UpdateTranspOverview()
{
	//TODO  :
	//		put a default image (or even better the bgndimage!) on the GUI 
	//      and put a default colormap on it with the selected transparency just for overview
}


void MicArrayAnalyzerConfDlg::MinSPLOnFocus(wxFocusEvent& event)
{
	m_wxtcMinSPL->SetValue(wxEmptyString);
}


void MicArrayAnalyzerConfDlg::MinSPLKillFocus(wxFocusEvent& event)
{
	double d = ReadAndForceDoubleTextCtrl(m_wxtcMinSPL, mMAA->GetMinSPLThreshold());
	mMAA->SetMinSPLThreshold(d);
	IsAllOKCheck();
}


void MicArrayAnalyzerConfDlg::MinSPLOnChar(wxKeyEvent& event)
{
	if (event.GetKeyCode() == WXK_RETURN)
	{
		double d = ReadAndForceDoubleTextCtrl(m_wxtcMinSPL, mMAA->GetMinSPLThreshold());
		mMAA->SetMinSPLThreshold(d);
		IsAllOKCheck();
	}
	else event.Skip();
}


void MicArrayAnalyzerConfDlg::FSOnFocus(wxFocusEvent& event)
{
	m_wxtcFS->SetValue(wxEmptyString);
}


void MicArrayAnalyzerConfDlg::FSKillFocus(wxFocusEvent& event)
{
	double d = ReadAndForceDoubleTextCtrl(m_wxtcFS, mMAA->GetFSLevel());
	mMAA->SetFSLevel(d);
	IsAllOKCheck();
}


void MicArrayAnalyzerConfDlg::FSOnChar(wxKeyEvent& event)
{
	if (event.GetKeyCode() == WXK_RETURN)
	{
		double d = ReadAndForceDoubleTextCtrl(m_wxtcFS, mMAA->GetFSLevel());
		mMAA->SetFSLevel(d);
		IsAllOKCheck();
	}
	else event.Skip();
}

void MicArrayAnalyzerConfDlg::FLengthOnFocus(wxFocusEvent& event)
{
	m_wxtcFLength->SetValue(wxEmptyString);
	m_wxstTotFrames->SetLabel(wxEmptyString);
}


void MicArrayAnalyzerConfDlg::FLengthKillFocus(wxFocusEvent& event)
{
	double d = ReadAndForceDoubleTextCtrlFrameLength(m_wxtcFLength, mMAA->GetFrameLength());
	mMAA->SetFrameLength(d);
	IsAllOKCheck();
}


void MicArrayAnalyzerConfDlg::FLengthOnChar(wxKeyEvent& event)
{
	if (event.GetKeyCode() == WXK_RETURN)
	{
		double d = ReadAndForceDoubleTextCtrlFrameLength(m_wxtcFLength, mMAA->GetFrameLength());
		mMAA->SetFrameLength(d);
//		m_wxtcFOvlp->SetFocusFromKbd();
		IsAllOKCheck();
	}
	else event.Skip();
}


void MicArrayAnalyzerConfDlg::FOvlpOnFocus(wxFocusEvent& event)
{
	m_wxtcFOvlp->SetValue(wxEmptyString);
	m_wxstTotFrames->SetLabel(wxEmptyString);
}


void MicArrayAnalyzerConfDlg::FOvlpKillFocus(wxFocusEvent& event)
{
	double d = ReadAndForceDoubleTextCtrlFrameOverlap(m_wxtcFOvlp, mMAA->GetFrameOverlapRatio()*100);
	mMAA->SetFrameOverlapRatio(d/100);
	IsAllOKCheck();
}


void MicArrayAnalyzerConfDlg::FOvlpOnChar(wxKeyEvent& event)
{
	if (event.GetKeyCode() == WXK_RETURN)
	{
		double d = ReadAndForceDoubleTextCtrlFrameOverlap(m_wxtcFOvlp, mMAA->GetFrameOverlapRatio()*100);
		mMAA->SetFrameOverlapRatio(d/100);
		IsAllOKCheck();
	}
	else event.Skip();
}


double MicArrayAnalyzerConfDlg::ReadAndForceDoubleTextCtrl(wxTextCtrl *txt, const double def_val = 0.0)
{
	double d = def_val;
	wxString str;
	
	str = txt->GetValue();
	if ((str == wxEmptyString) || ((str != wxEmptyString)&&(!str.ToDouble(&d)))) d = def_val;
	
	if (d < 0) d = 0;          //Avoiding SPL < 0 dB.
	if (d > 999.9) d = 999.9;  //Avoiding SPL > 999.9 dB.
	
	str.Printf(_("%3.1f"),d);
	txt->SetValue(str);
	return d;
}


double MicArrayAnalyzerConfDlg::ReadAndForceDoubleTextCtrlFrameLength(wxTextCtrl *txt, const double def_val = FRAMELENGTH)
{
	double d = def_val;
	double audiotracklengthinseconds = mMAA->GetAudioTrackLength() / mMAA->GetProjSampleRate();
	wxString str;
	
	str = txt->GetValue();
	str.Replace(_(","), _("."), true);
	if ((str == wxEmptyString) || ((str != wxEmptyString)&&(!str.ToDouble(&d)))) d = def_val;
	
	if (d < 0) 
		d = 0;      
	else if (d > audiotracklengthinseconds ) {
		str.Printf(_("Frame Length value too long!\nselected audio data is %f second long.\n\nvalue reset to default"),
				   audiotracklengthinseconds);
		wxMessageBox(str,_("Error"),wxOK|wxICON_ERROR);
		d= FRAMELENGTH ;
	}
	
	str.Printf(_("%1.3f"),d);
	txt->SetValue(str);
	int totframes = mMAA->GetAudioTrackLength() / ( d * mMAA->GetProjSampleRate() * ( 1 - mMAA->GetFrameOverlapRatio()));
	mMAA->SetNumOfFrames(totframes);
	str.Printf(_("%d"), totframes);
	m_wxstTotFrames->SetLabel(str);
	
	return d;
}

double MicArrayAnalyzerConfDlg::ReadAndForceDoubleTextCtrlFrameOverlap(wxTextCtrl *txt, const double def_val = 0.1)
{
	double d = def_val;
	wxString str;
	
	str = txt->GetValue();
	str.Replace(_(","), _("."), true);
	if ((str == wxEmptyString) || ((str != wxEmptyString)&&(!str.ToDouble(&d)))) d = def_val;
	
//	d= d/100; //translate to ratio
	if (d < 0) d = 0;          
	else if (d > 90) {
		wxMessageBox(_("Maximum frame overlap ratio is 90%.\n"),_("Error"),wxOK|wxICON_ERROR);
		d = 90; 
	}
	
	str.Printf(_("%3.1f"),d);
	txt->SetValue(str);
	int totframes = mMAA->GetAudioTrackLength()/(mMAA->GetFrameLengthSmpl() * (1 - d/100) );
	mMAA->SetNumOfFrames(totframes);
	str.Printf(_("%d"),totframes);
	m_wxstTotFrames->SetLabel(str);
	
	return d;
}



//----------------------------------------------------------------------------
// MicArrayAnalyzerDlg Constructor
//----------------------------------------------------------------------------
MicArrayAnalyzerDlg::MicArrayAnalyzerDlg(wxWindow* parent, MicArrayAnalyzer *maa) 
: MyModuleDlg(parent),
mMAA(maa), 
m_iCurrRulersFormat(MyRuler::RF_DEGREES),
m_benchTime(),
m_lastFrameElapsedTime(0),
m_lastMillitimer(0), 
m_timer(this, ID_MM_TIMER)
{
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzerDlg: Class INIT\n");
	fflush(stdout);
#endif
	//Loading icons
//	   m_buttonPlay->SetBitmapLabel(wxArtProvider::GetBitmap(wxT("play_icon")));
//	   m_buttonStop->SetBitmapLabel(wxArtProvider::GetBitmap(wxT("stop_icon")));
//	   m_buttonPause->SetBitmapLabel(wxArtProvider::GetBitmap(wxT("pause_icon")));   
	//   m_wxbbSpeedUp->SetBitmapLabel(wxArtProvider::GetBitmap(wxT("speedup_icon")));   
	//   m_wxbbSlowDown->SetBitmapLabel(wxArtProvider::GetBitmap(wxT("slowdown_icon")));
	//   m_wxbbRulersMenu->SetBitmapLabel(wxArtProvider::GetBitmap(wxT("rulers_menu_icon")));
	
	//Initializing Mouse Pointer Data Panel
	wxString buffer;
	buffer.Printf(_("-----"));
	m_wxtcXPos->SetValue(buffer);
	m_wxtcYPos->SetValue(buffer);
	m_wxtcLevel->SetValue(buffer);
	
	//Acquiring current Scale Style and Units.
	m_wxtcLevelUnit->SetValue(wxString::Format(wxT("[dB]"))); // Should be the default
	
	m_pMap->SetMicArrayAnalyzerPtr(mMAA); // Something better has to be done!
	m_pMap->SetImageAlpha(1, 100 - mMAA->GetTransparency(), true);
	m_pMap->SetMeasureUnit(m_wxcScaleUnit->GetSelection());
	m_pMap->SetBand(m_wxrbBandSelection->GetSelection());
	m_pMap->SetStyle(m_wxcScaleStyle->GetSelection());
	
	m_pMap->SetMaxMin( mMAA->GetMaxSPL(m_wxcbSeparateBandAutoscale->IsChecked(),
										m_wxrbBandSelection->GetSelection()),
					   mMAA->GetMinSPL(m_wxcbSeparateBandAutoscale->IsChecked(),
										m_wxrbBandSelection->GetSelection()) );

	
	m_pMap->SetTransparency(mMAA->GetTransparency());
	
	m_pMap->ShowVirtMikesPos(m_wxcbShowVirtMikes->IsChecked()); //Acquiring default value.
	
	//Centering dialog on screen
	this->Centre();
	
	// Connect events
	Connect(wxEVT_POINTER_POSITION, wxCommandEventHandler(MicArrayAnalyzerDlg::OnMouseOverMap), NULL, this);
	Connect(wxEVT_TIMER,       wxTimerEventHandler(MicArrayAnalyzerDlg::OnTimer),            NULL, this);
	
	//default values
	updating = 0;
	mMAA->SetPlaying(false);
	mMAA->SetCurFrame(1);
	m_sliderVideoFrame->SetMax(mMAA->GetNumOfFrames());
	m_spinCtrlCurFrame->SetRange(1, mMAA->GetNumOfFrames());
//	m_textCtrlCurTime->SetValue(wxT("00:00:000"));
	m_textCtrlCurTime->SetValue(mMAA->GetCurTime_Str());
//	m_wxcbSeparateBandAutoscale->SetValue(true);
}

MicArrayAnalyzerDlg::~MicArrayAnalyzerDlg()
{
	Disconnect(wxEVT_POINTER_POSITION, wxCommandEventHandler(MicArrayAnalyzerDlg::OnMouseOverMap), NULL, this);
	Disconnect(wxEVT_TIMER,       wxTimerEventHandler(MicArrayAnalyzerDlg::OnTimer),            NULL, this);
	
}

void MicArrayAnalyzerDlg::OnOk(wxCommandEvent& event)
{
	EndModal(true);
}

/*  -----> BUTTON REMOVED...SHOULD BE REUSED IN SOME WAY <-----
 void MicArrayAnalyzerDlg::OnChangeRulersFormat(wxCommandEvent& event) 
 {
 m_iCurrRulersFormat = (m_iCurrRulersFormat == MyRuler::RF_DEGREES) ? MyRuler::RF_PIXELS 
 : MyRuler::RF_DEGREES;  //Toggling.
 
 switch(m_iCurrRulersFormat)    
 {
 case MyRuler::RF_DEGREES:
 m_wxtcXPosLabel->SetValue(_("Azimuth:")); 
 m_wxtcYPosLabel->SetValue(_("Elevation:"));
 m_wxtcXPosUnit->SetValue(_("[deg]"));
 m_wxtcYPosUnit->SetValue(_("[deg]")); 
 break;
 
 case MyRuler::RF_PIXELS: 
 m_wxtcXPosLabel->SetValue(_("X Pos:"));
 m_wxtcYPosLabel->SetValue(_("Y Pos:"));
 m_wxtcXPosUnit->SetValue(_("[px]"));
 m_wxtcYPosUnit->SetValue(_("[px]")); 
 break;
 }
 m_pMap->GetRuler(MyMap::HORIZONTAL)->SetFormat(m_iCurrRulersFormat);
 m_pMap->GetRuler(MyMap::VERTICAL)->SetFormat(m_iCurrRulersFormat);
 
 m_pMap->Refresh();
 }
 */
void MicArrayAnalyzerDlg::OnShowVirtMikesPos(wxCommandEvent& event)
{
	m_pMap->ShowVirtMikesPos(event.IsChecked());
	m_pMap->Refresh();
}

void MicArrayAnalyzerDlg::OnCopyResultsToClipboard(wxCommandEvent& event) // SC ----> TODO !!!!
{
	if(!m_pMap->CopyToClipboard())
	{
		::wxMessageBox(wxT("Cannot copy map to the clipboard."),
					   wxT("Error"),
					   wxOK | wxICON_ERROR);
		return;
	}
	
#ifdef __AUDEBUG__
	mMAA->PrintResults();
	mMAA->PrintLevels();
#endif
	::wxMessageBox(wxT("Map successifully copied to the clipboard."),
				   wxT("Info"),
				   wxOK | wxICON_INFORMATION);    
}

void MicArrayAnalyzerDlg::OnHelp( wxCommandEvent& event )
{
	wxString txt,caption;
	txt.Printf( wxT("Frame Length = %1.3f sec.\nFrame Overlap Ratio = %3.2f "), mMAA->GetFrameLength(), mMAA->GetFrameOverlapRatio());
	wxMessageBox(txt,caption,wxOK|wxICON_INFORMATION);
}


void MicArrayAnalyzerDlg::OnSeparateBandAutoscale(wxCommandEvent& event)
{   
	 m_pMap->SetMaxMin( mMAA->GetMaxSPL(event.IsChecked(),
										m_wxrbBandSelection->GetSelection()),
						mMAA->GetMinSPL(event.IsChecked(),
										m_wxrbBandSelection->GetSelection()) );
	
	mMAA->SetBandAutoscale(event.IsChecked());
	
	m_pMap->Refresh();
}   

void MicArrayAnalyzerDlg::OnScaleUnit(wxCommandEvent& event) 
{
	wxString units;
	switch(event.GetSelection())
	{
		case MU_dB:   units.Printf(wxT("[dB]"));	m_buttonPlay->Enable(true);			break;
		case MU_Pa:   units.Printf(wxT("[Pa]"));	m_buttonPlay->Enable(false);		break;
		case MU_Sqrt: units.Printf(wxT("[SQRT]"));	m_buttonPlay->Enable(false);		break;
		case MU_Cbrt: units.Printf(wxT("[CBRT]"));	m_buttonPlay->Enable(false);		break;
		default:      units.Printf(wxT("[dB]"));	m_buttonPlay->Enable(true);
	}
	//NOTE: UPDATING MOUSE POINTER DATA DISPLAY UNIT TOO!!!!    
	m_wxtcLevelUnit->SetValue(units);
	
	m_pMap->SetMeasureUnit(event.GetSelection());
	m_pMap->Refresh();
}

void MicArrayAnalyzerDlg::OnScaleStyle(wxCommandEvent& event)  
{
	m_pMap->SetStyle(event.GetSelection());
	m_pMap->Refresh();
}

void MicArrayAnalyzerDlg::OnBandAnalysis(wxCommandEvent& event) 
{
	int band = event.GetSelection();
	m_pMap->SetBand(band);
	m_pMap->SetMaxMin( mMAA->GetMaxSPL(m_wxcbSeparateBandAutoscale->IsChecked(),
	                                       band),
					   mMAA->GetMinSPL(m_wxcbSeparateBandAutoscale->IsChecked(),
										  band) );

	
	m_pMap->Refresh();
}

void MicArrayAnalyzerDlg::OnMouseOverMap(wxCommandEvent& event)  
{
	MyMouseCoord* c = (MyMouseCoord*)event.GetClientData();
	
	wxString szX(wxT("----")), szY(wxT("----")), szZ(wxT("----"));
	
	if(c->x > 0.0 && c->y > 0.0)
	{
		switch(c->format)
		{
			case MyRuler::RF_PIXELS:
				szX.Printf(wxT("%d"), int(c->x));
				szY.Printf(wxT("%d"), int(c->y));
				break;
				
			case MyRuler::RF_DEGREES:
				szX.Printf(wxT("%.1f"), c->x);
				szY.Printf(wxT("%.1f"), c->y);
				break;
		}
		
		if(c->unit == MU_dB)
			szZ.Printf(wxT("%.1f"), c->z);
		else 
			szZ.Printf(wxT("%.1E"), c->z);        
	}      
	
	
	m_wxtcXPos->SetValue(szX);
	m_wxtcYPos->SetValue(szY);
	m_wxtcLevel->SetValue(szZ);
}

// --------------------
//	PLAYER VIDEO
//--------------------

void MicArrayAnalyzerDlg::UpdateFrameControls(){
//	
//	m_pMap->SetMaxMin( mMAA->GetMaxSPL(m_wxcbSeparateBandAutoscale->IsChecked(),
//										   m_wxrbBandSelection->GetSelection()),
//					   mMAA->GetMinSPL(m_wxcbSeparateBandAutoscale->IsChecked(),
//						     			  m_wxrbBandSelection->GetSelection()) );

	
	m_textCtrlCurTime->SetValue(mMAA->GetCurTime_Str());
#ifdef __AUDEBUG__
	//	mMAA->PrintResults();
#endif
	m_pMap->Refresh();
	
}

void MicArrayAnalyzerDlg::OnSpinCurFrame(wxCommandEvent& event)  {
	unsigned int frame = event.GetInt();
	if (frame < 1) mMAA->SetCurFrame(1);
	else if (frame> mMAA->GetNumOfFrames()) mMAA->SetCurFrame(mMAA->GetNumOfFrames());
	else mMAA->SetCurFrame(frame);
	m_sliderVideoFrame->SetValue(mMAA->GetCurFrame());
	UpdateFrameControls();
}

int MicArrayAnalyzerDlg::SpinProcessValue(wxString str)  {
	double timestamp;
	if (!str.ToDouble(&timestamp)) {
		::wxMessageBox(wxT("Cannot convert to double!"),
					   wxT("Error"),
					   wxOK | wxICON_ERROR);
	}
	int correspondingFrame = timestamp / mMAA->GetFrameLength() + 1;
	return correspondingFrame;
}

void MicArrayAnalyzerDlg::OnSpinCtrlTxt(wxCommandEvent& event)  {
	if (!updating) {
		updating++; //to prevent the next call (2nd of TWO!)
		//		unsigned int frame = SpinProcessValue( event.GetString());
		unsigned int frame = event.GetInt();
		if (frame < 1) mMAA->SetCurFrame(1);
		else if (frame> mMAA->GetNumOfFrames()) mMAA->SetCurFrame(mMAA->GetNumOfFrames());
		else mMAA->SetCurFrame(frame);		
		m_sliderVideoFrame->SetValue(mMAA->GetCurFrame());
		m_spinCtrlCurFrame->SetValue(mMAA->GetCurFrame());
		UpdateFrameControls();
	} else updating--;
}

void MicArrayAnalyzerDlg::OnSliderScroll( wxScrollEvent& event )  {
	unsigned int frame = m_sliderVideoFrame->GetValue();
	if (frame < 1) mMAA->SetCurFrame(1);
	else if (frame> mMAA->GetNumOfFrames()) mMAA->SetCurFrame(mMAA->GetNumOfFrames());
	else mMAA->SetCurFrame(frame);
	updating=2;
	m_spinCtrlCurFrame->SetValue(mMAA->GetCurFrame());
	UpdateFrameControls();
}

void MicArrayAnalyzerDlg::OnSTOPBtn(wxCommandEvent& event)  {
	mMAA->SetPlaying(false);
	mMAA->SetCurFrame(1);
	m_sliderVideoFrame->SetValue(1);
	updating=2;
	m_spinCtrlCurFrame->SetValue(1);
	UpdateFrameControls();
}

void MicArrayAnalyzerDlg::OnPAUSEBtn(wxCommandEvent& event)  {
	mMAA->SetPlaying(false);
}

void MicArrayAnalyzerDlg::OnPLAYBtn(wxCommandEvent& event)  {
	mMAA->SetPlaying(true);
	RestartTimer();
}

void MicArrayAnalyzerDlg::OnChoiceFrameRate(wxCommandEvent& event)  {
	switch (event.GetInt()) {
			
		case 0: // 0.1x
			m_frameRateCoeff=0.1;
			break;		
			
		case 1: // 0.2x
			m_frameRateCoeff=0.2;
			break;
			
		case 2: // 0.5x
			m_frameRateCoeff=0.5;
			break;
			
		case 3: // 1x
			m_frameRateCoeff=1;
			break;
			
		default:
			break;
	}	
}

void MicArrayAnalyzerDlg::RestartTimer() 
{
	double framelength_ms = mMAA->GetFrameLength()*1000;
	switch (m_wxcPlaybackSpeed->GetCurrentSelection()) { //decide how long to yeld to sync the video with the frame rate
		case 0: // 0.1x
			m_lastMillitimer = framelength_ms / 0.1 - (m_lastFrameElapsedTime - m_lastMillitimer); break;
			
		case 1: // 0.2x
			m_lastMillitimer = framelength_ms / 0.2 - (m_lastFrameElapsedTime - m_lastMillitimer); break;
			
		case 2: // 0.5x
			m_lastMillitimer = framelength_ms / 0.5 - (m_lastFrameElapsedTime - m_lastMillitimer); break;
			
		case 3: // 1x
			m_lastMillitimer = framelength_ms / 1.0 - (m_lastFrameElapsedTime - m_lastMillitimer); break;
			
		default:
			m_lastMillitimer = 1; break;
	}
	if (m_lastMillitimer <= 0 || m_lastMillitimer >= 1000) m_lastMillitimer = 1; // timer between [0 , 1] sec.
	m_timer.Start(m_lastMillitimer, true);
}

void MicArrayAnalyzerDlg::OnTimer(wxTimerEvent& evt)
{
#ifdef __AUDEBUG__
	m_benchTime.Stop();
	m_lastFrameElapsedTime = m_benchTime.GetElapsedTime();
	printf("onTimer!!! curFrame = [%d], timing: %.1f ms\n",mMAA->GetCurFrame(), m_lastFrameElapsedTime);
	m_benchTime.Start();
#endif
	
	if (mMAA->Playing()) {
		if(mMAA->GetCurFrame() < mMAA->GetNumOfFrames()) {
			mMAA->NextFrame();
		}
		else {
			mMAA->SetPlaying(false);
		}
		m_sliderVideoFrame->SetValue(mMAA->GetCurFrame());
		updating=2; 
		m_spinCtrlCurFrame->SetValue(mMAA->GetCurFrame()); //trigger the TEXT_UPDATED event 2 TIMES!!
		UpdateFrameControls();		
		RestartTimer();
	}
}








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

