import apache_beam as beam



outputs_prefix = 'outputs/part'

def transform_doc(document):
  return {'summary': str(document['summary'][0]['MeanTime'])}

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

