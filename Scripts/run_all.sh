#!/bin/sh

SKETCH_NAME=ESP_jQuery_Mobile_Interface
ESP_SCRIPT_DIR=./ESP_Action_Build_Scripts
TAG="all"

HELP="Paramter:\n
-t\ttag=all/build/eep\n
-h\thelp\n"

while getopts t:h flag
do
    case "${flag}" in
        t) TAG=${OPTARG};;
		h) echo $HELP; exit 0;
    esac
done

echo "TAG=$TAG"

if [ $TAG = "all" ]; then
	echo "### clean up ###"
	#git clean -xdf
fi

if [ $TAG = "all" ] || [ $TAG = "build" ]; then
	echo "### build ###"
	#sh ESP_Action_Build_Scripts/build_sketch.sh -s $SKETCH_NAME -c esp32 -b d1_mini32 -f 160
	#sh ESP_Action_Build_Scripts/build_sketch.sh -s $SKETCH_NAME -c esp8266 -b d1_mini -f 160
fi

if [ $TAG = "all" ] || [ $TAG = "eep" ]; then
	echo "### create eep ###"
	ARTIFACT_DIR=./Artifacts
	EEP=./EEP
	
	if [ ! -d $ARTIFACT_DIR ]; then
		mkdir $ARTIFACT_DIR
	fi
	
	if [ -d $EEP ]; then
		cd $EEP
		zip -r .${ARTIFACT_DIR}/${SKETCH_NAME}.zip *
		cd ..
	else
		echo "Error: $EEP does not exist, can not create eep package"
	fi	
fi