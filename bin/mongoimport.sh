#!/bin/bash
# Drop DB.
mongo --eval "db.ior.drop()"
mongo --eval "db.output.drop()"

# Go over IOR json files and import them to MongoDB.
for file in ../data/ior/*ior.*
do
  echo $file
  mongoimport -d test -c ior $file
done
