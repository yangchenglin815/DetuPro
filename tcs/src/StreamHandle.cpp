#include <assert.h>
#include <string.h>
#include "logging.h"
#include "StreamHandle.h"

CStreamHandle::CStreamHandle()
{
	m_ptr = NULL;
	m_buffer = NULL;
	m_buffer_size = 0;
}

CStreamHandle::~CStreamHandle()
{
	
}

int CStreamHandle::Initialize(char* buffer, int buffer_size)
{
	if (!buffer) {
		Log::Error("stream param bytes must not be NULL.");
		return -1;
	}

	if (buffer_size <= 0) {
		Log::Error("stream param size must be positive.");
		return -1;
	}

	m_buffer_size = buffer_size;
	m_buffer = m_ptr = buffer;

	return 0;
}

void CStreamHandle::Skip(int size)
{
	assert(require(size));

	m_ptr += size;
	return;
}

int CStreamHandle::Size(void)
{
	return m_buffer_size;
}

int CStreamHandle::CurrentPostion(void)
{
	return (int)(m_buffer - m_ptr);
}

unsigned char CStreamHandle::Read1Bytes(void)
{
	assert(require(1));

	return (unsigned char)*m_ptr++;
}

unsigned short CStreamHandle::Read2Bytes(void)
{
	assert(require(2));

	unsigned short value;
	char* pp = (char*)&value;
	pp[0] = *m_ptr++;
	pp[1] = *m_ptr++;

	return value;
}

unsigned int CStreamHandle::Read4Bytes(void)
{
	assert(require(4));

	unsigned int value = 0;
	char* pp = (char*)&value;
	pp[0] = *m_ptr++;
	pp[1] = *m_ptr++;
	pp[2] = *m_ptr++;
	pp[3] = *m_ptr++;

	return value;
}

void CStreamHandle::ReadBytes(char* data, int size)
{
	assert(require(size));

	memcpy(data, m_ptr, size);
	m_ptr += size;

	return;
}

void CStreamHandle::Write1Bytes(unsigned char value)
{
	assert(require(1));

	*m_ptr++ = value;

	return;
}

void CStreamHandle::Write2Bytes(unsigned short value)
{
	assert(require(2));

	char* pp = (char*)&value;
	*m_ptr++ = pp[0];
	*m_ptr++ = pp[1];

	return;
}

void CStreamHandle::Write4Bytes(unsigned int value)
{
	assert(require(4));

	char* pp = (char*)&value;
	*m_ptr++ = pp[0];
	*m_ptr++ = pp[1];
	*m_ptr++ = pp[2];
	*m_ptr++ = pp[3];

	return;
}

void CStreamHandle::WriteBytes(char* data, int size)
{
	assert(require(size));

	memcpy(m_ptr, data, size);
	m_ptr += size;

	return;
}

bool CStreamHandle::require(int required_size)
{
	assert(required_size >= 0);

	return required_size <= m_buffer_size - (m_ptr - m_buffer);
}
