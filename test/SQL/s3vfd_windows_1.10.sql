SELECT
  starttime AS "time",
  name AS metric,
  testpassed
FROM build
WHERE
  $__timeFilter(starttime) AND
  name LIKE '%hdf5110%S3VFD%Windows%' AND
  name NOT LIKE '%byrne%'
ORDER BY starttime
