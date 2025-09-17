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

# Testing

## GitHub Actions

The repository includes automated testing via GitHub Actions:

- **OpenBSD Testing** - Tests H5S implementation on OpenBSD 7.7
- **Ubuntu Testing** - Tests H5S implementation on Ubuntu Latest

The workflows automatically:
- Install HDF5 packages and development tools
- Build the H5S writer (`src/w.c`) and reader (`src/r.c`)
- Test file creation and reading
- Validate with `h5dump` from the official HDF5 tools
- Generate hex dumps for debugging

## Local Testing

Build and test locally:
```bash
# Make test script executable
chmod +x test-local.sh

# Run complete test suite
./test-local.sh
```

Manual build and test:
```bash
# Build components
gcc -o w src/w.c
gcc -o r src/r.c

# Create HDF5 file
./w

# Read HDF5 file
./r test.h5

# Test with official tools (if available)
h5dump test.h5
```

# FAQ

## Security

  h5s runs on OpenBSD only.

## Streaming Peformance

 `pkg_add iperf`

 h5s can use [AWS Timestream](https://aws.amazon.com/timestream/) as backend.

## Search Performance

  1PB in 1 sec.
