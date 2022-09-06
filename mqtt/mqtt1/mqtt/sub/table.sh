#!/bin/bash

name=$1
type=$2
line2=$3
coi=$4
name+="a"
mac=name
if [ "$coi" = "1" ]; then
sudo mysql << EOF
USE KK;
INSERT INTO $name VALUE ( ${type} , "$line2" );
EOF
fi

if [ "$coi" = "0" ]; then
sudo mysql << EOF
USE KK;
CREATE TABLE ${name} (type VARCHAR(300) NOT NULL,value VARCHAR(300) NOT NULL);
INSERT INTO ${name} VALUE ( ${type} , "$line2" );
EOF

fi
