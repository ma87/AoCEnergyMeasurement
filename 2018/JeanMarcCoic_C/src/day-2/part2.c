#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#define UNSAFE
#define BUFFER_SIZE  (2 << 20)

static inline void compare_ids(char *s1, char *s2)
{
    int nb_diff = 0;
    char *start = s1, *diff = NULL;
    char buf[30], *writer;

    for (;*s1 != '\n'; s1++, s2++) {
        if (*s1 != *s2) {
            diff = s1;
            nb_diff++;
        }
    }
    if (nb_diff == 1) {
        writer = buf;
        while (*start != '\n') {
            if (start == diff) {
                start++;
                continue;
            }
            *writer++ = *start++;
        }
        *writer = '\0';

        printf("found id: %s\n", buf);
        exit(0);
    }
}

int main(int argc, char **argv)
{
    int fd = -1;
    struct stat st;
    char *parser = MAP_FAILED;
    char *parser_start, *parser_end;

    if ((fd = open("input", O_RDONLY)) < 0 || fstat(fd, &st) < 0) {
        printf("failed to open input: %m\n");
        return 1;
    }
    if (!st.st_size) {
        printf("input is empty\n");
        return 1;
    }

    parser = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (parser == MAP_FAILED) {
        printf("failed to mmap input: %m\n");
        return 1;
    }
    parser_start = parser;
    parser_end = parser + st.st_size;

    for (int i = 0; i < 250; i++) {
        char *s1, *s2;

        s1 = parser + (27 * i);
        for (int j = i + 1; j < 250; j++) {
            s2 = parser + (27 * j);

            compare_ids(s1, s2);
        }
    }

    printf("not found\n");
    return 0;
}
