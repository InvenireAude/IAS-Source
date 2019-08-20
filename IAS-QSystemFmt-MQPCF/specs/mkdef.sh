#!/bin/bash

cut -d' ' -f3 |\
while read i 
do

ii=${i,,}
a=$(echo $ii | tr _ ' ' | cut -d' ' -f2)
b=$(echo $ii | tr _ ' ' | cut -d' ' -f3)
c=$(echo $ii | tr _ ' ' | cut -d' ' -f4)
d=$(echo $ii | tr _ ' ' | cut -d' ' -f5)
e=$(echo $ii | tr _ ' ' | cut -d' ' -f6)
f=$(echo $ii | tr _ ' ' | cut -d' ' -f6)
a=${a^}
b=${b^}
c=${c^}
d=${d^}
e=${e^}
f=${f^}
s=${a}${b}${c}${d}${e}${f}
echo hmParameterID2Name\[${i}\]=\"${s}\"\;
done

