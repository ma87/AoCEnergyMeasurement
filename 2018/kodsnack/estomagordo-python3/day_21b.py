def solve(d):
    ipreg = int(d[0][-1])
    ip = 0

    instructions = []

    for line in d[1:]:
        ls = line.split()
        instructions.append([ls[0]] + list(map(int, ls[1:])))

    inscount = len(instructions)
    registers = [0] * 6
    steps = 0
    last_insert = 0
    seen = {}

    while True:
        if not 0 <= ip < inscount:
            break

        steps += 1

        if steps > last_insert + 10**9:
            for k in seen:
                if seen[k] == last_insert:
                    return k 

        instruction, a, b, c = instructions[ip]

        registers[ipreg] = ip

        if instruction == 'seti':
            registers[c] = a
        elif instruction == 'addi':
            registers[c] = registers[a] + b
        elif instruction == 'setr':
            registers[c] = registers[a]
        elif instruction == 'addr':
            registers[c] = registers[a] + registers[b]
        elif instruction == 'muli':
            registers[c] = registers[a] * b
        elif instruction == 'mulr':
            registers[c] = registers[a] * registers[b]
        elif instruction == 'gtrr':
            registers[c] = 1 if (registers[a] > registers[b]) else 0
        elif instruction == 'gtir':
            registers[c] = 1 if (a > registers[b]) else 0
        elif instruction == 'eqrr':
            compvalue = registers[[r for r in [a, b] if r != 0][0]]
            if compvalue not in seen:
                seen[compvalue] = steps
                last_insert = steps
            registers[c] = 0
        elif instruction == 'eqri':
            registers[c] = 1 if (registers[a] == b) else 0
        elif instruction == 'bani':
            registers[c] = registers[a] & b
        elif instruction == 'bori':
            registers[c] = registers[a] | b

        ip = registers[ipreg]
        ip += 1


def read_and_solve():
    with open('input_21.txt') as f:
        data = [line.rstrip() for line in f]
        return solve(data)

if __name__ == '__main__':
    print(read_and_solve())