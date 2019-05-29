﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace day16
{
    public struct InstructionBits
    {
        public int opcode;
        public int input1;
        public int input2;
        public int output;

        public InstructionBits(int op, int i1, int i2, int u)
        {
            opcode = op;
            input1 = i1;
            input2 = i2;
            output = u;
        }
        public int A
        {
            get { return input1; }
        }
        public int B
        {
            get { return input2; }
        }
        public int C
        {
            get { return output; }
        }
    }

    public struct Memory
    {
        public int addr0;
        public int addr1;
        public int addr2;
        public int addr3;

        public Memory(int a0, int a1, int a2, int a3)
        {
            addr0 = a0;
            addr1 = a1;
            addr2 = a2;
            addr3 = a3;
        }
        public Memory(Memory m)
        {
            this = new Memory(m.addr0, m.addr1, m.addr2, m.addr3);
        }
        public int this[int key]
        {
            get
            {
                switch (key)
                {
                    case 0: return addr0;
                    case 1: return addr1;
                    case 2: return addr2;
                    case 3: return addr3;
                    default: throw new ArgumentOutOfRangeException();
                }
            }
            set
            {
                switch (key)
                {
                    case 0: addr0 = value; break;
                    case 1: addr1 = value; break;
                    case 2: addr2 = value; break;
                    case 3: addr3 = value; break;
                    default: throw new ArgumentOutOfRangeException();
                }
            }
        }
        public override bool Equals(Object obj)
        {
            return obj is Memory && Equals((Memory)obj);
        }
        public bool Equals(Memory m)
        {
            return (addr0 == m.addr0) && (addr1 == m.addr1) && (addr2 == m.addr2) && (addr3 == m.addr3);
        }
        public override int GetHashCode()
        {
            var hashCode = -2057292590;
            hashCode = hashCode * -1521134295 + base.GetHashCode();
            hashCode = hashCode * -1521134295 + addr0.GetHashCode();
            hashCode = hashCode * -1521134295 + addr1.GetHashCode();
            hashCode = hashCode * -1521134295 + addr2.GetHashCode();
            hashCode = hashCode * -1521134295 + addr3.GetHashCode();
            return hashCode;
        }
        public static bool operator ==(Memory m1, Memory m2)
        {
            return m1.Equals(m2);
        }
        public static bool operator !=(Memory m1, Memory m2)
        {
            return !m1.Equals(m2);
        }
    }

    public struct Execution
    {
        public Memory before;
        public Memory after;
        public InstructionBits instruction;
    }

    public abstract class Instruction
    {
        private int opcode;
        public Instruction(int op)
        {
            opcode = op;
        }
        public int Opcode
        {
            get
            {
                return opcode;
            }
        }
        public abstract void Execute(InstructionBits i, ref Memory m);
    }

    // ---------------------------------------------------------------------
    public class Addr : Instruction
    {
        public Addr(int op) : base(op) {}
        public override void Execute(InstructionBits i, ref Memory m)
        {
            m[i.C] = m[i.A] + m[i.B];
        }
    }
    public class Addi : Instruction
    {
        public Addi(int op) : base(op) { }
        public override void Execute(InstructionBits i, ref Memory m)
        {
            m[i.C] = m[i.A] + i.B;
        }
    }

    public class Mulr : Instruction
    {
        public Mulr(int op) : base(op) { }
        public override void Execute(InstructionBits i, ref Memory m)
        {
            m[i.C] = m[i.A] * m[i.B];
        }
    }
    public class Muli : Instruction
    {
        public Muli(int op) : base(op) { }
        public override void Execute(InstructionBits i, ref Memory m)
        {
            m[i.C] = m[i.A] * i.B;
        }
    }

    public class Banr : Instruction
    {
        public Banr(int op) : base(op) { }
        public override void Execute(InstructionBits i, ref Memory m)
        {
            m[i.C] = m[i.A] & m[i.B];
        }
    }
    public class Bani : Instruction
    {
        public Bani(int op) : base(op) { }
        public override void Execute(InstructionBits i, ref Memory m)
        {
            m[i.C] = m[i.A] & i.B;
        }
    }

    public class Borr : Instruction
    {
        public Borr(int op) : base(op) { }
        public override void Execute(InstructionBits i, ref Memory m)
        {
            m[i.C] = m[i.A] | m[i.B];
        }
    }
    public class Bori : Instruction
    {
        public Bori(int op) : base(op) { }
        public override void Execute(InstructionBits i, ref Memory m)
        {
            m[i.C] = m[i.A] | i.B;
        }
    }

    public class Setr : Instruction
    {
        public Setr(int op) : base(op) { }
        public override void Execute(InstructionBits i, ref Memory m)
        {
            m[i.C] = m[i.A];
        }
    }
    public class Seti : Instruction
    {
        public Seti(int op) : base(op) { }
        public override void Execute(InstructionBits i, ref Memory m)
        {
            m[i.C] = i.A;
        }
    }

    public class Gtir : Instruction
    {
        public Gtir(int op) : base(op) { }
        public override void Execute(InstructionBits i, ref Memory m)
        {
            m[i.C] = (i.A > m[i.B]) ? 1 : 0;
        }
    }
    public class Gtri : Instruction
    {
        public Gtri(int op) : base(op) { }
        public override void Execute(InstructionBits i, ref Memory m)
        {
            m[i.C] = (m[i.A] > i.B) ? 1 : 0;
        }
    }
    public class Gtrr : Instruction
    {
        public Gtrr(int op) : base(op) { }
        public override void Execute(InstructionBits i, ref Memory m)
        {
            m[i.C] = (m[i.A] > m[i.B]) ? 1 : 0;
        }
    }

    public class Eqir : Instruction
    {
        public Eqir(int op) : base(op) { }
        public override void Execute(InstructionBits i, ref Memory m)
        {
            m[i.C] = (i.A == m[i.B]) ? 1 : 0;
        }
    }
    public class Eqri : Instruction
    {
        public Eqri(int op) : base(op) { }
        public override void Execute(InstructionBits i, ref Memory m)
        {
            m[i.C] = (m[i.A] == i.B) ? 1 : 0;
        }
    }
    public class Eqrr : Instruction
    {
        public Eqrr(int op) : base(op) { }
        public override void Execute(InstructionBits i, ref Memory m)
        {
            m[i.C] = (m[i.A] == m[i.B]) ? 1 : 0;
        }
    }


    // ---------------------------------------------------------------------
    class Day16
    {
        static List<Execution> ReadInput1()
        {
            List<Execution> executions = new List<Execution>();
            string path = Path.Combine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location), @"..\..\input.txt");
            StreamReader reader = File.OpenText(path);
            Regex regex1 = new Regex(@"^Before: \[(\d+), (\d+), (\d+), (\d+)\]");
            Regex regex2 = new Regex(@"^(\d+) (\d+) (\d+) (\d+)");
            Regex regex3 = new Regex(@"^After:  \[(\d+), (\d+), (\d+), (\d+)\]");
            string line;
            while ((line = reader.ReadLine()) != null)
            {
                MatchCollection matches1 = regex1.Matches(line);
                if (matches1.Count > 0)
                {
                    GroupCollection groups1 = matches1[0].Groups;
                    Execution e = new Execution();
                    int i = 1;
                    e.before = new Memory(int.Parse(groups1[i++].Value), int.Parse(groups1[i++].Value), int.Parse(groups1[i++].Value), int.Parse(groups1[i++].Value));
                    line = reader.ReadLine();
                    MatchCollection matches2 = regex2.Matches(line);
                    if (matches2.Count > 0)
                    {
                        GroupCollection groups2 = matches2[0].Groups;
                        int j = 1;
                        e.instruction = new InstructionBits(int.Parse(groups2[j++].Value), int.Parse(groups2[j++].Value), int.Parse(groups2[j++].Value), int.Parse(groups2[j++].Value));
                        line = reader.ReadLine();
                        MatchCollection matches3 = regex3.Matches(line);
                        if (matches3.Count > 0)
                        {
                            GroupCollection groups3 = matches3[0].Groups;
                            int k = 1;
                            e.after = new Memory(int.Parse(groups3[k++].Value), int.Parse(groups3[k++].Value), int.Parse(groups3[k++].Value), int.Parse(groups3[k++].Value));
                            executions.Add(e);
                        }
                    }
                }
            }
            return executions;
        }

        static List<InstructionBits> ReadInput2()
        {
            List<InstructionBits> instructions = new List<InstructionBits>();
            string path = Path.Combine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location), @"..\..\input.txt");
            StreamReader reader = File.OpenText(path);
            string line;
            bool lastEmpty = false;
            bool thisEmpty = false;
            while (!lastEmpty || !thisEmpty)
            {
                if ((line = reader.ReadLine()) != null)
                {
                    lastEmpty = thisEmpty;
                    thisEmpty = line.Length == 0;
                }
            }
            Regex regex = new Regex(@"^(\d+) (\d+) (\d+) (\d+)");
            while ((line = reader.ReadLine()) != null)
            {
                MatchCollection matches = regex.Matches(line);
                if (matches.Count > 0)
                {
                    GroupCollection groups = matches[0].Groups;
                    int i = 1;
                    InstructionBits bits = new InstructionBits(int.Parse(groups[i++].Value), int.Parse(groups[i++].Value), int.Parse(groups[i++].Value), int.Parse(groups[i++].Value));
                    instructions.Add(bits);
                }
            }
            return instructions;
        }

        static public readonly List<Instruction> executableInstructions = new List<Instruction>
        {
            new Addr(4),
            new Addi(9),
            new Mulr(11),
            new Muli(13),
            new Banr(8),
            new Bani(15),
            new Borr(1),
            new Bori(12),
            new Setr(10),
            new Seti(5),
            new Gtir(2),
            new Gtri(7),
            new Gtrr(0),
            new Eqir(14),
            new Eqri(3),
            new Eqrr(6),
        };

        static void PartA()
        {
            List<Execution> executions = ReadInput1();
            int matchingSamples = 0;
            foreach (Execution e in executions)
            {
                int matches = 0;
                foreach (Instruction exe in executableInstructions)
                {
                    Memory outMem = new Memory(e.before);
                    exe.Execute(e.instruction, ref outMem);
                    if (outMem == e.after)
                    {
                        matches++;
                    }
                }
                if (matches >= 3)
                {
                    matchingSamples++;
                }
            }
            Console.WriteLine("Part A: Result is " + matchingSamples + ".");
        }

        static void PartB1()
        {
            List<Execution> executions = ReadInput1();

            foreach (Execution e in executions)
            {
                List<Tuple<Execution, Instruction>> matches = new List<Tuple<Execution, Instruction>>();
                foreach (Instruction exe in executableInstructions)
                {
                    Memory outMem = new Memory(e.before);
                    exe.Execute(e.instruction, ref outMem);
                    if ((outMem == e.after) && (exe.Opcode < 0))
                    {
                        matches.Add(Tuple.Create(e, exe));
                    }
                }
                if (matches.Count == 1)
                {
                    Console.Write("Opcode " + matches[0].Item1.instruction.opcode + " are: ");
                    foreach (Tuple<Execution, Instruction> t in matches)
                    {
                        Console.Write(t.Item2.GetType().Name + ", ");
                    }
                    Console.WriteLine();
                }
            }
        }

        static void PartB2()
        {
            Dictionary<int, Instruction> instructions = new Dictionary<int, Instruction>();
            foreach (Instruction i in executableInstructions)
            {
                instructions[i.Opcode] = i;
            }
            List<InstructionBits> testProgram = ReadInput2();
            Memory memory = new Memory();
            foreach (InstructionBits bits in testProgram)
            {
                instructions[bits.opcode].Execute(bits, ref memory);
            }
            Console.WriteLine("Part B: Result is " + memory[0] + ".");
        }

        static void Main(string[] args)
        {
            Console.WriteLine("AoC 2018 - " + typeof(Day16).Namespace + ":");
            PartA();
            PartB1();
            PartB2();
        }
    }
}
