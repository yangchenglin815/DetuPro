#include "MyMd5.h"
#include <QDebug>

#define  PTS_LEN 32768

MyMd5::MyMd5()
{
} 


MyMd5::~MyMd5()
{
}

void MyMd5::WriteMd5FromPts(QString pts_path, QString md5_path)
{
	QFile temp(md5_path);
	if (temp.exists())
	{
		temp.remove();
	}
	FILE* pat_pts = fopen(pts_path.toLocal8Bit(), "rb");
	unsigned char pts_data[PTS_LEN];
	memset(&pts_data, 0, PTS_LEN);
	int pts_length;
	if (pat_pts)
	{
		fseek(pat_pts, 0, SEEK_END);
		pts_length = ftell(pat_pts);
		fseek(pat_pts, 0, SEEK_SET);
		int sts = fread(pts_data, 1, pts_length, pat_pts);
		if (sts == 0)
		{
			fclose(pat_pts);
			//return NULL;
		}
	}
	fclose(pat_pts);

	//加密后字符串
	unsigned char decrypt[16];
	MD5_CTX md5;
	MD5Init(&md5);
	MD5Update(&md5, pts_data, pts_length);
	MD5Final(&md5, decrypt);

	FILE* stream;
	for (int i = 0; i < 16; i++)
	{
		qDebug("%02x", decrypt[i]);
		stream = fopen(md5_path.toLocal8Bit(), "ab+");
		fseek(stream, 0, SEEK_END);
		fprintf(stream, "%02x", decrypt[i]);					//以16进制的方式输出数据15到文本1.txt当中
		fclose(stream);
	}
}

void MyMd5::WriteMd5FromMemory(unsigned char* source_md5, QString md5_path)
{
	//保存md5校验文件
	FILE* md5_txt = fopen(md5_path.toLocal8Bit(), "wb+");
	fwrite(source_md5, 1, strlen((char *)source_md5), md5_txt);
	fclose(md5_txt);
}

unsigned char* MyMd5::GetMd5FromPts(QString pts_path)
{
	FILE* pat_pts = fopen(pts_path.toLocal8Bit(), "rb");
	unsigned char *pts_data = NULL;
	int pts_length;
	if (pat_pts)
	{
		fseek(pat_pts, 0, SEEK_END);
		pts_length = ftell(pat_pts);
		fseek(pat_pts, 0, SEEK_SET);
		pts_data = (unsigned char *)malloc(sizeof(char)*pts_length);
		int sts = fread(pts_data, 1, pts_length, pat_pts);
		if (sts == 0)
		{
			return NULL;
		}
	}
	fclose(pat_pts);

	//加密后字符串
	unsigned char decrypt[16];
	MD5_CTX md5;
	MD5Init(&md5);
	MD5Update(&md5, pts_data, strlen((char *)pts_data));
	MD5Final(&md5, decrypt);

	return decrypt;

}

unsigned char* MyMd5::GetMd5FromTxt(QString md5_path)
{
	FILE* md5_txt = fopen(md5_path.toLocal8Bit(), "rb");
	unsigned char *pts_data = NULL;
	int pts_length;
	if (md5_txt)
	{
		fseek(md5_txt, 0, SEEK_END);
		pts_length = ftell(md5_txt);
		fseek(md5_txt, 0, SEEK_SET);
		pts_data = (unsigned char *)malloc(sizeof(char)*pts_length);
		int sts = fread(pts_data, 1, pts_length, md5_txt);
		if (sts == 0)
		{
			fclose(md5_txt);
			return NULL;
		}
	}
	fclose(md5_txt);
	return pts_data;
}

bool MyMd5::CheckMd5(QString pts_path, QString md5_path)
{
	 	FILE* md5_txt = fopen(md5_path.toLocal8Bit(), "r+");
	 	unsigned char *txt_data;
	 	int txt_length;
	 	if (md5_txt)
	 	{
	 		fseek(md5_txt, 0, SEEK_END);
			txt_length = ftell(md5_txt);
	 		fseek(md5_txt, 0, SEEK_SET);
			txt_data = (unsigned char *)malloc(sizeof(char)*txt_length);
	 	}
		else
		{
			return false;
		}


		FILE* pat_pts = fopen(pts_path.toLocal8Bit(), "rb");
		unsigned char pts_data[PTS_LEN];
		memset(&pts_data, 0, PTS_LEN);
		int pts_length;
		if (pat_pts)
		{
			fseek(pat_pts, 0, SEEK_END);
			pts_length = ftell(pat_pts);
			fseek(pat_pts, 0, SEEK_SET);
			int sts = fread(pts_data, 1, pts_length, pat_pts);
			if (sts == 0)
			{
				fclose(md5_txt);
				fclose(pat_pts);
				return false;
			}
		}
		else
		{
			return false;
		}


		//加密后字符串
		unsigned char decrypt[16];
		MD5_CTX md5;
		MD5Init(&md5);
		MD5Update(&md5, pts_data, strlen((char *)pts_data));
		MD5Final(&md5, decrypt);

		for (int i = 0; i<16; i++)
		{
			fscanf(md5_txt, "%02x", (txt_data + i));
			std::string temp1 = std::to_string(txt_data[i]);
			std::string temp = std::to_string(decrypt[i]);
			if (temp1 != temp)
			{
				fclose(md5_txt);
				fclose(pat_pts);
				return false;
			}
		}


		fclose(md5_txt);
		fclose(pat_pts);
		return true;
}

