#!/usr/bin/env python3

from collections import Counter


def distance(x, y):
    return abs(x[0]-y[0]) + abs(x[1]-y[1])


def get_corner(data):
    x_min = min(x for x, _y in data)
    x_max = max(x for x, _y in data)
    y_min = min(y for _x, y in data)
    y_max = max(y for _x, y in data)
    return x_min, x_max, y_min, y_max


def count_area(data):
    result = Counter()
    infinite = set()

    x_min, x_max, y_min, y_max = get_corner(data)
    for x in range(x_min, x_max):
        for y in range(y_min, y_max):
            min_dist = distance((x_min, y_min), (x_max, y_max))
            min_cord = (0, 0)
            for cord in data:
                dist = distance((x, y), cord)
                if dist < min_dist:
                    min_dist = dist
                    min_cord = cord
                elif dist == min_dist:
                    min_cord = (-1, -1)
            if x in (x_min, x_max) or y in (y_min, y_max):
                infinite.add(min_cord)
            result[min_cord] += 1

    max_area = next(area for area in result.most_common() if area not in infinite)
    return max_area[1]


def get_safe_zone(data, threshold):
    count = 0
    x_min, x_max, y_min, y_max = get_corner(data)
    for x in range(x_min, x_max):
        for y in range(y_min, y_max):
            total_distance = 0
            for cord in data:
                dis = distance((x, y), cord)
                total_distance += dis
                if total_distance >= threshold:
                    break

            if total_distance < threshold:
                count += 1

    return count


if __name__ == "__main__":
    with open('data', 'r') as infile:
        data = [tuple(line.split(',')) for line in infile.read().splitlines()]
        data = [(int(x), int(y)) for x, y in data]
        data.sort()
        print("Solution 1 : ", count_area(data))
        print("Solution 2 : ", get_safe_zone(data, 10000))
