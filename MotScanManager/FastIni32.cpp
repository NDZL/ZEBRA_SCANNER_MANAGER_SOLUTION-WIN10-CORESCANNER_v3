/*

    This is a reduced version of the INI file interpreter.
    Instead of accesing the file in the GetProfile??? command it reads all the file in the
    constructor in order to speed up the config access. This will limit the length
    of the ini files to the maximum ram avaiable. Any how the king of applications
    this class is defined for uses small INI files less than 10 Kb. Also take into account
    that I am using heap space, so once the object is deleted, the memory is released

    It allows the reading of the profiles with duplicated keywords per section.
    
*/

#include "stdafx.h"
#include <windows.h>
#include "FastIni32.h"

xcIniFile::~xcIniFile()
{
	if (FileContentModified) CommitChanges();
    if (Line) delete Line;
    if (FileContents) delete FileContents;
}



xcIniFile::xcIniFile(wchar_t *IniFN)
{
	HANDLE  hIniFile;
    bool    AllOK;
	DWORD	FS;

	FileContentModified = false;
    IniFileName = IniFN;

    AllOK = (INVALID_HANDLE_VALUE !=( hIniFile = CreateFile(IniFN,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,0)));
        
    if(AllOK)
    {
		FS = GetFileSize(hIniFile,NULL);
		if (0xFFFFFFFF == FS)
			FileLen = 0;
		else
			FileLen = FS;

        if (NULL == (FileContents = (char *) new char[FileLen+1]))
        {
			FileLen = 0;
        }
        
        AllOK = (TRUE == ReadFile( hIniFile,FileContents,FileLen,&FileLen,NULL));
        
        if (AllOK)
        {
            FileContents[FileLen] = '\0'; // lets convert it into an string
            if (NULL == (Line    = (char *) new char[MAX_LINE_SIZE]))
            {
				FileLen = 0;
            }
        }
        else
        {
            delete FileContents;
        }
        
        CloseHandle( hIniFile );
    }
    
    if(!AllOK)
    {
        FileLen = 0;
        FileContents = Line = NULL;
    }
}



// Next three member modified to access the file in ram instead of directly
// from disk

short xcIniFile::OpenRead()
{
    FileIndex = 0;
    return (FileLen > 0);
}




int xcIniFile::GetC(char &C)
{
	while (true)
	{
		if (FileIndex == FileLen)
			return 0;
		else
		{
			C = FileContents[FileIndex++];
			// Unicode Ñapa to avoid NULLs
			if (C) return 1;
		}
	}
}

short xcIniFile::ReadLine(void)
{
    register    char    c = 0;
    register    int    Leidos;
    register    char    *P = Line;
                int     MaxLineLen = MAX_LINE_SIZE;

    LastLineRead = FileContents+FileIndex;
    
    while ((--MaxLineLen > 0)  &&  (Leidos = GetC(c)))
        if(c == '\r' || c == '\n')
            break;
        else
            *(P++) = c;

    if (!Leidos && P == Line)  return FALSE;
    *P = '\0';
    return TRUE;
}



short xcIniFile::ScanForSection (char *Section)
{
    register int SecLen = strlen ( Section );

    // find section, if present
    do {
        if ( !ReadLine()) return FALSE; // didn't find the section.  Return not found
    } while ( *Line != '['  || _strnicmp ( Section, Line+1, SecLen ) || *(Line+1+SecLen) != ']' );
    return TRUE;
}



char *xcIniFile::ScanForKeyName (char *KeyName )
{
    register int KeyLen = strlen ( KeyName );

    do {
        if ( !ReadLine() ) return NULL; // didn't find the keyword
        
        // at the end of an application.  Obviously we didn't find the keyword
        if ( *Line == '[' ) return NULL; // didn't find the keyword.  Return not found
    } while ( _strnicmp ( KeyName, Line, KeyLen )  || *(Line+KeyLen) != '=' );

    // OK, we found it, and it's in the current buffer.  Return success.
    // Success is the nonzero index into the return string of where
    // the result (after the equal sign) is located
    return (Line+KeyLen+1);
}


char *xcIniFile::ScanFor (char *Section, char *KeyName )
{
    if (!ScanForSection(Section))
        return NULL;
        
    return ScanForKeyName (KeyName );
}

// If you want to get an int just use a cast (int)
long   xcIniFile::GetProfileLong(char *SecName, char *KeyName, long Default)
{
    char *Ptr;

    if (!OpenRead()) return Default;
    if (!(Ptr = ScanFor ( SecName, KeyName))) return Default;
    return strtol( Ptr, NULL, 0);
}



// This function now allows you to look into a file with duplicated section names
// It shouldn't be necessary but if you haven't looked to a PTC.ASC file, do it now
// you will find a duplicated RF section
char *xcIniFile::GetProfileStr(char *SecName, char *KeyName, char *Default)
{
    char *Ptr;
	short result = OpenRead();
    if ( !result ) 
        return Default;

    while (TRUE)
    {    
        if ( !ScanForSection( SecName))
            return Default;

        if (Default != (Ptr = GetNextString(KeyName,Default)))
            return Ptr;
    }
}

char *xcIniFile::GetNextString(char *KeyName, char *Default)
{
    register char *Ptr;
    register int i;
    register char *p;


    
    if ( !(Ptr = ScanForKeyName ( KeyName)) ) 
        return Default;

    if ( NULL != ( p = strchr ( Ptr, ';' ) ) ) *p = '\0'; // lets get ride of comments

    // trim off trailing whitespace
    for ( i = strlen (Ptr)-1; i > 0; i-- ) 
        if ( isspace(Ptr[i]) ) Ptr[i] = '\0';   // trim it
        else break;
        
    return Ptr;
}


