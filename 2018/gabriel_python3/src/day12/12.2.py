#!/usr/bin/env python3

def parse_input(filename):
    state = list()
    rules = list()
    with open(filename) as f:
        for line in f:
            line = line.strip()

            if not line:
                continue

            if line.startswith('initial state:'):
                for c in line[len('initial state: '):]:
                    state.append(int(c == '#'))

            elif line.endswith('#'):
                tmp = 0
                for c in line.split(' => ')[0]:
                    tmp = tmp << 1
                    tmp += int(c == '#')
                rules.append(tmp)

    return (state, sorted(rules))

def print_state(state):
    for x in state:
        if x:
            print('#', end='')
        else:
            print('.', end='')
    print()

def trim(state, index):
    while not state[0]:
        state.pop(0)
        index += 1
    while not state[-1]:
        state.pop()
    return state, index

def total(state, index):
    total = 0
    for x, y in zip(state, range(index, index + len(state))):
        total += x * y
    return total

def puzzle(state, rules, generations, left_index):
    while True:
        if generations == 0:
            return state, rules, generations, left_index

        state.insert(0, 0)
        state.insert(0, 0)
        left_index -= 2
        state.append(0)
        state.append(0)

        next_state = [0] * len(state)

        # all the middle states
        curr = 0
        for i in range(0, len(state) - 2):
            curr = ((curr << 1) & 0b11111) + state[i + 2]
            if curr in rules:
                next_state[i] = 1

        curr = ((curr << 1) & 0b11111)
        next_state[-2] = int(curr in rules)
        curr = ((curr << 1) & 0b11111)
        next_state[-1] = int(curr in rules)

        next_state, left_index = trim(next_state, left_index)

        generations -= 1
        state, _ = trim(state, 0)
        if state == next_state:
            return next_state, rules, generations, left_index
            
        state = next_state

state, rules = parse_input('input')
state, _, remaining_gens, left_index = puzzle(state, rules, 50000000000, 0)
print(total(state, left_index + remaining_gens))
