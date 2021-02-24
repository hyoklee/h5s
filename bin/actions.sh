#!/bin/bash
# List runs [1].
curl \
  -H "Accept: application/vnd.github.v3+json" \
  https://api.github.com/repos/HDFGroup/hdf5/actions/runs

# Get a run.
curl \
  -H "Accept: application/vnd.github.v3+json" \
  https://api.github.com/repos/HDFGroup/hdf5/actions/runs/596012632

# List jobs.
curl \
  -H "Accept: application/vnd.github.v3+json" \
  https://api.github.com/repos/HDFGroup/hdf5/actions/runs/596012632/jobs

# Get a job.
curl \
  -H "Accept: application/vnd.github.v3+json" \
  https://api.github.com/repos/HDFGroup/hdf5/actions/jobs/1970032915

# Download a specific job log (e.g., Ubuntu), which requires a developer token [2].
curl \
    -H 'Authorization: token XXXXXXXX' \
    -H 'Accept: application/vnd.github.v3+json' \
  -O -L https://api.github.com/repos/HDFGroup/hdf5/actions/jobs/1970032915/logs


# Download the entire run log, which requires a developer token.
  curl \
      -H 'Authorization: token XXXXXXXX' \
      -H 'Accept: application/vnd.github.v3.raw' \
      -O -L  https://api.github.com/repos/HDFGroup/hdf5/actions/runs/596012632/logs


# List artifacts
curl \
  -H "Accept: application/vnd.github.v3+json" \
  https://api.github.com/repos/HDFGroup/hdf5/actions/artifacts


# Reference
# 1. https://docs.github.com/en/rest/reference/actions
# 2. https://github.com/settings/tokens
