import apache_beam as beam
import json
import datetime

outputs_prefix = 'outputs/part'

def transform_doc(document):
  out = {}
  dt = str(document['Began'])
  # Cut first 4 characters.
  v_dt = dt[4:]
  dto = datetime.datetime.strptime(v_dt, '%b %d %H:%M:%S %Y')
  s_e = dto.strftime('%Y-%m-%dT%H:%M:%SZ')
  out['ts'] = s_e
  out['value'] = document['summary'][0]['MeanTime']
  return out
  # For text output.
  # return json.dumps(out) 

# Running locally in the DirectRunner.
with beam.Pipeline() as pipeline:
  (
      pipeline
      | 'Read MongoDB '  >> beam.io.mongodbio.ReadFromMongoDB(
        uri='mongodb://localhost:27017',
        db='test',
        coll='ior')
      | 'transform' >> beam.Map(transform_doc)
      | 'Write MongoDB' >> beam.io.mongodbio.WriteToMongoDB(
        uri='mongodb://localhost:27017',
        db='test',
        coll='output',
        batch_size=10)
      # | 'Write results' >> beam.io.WriteToText(outputs_prefix)
  )

