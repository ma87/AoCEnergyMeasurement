#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

#define UNSAFE
#define BUFFER_SIZE  (2 << 20)

static uint8_t matrix[1000 * 1000];

static inline int get_offset(int x, int y)
{
    return y * 1000 + x;
}

static inline void mark_claim(int x0, int y0, int width, int height)
{
    for (int y = y0; y < y0 + height; y++) {
        for (int x = x0; x < x0 + width; x++) {
            int offset = get_offset(x, y);
            matrix[offset]++;
        }
    }
}

static inline int atoi_p(char *p, char **end)
{
    int res = 0;

    while (isdigit(*p)) {
        res = res * 10 + (*p - '0');
        p++;
    }

    *end = p;
    return res;
}

int main(int argc, char **argv)
{
    int fd = -1;
    struct stat st;
    char *parser = MAP_FAILED;
    char *parser_start, *parser_end;
    int count = 0;

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

    while (parser < parser_end) {
        //#24 @ 156,921: 18x17
        int claim = 0, x = 0, y = 0, width = 0, height = 0;

        // skip #
        parser++;
        claim = atoi_p(parser, &parser);

        // skip " @ "
        parser += 3;

        x = atoi_p(parser, &parser);
        // skip ","
        parser++;
        y = atoi_p(parser, &parser);

        // skip ": "
        parser += 2;
        width = atoi_p(parser, &parser);
        // skip "x"
        parser++;
        height = atoi_p(parser, &parser);

        // skip "\n"
        parser++;

        mark_claim(x, y, width, height);
    }

    for (int x = 0; x < 1000; x++) {
        for (int y = 0; y < 1000; y++) {
            if (matrix[get_offset(x, y)] > 1) {
                count++;
            }
        }
    }

    printf("count: %d\n", count);

    return 0;
}
