#!/bin/bash
ESP8266_BUILD_DIR="./BIN_ESP8266"
ESP32_BUILD_DIR="./BIN_ESP32"
BIN_DATA_DIR="./BIN_DATA"

EEP_DIR="./EEP"

CHECK_ESP8266=0
CHECK_ESP32=0
CHECK_DATA=0

ESPTOOL_PARA_ESP8266="\"--baud\", \"460800\", \"write_flash\", \"0x0\", \"${1}.ino.bin\""
ESPTOOL_PARA_ESP32=""
ESPTOOL_PARA_FS=", \"0x200000\" ${1}_littlefs.bin"

if [ -d $ESP8266_BUILD_DIR ]
	then
		CHECK_ESP8266=1
fi

if [ -d $ESP32_BUILD_DIR ]
	then
		CHECK_ESP32=1
fi

if [ -d $BIN_DATA_DIR ]
	then
		CHECK_DATA=1
fi

if [ -f $1.eep ]
	then
		rm $1.eep
fi

if [ $CHECK_ESP8266 -eq 0 ] && [ $CHECK_ESP32 -eq 0 ]; then
	echo "ERROR: can not create eep without data"
	exit 1
else
	echo "start creation of eep CHECK_ESP8266=$CHECK_ESP8266 CHECK_ESP32=$CHECK_ESP32 CHECK_DATA=$CHECK_DATA"
fi

# delete target dir and create an empty new target
if [ -d $EEP_DIR ]
	then
		rm rm -r -f $EEP_DIR
fi
mkdir $EEP_DIR

if [ $CHECK_DATA -eq 1 ]; then
	cp ${BIN_DATA_DIR}/${1}_littlefs.bin ${EEP_DIR}
fi

if [ $CHECK_ESP8266 -eq 1 ]; then
	cp ${ESP8266_BUILD_DIR}/${1}.ino.bin ${EEP_DIR}/ESP8266_${1}.ino.bin
	if [ $CHECK_DATA -eq 0 ]; then
		echo "{\n\t\"command\": [${ESPTOOL_PARA_ESP8266}]\n}" > $EEP_DIR/$1.eef
	else
		echo "{\n\t\"command\": [${ESPTOOL_PARA_ESP8266}${ESPTOOL_PARA_FS}]\n}" > $EEP_DIR/$1.eef
	fi
fi
