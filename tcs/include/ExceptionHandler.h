#ifndef __INCLUDE_EXCEPTION_HANDLER_H__
#define __INCLUDE_EXCEPTION_HANDLER_H__
#ifdef WIN32
#include <string>

#define GEH		CExceptionHandler::GetExceptionHandler()	
#define	R_A_S	200 * 1024 * 1024	//保留地址空间。

class CExceptionHandler
{
private:
	CExceptionHandler();
public:
	~CExceptionHandler();
	//启动监控
	//参数szFileName:生成dump文件的名字前缀
	//返回值0：成功
	int StartMonitor( const char* szFileName ); 
	//调用生成dump文件
	//参数pExceptionInfo：
	//返回值为EXCEPTION_EXECUTE_HANDLER:正常
	int DoMiniDump( void* pExceptionInfo );
	//谨慎调用该函数，在不确定程序中还存在使用其他异常处理的情况下，不可调用。
	int PreventOtherExceptionHandler(); 
	//获得该单件对象
	//参数无
	//返回值该单件对象
	static CExceptionHandler& GetExceptionHandler();
private:
	int create_mini_dumpfile();
	void close_mini_dumpfile();
	int write_mini_dumpfile( void* pExceptionInfo );
	void release_addr_space();
	void print_error( const char* sDst );
private:
	static CExceptionHandler m_exception_handler;
	std::string m_file_name;
	void* m_file_minidump;
	void* m_addr_space; //地址空间
};

#endif//WIN32
#endif//__INCLUDE_EXCEPTION_HANDLER_H__
