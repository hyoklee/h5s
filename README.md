# h5s

  This is an experimental HDF5-like library with
  
  **s**ecurity (e.g., OpenSSH),
  **s**treaming (e.g., Apache Kafka), and
  **s**earching (e.g., Elasticsearch) capability. 

  This is not free software.
  
  Please contact hyoklee@hdfgroup.org if you'd like to buy it.

# Usage

## Security

`h5s -i key cat (server:)/path/to/file.h5s/dset`
  
## Streaming

### Producer

`h5s -p (server:)path/to/file.h5s/topic < input`

### Consumer

`h5s -c (server:)path/to/file.h5s/topic`

### Watcher

[Apple Watch](https://youtu.be/qdjAHVON01s)


## Searching

### AI

`h5s -a "List all groups." [directory|file]`

### Grep

`h5s -r regex [directory|file]` 

### SQL

`h5s -s "SELECT * from [directory|file]/dset1"`


# FAQ

## Security

  h5s runs on default OpenBSD (clusters) only. No port package is required.

## Streaming Peformance

 `pkg_add iperf3` can help.

 h5s can use [AWS Timestream](https://aws.amazon.com/timestream/) as a backend.

## Search Performance

  1PB in 1 sec.
