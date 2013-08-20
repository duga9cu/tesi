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
dFSLevel(FS_DEFAULT),
dMinSPLThreshold(MIN_SPL_DEFAULT),
bAudioDataAlloc(false),
bDeconvIRsDataAlloc(false),
iAudioTrackLength(0),
bMirroredMikesAlloc(false),
iNTriangles(0),
bResultsAvail(false),
bWatchpointsAlloc(false),
iWatchpoints(0),
//mProgress(0),
frameLength(FRAMELENGTH),
frameOverlapRatio(FRAMEOVERLAP),
curFrame(1)
{
	outputFrames = new Video();
	mAAcritSec = new wxCriticalSection();
}

MicArrayAnalyzer::MicArrayAnalyzer(const MicArrayAnalyzer& mMAA) : 
//mProgress(mMAA.mProgress),
dMinSPLThreshold(mMAA.dMinSPLThreshold),
dFSLevel(mMAA.dFSLevel),
dProjectRate(mMAA.dProjectRate),
//sfProjectFormat(mMAA.sfProjectFormat), //not used in calculate()
iProjectNumTracks(mMAA.iProjectNumTracks),
iAudioTrackLength(mMAA.iAudioTrackLength),
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
//vmsMirroredMikes(mMAA.vmsMirroredMikes), // initialized in calculate()
//tmMeshes(mMAA.tmMeshes), // initialized in calculate()
iNTriangles(mMAA.iNTriangles),
ppfAudioData(mMAA.ppfAudioData), //* shared among threads! (read-only)
//ActualFrameAudioData(mMAA.ActualFrameAudioData),  //* vedi sotto
//bAudioDataAlloc(false), //* vedi sotto
pfLocalMin(mMAA.pfLocalMin), //* shared (read-only)
pfLocalMax(mMAA.pfLocalMax), //* shared (read-only)
pfAbsoluteMin(mMAA.pfAbsoluteMin),	//* shared (read-only)
pfAbsoluteMax(mMAA.pfAbsoluteMax),	//* shared (read-only)
//fdBScalingFactor(mMAA.fdBScalingFactor), // initialized in calculate()
pppfDeconvIRsData(mMAA.pppfDeconvIRsData), //* shared (read-only) 
bDeconvIRsDataAlloc(mMAA.bDeconvIRsDataAlloc),
//apOutputData(mMAA.apOutputData),	//*  - viene usato solo in calculate()
bResultsAvail(false), //devo ancora calcolare i risultati
//afmvConvolver //*		- viene usato solo in calculate()
 // per ora non uso i watchpoints
