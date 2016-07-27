

set terminal png



set title ""
set xlabel "Period"

set ylabel "-d log(M_2) / dt"
set format y "%.1t x 10^{%T}"
set output "mdot.png"
plot "dot_log.dat" u 1:(-$7) w lines t ""

set ylabel "-d log(a) / dt"
set format y "%.1t x 10^{%T}"
set output "adot.png"
plot "dot_log.dat" u 1:(-$3) w lines t ""

set ylabel "-d log(J_{orb}) / dt"
set format y "%.1t x 10^{%T}"
set output "jdot.png"
plot "dot_log.dat" u 1:(-$4) w lines t ""

set ylabel ""
set output "jorb.png"
set key bottom
plot "dot_log.dat" u 1:4 w lines t "d log(J_{orb}) / dt", "dot_log.dat" u 1:($6+$7+0.5*$3) w lines t "d (log(M_1) + log(M_2) + log(a)/2) / dt"


set title ""
set ylabel ""
set xlabel "Orbital Frequencies"
set out "disc_pow.png"
set xrange [0.1:15]
plot "out1" u 1:(($2*$2+$3*$3)) w lines t "gas energy", "out2" u 1:(($2*$2+$3*$3)) w lines t "potential energy", "out3" u 1:(($2*$2+$3*$3)) w lines t "moment of inertia"



