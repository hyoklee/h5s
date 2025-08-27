If standalone Apache Kafka, start ZooKeeper first, then Kafka.

```
confluent local start
python create_sample_hdf5.py
python kafka_hdf5_consumer.py
python kafka_hdf5_producer.py
```
