-- Devel
SELECT
  starttime AS "time",
  name AS metric,
  buildwarnings
FROM build
WHERE
  $__timeFilter(starttime) AND
  name LIKE '%hdf5trunk_hdf_develop%' AND
  name NOT LIKE '%byrne%'
ORDER BY name, starttime

-- 1.12
SELECT
  starttime AS "time",
  name AS metric,
  buildwarnings
FROM build
WHERE
  $__timeFilter(starttime) AND
  name LIKE '%hdf5_1_12%'
ORDER BY name, starttime

-- 1.10
SELECT
  starttime AS "time",
  name AS metric,
  buildwarnings
FROM build
WHERE
  $__timeFilter(starttime) AND
  name LIKE '%hdf5_1_10%'
ORDER BY name, starttime

-- 1.8
SELECT
  starttime AS "time",
  name AS metric,
  buildwarnings
FROM build
WHERE
  $__timeFilter(starttime) AND
  name LIKE '%hdf5_1_8%' AND buildwarnings > -1
ORDER BY name, starttime
