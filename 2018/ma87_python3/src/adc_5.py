import sys
import os
import re
import operator


if len(sys.argv) <= 1:
    exit(1)

filename = sys.argv[1]

character_delete = "!"

def get_next_letter(polymer, index, end_index):
    for i in range(index + 1, end_index, 1):
        if polymer[i] != character_delete:
            return polymer[i], i
    return None, None

def get_prev_index(polymer, index):
    for i in range(index, -1, -1):
        if polymer[i] != character_delete:
            return i
    return 0

def is_opposite_polarity(a, b):
    if a.upper() == b.upper():
        if a.isupper():
            return b.islower()
        else:
            return b.isupper()
    else:
        return False

def get_polymer_after_reaction(polymer):
    all_reaction_done = False

    current_index = 0
    end_index = len(polymer)
    while not all_reaction_done:
        current_letter = polymer[current_index]
        next_letter, index_next_letter = get_next_letter(polymer, current_index, end_index)
        if next_letter is None:
            all_reaction_done = True
        else:
            if is_opposite_polarity(current_letter, next_letter):
                polymer[current_index] = character_delete
                polymer[index_next_letter] = character_delete
                current_index = get_prev_index(polymer, current_index)
            else:
                _unused, current_index = get_next_letter(polymer, current_index, end_index)

    return "".join(polymer).replace(character_delete, "")

def char_range(c1, c2):
    for c in range(ord(c1), ord(c2)+1):
        yield chr(c)

def get_cut_polymer(polymer, char):
    cut_polymer = "".join(polymer)
    cut_polymer = cut_polymer.replace(char, "")
    cut_polymer = cut_polymer.replace(char.upper(), "")
    return list(cut_polymer)

with open(filename, 'r') as f:
    polymer = list(f.readlines()[0])[:-1]
    
    polymer_sol_1_list = polymer[:]
    polymer_sol_1 = get_polymer_after_reaction(polymer_sol_1_list)

    len_polymers = []
    for c in char_range('a', 'z'):
        polymer_char = get_cut_polymer(polymer, c)
        polymer_char_after_reaction = get_polymer_after_reaction(polymer_char)
        len_polymers.append(len(polymer_char_after_reaction))


print('solution 1 = ' + str(len(polymer_sol_1)))
print('solution 2 = ' + str(min(len_polymers)))