#define INSERT_SEC_KEY  1
#define INSERT_KEY      2
#define UPDATE_KEY      3
bool  xcIniFile::WriteProfileString(char *SecName, char *KeyName, char *Value)
{
    char    *NewFileContents;
    DWORD   NewFileLen;
    char    *Origen = FileContents;
    char    *Destino;
    char    *CpyPtr;
    int     Action;
    
    if ( NULL != ScanFor (SecName, KeyName ))
    {
        Action = UPDATE_KEY;
    }
    else
    {
        OpenRead(); // In order to reset the counter
        if (ScanForSection (SecName))
        {
            ReadLine(); // To update LastLineRead
            Action = INSERT_KEY;
        }
        else
        {
            Action = INSERT_SEC_KEY;
        }
    }
    
    switch(Action)
    {
        case INSERT_SEC_KEY:
            sprintf(Line,"[%s]\r\n%s=%s\r\n",SecName,KeyName,Value);
            break;

        case INSERT_KEY:
            sprintf(Line,"%s=%s\r\n",KeyName,Value);
            break;
        case UPDATE_KEY:
            sprintf(Line,"%s=%s",KeyName,Value);
            break;
    }

        
	NewFileContents = (char *) new char[strlen(Line)+FileLen+2];
    if (NULL == NewFileContents)
        return false;

    switch(Action)
    {
        case INSERT_SEC_KEY:
            strcpy(NewFileContents,FileContents);
            strcat(NewFileContents,Line);
            NewFileLen = strlen(NewFileContents);
            break;

        case INSERT_KEY:
        case UPDATE_KEY:
            Destino = NewFileContents;
            NewFileLen = 0;
            // copy up to the keyword
            while (Origen != LastLineRead)
            {
                *(Destino++) = *(Origen++);
                NewFileLen++;
            }
            
            // Copy new keyword
            CpyPtr = Line;
            while ('\0' != *CpyPtr)
            {
                *(Destino++) = *(CpyPtr++);
                NewFileLen++;
            }
            
            if (UPDATE_KEY == Action)
            {
                // Skip old keyword (wait enter or end of string
                while ( ('\r' != *Origen) && ('\n' != *Origen) && ('\0' != *Origen) )
                    Origen++;
            }
            
            // copy up to the end of file
            while ('\0' != *Origen)
            {
                *(Destino++) = *(Origen++);
                NewFileLen++;
            }
            
            *Destino = '\0';
            break;
    }

	delete FileContents;
	FileContents = NewFileContents;
	FileLen = NewFileLen;
	FileContentModified = true;
	// This still is in RAM, needs to be commited to disk
	return true;
}

bool  xcIniFile::CommitChanges(wchar_t *NewFileName)
{
	HANDLE File;
	DWORD NumberOfBytesWritten;

	File = CreateFile((NULL == NewFileName)? IniFileName : NewFileName, GENERIC_WRITE, 0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if (NULL == File)
		return false;

	if (0 == WriteFile( File,FileContents,FileLen,&NumberOfBytesWritten,NULL))
	{
		CloseHandle(File);
		return false;
	}

	FileContentModified = false;
	CloseHandle(File);
	return true;
}



void xcIniFile::GetProfileIP(char *SecName, char *KeyName, char *N1, char *N2, char *N3, char *N4)
{
	// Ojo se asume que la ip es correcta y hay siempre tres puntos, hay que corregir para asumir fallos
	char *Dummy = GetProfileStr(SecName, KeyName, "0.0.0.0");
	char  *pI1, *pI2, *pI3, *pI4;

	pI1 = Dummy;
	pI2 = pI1;
	while (L'.' != *pI2) pI2++;
	*pI2++ = 0;
	pI3 = pI2;

	while (L'.' != *pI3) pI3++;
	*pI3++ = 0;
	pI4 = pI3;

	while (L'.' != *pI4) pI4++;
	*pI4++ = 0;

	if (NULL != N1) strcpy(N1,pI1);
	if (NULL != N2) strcpy(N2,pI2);
	if (NULL != N3) strcpy(N3,pI3);
	if (NULL != N4) strcpy(N4,pI4);
}

void xcIniFile::GetProfileIP(char *SecName, char *KeyName, wchar_t *N1, wchar_t *N2, wchar_t *N3, wchar_t *N4)
{
	char szN1[6],szN2[6],szN3[6],szN4[6];
	GetProfileIP(SecName, KeyName, szN1, szN2, szN3, szN4);
	mbstowcs(N1,szN1,4);
	mbstowcs(N2,szN2,4);
	mbstowcs(N3,szN3,4);
	mbstowcs(N4,szN4,4);
}

bool xcIniFile::WriteProfileIP(char *SecName, char *KeyName, wchar_t *N1, wchar_t *N2, wchar_t *N3, wchar_t *N4)
{
	char szN1[6],szN2[6],szN3[6],szN4[6];
	wcstombs(szN1,N1,4);
	wcstombs(szN2,N2,4);
	wcstombs(szN3,N3,4);
	wcstombs(szN4,N4,4);

	return WriteProfileIP(SecName, KeyName, szN1, szN2, szN3, szN4);
}

bool xcIniFile::WriteProfileIP(char *SecName, char *KeyName, char *N1, char *N2, char *N3, char *N4)
{
	char Str[20];

	sprintf(Str,"%d.%d.%d.%d",atoi(N1),atoi(N2),atoi(N3),atoi(N4));
	return WriteProfileString(SecName,KeyName,Str);
}

bool xcIniFile::WriteProfileString(char *SecName, char *KeyName, wchar_t const *Value)
{
	char szStr[MAX_LINE_SIZE];
	wcstombs(szStr,Value,MAX_LINE_SIZE);

	return WriteProfileString(SecName, KeyName, szStr);
}
