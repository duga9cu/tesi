/**********************************************************************
 
 Audacity: A Digital Audio Editor
 
 Microphone Array Analyzer
 
 micarrayanalyzer.cpp
 
 Luca Novarini
 
 **********************************************************************/


#include "micarrayanalyzer.h"
#include <WaveTrack.h>
#include "tinyxml.h"       //Needed to read XML files
#include <sstream>

//#ifndef __AUDEBUG__  //FORCING DEBUG MODE
//#define __AUDEBUG__
//#endif


using std::vector;
using namespace tpp;


MicArrayAnalyzer::MicArrayAnalyzer()
: dProjectRate(0),
iProjectNumTracks(0),
bXMLFileAlloc(false),
bWAVFileAlloc(false),
bSndFileAlloc(false),
bMikesCoordsAlloc(false),
bBgndImageAlloc(false),
bBgndVideoAlloc(false),
m_bgndVideoFrameRate(0),
dFSLevel(FS_DEFAULT),
dMinSPLThreshold(MIN_SPL_DEFAULT),
bAudioDataAlloc(false),
bDeconvIRsDataAlloc(false),
iAudioTrackLength(0),
iAudioTrackStart(0),
iAudioTrackEnd(0),
bMirroredMikesAlloc(false),
iNTriangles(0),
bResultsAvail(false),
bWatchpointsAlloc(false),
iWatchpoints(0),
//mProgress(0),
m_frameLengthSmpl(FrameLengths[FRAMELENGTH_DFLT]),
m_frameOverlapRatio(FRAMEOVERLAP),
m_curFrame(1),
playing(false),
//bandAutoscale(true)
bandAutoscale(false),
m_bfdBScalingFactorAlloc(false)
{
	m_tmpDirPath=m_standardTMPdirPath.GetTempDir();
	outputFrames = new Video(MAP_WIDTH,MAP_HEIGHT);
	outputFrames->m_iCurrentUnit=MU_dB;
	mAAcritSec = new wxCriticalSection();
	wxImage::AddHandler(new wxPNMHandler);
	m_bErrorOutOfMemory= new bool(false);
	
	//	SetFrameLength(frameLength[1]); bad idea cause you don't know the projrate yet!
}

MicArrayAnalyzer::MicArrayAnalyzer(const MicArrayAnalyzer& mMAA) : 
//mProgress(mMAA.mProgress),
dMinSPLThreshold(mMAA.dMinSPLThreshold),
dFSLevel(mMAA.dFSLevel),
dProjectRate(mMAA.dProjectRate),
//sfProjectFormat(mMAA.sfProjectFormat), //not used in calculate()
iProjectNumTracks(mMAA.iProjectNumTracks),
iAudioTrackLength(mMAA.iAudioTrackLength),
iAudioTrackStart(mMAA.iAudioTrackStart),
iAudioTrackEnd(mMAA.iAudioTrackEnd),
bMirroredMikesAlloc(mMAA.bMirroredMikesAlloc),
wxfnXMLFile(mMAA.wxfnXMLFile),
bXMLFileAlloc(mMAA.bXMLFileAlloc),
wxfnWAVFile(mMAA.wxfnWAVFile),
bWAVFileAlloc(/*mMAA.bWAVFileAlloc*/ NULL),
infile(mMAA.infile),
bSndFileAlloc(mMAA.bSndFileAlloc),
sfinfo(mMAA.sfinfo),
wxsMicName(mMAA.wxsMicName),
wxsManufacturer(mMAA.wxsManufacturer),
iArrayType(mMAA.iArrayType),
iMikesCoordsUnits(mMAA.iMikesCoordsUnits),
iCapsules(mMAA.iCapsules),
iVirtualMikes(mMAA.iVirtualMikes),
iDeconvIRsLength(mMAA.iDeconvIRsLength),
MikesCoordinates(mMAA.MikesCoordinates), //* shared among threads! (read-only)
bMikesCoordsAlloc(mMAA.bMikesCoordsAlloc),
wxbBgndImage(mMAA.wxbBgndImage),
bBgndImageAlloc(mMAA.bBgndImageAlloc),
wxfnBgndImageFile(mMAA.wxfnBgndImageFile),
m_bgndVideoFrameRate(mMAA.m_bgndVideoFrameRate),
bBgndVideoAlloc(mMAA.bBgndVideoAlloc),
wxfnBgndVideoFile(mMAA.wxfnBgndVideoFile),
m_tmpDirPath(mMAA.m_tmpDirPath),
vmsMirroredMikes(mMAA.vmsMirroredMikes), // calculate only first time
tmMeshes(mMAA.tmMeshes), // calculate only first time
iNTriangles(mMAA.iNTriangles), //la triangolazione è uguale per tutti
ppfAudioData(mMAA.ppfAudioData), //* shared among threads! (read-only)
//ActualFrameAudioData(mMAA.ActualFrameAudioData),  //* vedi sotto
//bAudioDataAlloc(false), //* vedi sotto
pfLocalMin(mMAA.pfLocalMin), //* shared (read-only)
pfLocalMax(mMAA.pfLocalMax), //* shared (read-only)
pfAbsoluteMin(mMAA.pfAbsoluteMin),	//* shared (read-only)
pfAbsoluteMax(mMAA.pfAbsoluteMax),	//* shared (read-only)
fdBScalingFactor(mMAA.fdBScalingFactor), // calculate it only the first time!
m_bfdBScalingFactorAlloc(mMAA.m_bfdBScalingFactorAlloc),
pppfDeconvIRsData(mMAA.pppfDeconvIRsData), //* shared (read-only) 
bDeconvIRsDataAlloc(mMAA.bDeconvIRsDataAlloc),
//apOutputData(mMAA.apOutputData),	//*  - viene usato solo in calculate()
bResultsAvail(false), //devo ancora calcolare i risultati
// per ora non uso i watchpoints
//piWatchpoints(mMAA.piWatchpoints),
//iWatchpoints(mMAA.iWatchpoints), 
// wxasWatchpointsLabels(mMAA.wxasWatchpointsLabels),  
//bWatchpointsAlloc(mMAA.bWatchpointsAlloc), 
m_curFrame(mMAA.m_curFrame),
m_frameLengthSmpl(mMAA.m_frameLengthSmpl),
m_frameOverlapRatio(mMAA.m_frameOverlapRatio),
outputFrames(mMAA.outputFrames), //* shared among threads!
m_bErrorOutOfMemory(mMAA.m_bErrorOutOfMemory),
mAAcritSec(mMAA.mAAcritSec), //* shared among threads!
m_window(mMAA.m_window),  //* shared among threads!
libs(mMAA.libs) //* shared among threads
{
	try {
	wxfnBgndImageFile=mMAA.wxfnBgndImageFile;
	
	bAudioDataAlloc = true;	
	int ActualFrameLengthSmpl = GetFrameLengthSmpl();
	ActualFrameAudioData = new float* [iProjectNumTracks];
	for (int i=0; i<iProjectNumTracks; i++) {
		ActualFrameAudioData[i] = new float [ActualFrameLengthSmpl];
	}
	}catch (bad_alloc& ex) {
		GotBadAlloc();
	}
}

