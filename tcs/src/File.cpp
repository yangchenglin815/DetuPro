#include "File.h"
#include "Error.h"

#ifndef _WIN32
#include <unistd.h>
#include <sys/uio.h>
#endif

#include <fcntl.h>
#include <sstream>


FileWriter::FileWriter()
{
    m_fd = -1;
}

FileWriter::~FileWriter()
{
    Close();
}

//open file writer, in truncate mode
int FileWriter::Open(std::string p)
{
    int ret = ERROR_SUCCESS;

    if (m_fd > 0) {
        ret = ERROR_SYSTEM_FILE_ALREADY_OPENED;
		printf("file %s already opened. ret=%d.\n", m_path.c_str(), ret);
        return ret;
    }

    int flags = O_CREAT|O_WRONLY|O_TRUNC;
    mode_t mode = S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH;

    if ((m_fd = ::open(p.c_str(), flags, mode)) < 0) {//'::'��ʾ���open��ȫ�ֺ�����Ҳ����API�ӿڣ��������е�open������
        ret = ERROR_SYSTEM_FILE_OPENE;
		printf("open file %s failed. ret=%d.\n", p.c_str(), ret);
        return ret;
    }

    m_path = p;

    return ret;
}

//open file writer, in append mode
int FileWriter::OpenAppend(std::string p)
{
    int ret = ERROR_SUCCESS;

    if (m_fd > 0) {
        ret = ERROR_SYSTEM_FILE_ALREADY_OPENED;
		printf("file %s already opened. ret=%d.\n", m_path.c_str(), ret);
        return ret;
    }

    int flags = O_APPEND|O_WRONLY;
    mode_t mode = S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH;

    if ((m_fd = ::open(p.c_str(), flags, mode)) < 0) {
        ret = ERROR_SYSTEM_FILE_OPENE;
		printf("open file %s failed. ret=%d.\n", p.c_str(), ret);
        return ret;
    }

    m_path = p;

    return ret;
}

//close file writer
void FileWriter::Close()
{
    int ret = ERROR_SUCCESS;

    if (m_fd < 0) {
        return;
    }

    if (::close(m_fd) < 0) {//'::'��ʾclose������ȫ�ֺ�����Ҳ����API�ӿں���������������е�close����
        ret = ERROR_SYSTEM_FILE_CLOSE;
		printf("close file %s failed. ret=%d.\n", m_path.c_str(), ret);
        return;
    }
    m_fd = -1;

    return;
}

//whether is open
bool FileWriter::IsOpen()
{
    return m_fd > 0;
}

/**
*  SEEK_SET: ���ļ���ʵλ�ÿ�ʼ��λ
*  SEEK_END: ���ļ���β����ʼ��λ
*  SEEK_CUR: �ӵ�ǰ����λ�ÿ�ʼ��λ
*/
void FileWriter::Lseek(int64_t offset)
{
    ::lseek(m_fd, (off_t)offset, SEEK_SET);
}

//windwos����ý�lseek()����_lseeki64(),_lseeki64֧�ֳ���2G���ļ���λ
//#define _FILE_OFFSET_BITS 64  the definition must be the first line in .cpp����Ҫʹ��64��λ��ʱ����cpp�ĵ�һ�мӺ궨��
int64_t FileWriter::Tellg()
{
    return (int64_t)::lseek(m_fd, 0, SEEK_CUR);//lseek��λ2G���ϴ��ļ������⣬����2G��ʹ����Ҫ�Ӻ����
}

//дָ�����ȵ����ݵ��ļ���
int FileWriter::Write(void* buf, size_t count, ssize_t* pnwrite)
{
    int ret = ERROR_SUCCESS;

    ssize_t nwrite;
    // TODO: FIXME: use st_write.
    if ((nwrite = ::write(m_fd, buf, count)) < 0) {
        ret = ERROR_SYSTEM_FILE_WRITE;
		printf("write to file %s failed. ret=%d.\n", m_path.c_str(), ret);
        return ret;
    }

    if (pnwrite != NULL) {
        *pnwrite = nwrite;
    }

    return ret;
}

//дָ�����ȵ����ݵ��ļ���
int FileWriter::Writev(iovec* iov, int iovcnt, ssize_t* pnwrite)
{
    int ret = ERROR_SUCCESS;

    ssize_t nwrite = 0;
    for (int i = 0; i < iovcnt; i++) {
        iovec* piov = iov + i;
        ssize_t this_nwrite = 0;
        if ((ret = Write(piov->iov_base, piov->iov_len, &this_nwrite)) != ERROR_SUCCESS) {
            return ret;
        }
        nwrite += this_nwrite;
    }

    if (pnwrite) {
        *pnwrite = nwrite;
    }

    return ret;
}


//���ļ���
FileReader::FileReader()
{
    m_fd = -1;
}

FileReader::~FileReader()
{
    Close();
}

//�Զ��ķ�ʽ���ļ�
int FileReader::Open(std::string p)
{
    int ret = ERROR_SUCCESS;

    if (m_fd > 0) {
        ret = ERROR_SYSTEM_FILE_ALREADY_OPENED;
		printf("file %s already opened. ret=%d.\n", m_path.c_str(), ret);
        return ret;
    }

    if ((m_fd = ::open(p.c_str(), O_RDONLY)) < 0) {
        ret = ERROR_SYSTEM_FILE_OPENE;
		printf("open file %s failed. ret=%d.\n", p.c_str(), ret);
        return ret;
    }

    m_path = p;//���˽�г�Ա����

    return ret;
}

//�ر���
void FileReader::Close()
{
    int ret = ERROR_SUCCESS;

    if (m_fd < 0) {
        return;
    }

    if (::close(m_fd) < 0) {
        ret = ERROR_SYSTEM_FILE_CLOSE;
		printf("close file %s failed. ret=%d.\n", m_path.c_str(), ret);
        return;
    }
    m_fd = -1;

    return;
}

//�ж��Ƿ�Ϊ��״̬
bool FileReader::IsOpen()
{
    return m_fd > 0;
}

//���ص�ǰ���ļ�λ��
int64_t FileReader::Tellg()
{
    return (int64_t)::lseek(m_fd, 0, SEEK_CUR);
}

//�ӵ�ǰλ�ÿ�ʼ������size�ֽ�
void FileReader::Skip(int64_t size)
{
    ::lseek(m_fd, (off_t)size, SEEK_CUR);
}

//�ӵ�ǰλ�ã���λ��ƫ����Ϊoffset
int64_t FileReader::Lseek(int64_t offset)
{
    return (int64_t)::lseek(m_fd, (off_t)offset, SEEK_SET);
}

//�����ļ���С
int64_t FileReader::FileSize()
{
    int64_t cur = Tellg();
    int64_t size = (int64_t)::lseek(m_fd, 0, SEEK_END);
    ::lseek(m_fd, (off_t)cur, SEEK_SET);
    return size;
}

//���ļ��ж�ȡָ�����ȵ�����
int FileReader::Read(void* buf, size_t count, ssize_t* pnread)
{
    int ret = ERROR_SUCCESS;

    ssize_t nread;
    // TODO: FIXME: use st_read.
    if ((nread = ::read(m_fd, buf, count)) < 0) {
        ret = ERROR_SYSTEM_FILE_READ;
		printf("read from file %s failed. ret=%d.\n", m_path.c_str(), ret);
        return ret;
    }

    if (nread == 0) {
        ret = ERROR_SYSTEM_FILE_EOF;
        return ret;
    }

    if (pnread != NULL) {
        *pnread = nread;
    }

    return ret;
}
