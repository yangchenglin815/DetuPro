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
	unsigned int	nSequenceId;					// ֡���
	unsigned char   nImageFormatId;					// ͼ���ʽ
	unsigned short	nVideoHeight;					// ��Ƶ�߶�
	unsigned short	nVideoWidth;					// ��Ƶ���
	unsigned char	nFrameRate;						// ֡��
	unsigned short	nBitRate;						// ����
	unsigned char	nAudioSamplePerSec;				// ��Ƶ������
	unsigned char	nAudioBitPerSec;				// ��Ƶ�ֱ���
	unsigned char	nAudioFormatTag;				// ��Ƶ������ʽ
	unsigned char	nAudioChannels;					// ��Ƶͨ����

	unsigned int	nAbsoluteTimeStampHigh32;		// ����ʱ����ĸ�32λ
	unsigned int	nAbsoluteTimeStampLow32;		// ����ʱ����ĵ�32λ
	unsigned char	szReserver[2];					// Ԥ��
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
