import sys

if len(sys.argv) <= 1:
    exit(1)

filename = sys.argv[1]
current_frequency = 0
first_repeated_frequency_found = False
visited_frequencies = {0}
current_frequencies = []

with open(filename, 'r') as f:
    contents = f.readlines()
    while not first_repeated_frequency_found:
        for content in contents:
            if content[0] == '+':
                current_frequency = current_frequency + int(content[1:])
            elif content[0] == '-':
                current_frequency = current_frequency - int(content[1:])
            else:
                print('strange line = ' + content)

            if not first_repeated_frequency_found and current_frequency in visited_frequencies:
                first_repeated_frequency = current_frequency
                first_repeated_frequency_found = True
            else:
                visited_frequencies.add(current_frequency)
        current_frequencies.append(current_frequency)

print('solution 1: ' + str(current_frequencies[0]))
print('solution 2: ' + str(first_repeated_frequency))
