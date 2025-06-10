import json
import h5py
import numpy as np
from confluent_kafka import Consumer, KafkaException, OFFSET_BEGINNING

# Kafka configuration
KAFKA_BOOTSTRAP_SERVERS = 'localhost:9092'  # Adjust if your Kafka is elsewhere
KAFKA_TOPIC = 'hdf5_json_stream'
KAFKA_GROUP_ID = 'hdf5-json-consumer-group'

def consume_hdf5_data():
    """
    Consumes JSON messages from Kafka and prints the HDF5 data.
    """
    consumer_conf = {
        'bootstrap.servers': KAFKA_BOOTSTRAP_SERVERS,
        'group.id': KAFKA_GROUP_ID,
        'auto.offset.reset': 'earliest' # Start consuming from the beginning of the topic if no offset is committed
    }

    consumer = Consumer(consumer_conf)

    try:
        consumer.subscribe([KAFKA_TOPIC])
        print(f"Subscribed to topic: {KAFKA_TOPIC}. Waiting for messages...")

        while True:
            msg = consumer.poll(timeout=1.0) # Poll for messages with a 1-second timeout

            if msg is None:
                continue
            if msg.error():
                if msg.error().code() == KafkaException.PARTITION_EOF:
                    # End of partition event - not an error
                    print(f"%% {msg.topic()} [{msg.partition()}] reached end at offset {msg.offset()}")
                elif msg.error():
                    raise KafkaException(msg.error())
            else:
                # Proper message received
                key = msg.key().decode('utf-8') if msg.key() else 'N/A'
                value = msg.value().decode('utf-8')

                try:
                    data_received = json.loads(value)
                    print(f"\n--- Received message ---")
                    print(f"Key: {key}")
                    print(f"Path: {data_received.get('path', 'N/A')}")
                    print(f"Data Type: {data_received.get('dtype', 'N/A')}")
                    print(f"Shape: {data_received.get('shape', 'N/A')}")
                    print(f"Data: {data_received.get('data', 'N/A')}")
                    if 'attributes' in data_received:
                        print(f"Attributes: {data_received['attributes']}")

                    # Example of how you might reconstruct a NumPy array (optional)
                    # if 'data' in data_received and 'dtype' in data_received and 'shape' in data_received:
                    #     reconstructed_array = np.array(data_received['data'], dtype=data_received['dtype']).reshape(data_received['shape'])
                    #     print(f"Reconstructed NumPy array type: {type(reconstructed_array)}")
                    #     print(f"Reconstructed NumPy array: {reconstructed_array}")

                except json.JSONDecodeError as e:
                    print(f"Error decoding JSON: {e} - Message value: {value}")
                except Exception as e:
                    print(f"Error processing message: {e}")

    except KeyboardInterrupt:
        print("Consumer stopped by user.")
    finally:
        consumer.close()
        print("Consumer closed.")

if __name__ == "__main__":
    consume_hdf5_data()
