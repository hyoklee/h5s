# h5s

  This is an experimental HDF5 library with **s**treaming (e.g., Apache Kafka) and
 **s**earching (e.g., Elastic Search) capability. 

  This is not free software. Please contact hyoklee@hdfgroup.org if you'd like to buy and try it.

# Usage

## Streaming

### Producer

`bin/h5p`

### Consumer

`bin/h5c`

## Searching

`bin/h5s pattern [directory|file]`

# FAQ

## Patch for g++-8 on Mac

  See src/ for affected files.
  
## Peformance
  
  Test was done on GitHub Actions.
  
### Search Performance

 1PB in 1 sec.
  
### Streaming Performance

  h5s can use [AWS Timestream](https://aws.amazon.com/timestream/) as backend.
  

  
