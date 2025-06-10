import h5py
import json
import numpy as np
from confluent_kafka import Producer
import time

# Kafka configuration
KAFKA_BOOTSTRAP_SERVERS = 'localhost:9092'  # Adjust if your Kafka is elsewhere
KAFKA_TOPIC = 'hdf5_json_stream'
HDF5_FILENAME = 'sample_data.h5'

def numpy_to_json_serializable(obj):
    """
    Converts NumPy arrays and types to JSON serializable Python types.
    """
    if isinstance(obj, np.ndarray):
        return obj.tolist()
    elif isinstance(obj, (np.integer, np.floating, np.bool_)):
        return obj.item()
    elif isinstance(obj, bytes):
        return obj.decode('utf-8')
    return obj

def delivery_report(err, msg):
    """ Called once for each message produced to indicate delivery result. """
    if err is not None:
        print(f"Message delivery failed: {err}")
    else:
        print(f"Message delivered to topic {msg.topic()} [{msg.partition()}] at offset {msg.offset()}")

def produce_hdf5_data():
    """
    Reads data from HDF5 and produces it as JSON to Kafka.
    """
    producer_conf = {
        'bootstrap.servers': KAFKA_BOOTSTRAP_SERVERS,
        'client.id': 'hdf5-producer'
    }

    producer = Producer(producer_conf)

    try:
        with h5py.File(HDF5_FILENAME, 'r') as f:
            print(f"Reading data from HDF5 file: {HDF5_FILENAME}")

            # Iterate through all objects in the HDF5 file
            def process_hdf5_object(name, obj):
                if isinstance(obj, h5py.Dataset):
                    print(f"Processing dataset: /{name}")
                    data_to_stream = {
                        'path': f'/{name}',
                        'data': numpy_to_json_serializable(obj[()]), # Read entire dataset
                        'dtype': str(obj.dtype),
                        'shape': obj.shape
                    }
                    # Add attributes if any
                    if obj.attrs:
                        data_to_stream['attributes'] = {k: numpy_to_json_serializable(v) for k, v in obj.attrs.items()}

                    json_message = json.dumps(data_to_stream)
                    producer.produce(KAFKA_TOPIC, key=name.encode('utf-8'), value=json_message.encode('utf-8'), callback=delivery_report)
                    producer.poll(0) # Non-blocking poll for delivery reports
                elif isinstance(obj, h5py.Group):
                    print(f"Processing group: /{name}")
                    # You could choose to send group information if needed
                    pass

            f.visititems(process_hdf5_object)

        # Wait for any outstanding messages to be delivered and delivery reports received
        producer.flush()
        print("Finished producing HDF5 data.")

    except FileNotFoundError:
        print(f"Error: HDF5 file '{HDF5_FILENAME}' not found. Please run 'create_sample_hdf5.py' first.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    produce_hdf5_data()
    