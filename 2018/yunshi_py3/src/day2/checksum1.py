#!/usr/bin/env python3

from collections import Counter


def check_letter_appear_twice_and_three_times(element):
    counter = Counter(element)
    counts = counter.values()
    return 2 in counts, 3 in counts


def check_sum(str_list):
    check_result = [check_letter_appear_twice_and_three_times(element) for element in str_list]
    appear_twice = len([twice for twice, _three_times in check_result if twice])
    appear_threetimes = len([three_times for _twice, three_times in check_result if three_times])
    return appear_twice*appear_threetimes


if __name__ == "__main__":
    with open('data', 'r') as infile:
        print(check_sum(infile))
