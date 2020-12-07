#ifndef CRT_UTILS_H
#define CRT_UTILS_H

#include "crt_syscall.h"
#include "crt_memory.h"
#include <stdio.h>
#include <fcntl.h>

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

int read_file(char *path, char **ptr) {
    int fd = _open(path, O_RDONLY, 0);

    if (fd < 0) {
        return 0;
    }

    long file_size = get_file_size(fd);

    if (file_size <= 0) {
        _close(fd);
        return 0;
    }

    char *buffer = malloc(file_size);

    if (!buffer) {
        _close(fd);
        return 0;
    }

    memset(buffer, 0, file_size);

    if (_read(fd, buffer, file_size) != file_size) {
        free(buffer);
        _close(fd);
        return 0;
    }

    _close(fd);

    *ptr = buffer;

    return file_size;
}

#endif
