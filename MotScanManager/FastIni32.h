
#ifndef _INI_FILE_HPP_
#define _INI_FILE_HPP_


#define MAX_LINE_SIZE   1024

class xcIniFile {

    public:
	    bool WriteProfileString(char *SecName, char *KeyName, wchar_t const *Value);
                    xcIniFile(wchar_t *IniFile);
                    ~xcIniFile();

			bool	CommitChanges(wchar_t *NewFileName = NULL);
            char *  GetProfileStr(char *SecName, char *KeyName, char *Default);
            long    GetProfileLong(char *SecName, char *KeyName, long Default);
            char *  GetNextString(char *KeyName, char *Default);
			bool	WriteProfileString(char *SecName, char *KeyName, char *Value);
			void	GetProfileIP(char *SecName, char *KeyName, char *N1, char *N2, char *N3, char *N4);
			void	GetProfileIP(char *SecName, char *KeyName, wchar_t *N1, wchar_t *N2, wchar_t *N3, wchar_t *N4);
			bool	WriteProfileIP(char *SecName, char *KeyName, char *N1, char *N2, char *N3, char *N4);
			bool	WriteProfileIP(char *SecName, char *KeyName, wchar_t *N1, wchar_t *N2, wchar_t *N3, wchar_t *N4);

            
    private:
            short   OpenRead(void);
            short   ReadLine(void);
            int     GetC(char &C);
            short   ScanForSection (char *Section);
            char *  ScanForKeyName (char *KeyName );
            char *  ScanFor (char *Section, char *KeyName );
            
            char                *Line; // Here I read a line
            char                *FileContents;  // here I read the complete file
            DWORD	FileLen; //Self explanatory
            unsigned int         FileIndex; // Index to current pos in FileContents
            wchar_t             *IniFileName;
// internal variables
			char			*LastLineRead;
			bool	FileContentModified;
};

#endif

