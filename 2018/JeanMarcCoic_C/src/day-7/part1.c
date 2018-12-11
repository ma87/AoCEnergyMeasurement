#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

typedef struct step_t {
    int nb_depends_on;
    uint32_t needed_by;
    int dependency_finish_at;
} step_t;

#define NB_STEPS  26
static step_t steps[NB_STEPS];

typedef struct worker_t {
    int next_idle;
} worker_t;

#define NB_WORKERS  5
static worker_t workers[NB_WORKERS];

static inline int get_step_work(int step)
{
    return 60 + step + 1;
}

static inline int assign_worker(int current_time, int start_at, int step)
{
    int work = get_step_work(step);
    int min_worker = 0;
    int min_time = 10000000;
    for (int w = 0; w < NB_WORKERS; w++) {
        if (min_time > workers[w].next_idle) {
            min_time = workers[w].next_idle;
            min_worker = w;
        }
    }

    if (start_at > workers[min_worker].next_idle) {
        work += start_at - workers[min_worker].next_idle;
    }

    workers[min_worker].next_idle += work;

    return workers[min_worker].next_idle;
}

int main(int argc, char **argv)
{
    int fd = -1;
    struct stat st;
    char *parser = MAP_FAILED;
    char *parser_start, *parser_end;
    char order[NB_STEPS + 1];
    char *p;
    int part2_time = 0;
    int current_time = 0;

    order[NB_STEPS] = '\0';

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
        int a, b;
        // Step Q must be finished before step O can begin.

        parser += strlen("Step ");
        a = *parser++ - 'A';
        parser += strlen(" must be finished before step ");
        b = *parser++ - 'A';
        parser += strlen(" can begin.\n");

        steps[a].needed_by |= (1 << b);
        steps[b].nb_depends_on++;
    }

    p = order;
    while (p - order < NB_STEPS) {
        for (int c = 0; c < NB_STEPS; c++) {
            if (steps[c].nb_depends_on == 0) {
                *p++ = 'A' + c;

                for (int i = 0; i < NB_STEPS; i++) {
                    if (steps[c].needed_by & (1 << i)) {
                        steps[i].nb_depends_on--;
                    }
                }
                steps[c].nb_depends_on = -1;
                break;
            }
        }
    }

    memset(steps, '\0', sizeof(step_t) * NB_STEPS);

    parser = parser_start;
    while (parser < parser_end) {
        int a, b;
        // Step Q must be finished before step O can begin.

        parser += strlen("Step ");
        a = *parser++ - 'A';
        parser += strlen(" must be finished before step ");
        b = *parser++ - 'A';
        parser += strlen(" can begin.\n");

        steps[a].needed_by |= (1 << b);
        steps[b].nb_depends_on++;
    }
    p = order;
    while (p - order < NB_STEPS) {
        int min_finish_at = 0;

        for (int c = 0; c < NB_STEPS; c++) {
            if (steps[c].nb_depends_on == 0
            &&  current_time >= steps[c].dependency_finish_at)
            {
                int end_time = assign_worker(current_time, steps[c].dependency_finish_at,
                                             c);
                p++;

                if (min_finish_at < end_time) {
                    min_finish_at = end_time;
                }

                for (int i = 0; i < NB_STEPS; i++) {
                    if (steps[c].needed_by & (1 << i)) {
                        if (steps[i].nb_depends_on > 0) {
                            steps[i].nb_depends_on--;
                            if (steps[i].dependency_finish_at < end_time) {
                                steps[i].dependency_finish_at = end_time;
                            }
                        }
                    }
                }
                steps[c].nb_depends_on = -1;
            }
        }

        current_time = min_finish_at;
    }


    for (int w = 0; w < NB_WORKERS; w++) {
        if (part2_time < workers[w].next_idle) {
            part2_time = workers[w].next_idle;
        }
    }
    printf("steps: %s\n", order);
    printf("part2_time: %d\n", part2_time);

    return 0;
}
