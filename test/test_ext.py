import h5py
import numpy as np

c = h5py.File('c.h5', 'w')
arr_c = np.arange(10)
dset_c = c.create_dataset("dset", data=arr_c)
b = h5py.File('b.h5', 'w')
arr = np.arange(100)
dset = b.create_dataset("dset", data=arr)
b['ext link'] = h5py.ExternalLink("c.h5", "/dset")
a = h5py.File('a.h5','w')
a['ext link'] = h5py.ExternalLink("b.h5", "/dset")
