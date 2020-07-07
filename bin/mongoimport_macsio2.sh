#!/bin/bash

# List all items in the input table.
# mongo --eval "db.macsioinputs.find()" macsio
# Drop input table.
mongo --eval "db.macsioinputs.drop()" macsio2

# List all items in the output table.
# mongo --eval "db.macsiooutputs.find()" macsio
# Drop output table.
mongo --eval "db.macsiooutputs.drop()" macsio2


# Go over IOR json files and import them to MongoDB.
#for file in ../data/macsio2/*.json
for file in ../data/macsio2/*
do
  echo $file
  mongoimport -d macsio2 -c macsioinputs $file
done
