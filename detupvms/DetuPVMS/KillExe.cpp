#include "KillExe.h"


KillExe::KillExe()
{
	
}


KillExe::~KillExe()
{
}

void KillExe::KillProcess(LPCWSTR processName)
{
	PROCESSENTRY32 pe;
	DWORD id = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	DWORD current_id = GetCurrentProcessId();


	pe.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hSnapshot, &pe))
	{
		return;
	}

	while (1)
	{
		pe.dwSize = sizeof(PROCESSENTRY32);
		if (Process32Next(hSnapshot, &pe) == FALSE)
		{
			break;
		}
		//find processName
		if (wcsicmp(pe.szExeFile, processName) == 0)
		{
			id = pe.th32ProcessID;
			if (current_id==id)
			{
				continue;
			}
			//Kill The Process
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id);
			if (hProcess != NULL)
			{
				TerminateProcess(hProcess, 0);
				CloseHandle(hProcess);
			}
			//break;
		}
	}

	CloseHandle(hSnapshot);
}