void MicArrayAnalyzer::DeleteAllData()  {
	if(bXMLFileAlloc) {
		delete wxfnXMLFile;
		bXMLFileAlloc=false;
	}
	if(bWAVFileAlloc) {
		delete wxfnWAVFile;
		bWAVFileAlloc=false;
	}
	if(bSndFileAlloc) {
		sf_close(infile);
		bSndFileAlloc=false;
	}
	if(bMikesCoordsAlloc) {
		delete [] MikesCoordinates;
		bMikesCoordsAlloc=false;
	}
	if(bBgndImageAlloc) {
		delete wxfnBgndImageFile;
		bBgndImageAlloc=false;
	}
	if(bMirroredMikesAlloc) {
		delete vmsMirroredMikes;
		bMirroredMikesAlloc=false;
	}
	if(iNTriangles > 0) {
		for (int i=0; i<iNTriangles; ++i) {
			delete tmMeshes[i];
		}
		delete [] tmMeshes;
	}
	if (bAudioDataAlloc) {
		for (int i=0; i<iProjectNumTracks; ++i) {
			delete[] ppfAudioData[i];
		}
		delete [] ppfAudioData;
	}
	if (bDeconvIRsDataAlloc) {
		for (int i=0; i<sfinfo.channels; ++i) {
			for (int j=0; j<iCapsules; ++j) {
				delete[] pppfDeconvIRsData[i][j];
			}
			delete [] pppfDeconvIRsData[i];
		}
		delete [] pppfDeconvIRsData;
	}
	if(bWatchpointsAlloc) 
		delete [] piWatchpoints;
	
	//	outputFrames->DeleteAllData();
}


MicArrayAnalyzer::~MicArrayAnalyzer()
{ 
	//free some memory
	for (int i=0; i<iProjectNumTracks; i++) {
		delete [] ActualFrameAudioData[i] ;
	}
	delete [] ActualFrameAudioData;
	//REMEMBER TO CALL DeleteAllData() instead! otherwise every thread would destroy everything shared
	//	if(mProgress) delete mProgress;
	//	mProgress = 0;
	//	if(bXMLFileAlloc) {
	//		delete wxfnXMLFile;
	//		bXMLFileAlloc=false;
	//	}
	//	if(bWAVFileAlloc) {
	//		delete wxfnWAVFile;
	//		bWAVFileAlloc=false;
	//	}
	//	if(bSndFileAlloc) {
	//		sf_close(infile);
	//		bSndFileAlloc=false;
	//	}
	//	if(bMikesCoordsAlloc) {
	//		delete [] MikesCoordinates;
	//		bMikesCoordsAlloc=false;
	//	}
	//	if(bBgndImageAlloc) {
	//		delete wxfnBgndImageFile;
	//		bBgndImageAlloc=false;
	//	}
	//	if(bMirroredMikesAlloc) {
	//		delete vmsMirroredMikes;
	//		bMirroredMikesAlloc=false;
	//	}
	//	if(iNTriangles > 0) delete [] tmMeshes;
	//	if (bAudioDataAlloc) delete [] ppfAudioData;
	//	if (bDeconvIRsDataAlloc) delete [] pppfDeconvIRsData;
	//	if(bWatchpointsAlloc) delete [] piWatchpoints;
}


bool MicArrayAnalyzer::InitLevelsMap(int frame) //one frame, 12 bands, 1 measure unit
{
    int i,k,l;
	double **aadLevelsMap;
	for( int currentBand=0; currentBand<2+10; currentBand++) 
	{
		//Levels Map matrix init.
		try {
			aadLevelsMap = new double* [MAP_WIDTH];
		} catch (bad_alloc& ex) {
			return GotBadAlloc();
		}
		
		for ( l = 0; l < MAP_WIDTH; l++) {
			try {
				aadLevelsMap[l] = new double [MAP_HEIGHT];
			} catch (bad_alloc& ex) {
				return GotBadAlloc();
			}
		}
		TriangularMesh* tmCurrentTri;
		
		ClearInterpolCoeffs();  //Clearing A,B,C,det for each triangle.
		
		int j = 0; //Used to remember the previous triangle where a point was located, in order to speed-up point location!
		for (i = 0; i < MAP_WIDTH; i++)
		{
			for (k = 0; k < MAP_HEIGHT; k++)
			{
				//Locating the position of pixel (i,k) inside the triangulation
				for (l = 0; l <iNTriangles; l++)
				{
					tmCurrentTri = NULL;
					if (InOrOutTriangle(i,k,j) >= 0) //InOrOutTriangle returns -1 if point (i,k) is outside, 0 in it's onside and +1 if it's inside triangle number j.
					{
						tmCurrentTri = GetTriangle(j);
						break; //Location completed!
					}
					else
					{
						j++;
						if (j >= iNTriangles) 
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
							if (iArrayType==1) {								
								tb.Start();
								levels[vert] = GetResult(tmCurrentTri->GetMicAtVertex(vert),
														 currentBand);
								tb.Stop();
								printf("GetResult(%d) time %.3ms",frame,tb.GetElapsedTime());
							} else 
								levels[vert] = GetResult(tmCurrentTri->GetMicAtVertex(vert),
														 currentBand);
							
							//Scaling to the correct unit
							levels[vert] = FromdB(levels[vert], /*MeasureUnit(outputFrames->m_iCurrentUnit)*/ MU_dB); //what to do here?
						}
						//Setting levels will automatically compute interpolation coeffs.
						if (iArrayType==1) {					
							tb.Start();
							tmCurrentTri->SetLevelsAtVertexes(levels); 
							tb.Stop();
							printf("setlevelsatvertex(%d) time %.3ms",frame,tb.GetElapsedTime());
						} else
							tmCurrentTri->SetLevelsAtVertexes(levels); 
					}
					if (iArrayType==1) {
						tb.Start();
						aadLevelsMap[i][k] = tmCurrentTri->GetInterpolatedValue(i,k);
						tb.Stop();
						printf("getinterpolation(%d) time %.3ms",frame,tb.GetElapsedTime());
					} else
						aadLevelsMap[i][k] = tmCurrentTri->GetInterpolatedValue(i,k);
					
				}
			}
		}   
		wxCriticalSectionLocker lock(*mAAcritSec);
		outputFrames->SetFrameLevelsMap(frame, aadLevelsMap, currentBand);
	}
	return true;
}

bool MicArrayAnalyzer::GotBadAlloc() {
	mAAcritSec->Enter(); //leave it at the end of thread->Entry()
	cout << "\n\ninitLevelsMap(): Memory not allocated !!\n\n";
	//		wxMessageBox(_("Out Of Memory ! ... go get some memory ;)"),_("Error"),wxOK|wxICON_ERROR);
	//			if(!*m_bErrorOutOfMemory)
	*m_bErrorOutOfMemory=true;
	
	return false;
}

void MicArrayAnalyzer::InitWindow() {

		m_window=new float[m_frameLengthSmpl];
		for (int i=0; i<m_frameLengthSmpl; ++i) {
			m_window[i]=1;
		}
		WindowFunc(WINDOWFUNC, m_frameLengthSmpl, m_window); //.. at this point m_window contains the window itself
	}


