#!/bin/bash

memsize=15
echo "Your memsize is $memsize"
echo -n "Enter page size: "
read pagesize

nofpage=$((memsize/pagesize))

for ((i=0; i<nofpage; i++))
do
  echo -n "Enter the frame of page $((i+1)): "
  read p[i]
done

choice=1
while [ $choice -eq 1 ]
do
  echo -n "Enter a logical address: "
  read logadd
  frameno=$((logadd/pagesize))
  offset=$((logadd%pagesize))
  phyadd=$((p[frameno]*pagesize+offset))
  echo "Physical address is: $phyadd"
  echo "........................................"
  echo -n "Do you want to continue(1/0)?: "
  read choice
done
