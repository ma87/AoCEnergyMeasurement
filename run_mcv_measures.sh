#!/bin/bash

## HELPER
show_help()
{
  echo "usage: ./run_mcv_measures.sh [-b] -p path_to_mcv_energy_folder [-d 1,4] [-l python3] [-u ma87] [-y 2018]"
}

## global variables

verbose=0
forced_user=""
forced_language=""
forced_days=""
USER=""
year="2018"
forced_option=0
path_mcv_energy="../mcv_energy_measurement"
use_battery_measurement=0
number_iterations=10
sleep_time=10

## Parse arguments

while getopts "h?bvs:i:u:d:l:p:y:" opt; do
    case "$opt" in
    h|\?)
        show_help
        exit 0
        ;;
    v)  verbose=1
        ;;
    y)  year=$OPTARG
        ;;
    u)  forced_user=$OPTARG
        ;;
    i)  number_iterations=$OPTARG
        ;;
    s)  sleep_time=$OPTARG
        ;;
    d)  forced_days=$OPTARG
        ;;
    l)  forced_language=$OPTARG
        ;;
    p)  path_mcv_energy=$OPTARG
        ;;
    b)  use_battery_measurement=1
        ;;
    esac
done


## Init variables

root_dir=$(pwd)/$year
results_filename="$root_dir/$(date +%Y%m%d%H%M%S)_measure_${year}_${forced_user}_${forced_language}.csv" 
CPU_MODEL_NAME="\"$( lscpu | grep "Model name:" | sed -r 's/Model name:\s{1,}//g' )\""

source "$path_mcv_energy"/measure_energy.sh

cd $root_dir

for p in $(find . -name Info.txt) ; do
  cd $(dirname $p)
  LANGUAGE=$(grep "^LANGUAGE=" Info.txt | cut -d'=' -f2-)
  USER=$(grep "^USER=" Info.txt | cut -d'=' -f2-)
  DAYS=$(grep "^DAYS=" Info.txt | cut -d'=' -f2-)
  LIST_DAYS=$(echo $DAYS | cut -d',' --output-delimiter=$'\n' -f1-)

  if [[ -z $forced_user || $forced_user == $USER ]]; then
    if [[ -z $forced_language || $forced_language == $LANGUAGE ]]; then
      if [[ ! -z $forced_days ]]; then
        LIST_FORCED_DAYS=$(echo $forced_days | cut -d',' --output-delimiter=$'\n' -f1-)
        TESTED_DAYS=()
        for available_day in ${LIST_DAYS[@]}
        do
          for tested_day in ${LIST_FORCED_DAYS[@]}
          do
              if [[ $available_day -eq $tested_day ]]; then
                TESTED_DAYS+=( "$tested_day" )
              fi
          done
        done
      else
        TESTED_DAYS=$LIST_DAYS
      fi

      keys=("USER" "LANGUAGE" "DAY" "CPU_MODEL_NAME")
      for DAY in ${TESTED_DAYS[@]} ; do
        ./build.sh $DAY > /dev/null 2>&1
        cannot_build=$?

        if [[ "$cannot_build" -eq "0" ]]; then
          if [[ $verbose -eq "1" ]]; then
            echo "Measuring project file = $p USER = $USER LANGUAGE = $LANGUAGE DAY = $DAY"
          fi
          for (( u=0; u<${number_iterations}; u++ )) ; do
            measure_energy $use_battery_measurement $results_filename "./run.sh $DAY" $keys
            sleep $sleep_time
          done
        fi
      done
    fi
  fi

  cd $root_dir
done