bool MicArrayAnalyzer::Triangulate_and_mesh() 
{
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer::Calculate(): Adding virtual mikes to Delaunay triangulation.\n");
	fflush(stdout);
#endif
	
	//	InitProgressMeter(_("Adding virtual mikes to the Delaunay triangulation..."));
	
	//Adding mikes to the Delaunay triangulation
	Delaunay::Point tempP;
	vector<Delaunay::Point> v;
	
	if (iArrayType == 0 || iArrayType == 1)
	{
#ifdef __AUDEBUG__
		printf("MicArrayAnalyzer::Calculate(): Virtual mikes mirroring ENABLED (spherical or cylindrical array detected).\n");
		fflush(stdout);
#endif
		vmsMirroredMikes = new VirtualMikesSet;   //For spherical arrays we need to "clone" each virtual mike properly
		//to guarantee ColorMap boundary continuity.
		//See "GetMirroredMikes" if you want to explore cloning rules!
		bMirroredMikesAlloc = true;
	}
	int i, j;
	for (i=0;i<iVirtualMikes;i++)
	{
		//		UpdateProgressMeter(i,iVirtualMikes);
		
		// Get current virtualmike coordinates
		tempP[0] = MikesCoordinates[2*i]; 
		tempP[1] = MikesCoordinates[2*i + 1];
		//#ifdef __AUDEBUG__
		//		printf("MicArrayAnalyzer::Calculate(): adding virtual mike [%d]\n",i);
		//		fflush(stdout);
		//		//         VirtualMike* pvmDebug;
		//#endif
		v.push_back(tempP);  //Adding mike to the triangulation
		
		if (iArrayType == 0) //spherical
		{
			for (j=0;j<3;j++)   //For each virt. mike, three mirrored mikes exists.
			{
				double dMirroredMike[2];
				if (!GetMirroredMike(MikesCoordinates[2*i],MikesCoordinates[2*i+1],dMirroredMike,j,iArrayType)) //Retrieving mirror #j mike coords.
				{
					printf("problem with getmirroredmike() during calculate()..");
					return false;
				}
				tempP[0] = dMirroredMike[0]; tempP[1] = dMirroredMike[1];
				//#ifdef __AUDEBUG__
				//				printf("MicArrayAnalyzer::Calculate(): adding mirror [%d] of virtual mike [%d]\n",j,i);
				//				fflush(stdout);
				//#endif
				v.push_back(tempP);                                     //Adding mirrored mike to the triangulation
				vmsMirroredMikes->AddVirtualMike(tempP[0],tempP[1],i);    //By passing "i" to AddMike we specify that this is a clone of Mic #i.
			}
		} else if(iArrayType==1) //cylindrical
		{
			double dMirroredMike[2];
			if (!GetMirroredMike(MikesCoordinates[2*i],MikesCoordinates[2*i+1],dMirroredMike,0,iArrayType)) //Retrieving mirror #j mike coords.
			{
				printf("problem with getmirroredmike() during calculate()..");
				return false;
			}
			tempP[0] = dMirroredMike[0]; tempP[1] = dMirroredMike[1];
			//#ifdef __AUDEBUG__
			//				printf("MicArrayAnalyzer::Calculate(): adding mirror [%d] of virtual mike [%d]\n",j,i);
			//				fflush(stdout);
			//#endif
			v.push_back(tempP);                                     //Adding mirrored mike to the triangulation
			vmsMirroredMikes->AddVirtualMike(tempP[0],tempP[1],i);    //By passing "i" to AddMike we specify that this is a clone of Mic #i.
		}
	}
	
	//	DestroyProgressMeter();
	
	//	InitProgressMeter(_("Generating mesh surface..."));
#ifdef __AUDEBUG__
	
	printf("MicArrayAnalyzer::Calculate(): Triangulating...");
	fflush(stdout);
#endif
	Delaunay dt(v);   //"dt" stands for (d)elaunay (t)riangulation
	dt.Triangulate(); //The triangulation will be computed here....
	iNTriangles = dt.ntriangles(); //Storing the number of computed triangular meshes
	
	//	UpdateProgressMeter(1,iNTriangles+1);
	
	tmMeshes = new TriangularMesh* [iNTriangles];      //The computed triangulation will be stored inside a TriangularMesh array.
	int x[3],y[3],mic[3];                              //(x,y) = position, mic = mic #.
	Delaunay::fIterator fit = dt.fbegin();
	
	int k;
	for(j=0;j<iNTriangles;j++)
	{
		//		UpdateProgressMeter(j+1,iNTriangles+1);
		x[0] = dt.point_at_vertex_id(dt.Org(fit))[0];
		x[1] = dt.point_at_vertex_id(dt.Dest(fit))[0];
		x[2] = dt.point_at_vertex_id(dt.Apex(fit))[0];
		y[0] = dt.point_at_vertex_id(dt.Org(fit))[1];
		y[1] = dt.point_at_vertex_id(dt.Dest(fit))[1];
		y[2] = dt.point_at_vertex_id(dt.Apex(fit))[1];
		
		for (i = 0; i < iVirtualMikes; i++)
			for (k = 0; k < 3; k++)
				if ((x[k] == MikesCoordinates[2*i])&&(y[k] == MikesCoordinates[2*i + 1]))
				{
					mic[k] = i; //Find and save mic # for each vertex.
				}
		
		VirtualMike* pvmCurrent;
		
		for (i = 0; i < vmsMirroredMikes->GetNumberOfMikes(); i++)
			for (k = 0; k < 3; k++)
			{
				pvmCurrent = vmsMirroredMikes->GetVirtualMike(i);
				if ((x[k] == pvmCurrent->GetX())&&(y[k] == pvmCurrent->GetY()))
				{
					mic[k] = pvmCurrent->GetMicID(); //Find and save original mic # for each mirrored mike too.
				}
			}
		tmMeshes[j] = new TriangularMesh(x,y,mic);
		++fit;
	}
	return true;
}

