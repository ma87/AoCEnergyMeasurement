var tools = require('./tools.js')

var cacheFuels = {};
function computeFuel2(fuel)
{
	var str_fuel = fuel.toString();
	if (!(str_fuel in cacheFuels))
	{
		var current_fuel = computeFuel(fuel);
		if (current_fuel <= 0)
		{
			cacheFuels[str_fuel] = 0;
		}
		else
		{
			var next_fuel = computeFuel2(current_fuel);
			cacheFuels[str_fuel] = current_fuel + next_fuel;
		}
	}
	return cacheFuels[str_fuel];
}
function computeFuel(mass)
{
	return Math.floor(mass / 3) - 2;
}

function part1(masses) {
	return masses.reduce((acc, val) => acc + computeFuel(val));
}
function sum_list(masses) {
	return masses.reduce((acc, val) => acc + val);
}

function part2(masses) {
	return masses.reduce((acc, val) => acc + computeFuel2(val));
}

if (process.argv.length >= 3)
{
	masses = tools.parseInput(process.argv[2], n => parseInt(n));
	fuels = masses.map(n => computeFuel(n));
	console.log(sum_list(fuels));
	
	fuel_requirements = masses.map(n => computeFuel2(n));
	console.log(sum_list(fuel_requirements));
}

