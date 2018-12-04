#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <inttypes.h>

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

    printf("sum: %d\n", sum);

    return 0;
}
