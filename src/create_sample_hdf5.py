import h5py
import numpy as np
import json

def create_sample_hdf5(filename="sample_data.h5"):
    """
    Creates a sample HDF5 file with various datasets.
    """
    with h5py.File(filename, 'w') as f:
        # Create a group
        g1 = f.create_group('group1')

        # Create datasets within the group
        g1.create_dataset('dataset_int', data=np.array([1, 2, 3, 4, 5]), dtype='i4')
        g1.create_dataset('dataset_float', data=np.array([10.1, 20.2, 30.3]), dtype='f8')
        g1.create_dataset('dataset_string', data=np.array(['hello', 'world', 'HDF5'], dtype=h5py.string_dtype(encoding='utf-8')))

        # Create another dataset directly under root
        f.create_dataset('metrics', data=np.array([[100, 200], [300, 400]]), dtype='i4')

        # Create a dataset with attributes
        dset_attr = f.create_dataset('metadata_info', data='Important Information')
        dset_attr.attrs['version'] = '1.0'
        dset_attr.attrs['author'] = 'Kafka HDF5 Streamer'

    print(f"Sample HDF5 file '{filename}' created successfully.")

if __name__ == "__main__":
    create_sample_hdf5()
