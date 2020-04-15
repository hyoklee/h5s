#!/bin/bash
curday=`date +"%m%d"`
# curday=`date --date="1 days ago" +"%m%d"`
fname='/mnt/hdf/hdftest/MACSIO/output/jelly_'$curday'_*'
rm /home/hyoklee/src/hdf5s/data/macsio/*
cp $fname /home/hyoklee/src/hdf5s/data/macsio/
cd /home/hyoklee/src/hdf5s/bin/
./mongoimport_macsio.sh
/home/hyoklee/miniconda3/bin/python /home/hyoklee/src/hdf5s/test/beam_macsio_mongo.py
./mongolastic_macsio.sh
