#ifndef CRT_LOG_H
#define CRT_LOG_H

#include "crt_syscall.h"
#include "printf/printf.h"

#define LINE_PS     "> "
#define NEWLINE     "\n"

void _putchar(char character) {
    _write(1, &character, 1);
}

#define LOG(message, args...) printf(LINE_PS message NEWLINE, ## args)

#endif
