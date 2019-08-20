#!/bin/bash


function getXSIType(){

XSITYPE=""

if [ $1 == MQCFST ]
then 
 XSITYPE="xsi:string" 
 XSIMAX="1"
fi

if [ $1 == MQCFBS ]
then 
 XSITYPE="xsi:string" 
 XSIMAX="1"
fi

if [[ $1 ==  MQCFIN64 || $1 ==  MQCFIN ]]
then 
 XSITYPE="xsi:integer"
 XSIMAX="1"
fi

if [[ $1 ==  MQCFIL64 || $1 ==  MQCFIL ]]
then 
 XSITYPE="xsi:integer"
 XSIMAX="unbounded"
fi
}


cat <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<xsi:schema 
 xmlns:xsi="http://www.w3.org/2001/XMLSchema" 
 targetNamespace="http://www.invenireaude.com/qsystem/fmt/pcf/stats"
 xmlns="http://www.invenireaude.com/qsystem/fmt/pcf"
 xmlns:cmd="http://www.invenireaude.com/qsystem/fmt/pcf/stats">
 	
  <xsi:complexType name="Statistics">  		 
    	<xsi:sequence>
   			<xsi:element name="queueManager"       type="xsi:string"  minOccurs="0" maxOccurs="1" />
  			<xsi:element name="intervalStartDate"  type="xsi:date"    minOccurs="0" maxOccurs="1" />
  			<xsi:element name="intervalStartTime"  type="xsi:time"    minOccurs="0" maxOccurs="1" />
  			<xsi:element name="intervalEndDate"    type="xsi:date"    minOccurs="0" maxOccurs="1" />
  			<xsi:element name="intervalEndTime"    type="xsi:time"    minOccurs="0" maxOccurs="1" />  			
  			<xsi:element name="commandLevel"       type="xsi:string"  minOccurs="0" maxOccurs="1" />  			
  		</xsi:sequence>	 	  		
  </xsi:complexType>
EOF

for f in $* 
do
fbase=$(basename $f)

cat <<EOF
  
 <xsi:complexType name="${fbase/.txt/}">  		
 	<xsi:sequence>
EOF

while read n i t o ;
do 

#n="$(tr '[:upper:]' '[:lower:]' <<< ${n:0:1})${n:1}"

getXSIType $t
echo '			<xsi:element name="'$n'" type="'${XSITYPE}'" minOccurs="'$o'" maxOccurs="'${XSIMAX}'" />'

done < $f

cat <<EOF
 	   </xsi:sequence>   		    
    </xsi:complexType>

EOF
done

cat <<EOF

</xsi:schema>
EOF
