// MotScanManagerDlg.h : header file
//

#pragma once

#include "CmdRouter_i.c"
#include "CmdRouter.h"
#include "RouterEventSink.h"

// CMotScanManagerDlg dialog
class CMotScanManagerDlg : public CDialog
{
// Construction
public:
	CMotScanManagerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MOTSCANMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	void Init();
	ISblRouter * m_pISblRouter;//Reference to a command Router
	DWORD m_dwCookie;//cookie storage
	long m_hScanner;//scanner handle
	CString configurationPath;
	CRouterEventSink * m_pSink;//event sink
	bool visible;
public:
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	void SetConfigurationPath(CString configPath);
};
