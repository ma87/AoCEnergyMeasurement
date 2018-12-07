import sys
import re

class Step():
    def __init__(self, id):
        self.id = id
        self.steps = []
        self.is_done = False
        self.is_being_processed = False
        self.time_build = 61 + (ord(id) - ord('A'))

    def is_ready(self):
        if not self.is_done:
            for s in self.steps:
                if not s.is_done:
                    return False
            return True
        else:
            return False

    def process(self):
        self.time_build = self.time_build - 1
        if self.time_build == 0:
            self.is_done = True

        return self.is_done

def get_order(steps):
    counter_ready = len(steps.keys())
    order = []
    while counter_ready:
        ready_steps = [s.id for s in steps.values() if s.is_ready()]
        if len(ready_steps) == 0:
            print("can't find a ready step, problem")
            exit(1)
        if len(ready_steps) > 1:
            ready_steps.sort()

        steps[ready_steps[0]].is_done = True
        counter_ready -= 1
        order.append(ready_steps[0])
    return "".join(order)

class Worker():
    def __init__(self):
        self.is_busy = False
        self.current_step = '?'

    def assign(self, step):
        self.current_step = step
        self.is_busy = True

def is_worker_available(workers):
    for i, w in enumerate(workers):
        if not w.is_busy:
            return i
    return -1

def get_multiple_order(steps, number_workers):
    time_elapsed = 0
    all_steps_finished = False
    workers = [Worker() for i in range(number_workers)]
    while not all_steps_finished:
        # Find a step if a worker is available
        if is_worker_available(workers) >= 0:
            ready_steps = [s.id for s in steps.values() if s.is_ready()]
            if len(ready_steps) > 0:
                if len(ready_steps) > 1:
                    ready_steps.sort()
                assigned_steps = 0
                while assigned_steps < len(ready_steps):
                    index_free_worker = is_worker_available(workers)
                    if index_free_worker == -1:
                        break
                    if not steps[ready_steps[assigned_steps]].is_being_processed:
                        workers[index_free_worker].assign(ready_steps[assigned_steps])
                        steps[ready_steps[assigned_steps]].is_being_processed = True
                    assigned_steps += 1

        # Process current steps
        for w in workers:
            if w.is_busy:
                if steps[w.current_step].process():
                    w.is_busy = False
                    w.current_step = '?'

        all_steps_finished = True
        for s in steps:
            if not steps[s].is_done:
                all_steps_finished = False

        time_elapsed += 1

    return str(time_elapsed)

filename = sys.argv[1]
steps = {}
step_reg_exp = re.compile(r'Step (\w+) must be finished before step (\w+) can begin.')
with open(filename, 'r') as f:
    for line in f.readlines():
        dep_step, step = tuple(step_reg_exp.match(line).groups())
        if step not in steps:
            steps[step] = Step(step)
        if dep_step not in steps:
            steps[dep_step] = Step(dep_step)
        steps[step].steps.append(steps[dep_step])

print("solution 1 = " + get_order(steps))
for s in steps:
    steps[s].is_done = False
print("solution 2 = " + get_multiple_order(steps, 5))
