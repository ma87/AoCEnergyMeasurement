# AoCEnergyMeasurement
Energy measurement for solutions of Advent of Code

The objective is to compare the energy consumption of solutions in different programming languages for the same problem.Energy measurement framwork is based on this [repo](https://github.com/greensoftwarelab/Energy-Languages)

Workflow of AoCEnergyMeasurement is as follows:

1. Checkout AoCEnergyMeasurement repo
2. Create a docker container that will checkout repo https://github.com/ma87/KulKod that contains an executable to measure energy consumption of an executable
3. Traverse all solutions of advent of code and measure energy
4. Compute a csv file containing COMMIT_HASH,DATE,USER,PROGRAMMING_LANGUAGE,YEAR,DAY,ENERGY_CONSUMED,TIME_ELAPSED value for each solution

If you want to participate, push a folder in the corresponding year folder. Your folder has to contain:

- Info.txt: set value for USER, LANGUAGE and DAY. Example here:
DAYS=1,3,4,5,6,7,8,9,10,11
LANGUAGE=C++
USER=ma87

- build.sh: script is run by docker container to build the solution. Day is given in argument.

- run.sh: script to run the solution. Day is given in argument.

And then, you might have dependencies to run the solution. Edit Dockerfile to support them or ask for support.

Happy coding !
