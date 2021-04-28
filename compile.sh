rm -f asali.sh
g++ main.cpp plotInterface.cpp -o asali.sh -I/usr/include/plplot -I. -lplplot -lplplotcxx
./asali.sh
