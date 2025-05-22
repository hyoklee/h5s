# h5s

  This is an experimental HDF5 library with
  **s**ecurity (e.g., OpenSSH),
  **s**treaming (e.g., Apache Kafka), and
  **s**earching (e.g., Elasticsearch) capability. 

  This is not free software.
  Please contact hyoklee@hdfgroup.org if you'd like to buy it.

# Usage

## Security

  Run `make` on OpenBSD 7.7.
  
## Streaming

### Producer

`h5s -p`

### Consumer

`h5s -c`

### Watcher

[Apple Watch](https://youtu.be/qdjAHVON01s)


## Searching

### AI

`h5s -a "List all groups."`

### Grep

`h5s -r regex [directory|file]` 

### SQL

`h5s -s "SELECT * from [directory|fie]/dset1"`

# FAQ

## Security

  h5s runs on OpenBSD only.
  
## Streaming Peformance
  
 `pkg_add iperf`
 
 h5s can use [AWS Timestream](https://aws.amazon.com/timestream/) as backend.

## Search Performance

  1PB in 1 sec.

  

  
