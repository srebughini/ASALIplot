rm -f asali.sh
g++ main.cpp plotInterface.cpp -o asali.sh -I/usr/include/plplot -I. -lplplot -lplplotcxx -DASALI_ON_WINDOWS=0
./asali.sh
