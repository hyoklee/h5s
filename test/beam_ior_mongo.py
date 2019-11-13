import apache_beam as beam
import json
import datetime

outputs_prefix = 'outputs/part'

def transform_doc(document):
  out = {}


  # Handle timestamp.
  dt = str(document['Began'])
  
  # Cut first 4 characters.
  v_dt = dt[4:]
  dto = datetime.datetime.strptime(v_dt, '%b %d %H:%M:%S %Y')
  s_e = dto.strftime('%Y-%m-%dT%H:%M:%SZ')
  out['ts'] = s_e

  # Handle API and version.
  api = str(document['tests'][0]['Options']['api'])
  apv = str(document['tests'][0]['Options']['apiVersion'])
  out['api'] = api
  out['apv'] = apv

  # Handle clients per node, tasks, and aggregate file size.
  cpn = document['tests'][0]['Options']['clients per node']
  tsk = document['tests'][0]['Options']['tasks']
  agf = document['tests'][0]['Options']['aggregate filesize']
  
  out['cpn'] = cpn
  out['tsk'] = tsk
  out['agf'] = agf

  # Handle metric values.
  out['wmt'] = document['summary'][0]['MeanTime']
  out['wbw'] = document['summary'][0]['bwMeanMIB']
  out['rmt'] = document['summary'][1]['MeanTime']
  out['rbw'] = document['summary'][1]['bwMeanMIB']

  # TO-DO: tasksPerNode?

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

