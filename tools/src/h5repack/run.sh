rm d.h5
make >& make.log
./h5repack -v -X a.h5 d.h5 >& h5repack.log
../h5dump/h5dump d.h5 >& h5dump.log

