#!/bin/bash

function getXSIType(){

XSITYPE=""

if [[ $1 == MQCA ]]
then 
 XSITYPE="xsi:string" 
fi

if [[ $1 ==  MQIA ]]
then 
 XSITYPE="xsi:integer"
fi

if [[ $1 == MQCACH ]]
then 
 XSITYPE="xsi:string" 
fi

if [[ $1 ==  MQIACH ]]
then 
 XSITYPE="xsi:integer"
fi

if [[ $1 == MQCACF ]]
then 
 XSITYPE="xsi:string" 
fi

if [[ $1 ==  MQIACF ]]
then 
 XSITYPE="xsi:integer"
fi


if [[ $2 == MQIA_Q_TYPE || \
 $2 == MQIACH_CHANNEL_TYPE || \
 $2 == MQIACH_CHANNEL_STATUS ]]
then
 XSITYPE="xsi:string" 
fi

}

while read i 
do
ii=${i,,}
a=$(echo $i | tr _ ' ' | cut -d' ' -f1)
b=$(echo $ii | tr _ ' ' | cut -d' ' -f2)
c=$(echo $ii | tr _ ' ' | cut -d' ' -f3)
d=$(echo $ii | tr _ ' ' | cut -d' ' -f4)
e=$(echo $ii | tr _ ' ' | cut -d' ' -f5)
f=$(echo $ii | tr _ ' ' | cut -d' ' -f6)

b=${b^}
c=${c^}
d=${d^}
e=${e^}
f=${f^}
s=${b}${c}${d}${e}${f}
getXSIType $a $i

if [[ $s != 'First' && $s != 'LastUsed' ]]
then
echo '			<xsi:element name="'$s'" type="'${XSITYPE}'" minOccurs="0" maxOccurs="1" />'
fi

done

