#ifndef CRT_STD_H
#define CRT_STD_H

#include <limits.h>
#include <stddef.h>

int strlen(char * str) {
    int n = 0;

    while (*str++)
        n++;

    return n;
}

int strncmp(const char * s1, const char * s2, size_t l) {
    for (size_t i=0; i<l && *s1 && *s2; i++)
        if (s1[i] != s2[i])
            return -1;

    return 0;
}

int strcmp(char * s1, char * s2) {
    int l1 = strlen(s1);
    int l2 = strlen(s2);

    if (l1 == l2 && !strncmp(s1, s2, l1))
        return 0;

    return -1;
}

void memcpy(void *dst, void *src, unsigned int len) {
    unsigned char * d = (unsigned char *) dst;
    unsigned char * s = (unsigned char *) src;

    while (len--)
        *d++ = *s++;
}

int memcmp(void * dst, void * src, unsigned int len) {
    unsigned char * d = (unsigned char *) dst;
    unsigned char * s = (unsigned char *) src;

    while (len-- > 0)
        if (*d++ != *s++)
            return 1;

    return 0;
}

void memset(void * dst, unsigned char c, unsigned int len) {
    unsigned char *p = (unsigned char *)dst;

    while (len--)
        *p++ = c;
}

int isspace(int c) {
    return c == ' ' || (unsigned)c - '\t' < 5;
}

int isdigit(int c) {
    return (unsigned)c - '0' < 10;
}

int isalpha(int c) {
    return ((unsigned)c | 32U) - 'a' < 26;
}

int isupper(int c)
{
    return (unsigned)c - 'A' < 26;
}

unsigned long strtoul(const char *nptr, char **endptr, int base) {
    const char* s = nptr;
    unsigned long acc;
    int c;
    unsigned long cutoff;
    int neg = 0;
    int any;
    int cutlim;

    do {
        c = *s++;
    } while(isspace(c));

    if (c == '-') {
        neg = 1;
        c = *s++;
    } else if (c == '+') {
        c = *s++;
    }

    if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
        c = s[1];
        s += 2;
        base = 16;
    } else if ((base == 0 || base == 2) && c == '0' && (*s == 'b' || *s == 'B')) {
        c = s[1];
        s += 2;
        base = 2;
    }

    if (base == 0) {
        base = c == '0' ? 8 : 10;
    }

    cutoff = (unsigned long)ULONG_MAX / (unsigned long)base;
    cutlim = (int)((unsigned long)ULONG_MAX % (unsigned long)base);

    for (acc = 0, any = 0;; c = *s++) {
        if (isdigit(c)) {
            c -= '0';
        } else if (isalpha(c)) {
            c -= isupper(c) ? 'A' - 10 : 'a' - 10;
        } else {
            break;
        }

        if (c >= base) {
            break;
        }

        if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim)) {
            any = -1;
        } else {
            any = 1;
            acc *= (unsigned long)base;
            acc += (unsigned long)c;
        }
    }

    if (any < 0) {
        acc = ULONG_MAX;
    } else if (neg) {
        acc = -acc;
    }

    if (endptr != 0) {
        *endptr = (char*)(any ? s - 1 : nptr);
    }

    return acc;
}

#endif
