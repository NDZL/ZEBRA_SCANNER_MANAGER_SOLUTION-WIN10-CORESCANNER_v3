/*******************************************************************************
* FILENAME: RouterEventSink.cpp
*
* © 2005-2007 Symbol Technologies, Inc., A Motorola Company. All Rights Reserved.
*
* DESCRIPTION: Implementation of Event sink class for receiving events from 
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

#include "stdafx.h"
#include "SendKeys.h"
#include <time.h>

#define PREFIXKEYNAME		"Prefix"
#define SUFFIXKEYNAME		"Suffix"
#define CONFIGSNAME			"Configs"
#define INITNAME			"Init"
#define REGISTRYKEYNAME		"RegistryPath"
#define LOGKEYNAME			"LogEnabled"
#define REPLACEMENTKEYNAME	"Replacement"



//event sink
#include "RouterEventSink.h"

#include "FastIni32.h"

#include "CmdRouter_i.c"
#include "RouterDefn.h"

////new using directive
//#using <mscorlib.dll>
// 
////another using namespace directive.
//using namespace System;





#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CRouterEventSink, CCmdTarget)

CRouterEventSink::~CRouterEventSink()
{
}


void CRouterEventSink::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

void CRouterEventSink::onScanCmdResponseEvent(short status, BSTR scanCmdResponse)
{
	m_status = status;
	m_responseData = scanCmdResponse;
}

void CRouterEventSink::onScanRMDEvent(short eventType, BSTR eventData)
{
	m_eventType = eventType;
	m_eventData = eventData;
}


void CRouterEventSink::SetWnd(HWND mainWnd)
{
	m_mainWnd = mainWnd;
}



int CRouterEventSink::GetScanData(short *reserved, BSTR *data)
{
	*reserved = m_reserved;
	*data = m_scanData;
	return 0;
}


int CRouterEventSink::GetResponseData(short *status, BSTR *data)
{
	*status = m_status;
	*data = m_responseData;
	return 0;
}


int CRouterEventSink::GetRmdData(short *type, BSTR *data)
{
	*type = m_eventType;
	*data = m_eventData;
	return 0;
}



BEGIN_MESSAGE_MAP(CRouterEventSink, CCmdTarget)
	//{{AFX_MSG_MAP(RouterEventSink)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CRouterEventSink, CCmdTarget)
	//{{AFX_DISPATCH_MAP(RouterEventSink)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	DISP_FUNCTION_ID(CRouterEventSink,"ScanDataEvent",SCAN_DATA_EVENT,onScanDataEvent,VT_EMPTY,VTS_I2 VTS_BSTR)
	DISP_FUNCTION_ID(CRouterEventSink,"ScanCmdResponseEvent",SCAN_CMDRESPONSE_EVENT,onScanCmdResponseEvent,VT_EMPTY,VTS_I2 VTS_BSTR)
	DISP_FUNCTION_ID(CRouterEventSink,"ScanRMDEvent",SCAN_RMD_EVENT,onScanRMDEvent,VT_EMPTY,VTS_I2 VTS_BSTR)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IRouterEventSink to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {3DEC8A55-8839-4052-80B4-A8969C22ECC3}
static const IID IID_IRouterEventSink =
{ 0x3dec8a55, 0x8839, 0x4052, { 0x80, 0xb4, 0xa8, 0x96, 0x9c, 0x22, 0xec, 0xc3 } };

BEGIN_INTERFACE_MAP(CRouterEventSink, CCmdTarget)
	INTERFACE_PART(CRouterEventSink, DIID__ISblRouterEvents, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////




CRouterEventSink::CRouterEventSink()
{
	EnableAutomation();
}

void CRouterEventSink::LoadConfiguration()
{
	char  olddir[MAX_PATH];
	LPWSTR dir = new WCHAR[MAX_PATH];
	HKEY hKey = 0;
    char buf[255] = {0};
    DWORD dwType = 0;
    DWORD dwBufSize = sizeof(buf);
	CString configPath;

    if( RegOpenKey(HKEY_LOCAL_MACHINE,L"SOFTWARE\\MotorolaScannerManager",&hKey) == ERROR_SUCCESS)
    {
        dwType = REG_SZ;
        if( RegQueryValueEx(hKey,L"ConfigurationFilePath",0, &dwType, (BYTE*)buf, &dwBufSize) == ERROR_SUCCESS)
        {/*
            CString tempConfigPath(buf);
			configPath = tempConfigPath;*/

			int ndx=0;
			char dirpath[1024];
			int szRgVal=sizeof(buf);
			for(int i=0;i<szRgVal;i++)
			{
				dirpath[ndx++]=buf[i];
				i++;
			}
			int maxStr=strlen(dirpath);
			dirpath[maxStr+1]=(char)'\0';
			configPath = dirpath;
        }
        RegCloseKey(hKey);
    }
	if(configPath.GetLength() >0)
	{
		wcscpy( dir, CT2CW( (LPCTSTR) configPath ));
	}
	else
	{
		if (GetCurrentDirectory(MAX_PATH, dir) == 0)
		{
			exit(1);
		}
	}

	configurationAndLogPath = dir;
	wcsncat(dir,L"\\MotorolaScannerManager.INI",28);

	char    *Ptr;
	wchar_t	wStr[128];
	CString directory(dir);
	LibList = new xcIniFile (dir);
	logEnable = LibList->GetProfileLong(INITNAME,LOGKEYNAME,1);
	LogMessage("Init of Motorola Scanner Manager");
	if (NULL != (Ptr = LibList->GetProfileStr(INITNAME,REGISTRYKEYNAME,NULL)))
	{
		if (strlen(Ptr))
		{
			memset(wStr,0,sizeof(wStr));
			mbstowcs(wStr,Ptr,strlen(Ptr)+1);
			CString registryPath(wStr);
			registryLogPath = registryPath;
			LogMessage("Found Registry Path: ",registryLogPath);
		}
	}
	else
		LogMessage("LoadConfigurationNoArgs: Failed to find the RegistryKeyName", directory);
}

