#ifndef __INCLUDE_EXCEPTION_HANDLER_H__
#define __INCLUDE_EXCEPTION_HANDLER_H__
#ifdef WIN32
#include <string>

#define GEH		CExceptionHandler::GetExceptionHandler()	
#define	R_A_S	200 * 1024 * 1024	//������ַ�ռ䡣

class CExceptionHandler
{
private:
	CExceptionHandler();
public:
	~CExceptionHandler();
	//�������
	//����szFileName:����dump�ļ�������ǰ׺
	//����ֵ0���ɹ�
	int StartMonitor( const char* szFileName ); 
	//��������dump�ļ�
	//����pExceptionInfo��
	//����ֵΪEXCEPTION_EXECUTE_HANDLER:����
	int DoMiniDump( void* pExceptionInfo );
	//�������øú������ڲ�ȷ�������л�����ʹ�������쳣���������£����ɵ��á�
	int PreventOtherExceptionHandler(); 
	//��øõ�������
	//������
	//����ֵ�õ�������
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
	void* m_addr_space; //��ַ�ռ�
};

#endif//WIN32
#endif//__INCLUDE_EXCEPTION_HANDLER_H__
