var tools = require('./tools.js')

function add(mem, input_1, input_2, output)
{
  mem[output] = mem[input_1] + mem[input_2];
}

function mul(mem, input_1, input_2, output)
{
  mem[output] = mem[input_1] * mem[input_2];
}

function exe(mem)
{
  var i;
  for (i = 0 ; i < mem.length ; i+=4)
  {
    if (mem[i] >= 99 || mem[i] < 1 ) 
    {
      break;
    }
    var operator;
    switch(mem[i]) 
    {
      case 1:
        operator = add;
        break;
      case 2:
        operator = mul
        break;
    }
    if (operator)
    {
       operator(mem, mem[i+1], mem[i+2], mem[i+3]);
    }
  }
}

if (process.argv.length >= 3)
{
  program = tools.parseInput(process.argv[2], l => l.split(",").map(op => parseInt(op)));
  mem = program[0];
  stored_mem = mem.slice();
  mem[1] = 12;
  mem[2] = 2;
  exe(mem);

  console.log(mem[0]);

  var noun = 0;
  var verb = 0;

  for (noun = 0 ; noun < 99 ; noun++)
  {
    for (verb = 0 ; verb < 99 ; verb++)
    {
      mem = stored_mem.slice();
      mem[1] = noun;
      mem[2] = verb;
      exe(mem);
      
      if (mem[0] == 19690720)
      {
         console.log(100 * noun + verb);
         return;
      }
    }
  }
}

