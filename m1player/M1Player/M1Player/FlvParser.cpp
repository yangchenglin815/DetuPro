#include "FlvParser.h"
#include "ijksdl_log.h"

CFlvParser::CFlvParser()
{
	m_fp = NULL;
	m_file_size = 0;
	m_current_tag = NULL;
}

CFlvParser::~CFlvParser()
{

}

int CFlvParser::Init(void)
{
	if (!m_current_tag) {
		m_current_tag = (FlvTag *)malloc(sizeof(FlvTag));
		memset(m_current_tag, 0, sizeof(FlvTag));
		m_current_tag->buffer = (char*)malloc(MAX_TAG_SIZE);
	}

	return 1;
}

int CFlvParser::OpenRead(const char* filename)
{
	m_fp = fopen(filename, "rb+");
	if (!m_fp) {
        ALOGE("open file for read error, file path:%s", filename);
		return -1;
	}

	fseek(m_fp, 0, SEEK_END);
	m_file_size = ftell(m_fp);

	fseek(m_fp, FLV_HEADER_LENGTH + PREVIOUS_TAG_SIZE, SEEK_SET);
	return 0;
}

int CFlvParser::CreateFlvFile(const char* filename)
{
	m_fp = fopen(filename, "wb+");
	if (!m_fp) {
        ALOGE("open flv for write failed, file path:%s", filename);
		return -1;
	}

	char previous_tag_size[4] = { 0 };
	const char flv_header[] = { 'F', 'L', 'V', 0x01, 0x05, 0x00, 0x00, 0x00, 0x09 };

	fwrite(flv_header, 1, 9, m_fp);				//flv header
	fwrite(previous_tag_size, 1, 4, m_fp);		//previous_tag_size_#0

	return 0;
}

FlvTag* CFlvParser::ReadTag(void)
{
	if (!read_u8(&(m_current_tag->type))) {
        ALOGE("read tag type error.\n");
		return NULL;
	}

	if (!read_u24(&(m_current_tag->datalength))) {
		ALOGE("read tag datalength error.\n");
		return NULL;
	}

	if (!read_utime(&(m_current_tag->timestamp))) {
		ALOGE("read tag timestamp error.");
		return NULL;
	}

	if (!read_u24(&(m_current_tag->streamid))) {
		ALOGE("read tag streamid error.");
		return NULL;
	}

	if (m_current_tag->datalength > MAX_TAG_SIZE) {
		m_current_tag->buffer = (char*)realloc(m_current_tag->buffer, m_current_tag->datalength);
	}

	if (fread(m_current_tag->buffer, 1, m_current_tag->datalength, m_fp) != m_current_tag->datalength) {
		int current_pos = ftell(m_fp);
		if (m_file_size == current_pos) {
			ALOGE("file read over.");
		} else {
			ALOGE("read tag error.");
		}
		return NULL;
	}

	if (!read_u32(&(m_current_tag->taglength))) {
		ALOGE("read previous tag size error.");
		return NULL;
	}

	if (m_current_tag->type == RTMP_PACKET_TYPE_VIDEO) {
		parser_video_tag_data();
	} else if (m_current_tag->type == RTMP_PACKET_TYPE_AUDIO) {
		parser_audio_tag_data();
	} else if (m_current_tag->type == RTMP_PACKET_TYPE_INFO) {
		parser_metadata();
	} else {
		ALOGE("unknow tag type:%d", m_current_tag->type);
	}

	return m_current_tag;
}

int CFlvParser::WriteTag(FlvTag* tag)
{
	if ((tag->datalength + 11) != tag->taglength) {
		ALOGE("tag format error.");
		return -1;
	}

	write_u8(tag->type);
	write_u24(tag->datalength - RTMP_BUFFER_FAKE_NUAL_LENGTH - RTMP_VIDEO_DATA_WRONG_BYTES);
	write_utime(tag->timestamp);
	write_u24(tag->streamid);
	fwrite(tag->buffer, 1, RTMP_VIDEO_DATA_HEADER_LENGTH, m_fp);
	fwrite(tag->buffer + RTMP_VIDEO_DATA_HEADER_LENGTH + RTMP_BUFFER_FAKE_NUAL_LENGTH + RTMP_VIDEO_DATA_WRONG_BYTES, 1, tag->datalength - RTMP_VIDEO_DATA_HEADER_LENGTH - RTMP_BUFFER_FAKE_NUAL_LENGTH - RTMP_VIDEO_DATA_WRONG_BYTES, m_fp);
	write_u32(tag->taglength - RTMP_BUFFER_FAKE_NUAL_LENGTH - RTMP_VIDEO_DATA_WRONG_BYTES);
	fflush(m_fp);

	return 0;
}

