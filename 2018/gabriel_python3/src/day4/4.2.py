#!/usr/bin/env python3

from collections import OrderedDict

filename = 'input'

def date_to_datetime(string):
    return int(string.split(':')[-1])

# sort events
event_log = OrderedDict()
with open(filename) as f:
    for line in f:
        date_str, content = line.split(']')
        date_str = date_str[1:]
        content = content.strip()
        event_log[date_str] = content
event_log = OrderedDict(sorted(event_log.items()))


guard_shifts = dict()
guard_id = None
starts_sleeping = dict()
for date_str, content in event_log.items():
    curr_date = date_to_datetime(date_str[1:])

    content = content.strip()
    if content.startswith('Guard #'):
        guard_id = int(content[len('Guard #'):].split(' ')[0])
        if guard_id not in guard_shifts:
            guard_shifts[guard_id] = {'sleeptable': [0] * 60,
                                      'total_sleep': 0}
    elif content == 'falls asleep':
        if guard_id:
            starts_sleeping[guard_id] = curr_date
    elif content == 'wakes up':
        if guard_id not in starts_sleeping:
            continue
        i = starts_sleeping[guard_id]
        tmp = curr_date - i
        if tmp < 0:
            tmp += 60
        guard_shifts[guard_id]['total_sleep'] += tmp
        while i < curr_date:
            guard_shifts[guard_id]['sleeptable'][i] += 1
            i = (i + 1) % 60
    else:
        raise AssertionError('should not be here')


# TODO: update if not awake at the end ?

most_alseep = 0
max_sleep = 0
for guard, info  in guard_shifts.items():
    t = guard_shifts[guard]['sleeptable']
    max_sleep_minute = max(t)
    if max_sleep_minute > max_sleep:
        max_sleep = max_sleep_minute
        most_alseep = guard

t = guard_shifts[most_alseep]['sleeptable']
print(most_alseep * t.index(max_sleep))
