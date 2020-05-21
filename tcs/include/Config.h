/**
* Copy from SRS
* data: 2017/11/14
*/

#ifndef _TCS_CONFIG_H_
#define _TCS_CONFIG_H_

#include <vector>
#include <string>

#define MAX_IP_LENGTH	32
#define TCS_CONF_DEFAULT_MAX_CONNECTIONS 5
#define TCS_CONF_DEFAULT_LOG_LEVEL	"info"
#define TCS_CONF_DEFAULT_LOG_PATH	"./log/tcs.log"
#define TCS_CONF_DEFAULT_EXXPIRES	15
#define RCS_CONF_DEFAULT_LOG_DURATION	24

#define TCS_CONSTS_CR '\r' // 0x0D
#define TCS_CONSTS_LF '\n' // 0x0A

#define TCS_LF (char)TCS_CONSTS_LF
#define TCS_CR (char)TCS_CONSTS_CR

namespace _tcs_internal {
	class ConfigBuffer;
}

class ConfDirective
{
public:
	ConfDirective();
	virtual ~ConfDirective();

public:
	/**
	* get the args0,1,2, if user want to get more args,
	* directly use the args.at(index).
	*/
	virtual std::string Arg0();
	virtual std::string Arg1();
	virtual std::string Arg2();

public:
	/**
	* get the directive by index.
	* @remark, assert the index<directives.size().
	*/
	virtual ConfDirective* At(int index);
	/**
	* get the directive by name, return the first match.
	*/
	virtual ConfDirective* Get(std::string _name);
	/**
	* get the directive by name and its arg0, return the first match.
	*/
	virtual ConfDirective* Get(std::string _name, std::string _arg0);

public:
	/**
	* parse config directive from file buffer.
	*/
	virtual int Parse(_tcs_internal::ConfigBuffer* buffer);

private:
	/**
	* the directive parsing type.
	*/
	enum DirectiveType {
		/**
		* the root directives, parsing file.
		*/
		parse_file,
		/**
		* for each direcitve, parsing text block.
		*/
		parse_block
	};
	/**
	* parse the conf from buffer. the work flow:
	* 1. read a token(directive args and a ret flag),
	* 2. initialize the directive by args, args[0] is name, args[1-N] is args of directive,
	* 3. if ret flag indicates there are child-directives, read_conf(directive, block) recursively.
	*/
	virtual int parse_conf(_tcs_internal::ConfigBuffer* buffer, DirectiveType type);
	/**
	* read a token from buffer.
	* a token, is the directive args and a flag indicates whether has child-directives.
	* @param args, the output directive args, the first is the directive name, left is the args.
	* @param line_start, the actual start line of directive.
	* @return, an error code indicates error or has child-directives.
	*/
	virtual int read_token(_tcs_internal::ConfigBuffer* buffer, std::vector<std::string>& args, int& line_start);

public:
	/**
	* the line of config file in which the directive from
	*/
	int m_conf_line;
	/**
	* the name of directive, for example, the following config text:
	*       enabled     on;
	* will be parsed to a directive, its name is "enabled"
	*/
	std::string m_name;
	/**
	* the args of directive, for example, the following config text:
	*       listen      1935 1936;
	* will be parsed to a directive, its args is ["1935", "1936"].
	*/
	std::vector<std::string> m_args;
	/**
	* the child directives, for example, the following config text:
	*       vhost vhost.ossrs.net {
	*           enabled         on;
	*       }
	* will be parsed to a directive, its directives is a vector contains
	* a directive, which is:
	*       name:"enalbed", args:["on"], directives:[]
	*
	* @remark, the directives can contains directives.
	*/
	std::vector<ConfDirective*> m_directives;
};


/**
* the config service provider.
* for the config supports reload, so never keep the reference cross st-thread,
* that is, never save the SrsConfDirective* get by any api of config,
* for it maybe free in the reload st-thread cycle.
* you can keep it before st-thread switch, or simply never keep it.
*/
class CTcsConfig
{
public:
	CTcsConfig();
	virtual ~CTcsConfig();

public:
	/**
	* parse the cli, the main(argc,argv) function.
	*/
	virtual int ParseOptions(std::string config_path);

public:
	/**
	* parse the config file, which is specified by cli.
	*/
	virtual int ParseFile(const char* filename);
	/**
	* check the parsed config.
	*/
	virtual int CheckConfig();

protected:
	/**
	* parse config from the buffer.
	* @param buffer, the config buffer, user must delete it.
	* @remark, use protected for the utest to override with mock.
	*/
	virtual int ParseBuffer(_tcs_internal::ConfigBuffer* buffer);

public:
	/**
	* get the max connections limit of system.
	*/
	virtual int	GetMaxConnections();
	/**
	* get the listen port of server.
	* user can specifies multiple listen ports,
	* each args of directive is a listen port.
	*/
	virtual int	GetListenPort();
	/**
	* get the listen address of cms
	*/
	virtual std::string GetBLS();
	/**
	* get the url of tcs
	*/
	virtual std::string GetUrlAddr();
	/**
	* get tcs server id
	*/
	virtual int GetServerId();
	/**
	* get expires
	*/
	virtual int GetExpires();
	/**
	* get decode type
	*/
	virtual int GetDecodeType();
	/**
	* get encode type
	*/
	virtual int GetEncodeType();
	/**
	* get reserve degress
	*/
	virtual int GetReserveDegress();

public:
	/**
	* get the log duration.
	*/
	virtual int	GetLogDuration();
	/**
	* get the log level.
	*/
	virtual std::string		GetLogLevel();
	/**
	* get the log file path.
	*/
	virtual std::string		GetLogPath();

private:
	ConfDirective* get_log_directive();
	void set_config_directive(ConfDirective* parent, std::string dir, std::string value);

private:
	/**
	* the last parsed config file.
	* if reload, reload the config file.
	*/
	std::string config_file;
	/**
	* the directive root.
	*/
	ConfDirective* root;
};


namespace _tcs_internal {
	/**
	* the buffer of config content.
	*/
	class ConfigBuffer
	{
	protected:
		// last available position.
		char* m_last;
		// end of buffer.
		char* m_end;
		// start of buffer.
		char* m_start;
	public:
		// current consumed position.
		char* m_pos;
		// current parsed line.
		int m_line;
	public:
		ConfigBuffer();
		virtual ~ConfigBuffer();
	public:
		/**
		* fullfill the buffer with content of file specified by filename.
		*/
		virtual int FullFill(const char* filename);
		/**
		* whether buffer is empty.
		*/
		virtual bool Empty();
	};
};

#endif
