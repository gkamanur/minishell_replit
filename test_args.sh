#!/bin/bash
echo "Number of args: $#"
for i in $(seq 1 $#); do
    echo "Arg $i: '${!i}'"
done
