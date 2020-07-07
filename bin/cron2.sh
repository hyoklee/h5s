#!/bin/bash
curday=`date +"%m%d"`
# curday=`date --date="1 days ago" +"%m%d"`
fname='/mnt/hdf/hdftest/MACSIO/output/jelly_'$curday'_*'
rm /home/hyoklee/src/hdf5s/data/macsio2/*
cp $fname /home/hyoklee/src/hdf5s/data/macsio2/
cd /home/hyoklee/src/hdf5s/bin/
./mongoimport_macsio2.sh
/home/hyoklee/miniconda3/bin/python /home/hyoklee/src/hdf5s/test/beam_macsio2_mongo.py
./mongolastic_macsio2.sh

