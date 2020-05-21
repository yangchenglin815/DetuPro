#ifdef WIN32
#undef UNICODE
#include "ExceptionHandler.h"
#include <Windows.h>
#include <dbghelp.h>
#include <excpt.h>

CExceptionHandler CExceptionHandler::m_exception_handler;

CExceptionHandler::CExceptionHandler()
{
	m_file_minidump = INVALID_HANDLE_VALUE;
	m_addr_space = NULL;
}

CExceptionHandler::~CExceptionHandler()
{
	release_addr_space();
}

LONG WINAPI my_exception_handle(struct _EXCEPTION_POINTERS* ExceptionInfo)
{
	printf("enter my_exception_handle handle\n");
	if(ExceptionInfo)
		return GEH.DoMiniDump( (void*)ExceptionInfo );
	else
	{
		printf("struct _EXCEPTION_POINTERS* ExceptionInfo == NULL\n");
		return EXCEPTION_CONTINUE_SEARCH;
	}
}

void purecall_handler(void)
{
	printf("enter purecall_handler handle\n");
	GEH.DoMiniDump( NULL );
} 

void invalidparameter_handle(const wchar_t* expression, const wchar_t* function, const wchar_t* file, unsigned int line, uintptr_t pReserved)
{
	printf("enter invalidparameter_handle handle\n");
	GEH.DoMiniDump( (void*)expression );
	int* p = NULL;
	*p = 0;	//强制出错
}

LPTOP_LEVEL_EXCEPTION_FILTER
WINAPI
SetUnhandledExceptionFilter2( __in LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter )
{
	printf("enter SetUnhandledExceptionFilter2\n");
	return 0;
}

int CExceptionHandler::StartMonitor(const char* szFileName)
{
	::SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
	::SetUnhandledExceptionFilter(my_exception_handle);
	::_set_purecall_handler(purecall_handler);
	::_set_invalid_parameter_handler(invalidparameter_handle);
	m_addr_space = VirtualAlloc( 0, R_A_S, MEM_RESERVE, PAGE_EXECUTE_READWRITE );

	if(szFileName)
		m_file_name = szFileName;
	else
		m_file_name = " ";

	printf("Start ExceptionHandler...\n");
	return 0;
}

int CExceptionHandler::DoMiniDump( void* pExceptionInfo )
{
	if( create_mini_dumpfile() )
		return EXCEPTION_EXECUTE_HANDLER;

	MINIDUMP_EXCEPTION_INFORMATION exception_param;
	exception_param.ExceptionPointers = (PEXCEPTION_POINTERS)pExceptionInfo;
	exception_param.ThreadId = GetCurrentThreadId();
	exception_param.ClientPointers = TRUE;

	release_addr_space();

	if(pExceptionInfo)
		write_mini_dumpfile(&exception_param); //此处无需在申请地址空间，程序将会退出。
	else
	{
		write_mini_dumpfile(NULL);
		m_addr_space = VirtualAlloc(0, R_A_S, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	}

	close_mini_dumpfile();
	printf("DoMiniDump OK...\n");
	return EXCEPTION_EXECUTE_HANDLER;
}

int CExceptionHandler::PreventOtherExceptionHandler()
{
	HMODULE hKernel32 = LoadLibrary("kernel32.dll");
	if (hKernel32 == NULL) 
		return 1;

	void *pOrgEntry = GetProcAddress(hKernel32, "SetUnhandledExceptionFilter");
	if(pOrgEntry == NULL) 
		return 1;

	DWORD dwOldProtect = 0;
	SIZE_T jmpSize = 5;

	BOOL bProt = VirtualProtect(pOrgEntry, jmpSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	if (!bProt)
	{
		print_error("PreventOtherExceptionHandling");
		return 1;
	}

	BYTE newJump[20];
	void *pNewFunc = &SetUnhandledExceptionFilter2;

	SIZE_T dwOrgEntryAddr = (SIZE_T) pOrgEntry;
	dwOrgEntryAddr += jmpSize; // add 5 for 5 op-codes for jmp rel32
	SIZE_T dwNewEntryAddr = (SIZE_T) pNewFunc;
	SIZE_T dwRelativeAddr = dwNewEntryAddr - dwOrgEntryAddr;
	// JMP rel32: Jump near, relative, displacement relative to next instruction.
	newJump[0] = 0xE9;  // JMP rel32
	memcpy(&newJump[1], &dwRelativeAddr, sizeof(pNewFunc));

	SIZE_T bytesWritten;
	BOOL bRet = WriteProcessMemory(GetCurrentProcess(), pOrgEntry, newJump, jmpSize, &bytesWritten);
	if (!bRet)
	{
		print_error("PreventOtherExceptionHandling");
		return 1;
	}

	DWORD dwBuf;
	VirtualProtect(pOrgEntry, jmpSize, dwOldProtect, &dwBuf);
	return 0;
}

CExceptionHandler& CExceptionHandler::GetExceptionHandler()
{
	return CExceptionHandler::m_exception_handler;
}

int CExceptionHandler::create_mini_dumpfile()
{
	char file_name[MAX_PATH];
	SYSTEMTIME lpSystemTime;

	::GetLocalTime(&lpSystemTime);
	_snprintf_s(file_name, sizeof(file_name), sizeof(file_name), "%s-%04d%02d%02d-%02d%02d%02d-%ld.dmp", m_file_name.c_str(),
				lpSystemTime.wYear, lpSystemTime.wMonth, lpSystemTime.wDay, lpSystemTime.wHour, lpSystemTime.wMinute, 
				lpSystemTime.wSecond, GetCurrentProcessId() ); 

	m_file_minidump = ::CreateFile(file_name, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (m_file_minidump == INVALID_HANDLE_VALUE)
	{
		print_error("CreateMiniDumpFile");
		return 1;
	}

	return 0;
}

void CExceptionHandler::close_mini_dumpfile()
{
	if(m_file_minidump != INVALID_HANDLE_VALUE)
		CloseHandle(m_file_minidump);

	m_file_minidump = INVALID_HANDLE_VALUE;
}

int CExceptionHandler::write_mini_dumpfile( void* pExceptionInfo )
{
	if( !MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), m_file_minidump, 
						   MiniDumpWithFullMemory/*MiniDumpNormal*/, (PMINIDUMP_EXCEPTION_INFORMATION)pExceptionInfo, NULL, NULL))
	{
		print_error("WriteMiniDumpFile");
		return 1;
	}

	return 0;
}

void CExceptionHandler::print_error( const char* sDst )
{
	LPVOID lpMsgBuf;

	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
		);

	printf( "%s failed, error: %s\n", sDst, lpMsgBuf);
	LocalFree( lpMsgBuf );
}

void CExceptionHandler::release_addr_space()
{
	if(m_addr_space)
	{
		VirtualFree(m_addr_space, 0, MEM_RELEASE);
		m_addr_space = NULL;
	}
}

#endif
