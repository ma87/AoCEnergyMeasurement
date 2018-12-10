#!/bin/bash

root_dir=$(pwd)
output_folder="$root_dir/output"

if [[ ! -d $output_folder ]]; then
  mkdir $output_folder
fi

for year in */ ; do
    cd $year/
    for project in */ ; do
      if [[ -d $project ]]; then
        pushd $project
        if [[ -f "Info.txt" ]]; then
          LANGUAGE=$(grep "^LANGUAGE=" Info.txt | cut -d'=' -f2-)
          USER=$(grep "^USER=" Info.txt | cut -d'=' -f2-)
          DAYS=$(grep "^DAYS=" Info.txt | cut -d'=' -f2-)
          LIST_DAYS=$(echo $DAYS | cut -d',' --output-delimiter=$'\n' -f1-)
          HASH_COMMIT=$(git log -n 1 --pretty=format:%h -- .)
          TIME_COMMIT=$(git log -n 1 --pretty=format:%ai -- .)
          for day in $LIST_DAYS ; do
            ./build.sh $day > /dev/null 2>&1
            cannot_build=$?
            if [[ "$cannot_build" -eq "0" ]]; then
              echo '"'"$HASH_COMMIT"'"','"'"$TIME_COMMIT"'"','"'"$USER"'"','"'"$LANGUAGE"'"',"$year","$day","$(taskset -c 0 energy_measurement ./run.sh $day)" >> $output_folder/measures.csv
            fi
          done
        fi
        popd
      fi
    done
    cd $root_dir
done
