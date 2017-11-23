#include "CRegistry.h"

using namespace std;

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////
CRegistry::CRegistry()
{
	GetRegOpen();
	GetRegStarts();
}


CRegistry::~CRegistry()
{
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////
void CRegistry::SetRegistryKeyValue(HKEY hKey, REGKEYCLASS rk)
{
	//verander de register sleutel data
	RegSetValueEx(hKey, rk.lpValueName, 0, REG_DWORD, (unsigned char *)&rk.dwValue,
		sizeof(rk.dwValue));
}

int CRegistry::getStarts()
{
	return starts;
}

bool CRegistry::isOpen()
{
	return open;
}

void CRegistry::setClose()
{
	HKEY				hKey;
	REGKEYCLASS			rk;
	LONG				lRv;
	DWORD				dwDisposition;

	hKey =				HKEY_LOCAL_MACHINE;
	rk.dwValue = 0;
	rk.lpKeyName =	"Software\\PSPManager";
	rk.lpValueName =	"Open"; 

	lRv = RegCreateKeyEx (hKey, rk.lpKeyName, 0, NULL, REG_OPTION_NON_VOLATILE, 
	KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition);

	
	if (lRv == ERROR_SUCCESS)								//als het gelukt is....
	{
		rk.dwValue = 0;
    	if (dwDisposition != REG_CREATED_NEW_KEY)			//controleer of er een nieuwe
															//sleutel aangemaakt is of dat
															//er een sleutel geopend is
		{
			//zet de nieuwe waarde in de sleutel
			SetRegistryKeyValue(hKey, rk);
		}
	}
}

void CRegistry::GetRegStarts()
{
	HKEY				hKey;
	REGKEYCLASS			rk;
	LONG				lRv;
	DWORD				dwDisposition,
						dwType,
						dwLen;

	hKey =				HKEY_LOCAL_MACHINE;
	rk.lpKeyName =	"Software\\PSPManager";
	rk.lpValueName =	"Starts";


	//KEY AANMAKEN//
	lRv = RegCreateKeyEx (hKey, rk.lpKeyName, 0, NULL, REG_OPTION_NON_VOLATILE, 
	KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition);

	
	if (lRv == ERROR_SUCCESS)								//als hetgelukt is....
	{
		rk.dwValue = 0;
    	if (dwDisposition != REG_CREATED_NEW_KEY)			//controleer of er een nieuwe
															//sleutel aangemaakt is of dat
															//er een sleutel geopend is
		{
			//vraag de waarde van de sleutel op
			dwType = REG_DWORD;
			RegQueryValueEx(hKey, rk.lpValueName, NULL, &dwType, 
				(unsigned char *)&rk.dwValue, &dwLen);
		}

		rk.dwValue++;

		starts = rk.dwValue;

		//zet de nieuwe waarde in de sleutel
		SetRegistryKeyValue(hKey, rk);
	}
	else
		starts = -1;
	
	
	RegCloseKey (HKEY_LOCAL_MACHINE);
}

void CRegistry::GetRegOpen()
{
	HKEY				hKey;
	REGKEYCLASS			rk;
	LONG				lRv;
	DWORD				dwDisposition,
						dwType,
						dwLen;

	hKey =				HKEY_LOCAL_MACHINE;
	rk.lpKeyName =	"Software\\PSPManager";
	rk.lpValueName =	"Open";


	//KEY AANMAKEN//
	lRv = RegCreateKeyEx (hKey, rk.lpKeyName, 0, NULL, REG_OPTION_NON_VOLATILE, 
	KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition);

	
	if (lRv == ERROR_SUCCESS)								//als hetgelukt is....
	{
		rk.dwValue = 0;
    	if (dwDisposition != REG_CREATED_NEW_KEY)			//controleer of er een nieuwe
															//sleutel aangemaakt is of dat
															//er een sleutel geopend is
		{
			//vraag de waarde van de sleutel op
			dwType = REG_DWORD;
			RegQueryValueEx(hKey, rk.lpValueName, NULL, &dwType, 
				(unsigned char *)&rk.dwValue, &dwLen);
		}

		if (rk.dwValue >= 1)
			open = true;
		else
		{
			open = false;
			rk.dwValue = 1;
			//zet de nieuwe waarde in de sleutel
			SetRegistryKeyValue(hKey, rk);
		}

	}
	else
		open = true;
	
	
	RegCloseKey (HKEY_LOCAL_MACHINE);
}
