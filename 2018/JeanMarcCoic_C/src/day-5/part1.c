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

static inline int polarity_test(int c1, int c2)
{
    int diff = c1 - c2;

    if (diff == ('A' - 'a')) {
        return 1;
    }

    return diff == ('a' - 'A');
}

static inline int mmap_input(char **parser, char **parser_end)
{
    int fd = -1;
    struct stat st;

    if ((fd = open("input", O_RDONLY)) < 0 || fstat(fd, &st) < 0) {
        printf("failed to open input: %m\n");
        return 1;
    }
    if (!st.st_size) {
        printf("input is empty\n");
        return 1;
    }

    *parser = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (*parser == MAP_FAILED) {
        printf("failed to mmap input: %m\n");
        return 1;
    }
    *parser_end = *parser + st.st_size;
    return 0;
}

static inline int reduce_polymer(char *parser, char *parser_end,
                                 int del_char)
{
    char *parser_start;
    char *polymer_tail; /* last char of the polymer included */

    parser_start = parser;
    polymer_tail = parser;
    parser++;

    while (parser < parser_end) {
        if (*parser == '\n') {
            break;
        }

        if (*parser == del_char || *parser == (del_char + 'A' - 'a')) {
            parser++;
            continue;
        }

        if (polymer_tail - parser_start >= 0) {
            if (polarity_test(*polymer_tail, *parser)) {
                polymer_tail--;
                parser++;
                continue;
            }
        }

        polymer_tail++;
        *polymer_tail = *parser++;
    }

    return (int)(polymer_tail - parser_start + 1);
}

int main(int argc, char **argv)
{
    char *parser;
    char *parser_end;
    int length;
    int min_length;
    int min_char;

    if (mmap_input(&parser, &parser_end)) {
        exit(1);
    }

    length = reduce_polymer(parser, parser_end, '\0');

    printf("part1: polymer length: %d\n", length);

    min_length = length;
    min_char = '0';

    for (int c = 'a'; c <= 'z'; c++) {
        if (mmap_input(&parser, &parser_end)) {
            exit(1);
        }

        length = reduce_polymer(parser, parser_end, c);
        if (min_length > length) {
            min_length = length;
            min_char = c;
        }
    }

    printf("part2: min char: %c, min length: %d\n", min_char, min_length);

    return 0;
}
