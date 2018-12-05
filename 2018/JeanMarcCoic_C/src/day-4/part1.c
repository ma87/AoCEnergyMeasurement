#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

#define UNSAFE

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

enum event_type_t {
    TYPE_GUARD  = 0,
    TYPE_SLEEP  = 1,
    TYPE_WAKEUP = 2
};

typedef struct event_t {
    enum event_type_t type;
    int guard;
    int month;
    int day;
    int hour;
    int min;
} event_t;

static inline event_t *event_new(void)
{
    return calloc(1, sizeof(event_t));
}

static int event_compare(const void *evt1_p, const void *evt2_p)
{
    const event_t *evt1 = *(const event_t **)evt1_p;
    const event_t *evt2 = *(const event_t **)evt2_p;

    if (evt1->month != evt2->month) {
        return evt1->month - evt2->month;
    }
    if (evt1->day != evt2->day) {
        return evt1->day - evt2->day;
    }
    if (evt1->hour != evt2->hour) {
        return evt1->hour - evt2->hour;
    }

    return evt1->min - evt2->min;
}

typedef struct guard_t {
    int id;
    uint16_t minutes[60];
} guard_t;

static guard_t guards[24];

static guard_t *find_guard(int id)
{
    for (int i = 0; i < 24; i++) {
        if (guards[i].id == 0) {
            guards[i].id = id;
        }
        if (guards[i].id == id) {
            return &guards[i];
        }
    }
    printf("unknown id: %d", id);
    return NULL;
}

int main(int argc, char **argv)
{
    event_t *events[2000];
    int nb_events = 0;
    int fd = -1;
    struct stat st;
    char *parser = MAP_FAILED;
    char *parser_start, *parser_end;
    guard_t *last = NULL;
    int max_guard = 0;
    int max_sum = 0;
    int max_guard_min = 0;
    int part2_max_guard = 0;
    int part2_max_minute = 0;
    int part2_max_guard_min = 0;

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
        event_t *event = event_new();
        //[1518-06-05 00:46] falls asleep
        //#24 @ 156,921: 18x17

        parser += strlen("[1518-");
        event->month = atoi_p(parser, &parser);

        parser += strlen("-");
        event->day = atoi_p(parser, &parser);

        parser += strlen(" ");
        event->hour = atoi_p(parser, &parser);

        parser += strlen(":");
        event->min = atoi_p(parser, &parser);

        parser += strlen("] ");

        switch (*parser) {
          case 'G':
            //Guard #3539 begins shift
            parser += strlen("Guard #");
            event->guard = atoi_p(parser, &parser);

            event->type = TYPE_GUARD;
            while (*parser++ != '\n') {
            }
            break;

          case 'f':
            //falls asleep
            event->type = TYPE_SLEEP;
            while (*parser++ != '\n') {
            }
            break;

          case 'w':
            event->type = TYPE_WAKEUP;
            while (*parser++ != '\n') {
            }
            break;

          default:
            printf("unexpected char: %c\n", *parser);
            exit(1);
            break;
        }

        //printf("%02d/%02d %02d:%02d type: %d - guard = %d\n", event->month, event->day, event->hour,
        //       event->min, event->type, event->guard);
        events[nb_events++] = event;
    }

    qsort(events, nb_events, sizeof(event_t *), &event_compare);

    for (int i = 0; i < nb_events; i++) {
        const event_t *evt = events[i];
        switch (evt->type) {
          case TYPE_GUARD:
            last = find_guard(evt->guard);
            break;

          case TYPE_SLEEP:
            break;

          case TYPE_WAKEUP:
            for (int min = events[i - 1]->min; min < evt->min; min++) {
                last->minutes[min]++;
            }
            break;
        }
       //printf("%02d/%02d %02d:%02d type: %d - guard = %d\n", evt->month, evt->day, evt->hour,
       //       evt->min, evt->type, evt->guard);
    }

    //printf("guard|");
    //for (int i = 0; i < 60; i++) {
    //    printf("%02d", i);
    //}
    //printf("|total\n");

    for (int i = 0; i < 24; i++) {
        int sum = 0;
        int max_minute_min = 0;
        int max_minute = 0;

        if (guards[i].id == 0) {
            break;
        }

        //printf("%4d |", guards[i].id);
        for (int min = 0; min < 60; min++) {
            int nb_days = guards[i].minutes[min];

            //printf("%2d", nb_days);
            if (nb_days > 0) {
                sum += nb_days;
            }

            if (nb_days > max_minute) {
                max_minute = nb_days;
                max_minute_min = min;
            }
        }
        //printf("|%d\n", sum);

        if (sum > max_sum) {
            max_sum = sum;
            max_guard = i;
            max_guard_min = max_minute_min;
        }
        if (part2_max_minute < max_minute) {
            part2_max_minute = max_minute;
            part2_max_guard  = i;
            part2_max_guard_min = max_minute_min;
        }
    }

    printf("part1: guard: %d, max_minute: %d, answer: %d\n", guards[max_guard].id,
           max_guard_min, guards[max_guard].id * max_guard_min);
    printf("part2: guard: %d, max_minute: %d, answer: %d\n", guards[part2_max_guard].id,
           part2_max_guard_min, guards[part2_max_guard].id *
           part2_max_guard_min);

    return 0;
}
