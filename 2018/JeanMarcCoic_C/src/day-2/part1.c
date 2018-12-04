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

int main(int argc, char **argv)
{
    int fd = -1;
    struct stat st;
    char *parser = MAP_FAILED;
    char *parser_start, *parser_end;
    uint8_t buf[30];
    int letter;
    int count_2 = 0, count_3 = 0;
    int flag_2, flag_3;

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
          case '\n':
            flag_2 = flag_3 = 0;
            for (int l = 0; l < 26; l++) {
                if (buf[l] == 2) {
                    flag_2 = 1;
                    continue;
                }
                if (buf[l] == 3) {
                    flag_3 = 1;
                    continue;
                }
            }
            count_2 += flag_2;
            count_3 += flag_3;
            memset(buf, 0, 30);
            break;

          default:
            letter = *parser - 'a';
            buf[letter] += 1;
            break;
        }
        parser++;
    }

    printf("count2: %d, count3: %d, checksum: %d\n", count_2, count_3, count_2 * count_3);

    return 0;
}
