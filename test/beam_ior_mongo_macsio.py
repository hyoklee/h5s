import apache_beam as beam
import json
import datetime

outputs_prefix = 'outputs/part'

def transform_doc(document):
  out = {}


  # Handle timestamp.
  dt = str(document['now'])
  
  # Cut first 4 characters.
  v_dt = dt[4:]
  # %B = Month %d = day
  dto = datetime.datetime.strptime(v_dt, '%b  %d %H:%M:%S %Y')
  s_e = dto.strftime('%Y-%m-%dT%H:%M:%SZ')
  out['ts'] = s_e

  # Handle metric values.
  out['Mi'] = document['Mi']
  out['msecs'] = document['msecs']
  out['Mi/sec'] = document['Mi/sec']
  out['procs'] = document['procs']


  # Handle args
  out['args'] = document['args']

  return out
  # For text output.
  # return json.dumps(out) 

# Running locally in the DirectRunner.
with beam.Pipeline() as pipeline:
  (
      pipeline
      | 'Read MongoDB '  >> beam.io.mongodbio.ReadFromMongoDB(
        uri='mongodb://localhost:27017',
        db='macsio',
        coll='macsioinputs')
      | 'transform' >> beam.Map(transform_doc)
      | 'Write MongoDB' >> beam.io.mongodbio.WriteToMongoDB(
        uri='mongodb://localhost:27017',
        db='macsio',
        coll='macsiooutputs',
        batch_size=10)
      # | 'Write results' >> beam.io.WriteToText(outputs_prefix)
  )

