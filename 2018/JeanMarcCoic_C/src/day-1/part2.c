#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <inttypes.h>

#define BUFFER_SIZE  (2 << 20)

static uint32_t seen[2 * BUFFER_SIZE / 32];

static inline void mark_sum(int sum)
{
    uint32_t offset = 0, sub_offset;

    if (sum < 0) {
        offset = BUFFER_SIZE / 32;
        sum = -sum;
    }

    offset += sum / 32;
    sub_offset = sum % 32;

    if ((seen[offset] & (1 << sub_offset)) > 0) {
        printf("%d\n", sum);
        exit(0);
    }

    seen[offset] |= (1 << sub_offset);
}

int main(int argc, char **argv)
{
    int fd = -1;
    struct stat st;
    char *parser = MAP_FAILED;
    char *parser_start, *parser_end;
    int sum = 0;
    int sign = 1;
    int buf = 0, digit;

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

  again:
    while (parser < parser_end) {
        switch (*parser) {
          case '-':
            sign = -1;
            break;

          case '+':
            sign = 1;
            break;

          case '\n':
            sum += sign * buf;
            mark_sum(sum);
            sign = 1;
            buf = 0;
            break;

          default:
            digit = *parser - '0';
            buf = buf * 10 + digit;
            break;
        }
        parser++;
    }

    parser = parser_start;
    goto again;

    return 0;
}
