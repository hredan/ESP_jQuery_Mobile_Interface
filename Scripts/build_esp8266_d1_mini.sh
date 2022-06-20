#!/bin/bash
SCRIPT_DIR=${0%/*}
SKETCH_NAME=ESP_jQuery_Mobile_Interface
CORE=esp8266
BOARD=d1_mini
CPUF=80

SCRIPT_DIR=${0%/*}

# cleanup EEP directory before starting build and creating eef package (eep)
EEP_DIR=${SCRIPT_DIR}/../EEP
if [ -d ${EEP_DIR} ]; then
    rm -r ${EEP_DIR}
fi

# build ESP binaries
bash ${SCRIPT_DIR}/../ESP_Build_Scripts/build_sketch.sh -s ${SKETCH_NAME} -c ${CORE} -b ${BOARD} -f ${CPUF}

# create zip file (eef package)
if [ -d ${EEP_DIR} ]; then
     zip -j ${CORE}_${BOARD}_${SKETCH_NAME}.eep ${EEP_DIR}/*
else
    echo "Error could not find directory "
fi