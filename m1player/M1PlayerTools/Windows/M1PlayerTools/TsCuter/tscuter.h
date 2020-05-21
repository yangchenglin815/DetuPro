#ifndef TSCUTER_H
#define TSCUTER_H

#include <QtWidgets/QMainWindow>
#include "ui_tscuter.h"

#include <string>
#include <stdio.h>
#include <stdlib.h>

#define TS_PACKET_SIZE 188
#define TS_HEADER_LENGTH 13
#define PRIVATE_DATA_POSITION 20

typedef struct
{
	unsigned short	nSize;
	unsigned int	nSequenceId;					// 帧序号
	unsigned char   nImageFormatId;					// 图像格式
	unsigned short	nVideoHeight;					// 视频高度
	unsigned short	nVideoWidth;					// 视频宽度
	unsigned char	nFrameRate;						// 帧率
	unsigned short	nBitRate;						// 码率
	unsigned char	nAudioSamplePerSec;				// 音频采样率
	unsigned char	nAudioBitPerSec;				// 音频分辨率
	unsigned char	nAudioFormatTag;				// 音频采样格式
	unsigned char	nAudioChannels;					// 音频通道数

	unsigned int	nAbsoluteTimeStampHigh32;		// 绝对时间戳的高32位
	unsigned int	nAbsoluteTimeStampLow32;		// 绝对时间戳的低32位
	unsigned char	szReserver[2];					// 预留
}ts_private_data;

class TsCuter : public QMainWindow
{
	Q_OBJECT

public:
	TsCuter(QWidget *parent = 0);
	~TsCuter();

public slots:
	void onOpenFileButtonClick();
	void onStartButtonClick();

private:
	int parser_private_data(void);
	unsigned char read_1bytes(void);
	unsigned short read_2bytes(void);
	unsigned int read_4bytes(void);
	double read_timestamp(char* high_32, char* low_32);
	void skip(int size);

private:
	Ui::TsCuterClass ui;

private:
	QString m_file_path;

	FILE*			m_fp;
	FILE*			m_ts_writer;
	std::string		m_ts_out_path;
	unsigned long	m_cuter_position;
	bool			m_write_tag;

	char*				m_packet_buf;
	char*				m_read_ptr;
	ts_private_data*	m_private_data;

	int m_width;
	int m_height;
	int m_fps;
};

#endif // TSCUTER_H