//piWatchpoints(mMAA.piWatchpoints),
//iWatchpoints(mMAA.iWatchpoints), 
// wxasWatchpointsLabels(mMAA.wxasWatchpointsLabels),  
//bWatchpointsAlloc(mMAA.bWatchpointsAlloc), 
curFrame(mMAA.curFrame),
frameLength(mMAA.frameLength),
frameLengthSmpl(mMAA.frameLengthSmpl),
frameOverlapRatio(mMAA.frameOverlapRatio),
outputFrames(mMAA.outputFrames), //* shared among threads! 
mAAcritSec(mMAA.mAAcritSec) //* shared among threads!
{
	wxfnBgndImageFile=mMAA.wxfnBgndImageFile;
	ActualFrameAudioData = new float* [iProjectNumTracks];

	bAudioDataAlloc = true;
	
	int ActualFrameLengthSmpl = GetFrameLengthSmpl();
	for (int i=0; i<iProjectNumTracks; i++) {
		ActualFrameAudioData[i] = new float [ActualFrameLengthSmpl];
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
	if(iNTriangles > 0) delete [] tmMeshes;
	if (bAudioDataAlloc) delete [] ppfAudioData;
	if (bDeconvIRsDataAlloc) delete [] pppfDeconvIRsData;
	if(bWatchpointsAlloc) delete [] piWatchpoints;
	
	outputFrames->DeleteAllData();
}


MicArrayAnalyzer::~MicArrayAnalyzer()
{
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

bool MicArrayAnalyzer::Calculate(unsigned int frame)
{
	mAAcritSec->Enter(); //DEBUG per avere i printf coerenti tutti in serie
	
	
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer::Calculate(%d): copying ppfAudioData into ActualFrameAudioData\n",frame);
	fflush(stdout);
#endif
	sampleCount startFrameSmpl = (frame-1)*(frameLengthSmpl - frameLengthSmpl*frameOverlapRatio); // frame is bound between 1 and numofFrames but we want the first frame to start from the first sample (0)
	sampleCount endFrameSmpl = startFrameSmpl + frameLengthSmpl;
	bool lastframe = false;
	int zeropadding=0;
	if (endFrameSmpl >= iAudioTrackLength) { //on the last frame, cut!
		zeropadding=endFrameSmpl-iAudioTrackLength;
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
	PrintActualFrame(frame);
	printf("MicArrayAnalyzer::Calculate(): Background image check and resize\n");
	fflush(stdout);
#endif
	
	//	InitProgressMeter(_("Checking background image size..."));
	
	//Background Image Size Check (and scaling if necessary)
	if ((wxbBgndImage.GetWidth() != X_RES)||(wxbBgndImage.GetHeight() != Y_RES))
	{
		//We need to scale choosen image to fit image panel dimensions
		wxImage tmp = wxbBgndImage.ConvertToImage();
		tmp = tmp.Scale(X_RES,Y_RES,wxIMAGE_QUALITY_HIGH);
		wxbBgndImage = wxBitmap(tmp);
	}
	
	//	UpdateProgressMeter(1,1);
	
	//	DestroyProgressMeter();	

#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer::Calculate(): Adding virtual mikes to Delaunay triangulation.\n");
	fflush(stdout);
#endif
	
	//	InitProgressMeter(_("Adding virtual mikes to the Delaunay triangulation..."));
	
	//Adding mikes to the Delaunay triangulation
	Delaunay::Point tempP;
	vector<Delaunay::Point> v;
	
	if (iArrayType == 0)
	{
#ifdef __AUDEBUG__
		printf("MicArrayAnalyzer::Calculate(): Virtual mikes mirroring ENABLED (spherical array detected).\n");
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
		
		tempP[0] = MikesCoordinates[2*i]; 
		tempP[1] = MikesCoordinates[2*i + 1];
#ifdef __AUDEBUG__
		printf("MicArrayAnalyzer::Calculate(): adding virtual mike [%d]\n",i);
		fflush(stdout);
		//         VirtualMike* pvmDebug;
#endif
		v.push_back(tempP);  //Adding mike to the triangulation
		
		if (iArrayType == 0)
		{
			for (j=0;j<3;j++)   //For each virt. mike, three mirrored mikes exists.
            {
				double dMirroredMike[2];
				GetMirroredMike(MikesCoordinates[2*i],MikesCoordinates[2*i+1],dMirroredMike,j); //Retrieving mirror #j mike coords.
				tempP[0] = dMirroredMike[0]; tempP[1] = dMirroredMike[1];
#ifdef __AUDEBUG__
				printf("MicArrayAnalyzer::Calculate(): adding mirror [%d] of virtual mike [%d]\n",j,i);
				fflush(stdout);
#endif
				v.push_back(tempP);                                     //Adding mirrored mike to the triangulation
				vmsMirroredMikes->AddVirtualMike(tempP[0],tempP[1],i);    //By passing "i" to AddMike we specify that this is a clone of Mic #i.
            }
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
	//	DestroyProgressMeter();

	//Setting up convolution class
#ifdef __AUDEBUG__
	printf("Triangulating...DONE\nMicArrayAnalyzer::Calculate(): Setting up convolution class.\n");
	fflush(stdout);
#endif
    //afmvConvolver = new AFMatrixvolver(sfinfo.channels, iCapsules, iAudioTrackLength, iDeconvIRsLength); //The class constructor wanna know, in order: # of rows, # of columns, Audacity audio data Length, IRs length.
	afmvConvolver = new AFMatrixvolver(sfinfo.channels, iCapsules, GetFrameLengthSmpl(), iDeconvIRsLength); //The class constructor wanna know, in order: # of rows, # of columns, Audacity audio data Length, IRs length.
	afmvConvolver->SetMatrixAutorange(false); //I disabled autorange because it works on each output channel separately.
	afmvConvolver->SetRemoveDC(true);         //Remove DC is good instead.
	afmvConvolver->SetPreserveLength(true);   //Length preservation (truncation) enabled.
	
	//Copying data pointers inside the convolution class
	for(i = 0; i < sfinfo.channels; i++)  //for each row of the IRs matrix (REMEMBER that sfinfo.channels and iVirtualMikes are the same thing...)
	{
#ifdef __HARDDEBUG__
		printf("MicArrayAnalyzer::Calculate(): Copying audio track [%d] pointer.\n",i);
		fflush(stdout);
#endif
		afmvConvolver->SetInputVectorItem(ActualFrameAudioData[i],i); //inside this "for" loop I load Audacity tracks too instead of using another separate "for"
		for(j = 0; j < iCapsules; j++)
		{
#ifdef __HARDDEBUG__
            printf("MicArrayAnalyzer::Calculate(): Copying IR (%d,%d) pointer.\n",i,j);
            fflush(stdout);
#endif
			afmvConvolver->SetFilterMatrixItem(pppfDeconvIRsData[i][j],i,j);
		}
	}
//	mAAcritSec->Leave();
	/* Convolution calculation!
	 The convolution is computed in this fashion:
	 
	 |ir(1,1) ir(1,2) .... ir(1,j)|   |x1|
	 |ir(2,1) ir(2,2) .... ir(2,j)|   |x2|
	 |ir(3,1) ir(3,2) .... ir(3,j)|   |x3| 
	 | .....   .....  ....  ..... | * |..|  = |y1 y2 y3 ... yi|
	 | .....   .....  ....  ..... |   |..|
	 |ir(i,1)  .....  .... ir(i,j)|   |xj|
	 
	 where i = (# of rows) = (# of virtual microphones) and j = (# of audacity project tracks) = (# of array capsules).
	 "Obviously" yk = ir(k,1) * x1 + ir(k,2) * x2 + ... + ir(k,j) * xj , where * stands for convolution, not a simple product :)
	 AFMatrixvolver class does the summation too!
	 */
	//	mAAcritSec->Enter();
	//	 #ifdef __AUDEBUG__
	//	 printf("MicArrayAnalyzer::Calculate(): Convolving...");
	//	 fflush(stdout);
	//	 #endif
	//	 afmvConvolver->Process();
	//	 #ifdef __AUDEBUG__
	//	 printf("DONE\n");
	//	 fflush(stdout);
	//	 #endif
	

	//Retrieving Convolution Output Data
	//	InitProgressMeter(_("Retrieving convolution results from convolver object..."));
	CalculateFSScalingFactor();   //Finding the project track with the max absolute level, and computing the ratio between this level and the local peak level of the same track. This will be used as a trick to associate dFSLevel with the absolute max without the need of convolving the entire recording!
	apOutputData = new AudioPool(iVirtualMikes,dFSLevel - double(fdBScalingFactor),dProjectRate); //AudioPool alloc
	for(int i=0; i<iVirtualMikes; i++)
	{
#ifdef __AUDEBUG__
		printf("MicArrayAnalyzer::Calculate(): Retrieving convolution result [%d] from convolver object.\n",i);
		fflush(stdout);
#endif
		//		UpdateProgressMeter(i,iVirtualMikes);
		//Arguments: 1st -> track #, 2nd -> data pointer, 3rd -> data vector length, 4th -> true if data output array need to be alloc before copying.
		//apOutputData->SetTrack(i,(float*)afmvConvolver->GetOutputVectorItem(i),afmvConvolver->GetOutputVectorItemLength(),true);
		apOutputData->SetTrack(i,ActualFrameAudioData[i], GetFrameLengthSmpl(), true); //***DEBUG*** BYPASSING CONVOLUTION!
	}
	//	DestroyProgressMeter();
	

	//NORMALIZING Output Tracks! -->> new peak level will be 1.
	//	InitProgressMeter(_("Autoranging output signals to match FS..."));
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer::Calculate(): AutoRanging output signals.\n");
	fflush(stdout);
#endif
	double dMax;
	dMax = apOutputData->FindOverallMax();
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer::Calculate(): Found Max Level = %f [pressure]\n",dMax);
	fflush(stdout);
#endif
	//	UpdateProgressMeter(1,2);
	apOutputData->ApplyOverallGain(1/dMax);
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer::Calculate(): applied overall gain = %f ; new overall max = %f [pressure]\n",1/dMax,apOutputData->FindOverallMax());
	fflush(stdout);      
#endif
	//	UpdateProgressMeter(2,2);
	//	DestroyProgressMeter();
	
	//Calculating Results
	printf("thread #%d filling audiopool result matrix \n",frame);
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
		wxCriticalSectionLocker locker(*mAAcritSec);
		outputFrames->AddFrame(videoframe);
		bResultsAvail = true; 
		mAAcritSec->Leave();
	}
	else { 
		bResultsAvail = false; 
		mAAcritSec->Leave();
	}
	
//	PrintResult(frame);
	
	//THE END!
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
		int ActualFrameLengthSmpl = GetFrameLengthSmpl();
		ActualFrameAudioData[i] = new float [ActualFrameLengthSmpl];
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
}

bool MicArrayAnalyzer::SetAudioTrackLength(int len)
{
	if(!iAudioTrackLength) iAudioTrackLength = len;
	return (iAudioTrackLength != len) ? false: true; //Return false if there's a length mismatch!
}


bool MicArrayAnalyzer::LoadDeconvIRs()
{
	// Deconv IRs pool allocation. This is how the pool is arranged:
	// - the main array holds ROWS of the matrix, so with pppfDeconvIRsData[i] we gain access to the row number "i".
	// - each row is an array of COLUMNS, so with pppfDeconvIRsData[i][j] we gain access to the cell @ row "i", column "j".
	// - each cell is an IR, so each cell is an array of float. pppfDeconvIRsData[i][j] is a pointer to the first sample of this IR, while pppfDeconvIRsData[i][j][k] is the "k" sample value!
	
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer::LoadDeconvIRs(): IRs pool allocation...\n");
	fflush(stdout);
#endif
	if (bDeconvIRsDataAlloc) delete [] pppfDeconvIRsData;
	pppfDeconvIRsData = new float** [sfinfo.channels]; // # of rows = # of wav file channels.
	for(int i = 0; i < sfinfo.channels ; i++) pppfDeconvIRsData[i] = new float* [iCapsules]; // # of columns = # of array capsules.
	bDeconvIRsDataAlloc = true;
	
	//Cleaning up
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer::LoadDeconvIRs(): Cleaning up!\n");
	fflush(stdout);
#endif
	for (int i = 0; i < sfinfo.channels; i++)
	{ 
		for (int k = 0; i < iCapsules; i++)
		{
			pppfDeconvIRsData[i][k] = 0;   //cleaning each pointer.
		}
	}
	
	//Reading IRs from file and storing inside the structure!
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer::LoadDeconvIRs(): Reading WAV file data.\n");
	fflush(stdout);
#endif
	const int CHANNELS = sfinfo.channels;
	const int BLOCK_SIZE = iDeconvIRsLength;
	float *buf;
	buf = new float [CHANNELS * BLOCK_SIZE];
	int readcount, j = 0;
	
	//	InitProgressMeter(_("Loading deconv IRs from file..."));
	
	//NOTE that libsndfile loads data from file starting with the first sample of first channel, then going to the first sample of the second CHANNEL,
	//and so on, so at the first time for example in buf[2] we have the first sample of the third row, first column IR !!!!
	while ((readcount = sf_readf_float(infile, buf, BLOCK_SIZE)) > 0)
	{
		for (int i = 0; i < CHANNELS; i++)
		{
			//			UpdateProgressMeter(j*CHANNELS + i,(sfinfo.channels)*(iCapsules));
			pppfDeconvIRsData[i][j] = new float [iDeconvIRsLength];                                //Initing [i][j] deconv IRs memory.
#ifdef __AUDEBUG__
            printf("MicArrayAnalyzer::LoadDeconvIRs(): Writing to cell (%d;%d), readcount=%d\n",i,j,readcount);
            fflush(stdout);
#endif
			for (int k = 0; k < readcount; k++) pppfDeconvIRsData[i][j][k] = buf[k*CHANNELS + i];  //Reading a whole IR!
		}
		j++;
	}
	
	//	DestroyProgressMeter();
	
	sf_close(infile); //Freeing up memory!
	bSndFileAlloc = false;
	
#ifdef __AUDEBUG__
	printf("MicArrayAnalyzer::LoadDeconvIRs(): All done!\n");
	fflush(stdout);
#endif
	//All done!
	return true;
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
	
	if ( !wxbBgndImage.LoadFile(wxfnBgndImageFile->GetFullPath(), wxBITMAP_TYPE_JPEG) ) 
		return false;
	
	return true; // [esseci] else qui non ha senso...
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

bool MicArrayAnalyzer::GetMirroredMike(double original_x, double original_y, double* mirror_xy, int mirror_num)
{
	int quadrantA = 0, quadrantB = 0, quadrantC = 0, quadrantD = 0;
	
	if (original_x <= (X_RES/2))
	{
		if (original_y <= (Y_RES/2))   //Quadrant C
			quadrantC = 1;
		if (original_y >= (Y_RES/2))   //Quadrant A
			quadrantA = 1;
	}
	if (original_x >= (X_RES/2))
	{
		if (original_y <= (Y_RES/2))   //Quadrant D
			quadrantD = 1;
		if (original_y >= (Y_RES/2))   //Quadrant B
			quadrantB = 1;
	}
	
	switch (mirror_num)
	{
			//This equations could be further simplified, I know.... :-)
		case 0:
			mirror_xy[0] = quadrantA*(X_RES+original_x) + quadrantB*(original_x-X_RES) + quadrantC*(X_RES+original_x) + quadrantD*(original_x-X_RES);
			mirror_xy[1] = quadrantA*(original_y) + quadrantB*(original_y) + quadrantC*(original_y) + quadrantD*(original_y);
			break;
		case 1:
			mirror_xy[0] = quadrantA*(X_RES-original_x) + quadrantB*(2*X_RES-original_x) + quadrantC*(X_RES-original_x) + quadrantD*(2*X_RES-original_x);
			mirror_xy[1] = quadrantA*(2*Y_RES-original_y) + quadrantB*(2*Y_RES-original_y) + quadrantC*(-original_y) + quadrantD*(-original_y);
			break;
		case 2:
			mirror_xy[0] = quadrantA*(-original_x) + quadrantB*(X_RES-original_x) + quadrantC*(-original_x) + quadrantD*(X_RES-original_x);
			mirror_xy[1] = quadrantA*(2*Y_RES-original_y) + quadrantB*(2*Y_RES-original_y) + quadrantC*(-original_y) + quadrantD*(-original_y);
			break;
		default:
			return false;
	}
	
	return true;
}

double MicArrayAnalyzer::GetMaxSPL(bool autoscale_each_band, int band)
{
	double value = dMinSPLThreshold;
	
	if (bResultsAvail)
	{
		if (autoscale_each_band) { value = apOutputData->GetMaxResultInTheBand(band); }
		else { value = apOutputData->GetMaxResultInTheMatrix(); }
		
		if (value < dMinSPLThreshold) { value = dMinSPLThreshold; }
	}
	
	return value;
}

double MicArrayAnalyzer::GetMinSPL(bool autoscale_each_band, int band)
{
	double value = dMinSPLThreshold;
	
	if (bResultsAvail)
	{
		if (autoscale_each_band) { value = apOutputData->GetMinResultInTheBand(band); }
		else { value = apOutputData->GetMinResultInTheMatrix(); }
		
		if (value < dMinSPLThreshold) { value = dMinSPLThreshold; }
	}
	
	return value;
}

void MicArrayAnalyzer::PrintResults() {
	for (int f=1; f<=GetNumOfFrames(); f++) {
		
		printf("\n\n*** RESULTS MATRIX no [%d] *** (PRESSURE levels, not dB)\nCH#\tLIN\tA\t31.5\t63\t125\t250\t500\t1k\t2k\t4k\t8k\t16k\n", f);
		
		for (int i = 0; i < apOutputData->GetChannelsNumber(); i++) //For each audio track
		{
			printf("%d\t",i);
			for (int j = 0; j < (2+10); j++) //For each band
			{
				double ** matrix=outputFrames->GetFrameMatrix(f);
				printf("%1.4f\t",undB20(float(matrix[i][j]))*p0);
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


wxString MicArrayAnalyzer::GetCurTime() {
	wxString str; 
	int ms = iAudioTrackLength / dProjectRate * 1000; //millisec
	double progressRatio = (double)(curFrame-1) / (outputFrames->GetNumOfFrames() - 1) ;
	ms = (double)ms * progressRatio;
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
	
	//Results Matrix Calculation
	//	InitProgressMeter(_("Calculating levels for each audio band..."));
#ifdef __AUDEBUG__
	printf("AudioPool: Filling results matrix...");
	fflush(stdout);
#endif
	printf("*** RESULTS MATRIX *** (PRESSURE levels, not dB)\nCH#\tLIN\tA\t31.5\t63\t125\t250\t500\t1k\t2k\t4k\t8k\t16k\n");
	for (int i = 0; i < m_nChannels; i++) //For each audio track
	{
		printf("%d\t",i);
		for (int j = 0; j < (2+10); j++) //For each band
		{
			//			UpdateProgressMeter(i*(2+10) + j,(m_nChannels)*(2+10));
			
			if (j == 0)
            {  //Linear Filter
				ResetFilteredTrack(i);
				LFilter(i); //Linear filtering track #i
				ppdResultsMatrix[i][j] = LeqFilteredTrack(i); //Storing squared mean level inside results matrix.
            }
			else if (j == 1)
            {  //A-weighted
				ResetFilteredTrack(i);
				AFilter(i); //A-weighting track #i
				ppdResultsMatrix[i][j] = LeqFilteredTrack(i); //Storing mean squared level inside results matrix.
            }
			else
            {  //Octave bands
				ResetFilteredTrack(i);
				OctaveFilter(i,dFcOctaveBandFilters[j-2]); //Octave band filtering track #i
				ppdResultsMatrix[i][j] = LeqFilteredTrack(i); //Storing mean squared level inside results matrix.
            }
			printf("%1.4f\t",undB20(float(ppdResultsMatrix[i][j]))*p0);
		}
		printf("\n");
		fflush(stdout);
	}
	
#ifdef __AUDEBUG__
//	printf("AudioPool: Filling results matrix...DONE\n");
//	fflush(stdout);
#endif
	//	DestroyProgressMeter();
	return true;
}

double AudioPool::GetMaxResultInTheMatrix()
{
#ifdef __AUDEBUG__
	printf("AudioPool::GetMAXResultInTheMatrix\n");
	fflush(stdout);
#endif
	if (bResultsMatrixAlloc)
	{
		double max;
		max = GetMaxResultInTheBand(0);
		for (int i=1;i<12;i++)
		{
			max = (GetMaxResultInTheBand(i) > max) ? GetMaxResultInTheBand(i) : max;
		}
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
#ifdef __AUDEBUG__
		printf("AudioPool::GetMAXResultInTheBand: band [%d] = %f\n",col,max);
		fflush(stdout);
#endif
		return max;
	}
	else { return 0; }
}

double AudioPool::GetMinResultInTheMatrix()
{
#ifdef __AUDEBUG__
	printf("AudioPool::GetMINResultInTheMatrix\n");
	fflush(stdout);
#endif
	if (bResultsMatrixAlloc)
	{
		double min;
		min = GetMinResultInTheBand(0);
		for (int i=1;i<12;i++)
		{
			min = (GetMinResultInTheBand(i) < min) ? GetMinResultInTheBand(i) : min;
		}
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
#ifdef __AUDEBUG__
		printf("AudioPool::GetMINResultInTheBand: band [%d] = %f\n",col,min);
		fflush(stdout);
#endif
		return min;
	}
	else { return 0; }
}

double AudioPool::LeqFilteredTrack(int ch)
{
	double acc = 0.0;
	double dData;
	
	//   #ifdef __AUDEBUG__
	//      printf("AudioPool::LeqFilteredTrack on channel [%d]\n",ch);
	//      fflush(stdout);
	//   #endif
	
	for(int i = 0; i < GetTrackLength(); i++) 
	{ 
		dData = double(GetFilteredTrackSquaredSample(ch,i));  //Explicit conversion to double.
		acc = acc + dData;                            //Accumulating.
		//      #ifdef __AUDEBUG__
		//         printf("LEQ: (filteredsample[%d]/p0)^2 = %f ; new acc = %f\n",i,dData,acc);
		//         fflush(stdout);
		//      #endif
	}
	
	//   #ifdef __AUDEBUG__
	//      printf("LEQ ENDING RESULT: acc/length = %f ; Leq_dB = %f\n",acc/GetTrackLength(),dB(acc/GetTrackLength()));
	//      fflush(stdout);
	//   #endif
	return (dB(acc/GetTrackLength()) + GetFullScale()); //Scaling [-inf;0] result accordingly with FS [dB] level.
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
	return true;
}

void AudioPool::InitProgressMeter(const wxString& operation)
{
	mProgress = new ProgressDialog(_("Mic Array Analyzer"),operation);
}

bool AudioPool::UpdateProgressMeter(int step,int total)
{
	return bool(mProgress->Update(step, total) == eProgressSuccess); // [esseci]
}

void AudioPool::DestroyProgressMeter()
{
	if(mProgress) delete mProgress;
	mProgress = 0;
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

