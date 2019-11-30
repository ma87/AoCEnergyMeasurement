# AoCEnergyMeasurement

Energy measurement for solutions of Advent of Code

The objective is to compare the energy consumption of solutions in different programming languages for the same problem. The repo containing energy measurement toolkit is available [here](https://github.com/ma87/mcv_energy_measurement);

Workflow of AoCEnergyMeasurement is as follows:

1. Checkout AoCEnergyMeasurement repo
2. Install dependencies of projects you want to measure
3. Run run\_mcv\_energy\_measures.sh script with options to select what you want to measure (Other bash scripts are deprecated).
4. A csv file containing USER,PROGRAMMING\_LANGUAGE,YEAR,DAY,ENERGY\_CONSUMED,TIME\_ELAPSED value for each solution

If you want to participate, push a folder in the corresponding year folder. Your folder has to contain:

- Info.txt: set value for USER, LANGUAGE and DAY. Example here:
DAYS=1,3,4,5,6,7,8,9,10,11
LANGUAGE=C++
USER=ma87

- build.sh: script is run to build the solution. Day is given in argument.

- run.sh: script to run the solution. Day is given in argument.

Happy coding !
