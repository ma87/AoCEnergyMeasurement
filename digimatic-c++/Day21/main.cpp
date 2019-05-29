// Advent of Code 2018
// Peter Westerström (digimatic)

#include "config.h"

#include <common/common.h>

#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>

using namespace westerstrom;
using namespace std;

using IntList = vector<int>;
using Registers = IntList;
using Instruction = IntList;

enum Opcode : int
{
	addr,
	addi,
	mulr,
	muli,
	banr,
	bani,
	borr,
	bori,
	setr,
	seti,
	gtir,
	gtri,
	gtrr,
	eqir,
	eqri,
	eqrr
};

unordered_map<string, Opcode> opmap = {
    {"addr", addr}, {"addi", addi}, {"mulr", mulr}, {"muli", muli}, {"banr", banr}, {"bani", bani},
    {"borr", borr}, {"bori", bori}, {"setr", setr}, {"seti", seti}, {"gtir", gtir}, {"gtri", gtri},
    {"gtrr", gtrr}, {"eqir", eqir}, {"eqri", eqri}, {"eqrr", eqrr}};

struct Program
{
	Registers r{0, 0, 0, 0, 0, 0};
	vector<Instruction> i;
	int ipr{0};
	int ip{0};
};

Program parseProgram(const vector<string>& lines)
{
	Program p;
	int i;
	for(i = 0; i < lines.size(); i++)
	{
		auto s = lines[i];
		auto nums = splitNumbers(s);
		if(s.substr(0, 3) == "#ip")
		{
			p.ipr = nums[1];
		} else
		{
			Instruction i(4);
			auto instrstr = s.substr(0, 4);
			i[0] = opmap[instrstr];
			i[1] = nums[1];
			i[2] = nums[2];
			i[3] = nums[3];
			p.i.push_back(i);
		}
	}
	return p;
}

void execute(const Instruction& i, Registers& r)
{
	auto op = i[0];
	auto a = i[1];
	auto b = i[2];
	auto c = i[3];
	switch(op)
	{
		case addr:
			r[c] = r[a] + r[b];
			break;
		case addi:
			r[c] = r[a] + b;
			break;
		case mulr:
			r[c] = r[a] * r[b];
			break;
		case muli:
			r[c] = r[a] * b;
			break;
		case banr:
			r[c] = r[a] & r[b];
			break;
		case bani:
			r[c] = r[a] & b;
			break;
		case borr:
			r[c] = r[a] | r[b];
			break;
		case bori:
			r[c] = r[a] | b;
			break;
		case setr:
			r[c] = r[a];
			break;
		case seti:
			r[c] = a;
			break;
		case gtir:
			r[c] = a > r[b] ? 1 : 0;
			break;
		case gtri:
			r[c] = r[a] > b ? 1 : 0;
			break;
		case gtrr:
			r[c] = r[a] > r[b] ? 1 : 0;
			break;
		case eqir:
			r[c] = a == r[b] ? 1 : 0;
			break;
		case eqri:
			r[c] = r[a] == b ? 1 : 0;
			break;
		case eqrr:
			r[c] = r[a] == r[b] ? 1 : 0;
			break;
		default:
			break;
	}
}

void printReg(Program& p)
{
	cout << "[";
	for(int i = 0; i < 6; i++)
	{
		cout << p.r[i];
		if(i != 5)
			cout << ", ";
	}
	cout << "] ";
}

void printInstr(Program& p)
{
	auto ip = p.r[p.ipr];
	auto& instr = p.i[ip];
	auto opcode = instr[0];
	auto it = find_if(begin(opmap), end(opmap), [opcode](auto&& i) { return i.second == opcode; });
	cout << it->first << " " << instr[1] << " " << instr[2] << " " << instr[3] << " ";
}

int run(Program p, bool verbose = false)
{
	bool firstLoop = true;
	unordered_multiset<int> seenNumbers;
	int previousNumber = -1;
	while(p.r[p.ipr] >= 0 && p.r[p.ipr] < p.i.size())
	{
		auto ip = p.r[p.ipr];

		if(verbose)
		{
			cout << "ip=" << ip << " : ";
			printReg(p);
			printInstr(p);
		}
		if(ip == 29) // this is the where exit condition is. exit condition is r[1] == r[0]
		{
			if(firstLoop)
			{
				cout << dayName << " - part 1: " << p.r[1] << endl;
				assert(10332277 == p.r[1]);
				firstLoop = false;
			} else if(seenNumbers.find(p.r[1]) != seenNumbers.end())
			{
				cout << dayName << " - part 2: " << previousNumber << endl;
				assert(previousNumber == 13846724);
				return true;
			}
			previousNumber = p.r[1];
			seenNumbers.insert(p.r[1]);
		}

		execute(p.i[ip], p.r);

		if((p.r[p.ipr] + 1 < 0) || (p.r[p.ipr] + 1) >= p.i.size())
			break;

		if(verbose)
		{
			printReg(p);
			cout << endl;
		}

		p.r[p.ipr]++;
	}
	return false;
}

int main()
{
	auto p = parseProgram(readLines(string(inputFile)));
	if(!run(p))
	{
		cout << "ERROR No solution found for part 2." << endl;
	}
	return 0;
}
