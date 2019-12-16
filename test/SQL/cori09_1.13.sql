SELECT
  starttime AS "time",
  name AS metric,
  testpassed
FROM build
WHERE
  $__timeFilter(starttime) AND
  name LIKE '%cori09%'
ORDER BY starttime
