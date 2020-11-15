#ifndef CRT_UTILS_H
#define CRT_UTILS_H

#include "crt_syscall.h"
#include <stdio.h>

long get_file_size(int fd) {
    long fs, r;
    char tmp[0x1000] = {};

    fs = _lseek(fd, 0, SEEK_END);

    if (fs > 0) {
        _lseek(fd, 0, SEEK_SET);
        return fs;
    }

    fs = 0;

    do
    {
        r = _read(fd, tmp, 0x1000);

        if (r < 0)
            return -1;
        else
            fs += r;
    } while(r > 0);

    _lseek(fd, 0, SEEK_SET);

    return fs;
}

#endif
