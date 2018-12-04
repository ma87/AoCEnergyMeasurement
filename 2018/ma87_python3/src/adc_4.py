import sys
import os
import re
import operator


if len(sys.argv) <= 1:
    exit(1)

filename = sys.argv[1]


def get_solution_1(guards_asleep):
    most_asleep_id = 0
    max_number_minutes = -1
    for guard_id, asleep_minutes in guards_asleep.items():
        number_minutes = sum([len(m) for m in asleep_minutes])
        if number_minutes > max_number_minutes:
            max_number_minutes = number_minutes
            most_asleep_id = guard_id

    minutes_asleep = {}
    for minutes in guards_asleep[most_asleep_id]:
        for m in minutes:
            if m in minutes_asleep:
                minutes_asleep[m] += 1
            else:
                minutes_asleep[m] = 1
    most_common_minutes, value = max(minutes_asleep.items(), key=operator.itemgetter(1))

    return most_asleep_id * most_common_minutes

def get_solution_2(guards_asleep):
    values = {}
    most_common_minutes = {}
    for id in guards_asleep:
        minutes_asleep = {}
        for minutes in guards_asleep[id]:
            for m in minutes:
                #print("for id = " + str(id) + " , m = " + str(m))
                if m in minutes_asleep:
                    minutes_asleep[m] += 1
                else:
                    minutes_asleep[m] = 1
        if len(minutes_asleep) > 0:
            most_common_minutes[id], values[id] = max(minutes_asleep.items(), key=operator.itemgetter(1))

    guard_id, _value = max(values.items(), key=operator.itemgetter(1))

    return guard_id * most_common_minutes[guard_id]


with open(filename, 'r') as f:
    entry_reg_exp = re.compile(r'\[(\d+)-(\d+)-(\d+) (\d+):(\d+)\] (.*)')
    guard_reg_exp = re.compile(r'Guard #(\d+) begins shift')
    entries = f.readlines()

    events = {}
    timestamps = []
    for entry in entries:
        year, month, day, hour, minutes, text = tuple(entry_reg_exp.match(entry).groups())
        #print("entry date = {}/{}/{}-{}:{} = {}".format(year,month,day,hour,minutes, text))
        timestamp = "{}{}{}{}".format(month,day,hour,minutes)
        events[timestamp] = text
        timestamps.append(timestamp)

    timestamps.sort()
    
    guards_asleep = {}
    id = 0
    minute_asleep = 0
    for t in timestamps:
        if "#" in events[t]:
            id = int(guard_reg_exp.match(events[t]).groups()[0])
            if not id in guards_asleep:
                guards_asleep[id] = []
        elif "falls" in events[t]:
            minutes_asleep = int(t[-2:])
        elif "wakes" in events[t]:
            minutes_wake_up = int(t[-2:])
            guards_asleep[id].append([m for m in range(minutes_asleep, minutes_wake_up, 1)])


print("solution 1 = " + str(get_solution_1(guards_asleep)))
print("solution 2 = " + str(get_solution_2(guards_asleep)))
