#!/bin/bash

sudo mysql << EOF
DROP DATABASE KK;
CREATE DATABASE KK;
EOF

declare -A dict

while true
do
echo "SSSS1" 
line1=$(mosquitto_sub -t '/#' 2>&1)
echo "SSSS2" 
line2=$(mosquitto_sub -t '/#' 2>&1)
echo "SSSS3" 
#while read -r line1;read -r line2;
#do

echo $line1
echo $line2
#sed -i '1,2d' data.txt
type="${line1:0:2}"
mac="${line1:2:9}"
echo $type
echo $mac

name=$mac

if [ -v dict[$mac] ]; then
echo "exists"
sudo mysql << EOF
USE KK;
INSERT INTO $name VALUE ( ${type} , "$line2" );
EOF
fi

if [ ! -v dict[$mac] ]; then
dict[$mac]=1
echo "added"

echo ${line2}
sudo mysql << EOF
USE KK;
CREATE TABLE $name (type VARCHAR(100) NOT NULL,value VARCHAR(50) NOT NULL);
INSERT INTO $name VALUE ( ${type} , "$line2" );
EOF

fi

#done < data.txt
#sleep 5
done