bool MicArrayAnalyzer::Calculate(unsigned int frame)
{	
	try{ //catching out-of-memory situations
#ifdef __AUDEBUG__
		//	mAAcritSec->Enter(); //DEBUG per avere i printf coerenti tutti in serie
		printf("MicArrayAnalyzer::Calculate(%d): copying ppfAudioData into ActualFrameAudioData\n",frame);
		fflush(stdout);
#endif		
		
		//init ActualFrameAudioData
		for (int c=0; c<iProjectNumTracks; ++c) {		
			int ActualFrameLengthSmpl = GetFrameLengthSmpl();
			ActualFrameAudioData[c] = new float [ActualFrameLengthSmpl];
		}
		
		sampleCount startFrameSmpl = (frame-1)*(m_frameLengthSmpl - m_frameLengthSmpl*m_frameOverlapRatio); // frame is bound between 1 and numofFrames but we want the first frame to start from the first sample (0)
		sampleCount endFrameSmpl = startFrameSmpl + m_frameLengthSmpl;
		bool lastframe = false;
		int zeropadding=0;
		if (endFrameSmpl >=	iAudioTrackLength) { //on the last frame, cut!
			zeropadding = endFrameSmpl-iAudioTrackLength;
			endFrameSmpl = iAudioTrackLength;
			lastframe=true;
		}
		
		for (int i=0; i<iProjectNumTracks; i++) {  //copy data into actual frame
			for (int j=startFrameSmpl; j<endFrameSmpl; j++) { 
				ActualFrameAudioData[i][j-startFrameSmpl] = ppfAudioData[i][j];
			}
		}
		
		if (lastframe) { //on the last frame, zero padding!
			for (int i=0; i<iProjectNumTracks; i++) { 
				for (int j=endFrameSmpl; j<endFrameSmpl+zeropadding; j++) {    
					ActualFrameAudioData[i][j-startFrameSmpl] = 0;
				}
			}	
		}
		
#ifdef __AUDEBUG__
		printf("MicArrayAnalyzer::Calculate(%d): hanning windowing\n",frame);
		fflush(stdout);
#endif
		for (int c=0; c<iProjectNumTracks; ++c) {			
			for (int i=0; i<m_frameLengthSmpl; ++i) {
//				ActualFrameAudioData[c][i]=0.5*(1-cos(2*M_PI*i/(m_frameLengthSmpl-1)));
				ActualFrameAudioData[c][i] *= m_window[i];
			}
		}
		
		//#ifdef __AUDEBUG__
		//	PrintActualFrame(frame);
		//	fflush(stdout);
		//#endif
		if(!bMirroredMikesAlloc)
		{		
			if (!Triangulate_and_mesh()) {			
				printf("MicArrayAnalyzer::Calculate(): Triangulate_and_mesh...FAILED\n");
				fflush(stdout);
				return false;
			}
		}
		
#ifdef __AUDEBUG__
		
		printf("MicArrayAnalyzer::Calculate(): Audiopool...");
		fflush(stdout);
#endif
		if(!m_bfdBScalingFactorAlloc) {
			CalculateFSScalingFactor();   //Finding the project track with the max absolute level, and computing the ratio between this level and the local peak level of the same track. This will be used as a trick to associate dFSLevel with the absolute max without the need of convolving the entire recording!
		}
		apOutputData = new AudioPool(iVirtualMikes,dFSLevel - double(fdBScalingFactor),dProjectRate); //AudioPool alloc
		for(int i=0; i<iVirtualMikes; i++)
		{
			apOutputData->SetTrack(i,ActualFrameAudioData[i], m_frameLengthSmpl, true); 
		}
		
		
		//Calculating Results
		if (apOutputData->FillResultsMatrix()) {
			//construct video frame...
			double** resultmatrix=apOutputData->GetResultsMatrix();
			int channelsnumber= apOutputData->GetChannelsNumber();
			double maxresultinthematrix = apOutputData->GetMaxResultInTheMatrix();
			double minresultinthematrix = apOutputData->GetMinResultInTheMatrix();
			VideoFrame* videoframe= new VideoFrame(resultmatrix,
												   channelsnumber,
												   frame,
												   maxresultinthematrix,
												   minresultinthematrix);
			for (int band=0; band<12; band++) {
				videoframe->SetMaxInTheBand(apOutputData->GetMaxResultInTheBand(band), band);
				videoframe->SetMinInTheBand(apOutputData->GetMinResultInTheBand(band), band);
			}
			
			//... and add it to the video!
			mAAcritSec->Enter();
			
			if(*m_bErrorOutOfMemory) return false;
			
			outputFrames->AddFrame(videoframe);
						
			if (!SetBGNDVideoBmp(frame)) //retrieve and add to videoframe respective ppm file (saved during EncodeFrames() )
			{
				std::cout<<"\nCalculate(): ERROR can't save background image!"<<std::endl;
				outputFrames->DeleteFrame(frame);
			}
			
			bResultsAvail = true;
			//		PrintResult(frame);
			mAAcritSec->Leave();
			
						
			//build SPL map 
			if (!InitLevelsMap(frame))
				return false;
			
			//		mAAcritSec->Leave();
		}
		else { 
			bResultsAvail = false; 
			//		mAAcritSec->Leave();
		}
		
	
		
		//THE END!
		
	} catch (bad_alloc& ex) {
		cout << "\n\nCalculate(): Memory not allocated !!\n\n";
		return false;
    }
	return true;
}

void MicArrayAnalyzer::AudioDataInit()
{
	if (bAudioDataAlloc)
	{
		delete [] ppfAudioData;
		delete [] pfLocalMin;
		delete [] pfLocalMax;
		delete [] pfAbsoluteMin;
		delete [] pfAbsoluteMax;
	}
	ppfAudioData = new float* [iProjectNumTracks];
	ActualFrameAudioData = new float* [iProjectNumTracks];
	pfLocalMin = new float [iProjectNumTracks];
	pfLocalMax = new float [iProjectNumTracks];
	pfAbsoluteMin = new float [iProjectNumTracks];
	pfAbsoluteMax = new float [iProjectNumTracks];
	bAudioDataAlloc = true;
	
	for (int i = 0; i < iProjectNumTracks; i++) {ppfAudioData[i] = 0; ActualFrameAudioData[i]=0;}  //Init each pointer to zero!
}

bool MicArrayAnalyzer::AudioTrackInit(int i, int length)
{
	if (!bAudioDataAlloc) return false; //Main audio tracks array not init before!!!
	else
	{
		ppfAudioData[i] = new float [length];
		return true;
	}
}

void MicArrayAnalyzer::CalculateFSScalingFactor()
{
	float max;
	int ch = 0;
	
	max = fabs(pfAbsoluteMax[ch]); //Init
	for (int i=1;i<iProjectNumTracks;i++)
	{  //Searching for the track with the stronger peak level.
		if (fabs(pfAbsoluteMax[i]) > max)
		{
			max = fabs(pfAbsoluteMax[i]);    
			ch = i;  //Need to be remembered 'cause the scaling factor will be computed as the ratio between absolute and local max of this channel.
		}
	}
	
	fdBScalingFactor = dB20(fabs(pfAbsoluteMax[ch]) / fabs(pfLocalMax[ch]));  //Stored in dB!!!!
	m_bfdBScalingFactorAlloc=true;
}

bool MicArrayAnalyzer::SetAudioTrackLength(int len)
{
	if(!iAudioTrackLength) iAudioTrackLength = len;
	return (iAudioTrackLength != len) ? false: true; //Return false if there's a length mismatch!
}


wxString MicArrayAnalyzer::GetWAVFormatName()
{
	if (((sfinfo.format & WAV_FORMAT_ANDMASK)==SF_FORMAT_PCM_S8) || ((sfinfo.format & WAV_FORMAT_ANDMASK)==SF_FORMAT_PCM_U8)) return _("8-bit PCM");
	else if ((sfinfo.format & WAV_FORMAT_ANDMASK)==SF_FORMAT_PCM_16) return _("16-bit PCM");
	else if ((sfinfo.format & WAV_FORMAT_ANDMASK)==SF_FORMAT_PCM_24) return _("24-bit PCM");
	else if ((sfinfo.format & WAV_FORMAT_ANDMASK)==SF_FORMAT_FLOAT) return _("32-bit float");
	else return wxEmptyString;
}

sampleFormat MicArrayAnalyzer::GetWAVSampleFormat()
{
	if ((sfinfo.format & WAV_FORMAT_ANDMASK)==SF_FORMAT_PCM_16) return int16Sample;
	else if ((sfinfo.format & WAV_FORMAT_ANDMASK)==SF_FORMAT_PCM_24) return int24Sample;
	else if ((sfinfo.format & WAV_FORMAT_ANDMASK)==SF_FORMAT_FLOAT) return floatSample;
	return int16Sample;     // [esseci] sostuire int16Sample con un default
}

bool MicArrayAnalyzer::SetBgndImage(const wxString& str)
{
	if (bBgndImageAlloc) delete wxfnBgndImageFile;
	else bBgndImageAlloc = true;
	wxfnBgndImageFile = new wxFileName(str);
	
	if ( !wxbBgndImage.LoadFile(wxfnBgndImageFile->GetFullPath(), wxBITMAP_TYPE_JPEG) ) {
		return false;
	}
	
	return true; // [esseci] else qui non ha senso...
}

