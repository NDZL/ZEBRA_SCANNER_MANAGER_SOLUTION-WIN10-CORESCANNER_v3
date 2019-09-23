// MotScanManagerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MotScanManager.h"
#include "MotScanManagerDlg.h"
#include <afxctl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMotScanManagerDlg dialog




CMotScanManagerDlg::CMotScanManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMotScanManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	configurationPath = "";
}

void CMotScanManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMotScanManagerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()


// CMotScanManagerDlg message handlers

BOOL CMotScanManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	visible = false;
	Init();
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}



// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMotScanManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMotScanManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMotScanManagerDlg::Init()
{
	CoInitialize(NULL);
	HRESULT hr = CoCreateInstance(CLSID_SblRouter,NULL, CLSCTX_ALL, IID_ISblRouter, (void**)&m_pISblRouter);
	if(hr!=S_OK)
	{
		//creating Router instance failed. take action.
		AfxMessageBox(_T("COM Creation failed"));

		CString logFileName("C:\\\\MotScanManagerNotRecoverableErrorLog.txt");

		//CString logFileName(".\\MotScanManagerNotRecoverableErrorLog.txt");
		LPCTSTR logFileFullPath=logFileName;
		CStdioFile file;
		if(!file.Open(logFileFullPath, CFile::modeRead))
		{
			file.Open(logFileFullPath, CFile::modeCreate);
			file.Close();
		}
		else
			file.Close();

		if(file.Open(logFileFullPath, CFile::modeWrite))
		{
			file.SeekToEnd();
			CString logEntry("COM Creation Failed - check opos installation");
			file.WriteString(logEntry);
		}
		file.Close();
	}
	else
	{
		m_pSink = new CRouterEventSink();

		if(configurationPath.GetLength()==0)
			m_pSink->LoadConfiguration();
		else
			m_pSink->LoadConfiguration(configurationPath);

		m_pSink->SetWnd(m_hWnd);

		//Get a pointer to sinks IUnknown, no AddRef.
		LPUNKNOWN pUnkSink = m_pSink->GetIDispatch(FALSE);
		//Establish a connection between source and sink.
		//m_pUnkSrc is IUnknown of server obtained by CoCreateInstance().
		//m_dwCookie is a cookie identifying the connection, and is needed
		//to terminate the connection.
		BOOL stat = AfxConnectionAdvise(m_pISblRouter,
			DIID__ISblRouterEvents, pUnkSink, FALSE, &m_dwCookie);
		if(!stat)
		{
			//connection advise failed. take action.
			AfxMessageBox(_T("Advise failed"));
			CString logFileName("C:\\\\MotScanManagerNotRecoverableErrorLog.txt");
		LPCTSTR logFileFullPath=logFileName;
		CStdioFile file;
		if(!file.Open(logFileFullPath, CFile::modeRead))
		{
			file.Open(logFileFullPath, CFile::modeCreate);
			file.Close();
		}
		else
			file.Close();

		if(file.Open(logFileFullPath, CFile::modeWrite))
		{
			file.SeekToEnd();
			CString logEntry("Advise failed - check opos installation");
			file.WriteString(logEntry);
		}
		file.Close();
		}
	}

	bool autostart = true;
	if(autostart)
	{
		long status = 0;
		CString conn = _T("ConnUSB");
		BSTR openString = conn.AllocSysString();
		HRESULT res = m_pISblRouter->OpenDevice(1,openString, &m_hScanner, &status);
		if (res != S_OK && res != S_FALSE)
		{
			// server may be down or restarted. Re-init to obtain a valid interface pointer
			Init();
			res = m_pISblRouter->OpenDevice(1,openString, &m_hScanner, &status);
		}

		if (res == S_OK || res == S_FALSE)
		{
			CString	m_editVar;
			char cstatus[8];
			memset(cstatus, 0, 8);
			_itoa((int)status, cstatus, 10);
		}

		long m_lDataEvents = 1;
		long m_lResponseEvents = 0;//2;
		long m_lRMDEvents = 0;//4;
		long m_lEventsInterested = m_lDataEvents|m_lResponseEvents|m_lRMDEvents;
		m_pISblRouter->RegisterForEvents(m_hScanner, m_lEventsInterested, &status);
	}
}


void CMotScanManagerDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{

	if(!visible)
        lpwndpos->flags &= ~SWP_SHOWWINDOW;

	CDialog::OnWindowPosChanging(lpwndpos);

	
}
void CMotScanManagerDlg::SetConfigurationPath(CString configPath)
{
	configurationPath = configPath;
}