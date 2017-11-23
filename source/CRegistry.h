#ifndef CREGISTRY_H
#define CREGISTRY_H

#include <windows.h>
#include "..\Resource\resource.h"
#include <strstream>
#include <string>

typedef struct _REGKEYCLASS 
{ 
    LPCSTR  lpKeyName;
	LPCTSTR lpValueName; 
    DWORD   dwValue; 
} REGKEYCLASS;

class CRegistry
{
private:
	REGKEYCLASS m_rk;
	int starts;
	bool open;

public:
	CRegistry();
	~CRegistry();

	void SetRegistryKeyValue(HKEY, REGKEYCLASS);
	void OpenRegistryKey(HKEY, REGKEYCLASS);

	void GetRegStarts();
	void GetRegOpen();
	int getStarts();
	bool isOpen();
	void setClose();
};

#endif
