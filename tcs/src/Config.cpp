#include "Config.h"
#include "File.h"
#include "Error.h"
#include <assert.h>


static bool is_common_space(char ch)
{
	return (ch == ' ' || ch == '\t' || ch == TCS_CR || ch == TCS_LF);
}


ConfDirective::ConfDirective()
{

}

ConfDirective::~ConfDirective()
{
	std::vector<ConfDirective*>::iterator it;
	for (it = m_directives.begin(); it != m_directives.end(); ++it) {
		ConfDirective* directive = *it;
		if (directive) {
			delete directive;
			directive = NULL;
		}
	}
	m_directives.clear();
}

std::string ConfDirective::Arg0()
{
	if (m_args.size() > 0) {
		return m_args.at(0);
	}

	return "";
}

std::string ConfDirective::Arg1()
{
	if (m_args.size() > 1) {
		return m_args.at(1);
	}

	return "";
}

std::string ConfDirective::Arg2()
{
	if (m_args.size() > 2) {
		return m_args.at(2);
	}

	return "";
}

ConfDirective* ConfDirective::At(int index)
{
	assert(index < (int)m_directives.size());
	return m_directives.at(index);
}

ConfDirective* ConfDirective::Get(std::string _name)
{
	std::vector<ConfDirective*>::iterator it;
	for (it = m_directives.begin(); it != m_directives.end(); ++it) {
		ConfDirective* directive = *it;
		if (directive->m_name == _name) {
			return directive;
		}
	}

	return NULL;
}

ConfDirective* ConfDirective::Get(std::string _name, std::string _arg0)
{
	std::vector<ConfDirective*>::iterator it;
	for (it = m_directives.begin(); it != m_directives.end(); ++it) {
		ConfDirective* directive = *it;
		if (directive->m_name == _name && directive->Arg0() == _arg0) {
			return directive;
		}
	}

	return NULL;
}

int ConfDirective::Parse(_tcs_internal::ConfigBuffer* buffer)
{
	return parse_conf(buffer, parse_file);
}

// see: ngx_conf_parse
int ConfDirective::parse_conf(_tcs_internal::ConfigBuffer* buffer, DirectiveType type)
{
	int ret = ERROR_SUCCESS;

	while (true) {
		std::vector<std::string> args;
		int line_start = 0;
		ret = read_token(buffer, args, line_start);

		/**
		* ret maybe:
		* ERROR_SYSTEM_CONFIG_INVALID           error.
		* ERROR_SYSTEM_CONFIG_DIRECTIVE         directive terminated by ';' found
		* ERROR_SYSTEM_CONFIG_BLOCK_START       token terminated by '{' found
		* ERROR_SYSTEM_CONFIG_BLOCK_END         the '}' found
		* ERROR_SYSTEM_CONFIG_EOF               the config file is done
		*/
		if (ret == ERROR_SYSTEM_CONFIG_INVALID) {
			return ret;
		}
		if (ret == ERROR_SYSTEM_CONFIG_BLOCK_END) {
			if (type != parse_block) {
				printf("line %d: unexpected \"}\", ret=%d.\n", buffer->m_line, ret);
				return ret;
			}
			return ERROR_SUCCESS;
		}
		if (ret == ERROR_SYSTEM_CONFIG_EOF) {
			if (type == parse_block) {
				printf("line %d: unexpected end of file, expecting \"}\", ret=%d.\n", m_conf_line, ret);
				return ret;
			}
			return ERROR_SUCCESS;
		}

		if (args.empty()) {
			ret = ERROR_SYSTEM_CONFIG_INVALID;
			printf("line %d: empty directive. ret=%d.\n", m_conf_line, ret);
			return ret;
		}

		// build directive tree.
		ConfDirective* directive = new ConfDirective();

		directive->m_conf_line = line_start;
		directive->m_name = args[0];
		args.erase(args.begin());
		directive->m_args.swap(args);

		m_directives.push_back(directive);

		if (ret == ERROR_SYSTEM_CONFIG_BLOCK_START) {
			if ((ret = directive->parse_conf(buffer, parse_block)) != ERROR_SUCCESS) {
				return ret;
			}
		}
	}

	return ret;
}

