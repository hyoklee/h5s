import h5py
import numpy as np

a = h5py.File('a.h5','w')
arr_a = np.arange(5)
dset_a = a.create_dataset("dset", data=arr_a)
c = h5py.File('c.h5', 'w')
c['ext link'] = h5py.ExternalLink("a.h5", "/dset")
b = h5py.File('b.h5', 'w')
b['ext link'] = h5py.ExternalLink("c.h5", "/ext link")
a['ext link'] = h5py.ExternalLink("b.h5", "/ext link")


