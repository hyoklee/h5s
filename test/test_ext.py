# This program tests h5 external links.
import h5py
import numpy as np

# Slave
c = h5py.File('c.h5', 'w')
arr_c = np.arange(10)
dset_c = c.create_dataset("dset", data=arr_c)

# Master and Slave
b = h5py.File('b.h5', 'w')
arr = np.arange(100)
dset = b.create_dataset("dset", data=arr)
b['ext link'] = h5py.ExternalLink("c.h5", "/dset")

# Master
a = h5py.File('a.h5','w')
a['ext link to dset'] = h5py.ExternalLink("b.h5", "/dset")
a['ext link to link'] = h5py.ExternalLink("b.h5", "/ext link")
a['ext link to root'] = h5py.ExternalLink("b.h5", "/")
