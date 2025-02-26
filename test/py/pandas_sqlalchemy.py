import pandas as pd
import sqlalchemy as sql
connect_string = 'mysql://joe_read:********@10.10.10.82/cdash'
sql_engine = sql.create_engine(connect_string)
query = "SELECT buildid, testid FROM build2test LIMIT 10"
df = pd.read_sql_query(query, sql_engine)
print(df)
