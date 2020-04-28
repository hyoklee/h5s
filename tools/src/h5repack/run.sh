rm d.h5
make
./h5repack -v -X a.h5 d.h5
../h5dump/h5dump d.h5
