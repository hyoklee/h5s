import apache_beam as beam
import json


outputs_prefix = 'outputs/part'

def transform_doc(document):
  out = {}
  dt = str(document['Began'])
  # Cut first 4 characters.
  v_dt = dt[4:]
  out['ts'] = v_dt
  out['value'] = document['summary'][0]['MeanTime']
  return json.dumps(out)

# Running locally in the DirectRunner.
with beam.Pipeline() as pipeline:
  (
      pipeline
      | 'Read MongoDB '  >> beam.io.mongodbio.ReadFromMongoDB(
        uri='mongodb://localhost:27017',
        db='test',
        coll='ior')
      | 'transform' >> beam.Map(transform_doc)
      | 'Write results' >> beam.io.WriteToText(outputs_prefix)
  )

