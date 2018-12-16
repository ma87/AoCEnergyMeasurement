#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

static int scores[30 << 20];
static int length;
#define INPUT  330121

static inline int recipe_check_pattern(int offset, int pattern)
{
    if (pattern == 0) {
        return 1;
    }
    if (scores[offset] == pattern % 10) {
        return recipe_check_pattern(offset - 1, pattern / 10);
    }
    return 0;
}

static int part2_found;
static int part1_found;

static inline void recipe_add(int score)
{
    scores[length++] = score;

    if (length > 6 && !part2_found) {
        if (recipe_check_pattern(length - 1, INPUT)) {
            printf("part2: %d\n", length - 6);
            part2_found = 1;
            if (part1_found) {
                exit(0);
            }
        }
    }
    if (length >= INPUT + 10 && !part1_found) {
        printf("part1: ");
        for (int i = 0; i < 10; i++) {
            printf("%d", scores[length - (10 - i)]);
        }
        printf("\n");
        part1_found = 1;
        if (part2_found) {
            exit(0);
        }
    }
}

int main(int argc, char **argv)
{
    int elf1, elf2;

    scores[0] = 3;
    scores[1] = 7;
    length = 2;

    elf1 = 0;
    elf2 = 1;

    for (;;) {
        int combined = scores[elf1] + scores[elf2];

        if (combined >= 10) {
            recipe_add(combined / 10);
        }

        recipe_add(combined % 10);

        elf1 = (elf1 + scores[elf1] + 1) % length;
        elf2 = (elf2 + scores[elf2] + 1) % length;
    }

    return 0;
}