bool MicArrayAnalyzer::SetBgndVideo(const wxString& str)
{
	if (bBgndVideoAlloc) 
	{ 
		delete wxfnBgndVideoFile;
		//		m_vBgndVideo.clear();
	}
	else bBgndVideoAlloc = true;
	wxfnBgndVideoFile = new wxFileName(str);
	char videofilepath[100];
	strcpy(videofilepath, (const char*) wxfnBgndVideoFile->GetFullPath().mb_str(wxConvUTF8));
	char standardTMPdir[100];
	strcpy(standardTMPdir, (const char*) m_tmpDirPath.mb_str(wxConvUTF8));
	int start_ms = iAudioTrackStart / dProjectRate *1000;
	int end_ms = iAudioTrackEnd / dProjectRate *1000;
	
	
	m_bgndVideoFrameRate = EncodeFrames(videofilepath, standardTMPdir,start_ms,end_ms);  //TODO calculate it to a separate thread!	
	m_bgndVideoFrameRate = m_bgndVideoFrameRate / 2 ; /// !!! is it right? it seems that the real fps value is half the value ffmpeg is finding

	return true; 
}


void MicArrayAnalyzer::SetWAVFile(const wxString& str)
{
	if (bWAVFileAlloc) { delete wxfnWAVFile; }
	else { bWAVFileAlloc = true; }
	wxfnWAVFile = new wxFileName(str);
	wxfnWAVFile->MakeAbsolute(wxfnXMLFile->GetPath()); //Making the WAV file path absolute!
}

void MicArrayAnalyzer::SetXMLFile(const wxString& str)
{
	if (bXMLFileAlloc) { delete wxfnXMLFile; }
	else { bXMLFileAlloc = true; }
	wxfnXMLFile = new wxFileName(str);
}

bool MicArrayAnalyzer::BadXML()
{
	string sBuffer;
	sBuffer = string((wxfnXMLFile->GetFullPath()).mb_str()); //Converting the file path from wxString to string.
	TiXmlDocument doc((char*)sBuffer.c_str()); //Creating a new TiXmlDocument object loading data from file.
	if (!doc.LoadFile()) return true;
	TiXmlElement *root;
	root = doc.FirstChildElement("MicArrayData"); //Trying to retrieve the root node, considered as an header for the config file.
	if (!root) return true;
	return false;
}

bool MicArrayAnalyzer::BadWAV()
{
	string sBuffer;
	sBuffer = string((wxfnWAVFile->GetFullPath()).mb_str()); //Converting the file path from wxString to string.
	if (!(infile = sf_open((char*)sBuffer.c_str(),SFM_READ,&sfinfo))) { bSndFileAlloc = true; return true; }
	else { return false; }
}

bool MicArrayAnalyzer::ReadXMLData()
{
	string sBuffer;
	sBuffer = string((wxfnXMLFile->GetFullPath()).mb_str()); //Converting the file path from wxString to string.
	TiXmlDocument doc((char*)sBuffer.c_str());   //Creating a new TiXmlDocument object loading data from file.
	if (doc.LoadFile())
	{
		//File loaded correctly
		TiXmlElement *root,*data,*mic_coord;
		root = doc.FirstChildElement("MicArrayData");
		data = root->FirstChildElement("Data");
		if (data)
		{
			//main data node found correctly
			wxsMicName = cs2ws(data->Attribute("MicName"));
			wxsManufacturer = cs2ws(data->Attribute("Manufacturer"));
			iArrayType = atoi(data->Attribute("ArrayType"));
			iCapsules = atoi(data->Attribute("Capsules"));
			iVirtualMikes = atoi(data->Attribute("VirtualMikes"));
			wxString tmp(cs2ws(data->Attribute("DeconvIRsWAVFile")));
			if (!tmp.IsNull()) SetWAVFile(tmp);
			iDeconvIRsLength = atoi(data->Attribute("DeconvIRsLength"));
			iMikesCoordsUnits = atoi(data->Attribute("MikesCoordsUnits"));
			
			//Alloc a new coord table of the correct size
			if(bMikesCoordsAlloc) delete MikesCoordinates;
			else { bMikesCoordsAlloc = true; }
			MikesCoordinates = new double[iVirtualMikes*2];
			
			mic_coord = data->FirstChildElement("Mic_1");
			if (!mic_coord) return false;  //ERROR
			else
            {
				int i=0;
				ostringstream oss;
				while (mic_coord)
				{
					MikesCoordinates[2*i] = atof(mic_coord->Attribute("X"));
					MikesCoordinates[2*i + 1] = atof(mic_coord->Attribute("Y"));
					
					//Retrieving the next node
					i++;
					oss.str("");   //Clear the ostringstream
					oss << i + 1;
					sBuffer = "Mic_" + oss.str();
					mic_coord = data->FirstChildElement((char*)(sBuffer.c_str()));
				}
            }
		}
		else return false; //ERROR
	}
	else return false; //ERROR
	
	return true;
}

//void MicArrayAnalyzer::InitProgressMeter(const wxString& operation)
//{
//	mProgress = new ProgressDialog(_("Mic Array Analyzer"),operation);
//}
//
//bool MicArrayAnalyzer::UpdateProgressMeter(int step,int total)
//{
//	return bool(mProgress->Update(step, total) == eProgressSuccess); // [esseci] 
//}
//
//void MicArrayAnalyzer::DestroyProgressMeter()
//{
//	if(mProgress) delete mProgress;
//	mProgress = 0;
//}

bool MicArrayAnalyzer::GetMirroredMike(double original_x, double original_y, double* mirror_xy, int mirror_num, int arrayType)
{
	int quadrantA = 0, quadrantB = 0, quadrantC = 0, quadrantD = 0;
	
	if (original_x <= (X_RES/2))
	{
		if (original_y <= (Y_RES/2))   //Quadrant C
			quadrantC = 1;
		else if (original_y > (Y_RES/2))   //Quadrant A
			quadrantA = 1;
		else return false;
	}
	else if (original_x > (X_RES/2))
	{
		if (original_y <= (Y_RES/2))   //Quadrant D
			quadrantD = 1;
		else if (original_y > (Y_RES/2))   //Quadrant B
			quadrantB = 1;
		else return false;
	}
	else return false;
	
	switch (mirror_num)
	{
			//This equations could be further simplified, I know.... :-)
		case 0:
			mirror_xy[0] = quadrantA*(X_RES+original_x) + quadrantB*(original_x-X_RES) + quadrantC*(X_RES+original_x) + quadrantD*(original_x-X_RES);
			mirror_xy[1] = quadrantA*(original_y) + quadrantB*(original_y) + quadrantC*(original_y) + quadrantD*(original_y);
			break;
		case 1:
			if (iArrayType == 0 ) //spherical 
			{
				mirror_xy[0] = quadrantA*(X_RES-original_x) + quadrantB*(2*X_RES-original_x) + quadrantC*(X_RES-original_x) + quadrantD*(2*X_RES-original_x);
				mirror_xy[1] = quadrantA*(2*Y_RES-original_y) + quadrantB*(2*Y_RES-original_y) + quadrantC*(-original_y) + quadrantD*(-original_y);
			}
			break;
		case 2:
			if (iArrayType == 0 ) //spherical 
			{
				mirror_xy[0] = quadrantA*(-original_x) + quadrantB*(X_RES-original_x) + quadrantC*(-original_x) + quadrantD*(X_RES-original_x);
				mirror_xy[1] = quadrantA*(2*Y_RES-original_y) + quadrantB*(2*Y_RES-original_y) + quadrantC*(-original_y) + quadrantD*(-original_y);
			}
			break;
		default:
			return false;
	}
	
	return true;
}