void CRouterEventSink::LoadConfiguration(CString configPath)
{
	char  olddir[MAX_PATH];
	LPWSTR dir = new WCHAR[MAX_PATH];
	wcscpy( dir, CT2CW( (LPCTSTR) configPath ));
	configurationAndLogPath = configPath;
	wcsncat(dir,L"\\MotorolaScannerManager.INI",28);

	char    *Ptr;
	wchar_t	wStr[128];
	LibList = new xcIniFile (dir);
	CString directory(dir);
	logEnable = LibList->GetProfileLong(INITNAME,LOGKEYNAME,1);
	LogMessage("Init of Motorola Scanner Manager");
	if (NULL != (Ptr = LibList->GetProfileStr(INITNAME,REGISTRYKEYNAME,NULL)))
	{
		if (strlen(Ptr))
		{
			memset(wStr,0,sizeof(wStr));
			mbstowcs(wStr,Ptr,strlen(Ptr)+1);
			CString registryPath(wStr);
			registryLogPath = registryPath;
			LogMessage("Found Registry Path: ",registryLogPath);
		}
	}
	else
		LogMessage("LoadConfigurationWithArgs: Failed to find the RegistryKeyName",directory);

	//IncreaseRegistryCounter();
}

void CRouterEventSink::WriteBarcodeToRegistry(CString barcodeReading)
{
	HKEY hKey;
	DWORD result;
	DWORD  dwDisposition;
	CString RegistryLogPath("SOFTWARE\\MotorolaScannerManager\\ScanData");
	
	result= RegOpenKeyEx(HKEY_LOCAL_MACHINE, RegistryLogPath,0,KEY_ALL_ACCESS,&hKey); 
	
	if(result!=ERROR_SUCCESS)
	{
		result=RegCreateKeyEx(HKEY_LOCAL_MACHINE, RegistryLogPath, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition);			
	}

	if ( ERROR_SUCCESS == result)
	{
		DWORD dwType=REG_DWORD;
		DWORD dwTimestamp = time(NULL);
		DWORD dwSize=sizeof(DWORD);
		RegSetValueEx(hKey, TEXT("ScanTime"), NULL, REG_DWORD,(BYTE *) &dwTimestamp, sizeof( dwTimestamp ) );
		
		LPCTSTR lpszValue = barcodeReading;
		RegSetValueEx(hKey, TEXT("ScanReading"), 0, REG_SZ, (LPBYTE)lpszValue, (lstrlen(lpszValue))*sizeof TCHAR);

		RegCloseKey(hKey);
	}


}



