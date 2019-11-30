from aocbase import readInput
import re
from collections import deque

inp = readInput()
p = re.compile(r"(\w+) (\d+) (\d+) (\d+)")

def doAddr(inst, reg):
    reg[inst[3]] = reg[inst[1]] + reg[inst[2]]

def doAddi(inst, reg):
    reg[inst[3]] = reg[inst[1]] + inst[2]

def doMulr(inst, reg):
    reg[inst[3]] = reg[inst[1]] * reg[inst[2]]

def doMuli(inst, reg):
    reg[inst[3]] = reg[inst[1]] * inst[2]

def doBanr(inst, reg):
    reg[inst[3]] = reg[inst[1]] & reg[inst[2]]

def doBani(inst, reg):
    reg[inst[3]] = reg[inst[1]] & inst[2]

def doBorr(inst, reg):
    reg[inst[3]] = reg[inst[1]] | reg[inst[2]]

def doBori(inst, reg):
    reg[inst[3]] = reg[inst[1]] | inst[2]

def doSetr(inst, reg):
    reg[inst[3]] = reg[inst[1]]

def doSeti(inst, reg):
    reg[inst[3]] = inst[1]

def doGtir(inst, reg):
    if inst[1] > reg[inst[2]]:
        reg[inst[3]] = 1
    else:
        reg[inst[3]] = 0

def doGtri(inst, reg):
    if reg[inst[1]] > inst[2]:
        reg[inst[3]] = 1
    else:
        reg[inst[3]] = 0

def doGtrr(inst, reg):
    if reg[inst[1]] > reg[inst[2]]:
        reg[inst[3]] = 1
    else:
        reg[inst[3]] = 0

def doEqir(inst, reg):
    if inst[1] == reg[inst[2]]:
        reg[inst[3]] = 1
    else:
        reg[inst[3]] = 0

def doEqri(inst, reg):
    if reg[inst[1]] == inst[2]:
        reg[inst[3]] = 1
    else:
        reg[inst[3]] = 0

def doEqrr(inst, reg):
    if reg[inst[1]] == reg[inst[2]]:
        reg[inst[3]] = 1
    else:
        reg[inst[3]] = 0

def parse(s):
    l = []
    for line in s.splitlines():
        m = p.match(line)
        if m:
            funcName = "do"+m.group(1)[0].upper()+m.group(1)[1:]
            l.append([globals()[funcName]] + list(map(int, m.groups()[1:])))
        else:
            if line[0]=='#':
                ip = int(line[4])
            else:
                print("Error:"+line)
    return l, ip

def run(ip, prog, reg=[0]*6):
    debug =  reg[0]>0
    while True:
        instr = prog[reg[ip]]
        instr[0](instr, reg)
        reg[ip] += 1
        if reg[ip] == 1:
            return max(reg)
        if reg[ip] < 0 or reg[ip] >= len(prog):
            break

def calcResult(n):
    i = 1
    sm = 0
    while i*i <= n:
        if n % i == 0:
            if i*i != n:
                sm += i
                sm += n//i
            else:
                sm += i
        i += 1
    return sm

instr, ip = parse(inp)

print("Solution to day 19 part 1:",calcResult(run(ip, instr)))
print("Solution to day 19 part 2:",calcResult(run(ip, instr, [1, 0, 0, 0, 0, 0])))
