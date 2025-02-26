# h5s

  This is an experimental HDF5 library with enhanced **s**ecurity,
  **s**treaming (e.g., Apache Kafka), and **s**earching
  (e.g., Elasticsearch) capability. 

  This is not free software.
  Please contact hyoklee@hdfgroup.org if you'd like to buy and try it.

# Usage

## Security

  Run `make` on OpenBSD 7.6.
  
## Streaming

### Producer

`bin/h5p`

### Consumer

`bin/h5c`

### Watcher

[Apple Watch](https://youtu.be/qdjAHVON01s)


## Searching

### Grep

`bin/h5s -r regex [directory|file]` 

### SQL

`bin/h5s -s "SELECT * from [directory|fie]/dset1"`

# FAQ

## Security: OpenBSD Only

 I don't care other platforms that have too many security holes.
  
## Streaming Peformance
  
 `pkg_add iperf`
 
 h5s can use [AWS Timestream](https://aws.amazon.com/timestream/) as backend.

## Search Performance

  1PB in 1 sec.

  

  