void CRouterEventSink::IncreaseRegistryCounter(CString RegistryLogPath)
{
	HKEY hKey;
	DWORD result;
	DWORD  dwDisposition;

	
	result= RegOpenKeyEx(HKEY_LOCAL_MACHINE,RegistryLogPath,0,KEY_ALL_ACCESS,&hKey); 
	
	if(result!=ERROR_SUCCESS)
	{
		result=RegCreateKeyEx(HKEY_LOCAL_MACHINE,RegistryLogPath, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition);
		
		SYSTEMTIME st;
        GetLocalTime(&st);
		CString currentTime;
		currentTime.Format(L"%d:%d:%d %d/%d/%d" ,st.wHour,st.wMinute,st.wSecond,st.wDay,st.wMonth,st.wYear);
        
		LPCTSTR lpszValue = currentTime;
		RegSetValueEx (hKey, TEXT("FirstSeen"), 0, REG_SZ, (LPBYTE)lpszValue, (lstrlen(lpszValue))*sizeof TCHAR);
		LogMessage("Set FirstSeen RegValue: ", currentTime);
	}

	if ( ERROR_SUCCESS == result)
	{
		int counter = 0;

		DWORD dwType=REG_DWORD;
		DWORD dwCounter =0;
		DWORD dwSize=sizeof(DWORD);

		result = RegQueryValueEx(hKey, TEXT("ScanCount"), NULL, &dwType,(LPBYTE)&dwCounter, &dwSize);

		if(result == ERROR_SUCCESS)
		{
			LogMessage("Opened ScanCount RegValue: ",RegistryLogPath);
		}
		else
		{
			LogMessage("Cannot opened ScanCount RegValue: ",RegistryLogPath);
		}

		counter = dwCounter +1;

		result =  RegSetValueEx( hKey, TEXT("ScanCount"), NULL, REG_DWORD,(BYTE *) &counter, sizeof( counter ) );
		
		SYSTEMTIME st;
        GetLocalTime(&st);
		CString currentTime;
		currentTime.Format(L"%d:%d:%d %d/%d/%d" ,st.wHour,st.wMinute,st.wSecond,st.wDay,st.wMonth,st.wYear);
        
		LPCTSTR lpszValue = currentTime;
		RegSetValueEx (hKey, TEXT("LastScan"), 0, REG_SZ, (LPBYTE)lpszValue, (lstrlen(lpszValue))*sizeof TCHAR);
		LogMessage("Set LastScan RegValue: ", currentTime);

		RegCloseKey(hKey);
	}
	else
		LogMessage("Failed to open the RegistryLogPath: ",registryLogPath);

}


void CRouterEventSink::KbEmulation(CString result, int Delay)
{
	char    *Ptr;
	wchar_t	wStr[128];
	wchar_t	inputHex[128];

	LogMessage("Initial DataLabel readed: ",result);

	if (NULL != (Ptr = LibList->GetProfileStr(CONFIGSNAME,REPLACEMENTKEYNAME,NULL)))
	{
		do
		{
			memset(wStr,0,sizeof(wStr));
			mbstowcs(wStr,Ptr,strlen(Ptr)+1);
			Ptr = LibList->GetNextString(REPLACEMENTKEYNAME,NULL);
			CString repls(wStr);

			int position = repls.Find(_T("-:-"));
			int rlenght = repls.GetLength()-position-3;
			CString left = repls.Left(position);
			CString right = repls.Right(rlenght);

			LogMessage("Replacement Found: ",repls);

			result.Replace(left,right);
		} while (Ptr);

	}
	if (NULL != (Ptr = LibList->GetProfileStr(CONFIGSNAME,PREFIXKEYNAME,NULL)))
	{
		if (strlen(Ptr))
		{
			memset(wStr,0,sizeof(wStr));
			mbstowcs(wStr,Ptr,strlen(Ptr)+1);
			CString prefix(wStr);
			result = prefix + result;
			LogMessage("Prefix Found: ",prefix);
		}
	}
	if (NULL != (Ptr = LibList->GetProfileStr(CONFIGSNAME,SUFFIXKEYNAME,NULL)))
	{
		if (strlen(Ptr))
		{
			memset(wStr,0,sizeof(wStr));
			mbstowcs(wStr,Ptr,strlen(Ptr)+1);
			CString suffix(wStr);
			result = result+suffix;
			LogMessage("Suffix Found: ",suffix);
		}
	}

	LogMessage("Final DataLabel computed: ",result);

	////ORIGINAL CODE NOT WORKING ON WIN7 => CAUSA CRASH/TERMINTATION DELL'APPLICAZIONE CORRENTE SE L'EXE è INVOCATO DA WIN SERVICE
	CSendKeys sk;
	sk.SendKeys(result);
	
	////TEST SENDKEY MANAGED WIN7 DOTNET 2.0 => NON SI RIESCE A COMPILARE: 
	//// SAREBBE NECESSARIO USARE /CLR CON THREAD MODEL "MD", MA A QUEL PUNTO NON POSSO AVERE MFC STATICALLY LINKED
	//// mfc statically linked è un requisito essenziale
	////SendKeys.Send(result);

	//TEST: STAMPO SU CONSOLE LA LETTURA DEL BARCODE E CHIAMO LA SENDKEY DA C#
	//printf("%s", result);

	//TEST: PASSO PER IL REGISTRY
	//WriteBarcodeToRegistry(result);
}

