#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define  POT0_OFFSET  5
#define  NB_POTS  330 + POT0_OFFSET


int main(int argc, char **argv)
{
    int fd = -1;
    struct stat st;
    char *parser = MAP_FAILED;
    char *parser_start, *parser_end;
    char patterns[2][2][2][2][2];
    char pots1[NB_POTS + 1];
    char pots2[NB_POTS + 1];

    char *cur_pots = pots1, *next_pots = pots2;
    char *writer;
    char *reader;
    int part1_result = 0;
    uint64_t part2_result = 0;
    int nb_pots = 0;

    memset(pots1, '.', NB_POTS);
    pots1[NB_POTS] = '\0';
    memset(pots2, '.', NB_POTS);
    pots2[NB_POTS] = '\0';
    memset(patterns, '.', 2 * 2 * 2 * 2 * 2);

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

    parser += strlen("initial state: ");

    writer = cur_pots + POT0_OFFSET;
    while (*parser != '\n') {
        *writer++ = *parser++;
    }
    parser += strlen("\n\n");

    while (parser < parser_end) {
        char *pattern = parser;

        parser += strlen("##### => ");

#define PAT(pointer, i)  ((pointer)[i] == '#' ? 1 : 0)
#define IDX(i)  PAT(pattern, i)
        if (*parser++ == '#') {
            patterns[IDX(0)][IDX(1)][IDX(2)][IDX(3)][IDX(4)] = '#';
        }

        parser += strlen("\n");
    }

#define NB_GENERATIONS  200
    for (int i = 0; i < NB_GENERATIONS; i++) {
        writer = next_pots + 2;
        reader = cur_pots + 2;

        for (int p = 0; p <= NB_POTS - 5; p++) {
#define ID(i)  PAT(reader - 2, i)
            *writer++ = patterns[ID(0)][ID(1)][ID(2)][ID(3)][ID(4)];
            reader++;
        }
        if (cur_pots == pots1) {
            cur_pots = pots2;
            next_pots = pots1;
        } else {
            cur_pots = pots1;
            next_pots = pots2;
        }

        if (i == 19) {
            for (int j = 0; j < NB_POTS; j++) {
                if (cur_pots[j] == '#') {
                    part1_result += j - POT0_OFFSET;
                }
            }
        }
    }

    for (int j = 0; j < NB_POTS; j++) {
        if (cur_pots[j] == '#') {
            nb_pots++;
            part2_result += (j - POT0_OFFSET);
        }
    }

    printf("part1: %d\n", part1_result);
    printf("part2: %llu\n", part2_result + nb_pots * (50000000000ULL -
                                                     NB_GENERATIONS));

    return 0;
}
