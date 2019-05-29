from collections import defaultdict, Counter


def parse_data(data):
	eventstr = data.split()
	datestr = eventstr[0][1:]
	timestr = eventstr[1][:-1]
	year, month, day = list(map(int, datestr.split('-')))
	hour, minute = list(map(int, timestr.split(':')))
	event = 0 if len(eventstr) == 6 else 1 if eventstr[2] == 'falls' else 2
	guard = int(eventstr[3][1:]) if event == 0 else -1

	return (year, month, day, hour, minute, event, guard)


def solve(d):
	events = []

	for data in d:
		events.append(parse_data(data))

	events.sort()

	guards = defaultdict(list)
	active = -1
	last_time = 0

	for year, month, day, hour, minute, event, guard in events:
		if event == 0:
			active = guard
			last_time = 0
		if event == 1:
			last_time = minute
		if event == 2:
			for x in range(last_time, minute):
				guards[active].append(x)

	most = -1
	answer = -1

	for guard, minutes in guards.items():		
		c = Counter(minutes)
		candidate, count = c.most_common(1)[0]
		if count > most:
			most = count
			answer = guard * candidate

	return answer

def read_and_solve():
	with open('input_4.txt') as f:
		data = [line.rstrip() for line in f]
		return solve(data)

if __name__ == '__main__':
	print(read_and_solve())