/*******************************************************************************
* FILENAME: RouterEventSink.h
*
* © 2005-2007 Symbol Technologies, Inc., A Motorola Company. All Rights Reserved.
*
* DESCRIPTION: Decleration of Event sink class for receiving events from 
* CmdRouter
*
* CREATION DATE: December 2005
*
* DERIVED FROM: New File
*
* NOTES: *
* EDIT HISTORY:
* $Log$ *
*
********************************************************************************/

#include "FastIni32.h"


#if !defined(AFX_ROUTEREVENTSINK_H__BE67AC0F_38E4_43F9_B227_EC37B58B7B1E__INCLUDED_)
#define AFX_ROUTEREVENTSINK_H__BE67AC0F_38E4_43F9_B227_EC37B58B7B1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////////////
// RouterEventSink command target

class CRouterEventSink : public CCmdTarget
{
	DECLARE_DYNCREATE(CRouterEventSink)

	CRouterEventSink();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	BSTR m_eventData;
	short m_eventType;
	BSTR m_scanData;
	short m_reserved;
	BSTR m_responseData;
	short m_status;
    xcIniFile   *LibList;

	int autoEnter;
	CString registryLogPath;
	CString configurationAndLogPath;
	int logEnable;
	int GetRmdData(short * type, BSTR * data);
	int GetResponseData(short * status, BSTR * data);
	int GetScanData(short * reserved, BSTR * data);
	void SetWnd(HWND mainWnd);
	void SetAutoEnter(int enter);
	void IncreaseRegistryCounter(CString RegistryLogPath);
	void WriteBarcodeToRegistry(CString);
	HWND m_mainWnd;
	void onScanDataEvent(short reserved, BSTR scanData);
	void onScanCmdResponseEvent(short status, BSTR scanCmdResponse);
	void onScanRMDEvent(short eventType, BSTR eventData);
	void KbEmulation(CString result, int Delay);
	void KbEmulation(CString result, CString codeType, int Delay);
	void LoadConfiguration();
	void LoadConfiguration(CString configPath);
	void LogMessage(CString logEntry);
	void LogMessage(char* logEntry);
	void LogMessage(char* logEntry1, CString logEntry2);

	virtual ~CRouterEventSink();

   // Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RouterEventSink)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RouterEventSink)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(RouterEventSink)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROUTEREVENTSINK_H__BE67AC0F_38E4_43F9_B227_EC37B58B7B1E__INCLUDED_)
