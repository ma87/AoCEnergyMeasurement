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

static inline int atoi_p(char *p, char **end)
{
    int res = 0;
    int sign = 1;

    while (*p == ' ') {
        p++;
    }

    if (*p == '-') {
        sign = -1;
        p++;
    }

    while (isdigit(*p)) {
        res = res * 10 + (*p - '0');
        p++;
    }

    *end = p;
    return sign * res;
}

typedef struct point_t {
    int x;
    int y;

    int vel_x;
    int vel_y;
} point_t;

#define MAX_POINTS  1000
static point_t points[MAX_POINTS];
static int nb_points;

static inline int compute_density(int time)
{
    int max_y = INT32_MIN, min_y = INT32_MAX;

    for (int i = 0; i < nb_points; i++) {
        point_t *p = &points[i];
        int new_y = p->y + p->vel_y * time;

        if (min_y > new_y) {
            min_y = new_y;
        }

        if (max_y < new_y) {
            max_y = new_y;
        }
    }

    return max_y - min_y;
}

static void print_points(int time)
{
    int max_y = INT32_MIN, min_y = INT32_MAX;
    int max_x = INT32_MIN, min_x = INT32_MAX;
    int size_x, size_y;
    char *output;

    for (int i = 0; i < nb_points; i++) {
        point_t *p = &points[i];
        int new_x = p->x + p->vel_x * time;
        int new_y = p->y + p->vel_y * time;

        if (min_y > new_y) {
            min_y = new_y;
        }

        if (max_y < new_y) {
            max_y = new_y;
        }

        if (min_x > new_x) {
            min_x = new_x;
        }

        if (max_x < new_x) {
            max_x = new_x;
        }
    }

    size_x = max_x - min_x + 1;
    size_y = max_y - min_y + 1;
    output = malloc(size_y * (size_x + 1));

    memset(output, ' ', size_y * (size_x + 1));

    for (int y = 0; y < size_y; y++) {
        output[y * (size_x + 1) + size_x] = '\0';
    }

    for (int i = 0; i < nb_points; i++) {
        point_t *p = &points[i];
        int x = p->x + p->vel_x * time - min_x;
        int y = p->y + p->vel_y * time - min_y;

        output[y * (size_x + 1) + x] = 'X';
    }

    for (int i = 0; i < size_y; i++) {
        printf("%s\n", output + i * (size_x + 1));
    }

    //printf("time: %d, min_x: %d, max_x: %d, min_y: %d, max_y: %d, size_x: %d, size_y: %d\n", time, min_x, max_x, min_y, max_y,
     //      max_x - min_x, max_y - min_y);
    printf("time: %d\n", time);
}

static void bisect(void)
{
    int a, b;

    a = 0;
    b = 1000;

    for (;;) {
        int d = compute_density(b);

        if (d < compute_density(b + 1)) {
            break;
        }

        a = b;
        b *= 2;
    }

    for (;;) {
        int c = (b + a) / 2;

        if (compute_density(c) > compute_density(c + 1)) {
            a = c;
        } else {
            b = c;
        }

        if (b - a <= 1) {
            break;
        }
    }

    print_points(b);
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

    nb_points = 0;
    while (parser < parser_end) {
        point_t *p = &points[nb_points++];

        if (nb_points >= MAX_POINTS) {
            printf("too many points\n");
            exit(1);
        }

        // position=<-31656,  32013> velocity=< 3, -3>
        parser += strlen("position=<");
        p->x = atoi_p(parser, &parser);
        parser += strlen(", ");
        p->y = atoi_p(parser, &parser);
        parser += strlen("> velocity=<");

        p->vel_x = atoi_p(parser, &parser);
        parser += strlen(", ");
        p->vel_y = atoi_p(parser, &parser);
        parser += strlen(">\n");
    }

    bisect();

    return 0;
}
