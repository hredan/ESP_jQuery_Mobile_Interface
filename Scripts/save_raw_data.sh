#!/bin/bash
ARTIFACT_DIR="./Artifacts"
ESP8266_BUILD_DIR="./BIN_ESP8266"
ESP32_BUILD_DIR="./BIN_ESP32"
BIN_DATA_DIR="./BIN_DATA"

OUTPUT_ZIP_PATH="$ARTIFACT_DIR/raw_build_data.zip"

mkdir $ARTIFACT_DIR

if [ -f $OUTPUT_ZIP_PATH ]
	then
		echo "delete $OUTPUT_ZIP_PATH"
		rm $OUTPUT_ZIP_PATH
fi

sh ./Scripts/save_dir2file.sh $ESP8266_BUILD_DIR $OUTPUT_ZIP_PATH
sh ./Scripts/save_dir2file.sh $ESP32_BUILD_DIR $OUTPUT_ZIP_PATH
sh ./Scripts/save_dir2file.sh $BIN_DATA_DIR $OUTPUT_ZIP_PATH

