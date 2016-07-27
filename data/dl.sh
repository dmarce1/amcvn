#scp neutron:/media/dmarce1/DWD4/arc/0.20/sample/virial.dat virial_end.dat
g++ ../code/transform.cpp
./a.out virial_end.dat 3 > out1
./a.out virial_end.dat 4 > out2
./a.out virial_end.dat 5 > out3
g++ -std=c++11 -O3 ../code/proc.cpp 
./a.out silo.dat
rm a.out




