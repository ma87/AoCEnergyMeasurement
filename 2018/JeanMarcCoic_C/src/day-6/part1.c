#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

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

typedef struct point_t {
    int x, y;
    int area;
    int is_infinite;
} point_t;

typedef struct location_t {
    int closest;
    int distance;
    int total_distance;
} location_t;

static point_t points[50];
#define SQUARE_SIZE  500
static location_t locations[SQUARE_SIZE * SQUARE_SIZE];

#define ORIG_X  100
#define ORIG_Y  100

static inline location_t *location_at(int x, int y)
{
    return &locations[(y + ORIG_Y) * SQUARE_SIZE + x + ORIG_X];
}

static inline int dist(int x1, int y1, int x2, int y2)
{
    return (x1 > x2 ? x1 - x2 : x2 - x1)
        +  (y1 > y2 ? y1 - y2 : y2 - y1);
}

//static char *codes = ". abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, char **argv)
{
    int fd = -1;
    struct stat st;
    char *parser = MAP_FAILED;
    char *parser_start, *parser_end;
    int point = 0;
    point_t *p = points;
    int max_point = 0;
    int max_area = 0;
    int part2_count = 0;

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
        p = &points[point++];

        p->x = atoi_p(parser, &parser);
        parser += strlen(", ");
        p->y = atoi_p(parser, &parser);
        parser += strlen("\n");
    }

    for (int i = 0; i < 50; i++) {
        p = &points[i];
        for (int x = -ORIG_X; x < SQUARE_SIZE - ORIG_X; x++) {
            for (int y = -ORIG_Y; y < SQUARE_SIZE - ORIG_Y; y++) {
                location_t *l = location_at(x, y);
                int d = dist(p->x, p->y, x, y);

                l->total_distance += d;

                if (l->closest == 0) {
                    l->closest = i + 1;
                    l->distance = d;
                } else if (l->closest == -1) {
                    if (d < l->distance) {
                        l->closest = i + 1;
                        l->distance = d;
                    }
                } else {
                    if (d == l->distance) {
                        l->closest = -1;
                    } else if (d < l->distance) {
                        l->closest = i + 1;
                        l->distance = d;
                    }
                }
            }
        }
    }

    for (int x = -ORIG_X; x < SQUARE_SIZE - ORIG_X; x++) {
        location_t *l = location_at(x, 0);

        if (l->closest > 0) {
            points[l->closest - 1].is_infinite = 1;
        }

        l = location_at(x, SQUARE_SIZE - ORIG_Y - 1);
        if (l->closest > 0) {
            points[l->closest - 1].is_infinite = 1;
        }

        l = location_at(0, x);
        if (l->closest > 0) {
            points[l->closest - 1].is_infinite = 1;
        }

        l = location_at(SQUARE_SIZE - ORIG_X - 1, x);
        if (l->closest > 0) {
            points[l->closest - 1].is_infinite = 1;
        }
    }

    for (int x = -ORIG_X; x < SQUARE_SIZE - ORIG_X; x++) {
        for (int y = -ORIG_Y; y < SQUARE_SIZE - ORIG_Y; y++) {
            location_t *l = location_at(x, y);
            point_t *p;

            if (l->closest > 0) {
                p = &points[l->closest - 1];
                p->area++;
            }

            if (l->total_distance < 10000) {
                part2_count++;
            }
        }
    }

    for (int i = 0; i < 50; i++) {
        p = &points[i];

        if (max_area < p->area && p->is_infinite == 0) {
            max_area = p->area;
            max_point = i;
        }
    }

    printf("part1: max_area = %d (point %d)\n", max_area, max_point);
    printf("part2: count = %d\n", part2_count);

    //for (int y = -ORIG_Y; y < SQUARE_SIZE - ORIG_Y; y++) {
    //    for (int x = -ORIG_X; x < SQUARE_SIZE - ORIG_X; x++) {
    //        location_t *l = location_at(x, y);
    //        printf("%c", codes[l->closest + 1]);
    //    }
    //    printf("\n");
    //}

    return 0;
}
