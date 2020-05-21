/**
* Copy from SRS
* data: 2017/11/14
*/

#ifndef _TCS_FILE_H_
#define _TCS_FILE_H_

#include <string>
#include "Platform.h"

#ifndef _WIN32
#include <sys/uio.h>
#endif

/**
* file writer, to write to file.
*/
class FileWriter
{
public:
    FileWriter();
    virtual ~FileWriter();

public:
    /**
     * open file writer, in truncate mode.
     * @param p a string indicates the path of file to open.
     */
    virtual int Open(std::string p);
    /**
     * open file writer, in append mode.
     * @param p a string indicates the path of file to open.
     */
    virtual int OpenAppend(std::string p);
    /**
     * close current writer.
     * @remark user can reopen again.
     */
    virtual void Close();

public:
    virtual bool IsOpen();
    virtual void Lseek(int64_t offset);
    virtual int64_t Tellg();

public:
    /**
    * write to file.
    * @param pnwrite the output nb_write, NULL to ignore.
    */
    virtual int Write(void* buf, size_t count, ssize_t* pnwrite);
    /**
     * for the HTTP FLV, to writev to improve performance.
     */
    virtual int Writev(iovec* iov, int iovcnt, ssize_t* pnwrite);

private:
	std::string m_path;
	int m_fd;
};

/**
* file reader, to read from file.
*/
class FileReader
{
public:
    FileReader();
    virtual ~FileReader();

public:
    /**
     * open file reader.
     * @param p a string indicates the path of file to open.
     */
    virtual int Open(std::string p);
    /**
     * close current reader.
     * @remark user can reopen again.
     */
    virtual void Close();

public:
    virtual bool IsOpen();
    virtual int64_t Tellg();
    virtual void Skip(int64_t size);
    virtual int64_t Lseek(int64_t offset);
    virtual int64_t FileSize();

public:
    /**
    * read from file.
    * @param pnread the output nb_read, NULL to ignore.
    */
    virtual int Read(void* buf, size_t count, ssize_t* pnread);

private:
	std::string m_path;
	int m_fd;
};

#endif
