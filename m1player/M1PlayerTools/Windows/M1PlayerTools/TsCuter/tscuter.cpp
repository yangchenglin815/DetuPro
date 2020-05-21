#include "tscuter.h"
#include "logging.h"
#include <time.h>
#include <QFileDialog>

TsCuter::TsCuter(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_packet_buf = (char*)malloc(TS_PACKET_SIZE);
	memset(m_packet_buf, 0, TS_PACKET_SIZE);
	m_private_data = (ts_private_data*)malloc(sizeof(ts_private_data));
	memset(m_private_data, 0, sizeof(ts_private_data));

	connect(ui.openFileButton, SIGNAL(clicked()), this, SLOT(onOpenFileButtonClick()));
	connect(ui.StartButton, SIGNAL(clicked()), this, SLOT(onStartButtonClick()));
}

TsCuter::~TsCuter()
{
	if (m_packet_buf) {
		free(m_packet_buf);
		m_packet_buf = NULL;
	}
	if (m_private_data) {
		free(m_private_data);
		m_private_data = NULL;
	}
}


void TsCuter::onOpenFileButtonClick()
{
	m_file_path = QFileDialog::getOpenFileName(this, tr("Open Video"), tr("Image Files"));
	ui.lineEdit_filename->setText(m_file_path);
}

void TsCuter::onStartButtonClick()
{
	int width = ui.lineEdit_width->text().toInt();
	int height = ui.lineEdit_height->text().toInt();
	int fps = ui.lineEdit_fps->text().toInt();
	int position = ui.lineEdit_pos->text().toInt();

	std::string input_path = m_file_path.toLocal8Bit().data();
	std::string output_path = input_path;
	output_path.replace(input_path.size() - 3, input_path.size(), "_out.ts");

	FILE* ts_reader = fopen(input_path.c_str(), "rb+");
	FILE* ts_writer = fopen(output_path.c_str(), "wb+");

	int read_length = 0;
	bool write_tag = false;
	while ((read_length = fread(m_packet_buf, 1, TS_PACKET_SIZE, ts_reader)) == TS_PACKET_SIZE) {
		if ((m_packet_buf[PRIVATE_DATA_POSITION + 0] == (width & 0x00ff)) && (m_packet_buf[PRIVATE_DATA_POSITION + 1] == (height >> 8 & 0x00ff)) &&
			(m_packet_buf[PRIVATE_DATA_POSITION + 2] == (height & 0x00ff)) && (m_packet_buf[PRIVATE_DATA_POSITION + 3] == (width >> 8 & 0x00ff)) &&
			(m_packet_buf[PRIVATE_DATA_POSITION + 4] == fps)) {
			m_read_ptr = m_packet_buf;

			skip(TS_HEADER_LENGTH);

			m_private_data->nSize = read_2bytes();
			m_private_data->nSequenceId = read_4bytes();
			m_private_data->nImageFormatId = read_1bytes();
			m_private_data->nVideoHeight = read_2bytes();
			m_private_data->nVideoWidth = read_2bytes();
			m_private_data->nFrameRate = read_1bytes();
			m_private_data->nBitRate = read_2bytes();
			m_private_data->nAudioSamplePerSec = read_1bytes();
			m_private_data->nAudioBitPerSec = read_1bytes();
			m_private_data->nAudioFormatTag = read_1bytes();
			m_private_data->nAudioChannels = read_1bytes();
			m_private_data->nAbsoluteTimeStampLow32 = read_4bytes();
			m_private_data->nAbsoluteTimeStampHigh32 = read_4bytes();

			double time_stamp = read_timestamp((char*)&m_private_data->nAbsoluteTimeStampHigh32, (char*)&m_private_data->nAbsoluteTimeStampLow32);

			time_t ts;
			struct tm *pdata;
			ts = (time_t)time_stamp;
			pdata = gmtime(&ts);
			char timestring[80];
			strftime(timestring, 80, "%Y-%m-%d %H:%M:%S", pdata);

			Log::Info("seq:%d, width:%d, height:%d, fps:%d, bitrate:%d, timestamp:%f, data:%s", m_private_data->nSequenceId,
				m_private_data->nVideoWidth, m_private_data->nVideoHeight, m_private_data->nFrameRate, m_private_data->nBitRate, time_stamp, timestring);

			if (time_stamp > m_cuter_position) {
				write_tag = true;
			}
		}

		if (write_tag) {
			fwrite(m_packet_buf, 1, TS_PACKET_SIZE, ts_writer);
			fflush(ts_writer);
		}
	}

	if (ts_reader) {
		fclose(ts_reader);
		ts_reader = NULL;
	}
	if (ts_writer) {
		fclose(ts_writer);
		ts_writer = NULL;
	}
}

unsigned char TsCuter::read_1bytes(void)
{
	return (unsigned char)*m_read_ptr++;
}

unsigned short TsCuter::read_2bytes(void)
{
	unsigned short value;
	char* pp = (char*)&value;
	pp[0] = *m_read_ptr++;
	pp[1] = *m_read_ptr++;

	return value;
}

unsigned int TsCuter::read_4bytes(void)
{
	unsigned int value = 0;
	char* pp = (char*)&value;
	pp[0] = *m_read_ptr++;
	pp[1] = *m_read_ptr++;
	pp[2] = *m_read_ptr++;
	pp[3] = *m_read_ptr++;

	return value;
}

double TsCuter::read_timestamp(char* high_32, char* low_32)
{
	unsigned __int64 value = 0;
	char* pp = (char*)&value;
	pp[7] = high_32[3];
	pp[6] = high_32[2];
	pp[5] = high_32[1];
	pp[4] = high_32[0];

	pp[3] = low_32[3];
	pp[2] = low_32[2];
	pp[1] = low_32[1];
	pp[0] = low_32[0];

	double ret = (double)(value / 1000000.0);
	return ret;
}

void TsCuter::skip(int size)
{
	m_read_ptr += size;
	return;
}
