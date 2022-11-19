#!/bin/sh

# Usage message
if [ $# -eq 0 ]
then
  echo "Usage: $0 <directory data>";
exit 1;
fi

DIR="$1"
echo "$s"
#N="$(echo "$DIR"| cut -d'-' -f3)"
N="$(cat $DIR/input.txt | grep -oP "Particles_Num\s+\K\w+")"
steps="$(cat $DIR/input.txt | grep -oP "N_Samplings\s+\K\w+")"
radius="$(cat $DIR/input.txt | grep -oP "Potential_Sigma\s+\K\w+")"


gnuplot -e "dir='$DIR'" -c dinamica3.gnuplot $N $steps $radius