//double MicArrayAnalyzer::GetMaxSPL(bool autoscale_each_band, int band)
//{
//	double value = dMinSPLThreshold;
//	
//	if (bResultsAvail)
//	{
//		if (autoscale_each_band) { value = apOutputData->GetMaxResultInTheBand(band); }
//		else { value = apOutputData->GetMaxResultInTheMatrix(); }
//		
//		if (value < dMinSPLThreshold) { value = dMinSPLThreshold; }
//	}
//	
//	return value;
//}
//
//double MicArrayAnalyzer::GetMinSPL(bool autoscale_each_band, int band)
//{
//	double value = dMinSPLThreshold;
//	
//	if (bResultsAvail)
//	{
//		if (autoscale_each_band) { value = apOutputData->GetMinResultInTheBand(band); }
//		else { value = apOutputData->GetMinResultInTheMatrix(); }
//		
//		if (value < dMinSPLThreshold) { value = dMinSPLThreshold; }
//	}
//	
//	return value;
//}

double MicArrayAnalyzer::GetMaxSPL(bool autoscale_each_band, int band)
{
	double value = dMinSPLThreshold;
	
	if (bResultsAvail)
	{
		if (autoscale_each_band) { value = outputFrames->GetOverallBandMax(band); }
		else { /*value = outputFrames->GetOverallMax(); */ value= dFSLevel;}
		
		if (value < dMinSPLThreshold) { value = dMinSPLThreshold; }
	}
	
	return value;
}

double MicArrayAnalyzer::GetMinSPL(bool autoscale_each_band, int band)
{
	double value = dMinSPLThreshold;
	
	if (bResultsAvail)
	{
		if (autoscale_each_band) { value = outputFrames->GetOverallBandMin(band); }
		else { value = outputFrames->GetOverallMin(); }
		
		if (value < dMinSPLThreshold) { value = dMinSPLThreshold; }
	}
	
	return value;
}

void MicArrayAnalyzer::PrintResults() {
	for (int f=1; f<=GetNumOfFrames(); f++) {
		
		printf("\n\n*** RESULTS MATRIX no [%d] *** (PRESSURE levels, not dB)\nCH#\tLIN\tA\t31.5\t63\t125\t250\t500\t1k\t2k\t4k\t8k\t16k\n", f);
		double ** matrix=outputFrames->GetFrameMatrix(f);
		
		for (int i = 0; i < sfinfo.channels; i++) //For each audio track
		{
			printf("%d\t",i);
			for (int j = 0; j < (2+10); j++) //For each band
			{
				printf("%1.4f\t",undB20(float(matrix[i][j])));
			}
			printf("\n");
			fflush(stdout);
		}
	}
}

void MicArrayAnalyzer::PrintResult(unsigned int f) {
	
	printf("\n\n*** RESULTS MATRIX no [%d] *** (PRESSURE levels, not dB)\nCH#\tLIN\tA\t31.5\t63\t125\t250\t500\t1k\t2k\t4k\t8k\t16k\n", f);
	double ** matrix=outputFrames->GetFrameMatrix(f);
	
	for (int i = 0; i < sfinfo.channels; i++) //For each audio track
	{
		printf("%d\t",i);
		for (int j = 0; j < (2+10); j++) //For each band
		{
			printf("%1.4f\t",undB20(float(matrix[i][j])));
		}
		printf("\n");
		fflush(stdout);
	}
}

void MicArrayAnalyzer::PrintLevels() {
	for (int f=1; f<=GetNumOfFrames(); f++) {
		
		printf("\n\n*** LEVELS MATRIX no [%d] --- a part of it 10x10 --- *** (dB on vertex)\n", f);
		double ** matrix=outputFrames->GetFrameLevels(f, 0);
		
		for (int i = 0; i < 10; i++)
		{
			for (int k = 0; k < 10; k++)
			{
				printf("%1.4f  ",matrix[i][k]);
			}
			printf("\n");
			fflush(stdout);
		}
	}
}

void MicArrayAnalyzer::PrintActualFrame(int frame) {
	
	printf("\n\n*** ACTUAL FRAME # %d -PART- *** ", frame);
	for (int j = 0; j < 50; j++) 
	{
		for (int i=0; i < iProjectNumTracks; i++)
		{
			printf("  %f  ", ActualFrameAudioData[i][j]);
		}
		printf("\n");
		fflush(stdout);
	}
	printf("\n\n");
}

int MicArrayAnalyzer::GetCurTime_ms() 
{
	int ms =  iAudioTrackLength / dProjectRate * 1000; //millisec
	double progressRatio = (double)(m_curFrame-1) / (outputFrames->GetNumOfFrames() - 1) ;
	ms = (double)ms * progressRatio;
	ms += iAudioTrackStart / dProjectRate * 1000; //millisec of audio seleciont starting point
	return ms;
}

wxString MicArrayAnalyzer::GetCurTime_Str() 
{
	wxString str; 
	int ms = GetCurTime_ms();
	int h = ms / 1000 / 3600;
	ms = ms % 3600000; //remaining milliseconds without hours
	int m = ms / 1000 / 60;
	ms = ms % 60000; // remaining milliseconds without minutes
	int s = ms / 1000;
	ms = ms % 1000;  // remaining milliseconds without seconds
	if (h>0) 
		str.Printf(wxT("%02d:%02d:%02d:%03d"), h, m, s , ms);
	else
		str.Printf(wxT("%02d:%02d:%03d"), m, s , ms);
	return str;
}

int MicArrayAnalyzer::GetCurVideoFrameNum()
{
	return (double)GetCurTime_ms()/1000.0 * m_bgndVideoFrameRate; //current background video frame number

}

wxBitmap MicArrayAnalyzer::GetBGNDVideoBmp() 
{
	//	if (bBgndVideoAlloc) 
	//	{
	//		int bgndVideoFrameNum = (double)GetCurTime_ms()/1000.0 * m_bgndVideoFrameRate; //current background video frame number
	//		return m_vBgndVideo[bgndVideoFrameNum];
	//	} 
	//	else 
	//	{	
	return outputFrames->GetBgndImage(m_curFrame);
	//	} 
}

bool MicArrayAnalyzer::SetBGNDVideoBmp(int frame) 
{
	wxString szFilePath(m_tmpDirPath);
	wxString szFilename;
	wxBitmap wxbdumb;
	int actualframe = m_curFrame; //save it for later..
	m_curFrame = frame;
	int bgndVideoFrameNum = GetCurVideoFrameNum();
	if (bgndVideoFrameNum==0) 
		bgndVideoFrameNum++;
	szFilename.Printf( _("frame%d.ppm"), bgndVideoFrameNum);
	szFilePath.append(szFilename);
	
	//#ifdef __AUDEBUG__
	//	std::cout<<szFilePath.mb_str(wxConvUTF8);
	//#endif
	if ( !wxbdumb.LoadFile(szFilePath, wxBITMAP_TYPE_PNM) ) {
		return false; //TODO if other thread ripping the video hasn't finished then wait for him
	}
	//Background Image Size Check (and scaling if necessary)
	if ((wxbdumb.GetWidth() != X_RES)||(wxbdumb.GetHeight() != Y_RES))
	{
		//We need to scale choosen image to fit image panel dimensions
		wxImage tmp = wxbdumb.ConvertToImage();
		tmp = tmp.Scale(X_RES,Y_RES,wxIMAGE_QUALITY_HIGH);
		wxbdumb = wxBitmap(tmp);
	}
	
	outputFrames->SetBgndImage(wxbdumb, m_curFrame);
	m_curFrame = actualframe; //.. and set it back
	return true;
}






