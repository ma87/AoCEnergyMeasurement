import sys

if len(sys.argv) <= 1:
    exit(1)

filename = sys.argv[1]
counter_two_times = 0
counter_three_times = 0

def is_close_to_a_word(check_word, visited_words):
    for word in visited_words:
        counter = 0
        for i in range(len(word)):
            if word[i] != check_word[i]:
                idx = i
                counter = counter + 1
        if counter == 1:
            return word[0:idx] + word[idx+1:]
    return None

with open(filename, 'r') as f:
    words = f.readlines()
    visited_words = []
    close_word_found = False
    for word in words:
        map_letters = {}
        for letter in word:
            if letter in map_letters:
                map_letters[letter] = map_letters[letter] + 1
            else:
                map_letters[letter] = 1
        if 2 in map_letters.values():
            counter_two_times = counter_two_times + 1
        if 3 in map_letters.values():
            counter_three_times = counter_three_times + 1

        if not close_word_found:
            res = is_close_to_a_word(word, visited_words)
            if res is not None:
                solution_2 = res
                close_word_found = True
            visited_words.append(word)

print('solution 1 = ' + str(counter_two_times * counter_three_times))
print('solution 2 = ' + solution_2)
