/*
 * Distributed under the OSI-approved Apache License, Version 2.0.  See
 * accompanying file Copyright.txt for details.
 *
 * FileDescriptor.h wrapper of POSIX library functions for file I/O
 *
 *  Created on: Oct 6, 2016
 *      Author: William F Godoy godoywf@ornl.gov
 */

#ifndef ADIOS2_TOOLKIT_TRANSPORT_FILE_FILEDESCRIPTOR_H_
#define ADIOS2_TOOLKIT_TRANSPORT_FILE_FILEDESCRIPTOR_H_

#include <future> //std::async, std::future

#include "adios2/common/ADIOSConfig.h"
#include "adios2/toolkit/transport/Transport.h"

namespace adios2
{
namespace helper
{
class Comm;
}
namespace transport
{

/** File descriptor transport using the POSIX IO library */
class FilePOSIX : public Transport
{

public:
    FilePOSIX(helper::Comm const &comm);

    ~FilePOSIX();

    void Open(const std::string &name, const Mode openMode,
              const bool async = false) final;

    void OpenChain(const std::string &name, Mode openMode,
                   const helper::Comm &chainComm,
                   const bool async = false) final;

    void Write(const char *buffer, size_t size, size_t start = MaxSizeT) final;

    void Read(char *buffer, size_t size, size_t start = MaxSizeT) final;

    size_t GetSize() final;

    /** Does nothing, each write is supposed to flush */
    void Flush() final;

    void Close() final;

    void Delete() final;

    void SeekToEnd() final;

    void SeekToBegin() final;

private:
    /** POSIX file handle returned by Open */
    int m_FileDescriptor = -1;
    int m_Errno = 0;
    bool m_IsOpening = false;
    std::future<int> m_OpenFuture;

    /**
     * Check if m_FileDescriptor is -1 after an operation
     * @param hint exception message
     */
    void CheckFile(const std::string hint) const;
    void WaitForOpen();
    std::string SysErrMsg() const;
};

} // end namespace transport
} // end namespace adios2

#endif /* ADIOS2_TRANSPORT_FILE_FILEDESCRIPTOR_H_ */
