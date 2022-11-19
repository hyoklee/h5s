# h5s

  This is an experimental HDF5 library with enhanced **s**ecurity, **s**treaming (e.g., Apache Kafka) and
 **s**earching (e.g., Elasticsearch) capability. 

  This is not free software. Please contact hyoklee@hdfgroup.org if you'd like to buy and try it.

# Usage

## Streaming

### Producer

`bin/h5p`

### Consumer

`bin/h5c`

## Searching

`bin/h5s regex [directory|file]`

# FAQ

## OpenBSD Only

 I don't care other platforms that have too many security holes.
  
## Streaming Peformance
  
 `pkg_add iperf`
  
### Search Performance

  1PB in 1 sec.
  
### Streaming Performance

  h5s can use [AWS Timestream](https://aws.amazon.com/timestream/) as backend.
  

  
