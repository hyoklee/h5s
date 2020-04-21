import h5py
import numpy as np

# Slave
c = h5py.File('c.h5', 'w')
arr_c = np.arange(10)
dset_c = c.create_dataset("dset", data=arr_c)

# 2 Master and Slave
b1 = h5py.File('b1.h5', 'w')
arr = np.arange(100)
dset = b1.create_dataset("dset", data=arr)
b1['ext link'] = h5py.ExternalLink("c.h5", "/dset")

b2 = h5py.File('b2.h5', 'w')
arr = np.arange(50)
dset = b2.create_dataset("dset", data=arr)
b2['ext link'] = h5py.ExternalLink("c.h5", "/dset")

# 1 Mastger
a = h5py.File('a.h5','w')
arr_a = np.arange(5)
dset_a = a.create_dataset("dset", data=arr_a)
a['ext link1'] = h5py.ExternalLink("b1.h5", "/dset")
a['ext link2'] = h5py.ExternalLink("b2.h5", "/dset")


