#!/bin/bash
# Drop DB.
mongo --eval "db.macsioinputs.drop()"
# mongo --eval "db.macsiooutputs.drop()"

# Go over IOR json files and import them to MongoDB.
for file in ../data/macsio/*.json
do
  echo $file
  mongoimport -d test -c macsioinputs $file
done
