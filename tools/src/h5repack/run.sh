rm d.h5
make >& make.log
./h5repack -v -x 1 a.h5 d.h5 >& x.log
./h5repack -v -X -x 1 a.h5 d.h5 >& h5repack.log
../h5dump/h5dump d.h5 >& h5dump.log

