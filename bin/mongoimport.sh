#!/bin/bash

# Go over IOR json files and import them to MongoDB.
for file in ../data/ior/*.json
do
  echo $file
  mongoimport -d test -c ior $file
done
