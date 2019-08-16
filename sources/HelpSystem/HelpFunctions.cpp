// HelpFunctions.cpp: implementation of the CHelpFunctions class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HtmlHelp.h"

#include "HelpFunctions.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHelpFunctions::CHelpFunctions()
{

}

CHelpFunctions::~CHelpFunctions()
{

}

void CHelpFunctions::DisplayCtrlPopup(CWnd *pWnd, POINT pt, int iCtrlID)
{
	CString s;
	// Load help text from String Table
	if(s.LoadString(iCtrlID))
		{
		HH_POPUP hPop; // HTML Help popup structure
		// Initialize structure to NULLs
		memset(&hPop, 0, sizeof(hPop));
		// Set size of structure
		hPop.cbStruct = sizeof(hPop);
		// Yellow background color
		hPop.clrBackground = RGB(255, 255, 208);
		hPop.clrForeground = -1; // Font color	
		hPop.rcMargins.left = -1;
		hPop.rcMargins.bottom = -1;
		hPop.rcMargins.right = -1;
		hPop.pt = pt;
		hPop.pszText = s; // Message from String Table
		hPop.pszFont = NULL; // Font
		HtmlHelp(pWnd->GetSafeHwnd(), NULL,
		HH_DISPLAY_TEXT_POPUP, (DWORD)&hPop);
		} // End if found a help string for this request
}

void CHelpFunctions::OpenTopic(HWND hwndApp, DWORD topic)
{	
	CWinApp* theApp=AfxGetApp();
	CString helpPath=theApp->m_pszHelpFilePath;
	if (0==topic)
		{
		HtmlHelp(hwndApp,helpPath,HH_DISPLAY_TOPIC,0);
		}
	else
		{
		if(0x20080==topic) // MainFrame
			{
			}
		else if( ((0x18000<=topic)&&(topic<0x20000))
			|| ((0x1E100<=topic)||(topic<0x1E110)) )	// save and open document
			{
			helpPath+=">CommandWindow";
			}
		else if(topic>0x20000)
			{
			helpPath+=">DialogWindow";
			}
		HtmlHelp(hwndApp,helpPath, HH_HELP_CONTEXT, topic);
		}

}
