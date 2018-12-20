import sys

if len(sys.argv) <= 1:
    exit(1)

filename = sys.argv[1]

def get_mask():
    return [(-1, -1), (0, -1), (1, -1),
            (-1, 0),           (1, 0),
            (-1, 1),  (0, 1),  (1, 1)
            ]

def is_in_grid(x,y,m,max_x,max_y):
    new_x = x + m[0]
    new_y = y + m[1]

    if new_x >= 0 and new_x < max_x and new_y >= 0 and new_y < max_y:
        return (new_x, new_y)
    else:
        return None

def get_number_state(states, x, y, mask, state):
    number_state = 0
    max_x = len(states[0])
    max_y = len(states)

    for m in mask:
        coord = is_in_grid(x,y,m,max_x,max_y)
        if coord and states[coord[1]][coord[0]] == state:
            number_state += 1

    return number_state

def process_mask(states, x, y, mask):
    process_state = states[y][x]
    if process_state == '.':
        if get_number_state(states,x,y,mask,'|')>=3:
            process_state = '|'
    elif process_state == '|':
        if get_number_state(states,x,y,mask,'#')>=3:
            process_state = '#'
    elif process_state == '#':
        if get_number_state(states,x,y,mask,'#')>=1 and get_number_state(states,x,y,mask,'|')>=1:
            process_state = '#'
        else:
            process_state = '.'
    return process_state

def process_line(states, y, mask):
    return "".join([process_mask(states, x, y, mask) for x in range(len(states[y]))])

def process(states):
    process_lines = []
    for y, l in enumerate(states):
        process_lines.append(process_line(states, y, get_mask()))
    return process_lines
    #return [processed_line for y in range(len(states)) for processed_line in "".join([process_mask(states,x,y,get_mask()) for x in range(len(states[y]))])]

with open(filename, 'r') as f:
    states = f.read().splitlines()

prev_number_trees = 0
prev_number_lumberyards = 0

resources = {0}

frequencies = {}

for i in range(1000):
    process_states = process(states)
    #print(" -- ")
    #print("\n".join(process(states)))
    states[:] = process_states

    number_trees = "".join(states).count('|')
    number_lumberyards = "".join(states).count('#')

    tmp_resources = number_trees * number_lumberyards

    #print("resources = " + str(number_trees * number_lumberyards))
    if tmp_resources in resources:
        frequencies[tmp_resources].append(i)
        #print("resources " + str(tmp_resources) + " was found at " + " ".join(str(f) for f in frequencies[tmp_resources]))
    else:
        resources.add(tmp_resources)
        frequencies[tmp_resources] = [i]


    if i==9:
        solution_1 = number_trees * number_lumberyards
    #if number_lumberyards - prev_number_lumberyards == 0 and number_trees - prev_number_trees == 0:

ref_f = 0
stab_f = 0
for freqs in frequencies.values():
    for i, f in enumerate(freqs[1:]):
        if ref_f == 0:
            ref_f = freqs[i+1] - freqs[i]
        elif ref_f == freqs[i+1] - freqs[i]:
            stab_f = ref_f
            print("stab_f = " + str(stab_f))
        ref_f = freqs[i+1] - freqs[i]

if stab_f > 0:
    mod_stab_f = (100000 - 1) % stab_f

print("mod_stab_f = " + str(mod_stab_f))

solution_2 = 0
max_index = -1
for res, freqs in frequencies.items():
    for f in freqs:
        if f % stab_f == mod_stab_f:
            if f > max_index:
                print("f = " + str(f))
                print("res = " + str(res))
                max_index = f
                solution_2 = res

number_trees = "".join(states).count('|')
number_lumberyards = "".join(states).count('#')
print("solution 1 = " + str(solution_1))

# solution 2 not working: should be < 191295
print("solution 2 = " + str(solution_2))
