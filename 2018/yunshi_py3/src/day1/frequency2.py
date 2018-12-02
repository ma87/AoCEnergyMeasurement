#!/usr/bin/env python3
if __name__ == "__main__":
    with open('data', 'r') as infile:
        data_list = [int(line) for line in infile]
        seen = {0}
        first_seen_twice = None

        cursor = 0
        while not first_seen_twice:
            for data in data_list:
                cursor += data
                if cursor in seen:
                    first_seen_twice = cursor
                    break
                else:
                    seen.add(cursor)

        print(first_seen_twice)
