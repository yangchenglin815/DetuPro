#ifndef _STREAM_HANDLE_H_
#define _STREAM_HANDLE_H_

class CStreamHandle
{
public:
	CStreamHandle();
	~CStreamHandle();

public:
	int				Initialize(char* buffer, int buffer_size);
	void			Skip(int size);
	int				Size(void);
	int				CurrentPostion(void);

	unsigned char	Read1Bytes(void);
	unsigned short	Read2Bytes(void);
	unsigned int	Read4Bytes(void);
	void			ReadBytes(char* data, int size);

	void			Write1Bytes(unsigned char value);
	void			Write2Bytes(unsigned short value);
	void			Write4Bytes(unsigned int value);
	void			WriteBytes(char* data, int size);

private:
	bool			require(int required_size);

private:
	char*	m_ptr;
	char*	m_buffer;
	int		m_buffer_size;
};

#endif