//-----------------------------
// AudioPool Class
//-----------------------------
AudioPool::AudioPool(const int nTracks, double dBFullScale, double Fs) : AFAudioTrack(nTracks), bResultsMatrixAlloc(false), mProgress(0)
{
	//Octave band filters center frequencies
	dFcOctaveBandFilters[0] = 31.5;
	dFcOctaveBandFilters[1] = 63.0;
	dFcOctaveBandFilters[2] = 125.0;
	dFcOctaveBandFilters[3] = 250.0;
	dFcOctaveBandFilters[4] = 500.0;
	dFcOctaveBandFilters[5] = 1000.0;
	dFcOctaveBandFilters[6] = 2000.0;
	dFcOctaveBandFilters[7] = 4000.0;
	dFcOctaveBandFilters[8] = 8000.0;
	dFcOctaveBandFilters[9] = 16000.0;
	
	//Octave band filters border frequencies. They will be divided for the width of a single spectrum line as soon as we know it
	m_dOctaveOnSpectrum[0] = 22;
	m_dOctaveOnSpectrum[1] = 44;
	m_dOctaveOnSpectrum[2] = 88;
	m_dOctaveOnSpectrum[3] = 177;
	m_dOctaveOnSpectrum[4] = 355;
	m_dOctaveOnSpectrum[5] = 710;
	m_dOctaveOnSpectrum[6] = 1420;
	m_dOctaveOnSpectrum[7] = 2840;
	m_dOctaveOnSpectrum[8] = 5680;
	m_dOctaveOnSpectrum[9] = 11360;
	m_dOctaveOnSpectrum[10] = 22720;
	
	//Setting FS level.
	SetFullScale(dBFullScale);
	
	//Setting sampling freq
	SetSamplerate(Fs);
}

AudioPool::~AudioPool()
{
	if(mProgress) delete mProgress;
	mProgress = 0;
	if(bResultsMatrixAlloc) delete [] ppdResultsMatrix;
}

double AudioPool::FindOverallMax()
{
	double max = 0.0;
#ifdef __AUDEBUG__
	double oldmax = 0.0;
#endif
	for(int i = 0; i < m_nChannels; i++) //For every audio track
	{
		for(int j = 0; j < m_smpcLen; j++) //For every sample
		{
#ifdef __AUDEBUG__
            oldmax = max;
#endif
			max = (fabs(m_apsmpTrack[i][j]) > max) ? fabs(m_apsmpTrack[i][j]) : max;
#ifdef __AUDEBUG__
            if (max != oldmax)
			{
				printf("FindOverallMax(): new max found on CH[%d] @ sample[%d] = %f\n",i,j,max);
				fflush(stdout);
			}
#endif
		}
	}
	return max;
}

bool AudioPool::ApplyOverallGain(double gain)
{
#ifdef __AUDEBUG__
	printf("AudioPool: Applying overall gain of %f\n",gain);
	fflush(stdout);
#endif
	for(int i = 0; i < m_nChannels; i++) //For every audio track
	{
		for(int j = 0; j < m_smpcLen; j++) //For every sample
		{
			m_apsmpTrack[i][j] = gain * m_apsmpTrack[i][j];
		}
	}
	return true;
}

bool AudioPool::FillResultsMatrix()
{
	//Memory init
	ResultsMatrixInit();
	
	assert(!(m_smpcLen & (m_smpcLen - 1))); // is power of two!
	
	int fNyquist = m_smpcLen/2+1;
	
	float deltaF = (m_dbRate/2)/(fNyquist);
	float powerspectrum[fNyquist];
	float filterA[fNyquist];
	float dBALut[10] = {-39.4, 
						-26.2, 
						-16.1,
						-8.6,
						-3.2,
						0.0,
						1.2,
						1.0,
						-1.1,
						-6.6};
	float singlebandacc[12]; //results for each band [lin, A, band0, band1, band2, ... , band9]
	
	for (int c=0; c<m_nChannels; ++c) 
	{
		//spettro di potenza
		PowerSpectrum(m_smpcLen, m_apsmpTrack[c], powerspectrum);	
		
		// band energy accumulation
		/*
		 * [0] accumulate linear filter with all the spectral lines but the ones from the first two bands.
		 * [1] accumulate A-filtered spectral lines.
		 * [2-11] accumulate every band with the spectral lines inside the related interval.
		 */
		
		//init accumulation structures
		for (int i=0; i<10+2; ++i) {
			singlebandacc[i]=0;
		}
		
		for (int i=m_dOctaveOnSpectrum[0]; i<fNyquist; ++i) {
			if(i<m_dOctaveOnSpectrum[1]) // band (31,5 Hz)
			{
				singlebandacc[2] += powerspectrum[i];
			}
			else if(i<m_dOctaveOnSpectrum[2]) // band (63 Hz)
			{
				singlebandacc[3] += powerspectrum[i];
			}
			else if(i<m_dOctaveOnSpectrum[3]) // band (125 Hz)
			{
				singlebandacc[4] += powerspectrum[i];
//				singlebandacc[0] += powerspectrum[i];
			}
			else if(i<m_dOctaveOnSpectrum[4]) // band (250 Hz)
			{
				singlebandacc[5] += powerspectrum[i];
//				singlebandacc[0] += powerspectrum[i];
			}
			else if(i<m_dOctaveOnSpectrum[5]) // band (500 Hz)
			{
				singlebandacc[6] += powerspectrum[i];
//				singlebandacc[0] += powerspectrum[i];
			}
			else if(i<m_dOctaveOnSpectrum[6]) // band (1000 Hz)
			{
				singlebandacc[7] += powerspectrum[i];
//				singlebandacc[0] += powerspectrum[i];
			}
			else if(i<m_dOctaveOnSpectrum[7]) // band (2000 Hz)
			{
				singlebandacc[8] += powerspectrum[i];
//				singlebandacc[0] += powerspectrum[i];
			}
			else if(i<m_dOctaveOnSpectrum[8]) // band (4000 Hz)
			{
				singlebandacc[9] += powerspectrum[i];
//				singlebandacc[0] += powerspectrum[i];
			}
			else if(i<m_dOctaveOnSpectrum[9]) // band (8000 Hz)
			{
				singlebandacc[10] += powerspectrum[i];
//				singlebandacc[0] += powerspectrum[i];
			}
			else if(i<m_dOctaveOnSpectrum[10]) // band (16000 Hz)
			{
				singlebandacc[11] += powerspectrum[i];
//				singlebandacc[0] += powerspectrum[i];
			}
//			if(i>m_dOctaveOnSpectrum[0] && i<m_dOctaveOnSpectrum[10])  // db(A)
//			{
//				float f = i*deltaF+deltaF/2; // central frequency of the spectral line
//				double num = 3.5041384*powf(10.0, 16.0)*powf(f, 8);
//				double denA = (20.598997*20.598997 + f*f);
//				double denB = (107.65265*107.65265 + f*f);
//				double denC = (737.86223*737.86223 + f*f);
//				double denD = (12194.217*12194.217 + f*f);
//				double A = 10*log10(num / ( denA*denA * denB * denC * denD*denD )) ;
//				filterA[i]=A; // save the A-filter coefficients----------------------------------------->> (is it futile?)
//				singlebandacc[1] += pow(10, (dB(powerspectrum[i]) + A) /10); // acc + 10^(Li/10) 
//			}
		} // spectral lines cycle
		
		//fill result matrix !
		for (int b=2; b<12; ++b) {
//			singlebandacc[0] += singlebandacc[b]; // acc over Lin
			singlebandacc[b]=dB(singlebandacc[b]); //band power -> dB
			ppdResultsMatrix[c][b] = singlebandacc[b]; //save band level result
			
			if(b>3) {
			singlebandacc[0] += powf(10, singlebandacc[b] / 10); // acc + 10^(Li/10) 
			}
			singlebandacc[1] += powf(10, (singlebandacc[b] + dBALut[b-2]) / 10)  ; // A weighting
		}
//		singlebandacc[0] = dB(singlebandacc[0]);
	
		singlebandacc[0] = 10*log10f(singlebandacc[0] / (12-2-2)); //energetic mean (Lin)
//		singlebandacc[1] = 10*log10f(singlebandacc[1] / (fNyquist - m_dOctaveOnSpectrum[0])); //energetic mean (Lin dB(A))
		singlebandacc[1] = 10*log10f(singlebandacc[1] / (12-2)); //energetic mean (Lin dB(A))
		ppdResultsMatrix[c][1] = singlebandacc[1]; //save lin(dBA) level result
		ppdResultsMatrix[c][0] = singlebandacc[0]; //save lin level result

	}
	return true;
}

