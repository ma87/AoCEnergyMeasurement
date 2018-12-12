#!/usr/bin/env python3

import datetime
from collections import Counter
import re


pattern = re.compile(r'^\[(\d{4})-(\d{2})-(\d{2})\s(\d{2}):(\d{2})\]\s(.+)$')
pattern_wakeup = re.compile(r'wakes up')
pattern_asleep = re.compile(r'falls asleep')
pattern_guard = re.compile(r'Guard #(\d+) begins shift')


def get_records(data_list):
    records = []

    for year, month, day, hour, minute, text in data_list:

        year = int(year)
        month = int(month)
        day = int(day)
        hour = int(hour)
        minute = int(minute)

        record_time = datetime.datetime(year=year, month=month, day=day, hour=hour, minute=minute)
        records.append((record_time, text))

    records.sort(key=lambda x: x[0])

    results = {}
    for record_time, text in records:

        if pattern_guard.match(text):
            guard_id = int(pattern_guard.match(text).groups()[0])
            asleep_minute = None
            if guard_id not in results:
                results[guard_id] = {
                    'asleep_total': 0,
                    'asleep_minute_count': Counter(),
                }
        elif pattern_asleep.match(text):
            asleep_minute = record_time.minute
        elif pattern_wakeup.match(text):
            asleep_count = record_time.minute - asleep_minute
            results[guard_id]['asleep_total'] += asleep_count
            for i in range(asleep_minute, record_time.minute):
                results[guard_id]['asleep_minute_count'][i] += 1
            asleep_minute = None
        else:
            raise ValueError()

    for guard_id, guard_record in results.items():
        most_frequency = results[guard_id]['asleep_minute_count'].most_common(1)
        results[guard_id]['most_slept_day'] = most_frequency[0] if most_frequency else (0, 0)

    return results


def get_sleep_longest(records):
    max_guard_id = max(records, key=lambda x: records[x]['asleep_total'])
    return max_guard_id*records[max_guard_id]['most_slept_day'][0]


def get_sleep_most_frequency(records):
    max_guard_id = max(records, key=lambda x: records[x]['most_slept_day'][1])
    return max_guard_id*records[max_guard_id]['most_slept_day'][0]


if __name__ == "__main__":

    with open('data', 'r') as infile:
        lines = [line for line in infile]
        data_list = [pattern.match(line).groups() for line in lines]
        records = get_records(data_list)

        print('Solution 1 : ', get_sleep_longest(records))
        print('Solution 2 : ', get_sleep_most_frequency(records))