int CFlvParser::Close(void)
{
	this->destroy();
	return 0;
}

long CFlvParser::GetFileSize(void)
{
	return m_file_size;
}

int CFlvParser::read_u8(int* u8)
{
	if (fread(u8, 1, 1, m_fp) != 1) {
		return 0;
	}

	return 1;
}

int CFlvParser::read_u16(int* u16)
{
	if (fread(u16, 2, 1, m_fp) != 1) {
		return 0;
	}

	*u16 = HTON16(*u16);
	return 1;
}

int CFlvParser::read_u24(int* u24)
{
	if (fread(u24, 3, 1, m_fp) != 1) {
		return 0;
	}

	*u24 = HTON24(*u24);
	return 1;
}

int CFlvParser::read_u32(int* u32)
{
	if (fread(u32, 4, 1, m_fp) != 1) {
		return 0;
	}

	*u32 = HTON32(*u32);
	return 1;
}

int CFlvParser::peek_u8(int* u8)
{
	if (fread(u8, 1, 1, m_fp) != 1) {
		return 0;
	}

	fseek(m_fp, -1, SEEK_CUR);
	return 1;
}

int CFlvParser::read_utime(int* utime)
{
	if (fread(utime, 4, 1, m_fp) != 1) {
		return 0;
	}

	*utime = HTONTIME(*utime);
	return 1;
}

int CFlvParser::write_u8(int u8)
{
	if (fwrite(&u8, 1, 1, m_fp) != 1) {
		return 0;
	}

	return 1;
}
int CFlvParser::write_u16(int u16)
{
	u16 = HTON16(u16);
	if (fwrite(&u16, 2, 1, m_fp) != 1) {
		return 0;
	}

	return 1;
}
int CFlvParser::write_u24(int u24)
{
	u24 = HTON24(u24);
	if (fwrite(&u24, 3, 1, m_fp) != 1) {
		return 0;
	}

	return 1;
}
int CFlvParser::write_u32(int u32)
{
	u32 = HTON32(u32);
	if (fwrite(&u32, 4, 1, m_fp) != 1) {
		return 0;
	}

	return 1;
}
int CFlvParser::write_utime(int utime)
{
	utime = HTONTIME(utime);
	if (fwrite(&utime, 4, 1, m_fp) != 1) {
		return 0;
	}

	return 1;
}

void CFlvParser::destroy()
{
	if (m_fp) {
		fclose(m_fp);
		m_fp = NULL;
	}

	if (m_current_tag) {
		free(m_current_tag->buffer);
		free(m_current_tag);
		m_current_tag = NULL;
	}
}

void CFlvParser::parser_metadata(void)
{
	return;
}

void CFlvParser::parser_audio_tag_data(void)
{
	return;
}

/**
* ------------------------------------------------------------------------------------------
* Frame Type(4 bit) |  CodeID(4 bit) |  AVCPackettype(1 byte) if CodeID=7  |  Composition
* ------------------------------------------------------------------------------------------
* time(cont)  (3 byte)  if CodeID=7  |  Data   |
* ----------------------------------------------------------------------
**/
void CFlvParser::parser_video_tag_data(void)
{
	if (!m_current_tag) {
		ALOGE("current flv tag is null.");
		return;
	}
	if (m_current_tag->type != RTMP_PACKET_TYPE_VIDEO) {
		ALOGE("current flv tag not video tag.");
		return;
	}

	m_current_tag->code_type	= (m_current_tag->buffer)[0] & 0x0f;
	m_current_tag->frame_type	= ((m_current_tag->buffer)[0] >> 4) & 0x0f;
	m_current_tag->packet_type	= (m_current_tag->buffer)[1];

	int con_time = 0;
	char* p = (char*)&con_time;
	p[0] = m_current_tag->buffer[4];//¾°Ñô4ÂëÁ÷²ð·Ö
	m_current_tag->composition_time = con_time;

	//ALOGE("type:%d,datalength:%6d,timestamp:%6d,streamid:%6d,taglength:%6d,frame_type:%d,code_type:%d,packet_type:%d,cam_seq:%d\n",
	//	m_current_tag->type,m_current_tag->datalength,m_current_tag->timestamp,m_current_tag->streamid,
	//	m_current_tag->taglength,m_current_tag->frame_type,m_current_tag->code_type,m_current_tag->packet_type,
	//	m_current_tag->composition_time);
	return;
}