//bool AudioPool::FillResultsMatrix()
//{
//	//Memory init
//	ResultsMatrixInit();
//
//	//Results Matrix Calculation
//	//	InitProgressMeter(_("Calculating levels for each audio band..."));
//	//#ifdef __AUDEBUG__
//	//	printf("AudioPool: Filling results matrix...");
//	//	fflush(stdout);
//	//#endif
//	//	printf("*** RESULTS MATRIX *** (PRESSURE levels, not dB)\nCH#\tLIN\tA\t31.5\t63\t125\t250\t500\t1k\t2k\t4k\t8k\t16k\n");
//	for (int i = 0; i < m_nChannels; i++) //For each audio track
//	{
//		//		printf("%d\t",i);
//		for (int j = 0; j < (2+10); j++) //For each band
//		{
//			//			UpdateProgressMeter(i*(2+10) + j,(m_nChannels)*(2+10));
//			
//			if (j == 0)
//            {  //Linear Filter
//				ResetFilteredTrack(i);
//				LFilter(i); //Linear filtering track #i
//				ppdResultsMatrix[i][j] = LeqFilteredTrack(i); //Storing squared mean level inside results matrix.
//            }
//			else if (j == 1)
//            {  //A-weighted
//				ResetFilteredTrack(i);
//				AFilter(i); //A-weighting track #i
//				ppdResultsMatrix[i][j] = LeqFilteredTrack(i); //Storing mean squared level inside results matrix.
//            }
//			else
//            {  //Octave bands
//				ResetFilteredTrack(i);
//				OctaveFilter(i,dFcOctaveBandFilters[j-2]); //Octave band filtering track #i
//				ppdResultsMatrix[i][j] = LeqFilteredTrack(i); //Storing mean squared level inside results matrix.
//            }
//			//			printf("%1.4f\t",undB20(float(ppdResultsMatrix[i][j])));
//		}
//		//		printf("\n");
//		fflush(stdout);
//	}
//	
//#ifdef __AUDEBUG__
//	//	printf("AudioPool: Filling results matrix...DONE\n");
//	//	fflush(stdout);
//#endif
//	//	DestroyProgressMeter();
//	return true;
//}

double AudioPool::GetMaxResultInTheMatrix()
{
	if (bResultsMatrixAlloc)
	{
		double max;
		max = GetMaxResultInTheBand(0);
		for (int i=1;i<12;i++)
		{
			max = (GetMaxResultInTheBand(i) > max) ? GetMaxResultInTheBand(i) : max;
		}
#ifdef __AUDEBUG__
		printf("AudioPool::GetMAXResultInTheMatrix = %f\n", max);
		fflush(stdout);
#endif
		return max;
	}
	else { return 0; }
}

double AudioPool::GetMaxResultInTheBand(int col)
{
	if (bResultsMatrixAlloc)
	{
		double max;
		max = ppdResultsMatrix[0][col]; //Remember that levels are saved as dB -> are always >= 0! -> ABS(x) not needed.
		for (int i=1;i<m_nChannels;i++)
		{
			max = (ppdResultsMatrix[i][col] > max) ? ppdResultsMatrix[i][col] : max;
		}
		//#ifdef __AUDEBUG__
		//		printf("AudioPool::GetMAXResultInTheBand: band [%d] = %f\n",col,max);
		//		fflush(stdout);
		//#endif
		return max;
	}
	else { return 0; }
}

double AudioPool::GetMinResultInTheMatrix()
{
	if (bResultsMatrixAlloc)
	{
		double min;
		min = GetMinResultInTheBand(0);
		for (int i=1;i<12;i++)
		{
			min = (GetMinResultInTheBand(i) < min) ? GetMinResultInTheBand(i) : min;
		}
#ifdef __AUDEBUG__
		printf("AudioPool::GetMINResultInTheMatrix = %f\n",min);
		fflush(stdout);
#endif
		return min;
	}
	else { return 0; }
}

double AudioPool::GetMinResultInTheBand(int col)
{
	if (bResultsMatrixAlloc)
	{
		double min;
		min = ppdResultsMatrix[0][col]; //ABS(x) not needed too.
		for (int i=1;i<m_nChannels;i++)
		{
			min = (ppdResultsMatrix[i][col] < min) ? ppdResultsMatrix[i][col] : min;
		}
		//#ifdef __AUDEBUG__
		//		printf("AudioPool::GetMINResultInTheBand: band [%d] = %f\n",col,min);
		//		fflush(stdout);
		//#endif
		return min;
	}
	else { return 0; }
}



bool AudioPool::ResultsMatrixInit()
{
#ifdef __AUDEBUG__
	printf("AudioPool: Results Matrix INIT\n");
	fflush(stdout);
#endif
	if (bResultsMatrixAlloc) 
		delete [] ppdResultsMatrix;
	ppdResultsMatrix = new double* [m_nChannels];
	
	for (int i = 0; i < m_nChannels; i++)
	{
		ppdResultsMatrix[i] = new double [2+10];                       //2 = Lin + A-Weighted, 10 = 10 bands octave filters, for each audio track!
		for (int j = 0; j < 12; j++) { ppdResultsMatrix[i][j] = 0; }   //Clearing.
	}
	
	bResultsMatrixAlloc = true;
	
	
#ifdef __AUDEBUG__
	printf("AudioPool: band frequencies INIT\n");
	fflush(stdout);
#endif		
	// the power spectrum start from zero to the nyquist frequency (= half sample rate) 
	// so we have to spread the number of spectral lines (= half the sample length) among those frequencies
	float deltaF = m_dbRate/2/(m_smpcLen/2+1);
	
	assert(deltaF != 0);
	
	for (int b=0; b<11; ++b) {
		m_dOctaveOnSpectrum[b] = (float)m_dOctaveOnSpectrum[b] / deltaF;
	}
	return true;
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

