#ifndef __GEA_FILESYSTEM_WIN32_H__
#define __GEA_FILESYSTEM_WIN32_H__

#include <windows.h>
#include <strsafe.h>
#include <assert.h>

#include <stdio.h>
#include <iostream>

#include <gea/engine/system/memory.h>

namespace gea {
namespace fs {

//
enum FileAccessFlags {
    FILE_READ   = FILE_READ_DATA,
    FILE_WRITE  = FILE_WRITE_DATA,
    FILE_APPEND = FILE_APPEND_DATA,
    FILE_EXEC   = FILE_EXECUTE,

    FILE_READ_ATTR   = FILE_READ_ATTRIBUTES,
    FILE_WRITE_ATTR  = FILE_WRITE_ATTRIBUTES,
    FILE_READ_XATTR  = FILE_READ_EA,
    FILE_WRITE_XATTR = FILE_WRITE_EA,

    FILE_ALL = FILE_ALL_ACCESS,
};

enum DirectoryAccessFlags {
    DIR_READ     = FILE_LIST_DIRECTORY,
    DIR_ADD_FILE = FILE_ADD_FILE,
    DIR_ADD_DIR  = FILE_ADD_SUBDIRECTORY,

    DIR_TRAVERSE = FILE_TRAVERSE,
    DIR_DELETE   = FILE_DELETE_CHILD,

    DIR_READ_ATTR   = FILE_READ_ATTRIBUTES,
    DIR_WRITE_ATTR  = FILE_WRITE_ATTRIBUTES,
    DIR_READ_XATTR  = FILE_READ_EA,
    DIR_WRITE_XATTR = FILE_WRITE_EA,

    DIR_ALL = FILE_ALL_ACCESS,
};


/*
 r = FILE_READ_DATA
 w = FILE_WRITE_DATA
 a = FILE_APPEND_DATA
 e = FILE_EXECUTE
*/
static const uint32_t read_access_mask_lookup['z'-'a'+1] = { 0 };

uint32_t access_mask(const char* str_mask, const uint32_t* lookup, uint32_t additional) {
    uint32_t agg_mask = 0;

    for (char c; (c = *str_mask) != NULL; ++str_mask ) {
        c -= 'a';
        agg_mask |= (c <= 'z'-'a') ? lookup[c] : 0;
    }
    return agg_mask | additional;
}







// asynchroeous file system functions
namespace async {

class file {
public:
    file() : handle(INVALID_HANDLE_VALUE), in_queue(false) {
        mem::zero_memory( &overlapped, sizeof(overlapped) );
        overlapped.hEvent = CreateEvent(NULL, true, false, NULL);
    }
    HANDLE     handle;
    OVERLAPPED overlapped;
    bool in_queue;
};

VOID CALLBACK async_read_cb(
  __in     DWORD dwErrorCode,
  __in     DWORD dwNumberOfBytesTransfered,
  __inout  LPOVERLAPPED lpOverlapped)
{

}

bool open_file(const LPCWSTR name, file& f) {
    assert(name != NULL);

    HANDLE new_handle;
    new_handle = CreateFile( name, FILE_READ_DATA, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL );

    if (new_handle != INVALID_HANDLE_VALUE) {
        f.handle = new_handle;
    }

    return new_handle != INVALID_HANDLE_VALUE;
}

bool read_file(file& f, void* buffer, uint32_t bytes, uint32_t offset = 0) {

    if (offset != 0) {
        f.overlapped.Offset = offset;
        f.overlapped.OffsetHigh = 0;
    }

    bool res = ReadFileEx( f.handle, buffer, (DWORD) bytes, &f.overlapped, NULL ) != 0;
    if (!res) {
        int error = GetLastError();
        if (error == ERROR_IO_PENDING)
            f.in_queue = true;
    }
    return res || f.in_queue;
}

void wait(file& f) {
    if (f.in_queue) {
        while (HasOverlappedIoCompleted( &f.overlapped ) );
        f.in_queue = false;
    }
}

} // namespace async //


} // namespace fs //

void ErrorExit(LPTSTR lpszFunction) 
{ 
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"),
        lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw); 
}

} // namespace gea //

#endif // __GEA_FILESYSTEM_WIN32_H__ //
