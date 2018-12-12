#!/usr/bin/env python3

import re

pattern = re.compile(r'Step (.*) must be finished before step (.*) can begin.')
nb_workers = 5


def get_task_sequence(data):

    def has_src_finished(task):
        return set(src for src, dest in data if task == dest).issubset(set(result))

    result = []
    src_list = list(set(src for src, _dest in data) - set(dest for _src, dest in data))
    src_list.sort()

    while src_list:
        cursor = src_list.pop(0)
        result.append(cursor)

        new_candidates = [
            dest for src, dest in data if src == cursor and has_src_finished(dest)]
        src_list.extend(new_candidates)
        src_list.sort()

    return result


def get_next(data_list, done, tasks):
    candidates = set(
        task for task in tasks
        if set(src for src, dest in data_list if task == dest).issubset(done)
    )

    if candidates:
        candidates = list(candidates)
        candidates.sort()
        candidate = candidates.pop(0)
        tasks.remove(candidate)
        return candidate, abs(ord(candidate)-ord('A')) + 60

    return None, 0


def get_tasks_done(tasks, data_list):
    time = 0
    workers = [(None, 0)] * nb_workers
    done = set()

    while True:

        for i, worker in enumerate(workers):
            if worker[0] and worker[1] == 0:  # Job done
                done.add(worker[0])
                workers[i] = None, 0

            if worker[1] == 0:  # Idle
                if tasks:
                    workers[i] = get_next(data_list, done, tasks)

            else:
                workers[i] = worker[0], worker[1] - 1

        if not tasks:
            time += max(worker[1] for worker in workers)
            return time

        time += 1

    return None


if __name__ == "__main__":
    with open('data', 'r') as infile:
        lines = [line for line in infile.read().splitlines()]
        data_list = [pattern.match(line).groups() for line in lines]
        data_list.sort()

        tasks = get_task_sequence(data_list)
        print('Solution 1 :', ''.join(tasks))
        print('Solution 2 :', get_tasks_done(tasks, data_list))
