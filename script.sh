cd data
#./dl.sh
#g++ -std=c++11 -O3 proc.cpp 
#./a.out silo.dat
gnuplot gnuplot.sh
mv *.png ../images/
cd ..
pdflatex paper
bibtex paper
pdflatex paper
pdflatex paper