// see: ngx_conf_read_token
int ConfDirective::read_token(_tcs_internal::ConfigBuffer* buffer, std::vector<std::string>& args, int& line_start)
{
	int ret = ERROR_SUCCESS;

	char* pstart = buffer->m_pos;

	bool sharp_comment = false;

	bool d_quoted = false;
	bool s_quoted = false;

	bool need_space = false;
	bool last_space = true;

	while (true) {
		if (buffer->Empty()) {
			ret = ERROR_SYSTEM_CONFIG_EOF;

			if (!args.empty() || !last_space) {
				printf("line %d: unexpected end of file, expecting ; or \"}\" \n", buffer->m_line);
				return ERROR_SYSTEM_CONFIG_INVALID;
			}
			printf("config parse complete.\n");

			return ret;
		}

		char ch = *buffer->m_pos++;

		if (ch == TCS_LF) {
			buffer->m_line++;
			sharp_comment = false;
		}

		if (sharp_comment) {
			continue;
		}

		if (need_space) {
			if (is_common_space(ch)) {
				last_space = true;
				need_space = false;
				continue;
			}
			if (ch == ';') {
				return ERROR_SYSTEM_CONFIG_DIRECTIVE;
			}
			if (ch == '{') {
				return ERROR_SYSTEM_CONFIG_BLOCK_START;
			}
			printf("line %d: unexpected '%c'.\n", buffer->m_line, ch);
			return ERROR_SYSTEM_CONFIG_INVALID;
		}

		// last charecter is space.
		if (last_space) {
			if (is_common_space(ch)) {
				continue;
			}
			pstart = buffer->m_pos - 1;
			switch (ch) {
			case ';':
				if (args.size() == 0) {
					printf("line %d: unexpected ';'.\n", buffer->m_line);
					return ERROR_SYSTEM_CONFIG_INVALID;
				}
				return ERROR_SYSTEM_CONFIG_DIRECTIVE;
			case '{':
				if (args.size() == 0) {
					printf("line %d: unexpected '{'.\n", buffer->m_line);
					return ERROR_SYSTEM_CONFIG_INVALID;
				}
				return ERROR_SYSTEM_CONFIG_BLOCK_START;
			case '}':
				if (args.size() != 0) {
					printf("line %d: unexpected '}'.\n", buffer->m_line);
					return ERROR_SYSTEM_CONFIG_INVALID;
				}
				return ERROR_SYSTEM_CONFIG_BLOCK_END;
			case '#':
				sharp_comment = 1;
				continue;
			case '"':
				pstart++;
				d_quoted = true;
				last_space = 0;
				continue;
			case '\'':
				pstart++;
				s_quoted = true;
				last_space = 0;
				continue;
			default:
				last_space = 0;
				continue;
			}
		} else {
			// last charecter is not space
			if (line_start == 0) {
				line_start = buffer->m_line;
			}

			bool found = false;
			if (d_quoted) {
				if (ch == '"') {
					d_quoted = false;
					need_space = true;
					found = true;
				}
			} else if (s_quoted) {
				if (ch == '\'') {
					s_quoted = false;
					need_space = true;
					found = true;
				}
			} else if (is_common_space(ch) || ch == ';' || ch == '{') {
				last_space = true;
				found = 1;
			}

			if (found) {
				int len = (int)(buffer->m_pos - pstart);
				char* aword = new char[len];
				memcpy(aword, pstart, len);
				aword[len - 1] = 0;

				std::string word_str = aword;
				if (!word_str.empty()) {
					args.push_back(word_str);
				}
				if (aword) {
					delete[] aword;
					aword = NULL;
				}

				if (ch == ';') {
					return ERROR_SYSTEM_CONFIG_DIRECTIVE;
				}
				if (ch == '{') {
					return ERROR_SYSTEM_CONFIG_BLOCK_START;
				}
			}
		}
	}

	return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

CTcsConfig::CTcsConfig()
{
	root = new ConfDirective();
	root->m_conf_line = 0;
	root->m_name = "root";
}

CTcsConfig::~CTcsConfig()
{
	if (root) {
		delete root;
		root = NULL;
	}
}

// see: ngx_get_options
int CTcsConfig::ParseOptions(std::string config_path)
{
	int ret = ERROR_SUCCESS;

	if (config_path.empty()) {
		ret = ERROR_SYSTEM_CONFIG_INVALID;
		printf("config file not specified,ret=%d.\n", ret);
		return ret;
	}

	config_file = config_path;
	ret = ParseFile(config_file.c_str());

	return ret;
}

int CTcsConfig::ParseFile(const char* filename)
{
	int ret = ERROR_SUCCESS;

	config_file = filename;

	if (config_file.empty()) {
		return ERROR_SYSTEM_CONFIG_INVALID;
	}

	_tcs_internal::ConfigBuffer buffer;

	if ((ret = buffer.FullFill(config_file.c_str())) != ERROR_SUCCESS) {
		return ret;
	}

	return ParseBuffer(&buffer);
}

int CTcsConfig::CheckConfig()
{
	int ret = ERROR_SUCCESS;

	printf("tcs checking config...\n");

	if (root->m_directives.size() == 0) {
		ret = ERROR_SYSTEM_CONFIG_INVALID;
		printf("conf is empty, ret=%d.\n", ret);
		return ret;
	}

	for (int i = 0; i < (int)root->m_directives.size(); i++) {
		ConfDirective* conf = root->At(i);
		std::string n = conf->m_name;
		if (n != "listen" && n != "server_id" && n != "bls" && n != "expires" && n != "log" && n != "max_connections" &&
			n != "url_addr" && n != "decode_type" && n != "encode_type" && n != "ipc_reserve") {
			ret = ERROR_SYSTEM_CONFIG_INVALID;
			printf("unsupported directive %s, ret=%d.\n", n.c_str(), ret);
			return ret;
		}
	}

	if (GetListenPort() <= 0) {
		ret = ERROR_SYSTEM_CONFIG_INVALID;
		printf("directive listen invalid, ret=%d.\n", ret);
		return ret;
	}

	if (GetServerId() <= 0) {
		ret = ERROR_SYSTEM_CONFIG_INVALID;
		printf("directive server_id invalid, ret=%d.\n", ret);
		return ret;
	}

	if (GetBLS() == "") {
		ret = ERROR_SYSTEM_CONFIG_INVALID;
		printf("directive bls invalid, ret=%d.\n", ret);
		return ret;
	}

	if (GetUrlAddr() == "") {
		ret = ERROR_SYSTEM_CONFIG_INVALID;
		printf("directive url_addr invalid, ret=%d.\n", ret);
		return ret;
	}

	printf("tcs checking config success.\n");
	return ret;
}

int CTcsConfig::ParseBuffer(_tcs_internal::ConfigBuffer* buffer)
{
	int ret = ERROR_SUCCESS;

	if ((ret = root->Parse(buffer)) != ERROR_SUCCESS) {
		return ret;
	}

	return ret;
}

int CTcsConfig::GetMaxConnections()
{
	assert(root);

	ConfDirective* conf = root->Get("max_connections");
	if (!conf || conf->Arg0().empty()) {
		printf("can't find max_connections options, set default value:%d.\n", TCS_CONF_DEFAULT_MAX_CONNECTIONS);
		return TCS_CONF_DEFAULT_MAX_CONNECTIONS;
	}

	int max_connections = ::atoi(conf->Arg0().c_str());
	return max_connections;
}

int CTcsConfig::GetListenPort()
{
	assert(root);

	ConfDirective* conf = root->Get("listen");
	if (!conf || conf->Arg0().empty()) {
		printf("can't find listen options.\n");
		return ERROR_FAILED;
	}

	int port = ::atoi(conf->Arg0().c_str());
	return port;
}

std::string CTcsConfig::GetBLS()
{
	assert(root);

	ConfDirective* conf = root->Get("bls");
	if (!conf || conf->Arg0().empty()) {
		return "";
	}

	return conf->Arg0();
}

std::string CTcsConfig::GetUrlAddr()
{
	assert(root);

	ConfDirective* conf = root->Get("url_addr");
	if (!conf || conf->Arg0().empty() || conf->Arg0().size() > MAX_IP_LENGTH) {
		return "";
	}

	return conf->Arg0();
}

int CTcsConfig::GetServerId()
{
	assert(root);

	ConfDirective* conf = root->Get("server_id");
	if (!conf || conf->Arg0().empty()) {
		printf("can't find server id options.\n");
		return ERROR_FAILED;
	}

	int server_id = ::atoi(conf->Arg0().c_str());
	return server_id;
}

int CTcsConfig::GetExpires()
{
	assert(root);

	ConfDirective* conf = root->Get("expires");
	if (!conf || conf->Arg0().empty()) {
		printf("can't find expires options, set default value:%d.\n", TCS_CONF_DEFAULT_EXXPIRES);
		return TCS_CONF_DEFAULT_EXXPIRES;
	}

	int expires = ::atoi(conf->Arg0().c_str());
	return expires;
}

int CTcsConfig::GetDecodeType()
{
	assert(root);

	ConfDirective* conf = root->Get("decode_type");
	if (!conf || conf->Arg0().empty()) {
		printf("can't find decode type options, set default value:0.\n");
		return 0;
	}

	int decode_type = ::atoi(conf->Arg0().c_str());
	return decode_type;
}

int CTcsConfig::GetEncodeType()
{
	assert(root);

	ConfDirective* conf = root->Get("encode_type");
	if (!conf || conf->Arg0().empty()) {
		printf("can't find encode type options, set default value:0.\n");
		return 0;
	}

	int encode_type = ::atoi(conf->Arg0().c_str());
	return encode_type;
}

int CTcsConfig::GetReserveDegress()
{
	assert(root);

	ConfDirective* conf = root->Get("ipc_reserve");
	if (!conf || conf->Arg0().empty()) {
		printf("can't find reserve degress options, set default value:0.\n");
		return 0;
	}

	int reserve_degress = ::atoi(conf->Arg0().c_str());
	return reserve_degress;
}

int	CTcsConfig::GetLogDuration()
{
	assert(root);

	ConfDirective* conf = get_log_directive();
	if (!conf) {
		return RCS_CONF_DEFAULT_LOG_DURATION;
	}

	conf = conf->Get("tcs_log_duration");
	if (!conf || conf->Arg0().empty()) {
		return RCS_CONF_DEFAULT_LOG_DURATION;
	}

	int duration = ::atoi(conf->Arg0().c_str());
	return duration;
}

std::string CTcsConfig::GetLogLevel()
{
	assert(root);

	ConfDirective* conf = get_log_directive();
	if (!conf) {
		return TCS_CONF_DEFAULT_LOG_LEVEL;
	}

	conf = conf->Get("tcs_log_level");
	if (!conf || conf->Arg0().empty()) {
		return TCS_CONF_DEFAULT_LOG_LEVEL;
	}

	return conf->Arg0();
}

std::string CTcsConfig::GetLogPath()
{
	assert(root);

	ConfDirective* conf = get_log_directive();
	if (!conf) {
		return TCS_CONF_DEFAULT_LOG_PATH;
	}

	conf = conf->Get("tcs_log_path");
	if (!conf || conf->Arg0().empty()) {
		return TCS_CONF_DEFAULT_LOG_PATH;
	}
	return conf->Arg0();
}

ConfDirective* CTcsConfig::get_log_directive()
{
	return root->Get("log");
}

void CTcsConfig::set_config_directive(ConfDirective* parent, std::string dir, std::string value)
{
	ConfDirective* d = parent->Get(dir);

	if (!d) {
		d = new ConfDirective();
		if (!dir.empty()) {
			d->m_name = dir;
		}
		parent->m_directives.push_back(d);
	}

	d->m_args.clear();
	if (!value.empty()) {
		d->m_args.push_back(value);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

namespace _tcs_internal {
	ConfigBuffer::ConfigBuffer()
	{
		m_line = 1;

		m_pos = m_last = m_start = NULL;
		m_end = m_start;
	}

	ConfigBuffer::~ConfigBuffer()
	{
		if (m_start) {
			delete[] m_start;
			m_start = NULL;
		}
	}

	int ConfigBuffer::FullFill(const char* filename)
	{
		int ret = ERROR_SUCCESS;

		FileReader reader;

		// open file reader.
		if ((ret = reader.Open(filename)) != ERROR_SUCCESS) {
			printf("open conf file error. ret=%d.\n", ret);
			return ret;
		}

		// read all.
		int filesize = (int)reader.FileSize();

		// create buffer
		if (m_start) {
			delete[] m_start; 
			m_start = NULL; 
		}
		m_pos = m_last = m_start = new char[filesize];
		m_end = m_start + filesize;

		// read total content from file.
		ssize_t nread = 0;
		if ((ret = reader.Read(m_start, filesize, &nread)) != ERROR_SUCCESS) {
			printf("read file read error. expect %d, actual %d bytes, ret=%d.\n",
				filesize, nread, ret);
			return ret;
		}

		return ret;
	}

	bool ConfigBuffer::Empty()
	{
		return m_pos >= m_end;
	}
};
