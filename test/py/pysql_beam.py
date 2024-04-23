# Usage:
# $python psql_beam.py --host localhost --port 3306 --database SECRET_DATABASE --username SECRET_USER --password SECRET_PASSWORD --table YOUR_TABLE --output YOUR_OUTPUT_FLLE

import logging
import apache_beam as beam
from pysql_beam.sql_io.sql import ReadFromSQL
from apache_beam.options.pipeline_options import PipelineOptions, SetupOptions

logging.getLogger().setLevel(logging.WARNING)
pipeline_options = PipelineOptions()
options = pipeline_options.view_as(SQLOptions)
options.view_as(SetupOptions).save_main_session = True
pipeline = beam.Pipeline(options=options)
mysql_data = pipeline | ReadFromSQL(host=self.options.host,
                                    port=self.options.port,
                                    username=self.options.username,
                                    password=self.options.password,
                                    databse=self.options.database,
                                    query=self.options.source_query,
                                    wrapper=MySQLWrapper,
                                    batch=100000)
mysql_data | "Log records " >> beam.Map(log) | beam.io.WriteToText(options.output, num_shards=1, file_name_suffix=".json")
pipeline.run().wait_until_finish()
