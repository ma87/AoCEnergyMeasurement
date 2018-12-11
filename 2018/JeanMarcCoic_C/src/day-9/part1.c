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

typedef struct elem_t {
    struct elem_t *prev;
    struct elem_t *next;

    uint64_t value;
} elem_t;

static inline elem_t *elem_new(uint64_t value)
{
    elem_t *e = malloc(sizeof(*e));

    e->value = value;
    e->prev = e;
    e->next = e;

    return e;
}

static inline void elem_delete(elem_t **e)
{
    if (e && *e) {
        free(*e);
        *e = NULL;
    }
}

static inline elem_t *elem_lookup(elem_t *circle, int location)
{
    if (location == 0) {
        return circle;
    }
    if (location < 0) {
        return elem_lookup(circle->prev, location + 1);
    }
    return elem_lookup(circle->next, location - 1);
}

static inline elem_t *elem_insert(elem_t *circle, elem_t *e)
{
    elem_t *right = circle->next;

    circle->next = e;
    e->prev = circle;

    right->prev = e;
    e->next = right;

    return e;
}

static inline void elem_remove(elem_t *elem)
{
    elem->next->prev = elem->prev;
    elem->prev->next = elem->next;
}

static void do_game(int nb_players, int nb_marbles)
{
    uint64_t *players;
    elem_t *circle = elem_new(0);
    elem_t *current = circle;
    uint64_t max_score = 0;

    players = calloc(nb_players, sizeof(uint64_t));

    for (int i = 1; i < nb_marbles; i++) {
        if (i % 23 == 0) {
            elem_t *to_remove = elem_lookup(current, -7);

            players[i % nb_players] += i + to_remove->value;
            current = to_remove->next;
            elem_remove(to_remove);
            elem_delete(&to_remove);
            continue;
        }

        current = elem_insert(elem_lookup(current, 1), elem_new(i));
    }

    for (int i = 0; i < nb_players; i++) {
        if (max_score < players[i]) {
            max_score = players[i];
        }
    }

    printf("max_score: %zu\n", max_score);

    free(players);
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

    while (parser < parser_end) {
        int nb_players, nb_marbles;
        // 411 players; last marble is worth 71170 points
        nb_players = atoi_p(parser, &parser);
        parser += strlen(" players; last marble is worth ");
        nb_marbles = atoi_p(parser, &parser);
        parser += strlen(" points\n");

        do_game(nb_players, nb_marbles + 1);
        do_game(nb_players, nb_marbles * 100 + 1);
    }

    return 0;
}
