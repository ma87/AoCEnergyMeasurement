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

//#define TRACK_SIZE  13
#define TRACK_SIZE  150

typedef struct tile_t {
    char type;
    struct cart_t *current;
} tile_t;

enum direction {
    LEFT = 0,
    UP = 1,
    RIGHT = 2,
    DOWN = 3
};

typedef struct cart_t {
    int x, y;
    int direction;
    int cross_step;
    int crashed;
} cart_t;

#define MAX_NB_CARTS  20
static cart_t *carts[MAX_NB_CARTS];
static int nb_carts;
static int nb_carts_left;

static cart_t *cart_new(void)
{
    cart_t *cart = calloc(1, sizeof(cart_t));

    carts[nb_carts++] = cart;

    return cart;
}

static tile_t tracks[TRACK_SIZE][TRACK_SIZE];
static int got_crash;

static int cart_compare(const void *cart1_p, const void *cart2_p)
{
    const cart_t *cart1 = *(const cart_t **)cart1_p;
    const cart_t *cart2 = *(const cart_t **)cart2_p;

    if (cart1->crashed != cart2->crashed) {
        return cart1->crashed - cart2->crashed;
    }

    if (cart1->y != cart2->y) {
        return cart1->y - cart2->y;
    }

    return cart1->x - cart2->x;
}

static void cart_move(cart_t *cart)
{
    tile_t *before, *after;

    before = &tracks[cart->x][cart->y];
    cart = before->current;

    if (nb_carts_left <= 1) {
        printf("part2: %d,%d\n", cart->x, cart->y);
        exit(0);
    }

    switch (cart->direction) {
      case UP:
        cart->y -= 1;
        break;
      case DOWN:
        cart->y += 1;
        break;
      case LEFT:
        cart->x -= 1;
        break;
      case RIGHT:
        cart->x += 1;
        break;
    }

    after = &tracks[cart->x][cart->y];
    before->current = NULL;

    if (after->current) {
        /* crash */
        if (!got_crash) {
            printf("part1: %d,%d\n", cart->x, cart->y);
            got_crash = 1;
        }

        after->current->crashed = 1;
        after->current = NULL;
        cart->crashed = 1;
        nb_carts_left -= 2;
        return;
    }

    after->current = cart;

    switch (after->type) {
      case '+':
        switch (cart->cross_step) {
          case 0:
            cart->direction--;
            break;

          case 1:
            /* straight */
            break;

          case 2:
            cart->direction++;
            break;
        }
        if (cart->direction < 0) {
            cart->direction += 4;
        }
        if (cart->direction > 3) {
            cart->direction -= 4;
        }
        cart->cross_step++;
        if (cart->cross_step >= 3) {
            cart->cross_step = 0;
        }
        break;

      case '-':
      case '|':
        break;

      case '\\':
        switch (cart->direction) {
          case RIGHT:
            cart->direction = DOWN;
            break;

          case UP:
            cart->direction = LEFT;
            break;

          case LEFT:
            cart->direction = UP;
            break;

          case DOWN:
            cart->direction = RIGHT;
            break;
        }
        break;

      case '/':
        switch (cart->direction) {
          case RIGHT:
            cart->direction = UP;
            break;

          case UP:
            cart->direction = RIGHT;
            break;

          case LEFT:
            cart->direction = DOWN;
            break;

          case DOWN:
            cart->direction = LEFT;
            break;
        }
        break;

      case ' ':
        printf("off-track\n");
        exit(1);
    }
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

    for (int y = 0; y < TRACK_SIZE; y++) {
        for (int x = 0; x < TRACK_SIZE; x++) {
            cart_t *cart;

            tracks[x][y].type = *parser++;
            switch (tracks[x][y].type) {
              case '^':
                tracks[x][y].type = '|';
                cart = cart_new();

                cart->x = x;
                cart->y = y;
                cart->direction = UP;
                tracks[x][y].current = cart;
                break;

              case 'v':
                tracks[x][y].type = '|';
                cart = cart_new();

                cart->x = x;
                cart->y = y;
                cart->direction = DOWN;
                tracks[x][y].current = cart;
                break;

              case '<':
                tracks[x][y].type = '-';
                cart = cart_new();

                cart->x = x;
                cart->y = y;
                cart->direction = LEFT;
                tracks[x][y].current = cart;
                break;

              case '>':
                tracks[x][y].type = '-';
                cart = cart_new();

                cart->x = x;
                cart->y = y;
                cart->direction = RIGHT;
                tracks[x][y].current = cart;
                break;

              default:
                break;
            }
        }
        parser++;
    }

    nb_carts_left = nb_carts;

    for (;;) {
        qsort(carts, nb_carts, sizeof(cart_t *), &cart_compare);

        for (int i = 0; i < nb_carts; i++) {
            if (!carts[i]->crashed) {
                cart_move(carts[i]);
            }
        }
    }
    return 0;
}
