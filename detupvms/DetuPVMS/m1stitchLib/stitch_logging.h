#pragma once 

#include <fstream>
#include <string>
#include <vector>

#include <stdarg.h>

#ifndef _STITCH_LOGGING_H_
#define _STITCH_LOGGING_H_

/**
* @def PUSH_LOG_STACK
* @brief Pushes the logging stack with the function name that called it
*/
// #define PUSH_LOG_STACK \
// 	const StackLogger stackLoggerTempObject = StackLogger(__FUNCTION__);



/**
* @class STL_LOG
* @brief Basic logging class
* @author Jimmy Thompson (http://jimmythompson.co.uk)
* @author wuqiong
*
* @version $Revision: 1.1 $
* @date $Date: 2012/09/08 - 14:25:00 $
*
* @details Logging class to deal with basic string messages and macro-based
* @details stack tracing. Something quick I made to handle logging in my own
* @details programs.
*/

enum Type 
{
    STL_LOG_TYPE_FATAL,
    STL_LOG_TYPE_ERROR,
    STL_LOG_TYPE_WARN,
    STL_LOG_TYPE_INFO,
    STL_LOG_TYPE_DEBUG
};

class STL_LOG 
{
public:
// 	static const enum Type {
// 		STL_LOG_TYPE_FATAL,
// 		STL_LOG_TYPE_ERROR,
// 		STL_LOG_TYPE_WARN,
// 		STL_LOG_TYPE_INFO,
// 		STL_LOG_TYPE_DEBUG
// 	};

	static const char* TypeToString(const Type& type);

	static bool Initialise(const std::string& fileName);
	static bool Finalise();

	static void SetThreshold(const Type& type);

	static bool Fatal(const std::string& message);
	static bool Fatal(const char* format, ...);

	static bool Error(const std::string& message);
	static bool Error(const char* format, ...);

	static bool Warn(const std::string& message);
	static bool Warn(const char* format, ...);

	static bool Info(const std::string& message);
	static bool Info(const char* format, ...);

	static bool Debug(const std::string& message);
	static bool Debug(const char* format, ...);

	static std::string Peek();
	static bool Push(const std::string& input);
	static std::string Pop();
	static void PrintStackTrace();

private:
	Type m_threshold;
	bool m_initialised;
	std::string m_fileName;
	std::vector<std::string> m_stack;
	std::ofstream m_stream;

	STL_LOG();
	STL_LOG(const STL_LOG&);
	~STL_LOG();

	static STL_LOG& get();

	void write(const char* format, ...);

	bool log(const Type& type, const std::string& message);
	bool log(const Type& type, const char* format, const va_list& varArgs);

	STL_LOG& operator=(const STL_LOG&);
};

// struct StackLogger
// {
// 	StackLogger(const std::string& input)
// 	{
// 		STL_LOG::Push(input);
// 	}
// 
// 	~StackLogger()
// 	{
// 		STL_LOG::Pop();
// 	}
// };

#endif //_STITCH_LOGGING_H_

