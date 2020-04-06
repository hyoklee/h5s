#!/bin/bash

# List all items in the input table.
# mongo --eval "db.macsioinputs.find()" macsio
# Drop input table.
mongo --eval "db.macsioinputs.drop()" macsio

# List all items in the output table.
# mongo --eval "db.macsiooutputs.find()" macsio
# Drop output table.
# mongo --eval "db.macsiooutputs.drop() macsio"


# Go over IOR json files and import them to MongoDB.
for file in ../data/macsio/*.json
do
  echo $file
  mongoimport -d macsio -c macsioinputs $file
done
