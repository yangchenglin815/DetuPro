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

    if ((m_fd = ::open(p.c_str(), flags, mode)) < 0) {//'::'表示这个open是全局函数，也就是API接口，不是类中的open函数；
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

    if (::close(m_fd) < 0) {//'::'表示close函数是全局函数，也就是API接口函数，避免与该类中的close混淆
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
*  SEEK_SET: 从文件其实位置开始定位
*  SEEK_END: 从文件结尾处开始定位
*  SEEK_CUR: 从当前索引位置开始定位
*/
void FileWriter::Lseek(int64_t offset)
{
    ::lseek(m_fd, (off_t)offset, SEEK_SET);
}

//windwos下最好将lseek()换成_lseeki64(),_lseeki64支持超过2G的文件定位
//#define _FILE_OFFSET_BITS 64  the definition must be the first line in .cpp，需要使用64定位的时候，在cpp的第一行加宏定义
int64_t FileWriter::Tellg()
{
    return (int64_t)::lseek(m_fd, 0, SEEK_CUR);//lseek定位2G以上大文件有问题，超过2G的使用需要加宏编译
}

//写指定长度的数据到文件中
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

//写指定长度的数据到文件中
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


//读文件类
FileReader::FileReader()
{
    m_fd = -1;
}

FileReader::~FileReader()
{
    Close();
}

//以读的方式打开文件
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

    m_path = p;//类的私有成员变量

    return ret;
}

//关闭类
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

//判断是否为打开状态
bool FileReader::IsOpen()
{
    return m_fd > 0;
}

//返回当前的文件位置
int64_t FileReader::Tellg()
{
    return (int64_t)::lseek(m_fd, 0, SEEK_CUR);
}

//从当前位置开始，跳过size字节
void FileReader::Skip(int64_t size)
{
    ::lseek(m_fd, (off_t)size, SEEK_CUR);
}

//从当前位置，定位，偏移量为offset
int64_t FileReader::Lseek(int64_t offset)
{
    return (int64_t)::lseek(m_fd, (off_t)offset, SEEK_SET);
}

//返回文件大小
int64_t FileReader::FileSize()
{
    int64_t cur = Tellg();
    int64_t size = (int64_t)::lseek(m_fd, 0, SEEK_END);
    ::lseek(m_fd, (off_t)cur, SEEK_SET);
    return size;
}

//从文件中读取指定长度的数据
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
