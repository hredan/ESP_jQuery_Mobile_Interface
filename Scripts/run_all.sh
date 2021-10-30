#!/bin/bash
# clean folder
git clean -xdf
# define sketch name
SKETCH_NAME=ESP_jQuery_Mobile_Interface
#create data bin
sh ./Scripts/build_data.sh $SKETCH_NAME