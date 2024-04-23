import pandas as pd
df = pd.read_json('splunk-00000-of-00001.json', lines=True)
df.to_csv('ior_superset.csv')

