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

#define GRID_SIZE  300
static int cells[GRID_SIZE * GRID_SIZE];
static int serial = 5791;

static inline int compute_power(int x, int y)
{
    int rack_id = x + 10;
    int power = rack_id * y + serial;

    power *= rack_id;

    power = ((power / 100) % 10) - 5;

    return power;
}

static int compute_max(int square_size, int *max_x, int *max_y)
{
    int max_power = -1000000000;
    int right_most_square = GRID_SIZE - (square_size - 1);

    for (int x = 0; x < right_most_square; x++) {
        for (int y = 0; y < right_most_square; y++) {
            int total_power = 0;
            int *cell = &cells[y * GRID_SIZE + x];

            for (int i = 0; i < square_size; i++) {
                for (int j = 0; j < square_size; j++) {
                    total_power += *cell++;
                }
                cell += GRID_SIZE - (square_size);
            }

            if (max_power < total_power) {
                max_power = total_power;
                *max_x = x;
                *max_y = y;
            }
        }
    }

    return max_power;
}

int main(int argc, char **argv)
{
    int max_power = 0;
    int max_max_x, max_max_y, max_square_size;
    int max_x = 0, max_y = 0;

    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            cells[y * GRID_SIZE + x] = compute_power(x, y);
        }
    }

    compute_max(3, &max_x, &max_y);

    printf("part1: %d,%d\n", max_x, max_y);

    for (int square_size = 4; square_size <= 300; square_size++) {
        int m = compute_max(square_size, &max_x, &max_y);
        if (m < 0) {
            break;
        }

        if (max_power < m) {
            max_power = m;
            max_max_x = max_x;
            max_max_y = max_y;
            max_square_size = square_size;
        }
    }

    printf("part2: %d,%d,%d\n", max_max_x, max_max_y, max_square_size);

    return 0;
}
