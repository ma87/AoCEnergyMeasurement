#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

static int metadata_sum;

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

static int parse_node(char *p, char **end)
{
    int nb_children;
    int nb_metadata;
    int children[16];
    int metadatas[16];
    int node_value = 0;

    nb_children = atoi_p(p, &p);
    p++;
    nb_metadata = atoi_p(p, &p);
    p++;

    if (nb_children >= 16) {
        printf("too many children: %d\n", nb_children);
        exit(1);
    }
    if (nb_metadata >= 16) {
        printf("too many metadatas: %d\n", nb_metadata);
        exit(1);
    }

    for (int i = 0; i < nb_children; i++) {
        children[i] = parse_node(p, &p);
    }

    for (int i = 0; i < nb_metadata; i++) {
        int m = atoi_p(p, &p);

        metadata_sum += m;
        node_value += m;
        metadatas[i] = m;
        p++;
    }

    *end = p;

    if (nb_children == 0) {
        return node_value;
    }

    node_value = 0;

    for (int i = 0; i < nb_metadata; i++) {
        int c = metadatas[i];

        if (c >= 1 && c <= nb_children) {
            node_value += children[c - 1];
        }
    }
    return node_value;
}

int main(int argc, char **argv)
{
    int fd = -1;
    struct stat st;
    char *parser = MAP_FAILED;
    char *parser_start, *parser_end;
    int root_value;

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

    root_value = parse_node(parser, &parser);

    printf("metadata: %d\nroot_value: %d\n", metadata_sum, root_value);

    return 0;
}
