// ChecksumGen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ChecksumGen.h"
#include "../LicenceManaging/LicenceManagingResources.h"
#include "../LicenceManaging/Coder.h"

#include <io.h>

#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

void displayUsage()
{
	cout << "Error : a filename must be given as an argument" << endl;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		if(argc<2)
		{
			displayUsage();
			exit(-1);
		}
		try
		{
			// a little bit check
			CString strFilename=CString(argv[1]);
			if(0!=_access(strFilename,00))
			{
				displayUsage();
				exit(-1);
			}

			CString strChecksum=CCoder::GetInstance()->GetCheckSumValue(strFilename);
			CString strDataScrambler=CCoder::GetInstance()->GetDataScramblingValue(strFilename);
			CString strChkFile=strFilename;
			int nPointPos=strChkFile.ReverseFind('.');
			if(nPointPos>0)
			{
				strChkFile=strChkFile.Left(nPointPos);
			}
			strChkFile+=CString(".")+CString(CHECKSUM_FILENAME_EXT);

			try
			{
				ofstream chkFile(strChkFile);
				chkFile << (LPCSTR)strChecksum;
				chkFile << "\n";
				chkFile << (LPCSTR)strDataScrambler;
				cout << "Checksum written in file " << (LPCSTR)strChkFile << endl;
			}
			catch(...)
			{
				cout << "Error while trying to create check file!" << endl;
				exit(-1);
			}
		}
		catch(...)
		{
			cout << "Unknown error while creating check..." << endl;
			exit(-1);
		}
		nRetCode=0;
	}

	return nRetCode;
}