void CRouterEventSink::onScanDataEvent(short reserved, BSTR scanData)
{
	LogMessage("--- Inizio CRouterEventSink::onScanDataEvent");
	m_reserved = reserved;
	m_scanData = scanData;
	CString scanRes = scanData;

	int startIndex = scanRes.Find((CString)"</datalabel>");
	CString resRight = scanRes.Left(startIndex);
	int endIndex = resRight.GetLength() - resRight.Find((CString)"<datalabel>") -11;
	CString result = resRight.Right(endIndex);

	startIndex = scanRes.Find((CString)"</serial>");
	resRight = scanRes.Left(startIndex);
	endIndex = resRight.GetLength() - resRight.Find((CString)"<serial>") -8;
	CString serial = resRight.Right(endIndex);

	LogMessage("ScandData from Serial: ",serial);
	LogMessage("ScandData collected: ",result);
	
	KbEmulation(result,10);

	CString serialPrefix("S/N:");
	int findResult = serial.Find(serialPrefix);
	if(findResult >= 0)
	{
		serial = serial.Right(serial.GetLength()-4);
	}

	CString splitter("\\");
	IncreaseRegistryCounter(registryLogPath);
	IncreaseRegistryCounter(registryLogPath+splitter+serial);
	LogMessage("--- Fine CRouterEventSink::onScanDataEvent");
}

void CRouterEventSink::LogMessage(char * logEntry1, CString logEntry2)
{
	CString cs;
	cs = logEntry1;
	LogMessage(cs+logEntry2);
}
void CRouterEventSink::LogMessage(char * logEntry)
{
	CString cs;
	cs = logEntry;
	LogMessage(cs);
}
void CRouterEventSink::LogMessage(CString logEntry)
{
	if(logEnable==1)
	{
		SYSTEMTIME st;
        GetLocalTime(&st);
		CString currentTime;
		currentTime.Format(L"%d:%d:%d %d/%d/%d" ,st.wHour,st.wMinute,st.wSecond,st.wDay,st.wMonth,st.wYear);
        
		CString separator("\t - \t");
		CString enter("\n");

		logEntry = currentTime + separator + logEntry +enter;

		CString logFileName("\\Log.txt");
		CString fullPath = configurationAndLogPath+logFileName;
		LPCTSTR logFileFullPath=fullPath;
		
		CStdioFile file;

		if(!file.Open(logFileFullPath, CFile::modeRead))
		{
			file.Open(logFileFullPath, CFile::modeCreate);
			file.Close();
		}
		else
			file.Close();

		/*
		DWORD fileAtt = GetFileAttributesA((LPCSTR)logFileFullPath);
		if(fileAtt == INVALID_FILE_ATTRIBUTES)
		{
			file.Open(logFileFullPath, CFile::modeCreate);
			file.Close();
		}*/


		if(file.Open(logFileFullPath, CFile::modeWrite))
		{
			file.SeekToEnd();
			file.WriteString(logEntry);
		}
		file.Close();
	}
}